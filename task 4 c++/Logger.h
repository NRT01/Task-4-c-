#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <chrono>
#include <ctime>

class Logger
{
public:
    enum class Level
    {
        Info,
        Warning,
        Error
    };

    Logger();
    ~Logger();

    // Инициализация с указанием файла для логов
    bool Init(const std::wstring& filename);

    void Log(Level level, const std::wstring& message);

    void LogInfo(const std::wstring& message);
    void LogWarning(const std::wstring& message);
    void LogError(const std::wstring& message);

private:
    std::wofstream m_logFile;
    std::mutex m_mutex;

    std::wstring LevelToString(Level level) const;
    std::wstring GetCurrentTimeString() const;
};
