// HTML_Dlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "FileListCreator.h"
#include "FileListCreatorDlg.h"//�ǉ�

#include "HTML_Dlg.h"
#include "afxdialogex.h"



// HTML_Dlg �_�C�A���O

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


// HTML_Dlg ���b�Z�[�W �n���h���[


void HTML_Dlg::OnBnClickedButtonDefault2()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	m_xvRadioModifyDate=1;
	m_xvRadioRemarksColumn=2;
	m_xvChkCopyOn=TRUE;
	m_xvChkRedOn=TRUE;
	m_xvRadioENCODING_SELECT=0;
	UpdateData(FALSE);
}


void HTML_Dlg::OnBnClickedCheckCopyFuncOn()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	if (m_xvChkCopyOn == FALSE){
		m_xvChkCopyOn = TRUE;
	}else{
		m_xvChkCopyOn = FALSE;
	}
}


void HTML_Dlg::OnBnClickedCheckStrredOn()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	if (m_xvChkRedOn == FALSE){
		m_xvChkRedOn = TRUE;
	}else{
		m_xvChkRedOn = FALSE;
	}
}


void HTML_Dlg::OnBnClickedOk()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CDialogEx::OnOK();


	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->g_RadioModifyDate=m_xvRadioModifyDate;
	m_Dlg->g_RadioRemarksColumn=m_xvRadioRemarksColumn;
	m_Dlg->g_ChkCopyOn=m_xvChkCopyOn;
	m_Dlg->g_ChkRedOn=m_xvChkRedOn;
	m_Dlg->g_RadioENCODING_SELECT=m_xvRadioENCODING_SELECT; //�ǉ� 2012.04.21
	
	//m_Dlg->ExportFileList();

	//m_Dlg->g_NoDrawFLG = TRUE;

}


void HTML_Dlg::OnBnClickedRadioRemarkscolumnvisible()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if ( m_Dlg->CheckRemarksColumn() == FALSE ) {
		m_Dlg->StatusStringSet(_T("���l���ɂ̓f�[�^�͑��݂��܂���"),500,TRUE);
		m_xvRadioRemarksColumn=2;
		UpdateData(FALSE);
	}
}


void HTML_Dlg::OnBnClickedRadioRemarkscolumninvisible()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();
	
	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if ( m_Dlg->CheckRemarksColumn() == FALSE ) {
		m_Dlg->StatusStringSet(_T("���l���ɂ̓f�[�^�͑��݂��܂���"),500,TRUE);
		m_xvRadioRemarksColumn=2;
		UpdateData(FALSE);
	}
}


void HTML_Dlg::OnBnClickedCancel()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	//CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();
	//
	//if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
	//	return;
	//}

	//m_Dlg->StatusStringSet(_T("Export �L�����Z��"),0,TRUE);

	CDialogEx::OnCancel();
}
