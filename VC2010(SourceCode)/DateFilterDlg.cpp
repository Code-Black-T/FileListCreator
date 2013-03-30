// DateFilterDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "FileListCreator.h"

//�ǉ���
#include "FileListCreatorDlg.h"
#include <time.h>//�s�v�H
//�ǉ���

#include "DateFilterDlg.h"
#include "afxdialogex.h"


// DateFilterDlg �_�C�A���O

IMPLEMENT_DYNAMIC(DateFilterDlg, CDialogEx)

DateFilterDlg::DateFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DateFilterDlg::IDD, pParent)
	, m_xvChkDateSpan(FALSE)
	, m_xvChkTargetDate(FALSE)
{

}

DateFilterDlg::~DateFilterDlg()
{
}

void DateFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_StartDate, m_xcCombo_StartDate);
	DDX_Control(pDX, IDC_COMBO_EndDate, m_xcCombo_EndDate);
	DDX_Control(pDX, IDC_COMBO_TargetDate, m_xcCombo_TargetDate);
	DDX_Check(pDX, IDC_CHECK_DateSpan, m_xvChkDateSpan);
	DDX_Check(pDX, IDC_CHECK_TargetDate, m_xvChkTargetDate);
}


BEGIN_MESSAGE_MAP(DateFilterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &DateFilterDlg::OnBnClickedOk)
	ON_BN_CLICKED(ID_BTN_TargetRed, &DateFilterDlg::OnBnClickedBtnTargetred)
	ON_BN_CLICKED(ID_BTN_OverwriteDate, &DateFilterDlg::OnBnClickedBtnOverwritedate)
	ON_BN_CLICKED(ID_BTN_TargetBold, &DateFilterDlg::OnBnClickedBtnTargetbold)
	ON_BN_CLICKED(ID_BTN_ExcludeLIST_1, &DateFilterDlg::OnBnClickedBtnExcludelist1)
	ON_BN_CLICKED(ID_BTN_ExcludeLIST_2, &DateFilterDlg::OnBnClickedBtnExcludelist2)
	ON_BN_CLICKED(ID_BTN_FormatCancellation, &DateFilterDlg::OnBnClickedBtnFormatcancellation)
	ON_BN_CLICKED(ID_BTN_AllDateClear, &DateFilterDlg::OnBnClickedBtnAlldateclear)
	ON_BN_CLICKED(ID_BTN_Date_SetToday, &DateFilterDlg::OnBnClickedBtnDateSettoday)
	ON_BN_CLICKED(IDCANCEL, &DateFilterDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_DateSpan, &DateFilterDlg::OnBnClickedCheckDatespan)
	ON_BN_CLICKED(IDC_CHECK_TargetDate, &DateFilterDlg::OnBnClickedCheckTargetdate)
	ON_CBN_SETFOCUS(IDC_COMBO_StartDate, &DateFilterDlg::OnCbnSetfocusComboStartdate)
	ON_CBN_SETFOCUS(IDC_COMBO_EndDate, &DateFilterDlg::OnCbnSetfocusComboEnddate)
	ON_CBN_SETFOCUS(IDC_COMBO_TargetDate, &DateFilterDlg::OnCbnSetfocusComboTargetdate)
END_MESSAGE_MAP()


// DateFilterDlg ���b�Z�[�W �n���h���[


BOOL DateFilterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return FALSE;
	}

	ReadOrWriteComboData_Func(_T("read"));

	return TRUE;
}

