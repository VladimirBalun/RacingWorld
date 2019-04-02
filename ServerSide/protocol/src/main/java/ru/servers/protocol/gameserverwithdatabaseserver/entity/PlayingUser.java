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

package ru.servers.protocol.gameserverwithdatabaseserver.entity;

import lombok.*;
import java.io.Serializable;

@Getter
@Setter
@ToString
@NoArgsConstructor
@EqualsAndHashCode
public class PlayingUser implements Serializable {

    private static final long serialVersionUID = -4284748608152638926L;

    private int id;
    private User user;
    private RunningRaces runningRaces;

    public PlayingUser(User user, RunningRaces runningRaces){
        this.user = user;
        this.runningRaces = runningRaces;
    }

}
