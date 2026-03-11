/*!
 * @file GameClock.h
 * @brief ゲーム時間管理クラス
 */

#pragma once

#include <chrono>
#include "Core/Types.h"

namespace Remiayle::Core::Time
{
    /*!
     * @brief ゲーム時間管理クラス
     *
     * フレーム時間、総経過時間、FPS、
     * TimeScaleおよびPause制御を行う。
     */
    class GameClock final
    {
    public:

        /*!
         * @brief 初期化
         */
        static void Initialize();

        /*!
         * @brief フレーム更新
         */
        static void Update();

        /*!
         * @brief デルタタイム取得（秒）
         */
        static f32 GetDeltaTime();

        /*!
         * @brief 総経過時間取得（秒）
         */
        static f32 GetTotalTime();

        /*!
         * @brief TimeScale無視のデルタタイム取得（秒）
		 */
		static f32 GetUnscaledDeltaTime();

        /*!
         * @brief TimeScale無視の総経過時間取得（秒）
		 */
		static f32 GetUnscaledTotalTime();

        /*!
         * @brief フレーム数取得
         */
        static u64 GetFrameCount();

        /*!
         * @brief FPS取得
         */
        static f32 GetFPS();

        /*!
         * @brief TimeScale設定
         */
        static void SetTimeScale(f32 scale);

        /*!
         * @brief TimeScale取得
         */
        static f32 GetTimeScale();

        /*!
         * @brief 一時停止
         */
        static void Pause();

        /*!
         * @brief 再開
         */
        static void Resume();

        /*!
         * @brief 一時停止中か
         */
        static bool IsPaused();

    private:

        using Clock = std::chrono::steady_clock;

    private:

        static Clock::time_point s_StartTime;      /**< 起動時刻 */
        static Clock::time_point s_PreviousTime;   /**< 前フレーム時刻 */

        static f32 s_DeltaTime;                    /**< フレーム間時間（秒） */
        static f32 s_TotalTime;                    /**< 総経過時間（秒） */

		static f32 s_UnscaledDeltaTime;            /**< フレーム間時間（秒、TimeScale無視） */
		static f32 s_UnscaledTotalTime;            /**< 総経過時間（秒、TimeScale無視） */

        static u64 s_FrameCount;                   /**< フレーム数 */

        static f32 s_FPS;                          /**< 現在のFPS */
        static u64 s_FrameCounterForFPS;           /**< FPS計算用フレーム数 */
        static f32 s_FPSTimer;                     /**< FPS計算用経過時間 */

        static f32 s_TimeScale;                    /**< 時間倍率 */
        static bool s_IsPaused;                    /**< 一時停止フラグ */
    };
}
