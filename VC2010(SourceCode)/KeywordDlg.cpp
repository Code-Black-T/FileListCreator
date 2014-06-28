// KeywordDlg.cpp : 実装ファイル
//

////▼追加
//#include "afxwin.h"
////▲追加

////▼追加
//#include <windows.h>
////▲追加

#include "stdafx.h"
#include "FileListCreator.h"
#include "FileListCreatorDlg.h"//追加

#include "KeywordDlg.h"
#include "afxdialogex.h"



// KeywordDlg ダイアログ

IMPLEMENT_DYNAMIC(KeywordDlg, CDialogEx)

KeywordDlg::KeywordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(KeywordDlg::IDD, pParent)
	, m_xvChkFuzzySearch(TRUE)
	, m_xvChkKeywordFullPath(FALSE)
{

}

KeywordDlg::~KeywordDlg()
{
}

void KeywordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_OK_BOX, m_xcCombo_OK_BOX);
	DDX_Control(pDX, IDC_COMBO_NG_BOX, m_xcCombo_NG_BOX);
	DDX_Check(pDX, IDC_CHECK_FuzzySearch_ON, m_xvChkFuzzySearch);
	DDX_Check(pDX, IDC_CHK_KeywordFullPath, m_xvChkKeywordFullPath);
}


BEGIN_MESSAGE_MAP(KeywordDlg, CDialogEx)
	//ON_BN_CLICKED(ID_BTN_TargetBold, &KeywordDlg::OnBnClickedBtnTargetbold)
	ON_BN_CLICKED(ID_BTN_Asterisk, &KeywordDlg::OnBnClickedBtnAsterisk)
	ON_CBN_EDITCHANGE(IDC_COMBO_OK_BOX, &KeywordDlg::OnCbnEditchangeComboOkBox)
	ON_CBN_KILLFOCUS(IDC_COMBO_OK_BOX, &KeywordDlg::OnCbnKillfocusComboOkBox)
	ON_CBN_SELCHANGE(IDC_COMBO_OK_BOX, &KeywordDlg::OnCbnSelchangeComboOkBox)
	ON_CBN_SETFOCUS(IDC_COMBO_OK_BOX, &KeywordDlg::OnCbnSetfocusComboOkBox)
	ON_CBN_EDITUPDATE(IDC_COMBO_OK_BOX, &KeywordDlg::OnCbnEditupdateComboOkBox)
	ON_WM_LBUTTONDOWN()
	ON_CBN_EDITCHANGE(IDC_COMBO_NG_BOX, &KeywordDlg::OnCbnEditchangeComboNgBox)
	ON_CBN_SETFOCUS(IDC_COMBO_NG_BOX, &KeywordDlg::OnCbnSetfocusComboNgBox)
	ON_CBN_KILLFOCUS(IDC_COMBO_NG_BOX, &KeywordDlg::OnCbnKillfocusComboNgBox)
	ON_BN_CLICKED(ID_BTN_Space, &KeywordDlg::OnBnClickedBtnSpace)
	ON_BN_CLICKED(ID_BTN_QuestionMark, &KeywordDlg::OnBnClickedBtnQuestionmark)
	ON_BN_CLICKED(ID_BTN_PathSeparator, &KeywordDlg::OnBnClickedBtnPathseparator)
	ON_BN_CLICKED(ID_BTN_DoubleQuotationMark, &KeywordDlg::OnBnClickedBtnDoublequotationmark)
	ON_BN_CLICKED(ID_BTN_TargetRed, &KeywordDlg::OnBnClickedBtnTargetred)
	ON_BN_CLICKED(IDC_CHECK_FuzzySearch_ON, &KeywordDlg::OnBnClickedCheckFuzzysearchOn)
	ON_BN_CLICKED(IDOK, &KeywordDlg::OnBnClickedOk)
	ON_BN_CLICKED(ID_BTN_TargetBold, &KeywordDlg::OnBnClickedBtnTargetbold)
	ON_BN_CLICKED(ID_BTN_ExcludeLIST_1, &KeywordDlg::OnBnClickedBtnExcludelist1)
	ON_BN_CLICKED(ID_BTN_ExcludeLIST_2, &KeywordDlg::OnBnClickedBtnExcludelist2)
	ON_BN_CLICKED(ID_BTN_FormatCancellation, &KeywordDlg::OnBnClickedBtnFormatcancellation)
	ON_BN_CLICKED(ID_BTN_Keywords_CLEAR, &KeywordDlg::OnBnClickedBtnKeywordsClear)
	ON_BN_CLICKED(ID_BTN_Hyphen, &KeywordDlg::OnBnClickedBtnHyphen)
	ON_BN_CLICKED(ID_BTN_Slash, &KeywordDlg::OnBnClickedBtnSlash)
	ON_BN_CLICKED(ID_BTN_Underscore, &KeywordDlg::OnBnClickedBtnUnderscore)
	ON_BN_CLICKED(ID_BTN_Period, &KeywordDlg::OnBnClickedBtnPeriod)
	ON_BN_CLICKED(IDC_CHK_KeywordFullPath, &KeywordDlg::OnBnClickedChkKeywordfullpath)
	ON_BN_CLICKED(ID_Keywords_UNDO, &KeywordDlg::OnBnClickedKeywordsUndo)
END_MESSAGE_MAP()


// KeywordDlg メッセージ ハンドラー

//http://rararahp.cool.ne.jp/cgi-bin/lng/vc/vclng.cgi?print+200711/07110073.txt


//http://wisdom.sakura.ne.jp/system/winapi/win32/win66.html
//http://www.kumei.ne.jp/c_lang/sdk3/sdk_292.htm

