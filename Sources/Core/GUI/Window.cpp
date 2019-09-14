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

#define GLEW_STATIC

#include "Window.hpp"

#include <glew.h>
#include <GLFW/glfw3.h>

#include "../Helpers/Debug.hpp"
#include "../Input/InputEventHandler.hpp"

Core::GUI::Window::Window(const int width, const int height, const std::string& title) noexcept
{
    const int was_initialized = glfwInit();
    LOG_ERROR_IF(!was_initialized, "GLFW library was not initialized.");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    LOG_ERROR_IF(!m_window, "Window was not created.");
}

void Core::GUI::Window::show() noexcept
{
    initGLContext();
    initEventHandlers();

    while (!glfwWindowShouldClose(m_window))
    {
        int window_width = 0;
        int window_height = 0;
        glViewport(0, 0, window_width, window_height);
        glClearColor(0.3f, 0.7f, 0.9f, 1.0f);
        glfwGetWindowSize(m_window, &window_width, &window_height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Core::GUI::Window::initGLContext() const noexcept
{
    glfwMakeContextCurrent(m_window);
    glewExperimental = GL_TRUE;
    glfwSwapInterval(1);

    const unsigned int initialization_result = glewInit();
    LOG_ERROR_IF(initialization_result != GLEW_OK, "GLEW library was not initialized.");

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Core::GUI::Window::initEventHandlers() const noexcept
{
    glfwSetErrorCallback(Input::onInputError);
    glfwSetKeyCallback(m_window, Input::onKeyboardEvent);
    glfwSetCursorPosCallback(m_window, Input::onMouseMoveEvent);
    glfwSetMouseButtonCallback(m_window, Input::onMouseClickEvent);
}

Core::GUI::Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
