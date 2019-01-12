#include "SimpleMesh.hpp"
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

#include "SimpleMesh.hpp"

///////////////////////////////////////////////////////////////////////////
//   Cube
///////////////////////////////////////////////////////////////////////////
#define CUBE_NUM_VERT    8
#define CUBE_NUM_FACES   6
#define CUBE_NUM_TRIANGLE_ON_FACE  2
#define CUBE_ELEM_OBJ   (CUBE_NUM_FACES*CUBE_NUM_TRIANGLE_ON_FACE)

/* Vertex Coordinates */
float cube_v[CUBE_NUM_VERT * 3] =
{
    // front
    -0.5, -0.5,  -0.5,
     0.5, -0.5,  -0.5,
     0.5,  0.5,  -0.5,
    -0.5,  0.5,  -0.5,
    // back
    -0.5, -0.5, -1.5,
     0.5, -0.5, -1.5,
     0.5,  0.5, -1.5,
    -0.5,  0.5, -1.5
};

/* Vertex indices */
unsigned short cube_vi[CUBE_ELEM_OBJ*3] =
{
    0, 1, 2,  2, 3, 0,  // front
    1, 5, 6,  6, 2, 1,  // right
    7, 6, 5,  5, 4, 7,  // back
    4, 0, 3,  3, 7, 4,  // left
    4, 5, 1,  1, 0, 4,  // bottom
    3, 2, 6,  6, 7, 3   // top
};

///////////////////////////////////////////////////////////////////////////
//   Tetrahedron
///////////////////////////////////////////////////////////////////////////
#define TETRAHEDRON_NUM_VERT       4
#define TETRAHEDRON_NUM_FACES      4
#define TETRAHEDRON_ELEM_OBJ   (TETRAHEDRON_NUM_FACES*3)

/* Vertex Coordinates */
float tetrahedron_v[TETRAHEDRON_NUM_VERT * 3] =
{
                1.0f,             0.0f,             0.0f,
    -0.333333333333f,  0.942809041582f,             0.0f,
    -0.333333333333f, -0.471404520791f,  0.816496580928f,
    -0.333333333333f, -0.471404520791f, -0.816496580928f
};

/* Vertex indices */
unsigned short tetrahedron_vi[TETRAHEDRON_ELEM_OBJ] =
{
    1, 3, 2,
    0, 2, 3,
    0, 3, 1,
    0, 1, 2
};

Graphics::SimpleMesh::SimpleMesh::SimpleMesh()
{
    mesh = new Graphics::SceneGraph::HardwareBuffers();
    shader = new Graphics::Utils::ShaderProgram("Resources\\Shaders\\BaseShader.vert", "Resources\\Shaders\\BaseShader.frag");
    positionLocation = shader->getAttribLocation("position");
}

void Graphics::SimpleMesh::SimpleMesh::createCube(float size)
{
    for (float &n : cube_v)
        n *= size;

    mesh->bind();
    mesh->createBuffers3f(positionLocation, sizeof(cube_v), cube_v);
    glVertexAttrib3f(1, 1.0f, 1.0f, 1.0f);
    mesh->createIndexBuffer(sizeof(tetrahedron_vi), tetrahedron_vi);
    mesh->unbind();
}

void Graphics::SimpleMesh::SimpleMesh::createTetrahedron(float size)
{
    for (float &n : tetrahedron_v)
        n *= size;

    mesh->bind();
    mesh->createBuffers3f(positionLocation, sizeof(tetrahedron_v), tetrahedron_v);
    glVertexAttrib3f(1, 1.0f, 1.0f, 1.0f);
    mesh->createIndexBuffer(sizeof(cube_vi), cube_vi);
    mesh->unbind();
}

void Graphics::SimpleMesh::SimpleMesh::drawMesh(TypeRender tr)
{
    glPolygonMode(GL_FRONT_AND_BACK, tr);

    shader->setProgram();
    mesh->bind();
    glDrawElements(GL_TRIANGLES, CUBE_ELEM_OBJ*3, GL_UNSIGNED_SHORT, 0);
    mesh->unbind();
    shader->unsetProgram();
}

Graphics::SimpleMesh::SimpleMesh::~SimpleMesh()
{
    delete mesh;
    delete shader;
}
