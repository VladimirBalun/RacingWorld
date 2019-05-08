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
 * limita
 */

package ru.servers.resourceserver.geodata;

import ru.servers.resourceserver.network.HTTPException;

import java.io.IOException;

public interface GEOImporter {
    /**
     *  latWest - latitudeWest
     *  lonSouth - longitudeSouth
     *  latEast - latitudeEast
     *  lonNorth - longitudeNorth
     */
    String importGeoData(double latWest, double lonSouth, double latEast, double lonNorth) throws HTTPException, IOException;

}
