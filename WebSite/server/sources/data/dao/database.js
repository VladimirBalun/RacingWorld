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

const mysql = require("mysql");
const databaseConfiguration = require("../../../resources/configuration/database");

const log4js = require("log4js");
const log = log4js.getLogger(__filename);
log.level = "debug";

const connection = mysql.createConnection({
    host : databaseConfiguration.host,
    user : databaseConfiguration.user,
    password : databaseConfiguration.password,
    database: databaseConfiguration.database
});

connection.connect((error) => {
    if (error) {
        log.fatal(`Error, connection with database was not set. Cause: ${error}`);
        process.exit(1);
    }
});

module.exports = connection;
