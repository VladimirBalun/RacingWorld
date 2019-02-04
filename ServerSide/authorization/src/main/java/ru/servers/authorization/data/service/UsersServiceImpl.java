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

package ru.servers.authorization.data.service;

import lombok.extern.log4j.Log4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DataAccessException;
import org.springframework.stereotype.Service;
import ru.servers.authorization.data.dao.UsersRepository;
import ru.servers.authorization.data.entity.User;

@Log4j
@Service
public final class UsersServiceImpl implements UsersService{

    @Autowired
    private UsersRepository usersRepository;

    @Override
    public boolean addNewUser(String email, String username, String password) {
        try {
            usersRepository.saveAndFlush(new User(email, username, password));
            log.debug("User with email: " + email + " was added.");
            return true;
        } catch (DataAccessException e) {
            log.debug("User with email: " + email + " was " +
                      "not added. Cause: " + e.getMessage());
            return false;
        }
    }

    @Override
    public boolean removeUserByEmail(String email) {
        try {
            usersRepository.deleteByEmail(email);
            log.debug("Removed user with email: " + email);
            return true;
        } catch (DataAccessException e) {
            System.out.println("User with email: " + email + " was " +
                               "not deleted. Cause: " + e.getMessage());
            return false;
        }
    }

    @Override
    public boolean changePasswordByEmail(String email, String newPassword) {
        User user = usersRepository.findByEmail(email);
        if (user != null) {
            user.setPassword(newPassword);
            usersRepository.save(user);
            log.debug("Changed password of user with email: " + email);
            return true;
        } else {
            log.debug("User with email: " + email + " not found.");
            return false;
        }
    }

    @Override
    public boolean isExistUser(String email, String password) {
        return usersRepository.existsByEmailAndPassword(email, password);
    }

    @Override
    public User getUserByEmail(String email) {
        return usersRepository.findByEmail(email);
    }

}
