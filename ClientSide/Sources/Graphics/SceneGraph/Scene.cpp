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

Graphics::SceneGraph::Scene::Scene(HDC& window_context) noexcept :
    m_window_context(window_context),
    m_scene_light({ 1.2f, 1.0f, 2.0f }, { 0.2f, 0.2f, 0.2f }, { 0.5f, 0.5f, 0.5f })
{
    m_shader_manager.initializeShaders();
    m_mesh_manager.initializeMeshes();

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.3f, 0.7f, 0.9f, 1.0f);
    glViewport(0, 0, Configuration::Window::window_width, Configuration::Window::window_height);

    SceneGraphBuilder sceneGraphBuilder(m_mesh_manager);
    m_root_node = sceneGraphBuilder.build();
}

GLvoid Graphics::SceneGraph::Scene::render() noexcept
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Tools::ShaderProgram& shader = m_shader_manager.getShader(Managers::BASE_SHADER);
    shader.use();

    shader.setUniformVector3f("viewPosition", m_scene_camera.getPosition());
    shader.setUniformMatrix4x4f("projectionMatrix", m_scene_camera.getProjectionMatrix());
    shader.setUniformMatrix4x4f("viewMatrix", m_scene_camera.getViewMatrix());

    shader.setUniformVector3f("light.position", m_scene_light.getPosition());
    shader.setUniformVector3f("light.ambientColor", m_scene_light.getAmbientColor());
    shader.setUniformVector3f("light.diffuseColor", m_scene_light.getDiffuseColor());
    shader.setUniformVector3f("light.specularColor", m_scene_light.getSpecularColor());

    renderNode(m_root_node, shader);

    glFinish();
    SwapBuffers(m_window_context);
}

GLvoid Graphics::SceneGraph::Scene::renderNode(std::shared_ptr<Node>& node, Tools::ShaderProgram& shader) noexcept
{
    if (node->isExistChildren())
    {
        node->childrenForEach([&](std::shared_ptr<Node>& child)
        {
            const std::optional<Components::Mesh> mesh = child->getMesh();
            if (mesh.has_value())
            {
                shader.setUniformMatrix4x4f("modelMatrix", child->getTransformation());
                const std::optional<Components::Material> material = mesh->getMaterial();
                if (material.has_value())
                {
                    shader.setUniformf("material.shininess", material->getShininess());
                    shader.setUniformVector3f("material.ambientColor", material->getAmbientColor());
                    shader.setUniformVector3f("material.diffuseColor", material->getDiffuseColor());
                    shader.setUniformVector3f("material.specularColor", material->getSpecularColor());
                }
                mesh->draw();
            }

            if (child->isExistChildren())
                renderNode(child, shader);
        });
    }
}

GLvoid Graphics::SceneGraph::Scene::update() noexcept
{
    static GLuint64 delta_time = 0;
    static GLuint64 previous_time = 0;

    const GLuint64 current_time = Utils::getCurrentTimeMS();
    delta_time = current_time - previous_time;
    m_scene_camera.setSpeed(static_cast<GLfloat>(delta_time));
    previous_time = current_time;

    const Input::KeyboardState& keyboard = WindowSystem::WindowEventListener::getInstance().getKeyboardState();
    if (keyboard.isPressedKeyW())
        m_scene_camera.moveForward();
    if (keyboard.isPressedKeyS())
        m_scene_camera.moveBackward();
    if (keyboard.isPressedKeyA())
        m_scene_camera.moveLeft();
    if (keyboard.isPressedKeyD())
        m_scene_camera.moveRight();

    Input::MouseState& mouse = WindowSystem::WindowEventListener::getInstance().getMouseState();
    const GLint x_displacement_offset = mouse.getAndUnsetXDisplacementOffset();
    const GLint y_displacement_offset = mouse.getAndUnsetYDisplacementOffset();
    if (x_displacement_offset != 0 || y_displacement_offset != 0)
        m_scene_camera.turn(x_displacement_offset, y_displacement_offset);
    const GLint wheel_offset = mouse.getAndUnsetWheelOffset();
    if (wheel_offset != 0)
        m_scene_camera.scale(wheel_offset);
}
