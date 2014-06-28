// FileSpecsDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "FileListCreator.h"

#include "FileListCreatorDlg.h"

#include <ctype.h>//追加
#include "afxwin.h"//追加

#include "FileSpecsDlg.h"
#include "afxdialogex.h"

#include <locale.h> //追加//_wsetlocale(LC_ALL, _T("jpn"));を使うため 

//using namespace ?????

// CFileSpecsDlg ダイアログ

IMPLEMENT_DYNAMIC(CFileSpecsDlg, CDialogEx)

CFileSpecsDlg::CFileSpecsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileSpecsDlg::IDD, pParent)
{

}

CFileSpecsDlg::~CFileSpecsDlg()
{
}

void CFileSpecsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FileSpec, m_xcCombo_FileSpec);
}


BEGIN_MESSAGE_MAP(CFileSpecsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Default, &CFileSpecsDlg::OnBnClickedButtonDefault)
	ON_BN_CLICKED(IDOK, &CFileSpecsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_FileSpec_Audio, &CFileSpecsDlg::OnBnClickedButtonFilespecAudio)
	ON_BN_CLICKED(IDC_BUTTON_FileSpec_Movie, &CFileSpecsDlg::OnBnClickedButtonFilespecMovie)
	ON_BN_CLICKED(IDC_BUTTON_FileSpec_Image, &CFileSpecsDlg::OnBnClickedButtonFilespecImage)
	ON_BN_CLICKED(IDC_BUTTON_FileSpec_Document, &CFileSpecsDlg::OnBnClickedButtonFilespecDocument)
	ON_BN_CLICKED(IDC_BUTTON_FileSpec_ZIP, &CFileSpecsDlg::OnBnClickedButtonFilespecZip)
	ON_BN_CLICKED(IDC_BUTTON_FileSpec_HTML, &CFileSpecsDlg::OnBnClickedButtonFilespecHtml)
	ON_BN_CLICKED(IDC_BUTTON_FileSpec_TXT, &CFileSpecsDlg::OnBnClickedButtonFilespecTxt)
	ON_BN_CLICKED(IDC_BUTTON_FileSpec_PlayLIST, &CFileSpecsDlg::OnBnClickedButtonFilespecPlaylist)
	ON_BN_CLICKED(IDC_BUTTON_FileSpec_ALL, &CFileSpecsDlg::OnBnClickedButtonFilespecAll)
	ON_BN_CLICKED(IDCANCEL, &CFileSpecsDlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_BTN_SPECCLEAR, &CFileSpecsDlg::OnBnClickedBtnSpecclear)
END_MESSAGE_MAP()


BOOL CFileSpecsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
   //CDialog::OnInitDialog();

	ReadOrWriteComboData_Func(_T("read"));

	CString tempSpecs;

	CFileSpecsDlg::m_xcCombo_FileSpec.GetWindowText(tempSpecs);

	if (tempSpecs==_T("")){ //追加 2012.06.14
		UpdateData(TRUE);
		EditFileSpecs = _T("*.mp3;*.wav;*.m4a;*.mpg;*.mpeg;*.asf;*.avi;*.wmv;*.wma;*.zip;*.html;");

		CFileSpecsDlg::m_xcCombo_FileSpec.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(EditFileSpecs)));
		TargetFileSpecs = EditFileSpecs;
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CFileSpecsDlg::setFileSpecsFunc(CString targetFileSpec, BOOL addFlg)
{
 
	//UpdateData(TRUE);

    ((CComboBox*)GetDlgItem(IDC_COMBO_FileSpec))->GetWindowText(EditFileSpecs);

	if(EditFileSpecs.Find(targetFileSpec) >= 0 && addFlg == FALSE){
		EditFileSpecs.Replace(targetFileSpec, _T(""));
	}else if(EditFileSpecs.Find(targetFileSpec) < 0 && addFlg == TRUE){
		EditFileSpecs = EditFileSpecs + targetFileSpec;
	}
	
	CFileSpecsDlg::m_xcCombo_FileSpec.SetWindowText(EditFileSpecs);
	UpdateData(FALSE);
}

