/*!
 * @file Logger.cpp
 * @brief ÉçÉOä«óùÉNÉâÉXé¿ëï
 */

#include "Core/Log/Logger.h"
#include "Core/Time/RealClock.h"

namespace Remiayle::Core::Log
{
    std::vector<std::unique_ptr<ILogSink>> Logger::s_Sinks;
    LogLevel Logger::s_CurrentLevel = LogLevel::Trace;

    void Logger::Initialize()
    {
        s_Sinks.clear();
    }

    void Logger::AddSink(std::unique_ptr<ILogSink> sink)
    {
        s_Sinks.emplace_back(std::move(sink));
    }

    void Logger::SetLevel(LogLevel level)
    {
        s_CurrentLevel = level;
    }

    void Logger::Log(LogLevel level, const std::string& message)
    {
        if (static_cast<int>(level) < static_cast<int>(s_CurrentLevel))
        {
            return;
        }

        std::string formatted = Format(level, message);

        for (auto& sink : s_Sinks)
        {
            sink->Write(formatted);
        }
    }

    std::string Logger::Format(LogLevel level, const std::string& message)
    {
        std::string timestamp =
            Remiayle::Core::Time::RealClock::GetTimestampString();

        return "[" + timestamp + "] "
            + "[" + LevelToString(level) + "] "
            + message + "\n";
    }

    std::string Logger::LevelToString(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::Trace:   return "Trace";
        case LogLevel::Debug:   return "Debug";
        case LogLevel::Info:    return "Info";
        case LogLevel::Warning: return "Warning";
        case LogLevel::Error:   return "Error";
        case LogLevel::Fatal:   return "Fatal";
        default:                return "Unknown";
        }
    }
}
