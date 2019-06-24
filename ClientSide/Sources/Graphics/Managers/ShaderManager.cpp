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

#include "ShaderManager.hpp"

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "../../Utils/Debug.hpp"
#include "../../Utils/Configuration.hpp"

Graphics::Managers::ShaderManager& Graphics::Managers::ShaderManager::getInstance() noexcept
{
    static ShaderManager instance{};
    return instance;
}

GLvoid Graphics::Managers::ShaderManager::initialize() noexcept
{
    struct ShaderInfo
    {
        std::string name;
        std::string vs_filename;
        std::string fs_filename;
    };

    std::vector<ShaderInfo> shaders_info{};
    boost::property_tree::ptree xml_shaders_info{};
    const std::string shaders_config_full_name = Configuration::getResourcesPath() + Configuration::Resources::SHADERS_CONFIG_FILENAME;
    boost::property_tree::read_xml(shaders_config_full_name, xml_shaders_info);
    BOOST_FOREACH(const auto& xml_shader_info, xml_shaders_info.get_child("shaders"))
    {
        if (xml_shader_info.first == "shader")
        {
            ShaderInfo shader_info{};
            shader_info.name = xml_shader_info.second.get<std::string>("<xmlattr>.name");
            shader_info.vs_filename = xml_shader_info.second.get<std::string>("<xmlattr>.vert");
            shader_info.fs_filename = xml_shader_info.second.get<std::string>("<xmlattr>.frag");
            shaders_info.emplace_back(shader_info);
        }
    }

    const std::string shaders_path(Configuration::getShadersPath());
    for (const auto& shader_info : shaders_info)
    {
        const std::string vs_full_path = shaders_path + shader_info.vs_filename;
        const std::string fs_full_path = shaders_path + shader_info.fs_filename;
        const Tools::ShaderProgram shader_program(vs_full_path, fs_full_path);
        m_shader_programs.emplace(shader_info.name, shader_program);
    }

    LOG_DEBUG("Shader manager was initialized successfully.");
}

GLboolean Graphics::Managers::ShaderManager::isExistShader(const std::string& shader_name) const noexcept
{
    return m_shader_programs.find(shader_name) != end(m_shader_programs);
}

Graphics::Tools::ShaderProgram* Graphics::Managers::ShaderManager::getShader(const std::string& shader_name) noexcept
{
    const auto& it = m_shader_programs.find(shader_name);
    return (it != end(m_shader_programs)) ? (&it->second) : (nullptr);
}

Graphics::Managers::ShaderManager::~ShaderManager()
{
    for (auto& shader : m_shader_programs)
    {
        shader.second.destroy();
    }
}