void CFileSpecsDlg::ExistCheckFunc()
{
	BOOL tempFLG = TRUE;
	CString EditFileSpecs2 = _T("");
	//ReadOrWriteComboData_Func(0);
	CFileSpecsDlg::m_xcCombo_FileSpec.GetWindowText(EditFileSpecs2);


	if(EditFileSpecs2 !=_T("")){
		int k = 0;
	
		int k2 = 0;

		while (k <= CFileSpecsDlg::m_xcCombo_FileSpec.GetCount() -1){
			CString ComboText;
			CFileSpecsDlg::m_xcCombo_FileSpec.GetLBText(k, ComboText); // インデックスk番目の文字列を取得

			if(ComboText == EditFileSpecs2){
				CFileSpecsDlg::m_xcCombo_FileSpec.SetCurSel(k);
				k2 = k;
				tempFLG = FALSE;
			}
			k++;
		}


		//if(CFileSpecsDlg::m_xcCombo_FileSpec.GetCount()<=ComboBox_MAX){
			//文字列を挿入する

			if(tempFLG == TRUE){
				CFileSpecsDlg::m_xcCombo_FileSpec.InsertString(0,EditFileSpecs2);
				CFileSpecsDlg::m_xcCombo_FileSpec.SetCurSel(0);
				//MessageBox(EditFileSpecs);
			}else{
				CFileSpecsDlg::m_xcCombo_FileSpec.DeleteString(k2);
				CFileSpecsDlg::m_xcCombo_FileSpec.InsertString(0,EditFileSpecs2);
				CFileSpecsDlg::m_xcCombo_FileSpec.SetCurSel(0);
			}
		//}
		//MessageBox(EditFileSpecs);

		//ComboBox_MAX件以上は登録しない
		//if(CFileSpecsDlg::m_xcCombo_FileSpec.GetCount()>=1){
			for(k = CFileSpecsDlg::m_xcCombo_FileSpec.GetCount();k>=ComboBox_MAX;k--){
				CFileSpecsDlg::m_xcCombo_FileSpec.DeleteString(k);
			}
			//Sleep(300);
		//}
	}
	//return tempFLG;
}
// CFileSpecsDlg メッセージ ハンドラー

void CFileSpecsDlg::OnBnClickedButtonDefault()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	UpdateData(TRUE);
	EditFileSpecs = _T("*.mp3;*.wav;*.m4a;*.mpg;*.mpeg;*.asf;*.avi;*.wmv;*.wma;*.zip;*.html;");

	CFileSpecsDlg::m_xcCombo_FileSpec.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(EditFileSpecs)));
	TargetFileSpecs = EditFileSpecs;

	//Office2007_FileTypes == "Not_Selected";

	UpdateData(FALSE);
}

//CString TargetFileSpecs;