void DateFilterDlg::ExistCheckFunc(CString mySwitch)
{
	if (mySwitch==_T("TargetDate")){
		BOOL tempFLG = TRUE;
		CString EditData;
		DateFilterDlg::m_xcCombo_TargetDate.GetWindowText(EditData);

		//if(EditData !=_T("")){
			int k = 0;
	
			int k2 = 0;

			while (k <= DateFilterDlg::m_xcCombo_TargetDate.GetCount() -1){
				CString ComboText;
				DateFilterDlg::m_xcCombo_TargetDate.GetLBText(k, ComboText); // �C���f�b�N�Xk�Ԗڂ̕�������擾

				if(ComboText == EditData){
					DateFilterDlg::m_xcCombo_TargetDate.SetCurSel(k);
					k2 = k;
					tempFLG = FALSE;
				}
				k++;
			}

			if(tempFLG == TRUE){
				DateFilterDlg::m_xcCombo_TargetDate.InsertString(0,EditData);
				DateFilterDlg::m_xcCombo_TargetDate.SetCurSel(0);
			}else{
				DateFilterDlg::m_xcCombo_TargetDate.DeleteString(k2);
				DateFilterDlg::m_xcCombo_TargetDate.InsertString(0,EditData);
				DateFilterDlg::m_xcCombo_TargetDate.SetCurSel(0);
			}

			for(k = DateFilterDlg::m_xcCombo_TargetDate.GetCount();k>=ComboBox_MAX;k--){
				DateFilterDlg::m_xcCombo_TargetDate.DeleteString(k);
			}
		//}
	}else if (mySwitch==_T("StartDate")){
		BOOL tempFLG = TRUE;
		CString EditData;
		DateFilterDlg::m_xcCombo_StartDate.GetWindowText(EditData);

		//if(EditData !=_T("")){
			int k = 0;
	
			int k2 = 0;

			while (k <= DateFilterDlg::m_xcCombo_StartDate.GetCount() -1){
				CString ComboText;
				DateFilterDlg::m_xcCombo_StartDate.GetLBText(k, ComboText); // �C���f�b�N�Xk�Ԗڂ̕�������擾

				if(ComboText == EditData){
					DateFilterDlg::m_xcCombo_StartDate.SetCurSel(k);
					k2 = k;
					tempFLG = FALSE;
				}
				k++;
			}

			if(tempFLG == TRUE){
				DateFilterDlg::m_xcCombo_StartDate.InsertString(0,EditData);
				DateFilterDlg::m_xcCombo_StartDate.SetCurSel(0);
			}else{
				DateFilterDlg::m_xcCombo_StartDate.DeleteString(k2);
				DateFilterDlg::m_xcCombo_StartDate.InsertString(0,EditData);
				DateFilterDlg::m_xcCombo_StartDate.SetCurSel(0);
			}

			for(k = DateFilterDlg::m_xcCombo_StartDate.GetCount();k>=ComboBox_MAX;k--){
				DateFilterDlg::m_xcCombo_StartDate.DeleteString(k);
			}
		//}
	}else if (mySwitch==_T("EndDate")){
		BOOL tempFLG = TRUE;
		CString EditData;
		DateFilterDlg::m_xcCombo_EndDate.GetWindowText(EditData);

		//if(EditData !=_T("")){
			int k = 0;
	
			int k2 = 0;

			while (k <= DateFilterDlg::m_xcCombo_EndDate.GetCount() -1){
				CString ComboText;
				DateFilterDlg::m_xcCombo_EndDate.GetLBText(k, ComboText); // �C���f�b�N�Xk�Ԗڂ̕�������擾

				if(ComboText == EditData){
					DateFilterDlg::m_xcCombo_EndDate.SetCurSel(k);
					k2 = k;
					tempFLG = FALSE;
				}
				k++;
			}

			if(tempFLG == TRUE){
				DateFilterDlg::m_xcCombo_EndDate.InsertString(0,EditData);
				DateFilterDlg::m_xcCombo_EndDate.SetCurSel(0);
			}else{
				DateFilterDlg::m_xcCombo_EndDate.DeleteString(k2);
				DateFilterDlg::m_xcCombo_EndDate.InsertString(0,EditData);
				DateFilterDlg::m_xcCombo_EndDate.SetCurSel(0);
			}

			for(k = DateFilterDlg::m_xcCombo_EndDate.GetCount();k>=ComboBox_MAX;k--){
				DateFilterDlg::m_xcCombo_EndDate.DeleteString(k);
			}
		//}
	}
}

