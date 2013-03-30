// ReplaceDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "FileListCreator.h"

//�ǉ���
#include "FileListCreatorDlg.h"
//�ǉ���

#include "ReplaceDlg.h"
#include "afxdialogex.h"



// ReplaceDlg �_�C�A���O

IMPLEMENT_DYNAMIC(ReplaceDlg, CDialogEx)

ReplaceDlg::ReplaceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ReplaceDlg::IDD, pParent)
	, m_xvChkReplaceFullPath(FALSE)
{

}

ReplaceDlg::~ReplaceDlg()
{
}

void ReplaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SearchBOX, m_xcCombo_SearchBOX);
	DDX_Control(pDX, IDC_COMBO_ReplaceBOX, m_xcCombo_ReplaceBOX);
	DDX_Check(pDX, IDC_CHK_ReplaceFullPath, m_xvChkReplaceFullPath);
}


BEGIN_MESSAGE_MAP(ReplaceDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ReplaceDlg::OnBnClickedOk)
	ON_BN_CLICKED(ID_BTN_REPLACE_CLEAR, &ReplaceDlg::OnBnClickedBtnReplaceClear)
	ON_BN_CLICKED(IDCANCEL, &ReplaceDlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_BTN_REPLACE_GetFileName, &ReplaceDlg::OnBnClickedBtnReplaceGetfilename)
	ON_BN_CLICKED(ID_BTN_EXCHANGE, &ReplaceDlg::OnBnClickedBtnExchange)
	ON_BN_CLICKED(ID_BTN_REPLACE_GetFileName2, &ReplaceDlg::OnBnClickedBtnReplaceGetfilename2)
	ON_BN_CLICKED(ID_BTN_Search, &ReplaceDlg::OnBnClickedBtnSearch)
	ON_BN_CLICKED(ID_BTN_Replace, &ReplaceDlg::OnBnClickedBtnReplace)
	ON_CBN_EDITCHANGE(IDC_COMBO_SearchBOX, &ReplaceDlg::OnCbnEditchangeComboSearchbox)
	ON_CBN_SELCHANGE(IDC_COMBO_SearchBOX, &ReplaceDlg::OnCbnSelchangeComboSearchbox)
	ON_BN_CLICKED(IDC_CHK_ReplaceFullPath, &ReplaceDlg::OnBnClickedChkReplacefullpath)
END_MESSAGE_MAP()

// ReplaceDlg ���b�Z�[�W �n���h���[

BOOL ReplaceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return FALSE;
	}

	m_xvChkReplaceFullPath = FALSE;

	if (m_Dlg->CellSizeFixMode == _T("FilePath")){
		if (m_Dlg->m_xcList.GetItemCount()>=1){
			int myResult;
			myResult = MessageBox(_T("�����t�@�C���p�X�E���[�h�ŉ{�����Ă��܂��B�t�@�C���p�X����u���ł���悤�ɂ��܂����H") ,_T("���[�h�m�F"), MB_YESNOCANCEL );

			if (IDYES == myResult){
				CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_ReplaceFullPath);

				m_xvChkReplaceFullPath  = TRUE;
				chkbox1->SetCheck(1);
		
				//http://rararahp.cool.ne.jp/vc/vctips/button.htm

				CButton *button_01=(CButton*)GetDlgItem(ID_BTN_REPLACE_GetFileName);
				button_01->SetWindowText(_T("<-- GetFilePath"));
				CButton *button_02=(CButton*)GetDlgItem(ID_BTN_REPLACE_GetFileName2);
				button_02->SetWindowText(_T("<-- GetFilePath"));
			}
		}
	}

	MatchCNT=0;

	if(m_Dlg->m_xcList.GetSelectedCount()>=1){
		ReadOrWriteComboData_Func(_T("read"));
		int index = -1;

		while ((index = m_Dlg->m_xcList.GetNextItem
				(index, LVNI_ALL | LVNI_SELECTED)) != -1){
			CString SearchStr;
			SearchStr = m_Dlg->m_xcList.GetItemText(index, 3);
			m_xcCombo_SearchBOX.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(SearchStr)));
			break;
		}
	}else{
		ReadOrWriteComboData_Func(_T("read"));
	}

	return TRUE;
}