void CFileSpecsDlg::ReadOrWriteComboData_Func(CString mySwitch)
{

	CString FileSpec;

	if (mySwitch == _T("write")){ //write
		int k;

		k = 0;

		FileSpec = _T("");

		while (k <= CFileSpecsDlg::m_xcCombo_FileSpec.GetCount() -1){
			CString ComboText;
			CFileSpecsDlg::m_xcCombo_FileSpec.GetLBText(k, ComboText); // インデックス0番目の文字列を取得
			if(k<=ComboBox_MAX){
				FileSpec = FileSpec + ComboText + _T("\n");

//Windowsのテキストモードでは、ファイルに出力するときに、「\n」が「\r\n」に自動的に変換されます。
//また、ファイルから入力するときは、「\r\n」が「\n」に自動的に変換されます。ですので、
//テキストモードのファイル入出力を使うときは、プログラム上では改行コードは「\n」で扱わなければいけません。
			}
			k++;
		}
	}

	CStdioFile    stdFile;
	CString       wstr, rstr;
	LPTSTR        rstrBuf = NULL;
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

		//// フルパスを分解
		//TCHAR szDir[_MAX_DIR];
		//TCHAR szDrive[_MAX_DRIVE];
		//TCHAR szFName[_MAX_FNAME];
		//TCHAR szExt[_MAX_EXT];
		//_splitpath(szPath,szDrive,szDir,szFName,szExt);
		//
		//// フォルダ、ファイル名取得
		//TCHAR szFilePath[_MAX_PATH];
		//TCHAR szFileName[_MAX_PATH];
		//sprintf(szFilePath,"%s%s",szDrive,szDir);
		//sprintf(szFileName,"%s%s",szFName,szExt);

		CString CurDir;
		CurDir = szPath;

		CFileListCreatorDlg CFileListCreatorDlg_CLASS;
		CurDir = CFileListCreatorDlg_CLASS.CurrentDirFunc(CurDir,TRUE);

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
			if (!stdFile.Open(CurDir + _T("\\FileSpecs.dat"), 
				CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::modeNoTruncate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText
		}
		if (mySwitch == _T("write")){
			if (!stdFile.Open(CurDir + _T("\\FileSpecs.dat"), 
				CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText
		}
	}

	if(mySwitch == _T("write")){ //write
		// (2)書き込み
		if (!err)
		{
			wstr = FileSpec;

			TRY {stdFile.WriteString(wstr);}
			CATCH (CFileException, eP) {err = 1;}
			END_CATCH
		}
	}
	if(mySwitch == _T("read")){ //read
		int k;
		k = 0;
		while (!err) {
			if (stdFile.ReadString(rstr) == FALSE) err = 1;
			if (rstr!=_T("")&&(k<ComboBox_MAX)){
				CFileSpecsDlg::m_xcCombo_FileSpec.InsertString(k,rstr);
			}

			k++;
		}
		CFileSpecsDlg::m_xcCombo_FileSpec.SetCurSel(0);
	}

	// (6)クローズ(明示的)
	stdFile.Close();

}

void CFileSpecsDlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnOK();

	TargetFileSpecs = _T("");

    CString strFileSpecs;
    ((CComboBox*)GetDlgItem(IDC_COMBO_FileSpec))->GetWindowText(strFileSpecs);

    if((strFileSpecs) == _T("")){
		int myResult;

		myResult = MessageBox(_T("検索対象となる拡張子を1つ以上入れてください \r\n (すべてのファイルを対象にしますか？)") ,_T(""), MB_YESNO );
		if (myResult == IDYES){
			UpdateData(TRUE);
			m_xcCombo_FileSpec.AddString(_T("*.*;"));
			strFileSpecs = _T("*.*;");
			m_xcCombo_FileSpec.SetCurSel(0);
			UpdateData(FALSE);
		}else{
			UpdateData(TRUE);
			m_xcCombo_FileSpec.AddString(_T("Operation was canceled by the user."));
			strFileSpecs = _T("");
			m_xcCombo_FileSpec.SetCurSel(0);
			//TargetFileSpecs == _T("Operation was canceled by the user.");
			UpdateData(FALSE);
        }
	}

	if (strFileSpecs.Find(_T("*.*")) >= 0 && strFileSpecs.GetLength() > 4 ){
		int myResult;
		myResult = MessageBox(_T("全てのファイルを意味する「*.*;」を指定した場合、重複を避けるため、その他の拡張子を削除しますか？（推奨：はい）") ,_T("警告"), MB_YESNOCANCEL );

		if (IDYES == myResult){
			UpdateData(TRUE);
			//m_xcCombo_FileSpec.AddString(_T("*.*;"));
			strFileSpecs = _T("*.*;");
			//m_xcCombo_FileSpec.SetCurSel(0);
			UpdateData(FALSE);
		}
	}
    CString strBuff2;
    LONG k;

    k = 0; //VBA：1 → VC：0に添え字変更
    strBuff2 = _T("");


    CString fixFileSpecs;
    
    fixFileSpecs = _T("");
    //TRACE("1111 %s",strFileSpecs);
	
    while (k <= strFileSpecs.GetLength()-1 ){
        if (strFileSpecs.Mid(k,1) == _T(";"))  {
			//if (strBuff2 !=_T("") && k>=2 ){
				if(strBuff2.Find(_T('*')) == 0 && strBuff2.Find(_T('.')) == 1){
				}else{
					strBuff2 = _T("*.") + strBuff2;
				}
			//}
			fixFileSpecs = fixFileSpecs + strBuff2 + _T(";");

            strBuff2 = "";
        }else{
            strBuff2 = strBuff2 + strFileSpecs.Mid(k,1);
		}
        k = k + 1;
	}
	
	//MessageBox(fixFileSpecs);

	if(fixFileSpecs == _T("")){
		fixFileSpecs = _T("<<error>>");
	}

	TargetFileSpecs = fixFileSpecs;
	CFileSpecsDlg::m_xcCombo_FileSpec.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(fixFileSpecs)));
	
	CFileSpecsDlg::ExistCheckFunc();


	//fixFileSpecs.Replace(_T("*"),_T("*"));

    if (fixFileSpecs != _T("") && fixFileSpecs != _T("*.*;") && fixFileSpecs != _T("<<error>>")){
		CFileSpecsDlg::ReadOrWriteComboData_Func(_T("write"));
	}
}


