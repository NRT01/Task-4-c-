#pragma once

#include <afxwin.h>
#include <memory>
#include "Resource.h"

// Предварительные объявления
class SynonymDictionary;
class TextProcessor;
class Logger;
class ExceptionHandler;

class CMainFrame : public CFrameWnd
{
    DECLARE_MESSAGE_MAP()

public:
    CMainFrame();
    virtual ~CMainFrame();

protected:
    // Обработчики сообщений
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSelectTextFile();
    afx_msg void OnSelectSynonymsFile();
    afx_msg void OnProcessFiles();

private:
    // UI элементы
    CEdit m_logEdit;
    CButton m_btnSelectTextFile;
    CButton m_btnSelectSynonymsFile;
    CButton m_btnProcess;

    CString m_textFilePath;
    CString m_synonymsFilePath;

    SynonymDictionary m_dictionary;
    std::unique_ptr<TextProcessor> m_textProcessor;
    Logger m_logger;
    std::unique_ptr<ExceptionHandler> m_exceptionHandler;

    // Вспомогательные методы
    void LogMessage(const CString& msg);
    bool OpenFileDialog(CString& outPath, const WCHAR* filter);
};
