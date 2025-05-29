#pragma once

#include <string>
#include <exception>

class Logger;

class ExceptionHandler
{
public:
    explicit ExceptionHandler(Logger& logger);
    ~ExceptionHandler() = default;

    // Обработать исключение: логировать и показать сообщение
    void HandleException(const std::exception& ex, const std::wstring& contextMessage = L"");

    // Перегрузка для неизвестных исключений
    void HandleUnknownException(const std::wstring& contextMessage = L"");

private:
    Logger& m_logger;

    // Показать окно с сообщением пользователю (MFC MessageBox)
    void ShowErrorMessage(const std::wstring& message);
};