void CFileSpecsDlg::OnBnClickedButtonFilespecAudio()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	static BOOL Audio_AddFLG = TRUE;

    CFileSpecsDlg::setFileSpecsFunc(_T("*.mp3;"), Audio_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.wav;"), Audio_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.wma;"), Audio_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.m4a;"), Audio_AddFLG);

// aac [ Advanced Audio Coding ]

    CFileSpecsDlg::setFileSpecsFunc(_T("*.aac;"), Audio_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.mp4;"), Audio_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.m4p;"), Audio_AddFLG);

	//CFileSpecsDlg::ExistCheckFunc();

	Audio_AddFLG = !Audio_AddFLG;
}


void CFileSpecsDlg::OnBnClickedButtonFilespecMovie()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	static BOOL Movie_AddFLG = TRUE;

    CFileSpecsDlg::setFileSpecsFunc(_T("*.mpg;"), Movie_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.mpeg;"), Movie_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.asf;"), Movie_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.avi;"), Movie_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.mov;"), Movie_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.wmv;"), Movie_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.flv;"), Movie_AddFLG);

	//CFileSpecsDlg::ExistCheckFunc();

	Movie_AddFLG = !Movie_AddFLG;
}


void CFileSpecsDlg::OnBnClickedButtonFilespecImage()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	static BOOL Image_AddFLG = TRUE;

    CFileSpecsDlg::setFileSpecsFunc(_T("*.jpg;"), Image_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.jpeg;"), Image_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.gif;"), Image_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.png;"), Image_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.bmp;"), Image_AddFLG);


	//CFileSpecsDlg::ExistCheckFunc();

	Image_AddFLG = !Image_AddFLG;
}


