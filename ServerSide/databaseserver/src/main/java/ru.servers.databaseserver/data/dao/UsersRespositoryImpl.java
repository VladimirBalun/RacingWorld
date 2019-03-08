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
import ru.servers.databaseserver.data.entity.User;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

@Log4j
public class UsersRespositoryImpl implements UsersRepository {

    @Override
    public User findByEmail(String email) {
        // если пользователь не найден нужно возвращать либо nullлибо бросать исключение а в сервисе обрабатывать
        User user = new User();
        String sqlCommand = String.format("SELECT * FROM users WHERE email ='%s'" , email);
        try (Connection connection = Database.getInstance().getConnection()) {
            try {
                connection.setAutoCommit(false);
                Statement statement = connection.createStatement();
                ResultSet resultSet = statement.executeQuery(sqlCommand);
                while (resultSet.next()){
                    user.setId(resultSet.getInt(1));
                    user.setEmail(resultSet.getString(2));
                    user.setPassword(resultSet.getString(3));
                }
                if (user.getEmail() == null)
                    return null;
                connection.commit();
                statement.close();
            } catch (SQLException e){
                connection.rollback();
                log.error("Error while sending SQL query. Cause: " + e.getMessage());
            }
        } catch (Exception e) {
            log.error("Connection failed. Cause: " + e.getMessage());
        }
        return user;
    }

    @Override
    public boolean save(User newUser) {
        String userEmail = newUser.getEmail();
        String userPassword = newUser.getPassword();
        String sqlCommand = String.format("INSERT INTO users (email, password) VALUES ('%s', '%s')", userEmail, userPassword);
        try (Connection connection = Database.getInstance().getConnection()){
            try {
                connection.setAutoCommit(false);
                Statement statement = connection.createStatement();
                int rows = statement.executeUpdate(sqlCommand);
                connection.commit();
                statement.close();
                if (rows ==1)
                    return true;
            } catch (SQLException e){
                connection.rollback();
                log.error("Error while sending SQL query. Cause: " + e.getMessage());
            }
        } catch (Exception e){
            log.error("Connection failed. Cause: " + e.getMessage());
        }
        return false;
    }

    @Override
    public boolean removeByEmail(String email) {
        String sqlCommand = String.format("DELETE FROM users WHERE email = '%s'", email);
        try(Connection connection=Database.getInstance().getConnection()){
            try{
                connection.setAutoCommit(false);
                Statement statement = connection.createStatement();
                int rows = statement.executeUpdate(sqlCommand);
                connection.commit();
                statement.close();
                if (rows == 1)
                    return true;
            }catch(SQLException e){
                connection.rollback();
                log.error("Error while sending SQL query. Cause: " + e.getMessage());
            }
        }catch(Exception e){
            log.error("Connection failed. Cause: "+e.getMessage());
        }
        return false;
    }

    @Override
    public boolean updateByEmail(String email, User newUser) {
        String userEmail = newUser.getEmail();
        String userPassword = newUser.getPassword();
        String sqlCommand = String.format("UPDATE users SET email='%s', password='%s' WHERE email='%s'", userEmail, userPassword, email);
        try(Connection connection=Database.getInstance().getConnection()){
            try{
                connection.setAutoCommit(false);
                Statement statement = connection.createStatement();
                int rows = statement.executeUpdate(sqlCommand);
                connection.commit();
                statement.close();
                if (rows == 1)
                    return true;
            }catch(SQLException e){
                connection.rollback();
                log.error("Error while sending SQL query. Cause: " + e.getMessage());
            }
        }catch(Exception e){
            log.error("Connection failed. Cause: "+e.getMessage());
        }
        return false;
    }

}
