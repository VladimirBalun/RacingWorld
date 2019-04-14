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

type MySQLQueryResult = {id:number, title:string, description:string, date:Date};
type MySQLQueryOkPacket = {fieldCount: number,
    affectedRows: number,
    insertId: number,
    serverStatus: number,
    warningCount: number,
    message: string,
    protocol41: boolean,
    changedRows: number,
};

class NewsDAO implements NewsDAOInterface {

    private database;

    constructor(){
        this.database = new MySQLConnector();
    }

    public getAll(): Promise<MySQLQueryResult[]> {
        const sql = "SELECT * FROM news";
        return this.database.connectionQuery(sql)
            .then((result: MySQLQueryResult[]) => {
                return result;
            })
            .catch((error: string) => {
                return [];
            });
    }

    public getByID(id: number): Promise<MySQLQueryResult[]> {
        const sql = "SELECT * FROM news WHERE id = ?";
        return this.database.connectionQuery(sql, id)
            .then((result: MySQLQueryResult[]) => {
                return result;
            })
            .catch((error: string) => {
                return [];
            });
    }

    public insert(news: News): Promise<number> {
        const sql = "INSERT INTO news SET?";
        const errorReturn = -1;
        const defaultWarningCount = 0;
        return this.database.connectionQuery(sql, news)
            .then((result: MySQLQueryOkPacket) => {
                return result.warningCount === defaultWarningCount ? result.insertId : errorReturn;
            })
            .catch((error: string) => {
                return false;
            });
    }

    public remove(id: number): Promise<boolean> {
        const sql = "DELETE FROM news WHERE id = ?";
        const defaultWarningCount = 0;
        return this.database.connectionQuery(sql, id)
            .then((result: MySQLQueryOkPacket) => {
                return result.warningCount === defaultWarningCount;
            })
            .catch((error: string) => {
                return false;
            });
    }

}

export default NewsDAO;