void DateFilterDlg::ReadOrWriteComboData_Func(CString mySwitch)
{
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	CString WriteData1;
	CString WriteData2;
	CString WriteData3;

	if (mySwitch == _T("write")){ //write
		int k;

		k = 0;
		WriteData1 = _T("");

		while (k <= DateFilterDlg::m_xcCombo_TargetDate.GetCount() -1){
			CString ComboText;
			DateFilterDlg::m_xcCombo_TargetDate.GetLBText(k, ComboText); // �C���f�b�N�X0�Ԗڂ̕�������擾
			if(k<=ComboBox_MAX){
				WriteData1 = WriteData1 + ComboText + _T("\n");
			}
			k++;
		}

		k = 0;
		WriteData2 = _T("");

		while (k <= DateFilterDlg::m_xcCombo_StartDate.GetCount() -1){
			CString ComboText;
			DateFilterDlg::m_xcCombo_StartDate.GetLBText(k, ComboText); // �C���f�b�N�X0�Ԗڂ̕�������擾
			if(k<=ComboBox_MAX){
				WriteData2 = WriteData2 + ComboText + _T("\n");
			}
			k++;
		}

		k = 0;
		WriteData3 = _T("");

		while (k <= DateFilterDlg::m_xcCombo_EndDate.GetCount() -1){
			CString ComboText;
			DateFilterDlg::m_xcCombo_EndDate.GetLBText(k, ComboText); // �C���f�b�N�X0�Ԗڂ̕�������擾
			if(k<=ComboBox_MAX){
				WriteData3 = WriteData3 + ComboText + _T("\n");
			}
			k++;
		}
	}

	CStdioFile    stdFile1;
	CString       wstr, rstr;
	LPTSTR        rstrBuf = NULL;
	int           err = 0;

	// (1)�ǂݏ����p�ɃI�[�v��
	if (!err)
	{
		//// �J�����g�f�B���N�g���̎擾
		//TCHAR szCurrentDir[_MAX_PATH];
		//GetCurrentDirectory(_MAX_PATH,szCurrentDir);
	
		//CString CurDir;
		//CurDir = szCurrentDir;

		//http://rararahp.cool.ne.jp/vc/vctips/api.htm
		// ���s�t�@�C���̃t���p�X�擾
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
			if (!stdFile1.Open(CurDir + _T("\\TargetDate.dat"), 
				CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::modeNoTruncate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText
		}
		if (mySwitch == _T("write")){
			if (!stdFile1.Open(CurDir + _T("\\TargetDate.dat"), 
				CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText
		}
	}


	if(mySwitch == _T("write")){ //write
		// (2)��������
		if (!err)
		{
			wstr = WriteData1;

			TRY {stdFile1.WriteString(wstr);}
			CATCH (CFileException, eP) {err = 1;}
			END_CATCH
		}
		// (6)�N���[�Y(�����I)
		stdFile1.Close();
	}


	//2�ڂ̃t�@�C�����I�[�v��

	CStdioFile    stdFile2;
	//CString       wstr, rstr;

	//LPTSTR        rstrBuf = NULL;
	rstrBuf = NULL;
	//int           err = 0;
	err = 0;

	// (1)�ǂݏ����p�ɃI�[�v��
	if (!err)
	{
		//// �J�����g�f�B���N�g���̎擾
		//TCHAR szCurrentDir[_MAX_PATH];
		//GetCurrentDirectory(_MAX_PATH,szCurrentDir);
	
		//CString CurDir;
		//CurDir = szCurrentDir;

		//http://rararahp.cool.ne.jp/vc/vctips/api.htm
		// ���s�t�@�C���̃t���p�X�擾
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
			if (!stdFile2.Open(CurDir + _T("\\StartDate.dat"), 
				CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::modeNoTruncate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText
		}
		if (mySwitch == _T("write")){
			if (!stdFile2.Open(CurDir + _T("\\StartDate.dat"), 
				CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText
		}
	}


	if(mySwitch == _T("write")){ //write
		// (2)��������
		if (!err)
		{
			wstr = WriteData2;

			TRY {stdFile2.WriteString(wstr);}
			CATCH (CFileException, eP) {err = 1;}
			END_CATCH
		}
		// (6)�N���[�Y(�����I)
		stdFile2.Close();
	}


	//3�ڂ̃t�@�C�����I�[�v��

	CStdioFile    stdFile3;
	//CString       wstr, rstr;

	//LPTSTR        rstrBuf = NULL;
	rstrBuf = NULL;
	//int           err = 0;
	err = 0;

	// (1)�ǂݏ����p�ɃI�[�v��
	if (!err)
	{
		//// �J�����g�f�B���N�g���̎擾
		//TCHAR szCurrentDir[_MAX_PATH];
		//GetCurrentDirectory(_MAX_PATH,szCurrentDir);
	
		//CString CurDir;
		//CurDir = szCurrentDir;

		//http://rararahp.cool.ne.jp/vc/vctips/api.htm
		// ���s�t�@�C���̃t���p�X�擾
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
			if (!stdFile3.Open(CurDir + _T("\\EndDate.dat"), 
				CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::modeNoTruncate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText
		}
		if (mySwitch == _T("write")){
			if (!stdFile3.Open(CurDir + _T("\\EndDate.dat"), 
				CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText
		}
	}


	if(mySwitch == _T("write")){ //write
		// (2)��������
		if (!err)
		{
			wstr = WriteData3;

			TRY {stdFile3.WriteString(wstr);}
			CATCH (CFileException, eP) {err = 1;}
			END_CATCH
		}
		// (6)�N���[�Y(�����I)
		stdFile3.Close();
	}

	if(mySwitch == _T("read")){ //read
		int k;
		k = 0;
		while (!err) {
			if (stdFile1.ReadString(rstr) == FALSE) err = 1;
			if (!err && (k<ComboBox_MAX)){
				DateFilterDlg::m_xcCombo_TargetDate.InsertString(k,rstr);
			}

			k++;
		}
		DateFilterDlg::m_xcCombo_TargetDate.SetCurSel(0);

		err=0;
		k = 0;
		while (!err) {
			if (stdFile2.ReadString(rstr) == FALSE) err = 1;
			if (!err && (k<ComboBox_MAX)){
				DateFilterDlg::m_xcCombo_StartDate.InsertString(k,rstr);
			}

			k++;
		}
		DateFilterDlg::m_xcCombo_StartDate.SetCurSel(0);

		err=0;
		k = 0;
		while (!err) {
			if (stdFile3.ReadString(rstr) == FALSE) err = 1;
			if (!err && (k<ComboBox_MAX)){ //�ύX 2012.07.11
				DateFilterDlg::m_xcCombo_EndDate.InsertString(k,rstr);
			}

			k++;
		}
		DateFilterDlg::m_xcCombo_EndDate.SetCurSel(0);

		// (6)�N���[�Y(�����I)
		stdFile1.Close();
		stdFile2.Close();
		stdFile3.Close();
	}
}


void DateFilterDlg::OnBnClickedOk()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CDialogEx::OnOK();
}


BOOL DateFilterDlg::DateMatch(int workRow, CString mySwitch,CString strTargetDate,CString strStartDate,CString strEndDate)
{
	//LVITEM       lvi;
	//int          index = 0;
	int          err = 0;
	CString      str;	
	CString      FullPathString;

	//CString myFileName;
	//CString myFileSize;
	//ULONGLONG myLongFileSize;
	CString myDate;
	CString myTime;

	//CString tempDate;	

	FullPathString =_T("");

	//myFileName=_T("");
	//myFileSize = _T("");
	//myLongFileSize = -1;
	myDate = _T("");
	myTime = _T("");
   
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return FALSE;
	}

	m_Dlg->lvi.mask = LVIF_TEXT;

	//CString strStartDate;
	//CString strEndDate;

	//CString strTargetDate;

	FullPathString = m_Dlg->m_xcList.GetItemText(workRow,2);
	if (FullPathString !=_T("")){
		FullPathString.Replace(_T("%"),_T("%%"));
	}

	CTime cTime;
	CFile* pFile = NULL;
	CString workDate;


	CString EditDate;
	EditDate = m_Dlg->m_xcList.GetItemText(workRow, 6);

	//m_Dlg->GetStrFormat_Func();

	BOOL ParseDateFLG;

	ParseDateFLG = FALSE;

	workDate = m_Dlg->m_xcList.GetItemText(workRow, 7);
	if(workDate != _T("")){
		COleDateTime pd;
		//char * p = tempDate;
		if( pd.ParseDateTime( workDate ))
		{
			myDate = pd.Format(_T("%Y/%m/%d"));
			myTime = pd.Format(_T("%Y/%m/%d %H:%M:%S")); //Format(tdate, "yyyy/mm/dd")
										//Format(tdate, "yyyy/mm/dd hh:mm:ss")
			ParseDateFLG = TRUE;
		}
		else
		{
			TRACE("��͕s�\\n");
			ParseDateFLG = FALSE;
		}
	}else{
		ParseDateFLG = FALSE;
	}

    if (ParseDateFLG == FALSE) { //EditDate == _T("") || //�R�����g�� 2012.06.01

        //if (m_Dlg->ProhibitFileName(FullPathString, TRUE)) {
            m_Dlg->fileUpdatedRecently(FullPathString, workRow); //�R�����g�� 2012.06.01
		//}
        
        //Worksheets("FileList").Cells(6 + workRow, 8).Value = myDate;
	}
    
    //myDate = CDate(Worksheets("FileList").Cells(6 + workRow, 8).Value)

	CTime StartDate;
	CTime EndDate;
	CTime TargetDate;

	StartDate = m_Dlg->CStringToDate(strStartDate);
	EndDate = m_Dlg->CStringToDate(strEndDate);
	TargetDate = m_Dlg->CStringToDate(strTargetDate);

	//int FormatDataNum =11;

	//m_Dlg->GetStrFormat_Func();
	int FormatDataNum = m_Dlg->m_xcList.GetItemData(workRow);

	//CString FormatDataStr = m_Dlg->m_xcList.GetItemText(workRow,9);
	CString FormatDataStr;

	//m_Dlg->m_xcList.SetItemData(workRow,FormatDataNum);

	if (mySwitch == _T("Red") || mySwitch == _T("Bold")) {
		if (ParseDateFLG == TRUE) {
			if (strStartDate!=_T("") && strEndDate!=_T("") && myDate!=_T("") && m_xvChkDateSpan == TRUE){
				if ( StartDate<=m_Dlg->CStringToDate(myDate) && m_Dlg->CStringToDate(myDate)<=EndDate) {
					if (mySwitch == _T("Red")){
						FormatDataNum = m_Dlg->SetToRed(FormatDataNum);

						m_Dlg->ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13
					}
					if (mySwitch == _T("Bold")){
						FormatDataNum = m_Dlg->SetToBold(FormatDataNum);

						m_Dlg->ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13
					}
				}
			}
		}

		if (ParseDateFLG == TRUE) {
			if (strStartDate!=_T("") && myDate!=_T("") && strEndDate==_T("") && m_xvChkDateSpan == TRUE){
				if ( StartDate <= m_Dlg->CStringToDate(myDate)){
					if (mySwitch == _T("Red")){
						FormatDataNum = m_Dlg->SetToRed(FormatDataNum);

						m_Dlg->ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13
					}
					if (mySwitch == _T("Bold")){
						FormatDataNum = m_Dlg->SetToBold(FormatDataNum);

						m_Dlg->ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13
					}
				}
			}
		}

		if (ParseDateFLG == TRUE) {
			if (strEndDate!=_T("") && myDate!=_T("") && strStartDate==_T("") && m_xvChkDateSpan == TRUE){
				if (m_Dlg->CStringToDate(myDate) <= EndDate) {
					if (mySwitch == _T("Red")){
						FormatDataNum = m_Dlg->SetToRed(FormatDataNum);

						m_Dlg->ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13
					}
					if (mySwitch == _T("Bold")){
						FormatDataNum = m_Dlg->SetToBold(FormatDataNum);

						m_Dlg->ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13
					}
				}
			}
		}

		if (ParseDateFLG == TRUE) {
			if (strTargetDate!=_T("") && myDate!=_T("") && m_xvChkTargetDate == TRUE){
				if (m_Dlg->CStringToDate(myDate) == TargetDate) {
					//MessageBox (_T("���t���������G") + myDate);
					if (mySwitch == _T("Red")){
						FormatDataNum = m_Dlg->SetToRed(FormatDataNum);

						m_Dlg->ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13
					}
					if (mySwitch == _T("Bold")){
						FormatDataNum = m_Dlg->SetToBold(FormatDataNum);

						m_Dlg->ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13
					}
				}
			}

		}
	}


	BOOL DEL_FLG;
	DEL_FLG = FALSE;

	if (mySwitch == _T("ExcludeLIST")) {
		//FormatDataNum = m_Dlg->m_xcList.GetItemData(workRow);
		DEL_FLG = FALSE;

		if (myDate != _T("")){
    
			//if (ParseDateFLG == TRUE) {
			//	//������ ������
			//	if (strStartDate!=_T("") && myDate!=_T("") && strEndDate == _T("") && strTargetDate == _T("")){
			//		if (StartDate <= m_Dlg->CStringToDate(myDate)){
			//			DEL_FLG = TRUE;
			//		}
			//	}
			//}
    
			if (ParseDateFLG == TRUE) {
				if (strStartDate!=_T("") && myDate!=_T("")  && m_xvChkDateSpan == TRUE){
					if (StartDate > m_Dlg->CStringToDate(myDate)) {
						DEL_FLG = TRUE;
					}
				}
			}
    
			if (ParseDateFLG == TRUE ) {//&& IsDate(EndDate
				if (strEndDate!=_T("") && myDate!=_T("") &&  m_xvChkDateSpan == TRUE){
					if (m_Dlg->CStringToDate(myDate) > EndDate) { 
						DEL_FLG = TRUE;
					}
				}
			}
    
			if (ParseDateFLG == TRUE) {
				if (strTargetDate!=_T("") && myDate!=_T("")  && m_xvChkTargetDate == TRUE){
				   if(m_Dlg->CStringToDate(myDate)!= TargetDate) {
						DEL_FLG = TRUE;
				   }
				}
			}
		}
    
		m_Dlg->ListDataNoChange_FLG = !DEL_FLG;

		if (DEL_FLG == TRUE){
			//m_Dlg->m_xcList.DeleteItem(workRow);
			return TRUE;
		}

	}

	if (mySwitch == _T("ExcludeLIST2")) {
   
		DEL_FLG = FALSE;

		if (ParseDateFLG == TRUE) {
			//FormatDataNum = m_Dlg->m_xcList.GetItemData(workRow);
			if (FormatDataNum == 11) {
				DEL_FLG = TRUE;
			}
		}

		m_Dlg->ListDataNoChange_FLG = !DEL_FLG;

		if (DEL_FLG == TRUE){
			//m_Dlg->m_xcList.DeleteItem(workRow);
			return TRUE;
		}
	}

	if (mySwitch == _T("FormatCancellation")) {
		FormatDataNum =11;
		//m_Dlg->m_xcList.SetItemData(workRow,FormatDataNum);
	}

	m_Dlg->m_xcList.SetItemData(workRow,FormatDataNum);

	FormatDataStr = _T("NORMAL,BLACK,");

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


	//m_Dlg->ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13


	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}


	if (DEL_FLG == TRUE){ //OnLvnDeleteitemList()
		return TRUE;
	}else{
		return FALSE;
	}
}



void DateFilterDlg::EmphasisByDate(CString mySwitch)
{
	//LVITEM       lvi;
	//int          index = 0;
	int          err = 0;
	CString      str;	
	CString      FullPathString;

	//CString myFileName;
	//CString myFileSize;
	//ULONGLONG myLongFileSize;
	CString myDate;
	CString myTime;

	//CString tempDate;	

	FullPathString =_T("");

	//myFileName=_T("");
	//myFileSize = _T("");
	//myLongFileSize = -1;
	myDate = _T("");
	myTime = _T("");

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->lvi.mask = LVIF_TEXT;// | LVIF_PARAM;


	CString strStartDate;
	CString strEndDate;

	CString strTargetDate;

	((CComboBox*)GetDlgItem(IDC_COMBO_TargetDate))->GetWindowText(strTargetDate);
    ((CComboBox*)GetDlgItem(IDC_COMBO_StartDate))->GetWindowText(strStartDate);
	((CComboBox*)GetDlgItem(IDC_COMBO_EndDate))->GetWindowText(strEndDate);

	m_Dlg->GetStrFormat_Func();

    //BOOL tempFLG;
    
    int workRow=0;

	//myDate = m_Dlg->m_xcList.GetItemText(workRow,6);
	//myTime = m_Dlg->m_xcList.GetItemText(workRow,7);

    if (mySwitch == _T("Red")) {
        workRow = 0;
        while (workRow < m_Dlg->m_xcList.GetItemCount()) {
            if (m_Dlg->m_xcList.GetItemText(workRow,6)==_T("")||m_Dlg->m_xcList.GetItemText(workRow,7)==_T("")) {
				FullPathString = m_Dlg->m_xcList.GetItemText(workRow,2);
                m_Dlg->fileUpdatedRecently(FullPathString, workRow);
			}
            DateMatch(workRow, mySwitch,strTargetDate,strStartDate,strEndDate);
            workRow++;
		}
    }
    
    if (mySwitch == _T("Bold")) {
        workRow = 0;
        while (workRow < m_Dlg->m_xcList.GetItemCount()) {
            if (m_Dlg->m_xcList.GetItemText(workRow,6)==_T("")||m_Dlg->m_xcList.GetItemText(workRow,7)==_T("")) {
				FullPathString = m_Dlg->m_xcList.GetItemText(workRow,2);
                m_Dlg->fileUpdatedRecently(FullPathString, workRow);
			}
            DateMatch(workRow, mySwitch,strTargetDate,strStartDate,strEndDate);
            workRow++;
        }
    }

    if (mySwitch == _T("ExcludeLIST")) {
        workRow = 0;
        
        while (workRow < m_Dlg->m_xcList.GetItemCount()) {
            if (m_Dlg->m_xcList.GetItemText(workRow,6)==_T("")||m_Dlg->m_xcList.GetItemText(workRow,7)==_T("")) {
				FullPathString = m_Dlg->m_xcList.GetItemText(workRow,2);
                m_Dlg->fileUpdatedRecently(FullPathString, workRow);
			}            
            if (DateMatch(workRow, mySwitch,strTargetDate,strStartDate,strEndDate) == TRUE){
				m_Dlg->m_xcList.EnsureVisible(workRow, FALSE); //�ǉ� 2012.04.04  //�R�����g�� 2012.06.10
				m_Dlg->ItemCount_Func(TRUE); //�ǉ�2012.04.04

				m_Dlg->m_xcList.DeleteItem(workRow);
			}else{
				workRow++;
			}
        }
		m_Dlg->SetSEQ_NUM_Func(TRUE);
    }

	if ( mySwitch == _T("ExcludeLIST2") ){
		int FormatDataNum;

		workRow = 0;

		while (workRow<m_Dlg->m_xcList.GetItemCount()){
			FormatDataNum = m_Dlg->m_xcList.GetItemData(workRow);
			if ( FormatDataNum == 11) {
				m_Dlg->m_xcList.EnsureVisible(workRow, FALSE); //�ǉ� 2012.04.04  //�R�����g�� 2012.06.10
				m_Dlg->ItemCount_Func(TRUE); //�ǉ�2012.04.04

				m_Dlg->m_xcList.DeleteItem(workRow);
			}else{
				workRow++;
			}
		}
		m_Dlg->SetSEQ_NUM_Func(TRUE);
	}



    if (mySwitch == _T("FormatCancellation")) {
        workRow = 0;
        
        while (workRow < m_Dlg->m_xcList.GetItemCount()) {
            if (m_Dlg->m_xcList.GetItemText(workRow,6)==_T("")||m_Dlg->m_xcList.GetItemText(workRow,7)==_T("")) {
				FullPathString = m_Dlg->m_xcList.GetItemText(workRow,2);
                m_Dlg->fileUpdatedRecently(FullPathString, workRow);
			}            
            DateMatch(workRow, mySwitch,strTargetDate,strStartDate,strEndDate);
            workRow++;
        }
    }
    
	m_Dlg->SetStrFormat_Func();

	m_Dlg->Total_Bytes_Bold();
	m_Dlg->Total_Bytes_Func();
	m_Dlg->ItemCount_Func(TRUE);
}


void DateFilterDlg::OnBnClickedBtnTargetred()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	if(m_xvChkDateSpan != TRUE && m_xvChkTargetDate != TRUE){
		MessageBox(_T("Span �� Target �� �`�F�b�N�����Ă�������") ,_T("�`�F�b�N���ݒ�"), MB_OK );
		return;
	}

	CString StartDate;
	CString EndDate;
	CString TargetDate;

	((CComboBox*)GetDlgItem(IDC_COMBO_TargetDate))->GetWindowText(TargetDate);
    ((CComboBox*)GetDlgItem(IDC_COMBO_StartDate))->GetWindowText(StartDate);
	((CComboBox*)GetDlgItem(IDC_COMBO_EndDate))->GetWindowText(EndDate);

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount();
	m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	if(m_Dlg->m_xcList.GetItemCount() < 1) {
		m_Dlg->StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
	}else{
		m_Dlg->StatusStringSet(_T("DateFilter ���s��"),0,FALSE); //�ύX 2012.06.14

		EmphasisByDate(_T("Red"));
	}

	m_Dlg->StatusStringSet(_T("DateFilter �I��"),300,TRUE);

	UpdateData(FALSE);

	m_xcCombo_TargetDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(TargetDate)));
	m_xcCombo_StartDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(StartDate)));
	m_xcCombo_EndDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(EndDate)));

	ExistCheckFunc(_T("TargetDate"));

	ExistCheckFunc(_T("StartDate"));
	ExistCheckFunc(_T("EndDate"));

	ReadOrWriteComboData_Func(_T("write"));
	RedrawWindow();  //UpdateWindow();����ύX //�ύX 2012.06.01
}