void ReplaceDlg::ExistCheckFunc(CString mySwitch)
{
	if (mySwitch==_T("SearchBOX")){
		BOOL tempFLG = TRUE;
		CString EditData;
		ReplaceDlg::m_xcCombo_SearchBOX.GetWindowText(EditData);

		//if(EditData !=_T("")){
			int k = 0;
	
			int k2 = 0;

			while (k <= ReplaceDlg::m_xcCombo_SearchBOX.GetCount() -1){
				CString ComboText;
				ReplaceDlg::m_xcCombo_SearchBOX.GetLBText(k, ComboText); // �C���f�b�N�Xk�Ԗڂ̕�������擾

				if(ComboText == EditData){
					ReplaceDlg::m_xcCombo_SearchBOX.SetCurSel(k);
					k2 = k;
					tempFLG = FALSE;
				}
				k++;
			}

			if(tempFLG == TRUE){
				ReplaceDlg::m_xcCombo_SearchBOX.InsertString(0,EditData);
				ReplaceDlg::m_xcCombo_SearchBOX.SetCurSel(0);
			}else{
				ReplaceDlg::m_xcCombo_SearchBOX.DeleteString(k2);
				ReplaceDlg::m_xcCombo_SearchBOX.InsertString(0,EditData);
				ReplaceDlg::m_xcCombo_SearchBOX.SetCurSel(0);
			}

			for(k = ReplaceDlg::m_xcCombo_SearchBOX.GetCount();k>=ComboBox_MAX;k--){
				ReplaceDlg::m_xcCombo_SearchBOX.DeleteString(k);
			}
		//}
	}else if (mySwitch==_T("ReplaceBOX")){
		BOOL tempFLG = TRUE;
		CString EditData;
		ReplaceDlg::m_xcCombo_ReplaceBOX.GetWindowText(EditData);

		//if(EditData !=_T("")){
			int k = 0;
	
			int k2 = 0;

			while (k <= ReplaceDlg::m_xcCombo_ReplaceBOX.GetCount() -1){
				CString ComboText;
				ReplaceDlg::m_xcCombo_ReplaceBOX.GetLBText(k, ComboText); // �C���f�b�N�Xk�Ԗڂ̕�������擾

				if(ComboText == EditData){
					ReplaceDlg::m_xcCombo_ReplaceBOX.SetCurSel(k);
					k2 = k;
					tempFLG = FALSE;
				}
				k++;
			}

			if(tempFLG == TRUE){
				ReplaceDlg::m_xcCombo_ReplaceBOX.InsertString(0,EditData);
				ReplaceDlg::m_xcCombo_ReplaceBOX.SetCurSel(0);
			}else{
				ReplaceDlg::m_xcCombo_ReplaceBOX.DeleteString(k2);
				ReplaceDlg::m_xcCombo_ReplaceBOX.InsertString(0,EditData);
				ReplaceDlg::m_xcCombo_ReplaceBOX.SetCurSel(0);
			}

			for(k = ReplaceDlg::m_xcCombo_ReplaceBOX.GetCount();k>=ComboBox_MAX;k--){
				ReplaceDlg::m_xcCombo_ReplaceBOX.DeleteString(k);
			}
		//}
	}
}

void ReplaceDlg::ReadOrWriteComboData_Func(CString mySwitch)
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

		while (k <= ReplaceDlg::m_xcCombo_SearchBOX.GetCount() -1){
			CString ComboText;
			ReplaceDlg::m_xcCombo_SearchBOX.GetLBText(k, ComboText); // �C���f�b�N�X0�Ԗڂ̕�������擾
			if(k<=ComboBox_MAX){
				WriteData1 = WriteData1 + ComboText + _T("\n");
			}
			k++;
		}

		k = 0;
		WriteData2 = _T("");

		while (k <= ReplaceDlg::m_xcCombo_ReplaceBOX.GetCount() -1){
			CString ComboText;
			ReplaceDlg::m_xcCombo_ReplaceBOX.GetLBText(k, ComboText); // �C���f�b�N�X0�Ԗڂ̕�������擾
			if(k<=ComboBox_MAX){
				WriteData2 = WriteData2 + ComboText + _T("\n");
			}
			k++;
		}
	}
