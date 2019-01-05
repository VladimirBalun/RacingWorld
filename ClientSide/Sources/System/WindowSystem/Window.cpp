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

#include "Window.hpp"

Platforms::WindowSystem::Window::Window(HINSTANCE& instance, int cmdShow) 
    : mAppInstance(instance), mCmdShow(cmdShow), mWindowClassName("RacingWorld")
{
    memset(&mWindowEvent, 0, sizeof(mWindowEvent));
    mWindowClass.lpszClassName = mWindowClassName;
    mWindowClass.cbSize = sizeof(WNDCLASSEX);
    mWindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    mWindowClass.lpfnWndProc = &WindowEventListener::onWindowEvent;
    mWindowClass.hInstance = mAppInstance;
    mWindowClass.hIcon = NULL;
    mWindowClass.hIconSm = NULL;
    mWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    mWindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    mWindowClass.lpszMenuName = NULL;
    mWindowClass.cbClsExtra = 0;
    mWindowClass.cbWndExtra = 0;

    if (!RegisterClassEx(&mWindowClass)) 
        throw std::runtime_error("Window class was not registered.");
}

void Platforms::WindowSystem::Window::showWindow(LPCSTR windowTitle, int windowWidth, int windowHeight)
{
    mWindowHandle = CreateWindowEx(NULL, mWindowClassName, windowTitle, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, 0, windowWidth, windowHeight, NULL, NULL, mAppInstance, NULL);

    if (!mWindowHandle)
        throw std::runtime_error("Window was not created.");
 
    ShowWindow(mWindowHandle, mCmdShow);
    UpdateWindow(mWindowHandle);
    initWindowContext();

    Network::NetworkManager networkManager;
    if (!networkManager.login())
        throw std::runtime_error("Login is failure.");
    if (!networkManager.initializePosition())
        throw std::runtime_error("Initialization of position is failure.");

    Graphics::SceneGraph::Scene scene(mWindowContext, windowWidth, windowHeight);
    scene.initScene();

    // Game loop
    while (mWindowEvent.message != WM_QUIT)
    {
        if (PeekMessage(&mWindowEvent, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&mWindowEvent);
            DispatchMessage(&mWindowEvent);
        }

        scene.updateScene();
        scene.renderScene();
    }
}

void Platforms::WindowSystem::Window::initWindowContext() 
{
    PIXELFORMATDESCRIPTOR pixelFormat;
    memset(&pixelFormat, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pixelFormat.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pixelFormat.nVersion = 1;
    pixelFormat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelFormat.iPixelType = PFD_TYPE_RGBA;
    pixelFormat.cColorBits = 16;
    pixelFormat.cDepthBits = 16;

    mWindowContext = GetDC(mWindowHandle);
    const int format = ChoosePixelFormat(mWindowContext, &pixelFormat);
    if (format != 0) {
        SetPixelFormat(mWindowContext, format, &pixelFormat);
        const HGLRC glBoostrap = wglCreateContext(mWindowContext);
        wglMakeCurrent(mWindowContext, glBoostrap);

        static const int context_attributes[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 0,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };
        mOpenGLContext = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>
            (wglGetProcAddress("wglCreateContextAttribsARB"))
            (mWindowContext, NULL, context_attributes);
        wglMakeCurrent(mWindowContext, mOpenGLContext);
        wglDeleteContext(glBoostrap);
    }
}

Platforms::WindowSystem::Window::~Window()
{
    if (!mOpenGLContext)
    {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(mOpenGLContext);
        mOpenGLContext = NULL;
    }

    if (!mWindowContext)
    {
        ReleaseDC(mWindowHandle, mWindowContext);
        mWindowContext = NULL;
    }
}
