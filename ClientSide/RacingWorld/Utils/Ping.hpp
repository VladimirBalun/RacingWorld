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

#include <mutex>
#include <chrono>
#include <cstdint>

// Thread-safe Singleton
class Ping 
{
    Ping() = default;
    ~Ping() = default;
    Ping(const Ping& other) = delete;
    Ping& operator = (const Ping& other) = delete;
public:
    static Ping& getInstance() noexcept;
    void onSend(std::chrono::time_point<std::chrono::system_clock>&& time) noexcept;
    void onReceive(std::chrono::time_point<std::chrono::system_clock>&& time) noexcept;
    std::uint16_t getPing() const noexcept;
private:
    std::uint16_t _ping;
    std::mutex _mutexOnEvent;
    std::chrono::time_point<std::chrono::system_clock> _lastSendTime;
    std::chrono::time_point<std::chrono::system_clock> _lastReceiveTime;
};

inline Ping& Ping::getInstance() noexcept
{
    static Ping instance;
    return instance;
}

inline void Ping::onSend(std::chrono::time_point<std::chrono::system_clock>&& time) noexcept
{
    std::unique_lock<std::mutex> lock(_mutexOnEvent);
    _lastSendTime = time;
    _ping = std::chrono::duration_cast<std::chrono::milliseconds>(_lastReceiveTime - _lastReceiveTime).count();
}

inline void Ping::onReceive(std::chrono::time_point<std::chrono::system_clock>&& time) noexcept
{
    std::unique_lock<std::mutex> lock(_mutexOnEvent);
    _lastReceiveTime = time;
    _ping = std::chrono::duration_cast<std::chrono::milliseconds>(_lastReceiveTime - _lastReceiveTime).count();
}

inline std::uint16_t Ping::getPing() const noexcept 
{
    return _ping;
}
