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
import ru.servers.protocol.gameserverwithdatabaseserver.entity.RacingUser;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

@Log4j
public class RacingUsersRepositoryImpl implements RacingUsersRepository {

    @Override
    public RacingUser findById(int id) {
        final String sqlQuery = String.format("SELECT * FROM users_racings WHERE id ='%d'" , id);
        try (Connection connection = Database.getInstance().getConnection()) {
            connection.setAutoCommit(false);
            try (Statement statement = connection.createStatement()) {
                ResultSet resultSet = statement.executeQuery(sqlQuery);
                RacingUser racingUser = new RacingUser();
                while (resultSet.next()) {
                    racingUser.setId(resultSet.getInt("id"));
                    racingUser.setRacing(new RacingRepositoryImpl().findById(resultSet.getInt("id_racing")));
                    racingUser.setUser(new UsersRepositoryImpl().findById(resultSet.getInt("id_user")));
                }
                connection.commit();
                return racingUser;
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
    public boolean save(RacingUser newRacingUser) {
        final String sqlQuery = String.format("INSERT INTO users_racings (id_user, id_racing) VALUES (%d, %d)",
                newRacingUser.getUser().getId(), newRacingUser.getRacing().getId());
        return SQLExecutorUtils.executeSQLQuery(sqlQuery);
    }

    @Override
    public boolean updateById(int id, RacingUser newRacingUser) {
        final String sqlQuery = String.format("UPDATE users_racings SET id_user = %d, id_racing =%d WHERE id = %d",
                newRacingUser.getUser().getId(), newRacingUser.getRacing().getId(), id);
        return SQLExecutorUtils.executeSQLQuery(sqlQuery);
    }

    @Override
    public boolean removeById(int id) {
        final String sqlQuery = String.format("DELETE FROM users_racings WHERE id = %d", id);
        return SQLExecutorUtils.executeSQLQuery(sqlQuery);
    }

    @Override
    public List<RacingUser> getRacingsUserByUserId(int userID) {
        final String sqlQuery = String.format("SELECT * FROM users_racings WHERE id_user ='%d'" , userID);
        try (Connection connection = Database.getInstance().getConnection()) {
            connection.setAutoCommit(false);
            try (Statement statement = connection.createStatement()) {
                List<RacingUser> racingsUser = new ArrayList<>();
                ResultSet resultSet = statement.executeQuery(sqlQuery);
                while (resultSet.next()) {
                    RacingUser racingUser = new RacingUser();
                    racingUser.setId(resultSet.getInt("id"));
                    racingUser.setUser(new UsersRepositoryImpl().findById(resultSet.getInt("id_user")));
                    racingUser.setRacing(new RacingRepositoryImpl().findById(resultSet.getInt("id_racing")));
                    racingsUser.add(racingUser);
                }
                connection.commit();
                return racingsUser;
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
