/*!
 * @file Timer.cpp
 * @brief 拡張対応ゲームタイマークラス実装
 */

#include "Core/Time/Timer.h"
#include "Core/Time/GameClock.h"

namespace Remiayle::Core::Time
{
    /*!
     * @brief コンストラクタ
     */
    Timer::Timer()
        : m_Duration(0.0f)
        , m_ElapsedTime(0.0f)
        , m_Flags(TimerFlags::None)
        , m_MaxLoopCount(0)
        , m_CurrentLoopCount(0)
        , m_IsRunning(false)
        , m_IsFinished(false)
    {
    }

    /*!
     * @brief タイマー開始
     */
    void Timer::Start(f32 duration, TimerFlags flags, u32 maxLoopCount)
    {
        m_Duration = duration;
        m_Flags = flags;
        m_MaxLoopCount = maxLoopCount;
        m_CurrentLoopCount = 0;

        m_ElapsedTime = 0.0f;
        m_IsRunning = true;
        m_IsFinished = false;
    }

    /*!
     * @brief 更新処理
     */
    void Timer::Update()
    {
        if (!m_IsRunning || m_IsFinished)
        {
            return;
        }

        f32 deltaTime = HasFlag(TimerFlags::UnscaledTime)
            ? GameClock::GetUnscaledDeltaTime()
            : GameClock::GetDeltaTime();

        m_ElapsedTime += deltaTime;

        auto ProcessTrigger = [this]() -> bool
        {
            OnTimerTriggered();

            m_CurrentLoopCount++;

            if (HasFlag(TimerFlags::LimitedLoop) &&
                m_CurrentLoopCount >= m_MaxLoopCount)
            {
                m_IsFinished = true;
                m_IsRunning = false;
                return false;
            }

            if (HasFlag(TimerFlags::Loop) ||
                HasFlag(TimerFlags::LimitedLoop))
            {
                m_ElapsedTime -= m_Duration;
                return true;
            }

            m_IsFinished = true;
            m_IsRunning = false;
            m_ElapsedTime = m_Duration;
            return false;
        };

        if (HasFlag(TimerFlags::FixedInterval))
        {
            while (m_ElapsedTime >= m_Duration)
            {
                if (!ProcessTrigger())
                {
                    break;
                }
            }
        }
        else
        {
            if (m_ElapsedTime >= m_Duration)
            {
                ProcessTrigger();
            }
        }
    }

    /*!
     * @brief 停止
     */
    void Timer::Stop()
    {
        m_IsRunning = false;
    }

    /*!
     * @brief リセット
     */
    void Timer::Reset()
    {
        m_ElapsedTime = 0.0f;
        m_CurrentLoopCount = 0;
        m_IsFinished = false;
        m_IsRunning = false;
    }

    /*!
     * @brief 動作中か
     */
    bool Timer::IsRunning() const
    {
        return m_IsRunning;
    }

    /*!
     * @brief 終了済みか
     */
    bool Timer::IsFinished() const
    {
        return m_IsFinished;
    }

    /*!
     * @brief 残り時間取得
     */
    f32 Timer::GetRemainingTime() const
    {
        return m_Duration - m_ElapsedTime;
    }

    /*!
     * @brief 経過時間取得
     */
    f32 Timer::GetElapsedTime() const
    {
        return m_ElapsedTime;
    }

    /*!
     * @brief 設定時間取得
     */
    f32 Timer::GetDuration() const
    {
        return m_Duration;
    }

    /*!
     * @brief 指定フラグ保持判定
     */
    bool Timer::HasFlag(TimerFlags flag) const
    {
        return (static_cast<u32>(m_Flags) &
            static_cast<u32>(flag)) != 0;
    }

    /*!
     * @brief タイマー発火時処理
     */
    void Timer::OnTimerTriggered()
    {
        // デフォルトでは何もしない
    }
}