void DateFilterDlg::OnBnClickedBtnOverwritedate()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

    int workRow=0;
	CString FullPathString=_T("");

    workRow = 0;
    while (workRow < m_Dlg->m_xcList.GetItemCount()) {
        if (m_Dlg->m_xcList.GetItemText(workRow,6)==_T("")||m_Dlg->m_xcList.GetItemText(workRow,7)==_T("")) {
			FullPathString = m_Dlg->m_xcList.GetItemText(workRow,2);
			//FullPathString.Replace(_T("%"),_T("%%"));
            
			m_Dlg->fileUpdatedRecently(FullPathString, workRow);
		}
        workRow++;
	}
}


void DateFilterDlg::OnBnClickedBtnTargetbold()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	if(m_xvChkDateSpan != TRUE && m_xvChkTargetDate != TRUE){
		MessageBox(_T("Span �� Target �� �`�F�b�N�����Ă�������") ,_T("�`�F�b�N���ݒ�"), MB_OK );
		return;
	}

	CString StartDate;
	CString EndDate;
	CString TargetDate;

	((CComboBox*)GetDlgItem(IDC_COMBO_TargetDate))->GetWindowText(TargetDate);
    ((CComboBox*)GetDlgItem(IDC_COMBO_StartDate))->GetWindowText(StartDate);
	((CComboBox*)GetDlgItem(IDC_COMBO_EndDate))->GetWindowText(EndDate);

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount();
	m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	if(m_Dlg->m_xcList.GetItemCount() < 1) {
		m_Dlg->StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
	}else{
		m_Dlg->StatusStringSet(_T("DateFilter ���s��"),0,FALSE); //�ύX 2012.06.14

		EmphasisByDate(_T("Bold"));
	}

	m_Dlg->StatusStringSet(_T("DateFilter �I��"),300,TRUE);

	UpdateData(FALSE);

	m_xcCombo_TargetDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(TargetDate)));
	m_xcCombo_StartDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(StartDate)));
	m_xcCombo_EndDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(EndDate)));

	ExistCheckFunc(_T("TargetDate"));

	ExistCheckFunc(_T("StartDate"));
	ExistCheckFunc(_T("EndDate"));

	ReadOrWriteComboData_Func(_T("write"));
	RedrawWindow();  //UpdateWindow();����ύX //�ύX 2012.06.01
}


