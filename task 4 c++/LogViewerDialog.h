#pragma once
#include <afxwin.h>
#include <afxdlgs.h>
#include "Resource.h"

class CLogViewerDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CLogViewerDialog)

public:
    CLogViewerDialog(CWnd* pParent = nullptr);
    virtual ~CLogViewerDialog();

    enum { IDD = IDD_LOGVIEWER_DIALOG };

    // Добавить в окно одну строку текста
    void AppendLogLine(const CString& line);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

private:
    CEdit m_editLog;
};
