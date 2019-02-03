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

GLvoid Graphics::SceneGraph::Scene::initScene()
{
    std::future<void> futureMeshesInitialization =
        std::async(std::launch::async, std::bind(&Managers::MeshManager::initializeMeshes, &mMeshManager));
    std::future<void> futureShadersInitialization =
        std::async(std::launch::async, std::bind(&Managers::ShaderManager::initializeShaders, &mShaderManager));

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.7f, 0.9f, 1.0f);
    glViewport(0, 0, mSceneWidth, mSceneHeight);

    futureMeshesInitialization.wait();
    SceneGraphBuilder sceneGraphBuilder(mMeshManager);
    mRootNode = sceneGraphBuilder.build();
    futureShadersInitialization.wait();
}

GLvoid Graphics::SceneGraph::Scene::renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (mRootNode->isExistChildren())
        mRootNode->childrenForEach([](Node* child) {});

    glFinish();
    SwapBuffers(mWindowContext);
}

GLvoid Graphics::SceneGraph::Scene::updateScene()
{

}
