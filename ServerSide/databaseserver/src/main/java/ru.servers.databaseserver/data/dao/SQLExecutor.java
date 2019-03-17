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

package ru.servers.databaseserver.data.dao;

import lombok.extern.log4j.Log4j;
import ru.servers.databaseserver.data.Database;

import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;

@Log4j
class SQLExecutor {

    static boolean executeSQLQuery(String sqlQuery) {
        try (Connection connection = Database.getInstance().getConnection()) {
            connection.setAutoCommit(false);
            try (Statement statement = connection.createStatement()) {
                final int updatedRows = statement.executeUpdate(sqlQuery);
                connection.commit();
                if (updatedRows == 1)
                    return true;
            } catch(SQLException e){
                connection.rollback();
                log.warn("SQL request execution error. Cause: " + e.getMessage());
            }
        } catch(SQLException e){
            log.warn("SQL request execution error. Cause: " + e.getMessage());
        }
        return false;
    }

}
