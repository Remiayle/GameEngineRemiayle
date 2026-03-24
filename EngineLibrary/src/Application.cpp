/*!
 * @file Application.cpp
 * @brief エンジン全体の初期化・実行・終了処理を統括するアプリケーションクラス実装
 */

#include "EngineApp/Application.h"
#include "Core/Assert.h"
#include "Core/Log/Logger.h"
#include "Core/Time/RealClock.h"
#include "Core/Time/GameClock.h"

namespace Remiayle::EngineApp
{
	using namespace Core;

	Application::Application(const AppConfig& appConfig)
		: m_Config(appConfig)
		, m_WindowManager(nullptr)
	{

	}

	bool Application::Setup()
	{
		// 静的クラスの初期化(ロガークラスと実時間及びゲーム時間クラス)
		Log::Logger::Initialize();
		Time::RealClock::Initialize();
		Time::GameClock::Initialize();

		// ------------------------------
		// 各種機能の作成と初期化
		// ------------------------------

		// WindowManager
		m_WindowManager = std::make_unique<WindowManager>(m_Config.winCon);
		REMIAYLE_ASSERT(m_WindowManager->Setup());




		// ウィンドウの表示
		REMIAYLE_ASSERT(m_WindowManager->Show());
		return true;
	}

	void Application::Run()
	{
		// メインループ
		while (m_WindowManager->ProcessMessages())
		{
			// ゲーム時間の更新
			Time::GameClock::Update();


		}
	}

	void Application::Cleanup()
	{
		// ------------------------------
		// 各種機能の終了処理と破棄
		// ------------------------------

		// WindowManager
		REMIAYLE_ASSERT(m_WindowManager->Cleanup());
		m_WindowManager.release();
	}
}
