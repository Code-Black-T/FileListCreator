// InputBoxDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "FileListCreator.h"

//追加▼
#include "FileListCreatorDlg.h"
//追加▲

#include "InputBoxDlg.h"
#include "afxdialogex.h"


// InputBoxDlg ダイアログ

IMPLEMENT_DYNAMIC(InputBoxDlg, CDialogEx)

InputBoxDlg::InputBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(InputBoxDlg::IDD, pParent)
{

}

InputBoxDlg::~InputBoxDlg()
{
}

void InputBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_InputFileName, m_xcCombo_InputFileName);
	DDX_Control(pDX, IDC_COMBO_For_X, m_xcCombo_For_X);
}


BEGIN_MESSAGE_MAP(InputBoxDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &InputBoxDlg::OnBnClickedOk)
	ON_BN_CLICKED(ID_BTN_FILENAME_CLEAR, &InputBoxDlg::OnBnClickedBtnFilenameClear)
	ON_BN_CLICKED(ID_BTN_AlbumList, &InputBoxDlg::OnBnClickedBtnAlbumlist)
	ON_BN_CLICKED(ID_BTN_SingleList, &InputBoxDlg::OnBnClickedBtnSinglelist)
	ON_BN_CLICKED(ID_BTN_today, &InputBoxDlg::OnBnClickedBtntoday)
	ON_BN_CLICKED(ID_BTN_LastImportName, &InputBoxDlg::OnBnClickedBtnLastimportname)
	ON_CBN_SELCHANGE(IDC_COMBO_For_X, &InputBoxDlg::OnCbnSelchangeComboForX)
END_MESSAGE_MAP()


// InputBoxDlg メッセージ ハンドラー

BOOL InputBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return FALSE;
	}


	InputBoxDlg::m_xcCombo_For_X.Clear();

	InputBoxDlg::m_xcCombo_For_X.InsertString(-1,_T(" [DEL] "));

	TCHAR c = _T('A'); //追加 2012.12.01

    while (c <= _T('Z')){
		CString tempStr;

		tempStr = c;

		InputBoxDlg::m_xcCombo_For_X.InsertString(-1,_T("_For_") + tempStr);
		c++;
	}

	ReadOrWriteComboData_Func(_T("read"));

	KeepTime = m_Dlg->CreateDateTime(1);

	//int index = -1;

	//while ((index = m_Dlg->m_xcList.GetNextItem
	//		(index, LVNI_ALL | LVNI_SELECTED)) != -1){
		CString FileNameStr;
		FileNameStr = _T("LIST_")+ KeepTime;

		KeepFileNameStr = FileNameStr; //追加 2012.12.01

		m_xcCombo_InputFileName.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(FileNameStr)));
	//	break;
	//}

	ExportFileName = _T("");

	return TRUE;
}

void InputBoxDlg::ExistCheckFunc(CString mySwitch)
{
	if (mySwitch==_T("InputFileName")){
		BOOL tempFLG = TRUE;
		CString EditData = _T("");
		InputBoxDlg::m_xcCombo_InputFileName.GetWindowText(EditData);

		//if(EditData !=_T("")){
			int k = 0;
	
			int k2 = 0;

			while (k <= InputBoxDlg::m_xcCombo_InputFileName.GetCount() -1){
				CString ComboText;
				InputBoxDlg::m_xcCombo_InputFileName.GetLBText(k, ComboText); // インデックスk番目の文字列を取得

				if(ComboText == EditData){
					InputBoxDlg::m_xcCombo_InputFileName.SetCurSel(k);
					k2 = k;
					tempFLG = FALSE;
				}
				k++;
			}

			if(tempFLG == TRUE){
				InputBoxDlg::m_xcCombo_InputFileName.InsertString(0,EditData);
				InputBoxDlg::m_xcCombo_InputFileName.SetCurSel(0);
			}else{
				InputBoxDlg::m_xcCombo_InputFileName.DeleteString(k2);
				InputBoxDlg::m_xcCombo_InputFileName.InsertString(0,EditData);
				InputBoxDlg::m_xcCombo_InputFileName.SetCurSel(0);
			}

			for(k = InputBoxDlg::m_xcCombo_InputFileName.GetCount();k>=ComboBox_MAX;k--){
				InputBoxDlg::m_xcCombo_InputFileName.DeleteString(k);
			}
		//}
	}
}

