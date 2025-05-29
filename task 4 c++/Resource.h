#include "resource.h"
#pragma once

// Идентификаторы меню
#define ID_FILE_EXIT              100
#define ID_HELP_ABOUT            101

// Идентификаторы диалогов
#define IDD_LOGVIEWER_DIALOG     1000
#define IDD_SETTINGS_DIALOG      1001

// Идентификаторы элементов управления
#define IDC_EDIT_LOG             2000
#define IDC_CHECK_CASE_SENSITIVE 2001

// Идентификаторы кнопок
#define IDC_BTN_SELECT_TEXT      3000
#define IDC_BTN_SELECT_SYNONYMS  3001
#define IDC_BTN_PROCESS          3002
#define IDC_BTN_VIEW_LOG         3003

// Стандартные идентификаторы
#ifndef IDC_STATIC
#define IDC_STATIC              -1
#endif

// Иконки и изображения
#define IDI_APP_ICON             4000
#define IDB_LOGO_BITMAP          4001

// Next default values for new objects
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        4002
#define _APS_NEXT_COMMAND_VALUE         32771
#define _APS_NEXT_CONTROL_VALUE         3004
#define _APS_NEXT_SYMED_VALUE          3000
#endif
#endif

IDR_MAINMENU MENU
BEGIN
POPUP "&"
BEGIN
MENUITEM "", ID_FILE_EXIT
END
POPUP "&"
BEGIN
MENUITEM " ", ID_HELP_ABOUT
END
END

IDD_SETTINGS_DIALOG DIALOGEX 0, 0, 250, 120
STYLE DS_SETFONT | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "���������"
FONT 8, "MS Shell Dlg"
BEGIN
CONTROL "��������� �������", IDC_CHECK_CASE_SENSITIVE, "Button",
BS_AUTOCHECKBOX | WS_TABSTOP, 15, 20, 120, 20
DEFPUSHBUTTON "��", IDOK, 50, 90, 50, 14
PUSHBUTTON "������", IDCANCEL, 120, 90, 50, 14
END

IDI_APP_ICON ICON "res\\app.ico"
IDB_LOGO_BITMAP BITMAP "res\\logo.bmp"
