#include "ExceptionHandler.h"
#include "Logger.h"
#include <afxwin.h> // ��� AfxMessageBox

ExceptionHandler::ExceptionHandler(Logger& logger)
    : m_logger(logger)
{
}

void ExceptionHandler::HandleException(const std::exception& ex, const std::wstring& contextMessage)
{
    std::wstring errMsg = contextMessage.empty() ? L"" : (contextMessage + L"\n");
    errMsg += L"Exception: ";
    // ����������� std::exception::what() � wstring
    std::string whatStr = ex.what();
    errMsg += std::wstring(whatStr.begin(), whatStr.end());

    m_logger.LogError(errMsg);

    ShowErrorMessage(errMsg);
}

void ExceptionHandler::HandleUnknownException(const std::wstring& contextMessage)
{
    std::wstring errMsg = contextMessage.empty() ? L"" : (contextMessage + L"\n");
    errMsg += L"Unknown exception occurred";

    m_logger.LogError(errMsg);
    ShowErrorMessage(errMsg);
}

void ExceptionHandler::ShowErrorMessage(const std::wstring& message)
{
    ::MessageBoxW(nullptr, message.c_str(), L"������", MB_ICONERROR | MB_OK);
}