void DateFilterDlg::OnBnClickedBtnExcludelist1()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	if(m_xvChkDateSpan != TRUE && m_xvChkTargetDate != TRUE){
		MessageBox(_T("Span �� Target �� �`�F�b�N�����Ă�������") ,_T("�`�F�b�N���ݒ�"), MB_OK );
		return;
	}

	CString StartDate;
	CString EndDate;
	CString TargetDate;

	((CComboBox*)GetDlgItem(IDC_COMBO_TargetDate))->GetWindowText(TargetDate);
    ((CComboBox*)GetDlgItem(IDC_COMBO_StartDate))->GetWindowText(StartDate);
	((CComboBox*)GetDlgItem(IDC_COMBO_EndDate))->GetWindowText(EndDate);

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount();
	m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	if(m_Dlg->m_xcList.GetItemCount() < 1) {
		m_Dlg->StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
	}else{
		m_Dlg->StatusStringSet(_T("DateFilter ���s��"),0,FALSE); //�ύX 2012.06.14

		EmphasisByDate(_T("ExcludeLIST"));
	}

	m_Dlg->StatusStringSet(_T("DateFilter �I��"),300,TRUE);

	UpdateData(FALSE);

	m_xcCombo_TargetDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(TargetDate)));
	m_xcCombo_StartDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(StartDate)));
	m_xcCombo_EndDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(EndDate)));

	ExistCheckFunc(_T("TargetDate"));

	ExistCheckFunc(_T("StartDate"));
	ExistCheckFunc(_T("EndDate"));

	ReadOrWriteComboData_Func(_T("write"));
	RedrawWindow();  //UpdateWindow();����ύX //�ύX 2012.06.01
}


