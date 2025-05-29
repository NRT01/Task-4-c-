#include "SynonymApp.h"
#include "MainFrm.h"

BEGIN_MESSAGE_MAP(CSynonymApp, CWinApp)
END_MESSAGE_MAP()

CSynonymApp::CSynonymApp()
{
}

BOOL CSynonymApp::InitInstance()
{
    CWinApp::InitInstance();

    // Создаем главное окно
    CMainFrame* pFrame = new CMainFrame();
    m_pMainWnd = pFrame;

    if (!pFrame->Create(NULL, L"Synonym Replacement App"))
    {
        delete pFrame;
        return FALSE;
    }

    pFrame->ShowWindow(SW_SHOW);
    pFrame->UpdateWindow();

    return TRUE;
}
