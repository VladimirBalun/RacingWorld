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
const mysql = __importStar(require("mysql"));
const database_json_1 = __importDefault(require("../../resources/configuration/database.json"));
class MySQLConnector {
    static getDatabase() {
        return mysql.createConnection({
            host: database_json_1.default.host,
            user: database_json_1.default.user,
            password: database_json_1.default.password,
            database: database_json_1.default.database
        });
    }
    connectionQuery(sql, args) {
        const connection = MySQLConnector.getDatabase();
        return new Promise((resolve, reject) => {
            connection.query(sql, args, (error, result) => {
                connection.end();
                if (error) {
                    reject(error);
                }
                resolve(result);
            });
        });
    }
}
exports.default = MySQLConnector;
//# sourceMappingURL=DatabaseConnector.js.map