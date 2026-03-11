/*!
 * @file ILogSink.h
 * @brief ログ出力先インターフェース定義
 */

#pragma once

#include <string>

namespace Remiayle::Core::Log
{
    /*!
     * @brief ログ出力先インターフェース
     *
     * Logger から整形済みログメッセージを受け取り、
     * 具体的な出力処理を行うための抽象クラス。
     *
     * 例：
     * - コンソール出力
     * - ファイル出力
     * - デバッグウィンドウ出力
     */
    class ILogSink
    {
    public:

        /*!
         * @brief デストラクタ
         */
        virtual ~ILogSink() = default;

        /*!
         * @brief ログメッセージ出力
         *
         * @param message 整形済みログメッセージ
         */
        virtual void Write(const std::string& message) = 0;
    };
}
