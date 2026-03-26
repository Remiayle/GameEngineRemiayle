/*!
 * @file Application.h
 * @brief エンジン全体の初期化・実行・終了処理を統括するアプリケーションクラス
 */

#pragma once
#include <memory>
#include "Window/WindowManager.h"

namespace Remiayle::EngineApp
{
    /*!
     * @struct AppConfig
     * @brief Application クラスの初期設定を保持する構造体
     *
     * ウィンドウ設定など、アプリケーション起動に必要な情報をまとめて保持します。
     * この構造体を main() 側で設定し、Application に渡すことで
     * エンジン全体の初期化が行われます。
     */
    struct AppConfig
    {
        Window::WindowManagerConfig winCon;    /**< ウィンドウ生成用設定 */
    };

    /*!
     * @class Application
     * @brief エンジンのライフサイクル全体を管理するクラス
     *
     * Application クラスは、エンジンの初期化・メインループ・終了処理を統括します。
     * このクラスを利用するプロジェクトの main() 関数は、
     *
     * 1. Application インスタンスの生成
     * 2. Setup() による初期化
     * 3. Run() によるメインループ実行
     * 4. Cleanup() による終了処理
     *
     * の 4 ステップのみで完結するように設計されています。
     *
     * 将来的にレンダリングシステムや入力管理などを追加する際も、
     * それらはすべて Application の内部で統合されるため、
     * 利用側は最小限のコードでエンジンを動作させることができます。
     */
    class Application
    {
    public:
        /*!
         * @brief コンストラクタ
         * @param appConfig アプリケーション全体の初期設定
         */
        Application(const AppConfig& appConfig);

        /*!
         * @brief デストラクタ
         */
        ~Application() = default;

        /*!
         * @brief エンジンの初期化処理
         * @return true : 成功 false : 失敗
         *
         * ウィンドウ生成や、今後追加される DirectX 初期化処理などを行います。
         */
        bool Setup();

        /*!
         * @brief メインループの実行
         *
         * ウィンドウメッセージ処理を行いながら、更新処理や描画処理を呼び出します。
         * エンジンのフレームワークとしての中心的な役割を担います。
         */
        void Run();

        /*!
         * @brief 終了処理
         *
         * ウィンドウ破棄や、今後追加される GPU リソース解放などを行います。
         */
        void Cleanup();

    private:
        const AppConfig m_Config;                          /**< アプリケーション初期設定 */
        std::unique_ptr<Window::WindowManager> m_WindowManager;    /**< ウィンドウ管理クラス */
    };
}