void InputBoxDlg::ReadOrWriteComboData_Func(CString mySwitch)
{
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	CString WriteData1;

	if (mySwitch == _T("write")){ //write
		int k;

		k = 0;
		WriteData1 = _T("");

		while (k <= InputBoxDlg::m_xcCombo_InputFileName.GetCount() -1){
			CString ComboText;
			InputBoxDlg::m_xcCombo_InputFileName.GetLBText(k, ComboText); // インデックス0番目の文字列を取得
			if(k<=ComboBox_MAX){
				WriteData1 = WriteData1 + ComboText + _T("\n");
			}
			k++;
		}
	}

	CString       wstr, rstr;
	int           err = 0;

	// (1)読み書き用にオープン
	if (!err)
	{
		//// カレントディレクトリの取得
		//TCHAR szCurrentDir[_MAX_PATH];
		//GetCurrentDirectory(_MAX_PATH,szCurrentDir);
	
		//CString CurDir;
		//CurDir = szCurrentDir;

		//http://rararahp.cool.ne.jp/vc/vctips/api.htm
		// 実行ファイルのフルパス取得
		TCHAR szPath[_MAX_PATH];
		GetModuleFileName( NULL, szPath, MAX_PATH);

		CString CurDir;
		CurDir = szPath;

		//CFileListCreatorDlg CFileListCreatorDlg_CLASS;
		CurDir = m_Dlg->CurrentDirFunc(CurDir,TRUE);

		if(CurDir!=_T("")){
			CurDir.Replace(_T("\\"),_T("\\\\"));
		}
		CurDir = CurDir + _T("\\FileListCreator(Pref)");
		if(CreateDirectory(CurDir,NULL)){

		}
		else {
			
		}
		//http://www.g-ishihara.com/mfc_fi_01.htm
		if (mySwitch == _T("read")){

			if ( PathFileExists( CurDir + _T("\\InputFileName.dat") ) ){ //追加 2012.06.15

				FILE *fp;
				_tfopen_s(&fp,CurDir + _T("\\InputFileName.dat"), _T("r, ccs=UNICODE"));
				CStdioFile stdFile1(fp);

				err = 0;
				int k;
				k = 0;
				while (!err) {
					if (stdFile1.ReadString(rstr) == FALSE) err = 1;
					if (rstr!=_T("")&&(k<ComboBox_MAX)){
						InputBoxDlg::m_xcCombo_InputFileName.InsertString(k,rstr);
					}

					k++;
				}
				InputBoxDlg::m_xcCombo_InputFileName.SetCurSel(0);

				// (6)クローズ(明示的)
				stdFile1.Close();
				fclose(fp);
			}

		}
		if (mySwitch == _T("write")){
			FILE *fp;
			_tfopen_s(&fp,CurDir + _T("\\InputFileName.dat"), L"w,ccs=UNICODE");
			fputws(WriteData1, fp);
			fclose(fp);
		}
	}

}


void InputBoxDlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnOK();

	//CString EditData;
	InputBoxDlg::m_xcCombo_InputFileName.GetWindowText(ExportFileName);

	ExistCheckFunc(_T("InputFileName"));
	ReadOrWriteComboData_Func(_T("write"));


}


void InputBoxDlg::OnBnClickedBtnFilenameClear()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	m_xcCombo_InputFileName.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(_T(""))));
}


void InputBoxDlg::OnBnClickedBtnAlbumlist()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	CString EditData = _T("");
	InputBoxDlg::m_xcCombo_InputFileName.GetWindowText(EditData);

	CString KeepData = EditData;

	if(EditData == KeepFileNameStr) EditData = _T(""); //追加 2012.12.01

	static int AlbumSwitch=1;

	switch(AlbumSwitch){
		case 1:
			EditData.Replace(_T("_AlbumList"),_T(""));
			EditData.Replace(_T("AlbumList_"),_T(""));
			EditData.Replace(_T("AlbumList"),_T(""));

			EditData.Replace(_T("_SingleList"),_T(""));
			EditData.Replace(_T("SingleList_"),_T(""));
			EditData.Replace(_T("SingleList"),_T(""));

			if(EditData.Right(1)!=_T("_") && EditData!=_T("")){
				EditData = EditData + _T("_AlbumList");
			}else{
				EditData = EditData + _T("AlbumList");
			}
			if(KeepData != EditData) break;
		case 2:
			AlbumSwitch = 2;
			EditData.Replace(_T("_AlbumList"),_T(""));
			EditData.Replace(_T("AlbumList_"),_T(""));
			EditData.Replace(_T("AlbumList"),_T(""));

			EditData.Replace(_T("_SingleList"),_T(""));
			EditData.Replace(_T("SingleList_"),_T(""));
			EditData.Replace(_T("SingleList"),_T(""));

			if(EditData.Left(1)!=_T("_") && EditData!=_T("")){
				EditData = _T("AlbumList_") + EditData;
			}else{
				EditData = _T("AlbumList") + EditData;
			}
			if(KeepData != EditData) break;
		case 3:
			AlbumSwitch = 3;
			EditData.Replace(_T("_AlbumList"),_T(""));
			EditData.Replace(_T("AlbumList_"),_T(""));
			EditData.Replace(_T("AlbumList"),_T(""));
			if(KeepData != EditData) break;
		case 4:	
			EditData.Replace(_T("_AlbumList"),_T(""));
			EditData.Replace(_T("AlbumList_"),_T(""));
			EditData.Replace(_T("AlbumList"),_T(""));

			EditData.Replace(_T("_SingleList"),_T(""));
			EditData.Replace(_T("SingleList_"),_T(""));
			EditData.Replace(_T("SingleList"),_T(""));

			if(EditData.Right(1)!=_T("_") && EditData!=_T("")){
				EditData = EditData + _T("_AlbumList");
			}else{
				EditData = EditData + _T("AlbumList");
			}
			break;
		default:
			MessageBox(_T("不正な列です。"));
			break;
	}

	m_xcCombo_InputFileName.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(EditData)));

	AlbumSwitch++;
	if (AlbumSwitch==4){
		AlbumSwitch=1;
	}
}


