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

#include "MeshManager.hpp"

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "../Tools/ObjParser.hpp"
#include "../../Utils/Configuration.hpp"

Graphics::Managers::MeshManager& Graphics::Managers::MeshManager::getInstance() noexcept
{
    static MeshManager instance{};
    return instance;
}

GLvoid Graphics::Managers::MeshManager::initialize() noexcept
{
    struct MeshInfo
    {
        std::string name;
        std::string folder;
        std::string obj_filename;
        std::string mtl_filename;
    };

    std::vector<MeshInfo> models_info{};
    boost::property_tree::ptree xml_models_info{};
    const std::string models_config_full_name = Configuration::getResourcesPath() + Configuration::Resources::MODELS_CONFIG_FILENAME;
    boost::property_tree::read_xml(models_config_full_name, xml_models_info);
    BOOST_FOREACH(const auto& xml_model_info, xml_models_info.get_child("models"))
    {
        if (xml_model_info.first == "model")
        {
            MeshInfo mesh_info{};
            mesh_info.name = xml_model_info.second.get<std::string>("<xmlattr>.name");
            mesh_info.folder = xml_model_info.second.get<std::string>("<xmlattr>.folder", "");
            mesh_info.obj_filename = xml_model_info.second.get<std::string>("<xmlattr>.obj");
            mesh_info.mtl_filename = xml_model_info.second.get<std::string>("<xmlattr>.mtl", "");
            models_info.emplace_back(mesh_info);
        }
    }

    const std::string models_path(Configuration::getModelsPath());
    for (const auto& model : models_info)
    {
        const std::string model_full_path = (!model.folder.empty())
            ? (models_path + "/" + model.folder + "/" + model.obj_filename)
            : (models_path + "/" + model.obj_filename);

        Tools::ObjParser obj_parser{};
        Components::Mesh mesh = obj_parser.parse(model_full_path);
        m_meshes.emplace(model.name, mesh);
    }

    LOG_DEBUG("Mesh manager was initialized successfully.");
}

Graphics::Components::Mesh* Graphics::Managers::MeshManager::getMesh(const std::string& mesh_name) noexcept
{
    const auto& it = m_meshes.find(mesh_name);
    return (it != end(m_meshes)) ? (&it->second) : (nullptr);
}

GLboolean Graphics::Managers::MeshManager::isExistMesh(const std::string& mesh_name) const noexcept
{
    return m_meshes.find(mesh_name) != end(m_meshes);;
}

Graphics::Managers::MeshManager::~MeshManager()
{
    for (auto& mesh : m_meshes)
    {
        mesh.second.destroy();
    }
}
