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
#include <string>

#define STR(__value__) std::string(__value__)
#define TO_STR(__value__) std::to_string(__value__)
#define STRINGIFY(__value__) #__value__

#define DECLARE_SMART_PTRS_FOR_CLASS(__class_name__) \
    using __class_name__##SPtr = std::shared_ptr<__class_name__>; \
    using __class_name__##UPtr = std::unique_ptr<__class_name__>; \
    using __class_name__##WPtr = std::weak_ptr<__class_name__>;

#define DECLARE_SMART_PTRS_FOR_STRUCT(__struct_name__) \
    using __struct_name__##SPtr = std::shared_ptr<__struct_name__>; \
    using __struct_name__##UPtr = std::unique_ptr<__struct_name__>; \
    using __struct_name__##WPtr = std::weak_ptr<__struct_name__>;

#define FWD_DECLARE_SMART_PTRS_FOR_CLASS(__class_name__) \
    class __class_name__; \
    DECLARE_SMART_PTRS_FOR_CLASS(__class_name__)

#define FWD_DECLARE_SMART_PTRS_FOR_STRUCT(__struct_name__) \
    struct __struct_name__; \
    DECLARE_SMART_PTRS_FOR_STRUCT(__struct_name__)
