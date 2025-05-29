#include "LogViewerDialog.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(CLogViewerDialog, CDialogEx)

BEGIN_MESSAGE_MAP(CLogViewerDialog, CDialogEx)
END_MESSAGE_MAP()

CLogViewerDialog::CLogViewerDialog(CWnd* pParent)
    : CDialogEx(IDD_LOGVIEWER_DIALOG, pParent)
{
}

CLogViewerDialog::~CLogViewerDialog()
{
}

void CLogViewerDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_LOG, m_editLog);
}

BOOL CLogViewerDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    return TRUE;
}

void CLogViewerDialog::AppendLogLine(const CString& line)
{
    int len = m_editLog.GetWindowTextLength();
    m_editLog.SetSel(len, len);
    m_editLog.ReplaceSel(line + _T("\r\n"));
}