;
	CString       wstr, rstr;
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
			if ( PathFileExists( CurDir + _T("\\SearchBOX.dat") ) ){
				FILE *fp;
				_tfopen_s(&fp,CurDir + _T("\\SearchBOX.dat"), _T("r, ccs=UNICODE"));
				CStdioFile stdFile1(fp);

				err = 0;
				int k;
				k = 0;
				while (!err) {
					if (stdFile1.ReadString(rstr) == FALSE) err = 1;
					if (!err && (k<ComboBox_MAX)){
						ReplaceDlg::m_xcCombo_SearchBOX.InsertString(k,rstr);
					}

					k++;
				}
				ReplaceDlg::m_xcCombo_SearchBOX.SetCurSel(0);

				// (6)�N���[�Y(�����I)
				stdFile1.Close();
				fclose(fp);
			}

			if ( PathFileExists( CurDir + _T("\\ReplaceBOX.dat") ) ){ //�ǉ� 2012.06.15
				FILE *fp;
				_tfopen_s(&fp,CurDir + _T("\\ReplaceBOX.dat"), _T("r, ccs=UNICODE"));
				CStdioFile stdFile2(fp);

				err=0;
				int k;
				k = 0;
				while (!err) {
					if (stdFile2.ReadString(rstr) == FALSE) err = 1;
					if (!err && (k<ComboBox_MAX)){
						ReplaceDlg::m_xcCombo_ReplaceBOX.InsertString(k,rstr);
					}

					k++;
				}
				ReplaceDlg::m_xcCombo_ReplaceBOX.SetCurSel(0);

				// (6)�N���[�Y(�����I)
				stdFile2.Close();
				fclose(fp);
			}
		}
		if (mySwitch == _T("write")){
			FILE *fp;

			_tfopen_s(&fp,CurDir + _T("\\SearchBOX.dat"), L"w,ccs=UNICODE");
			fputws(WriteData1, fp);
			fclose(fp);

			_tfopen_s(&fp,CurDir + _T("\\ReplaceBOX.dat"), L"w,ccs=UNICODE");
			fputws(WriteData2, fp);
			fclose(fp);
		}
	}
}


void ReplaceDlg::ReplaceFunc(int index,CString SearchStr,CString ReplaceStr){
	//LVITEM       lvi;
	//int          index = 0;
	int          err = 0;
	CString      str;	
	CString      FullPathString;

	CString myFileName;
	CString myFileSize;
	ULONGLONG myLongFileSize;
	CString myDate;
	CString myTime;

	CString tempDate;

	FullPathString =_T("");

	myFileName=_T("");
	myFileSize = _T("");
	myLongFileSize = -1;
	myDate = _T("");
	myTime = _T("");



	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}


	m_Dlg->lvi.mask = LVIF_TEXT;// | LVIF_PARAM;


	// �t�@�C����
	if (!err)
	{
		myFileName = m_Dlg->m_xcList.GetItemText(index, 3);			
	}



	int myIDX1;
	myIDX1 = 0;
	while (myIDX1<=myFileName.GetLength()-SearchStr.GetLength()){
		int hitIDX=-1;

		hitIDX = myFileName.Find(SearchStr,myIDX1);
		if(hitIDX!=-1){
			MatchCNT++;
			myIDX1=hitIDX + SearchStr.GetLength()-1;
		}
		myIDX1++;
	}

	myFileName.Replace(SearchStr,ReplaceStr);

	// �t�@�C����
	if (!err)
	{
		m_Dlg->lvi.iItem = index;
		m_Dlg->lvi.iSubItem = 3;			
		//if (myFileName!=_T("")){
			m_Dlg->lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileName));
			if (!m_Dlg->m_xcList.SetItem(&m_Dlg->lvi)) err = 1;
		//}
	}

	if ( m_xvChkReplaceFullPath == TRUE ) {
		// �t���p�X
		if (!err)
		{
			FullPathString = m_Dlg->m_xcList.GetItemText(index, 2);			
		}

		int myIDX2;
		myIDX2 = 0;
		while (myIDX2<=FullPathString.GetLength()-SearchStr.GetLength()){
			int hitIDX=-1;

			hitIDX = FullPathString.Find(SearchStr,myIDX2);
			if(hitIDX!=-1){
				MatchCNT++;
				myIDX2=hitIDX + SearchStr.GetLength()-1;
			}
			myIDX2++;
		}

		FullPathString.Replace(SearchStr,ReplaceStr);

		// �t���p�X
		if (!err)
		{
			m_Dlg->lvi.iItem = index;
			m_Dlg->lvi.iSubItem = 2;			
			//if (FullPathString!=_T("")){
				m_Dlg->lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPathString));
				if (!m_Dlg->m_xcList.SetItem(&m_Dlg->lvi)) err = 1;
			//}
		}
	}


	CString RemarksColumn=_T("");

	// ���l��
	if (!err)
	{
		RemarksColumn = m_Dlg->m_xcList.GetItemText(index, 8);			
	}

	int myIDX3;
	myIDX3 = 0;
	while (myIDX3<=RemarksColumn.GetLength()-SearchStr.GetLength()){
		int hitIDX=-1;

		hitIDX = RemarksColumn.Find(SearchStr,myIDX3);
		if(hitIDX!=-1){
			MatchCNT++;
			myIDX3=hitIDX + SearchStr.GetLength()-1;
		}
		myIDX3++;
	}

	RemarksColumn.Replace(SearchStr,ReplaceStr);

	// ���l��
	if (!err)
	{
		m_Dlg->lvi.iItem = index;
		m_Dlg->lvi.iSubItem = 8;			
		//if (RemarksColumn!=_T("")){
			m_Dlg->lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(RemarksColumn));
			if (!m_Dlg->m_xcList.SetItem(&m_Dlg->lvi)) err = 1;
		//}
	}

	m_Dlg->m_xcList.EnsureVisible(index, FALSE);

	if (MatchCNT>=1){
		m_Dlg->ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13
		////http://q.hatena.ne.jp/1180853478
		//AfxGetMainWnd()->SetWindowText(_T("FileListCreator(*)")); //�ǉ� 2012.05.13

		CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

		if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
			return;
		}

		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
		m_Dlg->SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24
	}

	RedrawWindow(); //�ǉ� 2012.05.24 //XP�΍�
}

