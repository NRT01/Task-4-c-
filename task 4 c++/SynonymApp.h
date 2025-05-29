#pragma once

#include <afxwin.h>

class CSynonymApp : public CWinApp
{
    DECLARE_MESSAGE_MAP()

public:
    CSynonymApp();
    virtual ~CSynonymApp() = default;

    virtual BOOL InitInstance();
};
