
// FileListCreator.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル

// CFileListCreatorApp:
// このクラスの実装については、FileListCreator.cpp を参照してください。
//

class CFileListCreatorApp : public CWinApp
{
public:
	CFileListCreatorApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBtnTest();

	//ULONGLONG DoWithCnt;
	//ULONGLONG TotalItemsCount;
};

extern CFileListCreatorApp theApp;