void InputBoxDlg::OnBnClickedBtnSinglelist()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CString EditData = _T("");
	InputBoxDlg::m_xcCombo_InputFileName.GetWindowText(EditData);

	CString KeepData = EditData;

	if(EditData == KeepFileNameStr) EditData = _T(""); //追加 2012.12.01

	static int SingleSwitch=1;

	switch(SingleSwitch){
		case 1:
			EditData.Replace(_T("_AlbumList"),_T(""));
			EditData.Replace(_T("AlbumList_"),_T(""));
			EditData.Replace(_T("AlbumList"),_T(""));

			EditData.Replace(_T("_SingleList"),_T(""));
			EditData.Replace(_T("SingleList_"),_T(""));
			EditData.Replace(_T("SingleList"),_T(""));

			if(EditData.Right(1)!=_T("_") && EditData!=_T("")){
				EditData = EditData + _T("_SingleList");
			}else{
				EditData = EditData + _T("SingleList");
			}
			if(KeepData != EditData) break;
		case 2:
			SingleSwitch = 2;

			EditData.Replace(_T("_AlbumList"),_T(""));
			EditData.Replace(_T("AlbumList_"),_T(""));
			EditData.Replace(_T("AlbumList"),_T(""));

			EditData.Replace(_T("_SingleList"),_T(""));
			EditData.Replace(_T("SingleList_"),_T(""));
			EditData.Replace(_T("SingleList"),_T(""));

			if(EditData.Left(1)!=_T("_") && EditData!=_T("")){
				EditData = _T("SingleList_") + EditData;
			}else{
				EditData = _T("SingleList") + EditData;
			}
			if(KeepData != EditData) break;
		case 3:
			SingleSwitch = 3;

			EditData.Replace(_T("_SingleList"),_T(""));
			EditData.Replace(_T("SingleList_"),_T(""));
			EditData.Replace(_T("SingleList"),_T(""));
			if(KeepData != EditData) break;
		case 4:
			EditData.Replace(_T("_AlbumList"),_T(""));
			EditData.Replace(_T("AlbumList_"),_T(""));
			EditData.Replace(_T("AlbumList"),_T(""));

			EditData.Replace(_T("_SingleList"),_T(""));
			EditData.Replace(_T("SingleList_"),_T(""));
			EditData.Replace(_T("SingleList"),_T(""));

			if(EditData.Right(1)!=_T("_") && EditData!=_T("")){
				EditData = EditData + _T("_SingleList");
			}else{
				EditData = EditData + _T("SingleList");
			}
			break;
		default:
			MessageBox(_T("不正な列です。"));
			break;
	}

	m_xcCombo_InputFileName.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(EditData)));

	SingleSwitch++;
	if (SingleSwitch==4){
		SingleSwitch=1;
	}
}