void KeywordDlg::InsertStrIntoKeywords(CString str){

	//////http://www.geocities.jp/ky_webid/win32c/002.html
	////// メッセージループ

	CString ComboStr = _T("");

	DWORD dwSel;

	if (LastFocus == _T("OK_BOX")){
		((CComboBox*)GetDlgItem(IDC_COMBO_OK_BOX))->GetWindowText(ComboStr);
		dwSel = dwSel_OK;
		if (dwSel != CB_ERR){
			((CComboBox*)GetDlgItem(IDC_COMBO_OK_BOX))->SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(ComboStr.Left(LOWORD(dwSel)) + str + ComboStr.Right(ComboStr.GetLength()-LOWORD(dwSel)))));
			dwSel_OK++; //連続して挿入する場合を考慮
		}
	}else if (LastFocus == _T("NG_BOX")){
		((CComboBox*)GetDlgItem(IDC_COMBO_NG_BOX))->GetWindowText(ComboStr);
		dwSel = dwSel_NG;
		if (dwSel != CB_ERR){
			((CComboBox*)GetDlgItem(IDC_COMBO_NG_BOX))->SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(ComboStr.Left(LOWORD(dwSel)) + str + ComboStr.Right(ComboStr.GetLength()-LOWORD(dwSel)))));
			dwSel_NG++; //連続して挿入する場合を考慮
		}
	}else{
		dwSel = CB_ERR;
		return;
	}

	//LastFocus = _T("NowInserting");
}

void KeywordDlg::OnBnClickedBtnAsterisk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	InsertStrIntoKeywords(_T("*"));
}


//http://msdn.microsoft.com/en-us/library/ms644928(v=vs.85).aspx


BOOL KeywordDlg::OnInitDialog(){
	//WndProc;
	
	CDialogEx::OnInitDialog();

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return FALSE;
	}

	//MatchCNT=0;

	//if(m_Dlg->m_xcList.GetSelectedCount()>=1){
		ReadOrWriteComboData_Func(_T("read"));
	//}

	LastFocus = _T("NotSelected");
	m_xvChkFuzzySearch = TRUE;

	CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHECK_FuzzySearch_ON);

	if (m_xvChkFuzzySearch == TRUE) { //.GetCheck()
		chkbox1->SetCheck(1);
	}

	CButton* chkbox2 = (CButton*)GetDlgItem(IDC_CHK_KeywordFullPath);
	
	m_xvChkKeywordFullPath  = FALSE;
	chkbox2->SetCheck(0);


	if (m_Dlg->CellSizeFixMode == _T("FilePath")){
		if (m_Dlg->m_xcList.GetItemCount()>=1){
			int myResult;
			myResult = MessageBox(_T("只今ファイルパス・モードで閲覧しています。ファイルパス情報を処理できるようにしますか？") ,_T("モード確認"), MB_YESNOCANCEL );

			if (IDYES == myResult){
				CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_KeywordFullPath);

				m_xvChkKeywordFullPath = TRUE;
				chkbox1->SetCheck(1);
		
				//http://rararahp.cool.ne.jp/vc/vctips/button.htm
			}
		}
	}
	return TRUE;
}

void KeywordDlg::OnCbnEditchangeComboOkBox()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	LastFocus = _T("OK_BOX");

	DWORD dwSel;

	//if ((dwSel = m_xcCombo_OK_BOX.GetEditSel()) != CB_ERR){
	if ((dwSel = ((CComboBox*)GetDlgItem(IDC_COMBO_OK_BOX))->GetEditSel()) != CB_ERR){
		dwSel_OK = dwSel;
	}
}

void KeywordDlg::OnCbnSetfocusComboOkBox()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	((CComboBox*)GetDlgItem(IDC_COMBO_OK_BOX))->SetEditSel(-1,-1);  //選択なしで、最後の文字位置にカーソルを置く
}



void KeywordDlg::OnCbnKillfocusComboOkBox()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	LastFocus = _T("OK_BOX");
}


void KeywordDlg::OnCbnSelchangeComboOkBox()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}




void KeywordDlg::OnCbnEditupdateComboOkBox()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void KeywordDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
}

// PreTranslateMessage
BOOL KeywordDlg::PreTranslateMessage (MSG* pMsg)
{
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return 0;
	}

	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		//if(pMsg->hwnd == GetDlgItem(IDD_DIALOG_Keywords)->m_hWnd ){
			if ( ::GetKeyState( VK_CONTROL ) < 0 ) {
				switch ( (int)pMsg->wParam ) {

				case _T('D'):
					//モーダレス１
					m_Dlg->OnFilterDatefilter();
					break;

				case _T('K'):
					//モーダレス１
					m_Dlg->OnFilterKeywords();
					break;

				case _T('L'):
					m_Dlg->ChangeLanguage();
					break;

				case _T('Z'):
					/* アンドゥ */
					if (m_Dlg->ESCAPE_FLG == FALSE) {
						m_Dlg->ESCAPE_FLG = TRUE;
						m_Dlg->StatusStringSet(_T("実行中の処理を停止しました"),300,TRUE);
					}
					m_Dlg->OnEditlistUndo();
					m_Dlg->ESCAPE_FLG = FALSE;
					break;

				case _T('S'):
					/* 保存 */
					m_Dlg->OnMenuFileSave();
			
					m_Dlg->CFileListCreatorDlg::StatusStringSet(_T("ファイルを保存しました"),300,FALSE);
					break;

				//case _T('V'): //追加 2012.05.25
				//	/* ペースト */
				//	break;
				}
			}
		//}
	case WM_LBUTTONDOWN:
		//break;
	case WM_LBUTTONUP://コンボボックスの▼が押された時には拾ってくれる

	case WM_MOUSEMOVE://カーソルの移動そのものを拾う
		if(pMsg->hwnd == GetDlgItem(IDC_COMBO_OK_BOX)->m_hWnd ){

			LastFocus = _T("OK_BOX");
				
			DWORD dwSel;

			if ((dwSel = ((CComboBox*)GetDlgItem(IDC_COMBO_OK_BOX))->GetEditSel()) != CB_ERR){
				dwSel_OK = dwSel;
			}

			//MessageBox(_T("カーソルが移動しました"));
			break;
		}
		if(pMsg->hwnd == GetDlgItem(IDC_COMBO_NG_BOX)->m_hWnd ){

			LastFocus = _T("NG_BOX");
				
			DWORD dwSel;

			if ((dwSel = ((CComboBox*)GetDlgItem(IDC_COMBO_NG_BOX))->GetEditSel()) != CB_ERR){
				dwSel_NG = dwSel;
			}

			//MessageBox(_T("カーソルが移動しました"));
			break;
		}
	default:
		break;
	}


    return CDialog::PreTranslateMessage (pMsg);
}

