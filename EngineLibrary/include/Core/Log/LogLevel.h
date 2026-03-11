/*!
 * @file LogLevel.h
 * @brief ログレベル定義
 */

#pragma once

namespace Remiayle::Core::Log
{
    /*!
     * @brief ログ出力レベル
     *
     * 値が大きいほど重要度が高い。
     */
    enum class LogLevel
    {
        Trace = 0,  /**< 詳細ログ */
        Debug,      /**< デバッグログ */
        Info,       /**< 通常情報 */
        Warning,    /**< 警告 */
        Error,      /**< エラー */
        Fatal       /**< 致命的エラー */
    };
}