void InputBoxDlg::OnBnClickedBtntoday()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CString EditData;
	InputBoxDlg::m_xcCombo_InputFileName.GetWindowText(EditData);

	CString KeepData = EditData;

	if(EditData == KeepFileNameStr) EditData = _T(""); //追加 2012.12.01

	static int KeepTimeSwitch=1;

	switch(KeepTimeSwitch){
		case 1:
			EditData.Replace(_T("_") + KeepTime,_T(""));
			EditData.Replace(KeepTime + _T("_"),_T(""));
			EditData.Replace(KeepTime,_T(""));

			if(EditData.Right(1)!=_T("_") && EditData!=_T("")){
				EditData = EditData + _T("_") + KeepTime;
			}else{
				EditData = EditData + KeepTime;
			}
			if(KeepData != EditData) break;
		case 2:
			KeepTimeSwitch = 2;
			EditData.Replace(_T("_") + KeepTime,_T(""));
			EditData.Replace(KeepTime + _T("_"),_T(""));
			EditData.Replace(KeepTime,_T(""));

			if(EditData.Left(1)!=_T("_") && EditData!=_T("")){
				EditData =  KeepTime + _T("_") + EditData;
			}else{
				EditData =  KeepTime + EditData;
			}
			if(KeepData != EditData) break;
		case 3:
			KeepTimeSwitch = 3;
			EditData.Replace(_T("_") + KeepTime,_T(""));
			EditData.Replace(KeepTime + _T("_"),_T(""));
			EditData.Replace(KeepTime,_T(""));
			if(KeepData != EditData) break;
		case 4:
			EditData.Replace(_T("_") + KeepTime,_T(""));
			EditData.Replace(KeepTime + _T("_"),_T(""));
			EditData.Replace(KeepTime,_T(""));

			if(EditData.Right(1)!=_T("_") && EditData!=_T("")){
				EditData = EditData + _T("_") + KeepTime;
			}else{
				EditData = EditData + KeepTime;
			}
			break;
		default:
			MessageBox(_T("不正な列です。"));
			break;
	}

	m_xcCombo_InputFileName.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(EditData)));

	KeepTimeSwitch++;
	if (KeepTimeSwitch==4){
		KeepTimeSwitch=1;
	}
}


void InputBoxDlg::OnBnClickedBtnLastimportname()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->LastImportFileName = m_Dlg->FullPathToFileName(m_Dlg->LastImportFileName);

	if(m_Dlg->LastImportFileName == _T("")){
		MessageBox(_T("起動してから１つもリストファイルが読み込まれていません。\r\n（最後にインポートしたファイル名を挿入することができます）") ,_T("インポート未実行"), MB_OK );
	}else{
		// TODO: ここにコントロール通知ハンドラー コードを追加します。
		CString EditData = _T("");
		InputBoxDlg::m_xcCombo_InputFileName.GetWindowText(EditData);

		CString EditData2 = _T("");

		EditData2 = m_Dlg->LastImportFileName;
		EditData2.Replace(_T(".html"),_T(""));
		//EditData2.Replace(_T(".htm"),_T(""));

		if(EditData.Find(EditData2,0)>=0){
			//EditData.Replace(EditData2,_T(""));
			EditData = _T(""); //追加 2012.12.01
		}else{
			EditData = EditData2;
		}
		m_xcCombo_InputFileName.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(EditData)));
	}
}


void InputBoxDlg::OnCbnSelchangeComboForX() //追加 2012.12.01
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CString	EditData;
	InputBoxDlg::m_xcCombo_InputFileName.GetWindowText(EditData);

	CString addData;
	InputBoxDlg::m_xcCombo_For_X.GetWindowText(addData);

	BOOL existFLG = FALSE;

	CString Ptn;

	Ptn = _T("_For_?");
	existFLG = InputBoxDlg::StrMatchMBS(Ptn.MakeLower(),EditData.Right(Ptn.GetLength()).MakeLower());
	if (existFLG == TRUE) EditData = EditData.Left(EditData.GetLength()-Ptn.GetLength());
	m_xcCombo_InputFileName.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(EditData + addData)));

	Ptn = _T("For_?_");
	existFLG = InputBoxDlg::StrMatchMBS(Ptn.MakeLower(),EditData.Left(Ptn.GetLength()).MakeLower());
	if (existFLG == TRUE) EditData = EditData.Right(EditData.GetLength()-Ptn.GetLength());
	m_xcCombo_InputFileName.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(EditData + addData)));

	if (addData == _T(" [DEL] ")){
		addData = _T("");
		m_xcCombo_InputFileName.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(EditData + addData)));
	}
	
}

int InputBoxDlg::StrMatchMBS( const TCHAR *Ptn, const TCHAR *Str ){ //追加 2012.12.01

	//const char *Ptn …ワイルドカード付き文字列
	//const char *Str …検索対象
	//戻り値　…１／０：真／偽

	//_mbsinc()を_tcsinc()に _mbsnextc()を_tcsnextc()に、変更 2011.09.09

	switch( *Ptn )
	{
		case _T('\0'):
			return (_tcsnextc(Str)==_T('\0'));
		case _T('*'):
			return StrMatchMBS( _tcsinc(Ptn), Str ) || (_tcsnextc(Str)!=_T('\0')) && StrMatchMBS( Ptn, _tcsinc(Str) );
		case _T('?'):
			return (_tcsnextc(Str)!=_T('\0')) && StrMatchMBS( _tcsinc(Ptn), _tcsinc(Str) );
		default:
			return (_tcsnextc(Ptn)==_tcsnextc(Str)) && StrMatchMBS( _tcsinc(Ptn), _tcsinc(Str) );
	}
}