void KeywordDlg::OnCbnEditchangeComboNgBox()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	LastFocus = _T("NG_BOX");

	DWORD dwSel;

	//if ((dwSel = m_xcCombo_NG_BOX.GetEditSel()) != CB_ERR){
	if ((dwSel = ((CComboBox*)GetDlgItem(IDC_COMBO_NG_BOX))->GetEditSel()) != CB_ERR){
		dwSel_NG = dwSel;
	}
}


void KeywordDlg::OnCbnSetfocusComboNgBox()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	((CComboBox*)GetDlgItem(IDC_COMBO_NG_BOX))->SetEditSel(-1,-1);  //選択なしで、最後の文字位置にカーソルを置く
}


void KeywordDlg::OnCbnKillfocusComboNgBox()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	LastFocus = _T("NG_BOX");
}


void KeywordDlg::OnBnClickedBtnSpace()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	
	//if ( keywords_OK(_T("*うeえ??"),_T("aあiいuうeえoお")) == TRUE) {
	//	MessageBox(_T("文字は部分一致しました。"),_T("テスト"),MB_OK);
	//}

	//if ( keywords_OK(_T("*??"),_T("*??")) == TRUE) {
	//	MessageBox(_T("文字は部分一致しました。"),_T("テスト"),MB_OK);
	//}
	InsertStrIntoKeywords(_T(" "));
}


void KeywordDlg::OnBnClickedBtnQuestionmark()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	InsertStrIntoKeywords(_T("?"));
}


void KeywordDlg::OnBnClickedBtnPathseparator()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	InsertStrIntoKeywords(_T("\\"));
}


void KeywordDlg::OnBnClickedBtnDoublequotationmark()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	InsertStrIntoKeywords(_T("\""));
}


