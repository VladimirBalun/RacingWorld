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

    Math::setIdentityMatrix(matRot);
    Math::setIdentityMatrix(matpos);
    Math::setTranslationMatrix(matpos, 0.9f, 0.0f, 0.0f);
    //Math::setTranslationMatrix(matpos, {0.9f, 0.0f, 0.0f});

   // Math::setOrthoMatrix(matPerspect, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
   Math::setPerspectiveMatrix(matPerspect, 45.0f, (float)mSceneWidth / (float)mSceneHeight, 0.00f, 500.0f);
  
//-------------------------------------------------------------------------
 
    prog = new Graphics::Utils::ShaderProgram("Resources\\Shaders\\BaseShader.vert", "Resources\\Shaders\\BaseShader.frag");
    prog2 = new Graphics::Utils::ShaderProgram("Resources\\Shaders\\BaseShader2.vert", "Resources\\Shaders\\BaseShader2.frag");

    obj1 = new Graphics::SceneGraph::HardwareBuffers();
 
    mesh = new Graphics::SimpleMesh::SimpleMesh();
    mesh->createCube(0.3f);
    //mesh->createTetrahedron(0.3f);

//-------------------------------------------------------------------------
  
  GLfloat vertices[] = {
     0.5f,  0.9f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.9f, 0.0f,
    -0.5f,  0.5f, 0.0f
    };

    GLfloat colors[] = {
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     0.0f, 1.0f, 0.0f
    };

    GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
    };

    GLfloat vertices2[] = {
       0.5f,  0.9f, 0.0f,
       0.5f, -0.5f, 0.0f,
      -0.5f, -0.9f, 0.0f,

    };

 //-------------------------------------------------------------------------

    GLint  position, color;
    GLuint matrix, matrixPersctiv, matrix3;

   //position = prog->getAttribLocation("position");
   //color = prog->getAttribLocation("color");

    position = prog2->getAttribLocation("position");
    color = prog2->getAttribLocation("color");

    matrix = prog2->getUniformLocation("gWorld");
    matrixPersctiv = prog2->getUniformLocation("gWorldPerspectiv");
    
    LOG_PRINT(matrixPersctiv);
    LOG_PRINT(matrix);


    prog2->setProgram();
    prog2->setUniformMatrix("gWorldPerspectiv", matPerspect);

    obj1->bind();
    obj1->createBuffers3f(position, sizeof(vertices), vertices);
    obj1->createBuffers3f(color, sizeof(colors), colors);
    // glVertexAttrib3f(color, 1.0f, 0.0f, 0.0f);
    obj1->createIndexBuffer(sizeof(indices), indices);
    obj1->unbind();

}

GLvoid Graphics::SceneGraph::Scene::renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    prog2->setProgram();

    static float Scale = 0.0f;
    Scale += 0.001f;
    //prog2->setUniform("gScale", sinf(Scale));

    Math::setTranslationMatrix(matpos, 0.0f, 0.0f, -5.0f);
    prog2->setUniformMatrix("gWorldPos", matpos);

    Math::setRotationMatrixByZ(matRot, Scale);
    prog2->setUniformMatrix("gWorldRot", matRot);

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

    prog2->unsetProgram();

   //mesh->drawMesh(Graphics::SimpleMesh::TR_SOLID);

//----------------------------------------------
    glFinish();
    SwapBuffers(mWindowContext);
}

GLvoid Graphics::SceneGraph::Scene::updateScene()
{

}
