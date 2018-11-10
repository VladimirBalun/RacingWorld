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

package ru.servers.authorizationServer.data.dao;

import org.springframework.data.jpa.repository.JpaRepository;
import ru.servers.authorizationServer.data.entity.User;

public interface UsersRepository extends JpaRepository<User, Long> {

    User findByEmail(String email);

    boolean existsByEmailAndPassword(String email, String password);

    void deleteByEmail(String email);

}