void CFileSpecsDlg::OnBnClickedButtonFilespecDocument()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	static BOOL Document_AddFLG = TRUE;
	//static CString Office2007_FileTypes = _T("Not_Selected");

	static CString Office2007_FileTypes = _T("Not_Selected");

    if (Office2007_FileTypes == _T("Not_Selected")){
		int myResult;
        myResult = MessageBox(_T("オフィス２００７の拡張子(20個)も対象にしますか？") ,_T("Do you add extension of office2007 ?"), MB_YESNOCANCEL );

        if (IDYES == myResult){
            Office2007_FileTypes = "Office2007_ON";
		}else if(IDNO == myResult){
            Office2007_FileTypes = "Office2007_OFF";
		}
	}

	CFileSpecsDlg::setFileSpecsFunc(_T("*.xls;"), Document_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.doc;"), Document_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.wri;"), Document_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.ppt;"), Document_AddFLG);
	CFileSpecsDlg::setFileSpecsFunc(_T("*.mdb;"), Document_AddFLG);


    if (Office2007_FileTypes == "Office2007_ON" ){
		CFileSpecsDlg::setFileSpecsFunc(_T("*.docx;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.docm;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.dotx;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.dotm;"), Document_AddFLG);

		CFileSpecsDlg::setFileSpecsFunc(_T("*.pptx;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.pptm;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.potx;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.potm;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.ppsx;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.ppsm;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.ppam;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.sldx;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.sldm;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.thmx;"), Document_AddFLG);

		CFileSpecsDlg::setFileSpecsFunc(_T("*.xlsb;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.xlsx;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.xlsm;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.xltx;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.xltm;"), Document_AddFLG);
		CFileSpecsDlg::setFileSpecsFunc(_T("*.xlam;"), Document_AddFLG);
    
	}
    
	//CFileSpecsDlg::ExistCheckFunc();

    Document_AddFLG = !Document_AddFLG;
}


void CFileSpecsDlg::OnBnClickedButtonFilespecZip()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	static BOOL Zip_AddFLG = TRUE;

    CFileSpecsDlg::setFileSpecsFunc(_T("*.zip;"),Zip_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.lzh;"), Zip_AddFLG);

	//CFileSpecsDlg::ExistCheckFunc();

	Zip_AddFLG = !Zip_AddFLG;
}


void CFileSpecsDlg::OnBnClickedButtonFilespecHtml()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	static BOOL HTML_AddFLG = TRUE;

    CFileSpecsDlg::setFileSpecsFunc(_T("*.htm;"), HTML_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.html;"), HTML_AddFLG);

	//CFileSpecsDlg::ExistCheckFunc();

	HTML_AddFLG = !HTML_AddFLG;
}


void CFileSpecsDlg::OnBnClickedButtonFilespecTxt()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	static BOOL TXT_AddFLG = TRUE;

    CFileSpecsDlg::setFileSpecsFunc(_T("*.txt;"), TXT_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.text;"), TXT_AddFLG);

	//CFileSpecsDlg::ExistCheckFunc();

	TXT_AddFLG = !TXT_AddFLG;
}


void CFileSpecsDlg::OnBnClickedButtonFilespecPlaylist()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	static BOOL Play_LIST_AddFLG = TRUE;

    CFileSpecsDlg::setFileSpecsFunc(_T("*.m3u;"), Play_LIST_AddFLG);
    CFileSpecsDlg::setFileSpecsFunc(_T("*.wpl;"), Play_LIST_AddFLG);

	//CFileSpecsDlg::ExistCheckFunc();

	Play_LIST_AddFLG = !Play_LIST_AddFLG;
}


void CFileSpecsDlg::OnBnClickedButtonFilespecAll()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	UpdateData(TRUE);

	CFileSpecsDlg::m_xcCombo_FileSpec.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("*.*;"))));
	TargetFileSpecs = _T("*.*;");
	UpdateData(FALSE);
}


void CFileSpecsDlg::OnBnClickedCancel()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CFileSpecsDlg::m_xcCombo_FileSpec.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("")))); //追加 2012.06.14
	TargetFileSpecs = _T("");

	CDialogEx::OnCancel();
}

void CFileSpecsDlg::OnBnClickedBtnSpecclear()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	//int myResult;
 //   myResult = MessageBox(_T("テキストボックス内の文字を削除しますか？") ,_T("DELETE CONFIRM"), MB_YESNOCANCEL );

 //   if (IDYES == myResult){
		CFileSpecsDlg::m_xcCombo_FileSpec.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(_T(""))));
		TargetFileSpecs = _T("");
	//}else if(IDNO == myResult){
	//}
}

