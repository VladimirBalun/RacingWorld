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

#include <memory>

namespace Core::Helpers::Holders 
{

    template<class T>
    struct Polymorphic
    {
        Polymorphic() noexcept = default;
        explicit Polymorphic(const Polymorphic& other) = delete;
        Polymorphic& operator = (const Polymorphic& other) = delete;

        std::shared_ptr<T> createSharedCopy() const;
        std::unique_ptr<T> createUniqueCopy() const;
    };

    template<class T>
    std::shared_ptr<T> Polymorphic<T>::createSharedCopy() const
    {
        return std::make_shared<T>(*this);
    }

    template<class T>
    std::unique_ptr<T> Polymorphic<T>::createUniqueCopy() const
    {
        return std::make_unique<T>(*this);
    }

}
