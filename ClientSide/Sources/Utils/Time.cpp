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

#include "Time.hpp"

float Utils::getCurrentTimeMS()
{
    static FILETIME filetime;
    GetSystemTimeAsFileTime(&filetime);
    DWORD nowWindows = filetime.dwLowDateTime + (filetime.dwHighDateTime << 32ULL);
    DWORD nowUnix = nowWindows - 116444736000000000ULL;
    return static_cast<float>(nowUnix / 10000ULL);
}
