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
#define TO_SIZE_T(__value__) static_cast<std::size_t>(__value__)
#define TO_INT(__value__) static_cast<int>(__value__)
#define TO_DOUBLE(__value__) static_cast<double>(__value__)
#define TO_FLOAT(__value__) static_cast<float>(__value__)

#define STRINGIFY_IMPL(__value__) #__value__
#define STRINGIFY(__value__) STRINGIFY_IMPL(__value__)

#define CONCATENATE_IMPL(__first__, __second__) __first__##__second__
#define CONCATENATE(__first__, __second__) CONCATENATE_IMPL(__first__, __second__)

#define TEMPLATE_CLASS_WITH_PARAMS(__class_name__, ...) \
    __class_name__<__VA_ARGS__>

#define DECL_SMART_PTRS(__class_name__) \
    using CONCATENATE(__class_name__, SPtr) = std::shared_ptr<__class_name__ >; \
    using CONCATENATE(__class_name__, UPtr) = std::unique_ptr<__class_name__ >; \
    using CONCATENATE(__class_name__, WPtr) = std::weak_ptr<__class_name__ >;

#define DECL_SMART_PTRS_BY_TYPEDEF(__source_class_name__, __dest_class_name__) \
    using CONCATENATE(__dest_class_name__, SPtr) = std::shared_ptr<__source_class_name__ >; \
    using CONCATENATE(__dest_class_name__, UPtr) = std::unique_ptr<__source_class_name__ >; \
    using CONCATENATE(__dest_class_name__, WPtr) = std::weak_ptr<__source_class_name__ >;

#define FWD_DECL_SMART_PTRS_FOR_CLASS(__class_name__) \
    class __class_name__; \
    DECL_SMART_PTRS(__class_name__)

#define FWD_DECL_SMART_PTRS_FOR_STRUCT(__struct_name__) \
    struct __struct_name__; \
    DECL_SMART_PTRS(__struct_name__)

#define FWD_DECL_SMART_PTRS_FOR_CLASS_BY_TYPEDEF(__source_class_name__, __dest_class_name__) \
    class __source_class_name__; \
    DECL_SMART_PTRS_BY_TYPEDEF(__source_class_name__, __dest_class_name__)

#define FWD_DECL_SMART_PTRS_FOR_STRUCT_BY_TYPEDEF(__source_struct_name__, __dest_struct_name__) \
    struct __source_struct_name__; \
    DECL_SMART_PTRS_BY_TYPEDEF(__source_struct_name__, __dest_struct_name__)
