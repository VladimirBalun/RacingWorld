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

WindowSystem::Window::Window(HINSTANCE& instance, int cmdShow)
    : mAppInstance(instance), mCmdShow(cmdShow), mIsGlobalErrorOccured(false)
{
    EventSystem::EventManager& eventManager = EventSystem::EventManager::getInstance();
    eventManager.subscribeOnGlobalError(*this);

    memset(&mWindowEvent, 0, sizeof(mWindowEvent));
    mWindowClass.lpszClassName = "RacingWorld";
    mWindowClass.cbSize = sizeof(WNDCLASSEX);
    mWindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    mWindowClass.lpfnWndProc = (WNDPROC)WindowEventListener::onWindowEvent;
    mWindowClass.hInstance = mAppInstance;
    mWindowClass.hIcon = NULL;
    mWindowClass.hIconSm = NULL;
    mWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    mWindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    mWindowClass.lpszMenuName = NULL;
    mWindowClass.cbClsExtra = 0;
    mWindowClass.cbWndExtra = 0;

    if (!RegisterClassEx(&mWindowClass)) 
        eventManager.notifyGlobalError("Window class was not registered.");
}

void WindowSystem::Window::showWindow(LPCSTR windowTitle, bool fullscreen)
{
    mWindowHandle = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, "RacingWorld", windowTitle, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS |WS_CLIPCHILDREN,
        0, 0, Configuration::Window::windowWidth, Configuration::Window::windowHeight, NULL, NULL, mAppInstance, NULL);
    if (!mWindowHandle)
    {
        EventSystem::EventManager& eventManager = EventSystem::EventManager::getInstance();
        eventManager.notifyGlobalError("Window was not created.");
    }

    initOpenGLContext();
    ShowWindow(mWindowHandle, mCmdShow);
    SetForegroundWindow(mWindowHandle);
    SetFocus(mWindowHandle);
    UpdateWindow(mWindowHandle);
 
    Network::NetworkManager networkManager;
    if (!networkManager.login())
    {
        EventSystem::EventManager& eventManager = EventSystem::EventManager::getInstance();
        eventManager.notifyGlobalError("Login on the server is failure.");
    }
    //if (!networkManager.initializePosition())
    //{
    //    EventSystem::EventManager& eventManager = EventSystem::EventManager::getInstance();
    //    eventManager.notifyGlobalError("Initialization of position on the server is failure.");
    //}

    Graphics::SceneGraph::Scene scene(mWindowContext);
    while (mWindowEvent.message != WM_QUIT)
    {
        if (PeekMessage(&mWindowEvent, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&mWindowEvent);
            DispatchMessage(&mWindowEvent);
        }

        if (!mIsGlobalErrorOccured)
        {
            scene.update();
            scene.render();
        }
        else 
        {
            static EventSystem::EventManager& manager = EventSystem::EventManager::getInstance();
            scene.writeError(manager.getGlobalErrorMessage());
        }
    }
}

void WindowSystem::Window::onEvent(const char* message) const noexcept
{
    LOG_ERROR(message);
    mIsGlobalErrorOccured = true;
}

void WindowSystem::Window::initFullScreen(DWORD windowWidth, DWORD windowHeight, DWORD windowBPP)
{
    DEVMODE dmScreenSettings;
    memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
    dmScreenSettings.dmSize = sizeof(dmScreenSettings);
    dmScreenSettings.dmPelsWidth = windowWidth;
    dmScreenSettings.dmPelsHeight = windowHeight;
    dmScreenSettings.dmBitsPerPel = windowBPP;
    dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
    if (ChangeDisplaySettings(&dmScreenSettings, 0) != DISP_CHANGE_SUCCESSFUL) 
    {
        EventSystem::EventManager& eventManager = EventSystem::EventManager::getInstance();
        eventManager.notifyGlobalError("Fullscreen mode is not supporting.");
    }
}

void WindowSystem::Window::initOpenGLContext() 
{
    PIXELFORMATDESCRIPTOR pixelFormat;
    memset(&pixelFormat, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pixelFormat.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pixelFormat.nVersion = 1;
    pixelFormat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelFormat.iPixelType = PFD_TYPE_RGBA;
    pixelFormat.cColorBits = 32;
    pixelFormat.cDepthBits = 32;
    pixelFormat.cStencilBits = 16; 
    pixelFormat.iLayerType = PFD_MAIN_PLANE;;

    mWindowContext = GetDC(mWindowHandle);
    const int format = ChoosePixelFormat(mWindowContext, &pixelFormat);
    if (format != 0) 
    {
        SetPixelFormat(mWindowContext, format, &pixelFormat);
        const HGLRC glBoostrap = wglCreateContext(mWindowContext);
        wglMakeCurrent(mWindowContext, glBoostrap);
        static const int context_attributes[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 0,
            WGL_CONTEXT_FLAGS_ARB,  WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        mOpenGLContext = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>
            (wglGetProcAddress("wglCreateContextAttribsARB"))
            (mWindowContext, NULL, context_attributes);
        wglMakeCurrent(mWindowContext, mOpenGLContext);
        wglDeleteContext(glBoostrap);
        initOpenGL();
    }
}

WindowSystem::Window::~Window()
{
    ChangeDisplaySettings(NULL, 0);
    ShowCursor(TRUE);

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
