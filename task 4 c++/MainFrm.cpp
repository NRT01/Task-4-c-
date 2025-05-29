#include "MainFrm.h"
#include "SynonymDictionary.h"
#include "TextProcessor.h"
#include "Logger.h"
#include "ExceptionHandler.h"
#include <afxdlgs.h> // CFileDialog
#include <string>
#include <memory>

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_WM_CREATE()
    ON_BN_CLICKED(IDC_BTN_SELECT_TEXT, &CMainFrame::OnSelectTextFile)
    ON_BN_CLICKED(IDC_BTN_SELECT_SYNONYMS, &CMainFrame::OnSelectSynonymsFile)
    ON_BN_CLICKED(IDC_BTN_PROCESS, &CMainFrame::OnProcessFiles)
END_MESSAGE_MAP()

CMainFrame::CMainFrame()
    : m_textProcessor(nullptr)
    , m_exceptionHandler(nullptr)
{
    // Инициализация логгера
    if (!m_logger.Init(L"log.txt"))
    {
        AfxMessageBox(L"Не удалось создать файл логов");
        return;
    }

    // Создаем обработчик исключений
    try
    {
        m_exceptionHandler = std::make_unique<ExceptionHandler>(m_logger);
    }
    catch (const std::exception& ex)
    {
        AfxMessageBox(L"Ошибка при инициализации обработчика исключений");
        return;
    }
}

CMainFrame::~CMainFrame() = default;

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // Создаем и размещаем кнопки элементов
    int btnWidth = 150, btnHeight = 30;
    int margin = 10;

    // Кнопка выбора файла с текстом
    m_btnSelectTextFile.Create(L"Выбрать текстовый файл", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        CRect(margin, margin, margin + btnWidth, margin + btnHeight),
        this, IDC_BTN_SELECT_TEXT);

    // Кнопка выбора файла с синонимами
    m_btnSelectSynonymsFile.Create(L"Выбрать файл с синонимами", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        CRect(margin, margin * 2 + btnHeight, margin + btnWidth, margin * 2 + btnHeight * 2),
        this, IDC_BTN_SELECT_SYNONYMS);

    // Кнопка обработки
    m_btnProcess.Create(L"Обработать", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        CRect(margin, margin * 3 + btnHeight * 2, margin + btnWidth, margin * 3 + btnHeight * 3),
        this, IDC_BTN_PROCESS);

    // Многострочное поле для вывода логов (вертикальная, с прокруткой)
    m_logEdit.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        CRect(margin * 2 + btnWidth, margin, 700, 400), this, IDC_EDIT_LOG);

    return 0;
}

void CMainFrame::LogMessage(const std::wstring& msg)
{
    m_logEdit.SetSel(-1, -1);
    m_logEdit.ReplaceSel(CString(msg.c_str()) + L"\r\n");
    m_logger.LogInfo(msg);
}

bool CMainFrame::OpenFileDialog(CString& outPath, const WCHAR* filter)
{
    CFileDialog dlg(TRUE, nullptr, nullptr, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filter);
    if (dlg.DoModal() == IDOK)
    {
        outPath = dlg.GetPathName();
        return true;
    }
    return false;
}

void CMainFrame::OnSelectTextFile()
{
    if (OpenFileDialog(m_textFilePath, L"Текстовые файлы (*.txt)|*.txt||"))
    {
        LogMessage(std::wstring(m_textFilePath));
    }
}

void CMainFrame::OnSelectSynonymsFile()
{
    if (OpenFileDialog(m_synonymsFilePath, L"Файлы с синонимами (*.txt)|*.txt||"))
    {
        LogMessage(std::wstring(m_synonymsFilePath));
    }
}

void CMainFrame::OnProcessFiles()
{
    if (m_textFilePath.IsEmpty() || m_synonymsFilePath.IsEmpty())
    {
        AfxMessageBox(L"Пожалуйста, выберите оба файла: текстовый файл и словарь синонимов.");
        return;
    }

    try
    {
        LogMessage(L"Начинается загрузка словаря синонимов...");
        
        // Очищаем старый словарь
        m_dictionary.Clear();
        
        if (!m_dictionary.LoadFromFile(std::wstring(m_synonymsFilePath)))
        {
            AfxMessageBox(L"Ошибка загрузки файла с синонимами.");
            LogMessage(L"Ошибка загрузки файла с синонимами.");
            return;
        }
        LogMessage(L"Словарь синонимов загружен успешно.");

        // Создаем новый текстовый процессор
        m_textProcessor = std::make_unique<TextProcessor>(m_dictionary);

        LogMessage(L"Начинается обработка текста...");
        CString outputFilePath = m_textFilePath;
        outputFilePath.Replace(L".txt", L"_output.txt");

        if (!m_textProcessor->ProcessFile(std::wstring(m_textFilePath), std::wstring(outputFilePath)))
        {
            AfxMessageBox(L"Ошибка обработки текстового файла.");
            LogMessage(L"Ошибка обработки текстового файла.");
            return;
        }

        LogMessage(L"Обработка завершена успешно. Результат сохранен в: " + std::wstring(outputFilePath));
    }
    catch (const std::exception& ex)
    {
        if (m_exceptionHandler)
        {
            m_exceptionHandler->HandleException(ex, L"Ошибка во время обработки");
        }
        else
        {
            AfxMessageBox(L"Произошла ошибка, и обработчик исключений недоступен");
            m_logger.LogError(L"Ошибка без обработчика исключений: " + std::wstring(ex.what()));
        }
    }
    catch (...)
    {
        if (m_exceptionHandler)
        {
            m_exceptionHandler->HandleUnknownException(L"Неизвестная ошибка во время обработки");
        }
        else
        {
            AfxMessageBox(L"Произошла неизвестная ошибка, и обработчик исключений недоступен");
            m_logger.LogError(L"Неизвестная ошибка без обработчика исключений");
        }
    }
}
