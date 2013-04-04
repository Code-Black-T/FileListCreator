// HTML_Dlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "FileListCreator.h"
#include "FileListCreatorDlg.h"//追加

#include "HTML_Dlg.h"
#include "afxdialogex.h"



// HTML_Dlg ダイアログ

IMPLEMENT_DYNAMIC(HTML_Dlg, CDialogEx)

HTML_Dlg::HTML_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(HTML_Dlg::IDD, pParent)
	, m_xvRadioModifyDate(1)
	, m_xvRadioRemarksColumn(2)
	, m_xvChkCopyOn(TRUE)
	, m_xvChkRedOn(TRUE)
	, m_xvRadioENCODING_SELECT(0)
{

}

HTML_Dlg::~HTML_Dlg()
{
}

void HTML_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_ModifyDateVisible, m_xvRadioModifyDate);
	DDX_Radio(pDX, IDC_RADIO_RemarksColumnVisible, m_xvRadioRemarksColumn);
	DDX_Check(pDX, IDC_CHECK_Copy_Func_ON, m_xvChkCopyOn);
	DDX_Check(pDX, IDC_CHECK_StrRed_ON, m_xvChkRedOn);
	DDX_Radio(pDX, IDC_RADIO_Shift_JIS, m_xvRadioENCODING_SELECT);
}


BEGIN_MESSAGE_MAP(HTML_Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Default2, &HTML_Dlg::OnBnClickedButtonDefault2)
	ON_BN_CLICKED(IDC_CHECK_Copy_Func_ON, &HTML_Dlg::OnBnClickedCheckCopyFuncOn)
	ON_BN_CLICKED(IDC_CHECK_StrRed_ON, &HTML_Dlg::OnBnClickedCheckStrredOn)
	ON_BN_CLICKED(IDOK, &HTML_Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_RemarksColumnVisible, &HTML_Dlg::OnBnClickedRadioRemarkscolumnvisible)
	ON_BN_CLICKED(IDC_RADIO_RemarksColumnInvisible, &HTML_Dlg::OnBnClickedRadioRemarkscolumninvisible)
	ON_BN_CLICKED(IDCANCEL, &HTML_Dlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// HTML_Dlg メッセージ ハンドラー


void HTML_Dlg::OnBnClickedButtonDefault2()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	m_xvRadioModifyDate=1;
	m_xvRadioRemarksColumn=2;
	m_xvChkCopyOn=TRUE;
	m_xvChkRedOn=TRUE;
	m_xvRadioENCODING_SELECT=0;
	UpdateData(FALSE);
}


void HTML_Dlg::OnBnClickedCheckCopyFuncOn()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	if (m_xvChkCopyOn == FALSE){
		m_xvChkCopyOn = TRUE;
	}else{
		m_xvChkCopyOn = FALSE;
	}
}


void HTML_Dlg::OnBnClickedCheckStrredOn()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	if (m_xvChkRedOn == FALSE){
		m_xvChkRedOn = TRUE;
	}else{
		m_xvChkRedOn = FALSE;
	}
}


void HTML_Dlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnOK();


	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->g_RadioModifyDate=m_xvRadioModifyDate;
	m_Dlg->g_RadioRemarksColumn=m_xvRadioRemarksColumn;
	m_Dlg->g_ChkCopyOn=m_xvChkCopyOn;
	m_Dlg->g_ChkRedOn=m_xvChkRedOn;
	m_Dlg->g_RadioENCODING_SELECT=m_xvRadioENCODING_SELECT; //追加 2012.04.21
	
	//m_Dlg->ExportFileList();

	//m_Dlg->g_NoDrawFLG = TRUE;

}


void HTML_Dlg::OnBnClickedRadioRemarkscolumnvisible()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if ( m_Dlg->CheckRemarksColumn() == FALSE ) {
		m_Dlg->StatusStringSet(_T("備考欄にはデータは存在しません"),500,TRUE);
		m_xvRadioRemarksColumn=2;
		UpdateData(FALSE);
	}
}


void HTML_Dlg::OnBnClickedRadioRemarkscolumninvisible()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();
	
	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if ( m_Dlg->CheckRemarksColumn() == FALSE ) {
		m_Dlg->StatusStringSet(_T("備考欄にはデータは存在しません"),500,TRUE);
		m_xvRadioRemarksColumn=2;
		UpdateData(FALSE);
	}
}


void HTML_Dlg::OnBnClickedCancel()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	//CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();
	//
	//if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
	//	return;
	//}

	//m_Dlg->StatusStringSet(_T("Export キャンセル"),0,TRUE);

	CDialogEx::OnCancel();
}
