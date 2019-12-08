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

#include <deque>
#include <boost/geometry.hpp>

#include "Details.hpp"

namespace Core::GUI::Interface
{

    class Widget
    {
        virtual void layout();
    private:
        std::deque<std::shared_ptr<Widget>> m_children;
        EStyle m_style = EStyle::NONE;
        ELayoutType m_layout_type = ELayoutType::NONE;
        EPositionType m_position_type = EPositionType::CENTER;
        boost::geometry::model::point<int, 2, boost::geometry::cs::cartesian> m_position;
        boost::geometry::model::box<boost::geometry::model::point<int, 2, boost::geometry::cs::cartesian>> m_margins;
        boost::geometry::model::box<boost::geometry::model::point<int, 2, boost::geometry::cs::cartesian>> m_paddings;
    };

}
