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
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (Object.hasOwnProperty.call(mod, k)) result[k] = mod[k];
    result["default"] = mod;
    return result;
};
Object.defineProperty(exports, "__esModule", { value: true });
const News_1 = __importDefault(require("../entity/News"));
const NewsDAOImplementation_1 = __importDefault(require("../dao/NewsDAOImplementation"));
const _ = __importStar(require("underscore"));
const log4js = require("log4js");
const log = log4js.getLogger(__filename);
log.level = "debug";
class NewsService {
    constructor() {
        this.newsDAO = new NewsDAOImplementation_1.default();
    }
    addNews(news) {
        const resultFromQuery = this.newsDAO.insert(news);
        return resultFromQuery
            .then((result) => {
            if (result > 0) {
                log.debug(`Request insert news into db has been processed with id = ${result}`);
                return true;
            }
            return false;
        })
            .catch((error) => {
            log.warn(`Request insert news into db returned error - ${error}`);
            return false;
        });
    }
    getAllNews() {
        const resultFromQuery = this.newsDAO.getAll();
        return resultFromQuery
            .then((result) => {
            log.debug("Request getting all news has been processed");
            return _.map(result, (element) => {
                return new News_1.default(element.title, element.description, element.date);
            });
        })
            .catch((error) => {
            log.warn(`Request getting all records returned error - ${error}`);
            return [];
        });
    }
    getNewsByID(id) {
        const resultFromQuery = this.newsDAO.getByID(id);
        return resultFromQuery
            .then((result) => {
            log.debug(`Request getting news with id-${id} has been processed`);
            return _.first(_.map(result, (element) => {
                return new News_1.default(element.title, element.description, element.date);
            }));
        })
            .catch((error) => {
            log.warn(`Request getting news with id-${id} returned error - ${error}`);
            return [];
        });
    }
    removeNewsByID(id) {
        const resultFromQuery = this.newsDAO.remove(id);
        return resultFromQuery
            .then((result) => {
            log.debug(`Request remove news with id-${id} from db has been processed`);
            return result;
        })
            .catch((error) => {
            log.warn(`Request remove news from db returned error - ${error}`);
            return false;
        });
    }
}
exports.default = NewsService;
//# sourceMappingURL=NewsServiceImplementation.js.map