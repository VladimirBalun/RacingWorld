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

import News from "../entity/News";
import NewsDAO from "../dao/NewsDAOImplementation";
import NewsServiceInterface from "./NewsServiceInterface";
import * as _ from "underscore";
import * as log4js from "log4js";

const log = log4js.getLogger(__filename);
log.level = "debug";

type Result = {id: number, title: string, description: string, date: Date};

class NewsService implements NewsServiceInterface {

    private newsDAO: NewsDAO = new NewsDAO();

    public addNews(news: News): Promise<boolean> {
        const errorID = 0;
        const resultFromQuery: Promise<number> = this.newsDAO.insert(news);
        return resultFromQuery
            .then((result: number) => {
                if (result > errorID) {
                    log.debug(`Request insert news into db has been processed with id = ${result}`);
                    return true;
                }
                return false;
            })
            .catch((error: string) => {
                log.warn(`Request insert news into db returned error - ${error}`);
                return false;
            });
    }

    public getAllNews(): Promise<News[]> {
        const resultFromQuery: Promise<Result[]> = this.newsDAO.getAll();
        return resultFromQuery
            .then((result: Result[]) => {
                log.debug("Request getting all news has been processed");
                return _.map(result,(element: Result) => {
                    return new News(element.title, element.description, element.date);
                });
            })
            .catch((error: string) => {
                log.warn(`Request getting all records returned error - ${error}`);
                return [];
            });
    }

    public getNewsByID(id: number): Promise<News | Array<string>> {
        const resultFromQuery: Promise<Result[]> = this.newsDAO.getByID(id);
        return resultFromQuery
            .then((result: Result[]) => {
                log.debug(`Request getting news with id-${id} has been processed`);
                return _.first(_.map(result,(element: Result) => {
                    return new News(element.title,element.description,element.date);
                }));
            })
            .catch((error: string) => {
                log.warn(`Request getting news with id-${id} returned error - ${error}`);
                return [];
            });
    }

    public removeNewsByID(id: number): Promise<boolean> {
        const resultFromQuery: Promise<boolean> = this.newsDAO.remove(id);
        return resultFromQuery
            .then((result: boolean) => {
                log.debug(`Request remove news with id-${id} from db has been processed`);
                return result;
            })
            .catch((error: string) => {
                log.warn(`Request remove news from db returned error - ${error}`);
                return false;
            });
    }
    
}

export default NewsService;