void DateFilterDlg::OnBnClickedBtnExcludelist2()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	CString StartDate;
	CString EndDate;
	CString TargetDate;

	((CComboBox*)GetDlgItem(IDC_COMBO_TargetDate))->GetWindowText(TargetDate);
    ((CComboBox*)GetDlgItem(IDC_COMBO_StartDate))->GetWindowText(StartDate);
	((CComboBox*)GetDlgItem(IDC_COMBO_EndDate))->GetWindowText(EndDate);

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount();
	m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	if(m_Dlg->m_xcList.GetItemCount() < 1) {
		m_Dlg->StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
	}else{
		m_Dlg->StatusStringSet(_T("DateFilter ���s��"),0,FALSE); //�ύX 2012.06.14

		EmphasisByDate(_T("ExcludeLIST2"));
	}

	m_Dlg->StatusStringSet(_T("DateFilter �I��"),300,TRUE);

	UpdateData(FALSE);

	m_xcCombo_TargetDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(TargetDate)));
	m_xcCombo_StartDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(StartDate)));
	m_xcCombo_EndDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(EndDate)));

	ExistCheckFunc(_T("TargetDate"));

	ExistCheckFunc(_T("StartDate"));
	ExistCheckFunc(_T("EndDate"));

	ReadOrWriteComboData_Func(_T("write"));
	RedrawWindow();  //UpdateWindow();����ύX //�ύX 2012.06.01
}


