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

package ru.servers.databaseserver.data;

import lombok.extern.log4j.Log4j;

import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

@Log4j
public final class Database {

    private String databaseURL;
    private String databaseUsername;
    private String databasePassword;
    private static Database instance;

    private Database() {
        try {
            Properties properties = new Properties();
            try (InputStream inputStream = Files.newInputStream(Paths.get("databaseserver/src/main/resources/database.properties"))){
                properties.load(inputStream);
            } catch (IOException e) {
                throw new IOException("file with database properties was not read.");
            }

            databaseURL = properties.getProperty("db.url");
            databaseUsername = properties.getProperty("db.username");
            databasePassword = properties.getProperty("db.password");
            Class.forName(properties.getProperty("db.driver")).getDeclaredConstructor().newInstance();
        } catch (Exception e){
            log.error("Database connection failed. Cause:" + e.getMessage());
        }
    }

    public synchronized Connection getConnection() throws SQLException {
        return DriverManager.getConnection(databaseURL, databaseUsername, databasePassword);
    }

    public synchronized static Database getInstance() {
        if (instance == null){
            instance = new Database();
        }
        return instance;
    }

}
