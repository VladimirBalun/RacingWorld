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

const news = require("./data/service/news-service");

module.exports.route = (server) => {

    server.get("/news", async (request, response) => response.status(200).json(await news.getAllNews()));
    server.get("/news/:id", async (request, response) => response.status(200).json(await news.getNewsByID(request.params.id)));
    server.post("/news", async (request, response) => response.status(200).json(await news.insertNews(request.body)));
    server.delete("/news/:id", async (request, response) => response.status(200).json(await news.removeNews(request.params.id)));

};