BOOL KeywordDlg::Split_And_SetArray_Func(){ //CString targetStr,CString keywords
    
	CString TempStr;

	int i;

	i=0;
	while (i<100){
		Keywords_OK_Array[i]=_T("");
		Keywords_NG_Array[i]=_T("");
		i++;
	}


	CString ComboStr;
	((CComboBox*)GetDlgItem(IDC_COMBO_OK_BOX))->GetWindowText(ComboStr);
	keywords_OK_Str = ComboStr;

	((CComboBox*)GetDlgItem(IDC_COMBO_NG_BOX))->GetWindowText(ComboStr);
	keywords_NG_Str = ComboStr;


	TempStr = keywords_OK_Str;

	int myCnt=0;
	i=0;
	while (i<=TempStr.GetLength()-1){
		if(TempStr.Mid(i,1)==_T("\"")){
			myCnt++;
		}
		i++;
	}

	if(myCnt % 2 != 0){
		int myResult;
		
		myResult = MessageBox(_T("OK Wordは、「\"」(ダブルコーテーション)を、２個セットで(偶数個で)記述して下さい\r\nダブルコーテーションを削除して処理を続行しますか？") ,_T("ダブルコーテーション"), MB_YESNOCANCEL);
		
		if (IDYES == myResult){
			keywords_OK_Str.Replace(_T("\""),_T(""));
			((CComboBox*)GetDlgItem(IDC_COMBO_OK_BOX))->SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(keywords_OK_Str)));
		}else{
			return FALSE;
		}
	}

	TempStr = keywords_NG_Str;

	myCnt=0;
	i=0;
	while (i<=TempStr.GetLength()-1){
		if(TempStr.Mid(i,1)==_T("\"")){
			myCnt++;
		}
		i++;
	}

	if(myCnt % 2 != 0){
		int myResult;
		
		myResult = MessageBox(_T("NG Wordは、「\"」(ダブルコーテーション)を、２個セットで(偶数個で)記述して下さい\r\nダブルコーテーションを削除して処理を続行しますか？") ,_T("ダブルコーテーション"), MB_YESNOCANCEL);
		
		if (IDYES == myResult){
			keywords_NG_Str.Replace(_T("\""),_T(""));
			((CComboBox*)GetDlgItem(IDC_COMBO_NG_BOX))->SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(keywords_NG_Str)));
		}else{
			return FALSE;
		}
	}

	TempStr = keywords_OK_Str;


	OK_index = 0;

	int StartIDX;
	int EndIDX;

	BOOL QuotStartFLG;
	BOOL SpaceStartFLG;

	i=0;
	StartIDX = 0;
	EndIDX = 0;

	QuotStartFLG = FALSE;
	SpaceStartFLG = FALSE;

	TempStr = TempStr.TrimLeft(_T(" "));
	TempStr = TempStr.TrimRight(_T(" "));

	//if ( keywords_OK_Str.GetLength() == 1 ){ //追加 2012.04.04
	//	if (m_xvChkFuzzySearch == TRUE) {
	//		Keywords_OK_Array[OK_index] = _T("*") + keywords_OK_Str + _T("*");
	//	}
	//	OK_index++;
	//}else{
		while (i<=TempStr.GetLength()-1){
			if (TempStr.Mid(i,1) == _T("\"")){
				if(QuotStartFLG == FALSE){
					QuotStartFLG  = TRUE;
					StartIDX = i;

				}else if (QuotStartFLG == TRUE){
					QuotStartFLG = FALSE;
					EndIDX = i;

					if(OK_index<=100){
						Keywords_OK_Array[OK_index] = TempStr.Mid(StartIDX+1,EndIDX-StartIDX-1);

						if (m_xvChkFuzzySearch == TRUE) {
							Keywords_OK_Array[OK_index]= _T("*") + Keywords_OK_Array[OK_index] + _T("*");
						}
						OK_index++;
					}

					i++;

				}
			}


			if(QuotStartFLG == FALSE){
				if(SpaceStartFLG == FALSE && TempStr.Mid(i,1) != _T(" ") && TempStr.Mid(i,1) != _T("　")){
					SpaceStartFLG  = TRUE;
					StartIDX = i;
				}
				
				if ((TempStr.Find(_T(" "),0) == NULL && TempStr.Find(_T("　"),0) == NULL  || i ==TempStr.GetLength()-1 )){
					EndIDX = i;

					if(OK_index<=100){
						Keywords_OK_Array[OK_index] = TempStr.Mid(StartIDX,EndIDX-StartIDX+1);

						if (m_xvChkFuzzySearch == TRUE) {
							Keywords_OK_Array[OK_index]= _T("*") + Keywords_OK_Array[OK_index] + _T("*");
						}

						OK_index++;
					}

					//break;
				}else if ((TempStr.Mid(i,1) == _T(" ") || TempStr.Mid(i,1) == _T("　") || i ==TempStr.GetLength()-1 ) && ( SpaceStartFLG == TRUE )){
					SpaceStartFLG = FALSE;
					EndIDX = i;
				
					if(OK_index<=100){
						Keywords_OK_Array[OK_index] = TempStr.Mid(StartIDX,EndIDX-StartIDX);

						if (m_xvChkFuzzySearch == TRUE) {
							//Keywords_OK_Array[OK_index] = Keywords_OK_Array[OK_index].TrimLeft(_T(" "));
							//Keywords_OK_Array[OK_index] = Keywords_OK_Array[OK_index].TrimRight(_T(" "));
							Keywords_OK_Array[OK_index]= _T("*") + Keywords_OK_Array[OK_index] + _T("*");
						}

						OK_index++;
					}

				}
			}

			i++;
		}
	//}

	//i=0;
	//while (i<=OK_index-1){
	//	MessageBox(Keywords_OK_Array[i]);
	//	i++;
	//}

	TempStr = keywords_NG_Str;


	NG_index = 0;

	i=0;
	StartIDX = 0;
	EndIDX = 0;

	QuotStartFLG = FALSE;
	SpaceStartFLG = FALSE;

	TempStr = TempStr.TrimLeft(_T(" "));
	TempStr = TempStr.TrimRight(_T(" "));

	//if ( keywords_NG_Str.GetLength() == 1 ){ //追加 2012.04.04
	//	if (m_xvChkFuzzySearch == TRUE) {
	//		Keywords_NG_Array[NG_index] = _T("*") + keywords_NG_Str + _T("*");
	//	}
	//	NG_index++;
	//}else{
		while (i<=TempStr.GetLength()-1){
			if (TempStr.Mid(i,1) == _T("\"")){
				if(QuotStartFLG == FALSE){
					QuotStartFLG  = TRUE;
					StartIDX = i;

				}else if (QuotStartFLG == TRUE){
					QuotStartFLG = FALSE;
					EndIDX = i;

					if(NG_index<=100){
						Keywords_NG_Array[NG_index] = TempStr.Mid(StartIDX+1,EndIDX-StartIDX-1);

						if (m_xvChkFuzzySearch == TRUE) {
							Keywords_NG_Array[NG_index]= _T("*") + Keywords_NG_Array[NG_index] + _T("*");
						}
						NG_index++;
					}

					i++;

				}
			}

			if(QuotStartFLG == FALSE){
				if(SpaceStartFLG == FALSE && TempStr.Mid(i,1) != _T(" ") && TempStr.Mid(i,1) != _T("　")){
					SpaceStartFLG  = TRUE;
					StartIDX = i;
				}
				
				if ((TempStr.Find(_T(" "),0) == NULL && TempStr.Find(_T("　"),0) == NULL || i ==TempStr.GetLength()-1 )){
					EndIDX = i;

					if(NG_index<=100){
						Keywords_NG_Array[NG_index] = TempStr.Mid(StartIDX,EndIDX-StartIDX+1);

						if (m_xvChkFuzzySearch == TRUE) {
							Keywords_NG_Array[NG_index]= _T("*") + Keywords_NG_Array[NG_index] + _T("*");
						}
						NG_index++;
					}

					//break;
				}else if ((TempStr.Mid(i,1) == _T(" ") || TempStr.Mid(i,1) == _T("　") || i ==TempStr.GetLength()-1 ) && ( SpaceStartFLG == TRUE )){
					SpaceStartFLG = FALSE;
					EndIDX = i;
				
					if(NG_index<=100){
						Keywords_NG_Array[NG_index] = TempStr.Mid(StartIDX,EndIDX-StartIDX);

						if (m_xvChkFuzzySearch == TRUE) {
							//Keywords_NG_Array[NG_index] = Keywords_NG_Array[NG_index].TrimLeft(_T(" "));
							//Keywords_NG_Array[NG_index] = Keywords_NG_Array[NG_index].TrimRight(_T(" "));
							Keywords_NG_Array[NG_index]= _T("*") + Keywords_NG_Array[NG_index] + _T("*");
						}
						NG_index++;
					}

				}
			}

			i++;
		}
	//}

	//i=0;
	//while (i<=NG_index-1){
	//	MessageBox(Keywords_NG_Array[i]);
	//	i++;
	//}

	UpdateData(FALSE);

	if(OK_index>100 || NG_index>100){
		MessageBox(_T("OK WordとNG Wordは、それぞれ１００個まで指定可能です。１００個目以前のキーワード処理を続行します。") ,_T("キーワード数超過"), MB_OK);
	}

	return TRUE;
}

//BOOL KeywordDlg::Like_Func(CString targetStr){
//★http://oshiete.goo.ne.jp/qa/287644.html
//http://oshiete.goo.ne.jp/qa/6966243.html
//http://oshiete.goo.ne.jp/qa/6998958.html

