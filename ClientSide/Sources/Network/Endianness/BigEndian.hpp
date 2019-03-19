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
    class LittleEndian;

    #pragma pack(push, 1)

    template<typename Type>
    class BigEndian
    {
    public:
        BigEndian(Type value = Type()) noexcept;
        BigEndian(const BigEndian& another) noexcept;
        BigEndian(const LittleEndian<Type>& another) noexcept;
        BigEndian& operator = (const BigEndian& another) noexcept;
        operator const Type() const noexcept;
    private:
        unsigned char bytes[sizeof(Type)];
    };

    #pragma pack(pop)

    using uint8be_t = BigEndian<std::uint8_t>;
    using uint16be_t = BigEndian<std::uint16_t>;
    using uint32be_t = BigEndian<std::uint32_t>;
    using uint64be_t = BigEndian<std::uint64_t>;

    using int8be_t = BigEndian<std::int8_t>;
    using int16be_t = BigEndian<std::int16_t>;
    using int32be_t = BigEndian<std::int32_t>;
    using int64be_t = BigEndian<std::int64_t>;

    template<typename Type>
    BigEndian<Type>::BigEndian(Type value) noexcept
    {
        for (std::uint8_t i = 0; i < sizeof(Type); i++)
            bytes[sizeof(Type) - 1 - i] = value >> (i << 3);
    }

    template<typename Type>
    BigEndian<Type>::BigEndian(const BigEndian& another) noexcept
    {
        for (std::uint8_t i = 0; i < sizeof(Type); i++)
            bytes[i] = another.bytes[i];
    }

    template<typename Type>
    BigEndian<Type>::BigEndian(const LittleEndian<Type>& another) noexcept
    {
        for (std::uint8_t i = 0; i < sizeof(Type); i++)
            bytes[i] = another.bytes[sizeof(Type) - 1 - i];
    }

    template<typename Type>
    BigEndian<Type>& BigEndian<Type>::operator = (const BigEndian& another) noexcept
    {
        for (std::uint8_t i = 0; i < sizeof(Type); i++)
            bytes[i] = another.bytes[i];
        return *this;
    }

    template<typename Type>
    BigEndian<Type>::operator const Type() const noexcept
    {
        Type value = Type();
        for (std::uint8_t i = 0; i < sizeof(Type); i++)
            value |= bytes[sizeof(Type) - 1 - i] << (i << 3);
        return value;
    }

} }