void ReplaceDlg::OnBnClickedOk()  //ALL Replace
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CDialogEx::OnOK();

	CString SearchStr;
	CString ReplaceStr;

    ((CComboBox*)GetDlgItem(IDC_COMBO_SearchBOX))->GetWindowText(SearchStr);
	((CComboBox*)GetDlgItem(IDC_COMBO_ReplaceBOX))->GetWindowText(ReplaceStr);

	if (SearchStr==_T("") && ReplaceStr==_T("")){
		MessageBox(_T("�����ΏۂƂȂ镶���ƁA�u����̕�������͂��Ă�������"),_T("Replace"),MB_OK);
		return;
	}

	MatchCNT=0;

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}


	//m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount();
	//m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	if(m_Dlg->m_xcList.GetItemCount() < 1) {
		m_Dlg->StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
	}else{
		m_Dlg->StatusStringSet(_T("Replace ���s��"),0,FALSE); //�ύX 2012.06.14

		m_Dlg->m_xvChkRedOnMode = FALSE; //�ǉ� 2012.07.01
		m_Dlg->m_xvStrRedOnMode = _T("�F�@�ԕ��� ���ҏW");
		UpdateData(FALSE);	

		m_Dlg->m_xvChkEasySelect = FALSE; //�ǉ� 2012.07.01
		m_Dlg->m_xvStrEasySelectMode = _T("�F�@������ ���ҏW");
		UpdateData(FALSE);

		int myResult;
		if(m_Dlg->m_xcList.GetSelectedCount()==0){
			myResult = MessageBox(_T("�A�C�e�����I������Ă��܂���B���X�g�シ�ׂẴt�@�C������u�����܂����H"),_T("Replace"),MB_YESNOCANCEL);
			if (myResult==IDYES){
				m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount(); //�ǉ� 2012.07.01
				m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData"));

				if (m_Dlg->FindIDX==-1){
					OnBnClickedBtnSearch();
					m_Dlg->FindIDX--;
				}
				int index = 0;

				while(index < m_Dlg->m_xcList.GetItemCount()){
					ReplaceFunc(index,SearchStr,ReplaceStr);
					index++;
				}
			}else{
				m_Dlg->StatusStringSet(_T("Replace �L�����Z��"),300,FALSE);
				return;
			}
		}else if(m_Dlg->m_xcList.GetSelectedCount()>=1){

			m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount(); //�ǉ� 2012.07.01
			m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData"));

			myResult = MessageBox(_T("�I�����ꂽ�A�C�e���̃t�@�C������u�����܂����H�u�������v��I������ƃ��X�g�シ�ׂẴt�@�C������u�����܂��B"),_T("Replace"),MB_YESNOCANCEL);

			m_Dlg->m_xvChkRedOnMode = FALSE; //�ǉ� 2012.07.01
			m_Dlg->m_xvStrRedOnMode = _T("�F�@�ԕ��� ���ҏW");
			UpdateData(FALSE);	

			m_Dlg->m_xvChkEasySelect = FALSE; //�ǉ� 2012.07.01
			m_Dlg->m_xvStrEasySelectMode = _T("�F�@������ ���ҏW");
			UpdateData(FALSE);

			if (myResult==IDYES){
				int index = -1;

				while ((index = m_Dlg->m_xcList.GetNextItem
				        (index, LVNI_ALL | LVNI_SELECTED)) != -1){
					ReplaceFunc(index,SearchStr,ReplaceStr);
				}
			}else if(myResult==IDNO){
				int index = 0;

				while(index < m_Dlg->m_xcList.GetItemCount()){
					ReplaceFunc(index,SearchStr,ReplaceStr);
					index++;
				}
			}else{
				m_Dlg->StatusStringSet(_T("Replace �L�����Z��"),300,FALSE);
				return;
			}
		}
	}

	m_Dlg->m_xcList.EnsureVisible(1, FALSE);

	//RedrawWindow();

	CString tempCnt;
	tempCnt = _T("");

	if(MatchCNT>=1){ //�ǉ� 2012.06.14
		tempCnt.Format(_T("%d"),MatchCNT);
		tempCnt=_T("Replace �I���F") + tempCnt + _T(" �ӏ� �u�����܂���");
	}else{
		tempCnt=_T("Replace �I���F�w�肵���A�C�e�������������ߒu���͍s���܂���ł���");
	}
	m_Dlg->StatusStringSet(tempCnt,0,TRUE);
	UpdateData(FALSE);

	m_xcCombo_SearchBOX.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(SearchStr)));
	m_xcCombo_ReplaceBOX.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(ReplaceStr)));

	ExistCheckFunc(_T("SearchBOX"));
	ExistCheckFunc(_T("ReplaceBOX"));
	ReadOrWriteComboData_Func(_T("write"));
}