int KeywordDlg::StrMatchMBS( const TCHAR *Ptn, const TCHAR *Str ){

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
//}

BOOL KeywordDlg::keywords_OK(CString targetStr,CString in_Str){
	//MessageBox(targetStr);

	if( targetStr == _T("") ||  in_Str == _T("")){
		return FALSE;
	}

	if (m_xvChkFuzzySearch == TRUE) {
		if( targetStr == _T("**") ||  in_Str == _T("**")){
			return FALSE;
		}
	}


    BOOL tempFLG = FALSE;

	CString str_1 = targetStr;
	CString str_2 = in_Str;
	
	str_1.MakeLower();
	str_2.MakeLower();

	//■TCHAR[]に変換してしまうと「嵐」などの駄目文字に対応できない。CString のまま使う 20011.09.15


	tempFLG = StrMatchMBS(str_1,str_2);

	if( tempFLG == TRUE ){
        return TRUE;
	}else{
        return FALSE;
	}
}

BOOL KeywordDlg::keywords_NG(CString targetStr,CString in_Str){
	if( targetStr == _T("") ||  in_Str == _T("")){
		return FALSE;
	}

	if (m_xvChkFuzzySearch == TRUE) {
		if( targetStr == _T("**") ||  in_Str == _T("**")){
			return FALSE;
		}
	}

    BOOL tempFLG = FALSE;

	CString str_1 = targetStr;
	CString str_2 = in_Str;
	
	str_1.MakeLower();
	str_2.MakeLower();

	//■TCHAR[]に変換してしまうと「嵐」などの駄目文字に対応できない。CString のまま使う 20011.09.15

	tempFLG = StrMatchMBS(str_1,str_2);

	if( tempFLG == TRUE ){
        return TRUE;
	}else{
        return FALSE;
	}
}


void KeywordDlg::OnBnClickedBtnTargetred()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount();
	m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData")); //変更 2012.05.02

	Split_And_SetArray_Func();
	SameKeyword();
	EmphasisByKeywords(_T("Red"));
	return;
}

void KeywordDlg::EmphasisByKeywords(CString mySwitch){
	//LVITEM       lvi;
	int          err = 0;
	CString      str;	
	CString      FullPathString;



	CString myFileName;

	FullPathString =_T("");
	myFileName=_T("");

	CString RemarksColumnStr;

	RemarksColumnStr = _T("");

	//MessageBox (Keywords_OK_Array[0]);

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->lvi.mask = LVIF_TEXT;

	if(m_Dlg->m_xcList.GetItemCount() < 1) {
		m_Dlg->StatusStringSet(_T("データがないので何も行われませんでした"),300,TRUE);
		return;
	}

	m_Dlg->StatusStringSet(_T("KeywordsFilter 実行中"),0,FALSE); //変更 2012.06.14

	if( m_xvChkFuzzySearch == FALSE ) {
		int myResult;

		myResult = MessageBox(_T("あいまい検索がＯＦＦになっています。ＯＮにしますか？"),_T("あいまい検索"),MB_YESNOCANCEL);

		if (IDYES == myResult){
			CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHECK_FuzzySearch_ON);
			m_xvChkFuzzySearch = TRUE;
			chkbox1->SetCheck(1);
		}else if (IDCANCEL==myResult){
			return;
		}
	}
	//m_Dlg->SelectALL_CancellationFunc(); //コメント化 2012.06.01
	m_Dlg->GetStrFormat_Func();

	int workRow = 0;
	int FormatDataNum=11;
	CString FormatDataStr=_T("");

	if ( mySwitch == _T("Red") || mySwitch == _T("Bold") ) {
		BOOL OK_IS_TRUE;
		BOOL NG_IS_TRUE;

		workRow = 0;

		while (workRow<m_Dlg->m_xcList.GetItemCount()){
			FormatDataNum = m_Dlg->m_xcList.GetItemData(workRow);
			
			FullPathString = m_Dlg->m_xcList.GetItemText(workRow,2); //ファイルパス
			myFileName = m_Dlg->m_xcList.GetItemText(workRow,3); //ファイル名

			RemarksColumnStr = m_Dlg->m_xcList.GetItemText(workRow,8);//8:備考欄

			//if (FullPathString !=_T("")){
			//	FullPathString.Replace(_T("%"),_T("%%"));
			//}

			int i=0;

			OK_IS_TRUE = FALSE;

			while ( i <= OK_index -1 ){
				if ( (m_xvChkKeywordFullPath == TRUE && keywords_OK(Keywords_OK_Array[i],FullPathString)==TRUE )  || keywords_OK(Keywords_OK_Array[i],myFileName)==TRUE || keywords_OK(Keywords_OK_Array[i],RemarksColumnStr)==TRUE) {
					//備考欄も追加？NGの条件追加
					OK_IS_TRUE = TRUE;
				}
				i++;
			}

			i=0;
			NG_IS_TRUE = FALSE;

			while ( i <= NG_index -1 ){
				if ( (m_xvChkKeywordFullPath == TRUE && keywords_NG(Keywords_NG_Array[i],FullPathString)==TRUE )  || keywords_NG(Keywords_NG_Array[i],myFileName)==TRUE || keywords_NG(Keywords_NG_Array[i],RemarksColumnStr)==TRUE) {
					//備考欄も追加？NGの条件追加
					NG_IS_TRUE = TRUE;
				}
				i++;
			}
   
			if ( OK_IS_TRUE==TRUE && NG_IS_TRUE==FALSE ) {
//				//備考欄も追加？NGの条件追加
				if (mySwitch == _T("Red")){
					FormatDataNum = m_Dlg->SetToRed(FormatDataNum);
				}
				if (mySwitch == _T("Bold")){
					FormatDataNum = m_Dlg->SetToBold(FormatDataNum);
				}

				m_Dlg->m_xcList.SetItemData(workRow,FormatDataNum);

				if(FormatDataNum == 11){
					FormatDataStr = _T("NORMAL,BLACK,");
				}

				if(FormatDataNum == 12){
					FormatDataStr = _T("BOLD,BLACK,");
				}
		
				if(FormatDataNum == 21){
					FormatDataStr = _T("NORMAL,RED,");
				}

				if(FormatDataNum == 22){
					FormatDataStr = _T("BOLD,RED,");
				}

				m_Dlg->lvi.iItem = workRow;
				m_Dlg->lvi.iSubItem = 9;
				m_Dlg->lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

				m_Dlg->m_xcList.SetItem(&m_Dlg->lvi);
				UpdateData(FALSE);

				//ListView_Update(m_Dlg->m_xcList, workRow);//追加 2012.06.01
				m_Dlg->ListDataNoChange_FLG = FALSE;//追加 2012.05.13
			}
			workRow++;
		}
		m_Dlg->SetSEQ_NUM_Func(TRUE);
	}

	if ( mySwitch == _T("ExcludeLIST") ) {
		BOOL OK_IS_TRUE;
		BOOL NG_IS_TRUE;

		workRow = 0;

		while (workRow<m_Dlg->m_xcList.GetItemCount()){
			FormatDataNum = m_Dlg->m_xcList.GetItemData(workRow);

			FullPathString = m_Dlg->m_xcList.GetItemText(workRow,2); //ファイルパス
			myFileName = m_Dlg->m_xcList.GetItemText(workRow,3); //ファイル名
			
			RemarksColumnStr = m_Dlg->m_xcList.GetItemText(workRow,8);//8:備考欄

			//if (FullPathString !=_T("")){
			//	FullPathString.Replace(_T("%"),_T("%%"));
			//}

			int i=0;

			OK_IS_TRUE = FALSE;

			while ( i <= OK_index -1 ){
				if ( (m_xvChkKeywordFullPath == TRUE && keywords_OK(Keywords_OK_Array[i],FullPathString)==TRUE )  || keywords_OK(Keywords_OK_Array[i],myFileName)==TRUE || keywords_OK(Keywords_OK_Array[i],RemarksColumnStr)==TRUE) {
					//備考欄も追加？NGの条件追加
					OK_IS_TRUE = TRUE;
				}
				i++;
			}

			i=0;
			NG_IS_TRUE = FALSE;

			while ( i <= NG_index -1 ){
				if ((m_xvChkKeywordFullPath == TRUE && keywords_NG(Keywords_NG_Array[i],FullPathString)==TRUE )  || keywords_NG(Keywords_NG_Array[i],myFileName)==TRUE || keywords_NG(Keywords_NG_Array[i],RemarksColumnStr)==TRUE) {
					//備考欄も追加？NGの条件追加
					NG_IS_TRUE = TRUE;
				}
				i++;
			}
   
			if ( OK_IS_TRUE==FALSE || NG_IS_TRUE==TRUE) {
				m_Dlg->m_xcList.EnsureVisible(workRow, FALSE); //追加 2012.04.04  //コメント化 2012.06.10
				m_Dlg->ItemCount_Func(TRUE); //追加2012.04.04

				m_Dlg->m_xcList.DeleteItem(workRow);

				m_Dlg->ListDataNoChange_FLG = FALSE;//追加 2012.05.13
			}else{
				workRow++;
			}
		}
		m_Dlg->SetSEQ_NUM_Func(TRUE);
	}

	if ( mySwitch == _T("ExcludeLIST2") ){
		workRow = 0;

		while (workRow<m_Dlg->m_xcList.GetItemCount()){
			FormatDataNum = m_Dlg->m_xcList.GetItemData(workRow);

			if ( FormatDataNum == 11) {
				m_Dlg->m_xcList.EnsureVisible(workRow, FALSE); //追加 2012.04.04  //コメント化 2012.06.10
				m_Dlg->ItemCount_Func(TRUE); //追加2012.04.04

				m_Dlg->m_xcList.DeleteItem(workRow);

				m_Dlg->ListDataNoChange_FLG = FALSE;//追加 2012.05.13
			}else{
				workRow++;
			}
		}
		m_Dlg->SetSEQ_NUM_Func(TRUE);
	}

	if ( mySwitch == _T("FormatCancellation") ) {
		workRow = 0;
        
		while (workRow < m_Dlg->m_xcList.GetItemCount()) {
			m_Dlg->m_xcList.SetItemData(workRow,11);

			FormatDataStr = _T("NORMAL,BLACK,");

			m_Dlg->lvi.iItem = workRow;
			m_Dlg->lvi.iSubItem = 9;
			m_Dlg->lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

			m_Dlg->m_xcList.SetItem(&m_Dlg->lvi);
			//ListView_Update(m_Dlg->m_xcList, workRow);  //コメント化？ 2012,06.01 //再コメント化 2012.06.15
			UpdateData(FALSE);
			workRow++;
		}
		m_Dlg->SetSEQ_NUM_Func(TRUE);

		m_Dlg->ListDataNoChange_FLG = FALSE;//追加 2012.05.13
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //追加 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}

	m_Dlg->SetStrFormat_Func();

	m_Dlg->Total_Bytes_Bold();
	m_Dlg->Total_Bytes_Func();
	m_Dlg->ItemCount_Func(TRUE);


	ExistCheckFunc(_T("OK_BOX"));
	ExistCheckFunc(_T("NG_BOX"));
	ReadOrWriteComboData_Func(_T("write"));

	m_Dlg->StatusStringSet(_T("KeywordsFilter 終了"),300,TRUE);

}


