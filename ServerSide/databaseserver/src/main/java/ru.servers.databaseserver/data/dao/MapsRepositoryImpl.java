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
import ru.servers.protocol.gameserverwithdatabaseserver.entity.Map;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;


@Log4j
public class MapsRepositoryImpl implements  MapsRepository{

    @Override
    public boolean save(Map newMap) {
        final String sqlQuery = String.format("INSERT INTO maps (name) VALUES ('%s')", newMap.getName());
        return SQLExecutor.executeSQLQuery(sqlQuery);
    }

    @Override
    public boolean removeByName(String nameMap) {
        final String sqlQuery = String.format("DELETE FROM maps WHERE name = '%s'", nameMap);
        return SQLExecutor.executeSQLQuery(sqlQuery);
    }

    @Override
    public boolean removeById(int id) {
        final String sqlQuery = String.format("DELETE FROM maps WHERE id = %d", id);
        return SQLExecutor.executeSQLQuery(sqlQuery);
    }

    @Override
    public boolean updateNameById(int id, Map newMap) {
        final String sqlQuery = String.format("UPDATE maps SET name='%s' WHERE id = %d", newMap.getName(), id);
        return SQLExecutor.executeSQLQuery(sqlQuery);
    }

    @Override
    public Map findById(int id){
        final String sqlQuery = String.format("SELECT * FROM maps WHERE id =%d" , id);
        try (Connection connection = Database.getInstance().getConnection()) {
            connection.setAutoCommit(false);
            try (Statement statement = connection.createStatement()) {
                ResultSet resultSet = statement.executeQuery(sqlQuery);
                Map map = new Map();
                while (resultSet.next()) {
                    map.setId(resultSet.getInt("id"));
                    map.setName(resultSet.getString("name"));
                }
                connection.commit();
                return map;
            } catch (SQLException e){
                connection.rollback();
                log.warn("SQL request execution error. Cause: " + e.getMessage());
            }
        } catch (SQLException e) {
            log.warn("SQL request execution error. Cause: " + e.getMessage());
        }
        return null;
    }

}