void ReplaceDlg::OnBnClickedBtnReplaceClear()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	m_xcCombo_SearchBOX.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(_T(""))));
	m_xcCombo_ReplaceBOX.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(_T(""))));
}


void ReplaceDlg::OnBnClickedCancel()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CDialogEx::OnCancel();
}


void ReplaceDlg::OnBnClickedBtnReplaceGetfilename()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if(m_Dlg->m_xcList.GetSelectedCount()>=1){
		int index = -1;

		while ((index = m_Dlg->m_xcList.GetNextItem
				(index, LVNI_ALL | LVNI_SELECTED)) != -1){
			CString SearchStr;

			if ( m_xvChkReplaceFullPath == TRUE ) {
				SearchStr = m_Dlg->m_xcList.GetItemText(index, 2);//�t���p�X
			}else{
				SearchStr = m_Dlg->m_xcList.GetItemText(index, 3);//�t�@�C����
			}
			m_xcCombo_SearchBOX.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(SearchStr)));
			break;
		}
	}else{
		MessageBox(_T("�I����Ԃɂ���t�@�C������Search Str�ɃZ�b�g���܂��B�A�C�e�����P�I�����čēx�{�^���������ĉ������B") ,_T("GetFileName"), MB_OK );
	}
	ReplaceDlg::OnBnClickedBtnSearch();
}

void ReplaceDlg::OnBnClickedBtnReplaceGetfilename2()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if(m_Dlg->m_xcList.GetSelectedCount()>=1){
		int index = -1;

		while ((index = m_Dlg->m_xcList.GetNextItem
				(index, LVNI_ALL | LVNI_SELECTED)) != -1){
			CString ReplaceStr;

			if ( m_xvChkReplaceFullPath == TRUE ) {
				ReplaceStr = m_Dlg->m_xcList.GetItemText(index, 2);//�t���p�X
			}else{
				ReplaceStr = m_Dlg->m_xcList.GetItemText(index, 3);//�t�@�C����
			}
			m_xcCombo_ReplaceBOX.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(ReplaceStr)));
			break;
		}
	}else{
		MessageBox(_T("�I����Ԃɂ���t�@�C������Replace Str�ɃZ�b�g���܂��B�A�C�e�����P�I�����čēx�{�^���������ĉ������B") ,_T("GetFileName"), MB_OK );
	}
	ReplaceDlg::OnBnClickedBtnSearch();
}


