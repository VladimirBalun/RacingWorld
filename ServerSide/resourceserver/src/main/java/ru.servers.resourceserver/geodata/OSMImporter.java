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
import com.squareup.okhttp.OkHttpClient;
import com.squareup.okhttp.Request;
import com.squareup.okhttp.Response;
import lombok.extern.log4j.Log4j;
import ru.servers.resourceserver.network.HTTPException;
import ru.servers.resourceserver.network.HTTPStatusCode;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

@Log4j
public class OSMImporter implements GEOImporter {

    private static String serverAddress;
    private static String downloadGeoDataURL;

    public OSMImporter () throws IOException{
        try (InputStream inputStream = getClass().getResourceAsStream("/osm.properties")) {
            Properties properties = new Properties();
            properties.load(inputStream);
            serverAddress = properties.getProperty("osm.serverAddress");
            downloadGeoDataURL = properties.getProperty("osm.url.downloadGeoData ");
        } catch (IOException e) {
            throw new IOException("File with OSM server properties was not read.");
        }
    }

    /**
     * latWest - latitudeWest
     * lonSouth - longitudeSouth
     * latEast - latitudeEast
     * lonNorth - longitudeNorth
     */
    @Override
    public String importGeoData(double latWest, double lonSouth, double latEast, double lonNorth) throws HTTPException {
        try {
            OkHttpClient client = new OkHttpClient();
            Request request = new Request.Builder().url(composeURL(latWest, lonSouth, latEast, lonNorth)).build();
            Response response = client.newCall(request).execute();
            if (response.code() == HTTPStatusCode.OK) {
                return response.body().string();
            } else if (response.code() == HTTPStatusCode.BAD_REQUEST) {
                throw new HTTPException("Incorrect request to OSM server.");
            } else {
                throw new HTTPException("Inner OSM server error.");
            }
        } catch (IOException e) {
            throw new HTTPException(e.getMessage());
        }
    }

    private String composeURL(double latWest, double lonSouth, double latEast, double lonNorth) {
        return serverAddress + downloadGeoDataURL + latWest + "," + lonSouth + "," + latEast + "," + lonNorth;
    }

}
