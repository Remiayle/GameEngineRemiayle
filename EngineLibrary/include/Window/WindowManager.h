/*!
 * @file WindowManager.h
 * @brief アプリケーションウィンドウの生成・管理を行うクラスの宣言
 */

#pragma once
#include <Windows.h>
#include <string>

namespace Remiayle::Window
{
    /*!
     * @struct WindowManagerConfig
     * @brief ウィンドウ生成時の初期設定を保持する構造体
     *
     * タイトル、サイズ、フルスクリーン設定などを指定します。
     * 将来的な拡張を見据えて位置指定やリサイズ可否も含みます。
     */
    struct WindowManagerConfig
    {
        std::wstring title = L"EmptyProject";   /**< ウィンドウタイトル */
        bool isFullScreen = false;              /**< フルスクリーンで開始するか */
        UINT width = 1280;                      /**< 初期幅 */
        UINT height = 720;                      /**< 初期高さ */
        int posX = CW_USEDEFAULT;               /**< 初期X位置 */
        int posY = CW_USEDEFAULT;               /**< 初期Y位置 */
        bool resizable = true;                  /**< リサイズ可能か */
    };

    /*!
     * @class WindowManager
     * @brief アプリケーションウィンドウの生成・管理を行うクラス
     *
     * Win32 API を用いてウィンドウを生成し、メッセージ処理、サイズ変更、
     * フルスクリーン切替などの管理を行います。
     * DirectX などのレンダリングシステムに HWND やサイズ情報を提供します。
     */
    class WindowManager
    {
    public:
        /*!
         * @brief コンストラクタ
         * @param config 初期設定
         */
        WindowManager(const WindowManagerConfig& config);

        /*!
         * @brief デストラクタ
         */
        ~WindowManager();

        /*!
         * @brief ウィンドウの初期化
         * @return true : 成功 false : 失敗
         */
        bool Setup();

        /*!
         * @brief ウィンドウの表示
         * @return true : 成功 false : 失敗
         */
        bool Show();

        /*!
         * @brief メッセージ処理を行い、アプリ継続可否を返す
         * @return true : 継続 false : 終了
         */
        bool ProcessMessages();

        /*!
         * @brief フルスクリーン切替
         * @param enable true でフルスクリーン化
         */
        void SetFullScreen(bool enable);

        /*!
         * @brief ウィンドウハンドル取得
         * @return HWND
         */
        HWND GetHWnd() const { return m_HWnd; }

        /*!
         * @brief 現在の幅取得
         * @return 幅
         */
        UINT GetWidth() const { return m_Width; }

        /*!
         * @brief 現在の高さ取得
         * @return 高さ
         */
        UINT GetHeight() const { return m_Height; }

        /*!
         * @brief フルスクリーン状態取得
         * @return true : フルスクリーン
         */
        bool IsFullScreen() const { return m_IsFullScreen; }

    private:
        /*!
         * @brief 静的ウィンドウプロシージャ
         */
        static LRESULT CALLBACK StaticWindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

        /*!
         * @brief インスタンス用ウィンドウプロシージャ
         */
        LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

    private:
        WindowManagerConfig m_Config;   /**< 初期設定 */
        HINSTANCE m_HInstance;          /**< インスタンスハンドル */
        HWND m_HWnd;                    /**< ウィンドウハンドル */

        UINT m_Width;                   /**< 現在の幅 */
        UINT m_Height;                  /**< 現在の高さ */
        int m_PosX;                     /**< 現在のX位置 */
        int m_PosY;                     /**< 現在のY位置 */

        bool m_IsRunning;               /**< メインループ継続フラグ */
        bool m_IsFullScreen;            /**< フルスクリーン状態 */
        LONG m_WindowedStyle;           /**< フルスクリーン切替用に保存するウィンドウスタイル */
    };
}