void ReplaceDlg::OnBnClickedBtnExchange()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CString SearchStr;
	CString ReplaceStr;

    ((CComboBox*)GetDlgItem(IDC_COMBO_SearchBOX))->GetWindowText(SearchStr);
	((CComboBox*)GetDlgItem(IDC_COMBO_ReplaceBOX))->GetWindowText(ReplaceStr);

	if (SearchStr==_T("") && ReplaceStr==_T("")){
		MessageBox(_T("�����ΏۂƂȂ镶�����A�u����̕�������͂��Ă��������B"),_T("Replace"),MB_OK);
		return;
	}

	MatchCNT=0;

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}


	m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount();
	m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	if(m_Dlg->m_xcList.GetItemCount() < 1) {
		m_Dlg->StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
	}else{
		m_Dlg->StatusStringSet(_T("Replace ���s��"),0,FALSE); //�ύX 2012.06.14

		m_Dlg->m_xvChkRedOnMode = FALSE; //�ǉ� 2012.07.01
		m_Dlg->m_xvStrRedOnMode = _T("�F�@�ԕ��� ���ҏW");
		UpdateData(FALSE);	

		m_Dlg->m_xvChkEasySelect = FALSE; //�ǉ� 2012.07.01
		m_Dlg->m_xvStrEasySelectMode = _T("�F�@������ ���ҏW");
		UpdateData(FALSE);


		int myResult;
		if(m_Dlg->m_xcList.GetSelectedCount()==0){
			myResult = MessageBox(_T("�A�C�e�����I������Ă��܂���B���X�g�シ�ׂẴt�@�C���������ւ����܂����H"),_T("Replace"),MB_YESNOCANCEL);
			if (myResult==IDYES){
				int index = 0;

				while(index < m_Dlg->m_xcList.GetItemCount()){
					ReplaceFunc(index,SearchStr,_T("<<<<<<DummyString>>>>>>"));
					ReplaceFunc(index,ReplaceStr,SearchStr);
					ReplaceFunc(index,_T("<<<<<<DummyString>>>>>>"),ReplaceStr);
					index++;
				}
			}else{
				m_Dlg->StatusStringSet(_T("Replace �L�����Z��"),300,FALSE);
				return;
			}
		}
		if(m_Dlg->m_xcList.GetSelectedCount()>=1){

			myResult = MessageBox(_T("�I�����ꂽ�A�C�e���̃t�@�C���������ւ����܂����H"),_T("Replace"),MB_YESNOCANCEL);
			if (myResult==IDYES){
				int index = -1;

				while ((index = m_Dlg->m_xcList.GetNextItem
				        (index, LVNI_ALL | LVNI_SELECTED)) != -1){
					ReplaceFunc(index,SearchStr,_T("<<<<<<DummyString>>>>>>"));
					ReplaceFunc(index,ReplaceStr,SearchStr);
					ReplaceFunc(index,_T("<<<<<<DummyString>>>>>>"),ReplaceStr);
				}
			}else{
				m_Dlg->StatusStringSet(_T("Replace �L�����Z��"),300,FALSE);
				return;
			}
		}
	}


	CString tempCnt;
	tempCnt = _T("");
	if (MatchCNT/3>=1) { //�ǉ� 2012.06.12
		tempCnt.Format(_T("%d"),MatchCNT/3);
		tempCnt=_T("Exchange �I���F �A�C�e�������ւ����܂���");
	}else{
		tempCnt=_T("Exchange �I���F�w�肵���A�C�e�������������� Exchange �͍s���܂���ł���");
	}

	m_Dlg->StatusStringSet(tempCnt,300,TRUE);

	if (MatchCNT/3>=1){
		m_Dlg->ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13
		////http://q.hatena.ne.jp/1180853478
		//AfxGetMainWnd()->SetWindowText(_T("FileListCreator(*)")); //�ǉ� 2012.05.13

		CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

		if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
			return;
		}

		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}

	UpdateData(FALSE);

	m_xcCombo_SearchBOX.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(SearchStr)));
	m_xcCombo_ReplaceBOX.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(ReplaceStr)));

	ExistCheckFunc(_T("SearchBOX"));
	ExistCheckFunc(_T("ReplaceBOX"));
	ReadOrWriteComboData_Func(_T("write"));
}

