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
    LOG_PRINT( glGetString(GL_SHADING_LANGUAGE_VERSION));

    glClearColor(0.3f, 0.7f, 0.9f, 1.0f);
    glViewport(0, 0, mSceneWidth, mSceneHeight);

//-------------------------------------------------------------------------
    //Build and compile shader program
    prog = new Graphics::Utils::ShaderProgram("BaseShader.vert", "BaseShader.frag");
    mProgram = prog->getProgram();

//-------------------------------------------------------------------------
    //Creating buffers VAO and VBO
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    // создадим Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);

    // создадим Vertex Buffer Object (VBO)
    glGenBuffers(1, &VBO);

    // установим созданный VAO как текущий
    glBindVertexArray(VAO);

    // устанавливаем созданный VBO как текущий
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // заполним VBO данными треугольника
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//-----------------------------------------------------------------------------
    //Passing parameters to shader program
    GLint positionLocation;

    // получим индекс атрибута 'position' из шейдера
    positionLocation = glGetAttribLocation(mProgram, "position");
    if (positionLocation != -1)
    {
        // разрешим использование атрибута
        glEnableVertexAttribArray(positionLocation);

        // укажем параметры доступа вершинного атрибута к VBO
        glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE,
            3 * sizeof(GLfloat), (GLvoid*)0);

    }

//-----------------------------------------------------------------------------
    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

GLvoid Graphics::SceneGraph::Scene::renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Activate shader program
    glUseProgram(mProgram);  // через GL
    //prog->setProgram();   // через класс

    //Bind VAO
    glBindVertexArray(VAO);

    //Draw
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //Unbind 
    glBindVertexArray(0);
    glUseProgram(0);

    glFinish();
    SwapBuffers(mWindowContext);
}

GLvoid Graphics::SceneGraph::Scene::updateScene()
{

}
