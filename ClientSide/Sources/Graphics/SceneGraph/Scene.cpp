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

 GLfloat deltaTime = 0;
 GLfloat previousTime = 0;

Graphics::SceneGraph::Scene::Scene(HDC& windowContext) noexcept :
    mWindowContext(windowContext),
    mSceneGraphAllocator(EIGHT_VIRTUAL_PAGES, sizeof(Node)),
    mSceneLight({ 1.2f, 1.0f, 2.0f }, { 0.2f, 0.2f, 0.2f }, { 0.5f, 0.5f, 0.5f }) 
{
    mShaderManager.initializeShaders();
    mMeshManager.initializeMeshes();

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.3f, 0.7f, 0.9f, 1.0f);
    glViewport(0, 0, Configuration::Window::windowWidth, Configuration::Window::windowHeight);

    SceneGraphBuilder sceneGraphBuilder(mMeshManager, mSceneGraphAllocator);
    mRootNode = sceneGraphBuilder.build();
}

GLvoid Graphics::SceneGraph::Scene::render() noexcept
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Tools::ShaderProgram& shader = mShaderManager.getShader(Managers::BASE_SHADER);
    shader.use();

    shader.setUniformVector3f("viewPosition", mSceneCamera.getPosition());
    shader.setUniformMatrix4x4f("projectionMatrix", mSceneCamera.getProjectionMatrix());
    shader.setUniformMatrix4x4f("viewMatrix", mSceneCamera.getViewMatrix());

    shader.setUniformVector3f("light.position", mSceneLight.getPosition());
    shader.setUniformVector3f("light.ambientColor", mSceneLight.getAmbientColor());
    shader.setUniformVector3f("light.diffuseColor", mSceneLight.getDiffuseColor());
    shader.setUniformVector3f("light.specularColor", mSceneLight.getSpecularColor());

    renderNode(mRootNode, shader);

    glFinish();
    SwapBuffers(mWindowContext);
}

GLvoid Graphics::SceneGraph::Scene::renderNode(Node* node, Tools::ShaderProgram& shader) noexcept
{
    if (node->isExistChildren())
    {
        node->childrenForEach([&](Node* child)
        {
            if (child->isExistMesh())
            {
                shader.setUniformMatrix4x4f("modelMatrix", child->getTransformation());
                const Components::Mesh& mesh = child->getMesh();
                if (mesh.isExistMaterial())
                {
                    const Components::Material& material = mesh.getMaterial();
                    shader.setUniformf("material.shininess", material.getShininess());
                    shader.setUniformVector3f("material.ambientColor", material.getAmbientColor());
                    shader.setUniformVector3f("material.diffuseColor", material.getDiffuseColor());
                    shader.setUniformVector3f("material.specularColor", material.getSpecularColor());
                }
                mesh.draw();
            }

            if (child->isExistChildren())
                renderNode(child, shader);
        });
    }
}

GLvoid Graphics::SceneGraph::Scene::update() noexcept
{
    GLfloat currentTime = Utils::getCurrentTimeMS();
    deltaTime = currentTime - previousTime;
    mSceneCamera.setSpeed(deltaTime);
    previousTime = currentTime;

    Input::KeyboardState& keyboard = WindowSystem::WindowEventListener::getInstance().getKeyboardState();
    if (keyboard.isPressedKeyW())
        mSceneCamera.moveForward();
    if (keyboard.isPressedKeyS())
        mSceneCamera.moveBackward();
    if (keyboard.isPressedKeyA())
        mSceneCamera.moveLeft();
    if (keyboard.isPressedKeyD())
        mSceneCamera.moveRight();

    Input::MouseState& mouse = WindowSystem::WindowEventListener::getInstance().getMouseState();
    const int xDisplacementOffset = mouse.getAndUnsetXDisplacementOffset();
    const int yDisplacementOffset = mouse.getAndUnsetYDisplacementOffset();
    if (xDisplacementOffset != 0 || yDisplacementOffset != 0)
        mSceneCamera.turn(xDisplacementOffset, yDisplacementOffset);
    const int wheelOffset = mouse.getAndUnsetWheelOffset();
    if (wheelOffset != 0) 
        mSceneCamera.scale(wheelOffset);
}