void ReplaceDlg::OnBnClickedBtnSearch()  // Find Next
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	CString SearchStr;
	CString ReplaceStr;

    ((CComboBox*)GetDlgItem(IDC_COMBO_SearchBOX))->GetWindowText(SearchStr);
	((CComboBox*)GetDlgItem(IDC_COMBO_ReplaceBOX))->GetWindowText(ReplaceStr);

	if (SearchStr==_T("")){
		MessageBox(_T("�����ΏۂƂȂ镶������͂��Ă�������"),_T("Find"),MB_OK);
		return;
	}

	//MatchCNT=0;

	//LVITEM       lvi;
	//int          index = 0;
	int          err = 0;
	CString      str;	
	CString      FullPathString;

	CString myFileName;
	CString myFileSize;
	ULONGLONG myLongFileSize;
	CString myDate;
	CString myTime;

	CString tempDate;

	FullPathString =_T("");

	myFileName=_T("");
	myFileSize = _T("");
	myLongFileSize = -1;
	myDate = _T("");
	myTime = _T("");

	CString RemarksColumn;
	RemarksColumn = _T("");

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

			m_Dlg->m_xvChkRedOnMode = FALSE; //�ǉ� 2012.07.01
			m_Dlg->m_xvStrRedOnMode = _T("�F�@�ԕ��� ���ҏW");
			UpdateData(FALSE);	

			m_Dlg->m_xvChkEasySelect = FALSE; //�ǉ� 2012.07.01
			m_Dlg->m_xvStrEasySelectMode = _T("�F�@������ ���ҏW");
			UpdateData(FALSE);

	m_Dlg->lvi.mask = LVIF_TEXT;// | LVIF_PARAM;


	if ( m_Dlg->FindIDX == -1 ){
		m_Dlg->StatusStringSet(_T("�������J�n���܂���"),0,FALSE);
	}

	m_Dlg->m_xcList.SetItemState(m_Dlg->FindIDX,     // �t�H�[�J�X����I����Ԃɂ������A�C�e���̃C���f�b�N�X
	!LVIS_FOCUSED | !LVIS_SELECTED,    // ���
	LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N

	if(m_Dlg->FindIDX < m_Dlg->m_xcList.GetItemCount()){
		m_Dlg->FindIDX++;
	}

	int index = m_Dlg->FindIDX;

	while (index < m_Dlg->m_xcList.GetItemCount()){
		int myIDX;
		myIDX = 0;
			
		myFileName = m_Dlg->m_xcList.GetItemText(index, 3);			
		FullPathString = m_Dlg->m_xcList.GetItemText(index, 2);
		RemarksColumn = m_Dlg->m_xcList.GetItemText(index, 8);			

		int hitIDX1=-1;
		int hitIDX2=-1;
		int hitIDX3=-1;

		hitIDX1 = myFileName.Find(SearchStr,myIDX);
		if ( m_xvChkReplaceFullPath == TRUE ) {
			hitIDX2=-1;
			hitIDX2 = FullPathString.Find(SearchStr,myIDX);

		}

		hitIDX3=-1;
		hitIDX3 = RemarksColumn.Find(SearchStr,myIDX);

		if( hitIDX1!=-1 || hitIDX2!=-1 || hitIDX3!=-1){
			m_Dlg->FindIDX = index;

			MatchCNT++;
			//myIDX=hitIDX1 + SearchStr.GetLength()-1;

			m_Dlg->m_xcList.SetItemState(index,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
			LVIS_FOCUSED | LVIS_SELECTED,    // ���
			LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N

			m_Dlg->m_xcList.EnsureVisible(index, FALSE);

			//m_Dlg->m_xcList.SetItemState(index).SetEditSel(-1,-1);  //�I���Ȃ��ŁA�Ō�̕����ʒu�ɃJ�[�\����u��
			//m_Dlg->m_xcList.SetColumn(index).Selection
			
			break;
		}

		index++;
	}

	if (index >= m_Dlg->m_xcList.GetItemCount()-1) {
		m_Dlg->StatusStringSet(_T("�����܂Ō������I�����܂���"),300,TRUE);
		m_Dlg->FindIDX = -1;
	}


	MatchCNT--;

	//CString tempCnt;
	//tempCnt = _T("");

	//tempCnt.Format(_T("%d"),MatchCNT);
	//tempCnt=_T("Replace �I���F") + tempCnt + _T(" �ӏ� �u�����܂���");

	//m_Dlg->StatusStringSet(tempCnt,300,TRUE);

	//m_xvStCount = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempCnt));

	///m_Dlg->m_xcList.EnsureVisible(index-1, FALSE);
	UpdateData(FALSE);

	m_xcCombo_SearchBOX.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(SearchStr)));
	m_xcCombo_ReplaceBOX.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(ReplaceStr)));

	ExistCheckFunc(_T("SearchBOX"));
	ExistCheckFunc(_T("ReplaceBOX"));
	ReadOrWriteComboData_Func(_T("write"));
}


void ReplaceDlg::OnBnClickedBtnReplace()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CString SearchStr;
	CString ReplaceStr;

    ((CComboBox*)GetDlgItem(IDC_COMBO_SearchBOX))->GetWindowText(SearchStr);
	((CComboBox*)GetDlgItem(IDC_COMBO_ReplaceBOX))->GetWindowText(ReplaceStr);

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

		m_Dlg->m_xvChkRedOnMode = FALSE; //�ǉ� 2012.07.01
		m_Dlg->m_xvStrRedOnMode = _T("�F�@�ԕ��� ���ҏW");
		UpdateData(FALSE);	

		m_Dlg->m_xvChkEasySelect = FALSE; //�ǉ� 2012.07.01
		m_Dlg->m_xvStrEasySelectMode = _T("�F�@������ ���ҏW");
		UpdateData(FALSE);

	//m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount();
	//m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	//::SetFocus(::GetDlgItem(m_hWnd,IDD_DIALOG_Replace)); //�ǉ� 2012.05.03

	if(m_Dlg->m_xcList.GetSelectedCount()>=1){
		int index = -1;

		while ((index = m_Dlg->m_xcList.GetNextItem
				(index, LVNI_ALL | LVNI_SELECTED)) != -1){
			ReplaceFunc(index,SearchStr,ReplaceStr);
		}
	//}else{
	//	ReplaceFunc(m_Dlg->FindIDX,SearchStr,ReplaceStr);
	}

	//if (m_Dlg->FindIDX==-1){
		OnBnClickedBtnSearch();
	//}


	//CString tempCnt;
	//tempCnt = _T("");

	//tempCnt.Format(_T("%d"),MatchCNT);
	//tempCnt=_T("Replace �I���F") + tempCnt + _T(" �ӏ� �u�����܂���");
	//
	//m_Dlg->StatusStringSet(tempCnt,300,TRUE);
	//
	//m_xvStCount = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempCnt));
	///m_Dlg->m_xcList.EnsureVisible(index-1, FALSE);
	//UpdateData(FALSE);

	m_xcCombo_SearchBOX.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(SearchStr)));
	m_xcCombo_ReplaceBOX.SetWindowText(const_cast<LPTSTR>(static_cast<LPCTSTR>(ReplaceStr)));

	ExistCheckFunc(_T("SearchBOX"));
	ExistCheckFunc(_T("ReplaceBOX"));
	ReadOrWriteComboData_Func(_T("write"));
}


