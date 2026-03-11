/*!
 * @file FileData.h
 * @brief ファイルデータ構造体定義
 */

#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include "Core/Types.h"

namespace Remiayle::Core::File
{
    /*!
     * @brief ファイルデータ保持構造体
     *
     * 読み込まれたファイルの内容を保持する。
     * 解釈は行わず、生バイト列として扱う。
     */
    struct FileData
    {
        std::filesystem::path m_Path; /**< ファイルパス */
        std::vector<u8>       m_Data; /**< ファイルデータ */

        /*!
         * @brief データが空か判定する
         * @return 空ならtrue
         */
        bool IsEmpty() const;

        /*!
         * @brief ファイルサイズを取得
         * @return バイト数
         */
        size_t GetSize() const;

        /*!
         * @brief テキストとして取得
         * @return std::stringに変換したデータ
         */
        std::string GetText() const;

        /*!
         * @brief テキストを設定
         * @param text 設定する文字列
         */
        void SetText(const std::string& text);
    };
}
