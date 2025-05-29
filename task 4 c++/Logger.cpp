#include "Logger.h"
#include <locale>
#include <codecvt>
#include <iomanip>
#include <sstream>

Logger::Logger()
{
}

Logger::~Logger()
{
    if (m_logFile.is_open())
        m_logFile.close();
}

bool Logger::Init(const std::wstring& filename)
{
    m_logFile.open(filename, std::ios::app);
    if (!m_logFile.is_open())
        return false;

    // Устанавливаем локаль UTF-8 с BOM для корректной записи
    m_logFile.imbue(std::locale(m_logFile.getloc(),
        new std::codecvt_utf8_utf16<wchar_t, 0x10ffff, std::generate_header>));

    return true;
}

void Logger::Log(Logger::Level level, const std::wstring& message)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_logFile.is_open())
        return;

    m_logFile << L"[" << GetCurrentTimeString() << L"] "
        << L"[" << LevelToString(level) << L"] "
        << message << std::endl;

    m_logFile.flush();
}

void Logger::LogInfo(const std::wstring& message)
{
    Log(Level::Info, message);
}

void Logger::LogWarning(const std::wstring& message)
{
    Log(Level::Warning, message);
}

void Logger::LogError(const std::wstring& message)
{
    Log(Level::Error, message);
}

std::wstring Logger::LevelToString(Logger::Level level) const
{
    switch (level)
    {
    case Level::Info: return L"INFO";
    case Level::Warning: return L"WARNING";
    case Level::Error: return L"ERROR";
    default: return L"UNKNOWN";
    }
}

std::wstring Logger::GetCurrentTimeString() const
{
    using namespace std::chrono;

    auto now = system_clock::now();
    std::time_t now_time = system_clock::to_time_t(now);

    std::tm local_tm;
#ifdef _WIN32
    localtime_s(&local_tm, &now_time);
#else
    localtime_r(&now_time, &local_tm);
#endif

    std::wstringstream wss;
    wss << std::put_time(&local_tm, L"%Y-%m-%d %H:%M:%S");

    return wss.str();
}
