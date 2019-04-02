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
import ru.servers.protocol.gameserverwithdatabaseserver.entity.PlayingUser;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

@Log4j
public class PlayingUsersRepositoryImpl implements  PlayingUsersRepository {


    @Override
    public boolean save(PlayingUser newPlayingUser) {
        final String sqlQuery = String.format("INSERT INTO playing_users (id_user, id_running_racing) VALUES (%d, %d)",
                newPlayingUser.getUser().getId(), newPlayingUser.getRunningRaces().getId());
        return SQLExecutorUtils.executeSQLQuery(sqlQuery);
    }

    @Override
    public boolean removeById(int id) {
        final String sqlQuery = String.format("DELETE FROM playing_users WHERE id = %d", id);
        return SQLExecutorUtils.executeSQLQuery(sqlQuery);
    }

    @Override
    public boolean removeUserByUserId(int id_user) {
        final String sqlQuery = String.format("DELETE FROM playing_users WHERE id_user = %d", id_user);
        return SQLExecutorUtils.executeSQLQuery(sqlQuery);
    }

    @Override
    public boolean updateById(int id, PlayingUser newPlayingUser) {
        final String sqlQuery = String.format("UPDATE playing_users SET id_user = %d, id_running_racing = %d WHERE id = %d",
                newPlayingUser.getUser().getId(), newPlayingUser.getRunningRaces().getId(), id);
        return SQLExecutorUtils.executeSQLQuery(sqlQuery);
    }

    @Override
    public PlayingUser findById(int id) {
        final String sqlQuery = String.format("SELECT * FROM playing_users WHERE id = %d" , id);
        try (Connection connection = Database.getInstance().getConnection()) {
            connection.setAutoCommit(false);
            try (Statement statement = connection.createStatement()) {
                ResultSet resultSet = statement.executeQuery(sqlQuery);
                PlayingUser playingUser = new PlayingUser();
                while (resultSet.next()) {
                    playingUser.setId(resultSet.getInt("id"));
                    playingUser.setUser(new UsersRepositoryImpl().findById(resultSet.getInt("id_user")));
                    playingUser.setRunningRaces(new RunningRacesRepositoryImpl().findById(resultSet.getInt("id_running_racing")));
                }
                connection.commit();
                return playingUser;
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
