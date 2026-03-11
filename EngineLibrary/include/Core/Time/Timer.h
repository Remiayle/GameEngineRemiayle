/*!
 * @file Timer.h
 * @brief 拡張対応ゲームタイマークラス
 */

#pragma once

#include "Core/Types.h"

namespace Remiayle::Core::Time
{
    /*!
     * @brief タイマーフラグ
     *
     * ビットマスクで複数指定可能。
     *
     * Loop           : 無限ループ
     * LimitedLoop    : 指定回数ループ
     * UnscaledTime   : TimeScale無視
     * FixedInterval  : フレーム超過時複数回発火保証
     */
    enum class TimerFlags : u32
    {
        None          = 0,        /**< フラグなし */
        Loop          = 1 << 0,   /**< 無限ループ */
        LimitedLoop   = 1 << 1,   /**< 指定回数ループ */
        UnscaledTime  = 1 << 2,   /**< TimeScale無視 */
        FixedInterval = 1 << 3    /**< 複数回発火保証 */
    };

    /*!
     * @brief ビットOR演算子
     */
    inline TimerFlags operator|(TimerFlags a, TimerFlags b)
    {
        return static_cast<TimerFlags>(
            static_cast<u32>(a) | static_cast<u32>(b)
            );
    }

    /*!
     * @brief GameClock依存のゲームタイマー
     *
     * ・TimeScaleの影響を受ける／無視可能
     * ・ループ、指定回数ループ対応
     * ・FixedInterval保証対応
     * ・継承拡張可能
     */
    class Timer
    {
    public:

        /*!
         * @brief コンストラクタ
         */
        Timer();

        /*!
         * @brief 仮想デストラクタ
         */
        virtual ~Timer() = default;

        /*!
         * @brief タイマー開始
         *
         * @param duration       設定時間（秒）
         * @param flags          タイマーフラグ
         * @param maxLoopCount   指定回数ループ時の最大回数
         */
        void Start(
            f32 duration,
            TimerFlags flags = TimerFlags::None,
            u32 maxLoopCount = 0);

        /*!
         * @brief 更新処理
         *
         * 毎フレーム呼び出す。
         */
        void Update();

        /*!
         * @brief 停止
         */
        void Stop();

        /*!
         * @brief リセット
         */
        void Reset();

        /*!
         * @brief 動作中か
         */
        bool IsRunning() const;

        /*!
         * @brief 終了済みか
         */
        bool IsFinished() const;

        /*!
         * @brief 残り時間取得
         */
        f32 GetRemainingTime() const;

        /*!
         * @brief 経過時間取得
         */
        f32 GetElapsedTime() const;

        /*!
         * @brief 設定時間取得
         */
        f32 GetDuration() const;

    protected:

        /*!
         * @brief タイマー発火時に呼ばれる
         *
         * 継承クラスでオーバーライド可能。
         */
        virtual void OnTimerTriggered();

        /*!
         * @brief 指定フラグを保持しているか
         */
        bool HasFlag(TimerFlags flag) const;

    protected:

        f32 m_Duration;                /**< 設定時間（秒） */
        f32 m_ElapsedTime;             /**< 経過時間（秒） */
        TimerFlags m_Flags;            /**< タイマーフラグ */
        u32 m_MaxLoopCount;            /**< 最大ループ回数 */
        u32 m_CurrentLoopCount;        /**< 現在ループ回数 */
        bool m_IsRunning;              /**< 動作中フラグ */
        bool m_IsFinished;             /**< 終了フラグ */
    };
}
