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

#define COUNT_COLOR_BITS   32
#define COUNT_DEPTH_BITS   32
#define COUNT_STENCIL_BITS 16

WindowSystem::Window::Window(HINSTANCE& instance, int cmd_show) noexcept
    : m_app_instance(instance), m_cmd_show(cmd_show)
{
    EventSystem::EventManager& event_manager = EventSystem::EventManager::getInstance();
    event_manager.subscribeOnGlobalError(*this);

    memset(&m_window_event, 0, sizeof(m_window_event));
    m_window_class.lpszClassName = "RacingWorld";
    m_window_class.cbSize = sizeof(WNDCLASSEX);
    m_window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    m_window_class.lpfnWndProc = (WNDPROC)WindowEventListener::onWindowEvent;
    m_window_class.hInstance = m_app_instance;
    m_window_class.hIcon = NULL;
    m_window_class.hIconSm = NULL;
    m_window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    m_window_class.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    m_window_class.lpszMenuName = NULL;
    m_window_class.cbClsExtra = 0;
    m_window_class.cbWndExtra = 0;

    if (!RegisterClassEx(&m_window_class))
        event_manager.notifyGlobalError("Window class was not registered.");
}

void WindowSystem::Window::showWindow(LPCSTR window_title, bool full_screen) noexcept
{
    m_window_handle = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, "RacingWorld", window_title, WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE | WS_CLIPSIBLINGS |WS_CLIPCHILDREN,
        0, 0, Configuration::Window::window_width, Configuration::Window::window_height, NULL, NULL, m_app_instance, NULL);
    if (!m_window_handle)
    {
        EventSystem::EventManager& eventManager = EventSystem::EventManager::getInstance();
        eventManager.notifyGlobalError("Window was not created.");
    }

    initOpenGLContext();
    ShowWindow(m_window_handle, m_cmd_show);
    SetForegroundWindow(m_window_handle);
    SetFocus(m_window_handle);
    UpdateWindow(m_window_handle);

    Graphics::SceneGraph::Scene scene(m_window_context);
    while (m_window_event.message != WM_QUIT)
    {
        if (PeekMessage(&m_window_event, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&m_window_event);
            DispatchMessage(&m_window_event);
        }

        scene.update();
        scene.render();
    }
}

void WindowSystem::Window::onEvent(const char* message) const noexcept
{
    LOG_ERROR(message);
    MessageBox(m_window_handle, message, "Global error", MB_OK | MB_ICONERROR);
    exit(EXIT_FAILURE);
}

void WindowSystem::Window::initFullScreen(DWORD window_width, DWORD window_height, DWORD window_bpp) noexcept
{
    DEVMODE dm_screen_settings;
    memset(&dm_screen_settings, 0, sizeof(dm_screen_settings));
    dm_screen_settings.dmSize = sizeof(dm_screen_settings);
    dm_screen_settings.dmPelsWidth = window_width;
    dm_screen_settings.dmPelsHeight = window_height;
    dm_screen_settings.dmBitsPerPel = window_bpp;
    dm_screen_settings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
    if (ChangeDisplaySettings(&dm_screen_settings, 0) != DISP_CHANGE_SUCCESSFUL)
    {
        EventSystem::EventManager& eventManager = EventSystem::EventManager::getInstance();
        eventManager.notifyGlobalError("Fullscreen mode is not supporting.");
    }
}

void WindowSystem::Window::initOpenGLContext() noexcept
{
    PIXELFORMATDESCRIPTOR pixel_format;
    memset(&pixel_format, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pixel_format.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pixel_format.nVersion = 1;
    pixel_format.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixel_format.iPixelType = PFD_TYPE_RGBA;
    pixel_format.cColorBits = COUNT_COLOR_BITS;
    pixel_format.cDepthBits = COUNT_DEPTH_BITS;
    pixel_format.cStencilBits = COUNT_STENCIL_BITS;
    pixel_format.iLayerType = PFD_MAIN_PLANE;;

    m_window_context = GetDC(m_window_handle);
    const int format = ChoosePixelFormat(m_window_context, &pixel_format);
    if (format != 0) 
    {
        SetPixelFormat(m_window_context, format, &pixel_format);
        const HGLRC glBoostrap = wglCreateContext(m_window_context);
        wglMakeCurrent(m_window_context, glBoostrap);
        static const int context_attributes[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 0,
            WGL_CONTEXT_FLAGS_ARB,  WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        m_opengl_context = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>
            (wglGetProcAddress("wglCreateContextAttribsARB"))
            (m_window_context, NULL, context_attributes);
        wglMakeCurrent(m_window_context, m_opengl_context);
        wglDeleteContext(glBoostrap);
        initOpenGL();
    }
}

WindowSystem::Window::~Window()
{
    ChangeDisplaySettings(NULL, 0);
    ShowCursor(TRUE);

    if (!m_opengl_context)
    {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(m_opengl_context);
        m_opengl_context = NULL;
    }

    if (!m_window_context)
    {
        ReleaseDC(m_window_handle, m_window_context);
        m_window_context = NULL;
    }
}
