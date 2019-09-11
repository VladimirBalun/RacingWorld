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
 
#include "Scene.hpp"

#include "../Shader.hpp"


void Core::Graphics::SceneGraph::Scene::addMesh(Mesh&& mesh)
{
    m_meshes.push_back(std::move(mesh));
}

void Core::Graphics::SceneGraph::Scene::addMaterial(Material&& material)
{
    m_materials.push_back(std::move(material));
}

void Core::Graphics::SceneGraph::Scene::addShader(const std::string& shader_id, Shader&& shader)
{
    //m_shaders.insert({ shader_id, shader });
}

Core::Graphics::SceneGraph::Scene::NodeSPtr Core::Graphics::SceneGraph::Scene::getRootNode() noexcept
{
    return m_root_node;
}

void Core::Graphics::SceneGraph::Scene::setRootNode(NodeSPtr root_node) noexcept
{
    m_root_node = root_node;
}

const Core::Graphics::Shader* Core::Graphics::SceneGraph::Scene::getShaderByID(const std::string& shader_id) const noexcept
{
    const auto it = m_shaders.find(shader_id);
    if (it != end(m_shaders))
    {
        //return &it->second;
    }

    return nullptr;
}
