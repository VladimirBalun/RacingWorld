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
import ru.servers.protocol.gameserverwithdatabaseserver.entity.User;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

@Log4j
public class UsersRepositoryImpl implements UsersRepository {

    @Override
    public User findByEmail(String email) {
        final String sqlQuery = String.format("SELECT * FROM users WHERE email ='%s'" , email);
        return find(sqlQuery);
    }

    @Override
    public User findById(int id){
        final String sqlQuery = String.format("SELECT * FROM users WHERE id = %d" , id);
        return find(sqlQuery);
    }

    private User find(String sqlQuery){
        try (Connection connection = Database.getInstance().getConnection()) {
            connection.setAutoCommit(false);
            try (Statement statement = connection.createStatement()) {
                ResultSet resultSet = statement.executeQuery(sqlQuery);
                User user = new User();
                while (resultSet.next()) {
                    user.setId(resultSet.getInt("id"));
                    user.setEmail(resultSet.getString("email"));
                    user.setPassword(resultSet.getString("password"));
                }
                connection.commit();
                return user;
            } catch (SQLException e){
                connection.rollback();
                log.warn("SQL request execution error. Cause: " + e.getMessage());
            }
        } catch (SQLException e) {
            log.warn("SQL request execution error. Cause: " + e.getMessage());
        }
        return null;
    }


    @Override
    public boolean save(User newUser) {
        final String sqlQuery = String.format("INSERT INTO users (email, password) VALUES ('%s', '%s')", newUser.getEmail(), newUser.getPassword());
        return SQLExecutorUtils.executeSQLQuery(sqlQuery);
    }

    @Override
    public boolean removeByEmail(String email) {
        final String sqlQuery = String.format("DELETE FROM users WHERE email = '%s'", email);
        return SQLExecutorUtils.executeSQLQuery(sqlQuery);
    }

    @Override
    public boolean updateByEmail(String email, User newUser) {
        final String sqlQuery = String.format("UPDATE users SET email='%s', password='%s' WHERE email='%s'", newUser.getEmail(), newUser.getPassword(), email);
        return SQLExecutorUtils.executeSQLQuery(sqlQuery);
    }

}
