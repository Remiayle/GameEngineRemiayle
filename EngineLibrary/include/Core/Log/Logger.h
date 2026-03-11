/*!
 * @file Logger.h
 * @brief ログ管理クラス
 */

#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Core/Log/LogLevel.h"
#include "Core/Log/ILogSink.h"

namespace Remiayle::Core::Log
{
    /*!
     * @brief ログ管理クラス
     */
    class Logger final
    {
    public:

        /*!
         * @brief 初期化
         */
        static void Initialize();

        /*!
         * @brief Sink追加
         */
        static void AddSink(std::unique_ptr<ILogSink> sink);

        /*!
         * @brief ログ出力
         */
        static void Log(LogLevel level, const std::string& message);

        /*!
         * @brief ログレベル設定
         */
        static void SetLevel(LogLevel level);

    private:

        static std::string Format(LogLevel level, const std::string& message);
        static std::string LevelToString(LogLevel level);

    private:

        static std::vector<std::unique_ptr<ILogSink>> s_Sinks; /**< 出力先 */
        static LogLevel s_CurrentLevel;                        /**< 現在のログレベル */
    };
}
