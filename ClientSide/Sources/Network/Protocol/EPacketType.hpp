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

#pragma once

namespace Network { namespace Protocol {

    enum EPacketType
    {
        ERROR_PACKET = 0,
        LOGIN_PACKET = 1,
        LOGIN_ANSWER_PACKET = 2,
        LOGOUT_PACKET = 3,
        LOGOUT_ANSWER_PACKET = 4,
        INITIALIZE_POSITION_PACKET = 5,
        INITIALIZE_POSITION_ANSWER_PACKET = 6,
        USER_ACTION_PACKET = 7,
        WORLD_ACTION_PACKET = 8
    };

} }
