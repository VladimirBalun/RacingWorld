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

#include <boost/geometry.hpp>
#include <boost/filesystem.hpp>
#include <boost/polygon/polygon.hpp>

namespace boost::geometry
{

    template<typename Type>
    using point2_t = boost::geometry::model::point<Type, 2, boost::geometry::cs::cartesian>;

    using point2i_t = point2_t<int>;
    using point2f_t = point2_t<float>;
    using point2d_dt = point2_t<double>;

    template<typename Type>
    using point3_t = boost::geometry::model::point<Type, 3, boost::geometry::cs::cartesian>;

    using point3i_t = point3_t<int>;
    using point3f_t = point3_t<float>;
    using point3d_t = point3_t<double>;

    template<typename Type>
    using box2_t = boost::geometry::model::box<point2_t<Type>>;

    using box2i_t = box2_t<int>;
    using box2f_t = box2_t<float>;
    using box2d_t = box2_t<double>;

    template<typename Type>
    using box3_t = boost::geometry::model::box<point3_t<Type>>;

    using box3i_t = box3_t<int>;
    using box3f_t = box3_t<float>;
    using box3d_t = box3_t<double>;

}

namespace bp = boost::polygon;
namespace bg = boost::geometry;
namespace bf = boost::filesystem;
