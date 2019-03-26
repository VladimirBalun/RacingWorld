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

const _ = require("underscore");
const connection = require("./database");

module.exports = {

    getAllNews : () =>{
        return new Promise((resolve, reject) => {
            const sql = "SELECT * FROM news";
            connection.query(sql, (err, result) => {
               if(err) {
                   reject(err);
               } else {
                   resolve(result);
               }
            });
        });
    },

    getNewsByID : (id) =>{
        return new Promise((resolve,reject) => {
            const sql = "SELECT * FROM news WHERE id = ?";
            connection.query(sql, id, (err, result) => {
                if(err) {
                    reject(err);
                } else {
                    resolve(_.first(result));
                }
            });
        });
    },

    insertNews : (data) => {
        return new Promise((resolve, reject) => {
            const sql = "INSERT INTO news SET ?";
            connection.query(sql, data, err => {
                if (err){
                    reject({"result": "false"});
                } else {
                    resolve({"result": "true"});
                }
            });

        });
    },

    removeNews : (id) => {
        return new Promise((resolve, reject) => {
            const sql = "DELETE FROM news WHERE id = ?";
            connection.query(sql, id, err =>{
                if (err){
                    reject({"result": "false"});
                } else {
                    resolve({"result": "true"});
                }
            });
        });
    }

};
