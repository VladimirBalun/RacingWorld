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
    LOG_PRINT(glGetString(GL_VERSION));
    LOG_PRINT(glGetString(GL_SHADING_LANGUAGE_VERSION));

    glClearColor(0.3f, 0.7f, 0.9f, 1.0f);
    glViewport(0, 0, mSceneWidth, mSceneHeight);

    //Math::setOrthoMatrix(matPerspect, -10.0f, 10.0f, -10.0f, 10.0f, 10.0f, -10.0f);
    Math::setPerspectiveMatrix(matPerspect, 45.0f, (float)mSceneWidth / (float)mSceneHeight, 0.00f, 10.0f);

    Math::setIdentityMatrix(matRot1);
    Math::setIdentityMatrix(matpos1);
    Math::setScaleMatrix(matScale1, { 2.0f, 2.0f, 2.0f });

//-------------------------------------------------------------------------
 
    prog = new Graphics::Tools::ShaderProgram("Resources\\Shaders\\BaseShader.vert", "Resources\\Shaders\\BaseShader.frag");
    prog2 = new Graphics::Tools::ShaderProgram("Resources\\Shaders\\BaseShader2.vert", "Resources\\Shaders\\BaseShader2.frag");

    obj1 = new Graphics::Tools::HardwareBuffers();
 
    mesh = new Graphics::Components::SimpleMesh();
    mesh->createCube(0.3f);
    //mesh->createTetrahedron(0.3f);

//-------------------------------------------------------------------------
  GLfloat vertices[] = {
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
    };

    GLfloat colors[] = {
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     0.0f, 1.0f, 0.0f
    };

    GLuint indices[] = {
    0, 1, 2,
    0, 2, 3
    };

    GLfloat vertices2[] = {
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    };
 //-------------------------------------------------------------------------

    GLint  position, color;
    position = mShaderMgr.getShader("prog2").getAttribLocation("position");
    color = mShaderMgr.getShader("prog2").getAttribLocation("color");

    LOG_PRINT(position);
    LOG_PRINT(color);

    obj1->bind();
    obj1->createBuffers3f(position, sizeof(vertices), vertices);
    obj1->createBuffers3f(color, sizeof(colors), colors);
    obj1->createIndexBuffer(sizeof(indices), indices);
    obj1->unbind();

    position = mShaderMgr.getShader("prog1").getAttribLocation("position");
    color = mShaderMgr.getShader("prog1").getAttribLocation("color");

    LOG_PRINT(position);
    LOG_PRINT(color);

    obj2->bind();
    obj2->createBuffers3f(position, sizeof(vertices2), vertices2);
    glVertexAttrib3f(color, 1.0f, 0.0f, 0.0f);
    obj2->unbind();

    mShaderMgr.PrintShadersList();

    //mShaderMgr.destroyProgram("prog1");
    //mShaderMgr.destroyProgram("prog2");
    //mShaderMgr.PrintShadersList();
}

GLvoid Graphics::SceneGraph::Scene::renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static float Scale = 0.0f;
    Scale += 0.001f;

    mShaderMgr.setShader("prog1");
    obj2->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    obj2->unbind();
    mShaderMgr.unsetShader();


    mShaderMgr.setShader("prog2");
    Math::setTranslationMatrix(matpos1, -3.0f, -1.0f, -9.0f);
    /*
    prog2->setUniformMatrix("gWorldPos", matpos);
    prog2->setUniformMatrix("gWorldRot", matRot);
    prog2->setUniformMatrix("gWorldScale", matScale);
    prog2->setUniformMatrix("gWorldPerspectiv", matPerspect);
    */
    Math::setRotationMatrixByX(matRot1, (Scale));
    MVP = matPerspect * matpos1 * matRot1 * matScale1;
    mShaderMgr.getShader("prog2").setUniformMatrix("gWorld", MVP);
  
    obj1->bind();
    if (obj1->isIndexBuffer())
    {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    obj1->unbind();

    mShaderMgr.unsetShader();

//----------------------------------------------
    glFinish();
    SwapBuffers(mWindowContext);
}

GLvoid Graphics::SceneGraph::Scene::updateScene()
{

}
