/*!
 * @file FileSystem.h
 * @brief ファイル入出力および仮想ルート管理を行うクラス
 */

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "Core/File/FileData.h"

namespace Remiayle::Core::File
{
    /*!
     * @class FileSystem
     * @brief ファイルの読み書きおよび仮想ルート管理を行うユーティリティクラス
     */
    class FileSystem
    {
    public:

        // ==================================================
        // Root Management
        // ==================================================

        /*!
         * @brief 仮想ルートを登録する
         * @param name ルート名
         * @param path 実ディレクトリパス
         */
        static void RegisterRoot(const std::string& name,
            const std::filesystem::path& path);

        /*!
         * @brief 仮想ルートを削除する
         * @param name ルート名
         */
        static void UnregisterRoot(const std::string& name);

        /*!
         * @brief 仮想ルートのパスを取得する
         * @param name ルート名
         * @return パス（存在しなければ空）
         */
        static std::filesystem::path GetRootPath(const std::string& name);

        // ==================================================
        // Search
        // ==================================================

        /*!
         * @brief 実行ファイル基準で指定名を探索し、上位へ遡る
         * @param name ファイル名またはフォルダ名
         * @param maxDepth 最大遡り回数
         * @return 見つかったパス（無ければ空）
         */
        static std::filesystem::path FindUpwardByName(const std::string& name,
            std::uint32_t maxDepth);

        // ==================================================
        // Read
        // ==================================================

        /*!
         * @brief ファイルを読み込む
         * @param path ファイルパス
         * @return FileData
         */
        static FileData ReadFile(const std::filesystem::path& path);

        /*!
         * @brief 仮想ルートからファイルを読み込む
         * @param rootName 仮想ルート名
         * @param relativePath ルートからの相対パス
         * @return FileData
         */
        static FileData ReadFromRoot(const std::string& rootName,
            const std::filesystem::path& relativePath);

        // ==================================================
        // Write
        // ==================================================

        /*!
         * @brief FileDataに基づきファイルを書き込む
         * @param data 出力するデータ
         */
        static void WriteFile(const FileData& data);

        /*!
         * @brief 指定パスにFileDataを書き込む
         * @param path 出力先パス
         * @param data 書き込むデータ
         */
        static void WriteFile(const std::filesystem::path& path,
            const FileData& data);

        // ==================================================
        // Utility
        // ==================================================

        /*!
         * @brief パスが存在するか確認する
         * @param path 対象パス
         * @return 存在すればtrue
         */
        static bool Exists(const std::filesystem::path& path);

        /*!
         * @brief ディレクトリを作成する
         * @param path 作成するパス
         */
        static void CreateDirectory(const std::filesystem::path& path);

    private:

        static std::unordered_map<std::string, std::filesystem::path> s_Roots; /**< 仮想ルート一覧 */
    };
}
