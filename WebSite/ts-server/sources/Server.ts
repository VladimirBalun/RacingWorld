/*
 * Copyright 2018 Vladimir Balun
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

"use strict";

import * as _ from "underscore";
import * as express from "express";
import * as bodyParser from "body-parser";

import * as log4js from "log4js";
const log = log4js.getLogger(__filename);
log.level = "debug";

import News from "./data/entity/News";
import NewsService from "./data/service/NewsServiceImplementation";

class Server {

    private express;

    constructor () {
        this.express = express();
        this.express.use(bodyParser.json());
        this.express.use(bodyParser.urlencoded({ extended: true }));
        this.route();
    }

    private route (): void {
        const router = express.Router();
        const newsService = new NewsService();

        router.get("/news", (request, response) => {
            const news: News[] = newsService.getAllNews();
            if (!_.isEmpty(news)) {
                response.status(200).json(news);
            } else {
                response.status(404).json([]);
            }
        });

        router.get("/news/:id", (request, response) => {
            const id: number = request.params.id;
            const news: News = newsService.getNewsByID(id);
            if (!_.isEmpty(news)) {
                response.status(200).json(news);
            } else {
                response.status(404).json({});
            }
        });

        router.post("/news", (request, response) => {
            const title: string = request.body.title;
            const description: string = request.body.description;
            const date: Date = request.body.date;
            const addingResult: boolean = newsService.addNews(new News(title, description, date));
            if (addingResult) {
                response.status(201).json({ result: true });
            } else {
                response.status(400).json({ result: false });
            }
        });

        this.express.use("/", router);
    }

    public start(port: number): void {
        this.express.listen(port, (error) => {
            if (!error) {
                log.info(`Server was started successfully. Port: ${port}`);
            } else {
                log.fatal(`Server was not started. Cause: ${error}`);
                process.exit();
            }
        });
    }

}

export default Server;