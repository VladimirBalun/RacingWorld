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
import ru.servers.protocol.gameserverwithdatabaseserver.entity.Racing;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.SimpleDateFormat;
import java.util.ArrayList;

@Log4j
public class RacingRepositoryImpl implements RacingRepository {

    private SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    @Override
    public Racing findById(int id) {
        final String sqlQuery = String.format("SELECT * FROM racings WHERE id ='%d'" , id);
        try (Connection connection = Database.getInstance().getConnection()) {
            connection.setAutoCommit(false);
            try (Statement statement = connection.createStatement()) {
                ResultSet resultSet = statement.executeQuery(sqlQuery);
                Racing racing = new Racing();
                while (resultSet.next()) {
                    racing.setId(resultSet.getInt("id"));
                    racing.setStartTime(resultSet.getTimestamp("start_time"));
                    racing.setMap(new MapsRepositoryImpl().findById(resultSet.getInt("id_map")));
                    racing.setCountPlayers(resultSet.getInt("count_players"));
                    racing.setTotalTime(resultSet.getTimestamp("total_time"));
                }
                connection.commit();
                return racing;
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
    public boolean save(Racing newRacing) {
        final String sqlQuery = String.format("INSERT INTO racings (start_time, id_map, count_players, total_time) VALUES ('%s', %d, %d, '%s')",
                sdf.format(newRacing.getStartTime()), newRacing.getMap().getId(), newRacing.getCountPlayers(), sdf.format(newRacing.getTotalTime()));
        return SqlExecutor.executeSQLQuery(sqlQuery);

    }

    @Override
    public boolean removeById(int id) {
        final String sqlQuery = String.format("DELETE FROM racings WHERE id = %d", id);
        return SqlExecutor.executeSQLQuery(sqlQuery);
    }

    @Override
    public boolean updateById(int id, Racing newRacing) {
        final String sqlQuery = String.format("UPDATE racings SET start_time ='%s', id_map =%d, count_players = %d, total_time = '%s' WHERE id = %d",
                sdf.format(newRacing.getStartTime()), newRacing.getMap().getId(), newRacing.getCountPlayers(), sdf.format(newRacing.getTotalTime()), id);
        return SqlExecutor.executeSQLQuery(sqlQuery);
    }

    @Override
    public ArrayList<Racing> getAllRacings() {
        final String sqlQuery = "SELECT * FROM racings";
        try (Connection connection = Database.getInstance().getConnection()) {
            connection.setAutoCommit(false);
            try (Statement statement = connection.createStatement()) {
                ArrayList<Racing> racingList = new ArrayList<>();
                ResultSet resultSet = statement.executeQuery(sqlQuery);
                while (resultSet.next()) {
                    Racing racing = new Racing();
                    racing.setId(resultSet.getInt("id"));
                    racing.setMap(new MapsRepositoryImpl().findById(resultSet.getInt("id_map")));
                    racing.setCountPlayers(resultSet.getInt("count_players"));
                    racing.setStartTime(resultSet.getTimestamp("start_time"));
                    racing.setTotalTime(resultSet.getTimestamp("total_time"));
                    racingList.add(racing);
                }
                connection.commit();
                return racingList;
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
