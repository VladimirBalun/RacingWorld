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

#include "PrecompiledHeader.hpp"
#include "Scene.hpp"

#include "Mesh.hpp"
#include "Node.hpp"
#include "../Shader.hpp"

void Core::Graphics::SceneGraph::Scene::addMesh(const std::string& shader_id, Mesh&& mesh)
{
    m_meshes.emplace(shader_id, std::move(mesh));
}

void Core::Graphics::SceneGraph::Scene::addShader(const std::string& shader_id, Shader&& shader)
{
    m_shaders.emplace(shader_id, std::move(shader));
}

void Core::Graphics::SceneGraph::Scene::setLight(Light && scene_light) noexcept
{
    m_scene_light = scene_light;
}

Core::Graphics::SceneGraph::NodeSPtr Core::Graphics::SceneGraph::Scene::getRootNode() const noexcept
{
    return m_root_node;
}

void Core::Graphics::SceneGraph::Scene::setRootNode(NodeSPtr root_node) noexcept
{
    m_root_node = root_node;
}

bool Core::Graphics::SceneGraph::Scene::isExistsMesh(const std::string & mesh_id) const noexcept
{
    const auto it = m_meshes.find(mesh_id);
    return it != end(m_meshes);
}

const Core::Graphics::SceneGraph::Light& Core::Graphics::SceneGraph::Scene::getLight() const noexcept
{
    return m_scene_light;
}

const Core::Graphics::SceneGraph::Mesh* Core::Graphics::SceneGraph::Scene::getMeshByID(const std::string& mesh_id) const noexcept
{
    const auto it = m_meshes.find(mesh_id);
    if (it != end(m_meshes))
    {
        return &it->second;
    }

    return nullptr;
}

const Core::Graphics::Shader* Core::Graphics::SceneGraph::Scene::getShaderByID(const std::string& shader_id) const noexcept
{
    const auto it = m_shaders.find(shader_id);
    if (it != end(m_shaders))
    {
        return &it->second;
    }

    return nullptr;
}

Core::Graphics::SceneGraph::Scene::~Scene()
{
    for (auto& it : m_meshes)
    {
        Mesh& mesh = it.second;
        mesh.free();
    }
}
