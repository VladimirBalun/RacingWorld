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

type MySQLQueryResult = {id: number, title: string, description: string, date: Date};

interface NewsDAOInterface {

    getAll(): Promise<MySQLQueryResult[]>;

    getByID(id: number): Promise<MySQLQueryResult[]>;

    insert(news: News): Promise<number>;

    remove(id: number): Promise<boolean>;

}

export default NewsDAOInterface;