BOOL KeywordDlg::SameKeyword(){
	CString ComboStr;
	((CComboBox*)GetDlgItem(IDC_COMBO_OK_BOX))->GetWindowText(ComboStr);
	keywords_OK_Str = ComboStr;

	((CComboBox*)GetDlgItem(IDC_COMBO_NG_BOX))->GetWindowText(ComboStr);
	keywords_NG_Str = ComboStr;

    if( keywords_OK_Str == _T("") && keywords_NG_Str == _T("") ){
        return FALSE;
    }
    
    
    BOOL sameFLG;
    
    sameFLG = FALSE;


    int OK_WordIDX;
    int NG_WordIDX;
    
    for ( OK_WordIDX = 0; OK_WordIDX <= OK_index; OK_WordIDX++){ 
        if ( Keywords_OK_Array[OK_WordIDX] != _T("") && keywords_OK_Str != _T("") ){
            for (NG_WordIDX = 0; NG_WordIDX <= NG_index; NG_WordIDX++){
                if ( Keywords_NG_Array[NG_WordIDX] != _T("") && keywords_NG_Str != _T("") ){
                    if ( Keywords_NG_Array[NG_WordIDX] == Keywords_OK_Array[OK_WordIDX] ) {
                        sameFLG = TRUE;
                    }
				}
            }
       }
    }

	int Result;

    if ( sameFLG == TRUE ){
        Result = MessageBox(_T("検索ワードのOKワードとNGワードに同じものが含まれ、それらの条件では、検索結果にはヒットしません。同一文字を一括削除しますか？\r\n(「いいえ」を選択すると、検索を続行します。)"), _T("キーワード重複確認"), MB_YESNOCANCEL );
        
        if ( Result == IDYES ){
			for ( OK_WordIDX = 0; OK_WordIDX <= OK_index; OK_WordIDX++){ 
				if ( Keywords_OK_Array[OK_WordIDX] != _T("") && keywords_OK_Str != _T("") ){
					for (NG_WordIDX = 0; NG_WordIDX <= NG_index; NG_WordIDX++){
						if ( Keywords_NG_Array[NG_WordIDX] != _T("") && keywords_NG_Str != _T("") ){
							if ( Keywords_NG_Array[NG_WordIDX] == Keywords_OK_Array[OK_WordIDX] ) {

								CString tempOKStr;
								tempOKStr = Keywords_OK_Array[OK_WordIDX];
								if (m_xvChkFuzzySearch == TRUE) {
									//tempOKStr = tempOKStr.Mid(1,tempOKStr.GetLength()-2);

									tempOKStr = tempOKStr.TrimLeft(_T("*"));
									tempOKStr = tempOKStr.TrimRight(_T("*"));

								}
								keywords_OK_Str.Replace(tempOKStr,_T(""));
								keywords_OK_Str.Replace(_T("\"\""),_T("")); //追加 2012.04.22
								//keywords_OK_Str.Replace(_T("  "),_T(" "));

								if (keywords_OK_Str.Left(1)==_T(" ")){
									keywords_OK_Str = keywords_OK_Str.Mid(1,keywords_OK_Str.GetLength()-1);
								}

								((CComboBox*)GetDlgItem(IDC_COMBO_OK_BOX))->SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(keywords_OK_Str)));

								CString tempNGStr;
								tempNGStr = Keywords_NG_Array[NG_WordIDX];
								if (m_xvChkFuzzySearch == TRUE) {
									//tempNGStr = tempNGStr.Mid(1,tempNGStr.GetLength()-2);
									tempNGStr = tempNGStr.TrimLeft(_T("*"));
									tempNGStr = tempNGStr.TrimRight(_T("*"));
								}
								keywords_NG_Str.Replace(tempNGStr,_T(""));
								keywords_NG_Str.Replace(_T("\"\""),_T("")); //追加 2012.04.22
								//keywords_NG_Str.Replace(_T("  "),_T(" "));

								if (keywords_NG_Str.Left(1)==_T(" ")){
									keywords_NG_Str = keywords_NG_Str.Mid(1,keywords_NG_Str.GetLength()-1);
								}

								((CComboBox*)GetDlgItem(IDC_COMBO_NG_BOX))->SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(keywords_NG_Str)));
							}
						}
					}
				}
			}
			//ReadOrWriteComboData_Func(_T("write"));
			Split_And_SetArray_Func();
			return TRUE;
		}else if ( Result == IDNO ) {
            return FALSE;
        }else if ( Result == IDCANCEL ){
            return FALSE;
		}
	}
	return FALSE;
}

