/*!
 * @file GameClock.cpp
 * @brief ÉQÅ[ÉÄéûä‘ä«óùÉNÉâÉXé¿ëï
 */

#include "Core/Time/GameClock.h"

namespace Remiayle::Core::Time
{
    GameClock::Clock::time_point GameClock::s_StartTime;
    GameClock::Clock::time_point GameClock::s_PreviousTime;

    f32 GameClock::s_DeltaTime = 0.0f;
    f32 GameClock::s_TotalTime = 0.0f;
    u64 GameClock::s_FrameCount = 0;

    f32 GameClock::s_FPS = 0.0f;
    u64 GameClock::s_FrameCounterForFPS = 0;
    f32 GameClock::s_FPSTimer = 0.0f;

    f32 GameClock::s_TimeScale = 1.0f;
    bool GameClock::s_IsPaused = false;

    void GameClock::Initialize()
    {
        s_StartTime = Clock::now();
        s_PreviousTime = s_StartTime;

        s_DeltaTime = 0.0f;
        s_TotalTime = 0.0f;

		s_UnscaledDeltaTime = 0.0f;
		s_UnscaledTotalTime = 0.0f;

        s_FrameCount = 0;

        s_FPS = 0.0f;
        s_FrameCounterForFPS = 0;
        s_FPSTimer = 0.0f;

        s_TimeScale = 1.0f;
        s_IsPaused = false;
    }

    void GameClock::Update()
    {
        auto current = Clock::now();

        std::chrono::duration<f32> delta = current - s_PreviousTime;
        f32 rawDelta = delta.count();

        s_PreviousTime = current;

        if (s_IsPaused)
        {
            s_DeltaTime = 0.0f;
            return;
        }

        s_DeltaTime = rawDelta * s_TimeScale;
        s_TotalTime += s_DeltaTime;

		s_UnscaledDeltaTime = rawDelta;
		s_UnscaledTotalTime += s_UnscaledDeltaTime;

        ++s_FrameCount;

        ++s_FrameCounterForFPS;
        s_FPSTimer += rawDelta;

        if (s_FPSTimer >= 1.0f)
        {
            s_FPS = static_cast<f32>(s_FrameCounterForFPS) / s_FPSTimer;
            s_FrameCounterForFPS = 0;
            s_FPSTimer -= 1.0f;
        }
    }

    f32 GameClock::GetDeltaTime()
    {
        return s_DeltaTime;
    }

    f32 GameClock::GetTotalTime()
    {
        return s_TotalTime;
    }

    f32 GameClock::GetUnscaledDeltaTime()
    {
		return s_UnscaledDeltaTime;
    }

    f32 GameClock::GetUnscaledTotalTime()
	{
		return s_UnscaledTotalTime;
	}

    u64 GameClock::GetFrameCount()
    {
        return s_FrameCount;
    }

    f32 GameClock::GetFPS()
    {
        return s_FPS;
    }

    void GameClock::SetTimeScale(f32 scale)
    {
        s_TimeScale = scale;
    }

    f32 GameClock::GetTimeScale()
    {
        return s_TimeScale;
    }

    void GameClock::Pause()
    {
        s_IsPaused = true;
    }

    void GameClock::Resume()
    {
        s_IsPaused = false;
    }

    bool GameClock::IsPaused()
    {
        return s_IsPaused;
    }
}
