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
Object.defineProperty(exports, "__esModule", { value: true });
const DatabaseConnector_1 = __importDefault(require("../DatabaseConnector"));
class NewsDAO {
    constructor() {
        this.database = new DatabaseConnector_1.default();
    }
    getAll() {
        const sql = "SELECT * FROM news";
        return this.database.connectionQuery(sql)
            .then((result) => {
            return result;
        })
            .catch((error) => {
            return [];
        });
    }
    getByID(id) {
        const sql = "SELECT * FROM news WHERE id = ?";
        return this.database.connectionQuery(sql, id)
            .then((result) => {
            return result;
        })
            .catch((error) => {
            return [];
        });
    }
    insert(news) {
        const sql = "INSERT INTO news SET?";
        return this.database.connectionQuery(sql, news)
            .then((result) => {
            return result.warningCount === 0 ? result.insertId : -1;
        })
            .catch((error) => {
            return false;
        });
    }
    remove(id) {
        const sql = "DELETE FROM news WHERE id = ?";
        return this.database.connectionQuery(sql, id)
            .then((result) => {
            return result.warningCount === 0;
        })
            .catch((error) => {
            return false;
        });
    }
}
exports.default = NewsDAO;
//# sourceMappingURL=NewsDAOImplementation.js.map