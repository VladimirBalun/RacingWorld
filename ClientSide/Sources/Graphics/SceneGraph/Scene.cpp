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

GLvoid Graphics::SceneGraph::Scene::init(GLint sceneWidth, GLint sceneHeight)
{
    std::future<void> futureMeshesInitialization =
        std::async(std::launch::async, std::bind(&Managers::MeshManager::initializeMeshes, &mMeshManager));
    std::future<void> futureShadersInitialization =
        std::async(std::launch::async, std::bind(&Managers::ShaderManager::initializeShaders, &mShaderManager));

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.7f, 0.9f, 1.0f);
    glViewport(0, 0, sceneWidth, sceneHeight);

    // TODO: need to add class for camera
    Math::setLookAt(mViewMatrix, { 0.0f, 0.0f, 3.0f }, { 0.0f, 0.0f, 2.0f }, { 0.0f, 1.0f, 0.0f });
    Math::setPerspectiveMatrix(mPerspectiveMatrix, 45.0f, (GLfloat) sceneWidth / sceneHeight, 0.1f, 100.f);
    Tools::ShaderProgram shader = mShaderManager.getShader(Managers::BASE_SHADER);
    shader.setUniformMatrix("viewMatrix", mViewMatrix);
    shader.setUniformMatrix("perspectiveMatrix", mPerspectiveMatrix);

    futureMeshesInitialization.wait();
    mRootNode = SceneGraphBuilder::build(mMeshManager, mSceneGraphAllocator);
    futureShadersInitialization.wait();
}

GLvoid Graphics::SceneGraph::Scene::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO: need to use matrix of each node
    Math::Matrix4x4f modelMatrix; 
    Math::setTranslationMatrix(modelMatrix, { 0.0f, 0.0f, 0.0f });
    Tools::ShaderProgram shader = mShaderManager.getShader(Managers::BASE_SHADER);
    shader.setUniformMatrix("modelMatrix", modelMatrix);

    if (mRootNode->isExistChildren()) 
    {
        mRootNode->childrenForEach([](Node* child)
        {
            if (child->isExistMesh())
                child->getMesh().draw();
        });
    }

    glFinish();
    SwapBuffers(mWindowContext);
}

GLvoid Graphics::SceneGraph::Scene::update()
{

}