void ReplaceDlg::OnCbnEditchangeComboSearchbox()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->FindIDX = -1;
}


BOOL ReplaceDlg::PreTranslateMessage(MSG* pMsg) 
{
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return 0;
	}

	//LVITEM       lvi;
	//int err;


	//ReplaceDlg ReplaceDlg_CLASS;  //Ctrl + F  , Ctrl + G

	switch (pMsg->message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	//http://www.coara.or.jp/~tkuri/D/034.htm
	case WM_KEYDOWN:
		if ( ::GetKeyState( VK_CONTROL ) < 0 ) {
			switch ( (int)pMsg->wParam ) {
			//case _T('F'):

			case _T('G'):
				/* �������� */

				//if(pMsg->hwnd == GetDlgItem(IDD_DIALOG_Replace)->m_hWnd ){
					ReplaceDlg::OnBnClickedBtnSearch();
					//::SetFocus(::GetDlgItem(m_hWnd,IDD_DIALOG_Replace)); //�ǉ� 2012.05.03
				//}
				break;
			case _T('R'):
				/* �u�� */
				m_Dlg->LastPrevItemCount = m_Dlg->m_xcList.GetItemCount();
				m_Dlg->push_back_Func(m_Dlg->LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

				ReplaceDlg::OnBnClickedBtnReplace();
				//::SetFocus(::GetDlgItem(m_hWnd,IDD_DIALOG_Replace)); //�ǉ� 2012.05.03
				//ReplaceDlg::OnBnClickedBtnSearch();
				break;

			//case _T('Z'):  //UNDO����x�Ă΂��̂ŃR�����g��
				///* �A���h�D */
				//m_Dlg->OnEditlistUndo();
				//break;

			case _T('S'):
				/* �ۑ� */
				m_Dlg->OnMenuFileSave();
			
				m_Dlg->CFileListCreatorDlg::StatusStringSet(_T("�t�@�C����ۑ����܂���"),300,FALSE);
				break;
			//case _T('X'):
			//	/* �J�b�g */
			//	break;
			//case _T('C'):
			//	/* �R�s�[ */
			//	break;
			//case _T('V'):
			//	/* �y�[�X�g */
			//	break;

			//case _T('L'): //�R�����g�� 2012.04.17
			//	m_Dlg->ChangeLanguage();
			//	break;

			default:
				//ReplaceDlg ReplaceDlg_CLASS;
				/* ���̑� */
				break;
			}
			return 0;
		}
		return 0;
	}
	return CDialog::PreTranslateMessage (pMsg);
}

void ReplaceDlg::OnCbnSelchangeComboSearchbox()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->FindIDX = -1;
}


void ReplaceDlg::OnBnClickedChkReplacefullpath()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_ReplaceFullPath);
	
	if (m_xvChkReplaceFullPath == FALSE){
		m_xvChkReplaceFullPath  = TRUE;
		chkbox1->SetCheck(1);
		
		//http://rararahp.cool.ne.jp/vc/vctips/button.htm

		CButton *button_01=(CButton*)GetDlgItem(ID_BTN_REPLACE_GetFileName);
		button_01->SetWindowText(_T("<-- GetFilePath"));
		CButton *button_02=(CButton*)GetDlgItem(ID_BTN_REPLACE_GetFileName2);
		button_02->SetWindowText(_T("<-- GetFilePath"));
	}else{
		m_xvChkReplaceFullPath  = FALSE;
		chkbox1->SetCheck(0);

		CButton *button_01=(CButton*)GetDlgItem(ID_BTN_REPLACE_GetFileName);
		button_01->SetWindowText(_T("<-- GetFileName"));
		CButton *button_02=(CButton*)GetDlgItem(ID_BTN_REPLACE_GetFileName2);
		button_02->SetWindowText(_T("<-- GetFileName"));
	}
}
