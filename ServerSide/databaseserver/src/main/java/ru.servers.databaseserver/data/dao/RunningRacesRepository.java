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

import ru.servers.protocol.gameserverwithdatabaseserver.entity.RunningRaces;
import java.util.List;

public interface RunningRacesRepository {

    RunningRaces findById(int id);

    boolean save(RunningRaces newRunningRaces);

    boolean updateById(int id, RunningRaces newRunningRaces);

    boolean removeById(int id);

    List<RunningRaces> getAllRacings();

}