void DateFilterDlg::OnBnClickedBtnFormatcancellation()
{

	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	CString StartDate;
	CString EndDate;
	CString TargetDate;

	((CComboBox*)GetDlgItem(IDC_COMBO_TargetDate))->GetWindowText(TargetDate);
    ((CComboBox*)GetDlgItem(IDC_COMBO_StartDate))->GetWindowText(StartDate);
	((CComboBox*)GetDlgItem(IDC_COMBO_EndDate))->GetWindowText(EndDate);

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount();
	m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	if(m_Dlg->m_xcList.GetItemCount() < 1) {
		m_Dlg->StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
	}else{
		m_Dlg->StatusStringSet(_T("DateFilter ���s��"),0,FALSE); //�ύX 2012.06.14

		EmphasisByDate(_T("FormatCancellation"));

	}

	m_Dlg->StatusStringSet(_T("DateFilter �I��"),300,TRUE);

	UpdateData(FALSE);

	m_xcCombo_TargetDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(TargetDate)));
	m_xcCombo_StartDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(StartDate)));
	m_xcCombo_EndDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(EndDate)));

	ExistCheckFunc(_T("TargetDate"));

	ExistCheckFunc(_T("StartDate"));
	ExistCheckFunc(_T("EndDate"));

	ReadOrWriteComboData_Func(_T("write"));

	RedrawWindow();  //UpdateWindow();����ύX //�ύX 2012.06.01
}


