/*!
 * @file RealClock.h
 * @brief 実時間管理クラス
 */

#pragma once

#include <chrono>
#include <string>
#include "Core/Types.h"

namespace Remiayle::Core::Time
{
    /*!
     * @brief 実時間管理クラス
     *
     * OSの実時間を扱うクラス。
     * ゲーム時間とは独立して動作する。
     */
    class RealClock final
    {
    public:

        /*!
         * @brief 初期化
         *
         * エンジン起動時に呼び出す。
         */
        static void Initialize()
        {
            s_StartTime = SteadyClock::now();
        }

        /*!
         * @brief 起動からの経過時間取得（秒）
         */
        static f32 GetElapsedTime()
        {
            auto now = SteadyClock::now();
            std::chrono::duration<f32> elapsed = now - s_StartTime;
            return elapsed.count();
        }

        /*!
         * @brief 現在のシステム時刻取得
         */
        static std::chrono::system_clock::time_point GetNow()
        {
            return std::chrono::system_clock::now();
        }

        /*!
         * @brief フルタイムスタンプ文字列取得
         *
         * 形式: YYYY-MM-DD HH:MM:SS.mmm
         */
        static std::string GetTimestampString()
        {
            auto now = std::chrono::system_clock::now();
            auto timeT = std::chrono::system_clock::to_time_t(now);

            std::tm localTime{};
#ifdef _WIN32
            localtime_s(&localTime, &timeT);
#else
            localtime_r(&timeT, &localTime);
#endif

            char buffer[32];
            std::strftime(buffer, sizeof(buffer),
                "%Y-%m-%d %H:%M:%S", &localTime);

            auto milliseconds =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    now.time_since_epoch()) % 1000;

            char finalBuffer[40];
            std::snprintf(finalBuffer, sizeof(finalBuffer),
                "%s.%03d", buffer,
                static_cast<int>(milliseconds.count()));

            return std::string(finalBuffer);
        }

    private:

        using SteadyClock = std::chrono::steady_clock;

    private:

        static SteadyClock::time_point s_StartTime; /**< 起動時刻 */
    };
}
