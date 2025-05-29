#pragma once
#include <afxwin.h>
#include <afxdlgs.h>
#include "Resource.h"

class CSettingsDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CSettingsDialog)

public:
    CSettingsDialog(CWnd* pParent = nullptr);
    virtual ~CSettingsDialog();

    enum { IDD = IDD_SETTINGS_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

public:
    BOOL m_caseSensitive; // Флаг чувствительности к регистру
};
