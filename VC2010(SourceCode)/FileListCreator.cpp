
// FileListCreator.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
#include "FileListCreator.h"
#include "FileListCreatorDlg.h"

#include "FileSpecsDlg.h"

#include "HTML_Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFileListCreatorApp

BEGIN_MESSAGE_MAP(CFileListCreatorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()



// CFileListCreatorApp コンストラクション

CFileListCreatorApp::CFileListCreatorApp()
{
	// 再起動マネージャーをサポートします
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}



// 唯一の CFileListCreatorApp オブジェクトです。

CFileListCreatorApp theApp;


// CFileListCreatorApp 初期化

BOOL CFileListCreatorApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ダイアログにシェル ツリー ビューまたはシェル リスト ビュー コントロールが
	// 含まれている場合にシェル マネージャーを作成します。
	CShellManager *pShellManager = new CShellManager;

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));

	CFileListCreatorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	//dlg.g_NoDrawFLG = FALSE;

	////▼2011.05.21追加▼
	//if (m_lpCmdLine[0] == _T('\0')){
	//   // Create a new (empty) document.
	//   //OnFileNew();
	//}else{
	//   // Open a file passed as the first command line parameter.
	//   //OpenDocumentFile(m_lpCmdLine);
	//	//dlg.ListInit();
	//	dlg.PackageSearch_Func(m_lpCmdLine,_T("*.*"));
	//	//CString str_lpCmdLine;
	//	//str_lpCmdLine = m_lpCmdLine;
	//	//MessageBox (str_lpCmdLine);
	//}
	////▲2011.05.21追加▲

	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//  記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <キャンセル> で消された時のコードを
		//  記述してください。
	}

	// 上で作成されたシェル マネージャーを削除します。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}
	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	//  アプリケーションを終了するために FALSE を返してください。

	
	//CFileListCreatorDlg::PrevProc = NULL;

	return FALSE;
}

//==============================================================
//http://www007.upp.so-net.ne.jp/hama_d/newapi/chapters/c1.html