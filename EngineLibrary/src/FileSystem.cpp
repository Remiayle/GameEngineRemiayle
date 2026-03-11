/*!
 * @file FileSystem.cpp
 * @brief ファイル入出力および仮想ルート管理の実装
 */

#include <fstream>
#include "Core/File/FileSystem.h"

namespace Remiayle::Core::File
{
    std::unordered_map<std::string, std::filesystem::path> FileSystem::s_Roots;

    // ==================================================
    // Root Management
    // ==================================================

    void FileSystem::RegisterRoot(const std::string& name,
        const std::filesystem::path& path)
    {
        s_Roots[name] = path;
    }

    void FileSystem::UnregisterRoot(const std::string& name)
    {
        s_Roots.erase(name);
    }

    std::filesystem::path FileSystem::GetRootPath(const std::string& name)
    {
        auto it = s_Roots.find(name);
        if (it != s_Roots.end())
        {
            return it->second;
        }
        return {};
    }

    // ==================================================
    // Search
    // ==================================================

    std::filesystem::path FileSystem::FindUpwardByName(const std::string& name,
        std::uint32_t maxDepth)
    {
        std::filesystem::path current = std::filesystem::current_path();

        for (std::uint32_t i = 0; i <= maxDepth; ++i)
        {
            std::filesystem::path candidate = current / name;

            if (std::filesystem::exists(candidate))
            {
                return candidate;
            }

            if (!current.has_parent_path())
            {
                break;
            }

            current = current.parent_path();
        }

        return {};
    }

    // ==================================================
    // Read
    // ==================================================

    FileData FileSystem::ReadFile(const std::filesystem::path& path)
    {
        FileData result;
        result.m_Path = path;

        std::ifstream file(path, std::ios::binary);
        if (!file)
        {
            return result;
        }

        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        result.m_Data.resize(static_cast<std::size_t>(size));

        if (size > 0)
        {
            file.read(reinterpret_cast<char*>(result.m_Data.data()), size);
        }

        return result;
    }

    FileData FileSystem::ReadFromRoot(const std::string& rootName,
        const std::filesystem::path& relativePath)
    {
        std::filesystem::path root = GetRootPath(rootName);
        if (root.empty())
        {
            return {};
        }

        return ReadFile(root / relativePath);
    }

    // ==================================================
    // Write
    // ==================================================

    void FileSystem::WriteFile(const FileData& data)
    {
        if (data.m_Path.empty())
        {
            return;
        }

        WriteFile(data.m_Path, data);
    }

    void FileSystem::WriteFile(const std::filesystem::path& path,
        const FileData& data)
    {
        std::ofstream file(path, std::ios::binary);
        if (!file)
        {
            return;
        }

        if (!data.m_Data.empty())
        {
            file.write(reinterpret_cast<const char*>(data.m_Data.data()),
                static_cast<std::streamsize>(data.m_Data.size()));
        }
    }

    // ==================================================
    // Utility
    // ==================================================

    bool FileSystem::Exists(const std::filesystem::path& path)
    {
        return std::filesystem::exists(path);
    }

    void FileSystem::CreateDirectory(const std::filesystem::path& path)
    {
        std::filesystem::create_directories(path);
    }
}
