/*
 * @file WindowManager.cpp
 * @brief アプリケーションウィンドウの生成・管理を行うクラスの実装
 */

#include "Window/WindowManager.h"

namespace Remiayle::Window
{
    /*!
     * @brief コンストラクタ
     */
    WindowManager::WindowManager(const WindowManagerConfig& config)
        : m_Config(config)
        , m_HInstance(GetModuleHandle(nullptr))
        , m_HWnd(nullptr)
        , m_Width(config.width)
        , m_Height(config.height)
        , m_PosX(config.posX)
        , m_PosY(config.posY)
        , m_IsRunning(true)
        , m_IsFullScreen(config.isFullScreen)
        , m_WindowedStyle(0)
    {
    }

    /*!
     * @brief デストラクタ
     */
    WindowManager::~WindowManager()
    {
        if (m_HWnd)
        {
            DestroyWindow(m_HWnd);
            m_HWnd = nullptr;
        }
    }

    /*!
     * @brief ウィンドウ初期化
     */
    bool WindowManager::Setup()
    {
        WNDCLASSEX wc = {};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.lpfnWndProc = StaticWindowProcedure;
        wc.hInstance = m_HInstance;
        wc.lpszClassName = m_Config.title.c_str();

        if (!RegisterClassEx(&wc)) return false;

        DWORD style = WS_OVERLAPPEDWINDOW;
        if (!m_Config.resizable) style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);

        RECT rc = { 0, 0, (LONG)m_Width, (LONG)m_Height };
        AdjustWindowRect(&rc, style, FALSE);

        m_HWnd = CreateWindowEx(
            0,
            m_Config.title.c_str(),
            m_Config.title.c_str(),
            style,
            m_PosX, m_PosY,
            rc.right - rc.left,
            rc.bottom - rc.top,
            nullptr,
            nullptr,
            m_HInstance,
            this
        );

        if (!m_HWnd) return false;

        if (m_Config.isFullScreen)
        {
            SetFullScreen(true);
        }

        return true;
    }

    /*!
     * @brief ウィンドウ表示
     */
    bool WindowManager::Show()
    {
        ShowWindow(m_HWnd, SW_SHOW);
        return true;
    }

    /*!
     * @brief メッセージ処理
     */
    bool WindowManager::ProcessMessages()
    {
        MSG msg = {};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                m_IsRunning = false;
                return false;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return m_IsRunning;
    }

    /*!
     * @brief 終了処理
     */
    bool WindowManager::Cleanup()
    {
        bool success = true;

        if (m_HWnd)
        {
            if (!DestroyWindow(m_HWnd)) success = false;

            m_HWnd = nullptr;
        }

        if (!UnregisterClass(m_Config.title.c_str(), m_HInstance)) success = false;

        return success;
    }

    /*!
     * @brief フルスクリーン切替
     */
    void WindowManager::SetFullScreen(bool enable)
    {
        if (enable)
        {
            m_WindowedStyle = GetWindowLong(m_HWnd, GWL_STYLE);

            MONITORINFO mi = { sizeof(mi) };
            GetMonitorInfo(MonitorFromWindow(m_HWnd, MONITOR_DEFAULTTOPRIMARY), &mi);

            SetWindowLong(m_HWnd, GWL_STYLE, m_WindowedStyle & ~WS_OVERLAPPEDWINDOW);
            SetWindowPos(m_HWnd, HWND_TOP,
                mi.rcMonitor.left, mi.rcMonitor.top,
                mi.rcMonitor.right - mi.rcMonitor.left,
                mi.rcMonitor.bottom - mi.rcMonitor.top,
                SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        }
        else
        {
            SetWindowLong(m_HWnd, GWL_STYLE, m_WindowedStyle);
            SetWindowPos(m_HWnd, nullptr,
                m_PosX, m_PosY, m_Width, m_Height,
                SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        }

        m_IsFullScreen = enable;
    }

    /*!
     * @brief 静的ウィンドウプロシージャ
     */
    LRESULT CALLBACK WindowManager::StaticWindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
    {
        WindowManager* window = nullptr;

        if (msg == WM_NCCREATE)
        {
            CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lp);
            window = reinterpret_cast<WindowManager*>(cs->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
        }
        else
        {
            window = reinterpret_cast<WindowManager*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        }

        if (window) return window->WindowProcedure(hwnd, msg, wp, lp);

        return DefWindowProc(hwnd, msg, wp, lp);
    }

    /*!
     * @brief インスタンス用ウィンドウプロシージャ
     */
    LRESULT WindowManager::WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
    {
        switch (msg)
        {
        case WM_SIZE:
            m_Width = LOWORD(lp);
            m_Height = HIWORD(lp);
            return 0;

        case WM_MOVE:
            m_PosX = (int)(short)LOWORD(lp);
            m_PosY = (int)(short)HIWORD(lp);
            return 0;

        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(hwnd, msg, wp, lp);
    }
}
