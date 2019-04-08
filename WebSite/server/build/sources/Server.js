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
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : new P(function (resolve) { resolve(result.value); }).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (Object.hasOwnProperty.call(mod, k)) result[k] = mod[k];
    result["default"] = mod;
    return result;
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const _ = __importStar(require("underscore"));
//import * as express from "express";
const express_1 = __importDefault(require("express"));
const bodyParser = __importStar(require("body-parser"));
const mime = __importStar(require("mime"));
const log4js = __importStar(require("log4js"));
const log = log4js.getLogger(__filename);
log.level = "debug";
const News_1 = __importDefault(require("./data/entity/News"));
const NewsServiceImplementation_1 = __importDefault(require("./data/service/NewsServiceImplementation"));
class Server {
    constructor() {
        this.express = express_1.default();
        this.express.use(bodyParser.json());
        this.express.use(bodyParser.urlencoded({ extended: true }));
        this.route();
    }
    start(port) {
        this.express.listen(port, (error) => {
            if (!error) {
                log.info(`Server was started successfully. Port: ${port}`);
            }
            else {
                log.fatal(`Server was not started. Cause: ${error}`);
                process.exit();
            }
        });
    }
    route() {
        const router = express_1.default.Router();
        const newsService = new NewsServiceImplementation_1.default();
        router.get("/news", (request, response) => __awaiter(this, void 0, void 0, function* () {
            const news = yield newsService.getAllNews();
            if (!_.isEmpty(news)) {
                response.status(200).json(news);
            }
            else {
                response.status(404).json([]);
            }
        }));
        router.get("/news/:id", (request, response) => __awaiter(this, void 0, void 0, function* () {
            const id = request.params.id;
            const news = yield newsService.getNewsByID(id);
            if (!_.isEmpty(news)) {
                response.status(200).json(news);
            }
            else {
                response.status(404).json({});
            }
        }));
        router.post("/news", (request, response) => __awaiter(this, void 0, void 0, function* () {
            const title = request.body.title;
            const description = request.body.description;
            const date = request.body.date;
            const addingResult = yield newsService.addNews(new News_1.default(title, description, date));
            if (addingResult) {
                response.status(201).json({ result: true });
            }
            else {
                response.status(400).json({ result: false });
            }
        }));
        this.express.route("/news/:id")
            .delete((request, response) => __awaiter(this, void 0, void 0, function* () {
            const id = request.params.id;
            const removeResult = yield newsService.removeNewsByID(id);
            if (removeResult) {
                response.status(201).json({ result: true });
            }
            else {
                response.status(400).json({ result: false });
            }
        }));
        this.express.use("/", router);
    }
    static getMime(request) {
        const url = request.url;
        const mimeType = mime.getType(url);
        return mimeType !== null || undefined ? mimeType : "application/octet-stream";
    }
}
exports.default = Server;
//# sourceMappingURL=Server.js.map