void KeywordDlg::OnBnClickedCheckFuzzysearchOn()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	//http://www.ujasiri.com/prglib/vc/compo/vc_chkboxsap.html

	CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHECK_FuzzySearch_ON);

	if (m_xvChkFuzzySearch == TRUE) { //.GetCheck()
		m_xvChkFuzzySearch = FALSE;
		chkbox1->SetCheck(0);
	}else{
		m_xvChkFuzzySearch = TRUE;
		chkbox1->SetCheck(1);
	}
}


void KeywordDlg::ExistCheckFunc(CString mySwitch)
{
	if (mySwitch==_T("OK_BOX")){
		BOOL tempFLG = TRUE;
		CString EditData;
		KeywordDlg::m_xcCombo_OK_BOX.GetWindowText(EditData);

		//if(EditData !=_T("")){
			int k = 0;
	
			int k2 = 0;

			while (k <= KeywordDlg::m_xcCombo_OK_BOX.GetCount() -1){
				CString ComboText;
				KeywordDlg::m_xcCombo_OK_BOX.GetLBText(k, ComboText); // インデックスk番目の文字列を取得

				if(ComboText == EditData){
					KeywordDlg::m_xcCombo_OK_BOX.SetCurSel(k);
					k2 = k;
					tempFLG = FALSE;
				}
				k++;
			}

			if(tempFLG == TRUE){
				KeywordDlg::m_xcCombo_OK_BOX.InsertString(0,EditData);
				KeywordDlg::m_xcCombo_OK_BOX.SetCurSel(0);
			}else{
				KeywordDlg::m_xcCombo_OK_BOX.DeleteString(k2);
				KeywordDlg::m_xcCombo_OK_BOX.InsertString(0,EditData);
				KeywordDlg::m_xcCombo_OK_BOX.SetCurSel(0);
			}

			for(k = KeywordDlg::m_xcCombo_OK_BOX.GetCount();k>=ComboBox_MAX;k--){
				KeywordDlg::m_xcCombo_OK_BOX.DeleteString(k);
			}
		//}
	}else if (mySwitch==_T("NG_BOX")){
		BOOL tempFLG = TRUE;
		CString EditData;
		KeywordDlg::m_xcCombo_NG_BOX.GetWindowText(EditData);

		//if(EditData !=_T("")){
			int k = 0;
	
			int k2 = 0;

			while (k <= KeywordDlg::m_xcCombo_NG_BOX.GetCount() -1){
				CString ComboText;
				KeywordDlg::m_xcCombo_NG_BOX.GetLBText(k, ComboText); // インデックスk番目の文字列を取得

				if(ComboText == EditData){
					KeywordDlg::m_xcCombo_NG_BOX.SetCurSel(k);
					k2 = k;
					tempFLG = FALSE;
				}
				k++;
			}

			if(tempFLG == TRUE){
				KeywordDlg::m_xcCombo_NG_BOX.InsertString(0,EditData);
				KeywordDlg::m_xcCombo_NG_BOX.SetCurSel(0);
			}else{
				KeywordDlg::m_xcCombo_NG_BOX.DeleteString(k2);
				KeywordDlg::m_xcCombo_NG_BOX.InsertString(0,EditData);
				KeywordDlg::m_xcCombo_NG_BOX.SetCurSel(0);
			}

			for(k = KeywordDlg::m_xcCombo_NG_BOX.GetCount();k>=ComboBox_MAX;k--){
				KeywordDlg::m_xcCombo_NG_BOX.DeleteString(k);
			}
		//}
	}
}

