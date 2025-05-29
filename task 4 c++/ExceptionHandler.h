#pragma once

#include <string>
#include <exception>

class Logger;

class ExceptionHandler
{
public:
    explicit ExceptionHandler(Logger& logger);
    ~ExceptionHandler() = default;

    // ���������� ����������: ���������� � �������� ���������
    void HandleException(const std::exception& ex, const std::wstring& contextMessage = L"");

    // ���������� ��� ����������� ����������
    void HandleUnknownException(const std::wstring& contextMessage = L"");

private:
    Logger& m_logger;

    // �������� ���� � ���������� ������������ (MFC MessageBox)
    void ShowErrorMessage(const std::wstring& message);
};
