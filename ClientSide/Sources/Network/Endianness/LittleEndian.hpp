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

#include <cstdint>

namespace Network { namespace Endianness {

    template<typename Type>
    class BigEndian;

    #pragma pack(push, 1)

    template<typename Type>
    class LittleEndian
    {
    public:
        LittleEndian(Type value = Type());
        LittleEndian(const LittleEndian& another);
        LittleEndian(const BigEndian<Type>& another);
        LittleEndian& operator = (const LittleEndian& another);
        operator const Type() const;
    private:
        unsigned char bytes[sizeof(Type)];
    };

    #pragma pack(pop)

    using uint8le_t = LittleEndian<std::uint8_t>;
    using uint16le_t = LittleEndian<std::uint16_t>;
    using uint32le_t = LittleEndian<std::uint32_t>;
    using uint64le_t = LittleEndian<std::uint64_t>;

    using int8le_t = LittleEndian<std::int8_t>;
    using int16le_t = LittleEndian<std::int16_t>;
    using int32le_t = LittleEndian<std::int32_t>;
    using int64le_t = LittleEndian<std::int64_t>;

    template<typename Type>
    LittleEndian<Type>::LittleEndian(Type value)
    {
        for (std::uint8_t i = 0; i < sizeof(Type); i++)
            bytes[sizeof(Type) - 1 - i] = value >> (i << 3);
    }

    template<typename Type>
    LittleEndian<Type>::LittleEndian(const LittleEndian& another)
    {
        for (std::uint8_t i = 0; i < sizeof(Type); i++)
            bytes[i] = another.bytes[i];
    }

    template<typename Type>
    LittleEndian<Type>::LittleEndian(const BigEndian<Type>& another)
    {
        for (std::uint8_t i = 0; i < sizeof(Type); i++)
            bytes[i] = another.bytes[sizeof(Type) - 1 - i];
    }

    template<typename Type>
    LittleEndian<Type>& LittleEndian<Type>::operator = (const LittleEndian& another)
    {
        for (std::uint8_t i = 0; i < sizeof(Type); i++)
            bytes[i] = another.bytes[i];
        return *this;
    }

    template<typename Type>
    LittleEndian<Type>::operator const Type() const
    {
        Type value = Type();
        for (std::uint8_t i = 0; i < sizeof(Type); i++)
            value |= bytes[i] << (i << 3);
        return value;
    }

} }