void DateFilterDlg::OnBnClickedBtnAlldateclear()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	m_xcCombo_TargetDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(_T(""))));
	m_xcCombo_StartDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(_T(""))));
	m_xcCombo_EndDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(_T(""))));
}


void DateFilterDlg::OnBnClickedBtnDateSettoday()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	CTime    cTime;
	CString  str;

	cTime = CTime::GetCurrentTime();           // ���ݎ���
	str = cTime.Format("%Y/%m/%d");   // "YYYY/mm/dd HH:MM:SS"�`���̎�����������擾

	m_xcCombo_TargetDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(str)));
	m_xcCombo_StartDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(_T(""))));
	m_xcCombo_EndDate.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(_T(""))));

	//�ǉ� 2012.07.11
	CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHECK_DateSpan);
	chkbox1->SetCheck(0);

	CButton* chkbox2 = (CButton*)GetDlgItem(IDC_CHECK_TargetDate);
	chkbox2->SetCheck(1);

	m_xvChkDateSpan = FALSE;
	m_xvChkTargetDate = TRUE;
}


void DateFilterDlg::OnBnClickedCancel()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CDialogEx::OnCancel();
}


void DateFilterDlg::OnBnClickedCheckDatespan()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	//http://www.ujasiri.com/prglib/vc/compo/vc_chkboxsap.html
	CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHECK_TargetDate);
	
	if (m_xvChkDateSpan == FALSE){
		m_xvChkDateSpan = TRUE;
		m_xvChkTargetDate = FALSE;
		chkbox1->SetCheck(0);
	}else{
		m_xvChkDateSpan = FALSE;
		m_xvChkTargetDate = TRUE;
		chkbox1->SetCheck(1);
	}
}


void DateFilterDlg::OnBnClickedCheckTargetdate()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	//http://www.ujasiri.com/prglib/vc/compo/vc_chkboxsap.html
	CButton* chkbox2 = (CButton*)GetDlgItem(IDC_CHECK_DateSpan);

	if (m_xvChkTargetDate == FALSE){ //.GetCheck()
		m_xvChkTargetDate = TRUE;
		m_xvChkDateSpan = FALSE;
		//�`�F�b�N���O��
		chkbox2->SetCheck(0);
	}else{
		m_xvChkTargetDate = FALSE;
		m_xvChkDateSpan = TRUE;
		chkbox2->SetCheck(1);
	}
}


void DateFilterDlg::OnCbnSetfocusComboStartdate()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHECK_DateSpan);
	chkbox1->SetCheck(1);

	CButton* chkbox2 = (CButton*)GetDlgItem(IDC_CHECK_TargetDate);
	chkbox2->SetCheck(0);

	m_xvChkDateSpan = TRUE;
	m_xvChkTargetDate = FALSE;
}


void DateFilterDlg::OnCbnSetfocusComboEnddate()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHECK_DateSpan);
	chkbox1->SetCheck(1);

	CButton* chkbox2 = (CButton*)GetDlgItem(IDC_CHECK_TargetDate);
	chkbox2->SetCheck(0);

	m_xvChkDateSpan = TRUE;
	m_xvChkTargetDate = FALSE;

}


void DateFilterDlg::OnCbnSetfocusComboTargetdate()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHECK_DateSpan);
	chkbox1->SetCheck(0);

	CButton* chkbox2 = (CButton*)GetDlgItem(IDC_CHECK_TargetDate);
	chkbox2->SetCheck(1);

	m_xvChkDateSpan = FALSE;
	m_xvChkTargetDate = TRUE;
}

// PreTranslateMessage
BOOL DateFilterDlg::PreTranslateMessage (MSG* pMsg)
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
					//���[�_���X�P
					m_Dlg->OnFilterDatefilter();
					break;

				case _T('K'):
					//���[�_���X�P
					m_Dlg->OnFilterKeywords();
					break;

				case _T('L'):
					m_Dlg->ChangeLanguage();
					break;

				case _T('Z'):
					/* �A���h�D */
					if (m_Dlg->ESCAPE_FLG == FALSE) {
						m_Dlg->ESCAPE_FLG = TRUE;
						m_Dlg->StatusStringSet(_T("���s���̏������~���܂���"),300,TRUE);
					}
					m_Dlg->OnEditlistUndo();
					m_Dlg->ESCAPE_FLG = FALSE;
					break;

				case _T('S'):
					/* �ۑ� */
					m_Dlg->OnMenuFileSave();
			
					m_Dlg->CFileListCreatorDlg::StatusStringSet(_T("�t�@�C����ۑ����܂���"),300,FALSE);
					break;
				}
			}
		//}
	default:
		break;
	}


    return CDialog::PreTranslateMessage (pMsg);
}