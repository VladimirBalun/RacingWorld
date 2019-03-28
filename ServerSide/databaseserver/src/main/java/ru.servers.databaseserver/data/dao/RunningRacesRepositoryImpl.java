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
import ru.servers.protocol.gameserverwithdatabaseserver.entity.RunningRaces;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.SimpleDateFormat;
import java.util.ArrayList;

@Log4j
public class RunningRacesRepositoryImpl implements RunningRacesRepository {

    private SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    @Override
    public RunningRaces findById(int id) {
        final String sqlQuery = String.format("SELECT * FROM running_racings WHERE id ='%d'" , id);
        try (Connection connection = Database.getInstance().getConnection()) {
            connection.setAutoCommit(false);
            try (Statement statement = connection.createStatement()) {
                ResultSet resultSet = statement.executeQuery(sqlQuery);
                RunningRaces runningRaces = new RunningRaces();
                while (resultSet.next()) {
                    runningRaces.setId(resultSet.getInt("id"));
                    runningRaces.setMap(new MapsRepositoryImpl().findById(resultSet.getInt("id_map")));
                    runningRaces.setStartTime(resultSet.getTimestamp("start_time"));
                }
                connection.commit();
                return runningRaces;
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
    public boolean save(RunningRaces newRunningRaces) {
        final String sqlQuery = String.format("INSERT INTO running_racings (start_time, id_map) VALUES ('%s', %d)",
                sdf.format(newRunningRaces.getStartTime()), newRunningRaces.getMap().getId());
        return SqlExecutor.executeSQLQuery(sqlQuery);
    }

    @Override
    public boolean updateById(int id, RunningRaces newRunningRaces) {
        final String sqlQuery = String.format("UPDATE running_racings SET start_time ='%s', id_map =%d WHERE id = %d",
                sdf.format(newRunningRaces.getStartTime()), newRunningRaces.getMap().getId(), id);
        return SqlExecutor.executeSQLQuery(sqlQuery);
    }

    @Override
    public boolean removeById(int id) {
        final String sqlQuery = String.format("DELETE FROM running_racings WHERE id = %d", id);
        return SqlExecutor.executeSQLQuery(sqlQuery);
    }

    @Override
    public ArrayList<RunningRaces> getAllRacings() {
        final String sqlQuery = "SELECT * FROM running_racings";
        try (Connection connection = Database.getInstance().getConnection()) {
            connection.setAutoCommit(false);
            try (Statement statement = connection.createStatement()) {
                ArrayList<RunningRaces> runningRacesList = new ArrayList<>();
                ResultSet resultSet = statement.executeQuery(sqlQuery);
                while (resultSet.next()) {
                    RunningRaces runningRaces = new RunningRaces();
                    runningRaces.setId(resultSet.getInt("id"));
                    runningRaces.setMap(new MapsRepositoryImpl().findById(resultSet.getInt("id_map")));
                    runningRaces.setStartTime(resultSet.getTimestamp("start_time"));
                    runningRacesList.add(runningRaces);
                }
                connection.commit();
                return runningRacesList;
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
