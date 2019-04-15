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
import express from "express";
import * as bodyParser from "body-parser";
import * as mime from "mime";
import * as log4js from "log4js";
import * as fs from "fs";
import * as path from "path";

const log = log4js.getLogger(__filename);
log.level = "debug";

import News from "./data/entity/News";
import NewsService from "./data/service/NewsServiceImplementation";

enum statusCode{
    OK = 200,
    Created = 201,
    BadRequest = 400,
    NotFound = 404,
}


class Server {

    private express;

    constructor () {
        this.express = express();
        this.express.use(bodyParser.json());
        this.express.use(bodyParser.urlencoded({ extended: true }));
        this.route();
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

    private route (): void {
        const router = express.Router();
        const newsService = new NewsService();

        router.get("/news", async (request, response) => {
            const news: News[] = await newsService.getAllNews();
            if (!_.isEmpty(news)) {
                response.status(statusCode.OK).json(news);
            } else {
                response.status(statusCode.NotFound).json([]);
            }
        });

        router.get("/news/:id", async (request, response) => {
            const id: number = request.params.id;
            const news: News | Array<string> = await newsService.getNewsByID(id);
            if (!_.isEmpty(news)) {
                response.status(statusCode.OK).json(news);
            } else {
                response.status(statusCode.NotFound).json({});
            }
        });

        router.post("/news", async (request, response) => {
            const title: string = request.body.title;
            const description: string = request.body.description;
            const date: Date = request.body.date;
            const addingResult: boolean = await newsService.addNews(new News(title, description, date));
            if (addingResult) {
                response.status(statusCode.Created).json({ result: true });
            } else {
                response.status(statusCode.BadRequest).json({ result: false });
            }
        });

        router.get("/downloads/*", (request, response) => {
            const filename = request.path.substring(request.path.lastIndexOf("/")+1);
            fs.readFile(path.join(__dirname ,"../resources/webapp/" + filename), (error, data) =>{
                if(error){
                    response.status(statusCode.NotFound).send("<h1>404 Not Found</h1>");
                }
                else{
                    response.status(statusCode.OK).set({"Content-type":this.getMime(request)}).send(data);
                }
            })
        });

        this.express.route("/news/:id")
            .delete(async (request, response) => {
                const id: number = request.params.id;
                const removeResult: boolean = await newsService.removeNewsByID(id);
                if (removeResult) {
                    response.status(statusCode.Created).json({result: true});
                } else {
                    response.status(statusCode.BadRequest).json({result: false});
                }
            });

        this.express.use("/", router);
    }

    private getMime(request): string {
        const url: string = request.url;
        const mimeType: string = mime.getType(url);
        return mimeType !== null || undefined ? mimeType : "application/octet-stream"
    }

}

export default Server;
