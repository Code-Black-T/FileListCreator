// TipsInfo.cpp : 実装ファイル
//

#include "stdafx.h"
#include "FileListCreator.h"
#include "TipsInfo.h"
#include "afxdialogex.h"


// TipsInfo ダイアログ

IMPLEMENT_DYNAMIC(TipsInfo, CDialogEx)

TipsInfo::TipsInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(TipsInfo::IDD, pParent)
{

}

TipsInfo::~TipsInfo()
{
}

void TipsInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TipsInfo, CDialogEx)
END_MESSAGE_MAP()


// TipsInfo メッセージ ハンドラー
