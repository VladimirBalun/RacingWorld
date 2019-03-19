-- MySQL dump 10.13  Distrib 8.0.15, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: racingworld
-- ------------------------------------------------------
-- Server version	8.0.15

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
 SET NAMES utf8 ;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `maps`
--

DROP TABLE IF EXISTS maps;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE maps (
  id int(11) unsigned NOT NULL AUTO_INCREMENT,
  name varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (id),
  UNIQUE KEY name_UNIQUE (name)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `news`
--

DROP TABLE IF EXISTS news;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `news` (
  id int(10) unsigned NOT NULL AUTO_INCREMENT,
  title varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  description text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  date date NOT NULL,
  PRIMARY KEY (id),
  UNIQUE KEY title_UNIQUE (title)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `playing_users`
--

DROP TABLE IF EXISTS playing_users;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE playing_users (
  id int(11) unsigned NOT NULL AUTO_INCREMENT,
  id_user int(11) unsigned NOT NULL,
  id_running_racing int(11) unsigned NOT NULL,
  PRIMARY KEY (id),
  KEY playing_users_with_running_racings_idx (id_running_racing),
  KEY playing_users_with_users_idx (id_user),
  CONSTRAINT playing_users_with_running_racings FOREIGN KEY (id_running_racing) REFERENCES running_racings (id),
  CONSTRAINT playing_users_with_users FOREIGN KEY (id_user) REFERENCES users (id) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=26 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `racings`
--

DROP TABLE IF EXISTS racings;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE racings (
  id int(11) unsigned NOT NULL AUTO_INCREMENT,
  start_time datetime NOT NULL,
  id_map int(11) unsigned NOT NULL,
  count_players int(11) NOT NULL,
  total_time datetime NOT NULL,
  PRIMARY KEY (id),
  KEY racings_with_maps_idx (id_map),
  CONSTRAINT racings_with_maps FOREIGN KEY (id_map) REFERENCES maps (id) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE=InnoDB AUTO_INCREMENT=48 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `running_racings`
--

DROP TABLE IF EXISTS running_racings;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE running_racings (
  id int(11) unsigned NOT NULL AUTO_INCREMENT,
  start_time datetime NOT NULL,
  id_map int(11) unsigned NOT NULL,
  PRIMARY KEY (id),
  KEY running_racings_with_maps_idx (id_map),
  CONSTRAINT running_racings_with_maps FOREIGN KEY (id_map) REFERENCES maps (id)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=root@localhost*/ /*!50003 TRIGGER removeRunningRacing BEFORE DELETE ON running_racings FOR EACH ROW BEGIN
    DECLARE i INT DEFAULT 0;
    SET i:= 0;
    SET @start_time:= OLD.start_time;
    SET @id_map:= OLD.id_map;
    SET @id:= OLD.id;
    SET @countPlayers:= (SELECT COUNT(id) FROM playing_users WHERE id_running_racing = @id);
    INSERT INTO racings (start_time, id_map, count_players, total_time) VALUES (@start_time, @id_map, @countPlayers, now());
    SET @id_racing:= LAST_INSERT_ID();

    WHILE i < @countPlayers DO
        INSERT INTO users_racings (id_user, id_racing) VALUES ((SELECT id_user FROM playing_users WHERE id_running_racing = @id LIMIT i,1),(@id_racing));
        SET i:= i+1;
    end while;

    DELETE FROM playing_users WHERE id_running_racing = @id;
end */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS users;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE users (
  id int(10) unsigned NOT NULL AUTO_INCREMENT,
  email varchar(254) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  password varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (id),
  UNIQUE KEY email_UNIQUE (email)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `users_racings`
--

DROP TABLE IF EXISTS users_racings;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE users_racings (
  id int(11) unsigned NOT NULL AUTO_INCREMENT,
  id_user int(11) unsigned NOT NULL,
  id_racing int(11) unsigned NOT NULL,
  PRIMARY KEY (id),
  KEY users_racings_with_users_idx (id_user),
  KEY users_racings_with_racings_idx (id_racing),
  CONSTRAINT users_racings_with_racings FOREIGN KEY (id_racing) REFERENCES racings (id) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT users_racings_with_users FOREIGN KEY (id_user) REFERENCES users (id) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=32 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-03-19 21:46:09
