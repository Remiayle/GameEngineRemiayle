/*!
 * @file FileData.cpp
 * @brief ファイルデータ構造体実装
 */

#include "Core/File/FileData.h"

namespace Remiayle::Core::File
{
    bool FileData::IsEmpty() const
    {
        return m_Data.empty();
    }

    size_t FileData::GetSize() const
    {
        return m_Data.size();
    }

    std::string FileData::GetText() const
    {
        return std::string(m_Data.begin(), m_Data.end());
    }

    void FileData::SetText(const std::string& text)
    {
        m_Data.assign(text.begin(), text.end());
    }
}
