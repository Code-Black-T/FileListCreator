// AllYesOrNoDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "FileListCreator.h"
#include "AllYesOrNoDlg.h"
#include "afxdialogex.h"


// AllYesOrNoDlg ダイアログ

IMPLEMENT_DYNAMIC(AllYesOrNoDlg, CDialogEx)

AllYesOrNoDlg::AllYesOrNoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AllYesOrNoDlg::IDD, pParent)
{

}

AllYesOrNoDlg::~AllYesOrNoDlg()
{
}

void AllYesOrNoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AllYesOrNoDlg, CDialogEx)
END_MESSAGE_MAP()


// AllYesOrNoDlg メッセージ ハンドラー
