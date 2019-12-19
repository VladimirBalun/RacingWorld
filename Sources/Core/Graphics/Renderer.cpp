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
#include "Renderer.hpp"

#include "Shader.hpp"
#include "SceneGraph/Node.hpp"
#include "SceneGraph/Scene.hpp"
#include "SceneGraph/Light.hpp"
#include "Input/MouseState.hpp"
#include "Input/KeyboardState.hpp"

void Core::Graphics::Renderer::draw(const SceneGraph::Scene& scene, const std::string& shader_id)
{
    m_frame_calculator.onChangingFrame();

    m_basic_shader = scene.getShaderByID(shader_id);
    m_basic_shader->use();

    m_basic_shader->setUniformMatrix4x4f("vs_un_view", m_camera.getViewMatrix());
    m_basic_shader->setUniformMatrix4x4f("vs_un_projection", m_camera.getProjectionMatrix());

    const SceneGraph::Light& light = scene.getLight();
    m_basic_shader->setUniformVector3f("fs_un_light_color", light.getAmbientColor());

    updateCamera();
    drawNode(scene.getRootNode());
}

void Core::Graphics::Renderer::drawNode(SceneGraph::NodeSPtr node)
{
    if (node->isExistChildren())
    {
        for (auto it = node->childrenBegin(); it != node->childrenEnd(); ++it)
        {
            SceneGraph::NodeSPtr child_node = *it;
            drawNode(child_node);
        }
    }

    const glm::mat4x4& transformation = node->getTransformation();
    m_basic_shader->setUniformMatrix4x4f("vs_un_model", transformation);
    m_basic_shader->setUniformi("fs_un_texture", 0);
    if (const SceneGraph::Mesh* mesh = node->getMesh())
    {
        mesh->draw();
    }
}

void Core::Graphics::Renderer::updateCamera() noexcept
{
    m_camera.setSpeed(m_frame_calculator.getDeltaTime());

    const Input::KeyboardState& keyboard_state = g_keyboard_state.getInstance();
    if (keyboard_state.isPressedKeyW())
    {
        m_camera.moveForward();
    }
    if (keyboard_state.isPressedKeyS())
    {
        m_camera.moveBackward();
    }
    if (keyboard_state.isPressedKeyA())
    {
        m_camera.moveLeft();
    }
    if (keyboard_state.isPressedKeyD())
    {
        m_camera.moveRight();
    }

    Input::MouseState& mouse = g_mouse_state.getInstance();
    const int xDisplacementOffset = mouse.getAndUnsetXDisplacementOffset();
    const int yDisplacementOffset = mouse.getAndUnsetYDisplacementOffset();
    if (xDisplacementOffset != 0 || yDisplacementOffset != 0)
    {
        m_camera.turn(xDisplacementOffset, yDisplacementOffset);
    }
}
