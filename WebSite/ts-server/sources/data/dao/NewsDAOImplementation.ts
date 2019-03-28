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
import NewsDAOInterface from "./NewsDAOInterface";
import MySQLConnector from "../DatabaseConnector";

const log4js = require("log4js");
const log = log4js.getLogger(__filename);
log.level = "debug";

class NewsDAO implements NewsDAOInterface {

    getAll(): News[] {
        const database = MySQLConnector.getDatabase();
        database.connect((error) => {
            // ... https://codeburst.io/node-js-mysql-and-promises-4c3be599909b
        });
        return [];
    }

    getByID(id: number): News {
        return undefined;
    }

    insert(news: News): boolean {
        return false;
    }

    remove(id: number): boolean {
        return false;
    }

}

export default NewsDAO;