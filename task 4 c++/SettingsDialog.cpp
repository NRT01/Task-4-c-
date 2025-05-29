#include "SettingsDialog.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(CSettingsDialog, CDialogEx)

BEGIN_MESSAGE_MAP(CSettingsDialog, CDialogEx)
END_MESSAGE_MAP()

CSettingsDialog::CSettingsDialog(CWnd* pParent)
    : CDialogEx(IDD_SETTINGS_DIALOG, pParent)
    , m_caseSensitive(FALSE)
{
}

CSettingsDialog::~CSettingsDialog()
{
}

void CSettingsDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_CASE_SENSITIVE, m_caseSensitive);
}

BOOL CSettingsDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    return TRUE;
}
