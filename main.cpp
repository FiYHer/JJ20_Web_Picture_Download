#include "core.hpp"
#include <ShlObj_core.h>
#include <Windowsx.h>
#include "resource.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name = 'Microsoft.Windows.Common-Controls' \
version = '6.0.0.0' \
processorArchitecture = '*' \
publicKeyToken = '6595b64144ccf1df' \
language = '*'\"")

CONST TCHAR* DialogSave()
{
	static TCHAR szBuffer[MAX_PATH] = { 0 };
	BROWSEINFO bi = { 0 };
	bi.hwndOwner = NULL;//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄
	bi.pszDisplayName = szBuffer;//接收文件夹的缓冲区
	bi.lpszTitle = TEXT("选择一个文件夹");//标题
	bi.ulFlags = BIF_NEWDIALOGSTYLE;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	SHGetPathFromIDList(idl, szBuffer);
	return szBuffer;
}

VOID DialogCom(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	int wmId = LOWORD(wParam);
	int wmEvent = HIWORD(wParam);

	static const wchar_t* bit_types[] =
	{
		L"http://www.jj20.com/bz/zrfg/list_1_1.html" ,
		L"http://www.jj20.com/bz/dwxz/list_2_1.html",
		L"http://www.jj20.com/bz/hhzw/list_3_1.html",
		L"http://www.jj20.com/bz/jzfg/list_4_1.html",
		L"http://www.jj20.com/bz/qcjt/list_5_1.html",
		L"http://www.jj20.com/bz/ysbz/list_6_1.html",
		L"http://www.jj20.com/bz/nxxz/list_7_1.html",
		L"http://www.jj20.com/bz/rwtx/list_8_1.html",
		L"http://www.jj20.com/bz/jwxz/list_9_1.html",
		L"http://www.jj20.com/bz/mwjy/list_10_1.html",
		L"http://www.jj20.com/bz/czxt/list_11_1.html",
		L"http://www.jj20.com/bz/sjsh/list_12_1.html",
		L"http://www.jj20.com/bz/ysyx/list_13_1.html",
		L"http://www.jj20.com/bz/tyyd/list_14_1.html",
		L"http://www.jj20.com/bz/ppgg/list_15_1.html",
		L"http://www.jj20.com/bz/ktmh/list_16_1.html",
		L"http://www.jj20.com/bz/shsj/list_17_1.html",
		L"http://www.jj20.com/bz/slkt/list_18_1.html",
		L"http://www.jj20.com/bz/xmsc/list_19_1.html",
		L"http://www.jj20.com/bz/jqqd/list_20_1.html",
		L"http://www.jj20.com/bz/jxbz/list_120_1.html"
	};

	switch (wmId)
	{
	case ID_40001:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[0]);
		break;
	case ID_40002:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[1]);
		break;
	case ID_40003:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[2]);
		break;
	case ID_40004:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[3]);
		break;
	case ID_40005:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[4]);
		break;
	case ID_40006:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[5]);
		break;
	case ID_40007:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[6]);
		break;
	case ID_40008:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[7]);
		break;
	case ID_40009:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[8]);
		break;
	case ID_40010:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[9]);
		break;
	case ID_40011:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[10]);
		break;
	case ID_40012:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[11]);
		break;
	case ID_40013:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[12]);
		break;
	case ID_40014:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[13]);
		break;
	case ID_40015:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[14]);
		break;
	case ID_40016:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[15]);
		break;
	case ID_40017:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[16]);
		break;
	case ID_40018:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[17]);
		break;
	case ID_40019:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[18]);
		break;
	case ID_40020:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[19]);
		break;
	case ID_40021:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT1), bit_types[20]);
		break;

	case ID_40022:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT2), DialogSave());
		break;

	case IDC_BUTTON1:
	{
		char url[300]{ 0 };
		char path[300]{ 0 };

		GetWindowTextA(GetDlgItem(hWnd, IDC_EDIT1), url, 300);
		GetWindowTextA(GetDlgItem(hWnd, IDC_EDIT2), path, 300);
		if (!strlen(url) || !strlen(path)) return;

		start_work(GetDlgItem(hWnd, IDC_EDIT3), url, path);
	}
	break;
	}
}

INT_PTR CALLBACK DialogProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetWindowTextW(GetDlgItem(hWnd, IDC_EDIT2), L"C:\\");
		return 1;
	case WM_COMMAND:
		DialogCom(hWnd, uMsg, wParam, lParam);
		return 1;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 1;
	}

	return 0;
}

int _stdcall WinMain(
	HINSTANCE hInstance,
	HINSTANCE, LPSTR, int)
{
	HWND h = CreateDialogParamA(hInstance, MAKEINTRESOURCEA(IDD_DIALOG1), 0, DialogProc, 0);
	if (h)
	{
		ShowWindow(h, SW_SHOW);
		UpdateWindow(h);

		SendMessage(h, WM_SETICON, FALSE, (LPARAM)LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON1)));

		MSG msg{ 0 };
		while (GetMessageA(&msg, 0, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}

	return 0;
}