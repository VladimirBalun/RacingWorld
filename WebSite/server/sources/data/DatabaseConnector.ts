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

import * as mysql from "mysql"
import databaseConf from "../../resources/configuration/database.json";

class MySQLConnector {

    public static getDatabase() {
        return mysql.createConnection({
            host : databaseConf.host,
            user : databaseConf.user,
            password : databaseConf.password,
            database: databaseConf.database
        });
    }

    public connectionQuery(sql:string, args?:any): Promise<{}> {
        const connection = MySQLConnector.getDatabase();
        return new Promise((resolve, reject) => {
            connection.query(sql, args,(error: string, result: any)=> {
                connection.end();
                if(error){reject(error);}
                resolve(result);
            });
        });
    }
}

export default MySQLConnector;