void KeywordDlg::ReadOrWriteComboData_Func(CString mySwitch)
{
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	CString WriteData1;
	CString WriteData2;

	if (mySwitch == _T("write")){ //write
		int k;

		k = 0;
		WriteData1 = _T("");

		while (k <= KeywordDlg::m_xcCombo_OK_BOX.GetCount() -1){
			CString ComboText;
			KeywordDlg::m_xcCombo_OK_BOX.GetLBText(k, ComboText); // インデックス0番目の文字列を取得
			if(k<=ComboBox_MAX){
				WriteData1 = WriteData1 + ComboText + _T("\n");
			}
			k++;
		}

		k = 0;
		WriteData2 = _T("");

		while (k <= KeywordDlg::m_xcCombo_NG_BOX.GetCount() -1){
			CString ComboText;
			KeywordDlg::m_xcCombo_NG_BOX.GetLBText(k, ComboText); // インデックス0番目の文字列を取得
			if(k<=ComboBox_MAX){
				WriteData2 = WriteData2 + ComboText + _T("\n");
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

		}else{
			
		}
		//http://www.g-ishihara.com/mfc_fi_01.htm
		if (mySwitch == _T("read")){
			if ( PathFileExists( CurDir + _T("\\KeywordOK_BOX.dat") ) ){ //追加 2012.06.15
				FILE *fp;
				_tfopen_s(&fp,CurDir + _T("\\KeywordOK_BOX.dat"), _T("r, ccs=UNICODE"));
				CStdioFile stdFile1(fp);

				err = 0;
				int k;
				k = 0;
				while (!err) {
					if (stdFile1.ReadString(rstr) == FALSE) err = 1;
					if (!err && (k<ComboBox_MAX)){
						KeywordDlg::m_xcCombo_OK_BOX.InsertString(k,rstr);
					}

					k++;
				}
				KeywordDlg::m_xcCombo_OK_BOX.SetCurSel(0);


				// (6)クローズ(明示的)
				stdFile1.Close();
				fclose(fp);
			}
			err = 0;

			if ( PathFileExists( CurDir + _T("\\KeywordNG_BOX.dat") ) ){ //追加 2012.06.15
				FILE *fp;
				_tfopen_s(&fp,CurDir + _T("\\KeywordNG_BOX.dat"), _T("r, ccs=UNICODE"));
				CStdioFile stdFile2(fp);

				err=0;
				int k;
				k = 0;
				while (!err) {
					if (stdFile2.ReadString(rstr) == FALSE) err = 1;
					if (!err && (k<ComboBox_MAX)){
						KeywordDlg::m_xcCombo_NG_BOX.InsertString(k,rstr);
					}

					k++;
				}
				KeywordDlg::m_xcCombo_NG_BOX.SetCurSel(0);

				// (6)クローズ(明示的)
				stdFile2.Close();
				fclose(fp);
			}

		}
		if (mySwitch == _T("write")){
			FILE *fp;

			_tfopen_s(&fp,CurDir + _T("\\KeywordOK_BOX.dat"), L"w,ccs=UNICODE");
			fputws(WriteData1, fp);
			fclose(fp);

			_tfopen_s(&fp,CurDir + _T("\\KeywordNG_BOX.dat"), L"w,ccs=UNICODE");
			fputws(WriteData2, fp);
			fclose(fp);
		}
	}
}

void KeywordDlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnOK();

	//ReadOrWriteComboData_Func(_T("write"));
}


void KeywordDlg::OnBnClickedBtnTargetbold()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount();
	m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData")); //変更 2012.05.02

	Split_And_SetArray_Func();
	SameKeyword();
	EmphasisByKeywords(_T("Bold"));
	return;
}


void KeywordDlg::OnBnClickedBtnExcludelist1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount();
	m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData")); //変更 2012.05.02

	Split_And_SetArray_Func();
	SameKeyword();
	EmphasisByKeywords(_T("ExcludeLIST"));
	return;
}


void KeywordDlg::OnBnClickedBtnExcludelist2()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount();
	m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData")); //変更 2012.05.02

	Split_And_SetArray_Func();
	SameKeyword();
	EmphasisByKeywords(_T("ExcludeLIST2"));
	return;
}


void KeywordDlg::OnBnClickedBtnFormatcancellation()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount();
	m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData")); //変更 2012.05.02

	Split_And_SetArray_Func();
	SameKeyword();
	EmphasisByKeywords(_T("FormatCancellation"));
	return;
}


void KeywordDlg::OnBnClickedBtnKeywordsClear()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	m_xcCombo_OK_BOX.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(_T(""))));
	m_xcCombo_NG_BOX.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(_T(""))));
}


void KeywordDlg::OnBnClickedBtnHyphen()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	InsertStrIntoKeywords(_T("-"));
}


void KeywordDlg::OnBnClickedBtnSlash()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	InsertStrIntoKeywords(_T("/"));
}


void KeywordDlg::OnBnClickedBtnUnderscore()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	InsertStrIntoKeywords(_T("_"));
}


void KeywordDlg::OnBnClickedBtnPeriod()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	InsertStrIntoKeywords(_T("."));
}


void KeywordDlg::OnBnClickedChkKeywordfullpath()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_KeywordFullPath);
	
	if (m_xvChkKeywordFullPath == FALSE){
		m_xvChkKeywordFullPath  = TRUE;
		chkbox1->SetCheck(1);
		
		//http://rararahp.cool.ne.jp/vc/vctips/button.htm
	}else{
		m_xvChkKeywordFullPath  = FALSE;
		chkbox1->SetCheck(0);
	}
}


void KeywordDlg::OnBnClickedKeywordsUndo()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	//CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	//if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
	//	return;
	//}

	//m_Dlg->OnEditlistUndo();
}
