
// FileListCreatorDlg.cpp : �����t�@�C��
//

//�Q�l���Fhttp://www.g-ishihara.com/

#include "stdafx.h"
#include "afxcmn.h" //�蓮�Œǉ� ���X�g�R���g���[��

#include <string.h>

//��isdigit�֐� �p 2011.05.30��
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <conio.h> // don't forget !
#include <iostream>

//��isdigit�֐� �p 2011.05.30��

//SFXTextEncoding
//�����G���R�[�h��ϊ����邽�߂̃N���X�ł��B

#include "FileListCreator.h"
#include "FileListCreatorDlg.h"

#include "FileSpecsDlg.h"
#include "ReplaceDlg.h"
#include "InputBoxDlg.h"
#include "DateFilterDlg.h"
#include "KeywordDlg.h"

#include "afxdialogex.h"

#include "MylistCtrl.h"//�ǉ�

#include "HTML_Dlg.h"//�ǉ�

#include "TipsInfo.h"//�ǉ� 2012.04.17


//#include <tchar.h> //�ǉ� 2012.04.20
//#include <clocale> //�ǉ� 2012.04.20
//#include <cstdio> //�ǉ� 2012.04.20

#include <locale.h>  //�ǉ� 2012.04.20


//cstringt.h

#include "windows.h"//http://oshiete.goo.ne.jp/qa/2065303.html
#include <shlobj.h> // use shell32.lib//�ǉ�//�}�C�h�L�������g�̃p�X�̎擾

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//�ǉ���
#include <string>
#include <iostream>
using namespace std;
#include <AFXPRIV.H>

//#include <SFXTextEncoding.h.hpp>
//class SFXTextEncoding;
//SFMTYPEDEFCLASS(SFXTextEncoding)


//#include "cstringt.h"

/////////////////////////////////////////////////////////////////////////////
//  �t�H���_�I���_�C�A���O�̋N��
#include "winnetwk.h"
#include "shlobj.h"

//http://soheeya.net/programming/vctips/dialog.html
/////////////////////////////////////////////////////////////////////////////
//  SHBrowseForFolder()�p�R�[���o�b�N�֐�
int CALLBACK SHBrowseProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    if( uMsg == BFFM_INITIALIZED && lpData )
    {
        //  �f�t�H���g�őI��������p�X�̎w��
        SendMessage( hWnd, BFFM_SETSELECTION, TRUE, lpData);
    }
    return 0;
}

//http://soheeya.net/programming/vctips/dialog.html
//  �V�X�e�����m�ۂ���ITEMIDLIST���J�����Ȃ���΂Ȃ�Ȃ�
void _SHFree(ITEMIDLIST* pidl)
{
    IMalloc*  pMalloc;
    SHGetMalloc( &pMalloc );
    if ( pMalloc )
    {
        pMalloc->Free( pidl );
        pMalloc->Release();
    }
}

//http://soheeya.net/programming/vctips/dialog.html
/////////////////////////////////////////////////////////////////////////////
//  �t�H���_�I���_�C�A���O�̋N��
UINT GetOpenFolderName( HWND hWnd, LPCTSTR lpszDefaultFolder, LPTSTR lpszBuffer, DWORD dwBufferSize )
{
    BROWSEINFO  bi;
    ITEMIDLIST*  pidl;
    //char  szSelectedFolder[MAX_PATH];//�Q�lURL����ύX�@��TCHAR
	TCHAR  szSelectedFolder[MAX_PATH];

    ZeroMemory( &bi, sizeof( BROWSEINFO ));
    bi.hwndOwner = hWnd;
    //  �R�[���o�b�N�֐����w��
    bi.lpfn   = SHBrowseProc;
    //  �f�t�H���g�őI�������Ă����t�H���_���w��
    bi.lParam = (LPARAM)lpszDefaultFolder;
    //  �^�C�g���̎w��
    bi.lpszTitle = _T("�����ΏۂƂȂ�t�H���_��I�����Ă�������");

	// ����t�H���_��I�������Ȃ�//�Q�lURL�ɒǉ�
	//bi.ulFlags = BIF_BROWSEFORCOMPUTER | BIF_RETURNONLYFSDIRS;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
    
	//  �t�H���_�_�C�A���O�̋N��
    pidl = SHBrowseForFolder( &bi );
    if( pidl )
    {
        //  �I�����ꂽ�t�H���_�����擾
        SHGetPathFromIDList( pidl, szSelectedFolder );
        _SHFree(pidl);
        if( (DWORD)lstrlen(szSelectedFolder) < dwBufferSize )
            lstrcpy( lpszBuffer, szSelectedFolder );
        //  �t�H���_���I�����ꂽ
        return IDOK;
    }
    //  �t�H���_�͑I������Ȃ�����
    return IDCANCEL;
}


//http://soheeya.net/programming/vctips/control_static.html
//HBRUSH CFileListCreatorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
//{

//}

// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()




//http://www.codeguru.com/forum/archive/index.php/t-174318.html
int CFileListCreatorDlg::myReverseFind(CString cs, CString subString,int startIDX)
 {
 cs.MakeReverse();
 subString.MakeReverse();

 int n1 = cs.Find(subString,cs.GetLength()-startIDX);

 if (n1 != -1)
 n1 = cs.GetLength() - n1 - subString.GetLength();

 return n1;
 }

long CFileListCreatorDlg::CStringToLong(CString strValue)
{
	//http://rararahp.cool.ne.jp/cgi-bin/lng/vc/vclng.cgi?print+200011/00110021.txt

    USES_CONVERSION;
    int    intLength;    // CString������
    LPWSTR    strWPoint;    // UNICODE���� 
    LPSTR    strAPoint;    // JIS����

    // �������̎擾
    intLength = strValue.GetLength();
    
    // �����|�C���^�擾
    strWPoint = strValue.GetBuffer(intLength);

    // UNICODE����JIS�֕ϊ�
    strAPoint = W2A(strWPoint);

    // �o�b�t�@�J��
    strValue.ReleaseBuffer();

    return atol(strAPoint);
}

CString CharToStringFunc(TCHAR inStr)
{
    //char test[5] = "test";

    CString myStr;
    myStr = inStr;
	return myStr;
}

//char StringToCharFunc(CString myStr)
//{
//	//CString myStr = "test";
//	//CString::GetBuffer()
//
//    char *p = new char[myStr.GetLength()+1];
//	strcpy(p, myStr);
//
//	return *p;
//
//	delete [] p;
//}

//TCHAR StringToCharFunc(CString theString) //�듮��A��ō폜
//{
//	int     sizeOfString = (theString.GetLength() + 1);
//	LPTSTR  lpsz = new TCHAR[ sizeOfString ];
//	_tcscpy_s(lpsz, sizeOfString, theString);
//	//... modify lpsz as much as you want
//	return lpsz[sizeOfString];
//	delete[] lpsz;
//}

// CFileListCreatorDlg �_�C�A���O

CString ripString(CString str, int index)
{
//http://oshiete.goo.ne.jp/qa/4605453.html

	LPCTSTR pStart = str;
	for (int i = 0; i < index; ++i) {
		pStart = _tcsinc(pStart); // CharNext�ł����l
	}
	LPCTSTR pEnd = _tcsinc(pStart); // CharNext�ł����l

	TCHAR result[3];
	const int len = pEnd - pStart;
	memcpy(result, pStart, len);
	result[len] = _T('\0');
	return result;
}

//CString FullPathToFileName(CString FullPathStr){
//	//http://www.kab-studio.biz/Programing/Codian/MxA/09.html
//}

CString CFileListCreatorDlg::FullPathToFileName(CString FullPathStr){

	int PathSeparatorIDX = 0;
	
	CString  FileName;

	if(FullPathStr.GetLength()==0){
		FileName = "";
	}else{
		PathSeparatorIDX  = FullPathStr.ReverseFind(_T('\\'));

		if(PathSeparatorIDX == -1){
			FileName = FullPathStr;
		}else{
		
			FileName= FullPathStr.Mid(PathSeparatorIDX+1);
		}
	}
	return FileName;
}

CString CFileListCreatorDlg::StatusStringSet(CString tempStr,int tempTime,BOOL SndOn){
	if(SndOn == TRUE){
		MessageBeep(MB_OK);
	}
	Sleep(tempTime);
	CFileListCreatorDlg::m_xvStatusString = tempStr;
	UpdateData(FALSE);

	return tempStr;
}

CString ByteCalculation(ULONGLONG mySize,BOOL DetailMode)
{

//http://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q1311155003

 //k �L�� kilo 103 �M���V�����1000(khikioi) 
 //M ���K mega 106 �M���V����́u�傫���v(megas) 
 //G �M�K giga 109 �M���V����́u���l�v(gigas) 
 //T �e�� tera 1012 �M���V����́u���b�v(tegas) 
 //P �y�^ peta 1015 �u�T�Ԗځv��"penta"����n���Ƃ��� 
 //E �G�N�T exa 1018 �u�U�Ԗځv��"hexa"����h���Ƃ��� 
 //Z �[[�b]�^ zetta 1021 
 //Y ��[�b]�^ yotta 1024 ���e���A���t�@�x�b�g�̍Ō������Q�Ԗ� 

	int j;

    // Cautions: When a Internet shortcut file is read, an error happens.
    
	CString ret;
    ret.Format(_T("%I64u%s"), mySize,_T("B"));
    
	//return ret;

	double dblSize;

	dblSize = (double)mySize;
	
    for (j = 1;j<= 8;j++){
        dblSize = dblSize / 1024;
        if(dblSize >= 1){
			switch (j){
				case 1:
                    //mySize = Format(mySize, "#0.000 
                    ret.Format(_T("%.0f%s"), dblSize,_T("KB"));
					break;
				case 2:
                    //mySize = Format(mySize, "#0.000")
					if (DetailMode==TRUE && dblSize >= 100){
						ret.Format(_T("%.3f%s"), dblSize,_T("MB"));
					}else{
						ret.Format(_T("%.0f%s"), dblSize,_T("MB"));
					}
					break;
                case 3:
                    //mySize = Format(mySize, "#0.000")
					//ret.Format(_T("%.3f%s"), dblSize,_T("GB"));
					if (DetailMode==TRUE && dblSize >= 100){
						ret.Format(_T("%.3f%s"), dblSize,_T("GB"));
					}else{
						ret.Format(_T("%.0f%s"), dblSize,_T("GB"));
					}
					break;
                case 4:
                    //mySize = Format(mySize, "#0.000")
					//ret.Format(_T("%.3f%s"), dblSize,_T("TB"));
					if (DetailMode==TRUE && dblSize >= 100){
						ret.Format(_T("%.3f%s"), dblSize,_T("TB"));
					}else{
						ret.Format(_T("%.0f%s"), dblSize,_T("TB"));
					}
					break;
                case 5:
                    //mySize = Format(mySize, "#0.000")
					//ret.Format(_T("%.3f%s"), dblSize,_T("PB"));
					if (DetailMode==TRUE && dblSize >= 100){
						ret.Format(_T("%.3f%s"), dblSize,_T("PB"));
					}else{
						ret.Format(_T("%.0f%s"), dblSize,_T("PB"));
					}
					break;
                case 6:
                    //mySize = Format(mySize, "#0.000")
					//ret.Format(_T("%.3f%s"), dblSize,_T("EB"));
					if (DetailMode==TRUE && dblSize >= 100){
						ret.Format(_T("%.3f%s"), dblSize,_T("EB"));
					}else{
						ret.Format(_T("%.0f%s"), dblSize,_T("EB"));
					}
					break;
                case 7:
                    //mySize = Format(mySize, "#0.000")
					//ret.Format(_T("%.3f%s"), dblSize,_T("ZB"));
					if (DetailMode==TRUE && dblSize >= 100){
						ret.Format(_T("%.3f%s"), dblSize,_T("ZB"));
					}else{
						ret.Format(_T("%.0f%s"), dblSize,_T("ZB"));
					}
					break;
                case 8:
                    //mySize = Format(mySize, "#0.000")
					//ret.Format(_T("%.3f%s"), dblSize,_T("YB"));
					if (DetailMode==TRUE && dblSize >= 100){
						ret.Format(_T("%.3f%s"), dblSize,_T("YB"));
					}else{
						ret.Format(_T("%.0f%s"), dblSize,_T("YB"));
					}
					break;
				//default:
				//	break;
			}
		}
	}

	//ret.Format(_T("%.3f%s"), mySize,_T("KB"));
	return ret;

}

CString CFileListCreatorDlg::Total_Bytes_Func(){
	ESCAPE_FLG = FALSE;

    ULONGLONG myByteSum = 0;

	//LVITEM       lvi;
	int          index = 0;
	//int          err = 0;
	//CString      str;	

	//m_xvTotal_Bytes = _T("---");
	//UpdateData(FALSE);

	while(index < CFileListCreatorDlg::m_xcList.GetItemCount()){

		MSG msg; //�ǉ� 2011.10.12
		if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
			if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
				if (msg.wParam == VK_ESCAPE){
					ESCAPE_FLG = TRUE;
					break; //�I���B���b�Z�[�W���[�v�𔲂���B
				}
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			//continue;
		}

		CString myFileSize;
		ULONGLONG myLongFileSize;	

		myLongFileSize = 0;

		//lvi.mask = LVIF_TEXT;// | LVIF_PARAM;

		// �t�@�C���T�C�Y
			myLongFileSize = CStringToLong(CFileListCreatorDlg::m_xcList.GetItemText(index, 5));
			myByteSum = myByteSum + myLongFileSize;		

		//CFileListCreatorDlg::m_xcList.EnsureVisible(index -1, FALSE);
		index++;

		//return err;
	}


    CString BoldItemStr;

    if(BoldByteSum == 0 || g_ChkCopyOn == FALSE){
        BoldItemStr = _T("");
	}else{
        BoldItemStr = _T("(COPY : ") + ByteCalculation(BoldByteSum,TRUE) + _T(") / ");
	}


	m_xvTotal_Bytes =  BoldItemStr + ByteCalculation(myByteSum,TRUE);
	//CFileListCreatorDlg::m_xcList.EnsureVisible(CFileListCreatorDlg::m_xcList.GetItemCount()-1, FALSE);
	UpdateData(FALSE);

	return(ByteCalculation(myByteSum,TRUE));
}

CString CFileListCreatorDlg::ItemCount_Func(BOOL EnsureVisibleFLG){
	
    int myCnt = 0;

	//LVITEM       lvi;
	int          index = 0;
	int          err = 0;
	CString      str;

	myCnt = CFileListCreatorDlg::m_xcList.GetItemCount();

	CString tempCnt;
	tempCnt = "";

	tempCnt.Format(_T("%d"),myCnt);
	tempCnt=tempCnt + _T(" items");

	CString BoldItemStr;
	CString BoldItemCountStr;

	BoldItemCountStr.Format(_T("%I64u"),BolditemCount);

    if(BoldByteSum == 0 || g_ChkCopyOn == FALSE){
        BoldItemStr = _T("");
	}else{
        BoldItemStr = _T("(COPY : ") + BoldItemCountStr + _T(") / ");
	}


	m_xvStCount = const_cast<LPTSTR>(static_cast<LPCTSTR>(BoldItemStr + tempCnt));
	if(EnsureVisibleFLG == TRUE ){ //&& g_NoDrawFLG == FALSE
		//CFileListCreatorDlg::m_xcList.EnsureVisible(myCnt-1, FALSE);
	}
	UpdateData(FALSE);

	return(tempCnt);
}


void CFileListCreatorDlg::SelectALL_Func(){
	if( CFileListCreatorDlg::m_xcList.GetItemCount() <=0){
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	ESCAPE_FLG = FALSE;
	SelectALLFLG  = TRUE;

	int i = 0;

	while(i<=m_xcList.GetItemCount() -1){

		MSG msg; //�ǉ� 2011.10.12
		if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
			if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
				if (msg.wParam == VK_ESCAPE){
					ESCAPE_FLG = TRUE;
					break; //�I���B���b�Z�[�W���[�v�𔲂���B
				}
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			//continue;
		}

		m_xcList.SetItemState(i,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
		!LVIS_FOCUSED | LVIS_SELECTED,    // ���
		LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N

		CFileListCreatorDlg::m_xcList.EnsureVisible(i, FALSE);
		//UpdateData(FALSE);
		UpdateWindow();
		i++;

		//ListView_Update(m_xcList, i);//�ǉ����Ă��Ӗ����Ȃ�����2011.05.14
	}

	if (ESCAPE_FLG == TRUE) return;

	RedrawWindow();

	CFileListCreatorDlg::Total_Bytes_Bold();
	CFileListCreatorDlg::Total_Bytes_Func();
	CFileListCreatorDlg::ItemCount_Func(TRUE);

	SelectALLFLG  = FALSE;

	CFileListCreatorDlg::StatusStringSet(_T("���ׂẴA�C�e����I����Ԃɂ��܂���"),300,TRUE);
}

void CFileListCreatorDlg::SelectALL_CancellationFunc(){
	if( CFileListCreatorDlg::m_xcList.GetItemCount() <=0){
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	ESCAPE_FLG = FALSE;
	SelectALLFLG  = TRUE;

	int i = 0;

	while(i<=m_xcList.GetItemCount() -1){

		MSG msg; //�ǉ� 2011.10.12
		if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
			if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
				if (msg.wParam == VK_ESCAPE){
					ESCAPE_FLG = TRUE;
					break; //�I���B���b�Z�[�W���[�v�𔲂���B
				}
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			//continue;
		}

		m_xcList.SetItemState(i,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
		!LVIS_FOCUSED | !LVIS_SELECTED,    // ���
		LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N
		//if( m_xvChkEasySelect == TRUE){
			CFileListCreatorDlg::m_xcList.EnsureVisible(i, FALSE);
			//UpdateData(FALSE);
			UpdateWindow();
		//}
		i++;

		//ListView_Update(m_xcList, i);//�ǉ����Ă��Ӗ����Ȃ�����2011.05.14
	}

	if (ESCAPE_FLG == TRUE) return;

	RedrawWindow();

	CFileListCreatorDlg::Total_Bytes_Bold();
	CFileListCreatorDlg::Total_Bytes_Func();
	CFileListCreatorDlg::ItemCount_Func(TRUE);

	SelectALLFLG  = FALSE;

	CFileListCreatorDlg::StatusStringSet(_T("���ׂĂ̑I����Ԃ��L�����Z�����܂���"),300,TRUE);
}
void CFileListCreatorDlg::DEL_FileType_Func(){
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{


		LastPrevItemCount = m_xcList.GetItemCount();
		CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

		//LVITEM       lvi;
		//int          index = -1;
		int          err = 0;
		CString      str;	
		CString      FullPathString;

		//if(FullPathString.Right(1)!=_T("\\")){

			//LVITEM       lvi;
			int          index = 0;
			//int          err = 0;
			//CString      str;

			int myResult;
			if(m_xcList.GetSelectedCount()==0){
				myResult = MessageBox(_T("�A�C�e�����I������Ă��܂���B���X�g��񂩂炷�ׂĂ̊g���q����菜���܂����H"),_T("Trim FileType"),MB_YESNOCANCEL);
				if (myResult==IDYES){
					StatusStringSet(_T("DEL FileType ���s��"),0,FALSE); //�ύX 2012.06.14

					//LVITEM       lvi;
					//int          index = 0;
					//int          err = 0;
					//CString      str;	
					//CString      FullPathString;

					UpdateData();

					while(index < CFileListCreatorDlg::m_xcList.GetItemCount()){
						CString myFileName;	

						FullPathString =_T("");

						myFileName=_T("");



						lvi.mask = LVIF_TEXT;// | LVIF_PARAM;


						// �t���p�X
						if (!err)
						{

							FullPathString =CFileListCreatorDlg::m_xcList.GetItemText(index,2);
							if(FullPathString != _T("")){
								FullPathString.Replace(_T("%"),_T("%%"));
							}
						}

						if(FullPathString.Right(1)!=_T("\\")){
							CString keepFileName= _T("");

							// �t�@�C�����擾
							if (!err)
							{

								keepFileName =CFileListCreatorDlg::m_xcList.GetItemText(index,3);
								if(keepFileName != _T("")){
									keepFileName.Replace(_T("%"),_T("%%"));
								}
								//keepFileName.Replace(_T("/"),_T("\\"));

								if(keepFileName.ReverseFind(_T('/'))>=0){
									keepFileName = keepFileName.Left(keepFileName.ReverseFind(_T('/'))+1);
								}else{
									keepFileName=_T("");
								}
							}

							//TRACE(FullPathString);

							// �t�@�C����
							if (!err)
							{
								int DotIDX = FullPathString.ReverseFind(_T('.'));
								myFileName = FullPathToFileName(FullPathString.Left(DotIDX));
			
								if(keepFileName!=_T("")){
									keepFileName.Replace(_T("\\"),_T("/"));
								}

								myFileName = keepFileName + myFileName;

								myFileName.Replace(_T("%%"),_T("%"));


								lvi.iItem = index;
								lvi.iSubItem = 3;			
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileName));
								if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;			
							}
						}

						UpdateData(FALSE);
						//tempDate = "";
	
						index++;
					}

					CFileListCreatorDlg::StatusStringSet(_T("DEL FileType �I��"),300,TRUE);
				}
			}
			if(m_xcList.GetSelectedCount()>=1){
				myResult = MessageBox(_T("�I�����ꂽ�A�C�e���̊g���q������菜���܂����H"),_T("Trim FileType"),MB_YESNOCANCEL);
				if (myResult==IDYES){
					StatusStringSet(_T("DEL FileType ���s��"),0,FALSE); //�ύX 2012.06.14

					//LVITEM       lvi;
					int          index = -1;
					//int          err = 0;
					//CString      str;	
					//CString      FullPathString;

					UpdateData();

					while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
							(index, LVNI_ALL | LVNI_SELECTED)) != -1){

						CString myFileName;	

						FullPathString =_T("");

						myFileName=_T("");


						lvi.mask = LVIF_TEXT;// | LVIF_PARAM;


						// �t���p�X
						//if (!err)
						//{

							FullPathString =CFileListCreatorDlg::m_xcList.GetItemText(index,2);
							if(FullPathString != _T("")){
								FullPathString.Replace(_T("%"),_T("%%"));
							}
						//}
						if(FullPathString.Right(1)!=_T("\\")){
							CString keepFileName= _T("");

							// �t�@�C�����擾
							//if (!err)
							//{

								keepFileName =CFileListCreatorDlg::m_xcList.GetItemText(index,3);
								if(keepFileName != _T("")){
									keepFileName.Replace(_T("%"),_T("%%"));
								}
								//keepFileName.Replace(_T("/"),_T("\\"));

								if(keepFileName.ReverseFind(_T('/'))>=0){
									keepFileName = keepFileName.Left(keepFileName.ReverseFind(_T('/'))+1);
								}else{
									keepFileName=_T("");
								}
							//}

							//TRACE(FullPathString);

							//// �t�@�C����
							//if (!err)
							//{
								int DotIDX = FullPathString.ReverseFind(_T('.'));
								myFileName = FullPathToFileName(FullPathString.Left(DotIDX));
			
								if(keepFileName!=_T("")){
									keepFileName.Replace(_T("\\"),_T("/"));
								}

								myFileName = keepFileName + myFileName;
								
								myFileName.Replace(_T("%%"),_T("%"));

								lvi.iItem = index;
								lvi.iSubItem = 3;			
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileName));
								if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;			
								//}


								UpdateData(FALSE);
							}
						}

						CFileListCreatorDlg::StatusStringSet(_T("DEL FileType �I��"),300,TRUE);
					}
				}
			}
		//}


	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}

	UpdateData(FALSE);
}


void CFileListCreatorDlg::AddDirectorySTR_Func(){
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		LastPrevItemCount = m_xcList.GetItemCount();
		CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

		StatusStringSet(_T("AddDirectorySTR ���s��"),0,FALSE); //�ύX 2012.06.14

		int myResult;
		if(m_xcList.GetSelectedCount()==0){
			myResult = MessageBox(_T("�A�C�e�����I������Ă��܂���B���X�g�シ�ׂẴA�C�e���̏��Ƀt�H���_����t�����܂����H"),_T("AddDirectorySTR"),MB_YESNOCANCEL);
			if (myResult==IDYES){
				int index = 0;

				while(index < CFileListCreatorDlg::m_xcList.GetItemCount()){
					AddDirectorySTR_Items(index);
					index++;
				}
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("AddDirectorySTR �L�����Z��"),300,FALSE);
				return;
			}
		}
		if(m_xcList.GetSelectedCount()>=1){
			myResult = MessageBox(_T("�I�����ꂽ�A�C�e���̏��Ƀt�H���_����t�����܂����H"),_T("AddDirectorySTR"),MB_YESNOCANCEL);
			if (myResult==IDYES){
				int index = -1;

				while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
				        (index, LVNI_ALL | LVNI_SELECTED)) != -1){
					AddDirectorySTR_Items(index);
				}
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("AddDirectorySTR �L�����Z��"),300,FALSE);
				return;
			}
		}
	}
	
	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}

	CFileListCreatorDlg::StatusStringSet(_T("AddDirectorySTR �I��"),300,TRUE);

}

void CFileListCreatorDlg::AddDirectorySTR_Items(int index){
	//LVITEM       lvi;
	int          err = 0;
	CString      str;	
	CString      FullPathString;
	
	lvi.mask = LVIF_TEXT;// | LVIF_PARAM; //�f�[�^�̍X�V���ɕK�v�I�I

	//UpdateData();

	CString myFileName;	

	FullPathString =_T("");
	myFileName=_T("");


	// �t���p�X
	if (!err)
	{
		FullPathString = CFileListCreatorDlg::m_xcList.GetItemText(index,2);
		//FullPathString.Replace(_T("%"),_T("%%"));
	}

	CString keepFileName;
	// �t�@�C����
	if (!err)
	{
		myFileName = CFileListCreatorDlg::m_xcList.GetItemText(index,3);
		keepFileName = myFileName;
		//FullPathString.Replace(_T("%"),_T("%%"));
	}

    //CString FullPathString2;

	int SearchIDX;

	// �t�@�C����
	if (!err)
	{
		int PathSeparatorCNT=0;

        SearchIDX = 0;

		while (SearchIDX <= myFileName.GetLength()-1){            
			if(myFileName.Mid(SearchIDX,1)==_T("/")){
				PathSeparatorCNT++;
			}
            SearchIDX ++;
		}

		if(myFileName!=_T("")){
			myFileName.Replace( _T("/"),_T("\\"));
		}

		if(PathSeparatorCNT==0){
			PathSeparatorCNT=1;
		}

        SearchIDX = 0;

        while (1){
            if(FullPathString.GetLength() >= 1){
                if(FullPathString.Right(1) == _T("\\")){
                    FullPathString =FullPathString.Mid(0,FullPathString.GetLength() - 2);
				}else{
                    break;
                }
            }else{
                break;
            }
        }

        SearchIDX = FullPathString.GetLength()-1;

		//FullPathString2 = _T("");

		while (SearchIDX >= 0 && PathSeparatorCNT>=0){
            if(FullPathString.Mid(SearchIDX,1)==_T("\\")){
				PathSeparatorCNT--;
			}
            SearchIDX--;
		}


		CString  FolderPathString  = _T("");
		FolderPathString = CurrentDirFunc(FullPathString,FALSE);

		if (keepFileName !=_T("")){
			keepFileName.Replace( _T("/"),_T("\\"));
		}

		myFileName = FullPathString.Mid(SearchIDX + 1, FolderPathString.GetLength()-SearchIDX)  + FullPathToFileName(keepFileName);
		
		if (myFileName !=_T("")){
			myFileName.Replace(_T("\\"), _T("/"));
		}
	}

	// �t�@�C����
	if (!err)
	{
		lvi.iItem = index;
		lvi.iSubItem = 3;			
		//lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileName));
		lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileName));
		if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;			
	}

	UpdateData(FALSE);
}


void CFileListCreatorDlg::SetSEQ_NUM_Func(BOOL NotConfirm){
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		StatusStringSet(_T("SetSEQ_NUM ���s��"),0,FALSE); //�ύX 2012.06.14
		if (NotConfirm==TRUE){
			int index = 0;

			while(index < CFileListCreatorDlg::m_xcList.GetItemCount()){
				SetSEQ_NUM_Items(index);
				index++;
			}
		}else{
			int myResult;
			if(m_xcList.GetItemCount()>=0){
				myResult = MessageBox(_T("���X�g�̔ԍ����ēx�P���珇�ɘA�ԂŃZ�b�g���܂����H"),_T("RSetSEQ_NUM"),MB_YESNOCANCEL);
				if (myResult==IDYES){
					int index = 0;

					while(index < CFileListCreatorDlg::m_xcList.GetItemCount()){
						SetSEQ_NUM_Items(index);
						index++;
					}
				}else{
					CFileListCreatorDlg::StatusStringSet(_T("SetSEQ_NUM �L�����Z��"),300,FALSE);
					return;
				}
			}
		}
	}
	CFileListCreatorDlg::StatusStringSet(_T("SetSEQ_NUM �I��"),300,TRUE);

}

void CFileListCreatorDlg::SetSEQ_NUM_Items(int index){

	//LVITEM       lvi;
	int          err = 0;
	CString		str;

	lvi.mask = LVIF_TEXT;// | LVIF_PARAM; //�f�[�^�̍X�V���ɕK�v�I�I

	//UpdateData();

	// NO.

	if (!err)
	{
		lvi.iItem = index;
		lvi.iSubItem = 1; //NO.
		//lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileName));
		str.Format(_T("%d"), index + 1);	//�ʂ��ԍ�
		lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));
		if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;			
	}

	UpdateData(FALSE);
}


CString CFileListCreatorDlg::AddTagFunc(int workRow,int workColumn ){
	//LVITEM       lvi;
	CString      str;	
	
	lvi.mask =  LVIF_TEXT ;// | LVIF_PARAM; //�f�[�^�̍X�V���ɕK�v�I�I

	CString tempStr;

	tempStr = CFileListCreatorDlg::m_xcList.GetItemText(workRow,workColumn);
		//FullPathString.Replace(_T("%"),_T("%%"));

	if (tempStr !=_T("")){
		tempStr.Replace(_T("&"), _T("&amp;"));//�ŏ��ɕϊ�

		tempStr.Replace(_T("<"), _T("&lt;"));
		tempStr.Replace(_T(">"), _T("&gt;"));
		tempStr.Replace(_T("\""), _T("&quot;"));
    
		if (workColumn == 3 || workColumn == 8){
			tempStr.Replace(_T(" "), _T("&nbsp;"));
		}
		tempStr.Replace(_T("(c)"), _T("&copy;"));
		tempStr.Replace(_T("(r)"), _T("&reg;"));
	}


    if(workColumn == 6 || workColumn == 7) {
        if (tempStr == _T("")){
            //tempStr = _T("-"); //�R�����g�� 2011.10.10
		}else{
            if(g_RadioModifyDate == 2){//ModifyDateNoExport�̎�
				tempStr = _T("");
                //return tempStr;
			}
		}
	}

    if(workColumn == 8) {
		if(g_RadioRemarksColumn == 2){//RadioRemarksColumnNoExport�̎�
			tempStr = _T("");
            //return tempStr;
		}
		if(g_RadioRemarksColumn == 0){//RemarksColumnVisible�̎�
			if(tempStr == _T("")){
				tempStr = _T("&nbsp;&nbsp;&nbsp;");
			}
            //return tempStr;
		}
	}

//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
	if(workColumn == 1 || workColumn == 3 || workColumn == 4){

		if(g_ChkCopyOn == TRUE || g_ChkRedOn == TRUE){
			if(workColumn == 3){
				int FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(workRow);

				if(FormatDataNum == 11){
					return tempStr;
				}

				if(FormatDataNum == 12){
					if(g_ChkCopyOn == TRUE){
						tempStr = _T("<b>") + tempStr + _T("</b>");
					}
				}

				if(FormatDataNum == 22){
					if(g_ChkCopyOn == TRUE){
						tempStr = _T("<b>") + tempStr + _T("</b>");
					}
				}

				if(FormatDataNum == 21){
					if(g_ChkRedOn == TRUE){
						tempStr = _T("<font color=\"red\">") + tempStr + _T("</font>");
					}
				}

				if(FormatDataNum == 22){
					if(g_ChkRedOn == TRUE){
						tempStr = _T("<font color=\"red\">") + tempStr + _T("</font>");
					}
				}
			}
		}
	}else{
		if(workColumn == 2 || workColumn == 5 || workColumn == 7){ //�t���p�X �f�[�^�T�C�Y �C������
			tempStr = _T("<!---") + tempStr + _T("--->");
		}else if(workColumn == 6 && g_RadioModifyDate == 1){//ModifyDateInvisible
			tempStr = _T("<!---") + tempStr + _T("--->");
		}else if(workColumn == 6 && g_RadioModifyDate == 0){//ModifyDateVisible
		}else if(workColumn == 8 && g_RadioRemarksColumn == 1){//RemarksColumnInvisible
			tempStr = _T("<!---") + tempStr + _T("--->");
		}else if(workColumn == 8 && g_RadioRemarksColumn == 0){//RemarksColumnVisible
		}
	}
	return tempStr;
}

//=================================================




CString CreateDate(){
	CTime    cTime;
	CString  str;

	cTime = CTime::GetCurrentTime();           // ���ݎ���
	str = cTime.Format("%Y/%m/%d");   // "YYYY/mm/dd HH:MM:SS"�`���̎�����������擾

    return  str;
}

CString CFileListCreatorDlg::CreateDateTime(int mySwitch){//mySwitch//1:�t�@�C�����ɕt�^�������//2:���݂̎��Ԃ�\��
	CTime    cTime;
	CString  str;
	//2010.07.09_16-42-30

	switch(mySwitch){
		case 1:
			cTime = CTime::GetCurrentTime();           // ���ݎ���
			str = cTime.Format("%Y.%m.%d_%H-%M-%S");   // "YYYY/mm/dd HH:MM:SS"�`���̎�����������擾
			break;
		case 2:
			cTime = CTime::GetCurrentTime();           // ���ݎ���
			str = cTime.Format("%Y/%m/%d %H:%M:%S");   // "YYYY/mm/dd HH:MM:SS"�`���̎�����������擾
			break;
		default:
			break;					
	}
	return  str;
}


CString CFileListCreatorDlg::ProhibitFileName(CString tempFileName , BOOL AutoSkipMode){
//''���֎~����  \ / : * ? " < > |

	if(tempFileName == _T("")){
		return _T("");
	}
    
    BOOL illegalStrFLG;
    
    illegalStrFLG = FALSE;
    
    if(tempFileName.Find(_T("\\"),0)>=0){
        illegalStrFLG = TRUE;
	}

    if(tempFileName.Find(_T("/"),0)>=0){
        illegalStrFLG = TRUE;
	}

    if(tempFileName.Find(_T(":"),0)>=0){
        illegalStrFLG = TRUE;
	}

    if(tempFileName.Find(_T("*"),0)>=0){
        illegalStrFLG = TRUE;
	}

    if(tempFileName.Find(_T("\?"),0)>=0){
        illegalStrFLG = TRUE;
	}

    if(tempFileName.Find( _T("\""),0)>=0){
        illegalStrFLG = TRUE;
	}

    if(tempFileName.Find( _T("<"),0)>=0){
        illegalStrFLG = TRUE;
	}

    if(tempFileName.Find( _T(">"),0)>=0){
        illegalStrFLG = TRUE;
	}

    if(tempFileName.Find( _T("|"),0)>=0){
        illegalStrFLG = TRUE;
	}
    
	if(illegalStrFLG == FALSE){
        return tempFileName;
	}

    if(AutoSkipMode == TRUE){
		if (tempFileName !=_T("")){
			tempFileName.Replace(_T("\\"), _T("_"));
			tempFileName.Replace(_T("/"), _T("_"));
			tempFileName.Replace(_T(":"), _T("_"));
			tempFileName.Replace(_T("*"), _T("_"));
			tempFileName.Replace(_T("\?"), _T("_"));
			tempFileName.Replace(_T("\""), _T("_"));
			tempFileName.Replace(_T("<"), _T("_"));
			tempFileName.Replace(_T(">"), _T("_"));
			tempFileName.Replace(_T("|"), _T("_"));
		}
        return tempFileName;
	}

	int myResult;

    myResult = MessageBox(_T("�t�@�C�����Ɉȉ��̕����͎g�p�ł��܂���B\r\n�֎~������ _ �ɒu�������܂����H (�u�������v��I�������ꍇ�́A�폜���܂��B)\r\n \\ / : * \? \" < > |"), _T("�֎~����"), MB_YESNOCANCEL);

    if(myResult == IDYES){
		if (tempFileName !=_T("")){
			tempFileName.Replace(_T("\\"), _T("_"));
			tempFileName.Replace(_T("/"), _T("_"));
			tempFileName.Replace(_T(":"), _T("_"));
			tempFileName.Replace(_T("*"), _T("_"));
			tempFileName.Replace(_T("\?"), _T("_"));
			tempFileName.Replace(_T("\""), _T("_"));
			tempFileName.Replace(_T("<"), _T("_"));
			tempFileName.Replace(_T(">"), _T("_"));
			tempFileName.Replace(_T("|"), _T("_"));
		}
        return tempFileName;
	}else if(myResult == IDNO){
		if (tempFileName !=_T("")){
			tempFileName.Replace(_T("\\"), _T(""));
			tempFileName.Replace(_T("/"), _T(""));
			tempFileName.Replace(_T(":"), _T(""));
			tempFileName.Replace(_T("*"), _T(""));
			tempFileName.Replace(_T("\?"), _T(""));
			tempFileName.Replace(_T("\""), _T(""));
			tempFileName.Replace(_T("<"), _T(""));
			tempFileName.Replace(_T(">"), _T(""));
			tempFileName.Replace(_T("|"), _T(""));
		}
        return tempFileName;
	}else if(myResult == IDCANCEL){
        return _T("");
	}
	return _T("");
}


CString WindowsFolder_Func(){
//http://www.sabamiso.net/yoggy/hiki/?Windows%A4%CE%C6%C3%CA%CC%A4%CA%A5%D5%A5%A9%A5%EB%A5%C0%A4%CE%A5%D1%A5%B9%A4%F2%BC%E8%C6%C0%A4%B9%A4%EB%CA%FD%CB%A1(My+Documents%A4%C8%A4%AB)
	//�g����萔�͉��L�̂悤�Ȋ���
	//	SIDL_DESKTOP         �f�X�N�g�b�v(�l�[���X�y�[�X�̃��[�g�ɂ��鉼�z�t�H���_)
	//	CSIDL_DESKTOPDIRECTOY �f�X�N�g�b�v�̃t�@�C���𕨗��I�Ɋi�[����t�H���_
	//	CSIDL_STARTMENU       �X�^�[�g���j���[
	//	CSIDL_PROGRAMS        �v���O�������j���[
	//	CSIDL_PERSONAL        �}�C �h�L�������g
	//	CSIDL_PROGRAM_FILES   Program Files
	//	CSIDL_FAVORITES       ���C�ɓ���
	//	CSIDL_APPDATA         �A�v���P�[�V�����f�[�^
	//	CSIDL_COMMON_xxx      ����(All Users)�̃t�H���_

	TCHAR szPath[_MAX_PATH];
	LPITEMIDLIST pidl;
	HWND hWnd = NULL;

	IMalloc *pMalloc;
	SHGetMalloc( &pMalloc );

	if( SUCCEEDED(SHGetSpecialFolderLocation(hWnd,CSIDL_PERSONAL,&pidl)) ){
		SHGetPathFromIDList(pidl,szPath); // �p�X�ɕϊ�����
		pMalloc->Free(pidl);              // �擾����IDL��������� (CoTaskMemFree�ł���)
	}

	pMalloc->Release();
	//MessageBox(szPath,_T(""),MB_OK);
	CString str;
	str = szPath;
	if (str !=_T("")){
		str.Replace(_T("\\"),_T("\\\\"));
	}
	return  str;
}
//====================================================


void CFileListCreatorDlg::StrToTagSign(){
	//_wsetlocale(LC_ALL, _T("jpn"));
	StatusStringSet(_T(" < �� > �Ȃǂ̋L����ϊ���"),0,FALSE);

	//LVITEM       lvi;
	CString      str;	
	
	lvi.mask =  LVIF_TEXT ;// | LVIF_PARAM; //�f�[�^�̍X�V���ɕK�v�I�I

    ULONGLONG LastRow;
    
    LastRow = CFileListCreatorDlg::m_xcList.GetItemCount();
    
	ULONGLONG workRow;

    workRow = 0;
    
    while (workRow < LastRow){

        //CFileListCreatorDlg::m_xcList.EnsureVisible(workRow, FALSE);
     
        int columnIDX;
        
		for( columnIDX = 2; columnIDX <= 9; columnIDX++){
            CString tempStr;
            tempStr = CFileListCreatorDlg::m_xcList.GetItemText(workRow,columnIDX);

			tempStr.Replace(_T("&lt;"), _T("<"));
			tempStr.Replace(_T("&gt;"), _T(">"));
			tempStr.Replace(_T("&quot;"), _T("\""));
    
			tempStr.Replace(_T("&nbsp;"), _T(" "));
			tempStr.Replace(_T("&copy;"), _T("(c)"));
			tempStr.Replace(_T("&reg;"), _T("(r)")); 
			tempStr.Replace(_T("&amp;"), _T("&"));//�Ō�ɒu��

			lvi.iItem = workRow;
			lvi.iSubItem = columnIDX; //NO.
			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
			CFileListCreatorDlg::m_xcList.SetItem(&lvi);
		}
		workRow = workRow + 1;
	}
    
	StatusStringSet(_T(" < �� > �Ȃǂ̋L���𐳂����ϊ����܂���"),0,FALSE);
	//_wsetlocale(LC_ALL, _T(""));
}




void CFileListCreatorDlg::ExportFileList(BOOL AutoSaveFLG){ //�폜 BOOL ReExportFLG
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1 && AutoSaveFLG == FALSE) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	if (ListDataNoChange_FLG == TRUE && AutoSaveFLG == TRUE) return; //�ǉ� 2012.05.13

	FLC_CurrentVersion= _T("FileListCreator 2.8.6 (VC++)");


    CFileListCreatorDlg::StatusStringSet(_T("HTML �o�͒�"),0,FALSE);

    BOOL CurrentDirectory_FLG;
    CurrentDirectory_FLG = FALSE;


	if( AutoSaveFLG == TRUE ){
		g_RadioENCODING_SELECT = 1;
	}

	if (AutoSaveFLG == FALSE) {
		int myResult;

		myResult = MessageBox(_T("���A�v���P�[�V����������f�B���N�g���Ƀ��X�g���o�͂��܂����H \r\n\r\n�u�͂��v �J�����g�t�H���_�[�ɕۑ� \r\n�u�������v �}�C�h�L�������g�ɕۑ�"),_T("�o�͐�"),MB_YESNOCANCEL);
		if(myResult==IDYES){
			CurrentDirectory_FLG = TRUE;
		}else if(myResult==IDCANCEL){
			CFileListCreatorDlg::StatusStringSet(_T("Export �o�͐�w�� �L�����Z��"),0,TRUE);
			return;
		}
	}

    CString FileName;

	if (AutoSaveFLG == FALSE) {
		//���[�_��
		InputBoxDlg m_dlg;
		//m_dlg.DoModal();

		//FileName = InputBox("�t�@�C���ɖ��O�����ĉ������B", "���O�����ĕۑ�", CreateDateTime)

		if (m_dlg.DoModal()==IDOK){
			FileName = _T("");
			FileName = m_dlg.ExportFileName;
		}else{
			FileName = _T("");
		}
	}
	//FileName = CreateDateTime(1);//��ŏ���

	if (AutoSaveFLG == TRUE) {
		//CurrentDirectory_FLG = TRUE;
		FileName = _T("AutoSave");
	}else{
		FileName = ProhibitFileName(FileName, FALSE);
    
		if(FileName == _T("")){
			//MessageBox(_T("�o�͂��L�����Z������܂����B�f�t�H���g�̓��t���t�@�C�����ɂ���ۂ́A���̂܂܁uOK�{�^���v���N���b�N���ĉ������B"), _T("�o�̓L�����Z��"),MB_YESNOCANCEL);
			CFileListCreatorDlg::StatusStringSet(_T("Export �o�̓t�@�C���� ������"),0,TRUE);
			return;
		}
	}



	CString saveDir = _T("");

	//// �J�����g�f�B���N�g���̎擾
	//TCHAR szCurrentDir[_MAX_PATH];
	//GetCurrentDirectory(_MAX_PATH,szCurrentDir);
	
	//CString CurDir;
	//CurDir = szCurrentDir;

	//http://rararahp.cool.ne.jp/vc/vctips/api.htm
	// ���s�t�@�C���̃t���p�X�擾
	TCHAR szPath[_MAX_PATH];
	GetModuleFileName( NULL, szPath, MAX_PATH);

	//// �t���p�X�𕪉�
	//TCHAR szDir[_MAX_DIR];
	//TCHAR szDrive[_MAX_DRIVE];
	//TCHAR szFName[_MAX_FNAME];
	//TCHAR szExt[_MAX_EXT];
	//_splitpath(szPath,szDrive,szDir,szFName,szExt);
	//
	//// �t�H���_�A�t�@�C�����擾
	//TCHAR szFilePath[_MAX_PATH];
	//TCHAR szFileName[_MAX_PATH];
	//sprintf(szFilePath,"%s%s",szDrive,szDir);
	//sprintf(szFileName,"%s%s",szFName,szExt);

	CString CurDir;

	CurDir = CurrentDirFunc(szPath,TRUE);
	if (CurDir !=_T("")){
		CurDir.Replace(_T("\\"),_T("\\\\"));
	}
	if(CurrentDirectory_FLG == FALSE && AutoSaveFLG == FALSE) {
		saveDir = WindowsFolder_Func() + _T("\\\\") + _T("FileListCreator(LIST)") + _T("\\\\");
	}else{
		if (AutoSaveFLG == TRUE) {
			//CurrentDirectory_FLG = TRUE;
			//FileName = _T("AutoSave");
			saveDir = CurDir + _T("\\\\") + _T("FileListCreator(Pref)") + _T("\\\\");
		}else{
			saveDir = CurDir + _T("\\\\") + _T("FileListCreator(LIST)") + _T("\\\\");
		}
	}

	if(CreateDirectory(saveDir,NULL)){

	}else{
			
	}


	int OverwriteConfirm;
	OverwriteConfirm = IDYES;

	CString htmlFileName;
	htmlFileName = FileName + _T(".html");

	BOOL FileExistFLG = FALSE;

	if ( AutoSaveFLG == FALSE ) {
		if ( PathFileExists(saveDir + htmlFileName) ){
			FileExistFLG = TRUE;
			OverwriteConfirm = MessageBox(_T("�����̃t�@�C�������݂��܂��B�㏑�����܂����H") ,_T("�㏑���m�F"), MB_YESNOCANCEL );
		}
	}

	if (IDYES == OverwriteConfirm ){
		if ( AutoSaveFLG == FALSE ) {
			if ( FileExistFLG == TRUE ){
				CFileListCreatorDlg::StatusStringSet(_T("�㏑���ۑ����܂���"),0,TRUE);
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("�V�K�ۑ����܂���"),0,TRUE);
			}
		}
		CFileListCreatorDlg::ExportFileList_Func(saveDir,FileName); //AutoSave�̎����o�� //�ύX 2012.06.14
	}else{
		CFileListCreatorDlg::StatusStringSet(_T("�㏑�� �L�����Z��"),300,TRUE);
		return;
	}

	FILE *fp;
	_tfopen_s(&fp,saveDir + htmlFileName, _T("r, ccs=UNICODE")); //http://msdn.microsoft.com/ja-jp/library/yeby3zcb(v=vs.100).aspx
	CStdioFile stdFile(fp); //http://oshiete.goo.ne.jp/qa/7431848.html
	
	int err = 0;

	CString LastLine;
	CString Line;

	Line = _T("");

	while (!err) {
		if (stdFile.ReadString(Line) == FALSE) err = 1;
		if (Line!=_T("")){
			LastLine = Line;
		}
	}
	fclose(fp);

	if ( LastLine.Find(_T("</body></html>"),0 ) != 0 ){
		int myResult;
		myResult = MessageBox(_T("�o�͂ł��Ȃ����������o����܂����B���X�g�t�@�C���͕s���S�ȏ�Ԃł��B���j�R�[�h�ōďo�͂��܂����H\r\n\r\n�u�͂��v�ďo��\r\n�u�������v���s\r\n�u�L�����Z���v�I��") ,_T("�ďo�͊m�F"), MB_YESNOCANCEL );

		if (IDYES == myResult){
			//�t�@�C���ďo�͏���

			CFileListCreatorDlg::StatusStringSet(_T("���X�g���ďo�͒�"),0,FALSE);

			g_RadioENCODING_SELECT = 1;

			CFileListCreatorDlg::ExportFileList_Func(saveDir,FileName);
			CFileListCreatorDlg::StatusStringSet(_T("���X�g���ďo�͂��܂���"),300,TRUE);
		}else if (IDNO == myResult){
			StatusStringSet(_T("�V�t�g�i�h�r�ŏo�͂𑱍s���܂�"),300,TRUE);
		}else if (IDCANCEL == myResult){
			StatusStringSet(_T("�ꎞ�t�@�C�����폜���܂���"),300,TRUE);
			DeleteFile(saveDir + htmlFileName); //http://www.ujasiri.com/prglib/vc/filectrl/vc_delfile.html
			DeleteFile(saveDir + FileName + _T(".txt")); //http://www.ujasiri.com/prglib/vc/filectrl/vc_delfile.html
			g_NoDrawFLG = FALSE;
			RedrawWindow();
			return;
		}
	}

	if (AutoSaveFLG == FALSE) {
		if (CurrentDirectory_FLG == FALSE){
			MessageBox(_T("�u") + FileName + _T("�v�Ƃ������O�Ń��X�g�t�@�C��(html,text)���}�C�h�L�������g�ɏo�͂��܂���"),_T("���X�g�G�N�X�|�[�g�I��"),MB_OK);
		}else{
			MessageBox(_T("�u") + FileName + _T("�v�Ƃ������O�Ń��X�g�t�@�C��(html,text)���o�͂��܂���"),_T("���X�g�G�N�X�|�[�g�I��"),MB_OK);
		}
	}

	//saveDir = _T("\"") + saveDir +  _T("\"");
	//FileName = _T("\"") + FileName +  _T("\"");

	if (AutoSaveFLG == FALSE) {
		//FolderPath.Replace(_T("\\"),_T("\\\\"));
		//http://oshiete.goo.ne.jp/qa/976818.html
		

		///saveDir.Replace(_T("\\\\"),_T("\\"));

		TRACE(_T("��FileName��%s \r\n" ),FileName);
		TRACE(_T("��saveDir��%s \r\n" ),saveDir);

		//http://oshiete.goo.ne.jp/qa/2193377.html
		SetCurrentDirectory(saveDir); //�K�v

		//ShellExecute(handle, "find", path_to_folder, NULL, NULL, 0);

		////���G�N�X�v���[���ŊJ���i���̃\�[�X�j
		//ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), _T("/select,") + FileName , saveDir, SW_SHOWNORMAL );

		////���G�N�X�v���[���ŊJ���i�񓚎җl�̃\�[�X�j//http://oshiete.goo.ne.jp/qa/7388913.html
		//ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), _T("/select,") + saveDir + FileName, NULL, SW_SHOWNORMAL );

		////////���G�N�X�v���[���ŊJ��
		//CString strArgs; 
		//strArgs = _T("/select, \"");
		//strArgs +=saveDir + FileName; 
		//strArgs += _T("\"");

		//ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), strArgs, NULL, SW_SHOWNORMAL );

		//////���G�N�X�v���[���ŊJ��  //http://msdn.microsoft.com/ja-jp/library/cc422072.aspx
		ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), _T("/select,.\\" + htmlFileName) , saveDir, SW_SHOWNORMAL );

		////http://msdn.microsoft.com/en-us/library/windows/desktop/bb762153(v=vs.85).aspx
		//ShellExecute( NULL, _T("find"), saveDir, NULL , NULL, SW_SHOWNORMAL );

			ShellExecuteOpenFLG = TRUE; //���P�̍� //��Œ��� //�ǉ� 2012.06.14

				LastPrevItemCount = m_xcList.GetItemCount();
				CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02 //�d�v 2012.06.01

			ShellExecuteOpenFLG = FALSE; //���P�̍� //��Œ��� //�ǉ� 2012.06.14

		//int i=0;

		//for (i=0;i<100;i++){
		//	CFileListCreatorDlg::StatusStringSet(_T("Export �I������"),0,FALSE);
		//}

		////http://oshiete.goo.ne.jp/qa/7388913.html
		//ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), strArgs , NULL, SW_SHOWNORMAL );
		
		//http://oshiete.goo.ne.jp/qa/2193377.html
		
		//http://q.hatena.ne.jp/1108505976
	}

	//http://support.microsoft.com/kb/152457/ja
	
	//http://stackoverflow.com/questions/3010305/programmatically-selecting-file-in-explorer

	CFileListCreatorDlg::StatusStringSet(_T("Export �I��"),300,TRUE);
	UpdateData(FALSE); //�ύX RedrawWindow(); //�ǉ� 2012.05.04

}


void CFileListCreatorDlg::ExportFileList_Func(CString saveDir, CString FileName){ //�ǉ� 2012.04.22



	ESCAPE_FLG = FALSE;

	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	
	//CFileListCreatorDlg::SelectALL_CancellationFunc(); //�R�����g�� 2012.06.01

	g_NoDrawFLG = TRUE; //�R�����g�� 2012.06.14

	//http://truthandhope.dousetsu.com/link/learn/learn_class/page1_class/page3_class/page28.html

    //wchar_t *locale = NULL;         //�V�X�e���̕����Z�b�g�i�[�p

    //locale = _wsetlocale(LC_CTYPE, L"");    //�V�X�e�������Z�b�g�擾
    //_wsetlocale(LC_ALL, locale);            //�Ή���Z�b�g

	 //http://gurizuri0505.halfmoon.jp/develop/cplusplus/cstdiofile
	 //_wsetlocale(LC_ALL, _T("jpn"));
	 //_wsetlocale(LC_ALL, L"");

	_wsetlocale(LC_ALL, L"Japanese");
	//_tsetlocale(LC_ALL, _T("Japanese_Japan.932")); //http://cx5software.com/article_vcpp_unicode/

//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������

    CString writeData;
    CString Temp;

	int index = 0;

	while(index < CFileListCreatorDlg::m_xcList.GetItemCount()){
		SetSEQ_NUM_Items(index);
		index++;
	}

	int i;
	int MaxCnt;
	MaxCnt = CFileListCreatorDlg::m_xcList.GetItemCount()-1;

	CString str1;

    if ( g_RadioModifyDate ==2 && g_RadioRemarksColumn == 2 ){//"<!---FLC Generator Version 1.3--->"
        outGeneratorVer = _T("<!---FLC Generator Version 1.3--->");
        i = 0;
        Temp = _T("");
        Temp = Temp + _T("\n") + _T("<caption>");
        Temp = Temp + FLC_CurrentVersion+ _T("&nbsp;");
        Temp = Temp + CreateDateTime(2) + _T("</caption>") + _T("\n");
				//CString CreateDateTime(int mySwitch){//mySwitch//1:�t�@�C�����ɕt�^�������//2:���݂̎��Ԃ�\��
		while (i <= MaxCnt){

			MSG msg; //�ǉ� 2011.10.12
			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						ESCAPE_FLG = TRUE;
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			//StatusString.Format(_T("HTML �o�� ���s�� ( %d / %d )"),i+1,MaxCnt+1);
   //         CFileListCreatorDlg::StatusStringSet(StatusString,100,FALSE);

            Temp = Temp + _T("<tr>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 1) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 3) + AddTagFunc(i, 2) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 4) + AddTagFunc(i, 5) + AddTagFunc(i, 6) + AddTagFunc(i, 7) + _T("</td>");
            Temp = Temp + _T("</tr>"); //'+ vbNewLine

            Temp = Temp + _T("\n");

			str1.Format(_T("HTML �G�N�X�|�[�g ���s�� ( %d / %d ) "),i+1,MaxCnt+1);
			CFileListCreatorDlg::StatusStringSet(str1,0,FALSE);

			//CFileListCreatorDlg::m_xcList.EnsureVisible(i, FALSE);
            i = i + 1;
		}
	}else if( g_RadioModifyDate == 0 && g_RadioRemarksColumn == 2 ){ // '' "<!---FLC Generator Version 1.4.1--->"
        outGeneratorVer = _T("<!---FLC Generator Version 1.4.1--->");  //''���X�V�� �\��
        i = 0;
        Temp = _T("");
        Temp = Temp + _T("\n") + _T("<caption>");
        Temp = Temp + FLC_CurrentVersion + _T("&nbsp;");
        Temp = Temp + CreateDateTime(2) + _T("</caption>") + _T("\n");
    
		while (i <= MaxCnt){

			MSG msg; //�ǉ� 2011.10.12
			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						ESCAPE_FLG = TRUE;
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			//StatusString.Format(_T("HTML �o�� ���s�� ( %d / %d )"),i+1,MaxCnt+1);
   //         CFileListCreatorDlg::StatusStringSet(StatusString,100,FALSE);

            Temp = Temp + _T("<tr>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 1) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 3) + AddTagFunc(i, 2) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 4) +  AddTagFunc(i, 5) + _T("</td>") +
                    _T("<td>") + AddTagFunc(i, 6) + AddTagFunc(i, 7) + _T("</td>");
            Temp = Temp + _T("</tr>"); //'+ vbNewLine

            Temp = Temp + _T("\n");

			str1.Format(_T("HTML �G�N�X�|�[�g ���s�� ( %d / %d ) "),i+1,MaxCnt+1);
			CFileListCreatorDlg::StatusStringSet(str1,0,FALSE);

			//CFileListCreatorDlg::m_xcList.EnsureVisible(i, FALSE);
            i = i + 1;
		}
	}else if( g_RadioModifyDate == 1 && g_RadioRemarksColumn == 2 ){//  '' "<!---FLC Generator Version 1.4.2--->"
        outGeneratorVer = _T("<!---FLC Generator Version 1.4.2--->");// ''���X�V�� ��\��
        i = 0;
        Temp = _T("");
        Temp = Temp + _T("\n") + _T("<caption>");
        Temp = Temp + FLC_CurrentVersion+ _T("&nbsp;");
        Temp = Temp + CreateDateTime(2) + _T("</caption>") + _T("\n");
    
		while (i <= MaxCnt){

			MSG msg; //�ǉ� 2011.10.12
			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						ESCAPE_FLG = TRUE;
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			//StatusString.Format(_T("HTML �o�� ���s�� ( %d / %d )"),i+1,MaxCnt+1);
			//CFileListCreatorDlg::StatusStringSet(StatusString,0,FALSE);

            Temp = Temp + _T("<tr>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 1) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 3) + AddTagFunc(i, 2) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 4) + AddTagFunc(i, 5) + _T("</td>") + 
				AddTagFunc(i, 6) + AddTagFunc(i, 7);
            Temp = Temp + _T("</tr>"); //'+ vbNewLine

            Temp = Temp + _T("\n");
			
			str1.Format(_T("HTML �G�N�X�|�[�g ���s�� ( %d / %d ) "),i+1,MaxCnt+1);
			CFileListCreatorDlg::StatusStringSet(str1,0,FALSE);

			//CFileListCreatorDlg::m_xcList.EnsureVisible(i, FALSE);
            i = i + 1;
		}
	}else if( g_RadioModifyDate == 0 && g_RadioRemarksColumn == 0 ){ // '' "<!---FLC Generator Version 1.5.1--->"
        outGeneratorVer = _T("<!---FLC Generator Version 1.5.1--->");  //''���X�V�� �\�� //�����l�� �\��
        i = 0;
        Temp = _T("");
        Temp = Temp + _T("\n") + _T("<caption>");
        Temp = Temp + FLC_CurrentVersion + _T("&nbsp;");
        Temp = Temp + CreateDateTime(2) + _T("</caption>") + _T("\n");
    
		while (i <= MaxCnt){

			MSG msg; //�ǉ� 2011.10.12
			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						ESCAPE_FLG = TRUE;
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			//StatusString.Format(_T("HTML �o�� ���s�� ( %d / %d )"),i+1,MaxCnt+1);
   //         CFileListCreatorDlg::StatusStringSet(StatusString,100,FALSE);

            Temp = Temp + _T("<tr>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 1) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 3) + AddTagFunc(i, 2) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 4) +  AddTagFunc(i, 5) + _T("</td>") +
                    _T("<td>") + AddTagFunc(i, 6) + AddTagFunc(i, 7) + _T("</td>") +
					_T("<td>") + AddTagFunc(i, 8) + _T("</td>");//�����l�� �\��
            Temp = Temp + _T("</tr>"); //'+ vbNewLine

            Temp = Temp + _T("\n");

			str1.Format(_T("HTML �G�N�X�|�[�g ���s�� ( %d / %d ) "),i+1,MaxCnt+1);
			CFileListCreatorDlg::StatusStringSet(str1,0,FALSE);

			//CFileListCreatorDlg::m_xcList.EnsureVisible(i, FALSE);
            i = i + 1;
		}
	}else if( g_RadioModifyDate == 0 && g_RadioRemarksColumn == 1 ){ // '' "<!---FLC Generator Version 1.5.2--->"
        outGeneratorVer = _T("<!---FLC Generator Version 1.5.2--->");  //''���X�V�� �\�� //�����l�� ��\��
        i = 0;
        Temp = _T("");
        Temp = Temp + _T("\n") + _T("<caption>");
        Temp = Temp + FLC_CurrentVersion + _T("&nbsp;");
        Temp = Temp + CreateDateTime(2) + _T("</caption>") + _T("\n");
    
		while (i <= MaxCnt){

			MSG msg; //�ǉ� 2011.10.12
			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						ESCAPE_FLG = TRUE;
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			//StatusString.Format(_T("HTML �o�� ���s�� ( %d / %d )"),i+1,MaxCnt+1);
   //         CFileListCreatorDlg::StatusStringSet(StatusString,100,FALSE);

            Temp = Temp + _T("<tr>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 1) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 3) + AddTagFunc(i, 2) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 4) +  AddTagFunc(i, 5) + _T("</td>") +
                    _T("<td>") + AddTagFunc(i, 6) + AddTagFunc(i, 7) + _T("</td>") +
					AddTagFunc(i, 8);//�����l�� ��\��
            Temp = Temp + _T("</tr>"); //'+ vbNewLine

            Temp = Temp + _T("\n");

			str1.Format(_T("HTML �G�N�X�|�[�g ���s�� ( %d / %d ) "),i+1,MaxCnt+1);
			CFileListCreatorDlg::StatusStringSet(str1,0,FALSE);

			//CFileListCreatorDlg::m_xcList.EnsureVisible(i, FALSE);
            i = i + 1;
		}
	}else if( g_RadioModifyDate == 1 && g_RadioRemarksColumn == 0 ){//  '' "<!---FLC Generator Version 1.5.3--->"
        outGeneratorVer = _T("<!---FLC Generator Version 1.5.3--->");//''���X�V�� ��\�� //�����l�� �\��
        i = 0;
        Temp = _T("");
        Temp = Temp + _T("\n") + _T("<caption>");
        Temp = Temp + FLC_CurrentVersion+ _T("&nbsp;");
        Temp = Temp + CreateDateTime(2) + _T("</caption>") + _T("\n");
    
		while (i <= MaxCnt){

			MSG msg; //�ǉ� 2011.10.12
			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						ESCAPE_FLG = TRUE;
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			//StatusString.Format(_T("HTML �o�� ���s�� ( %d / %d )"),i+1,MaxCnt+1);
			//CFileListCreatorDlg::StatusStringSet(StatusString,0,FALSE);

            Temp = Temp + _T("<tr>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 1) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 3) + AddTagFunc(i, 2) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 4) + AddTagFunc(i, 5) + _T("</td>") + 
					AddTagFunc(i, 6) + AddTagFunc(i, 7) +
					_T("<td>") + AddTagFunc(i, 8) + _T("</td>");//�����l�� �\��

            Temp = Temp + _T("</tr>"); //'+ vbNewLine

            Temp = Temp + _T("\n");
			
			str1.Format(_T("HTML �G�N�X�|�[�g ���s�� ( %d / %d ) "),i+1,MaxCnt+1);
			CFileListCreatorDlg::StatusStringSet(str1,0,FALSE);

			//CFileListCreatorDlg::m_xcList.EnsureVisible(i, FALSE);
            i = i + 1;
		}
	}else if( g_RadioModifyDate == 1 && g_RadioRemarksColumn == 1 ){//  '' "<!---FLC Generator Version 1.5.4--->"
        outGeneratorVer = _T("<!---FLC Generator Version 1.5.4--->");//''���X�V�� ��\�� //�����l�� ��\��
        i = 0;
        Temp = _T("");
        Temp = Temp + _T("\n") + _T("<caption>");
        Temp = Temp + FLC_CurrentVersion+ _T("&nbsp;");
        Temp = Temp + CreateDateTime(2) + _T("</caption>") + _T("\n");
    
		while (i <= MaxCnt){

			MSG msg; //�ǉ� 2011.10.12
			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						ESCAPE_FLG = TRUE;
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			//StatusString.Format(_T("HTML �o�� ���s�� ( %d / %d )"),i+1,MaxCnt+1);
			//CFileListCreatorDlg::StatusStringSet(StatusString,0,FALSE);

            Temp = Temp + _T("<tr>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 1) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 3) + AddTagFunc(i, 2) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 4) +  AddTagFunc(i, 5) + _T("</td>") +
                    AddTagFunc(i, 6) + AddTagFunc(i, 7)+
					AddTagFunc(i, 8); //�����l�� ��\��
            Temp = Temp + _T("</tr>"); //'+ vbNewLine

            Temp = Temp + _T("\n");
			
			str1.Format(_T("HTML �G�N�X�|�[�g ���s�� ( %d / %d ) "),i+1,MaxCnt+1);
			CFileListCreatorDlg::StatusStringSet(str1,0,FALSE);

			//CFileListCreatorDlg::m_xcList.EnsureVisible(i, FALSE);
            i = i + 1;
		}
	}else if( g_RadioModifyDate == 2 && g_RadioRemarksColumn == 0 ){//  '' "<!---FLC Generator Version 1.5.5--->"
        outGeneratorVer = _T("<!---FLC Generator Version 1.5.5--->");//''���X�V�� �G�N�X�|�[�g���Ȃ� //�����l�� �\��
        i = 0;
        Temp = _T("");
        Temp = Temp + _T("\n") + _T("<caption>");
        Temp = Temp + FLC_CurrentVersion+ _T("&nbsp;");
        Temp = Temp + CreateDateTime(2) + _T("</caption>") + _T("\n");
    
		while (i <= MaxCnt){

			MSG msg; //�ǉ� 2011.10.12
			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						ESCAPE_FLG = TRUE;
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			//StatusString.Format(_T("HTML �o�� ���s�� ( %d / %d )"),i+1,MaxCnt+1);
			//CFileListCreatorDlg::StatusStringSet(StatusString,0,FALSE);

            Temp = Temp + _T("<tr>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 1) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 3) + AddTagFunc(i, 2) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 4) +  AddTagFunc(i, 5) + _T("</td>") +
					_T("<td>") + AddTagFunc(i, 8) + _T("</td>");//�����l�� �\��
            Temp = Temp + _T("</tr>"); //'+ vbNewLine

            Temp = Temp + _T("\n");
			
			str1.Format(_T("HTML �G�N�X�|�[�g ���s�� ( %d / %d ) "),i+1,MaxCnt+1);
			CFileListCreatorDlg::StatusStringSet(str1,0,FALSE);

			//CFileListCreatorDlg::m_xcList.EnsureVisible(i, FALSE);
            i = i + 1;
		}
	}else if( g_RadioModifyDate == 2 && g_RadioRemarksColumn == 1 ){//  '' "<!---FLC Generator Version 1.5.6--->"
        outGeneratorVer = _T("<!---FLC Generator Version 1.5.6--->");//''���X�V�� �G�N�X�|�[�g���Ȃ� //�����l�� ��\��
        i = 0;
        Temp = _T("");
        Temp = Temp + _T("\n") + _T("<caption>");
        Temp = Temp + FLC_CurrentVersion+ _T("&nbsp;");
        Temp = Temp + CreateDateTime(2) + _T("</caption>") + _T("\n");
    
		while (i <= MaxCnt){

			MSG msg; //�ǉ� 2011.10.12
			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						ESCAPE_FLG = TRUE;
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			//StatusString.Format(_T("HTML �o�� ���s�� ( %d / %d )"),i+1,MaxCnt+1);
			//CFileListCreatorDlg::StatusStringSet(StatusString,0,FALSE);

            Temp = Temp + _T("<tr>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 1) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 3) + AddTagFunc(i, 2) + _T("</td>");
            Temp = Temp + _T("<td>") + AddTagFunc(i, 4) +  AddTagFunc(i, 5) + _T("</td>") +
					AddTagFunc(i, 8);//�����l�� ��\��
            Temp = Temp + _T("</tr>"); //'+ vbNewLine

            Temp = Temp + _T("\n");
			
			str1.Format(_T("HTML �G�N�X�|�[�g ���s�� ( %d / %d ) "),i+1,MaxCnt+1);
			CFileListCreatorDlg::StatusStringSet(str1,0,FALSE);

			//CFileListCreatorDlg::m_xcList.EnsureVisible(i, FALSE);
            i = i + 1;
		}
	}
    //Call StatusStringSet("")

    //Call myActivateFunc(6 + 1)


	//'    outGeneratorVer = "<!---" & "FLC Generator Version 1.3" & "--->"
	//MessageBox(_T("�X�g�b�v"));
	CFileListCreatorDlg::Total_Bytes_Bold();
    CFileListCreatorDlg::Total_Bytes_Func();
    //Call Total_Bytes_Bold(False)

    CString BoldItemStr;
    CString BoldItemCountStr;

	BoldItemCountStr.Format(_T("%I64u"),BolditemCount);

    if(BoldByteSum == 0 || g_ChkCopyOn == FALSE){
        BoldItemStr = _T("");
	}else{
        BoldItemStr = _T("<div align =\"right\"><b>COPY : ") + ByteCalculation(BoldByteSum,TRUE) + _T(" (") + BoldItemCountStr + _T("items)</b></div>\n");
	}
    
    CString TotalItems;
    TotalItems = _T("");

    CString w_TotalItems;
    w_TotalItems = _T("");

    w_TotalItems.Format(_T("<!---itemCount:%d--->"),MaxCnt + 1);  //MaxCnt�͓Y�����ł��邽�߁A�{�P����
    
	TotalItems.Format(_T("%d"),MaxCnt+1);  //MaxCnt�͓Y�����ł��邽�߁A�{�P����
	writeData = _T("");

	CString META_ENCODING;

	if (g_RadioENCODING_SELECT == 0){
		META_ENCODING = _T("<META http-equiv=\"Content-Type\" content=\"text/html; charset=Shift_JIS\">");
	}else if(g_RadioENCODING_SELECT == 1){
		META_ENCODING = _T("<META http-equiv=\"Content-Type\" content=\"text/html; charset=unicode\">");
	}

    writeData = writeData + _T("<html>") + _T("<head>") + META_ENCODING + _T("<title>") + FLC_CurrentVersion + _T("</title>") + _T("</head>") + _T("\n")
        + _T("<body>") + _T("\n") + outGeneratorVer + _T("\n") + w_TotalItems + _T("\n") +
        _T("<div align =" + "\"" + "right" + "\"" + ">") + "TOTAL : " + CFileListCreatorDlg::Total_Bytes_Func() + 
            " (" + TotalItems + "items)" + _T("</div>") + _T("\n") + 
            + BoldItemStr +  
        _T("<div align =" + "\"" + "center" + "\"" + ">") + _T("<table border =" + "\"" + "1" + "\"" + ">") + _T("<font size=" + "\"" + "3" + "\"" + ">") 
        + Temp 
        + _T("</font>") + _T("</table>") + _T("</div>") + _T("\n") + _T("</body>") + _T("</html>");


//=====================================================

	CString htmlFileName;

	htmlFileName = FileName + _T(".html");


	if (g_RadioENCODING_SELECT == 0){
		FILE *fp;

		//-----------------------
		_tfopen_s(&fp,saveDir + htmlFileName, L"w"); //,ccs=Shift_JIS
		fputws(writeData, fp);
		fclose(fp);
	}
	if (g_RadioENCODING_SELECT == 1){
		FILE *fp;

		//-----------------------
		_tfopen_s(&fp,saveDir + htmlFileName, L"w,ccs=UNICODE");
		fputws(writeData, fp);
		fclose(fp);
	}

//================================================================================

		//''txt�t�@�C���o��

	//LVITEM       lvi;
	
	int err = 0;
	//CString      str;	
	
	lvi.mask = LVIF_TEXT;// | LVIF_PARAM; //�f�[�^�̍X�V���ɕK�v�I�I

	CString txtFileName;

	txtFileName = FileName + _T(".txt");

	writeData = _T("");

	//Worksheets("FileList").Activate
    
	int Edit_i = 0;

	while(Edit_i<=m_xcList.GetItemCount()-1){
		//if(CFileListCreatorDlg::m_xcList.GetItemText(Edit_i,2)!=_T("")){
			CString tempStr1;
			tempStr1 = m_xcList.GetItemText(Edit_i,3);
			if (tempStr1 !=_T("")){
				tempStr1.Replace(_T("%"),_T("%%"));
			}
			//CFileListCreatorDlg::m_xcList.EnsureVisible(Edit_i, FALSE);
			tempStr1.Format(_T("(%d) ") + tempStr1 + _T("\n"),Edit_i + 1);
			writeData = writeData +tempStr1;
		//}
		Edit_i = Edit_i + 1;
	}

	txtFileName = ProhibitFileName(txtFileName,FALSE);


	if (g_RadioENCODING_SELECT == 0){
		FILE *fp;

		//-----------------------
		_tfopen_s(&fp,saveDir + txtFileName, L"w"); //,ccs=Shift_JIS
		fputws(writeData, fp);
		fclose(fp);
	}
	if (g_RadioENCODING_SELECT == 1){
		FILE *fp;

		//-----------------------
		_tfopen_s(&fp,saveDir + txtFileName, L"w,ccs=UNICODE");
		fputws(writeData, fp);
		fclose(fp);
	}

	g_NoDrawFLG = FALSE; //�R�����g�� 2012.06.14

	//http://gurizuri0505.halfmoon.jp/develop/cplusplus/cstdiofile
	_wsetlocale(LC_ALL, _T(""));

}

//http://oshiete.goo.ne.jp/qa/1424060.html
//#include <stdio.h>
// #include <stdlib.h>
// #include <ctype.h>

BOOL CFileListCreatorDlg::myIsDigit_Func(CString targetStr){

	if (targetStr==_T("")) return (FALSE);

	int     sizeOfString_1 = (targetStr.GetLength() + 1);
	LPTSTR  lpsz_1 = new TCHAR[ sizeOfString_1 ];
	_tcscpy_s(lpsz_1, sizeOfString_1, targetStr);

	//char str[16];
	int error;
	TCHAR *p;
	//do{
		error=0;
		//fgets(str, sizeof(str), stdin);
		for(p=lpsz_1;*p!='\n' && *p;p++){ /* �ꕶ�������ׂ� */
			if(!isdigit(*p)){ /* ���������ȊO���܂܂�Ă��� */
				error=1; /* �G���[���� */
				//printf("�����ȊO�̕������܂܂�Ă��܂�\n");
				break;
			}
		}
		//if(error) continue; /* �G���[���N�����Ă��鎞�ȉ��̓X�L�b�v���� */

	//}while(!error); /* �G���[�łȂ���ΌJ��Ԃ� */

	delete[] lpsz_1;
	return (!error);
}


ULONGLONG CFileListCreatorDlg::FileListItemsCount(CString importFilePath){

	CString META_ENCODING_Shift_JIS = _T("<META http-equiv=\"Content-Type\" content=\"text/html; charset=Shift_JIS\">");
	CString META_ENCODING_UNICODE = _T("<META http-equiv=\"Content-Type\" content=\"text/html; charset=unicode\">");

	//BOOL META_ENCODING_FLG = FALSE;

    if(importFilePath.GetLength() >= 4){
        if (importFilePath.Right(5) == _T(".html") || importFilePath.Right(4) == _T(".htm")){
			//if(CFileListCreatorDlg::importFileList_Func(importFilePath,TRUE) == 1){
				CString       wstr, rstr;
				LPTSTR        rstrBuf = NULL;
				int           err = 0;

				FILE *fp;
				_tfopen_s(&fp,importFilePath, _T("r, ccs=UNICODE"));
				CStdioFile stdFile(fp);

				int RowCnt = 1;

				while (!err) {
					if (RowCnt >= 5) break; //<!---itemCount:???--->�ȍ~�̓X�L�b�v //itemCount��5�s��

					if (stdFile.ReadString(rstr) == FALSE) break;

					//http://www.cppll.jp/cppreference/cppstring_details.html
					if (RowCnt == 1 && (rstr.Find(META_ENCODING_Shift_JIS,0)==string::npos && rstr.Find(META_ENCODING_UNICODE,0)==string::npos)){
						if(AnyfileImport == FALSE){
							break;
						}
					}

					if (rstr!=_T("")){

						CString itemCnt;
            
						itemCnt = _T("");
						
						CString temp1;
						temp1 = _T("<!---itemCount:");

						CString temp2;
						temp2 = _T("--->");

						if(rstr.Find(temp1,0)>=0 && rstr.Find(temp2,0)>=0){
							if(rstr.GetLength()>=temp2.GetLength()){
								if(rstr.Left(temp1.GetLength()) == temp1 &&  rstr.Right(temp2.GetLength()) == temp2){
									itemCnt = rstr;
								}
							}
						}
						//stdFile.Close();
					
						if (itemCnt == _T("")) {
							//stdFile.Close();//�ǉ� 2012.06.14
							//return 0;
						}else{
							LONG myidx;
							LONG myidx2;

							LONG X;

							CString temp1;
							temp1 = _T("<!---itemCount:");

							CString temp2;
							temp2 = _T("--->");

							myidx = itemCnt.Find(temp1,0);
							X = myidx + temp1.GetLength();
							myidx2 = itemCnt.Find(temp2,X);
                
							CString tempCntStr;

							tempCntStr = _T("N/A");

							if(itemCnt.Find(temp1,0)>=0 && itemCnt.Find(temp2,0)>=0){
								//tempCntStr = Mid(itemCnt, myidx + Len(_T("<!---" + "itemCount:")), myidx2 - myidx - Len("<!---" & "itemCount:"))
								tempCntStr = itemCnt.Mid(myidx + temp1.GetLength(), myidx2 - myidx - temp1.GetLength());
							}

							//MessageBox(tempCntStr);
							if (myIsDigit_Func(tempCntStr) == TRUE){
								stdFile.Close();//�ǉ� 2012.06.02
								return CStringToLong(tempCntStr);
							}else{
								stdFile.Close();//�ǉ� 2012.06.02
								return 0;
			//'                    //FileListItemsCount = FileListItemsCount
							}
						}
					}
					RowCnt++;
				}
				// (6)�N���[�Y(�����I)
				//fclose(fp);
				stdFile.Close();
			//}
		}
	}
	return 0;
}

int CFileListCreatorDlg::importFileList_Func(CString importFilePath, BOOL importCheckFLG){
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	//_wsetlocale(LC_ALL, L"Japanese");

	////http://oshiete.goo.ne.jp/qa/934586.html
	//int ch = _getch(); // �� �R��
	//std::cout << std::hex << ch << std::endl;
	//return 0;

	if(importFilePath==_T(""))return 0;
    
	if(importFilePath.GetLength() < 4)return 0;
    
    if(importFilePath.Right(GetStrLen_Func(_T(".htm")))!= _T(".htm") && importFilePath.Right(GetStrLen_Func(_T(".html")))!= _T(".html")) return 0;

	if ( PathFileExists(importFilePath) == FALSE ) return 0; //�ǉ� 2012.07.26

	_wsetlocale(LC_ALL, L"Japanese");

	//if (ESCAPE_FLG == TRUE) return 0;//�ǉ� 2011.10.12

	//LVITEM       lvi;
	int          index = 0;
	//int          err = 0;
	CString      str;	

	UpdateData();
	lvi.mask = LVIF_TEXT;


	//////////��UNICODE �ŏo��
	//////////http://oshiete.goo.ne.jp/qa/5126054.html ���Q�l�ɂ��܂����B


	//http://typea.info/tips/wiki.cgi?page=MFC+%A5%D5%A5%A1%A5%A4%A5%EB%A4%F2%C6%C9%A4%E0
	int           err = 0;
	CString       wstr, rstr;
	//LPTSTR        rstrBuf = NULL;
	//CStdioFile stdFile(_tfopen(importFilePath, _T("r, ccs=UNICODE")));

	FILE *fp; //�ύX rw�ɕύX 2012.06.02
	_tfopen_s(&fp,importFilePath, _T("r, ccs=UNICODE")); //http://msdn.microsoft.com/ja-jp/library/yeby3zcb(v=vs.100).aspx
	CStdioFile stdFile(fp); //http://oshiete.goo.ne.jp/qa/7431848.html
	
	int RowCnt=1;

	// (4)�ǂݍ���(CString)
	inGeneratorVer = _T("<!---FLC Generator Version is Unknown--->");


	CString META_ENCODING_Shift_JIS = _T("<META http-equiv=\"Content-Type\" content=\"text/html; charset=Shift_JIS\">");
	CString META_ENCODING_UNICODE = _T("<META http-equiv=\"Content-Type\" content=\"text/html; charset=unicode\">");

	//BOOL META_ENCODING_FLG = FALSE;

	while (!err){
		if (RowCnt >= 4 ) break;//<!---FLC Generator Version x.x--->�ȍ~�̓X�L�b�v

		if (stdFile.ReadString(rstr) == FALSE) break;
		
		//http://www.cppll.jp/cppreference/cppstring_details.html
		if (RowCnt == 1 && (rstr.Find(META_ENCODING_Shift_JIS,0)==string::npos && rstr.Find(META_ENCODING_UNICODE,0)==string::npos)){
			if(AnyfileImport == FALSE){
				break;
			}
		}

		//MessageBox(rstr);
		if (rstr!=_T("")){
			if (rstr ==  _T("<!---FLC Generator Version 1.3--->")){
				inGeneratorVer = rstr;
				LastImportFileName = importFilePath;
				//stdFile.Close();
				break;
			}else if (rstr ==  _T("<!---FLC Generator Version 1.4.1--->")){
		        inGeneratorVer = rstr;
				LastImportFileName = importFilePath;
				//stdFile.Close();
				break;
			}else if (rstr ==  _T("<!---FLC Generator Version 1.4.2--->")){
		        inGeneratorVer = rstr;
				LastImportFileName = importFilePath;
				//stdFile.Close();
				break;
			}else if (rstr ==  _T("<!---FLC Generator Version 1.5.1--->")){
		        inGeneratorVer = rstr;
				LastImportFileName = importFilePath;
				//stdFile.Close();
				break;
			}else if (rstr ==  _T("<!---FLC Generator Version 1.5.2--->")){
		        inGeneratorVer = rstr;
				LastImportFileName = importFilePath;
				//stdFile.Close();
				break;
			}else if (rstr ==  _T("<!---FLC Generator Version 1.5.3--->")){
		        inGeneratorVer = rstr;
				LastImportFileName = importFilePath;
				//stdFile.Close();
				break;
			}else if (rstr ==  _T("<!---FLC Generator Version 1.5.4--->")){
		        inGeneratorVer = rstr;
				LastImportFileName = importFilePath;
				//stdFile.Close();
				break;
			}else if (rstr ==  _T("<!---FLC Generator Version 1.5.5--->")){
		        inGeneratorVer = rstr;
				LastImportFileName = importFilePath;
				//stdFile.Close();
				break;
			}else if (rstr ==  _T("<!---FLC Generator Version 1.5.6--->")){
		        inGeneratorVer = rstr;
				LastImportFileName = importFilePath;
				//stdFile.Close();
				break;
			}

		}
		RowCnt++;
	}

	//MessageBox (inGeneratorVer);
	//UpdateData(FALSE);

	if(inGeneratorVer == _T("<!---FLC Generator Version is Unknown--->") ){
		if (importCheckFLG == TRUE) {
			stdFile.Close();
			return 0;
		}else{
			StatusStringSet(_T("�P�ȏ�̃��X�g�t�@�C���̌`�����F���ł��܂���"),0,FALSE);
			stdFile.Close();
			return 0;
		}
	}else{
		if(importCheckFLG == TRUE){
			stdFile.Close();//�ǉ� 2012.06.02
			return 1;
		}
	}        
   
   if (inGeneratorVer == _T("<!---FLC Generator Version 1.3--->")){  //���X�V�����ߍ��܂�
		while (!err) {
			if (ESCAPE_FLG == TRUE) break;

			if (stdFile.ReadString(rstr) == FALSE) err = 1;

			if (rstr!=_T("")){

				//CString tempStrForLen;
	 			LONG stepIDX;
				int CurrentStepCheck[11];
		    
				for(stepIDX = 0;stepIDX<=10; stepIDX++){
					CurrentStepCheck[stepIDX] = 0;
				}

        
	            
				//rstr = _
				//Replace(rstr, "<", "��")
	                
				//rstr = _
				//Replace(rstr, ">", "��")
	    
				//rstr.Replace(_T("&lt;"), _T("<"));
				//rstr.Replace(_T("&gt;"), _T(">"));
				//rstr.Replace(_T("&quot;"), _T("\""));
	   // 
				rstr.Replace(_T("&nbsp;"), _T(" "));
				//rstr.Replace(_T("&copy;"), _T("(c)"));
				//rstr.Replace(_T("&reg;"), _T("(r)")); 
				//rstr.Replace(_T("&amp;"), _T("&"));//�Ō�ɒu��

				CString FullPath;

				BOOL RedFLG;
				BOOL BoldFLG;

				CString rstr2;

				LONG hiddenFullPathIDX1;
				LONG hiddenFullPathIDX2;

				LONG X;
				LONG myidx;
				LONG CurrentStep;
	                    
				LONG myidx2;
				//LONG DoWithCnt;

				BOOL ReadErrorFLG = FALSE;

				if ((rstr.Find(_T("<tr>"),0) == 0 ) && (rstr.Find(_T("</tr>"),0) >= (rstr.GetLength() - GetStrLen_Func(_T("</tr>"))))){ //Len("</tr>")=5){
					myidx2 = 0;
					CurrentStep = 1;
	                    
					X = 0;
	
					while (X <= rstr.GetLength()-1){
						MSG msg; //�ǉ� 2011.10.12

						if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
							if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
								if (msg.wParam == VK_ESCAPE){
									ESCAPE_FLG = TRUE;
									break; //�I���B���b�Z�[�W���[�v�𔲂���B
								}
							}
							TranslateMessage(&msg);
							DispatchMessage(&msg);
							//continue;
						}
						

						if( CurrentStep== 1){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(GetStrLen_Func(_T("</td>")),X);

							//Call myActivateFunc(6 + MaxCnt)
							//�d���i���o�[
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%s"), _T(""));	//�ʂ��ԍ�
								lvi.iItem = CFileListCreatorDlg::m_xcList.GetItemCount();
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 0;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));	//�t�@�C���d�����ʃi���o�[

								index = CFileListCreatorDlg::m_xcList.InsertItem(&lvi); //err = 1;
							}

							//�ʂ��ԍ�
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%d"), index+1);	//�ʂ��ԍ�
								lvi.iItem = index;
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 1;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}
							CurrentStep = 2;
							//break;
						}else if( CurrentStep== 2){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);

							rstr2 = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>"))); //- GetStrLen_Func(_T("--->")
	                        
							//BOOL RedFLG;
							RedFLG = FALSE;
	                                
							CString RedTag1;

							RedTag1 = _T("<font color=\"red\">");
	                                
							CString  RedTag2;
							RedTag2 = _T("</font>");
	                                
							LONG RedIDX1;
							RedIDX1 = rstr.Find(RedTag1,myidx);
	                                
							LONG RedIDX2;
							RedIDX2 = rstr.Find(RedTag2,myidx);
	                            
							CString FormatDataStr;
							//FormatDataStr = _T("NORMAL,BLACK,");

							FormatDataStr = _T("BLACK,");

							if( RedIDX1 >= 0 && RedIDX2 >= 0){

								
								FormatDataStr = _T("RED,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());
								RedFLG = TRUE;
							}else{
								CString FormatDataStr;
								FormatDataStr = _T("BLACK,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
							}
	                                
							//CString FullPath;
	                        
							//LONG hiddenFullPathIDX1;
							//LONG hiddenFullPathIDX2;
	                                    
							hiddenFullPathIDX1 = rstr.Find(_T("<!---"),0);
							X = hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")+1);//+1
							hiddenFullPathIDX2 = rstr.Find(_T("--->"),X);
	                                    
							if (hiddenFullPathIDX1 >= 0 && hiddenFullPathIDX2 >= 0 ){

	  
								FullPath = rstr.Mid( hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")), hiddenFullPathIDX2 - hiddenFullPathIDX1 - GetStrLen_Func(_T("<!---")));
	                                                                                                                     
							}else{

							}
	                                    
							//BOOL BoldFLG;
							BoldFLG = FALSE;
	                                    
							LONG BoldIDX;
							BoldIDX = rstr2.Find(_T("<b>"), 0);
	                                   
							LONG BoldIDX2;
							BoldIDX2 = rstr2.Find(_T("</b>"),BoldIDX + GetStrLen_Func(_T("<b>")));
	                                    
							if (BoldIDX >= 0 && BoldIDX2 >= 0) {
	                                        
								rstr2 = rstr2.Mid(BoldIDX + GetStrLen_Func(_T("<b>")), BoldIDX2 - BoldIDX - GetStrLen_Func(_T("<b>")));                           
								FormatDataStr = _T("BOLD,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								//rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());

								BoldFLG = TRUE;

							}else{
								FormatDataStr = _T("NORMAL,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
								BoldFLG = FALSE;
							}



							// �t���p�X
							if (!err)
							{
								//lvi.mask = LVIF_TEXT;
								//lvi.lParam = m_id++;        // ID
								lvi.iItem = index;
								lvi.iSubItem = 2;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPath));
								//MessageBox (FullPath);
								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}	                                            
	                                            
							if(BoldFLG == TRUE ||  RedFLG == TRUE){
								// �t�@�C����
								if (!err)
								{									
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}
							}else{
								CString temp;
								temp = rstr2.Left(rstr2.Find(_T("<!---"),0));
								//MessageBox (temp);
								// �t�@�C����
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
								}
	                                        
								if( BoldFLG == TRUE ||  RedFLG == TRUE ){
									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}else{
									CString temp;
									temp =rstr2.Left(rstr2.Find(_T("<!---"),0));

									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}
							}
							X = hiddenFullPathIDX2 + GetStrLen_Func(_T("--->")) + GetStrLen_Func(_T("</td>"));


							CurrentStep = 3;
							//break;
						}else if( CurrentStep== 3){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);
	                    
							CString tempSize;
							if( myidx >= 0 && myidx2 >= 0 ){
								tempSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
							}else{
								tempSize = "";
							}
	                                
							LONG SizeNumIDX1;
							LONG SizeNumIDX2;
	                                
							SizeNumIDX1 = tempSize.Find(_T("<!---"),0);
							X = SizeNumIDX1 + GetStrLen_Func(_T("<!---"));
							SizeNumIDX2 = tempSize.Find(_T("--->"),X);
					
							CString myFileSize;

							if( SizeNumIDX1 >= 0 && SizeNumIDX2 >= 0 ) {


								myFileSize = tempSize.Mid(SizeNumIDX1 +GetStrLen_Func(_T("<!---")), SizeNumIDX2 - SizeNumIDX1 - GetStrLen_Func(_T("<!---")));

								
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 5;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}


								myFileSize = tempSize.Mid( 0, SizeNumIDX1);

								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}else{
								myFileSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}

							X = myidx + SizeNumIDX2 + GetStrLen_Func(_T("--->"));
	                                       
							CurrentStep = 4;
							//break;
						}else if( CurrentStep== 4){
							CurrentStep = 5;
							//break; 
						}else if( CurrentStep== 5){
							//MaxCnt = MaxCnt + 1
							DoWithCnt = DoWithCnt + 1;
							CFileListCreatorDlg::ItemCount_Func(TRUE);
							CurrentStep = 6;
							//break;
						}else if( CurrentStep== 6){
							int stepIDX;
							for( stepIDX = 0; stepIDX <= 10; stepIDX++){
								CurrentStepCheck[stepIDX] = 0;
							}

							//X=rstr.GetLength();

							CurrentStep =1;//
							break;
							//goto label;
							
						}else{
							X = X + 1;
							//break;
						}
	                    UpdateData(FALSE);
						CurrentStepCheck[CurrentStep] = CurrentStepCheck[CurrentStep] + 1;
	                        
						if( CurrentStepCheck[CurrentStep] >=2){
							ReadErrorFLG = TRUE;
							break;
						}
					}
				}

				CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE);
				UpdateWindow();

				if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1 || MiniWindowFLG == FALSE){
					m_xcStaticString.ShowWindow(SW_HIDE);
				}else{
					m_xcStaticString.ShowWindow(SW_SHOW);
				}

				CString tempStatus;
				tempStatus.Format(_T("HTML �C���|�[�g ���s�� ( %I64u / %I64u ) ") , DoWithCnt,TotalItemsCount);					
				StatusStringSet(tempStatus,0,FALSE);
				UpdateData(FALSE);

			}
		}
	}
	

	if (inGeneratorVer == _T("<!---FLC Generator Version 1.4.1--->")){  //���X�V�� �\��
		while (!err) {
			if (ESCAPE_FLG == TRUE) break;

			if (stdFile.ReadString(rstr) == FALSE) err = 1;

			if (rstr!=_T("")){

				//CString tempStrForLen;
	 			LONG stepIDX;
				int CurrentStepCheck[11];
		    
				for(stepIDX = 0;stepIDX<=10; stepIDX++){
					CurrentStepCheck[stepIDX] = 0;
				}

        
	            
				//rstr = _
				//Replace(rstr, "<", "��")
	                
				//rstr = _
				//Replace(rstr, ">", "��")
	    
				//rstr.Replace(_T("&lt;"), _T("<"));
				//rstr.Replace(_T("&gt;"), _T(">"));
				//rstr.Replace(_T("&quot;"), _T("\""));
	   // 
				rstr.Replace(_T("&nbsp;"), _T(" "));
				//rstr.Replace(_T("&copy;"), _T("(c)"));
				//rstr.Replace(_T("&reg;"), _T("(r)")); 
				//rstr.Replace(_T("&amp;"), _T("&"));//�Ō�ɒu��

				CString FullPath;

				BOOL RedFLG;
				BOOL BoldFLG;

				CString rstr2;

				LONG hiddenFullPathIDX1;
				LONG hiddenFullPathIDX2;

				LONG X;
				LONG myidx;
				LONG CurrentStep;
	                    
				LONG myidx2;
				//LONG DoWithCnt;

				BOOL ReadErrorFLG = FALSE;

				if ((rstr.Find(_T("<tr>"),0) == 0 ) && (rstr.Find(_T("</tr>"),0) >= (rstr.GetLength() - GetStrLen_Func(_T("</tr>"))))){ //Len("</tr>")=5){
					myidx2 = 0;
					CurrentStep = 1;
	                    
					X = 0;
	
					while (X <= rstr.GetLength()-1){
						MSG msg; //�ǉ� 2011.10.12

						if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
							if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
								if (msg.wParam == VK_ESCAPE){
									ESCAPE_FLG = TRUE;
									break; //�I���B���b�Z�[�W���[�v�𔲂���B
								}
							}
							TranslateMessage(&msg);
							DispatchMessage(&msg);
							//continue;
						}

						//MessageBox (rstr);
						if( CurrentStep== 1){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(GetStrLen_Func(_T("</td>")),X);

							//Call myActivateFunc(6 + MaxCnt)
							//�d���i���o�[
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%s"), _T(""));	//�ʂ��ԍ�
								lvi.iItem = CFileListCreatorDlg::m_xcList.GetItemCount();
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 0;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));	//�t�@�C���d�����ʃi���o�[

								index = CFileListCreatorDlg::m_xcList.InsertItem(&lvi); //err = 1;
							}

							//�ʂ��ԍ�
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%d"), index+1);	//�ʂ��ԍ�
								lvi.iItem = index;
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 1;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}
							CurrentStep = 2;
							//break;
						}else if( CurrentStep== 2){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);

							rstr2 = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>"))); //- GetStrLen_Func(_T("--->")
	                        
							//BOOL RedFLG;
							RedFLG = FALSE;
	                                
							CString RedTag1;

							RedTag1 = _T("<font color=\"red\">");
	                                
							CString  RedTag2;
							RedTag2 = _T("</font>");
	                                
							LONG RedIDX1;
							RedIDX1 = rstr.Find(RedTag1,myidx);
	                                
							LONG RedIDX2;
							RedIDX2 = rstr.Find(RedTag2,myidx);
	                            
							CString FormatDataStr;
							//FormatDataStr = _T("NORMAL,BLACK,");

							FormatDataStr = _T("BLACK,");

							if( RedIDX1 >= 0 && RedIDX2 >= 0){

								
								FormatDataStr = _T("RED,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());
								RedFLG = TRUE;
							}else{
								CString FormatDataStr;
								FormatDataStr = _T("BLACK,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
							}
	                                
							//CString FullPath;
	                        
							//LONG hiddenFullPathIDX1;
							//LONG hiddenFullPathIDX2;
	                                    
							hiddenFullPathIDX1 = rstr.Find(_T("<!---"),0);
							X = hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")+1);//+1
							hiddenFullPathIDX2 = rstr.Find(_T("--->"),X);
	                                    
							if (hiddenFullPathIDX1 >= 0 && hiddenFullPathIDX2 >= 0 ){

	  
								FullPath = rstr.Mid( hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")), hiddenFullPathIDX2 - hiddenFullPathIDX1 - GetStrLen_Func(_T("<!---")));
	                                                                                                                     
							}else{

							}
	                                    
							//BOOL BoldFLG;
							BoldFLG = FALSE;
	                                    
							LONG BoldIDX;
							BoldIDX = rstr2.Find(_T("<b>"), 0);
	                                   
							LONG BoldIDX2;
							BoldIDX2 = rstr2.Find(_T("</b>"),BoldIDX + GetStrLen_Func(_T("<b>")));
	                                    
							if (BoldIDX >= 0 && BoldIDX2 >= 0) {
	                                        
								rstr2 = rstr2.Mid(BoldIDX + GetStrLen_Func(_T("<b>")), BoldIDX2 - BoldIDX - GetStrLen_Func(_T("<b>")));                           
								FormatDataStr = _T("BOLD,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								//rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());

								BoldFLG = TRUE;

							}else{
								FormatDataStr = _T("NORMAL,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
								BoldFLG = FALSE;
							}

							// �t���p�X
							if (!err)
							{
								//lvi.mask = LVIF_TEXT;
								//lvi.lParam = m_id++;        // ID
								lvi.iItem = index;
								lvi.iSubItem = 2;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPath));
								//MessageBox (FullPath);
								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}	                                            
	                                            
							if(BoldFLG == TRUE ||  RedFLG == TRUE){
								// �t�@�C����
								if (!err)
								{									
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}
							}else{
								CString temp;
								temp = rstr2.Left(rstr2.Find(_T("<!---"),0));
								//MessageBox (temp);
								// �t�@�C����
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
								}
	                                        
								if( BoldFLG == TRUE ||  RedFLG == TRUE ){
									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}else{
									CString temp;
									temp =rstr2.Left(rstr2.Find(_T("<!---"),0));

									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}
							}
							X = hiddenFullPathIDX2 + GetStrLen_Func(_T("--->")) + GetStrLen_Func(_T("</td>"));


							CurrentStep = 3;

							//break;
						}else if( CurrentStep== 3){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);
	                    
							CString tempSize;
							if( myidx >= 0 && myidx2 >= 0 ){
								tempSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
							}else{
								tempSize = "";
							}
	                                
							LONG SizeNumIDX1;
							LONG SizeNumIDX2;
	                                
							SizeNumIDX1 = tempSize.Find(_T("<!---"),0);
							X = SizeNumIDX1 + GetStrLen_Func(_T("<!---"));
							SizeNumIDX2 = tempSize.Find(_T("--->"),X);

						
							CString myFileSize;

							if( SizeNumIDX1 >= 0 && SizeNumIDX2 >= 0 ) {


								myFileSize = tempSize.Mid(SizeNumIDX1 +GetStrLen_Func(_T("<!---")), SizeNumIDX2 - SizeNumIDX1 - GetStrLen_Func(_T("<!---")));

								
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 5;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}


								myFileSize = tempSize.Mid( 0, SizeNumIDX1);

								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}else{
								myFileSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}

							X = myidx + SizeNumIDX2 + GetStrLen_Func(_T("--->"));
	                                       
							CurrentStep = 4;
							//MessageBox (_T("1111111"));
							//break;
						}else if( CurrentStep== 4){
								
			          			myidx = rstr.Find(_T("<td>"),X);
			                    X = myidx + GetStrLen_Func(_T("<td>"));
			                    myidx2 = rstr.Find(_T("</td>"),X);

		                        CString tempDate;
			                    
			                    if ( myidx >= 0 && myidx2 >= 0 ){
			                        tempDate = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
			                    }else{
			                        tempDate = _T("");
			                    }
			                    
								
			                    LONG DateIDX1;
			                    LONG DateIDX2;
			                                
			                    DateIDX1 = tempDate.Find(_T("<!---") ,0);
			                    X = DateIDX1 + GetStrLen_Func(_T("<!---"));
			                    DateIDX2 = tempDate.Find(_T("--->") ,X);

			                                
								CString tempStr;

			                    if(DateIDX1 >= 0 && DateIDX2 >= 0 ){

									tempStr = tempDate.Mid(DateIDX1 + GetStrLen_Func(_T("<!---")),DateIDX2 - DateIDX1 - GetStrLen_Func(_T("<!---")));
									//�C������
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 7;
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}			                                   

									tempStr = tempDate.Mid(0,DateIDX1);
									//�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 6;
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
			                    }else{
									tempStr = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
									//�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 6;
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
			                    }

			                    X = myidx + DateIDX2 + GetStrLen_Func(_T("--->"));

							CurrentStep = 5;
							//break; 
						}else if( CurrentStep== 5){
							//MaxCnt = MaxCnt + 1
							DoWithCnt = DoWithCnt + 1;
							CFileListCreatorDlg::ItemCount_Func(TRUE);
							CurrentStep = 6;
							//break;
						}else if( CurrentStep== 6){
							int stepIDX;
							for( stepIDX = 0; stepIDX <= 10; stepIDX++){
								CurrentStepCheck[stepIDX] = 0;
							}

							//X=rstr.GetLength();

							CurrentStep =1;//
							break;
							//goto label;
							
						}else{
							X = X + 1;
						}
	                    UpdateData(FALSE);
						CurrentStepCheck[CurrentStep] = CurrentStepCheck[CurrentStep] + 1;
	                        
						if( CurrentStepCheck[CurrentStep] >=2){
							ReadErrorFLG = TRUE;
							break;
						}
					}
				}

				CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE);
				UpdateWindow();

				if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1 || MiniWindowFLG == FALSE){
					m_xcStaticString.ShowWindow(SW_HIDE);
				}else{
					m_xcStaticString.ShowWindow(SW_SHOW);
				}
				CString tempStatus;
				tempStatus.Format(_T("HTML �C���|�[�g ���s�� ( %I64u / %I64u ) ") , DoWithCnt,TotalItemsCount);					
				StatusStringSet(tempStatus,0,FALSE);
				UpdateData(FALSE);

			}
		}
			
	}

	if (inGeneratorVer == _T("<!---FLC Generator Version 1.4.2--->")){  //���X�V�� ��\��

		while (!err) {
			if (ESCAPE_FLG == TRUE) break;

			if (stdFile.ReadString(rstr) == FALSE) err = 1;

			if (rstr!=_T("")){

				//CString tempStrForLen;
	 			LONG stepIDX;
				int CurrentStepCheck[11];
		    
				for(stepIDX = 0;stepIDX<=10; stepIDX++){
					CurrentStepCheck[stepIDX] = 0;
				}

        
	            
				//rstr = _
				//Replace(rstr, "<", "��")
	                
				//rstr = _
				//Replace(rstr, ">", "��")
	    
				//rstr.Replace(_T("&lt;"), _T("<"));
				//rstr.Replace(_T("&gt;"), _T(">"));
				//rstr.Replace(_T("&quot;"), _T("\""));
	   // 
				rstr.Replace(_T("&nbsp;"), _T(" "));
				//rstr.Replace(_T("&copy;"), _T("(c)"));
				//rstr.Replace(_T("&reg;"), _T("(r)"));

				////&apos; 
				//rstr.Replace(_T("&amp;"), _T("&"));//�Ō�ɒu��

				CString FullPath;

				BOOL RedFLG;
				BOOL BoldFLG;

				CString rstr2;

				LONG hiddenFullPathIDX1;
				LONG hiddenFullPathIDX2;

				LONG X;
				LONG myidx;
				LONG CurrentStep;
	                    
				LONG myidx2;
				//LONG DoWithCnt;

				BOOL ReadErrorFLG = FALSE;

				if ((rstr.Find(_T("<tr>"),0) == 0 ) && (rstr.Find(_T("</tr>"),0) >= (rstr.GetLength() - GetStrLen_Func(_T("</tr>"))))){ //Len("</tr>")=5){
					myidx2 = 0;
					CurrentStep = 1;
	                    
					X = 0;
	
					while (X <= rstr.GetLength()-1){
						MSG msg; //�ǉ� 2011.10.12

						if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
							if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
								if (msg.wParam == VK_ESCAPE){
									ESCAPE_FLG = TRUE;
									break; //�I���B���b�Z�[�W���[�v�𔲂���B
								}
							}
							TranslateMessage(&msg);
							DispatchMessage(&msg);
							//continue;
						}

						//MessageBox (rstr);
						if( CurrentStep== 1){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(GetStrLen_Func(_T("</td>")),X);

							//Call myActivateFunc(6 + MaxCnt)
							//�d���i���o�[
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%s"), _T(""));	//�ʂ��ԍ�
								lvi.iItem = CFileListCreatorDlg::m_xcList.GetItemCount();
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 0;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));	//�t�@�C���d�����ʃi���o�[

								index = CFileListCreatorDlg::m_xcList.InsertItem(&lvi); //err = 1;
							}

							//�ʂ��ԍ�
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%d"), index+1);	//�ʂ��ԍ�
								lvi.iItem = index;
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 1;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}
							CurrentStep = 2;
							//break;
						}else if( CurrentStep== 2){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);

							rstr2 = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>"))); //- GetStrLen_Func(_T("--->")
	                        
							//BOOL RedFLG;
							RedFLG = FALSE;
	                                
							CString RedTag1;

							RedTag1 = _T("<font color=\"red\">");
	                                
							CString  RedTag2;
							RedTag2 = _T("</font>");
	                                
							LONG RedIDX1;
							RedIDX1 = rstr.Find(RedTag1,myidx);
	                                
							LONG RedIDX2;
							RedIDX2 = rstr.Find(RedTag2,myidx);
	                            
							CString FormatDataStr;
							//FormatDataStr = _T("NORMAL,BLACK,");

							FormatDataStr = _T("BLACK,");

							if( RedIDX1 >= 0 && RedIDX2 >= 0){

								
								FormatDataStr = _T("RED,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());
								RedFLG = TRUE;
							}else{
								CString FormatDataStr;
								FormatDataStr = _T("BLACK,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
							}
	                                
							//CString FullPath;
	                        
							//LONG hiddenFullPathIDX1;
							//LONG hiddenFullPathIDX2;
	                                    
							hiddenFullPathIDX1 = rstr.Find(_T("<!---"),0);
							X = hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")+1);//+1
							hiddenFullPathIDX2 = rstr.Find(_T("--->"),X);
	                                    
							if (hiddenFullPathIDX1 >= 0 && hiddenFullPathIDX2 >= 0 ){

	  
								FullPath = rstr.Mid( hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")), hiddenFullPathIDX2 - hiddenFullPathIDX1 - GetStrLen_Func(_T("<!---")));
	                                                                                                                     
							}else{

							}
	                                    
							//BOOL BoldFLG;
							BoldFLG = FALSE;
	                                    
							LONG BoldIDX;
							BoldIDX = rstr2.Find(_T("<b>"), 0);
	                                   
							LONG BoldIDX2;
							BoldIDX2 = rstr2.Find(_T("</b>"),BoldIDX + GetStrLen_Func(_T("<b>")));
	                                    
							if (BoldIDX >= 0 && BoldIDX2 >= 0) {
	                                        
								rstr2 = rstr2.Mid(BoldIDX + GetStrLen_Func(_T("<b>")), BoldIDX2 - BoldIDX - GetStrLen_Func(_T("<b>")));                           
								FormatDataStr = _T("BOLD,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								//rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());

								BoldFLG = TRUE;

							}else{
								FormatDataStr = _T("NORMAL,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
								BoldFLG = FALSE;
							}

							// �t���p�X
							if (!err)
							{
								//lvi.mask = LVIF_TEXT;
								//lvi.lParam = m_id++;        // ID
								lvi.iItem = index;
								lvi.iSubItem = 2;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPath));
								//MessageBox (FullPath);
								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}	                                            
	                                            
							if(BoldFLG == TRUE ||  RedFLG == TRUE){
								// �t�@�C����
								if (!err)
								{									
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}
							}else{
								CString temp;
								temp = rstr2.Left(rstr2.Find(_T("<!---"),0));
								//MessageBox (temp);
								// �t�@�C����
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
								}
	                                        
								if( BoldFLG == TRUE ||  RedFLG == TRUE ){
									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}else{
									CString temp;
									temp =rstr2.Left(rstr2.Find(_T("<!---"),0));

									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}
							}
							X = hiddenFullPathIDX2 + GetStrLen_Func(_T("--->")) + GetStrLen_Func(_T("</td>"));


							CurrentStep = 3;

							//break;
						}else if( CurrentStep== 3){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);
	                    
							CString tempSize;
							if( myidx >= 0 && myidx2 >= 0 ){
								tempSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
							}else{
								tempSize = "";
							}
	                                
							LONG SizeNumIDX1;
							LONG SizeNumIDX2;
	                                
							SizeNumIDX1 = tempSize.Find(_T("<!---"),0);
							X = SizeNumIDX1 + GetStrLen_Func(_T("<!---"));
							SizeNumIDX2 = tempSize.Find(_T("--->"),X);

						
							CString myFileSize;

							if( SizeNumIDX1 >= 0 && SizeNumIDX2 >= 0 ) {


								myFileSize = tempSize.Mid(SizeNumIDX1 +GetStrLen_Func(_T("<!---")), SizeNumIDX2 - SizeNumIDX1 - GetStrLen_Func(_T("<!---")));

								
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 5;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}


								myFileSize = tempSize.Mid( 0, SizeNumIDX1);

								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}else{
								myFileSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}

							X = myidx + SizeNumIDX2 + GetStrLen_Func(_T("--->"));
	                                       
							CurrentStep = 4;
							//break;
						}else if( CurrentStep== 4){

			                if(X >= 1){
			                    X = X - 1;
			                }

							//myidx = rstr.Find(_T("<td>"),X);
			                //X = myidx + GetStrLen_Func(_T("<td>"));
			                //myidx2 = rstr.Find(_T("</td>"),X);

		                    CString tempDate;
			                    
			                if ( myidx >= 0 && myidx2 >= 0 ){
			                    tempDate = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
			                }else{
			                    tempDate = _T("");
			                }
			                  
							
							LONG DateIDX1;
							LONG DateIDX2;
			                                
							DateIDX1 = rstr.Find(_T("<!---") ,X);
							X = DateIDX1 + GetStrLen_Func(_T("<!---"));
							DateIDX2 = rstr.Find(_T("--->") ,X);

	                                
							CString tempStr;

			                if(DateIDX1 >= 0 && DateIDX2 >= 0 ){
								tempStr = rstr.Mid(DateIDX1 + GetStrLen_Func(_T("<!---")),DateIDX2 - DateIDX1 - GetStrLen_Func(_T("<!---")));
								//�C����
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 6;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
								}
							}

							X = DateIDX2 + GetStrLen_Func(_T("--->"));


			                DateIDX1 = rstr.Find(_T("<!---") ,X);
			                X = DateIDX1 + GetStrLen_Func(_T("<!---"));
			                DateIDX2 = rstr.Find(_T("--->") ,X);

			                if(DateIDX1 >= 0 && DateIDX2 >= 0 ){
								tempStr = rstr.Mid(DateIDX1 + GetStrLen_Func(_T("<!---")),DateIDX2 - DateIDX1 - GetStrLen_Func(_T("<!---")));
								//�C������
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 7;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}
			                                    
			                }

							X = DateIDX2 + GetStrLen_Func(_T("--->"));

							CurrentStep = 5;
							//break; 
						}else if( CurrentStep== 5){
							//MaxCnt = MaxCnt + 1
							DoWithCnt = DoWithCnt + 1;
							CFileListCreatorDlg::ItemCount_Func(TRUE);
							CurrentStep = 6;
							//break;
						}else if( CurrentStep== 6){
							int stepIDX;
							for( stepIDX = 0; stepIDX <= 10; stepIDX++){
								CurrentStepCheck[stepIDX] = 0;
							}

							//X=rstr.GetLength();

							CurrentStep =1;//
							break;
							//goto label;
							
						}else{
							X = X + 1;
							//break;
						}
	                    UpdateData(FALSE);
						CurrentStepCheck[CurrentStep] = CurrentStepCheck[CurrentStep] + 1;
	                        
						if( CurrentStepCheck[CurrentStep] >=2){
							ReadErrorFLG = TRUE;
							break;
						}
					}
				}

				CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE);
				UpdateWindow();

				if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1 || MiniWindowFLG == FALSE){
					m_xcStaticString.ShowWindow(SW_HIDE);
				}else{
					m_xcStaticString.ShowWindow(SW_SHOW);
				}
				
				CString tempStatus;
				tempStatus.Format(_T("HTML �C���|�[�g ���s�� ( %I64u / %I64u ) ") , DoWithCnt,TotalItemsCount);					
				StatusStringSet(tempStatus,0,FALSE);
				UpdateData(FALSE);

			}
		}
			
	}

	if (inGeneratorVer == _T("<!---FLC Generator Version 1.5.1--->")){  //���X�V�� �\�� //�����l�� �\��

		while (!err) {
			if (ESCAPE_FLG == TRUE) break;

			if (stdFile.ReadString(rstr) == FALSE) err = 1;

			if (rstr!=_T("")){

				//CString tempStrForLen;
	 			LONG stepIDX;
				int CurrentStepCheck[11];
		    
				for(stepIDX = 0;stepIDX<=10; stepIDX++){
					CurrentStepCheck[stepIDX] = 0;
				}

        
	            
				//rstr = _
				//Replace(rstr, "<", "��")
	                
				//rstr = _
				//Replace(rstr, ">", "��")
	    
				//rstr.Replace(_T("&lt;"), _T("<"));
				//rstr.Replace(_T("&gt;"), _T(">"));
				//rstr.Replace(_T("&quot;"), _T("\""));
	   // 
				rstr.Replace(_T("&nbsp;"), _T(" "));
				//rstr.Replace(_T("&copy;"), _T("(c)"));
				//rstr.Replace(_T("&reg;"), _T("(r)")); 
				//rstr.Replace(_T("&amp;"), _T("&"));//�Ō�ɒu��

				CString FullPath;

				BOOL RedFLG;
				BOOL BoldFLG;

				CString rstr2;

				LONG hiddenFullPathIDX1;
				LONG hiddenFullPathIDX2;

				LONG X;
				LONG myidx;
				LONG CurrentStep;
	                    
				LONG myidx2;
				//LONG DoWithCnt;

				BOOL ReadErrorFLG = FALSE;

				if ((rstr.Find(_T("<tr>"),0) == 0 ) && (rstr.Find(_T("</tr>"),0) >= (rstr.GetLength() - GetStrLen_Func(_T("</tr>"))))){ //Len("</tr>")=5){
					myidx2 = 0;
					CurrentStep = 1;
	                    
					X = 0;
	
					while (X <= rstr.GetLength()-1){
						MSG msg; //�ǉ� 2011.10.12

						if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
							if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
								if (msg.wParam == VK_ESCAPE){
									ESCAPE_FLG = TRUE;
									break; //�I���B���b�Z�[�W���[�v�𔲂���B
								}
							}
							TranslateMessage(&msg);
							DispatchMessage(&msg);
							//continue;
						}

						//MessageBox (rstr);
						if( CurrentStep== 1){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(GetStrLen_Func(_T("</td>")),X);

							//Call myActivateFunc(6 + MaxCnt)
							//�d���i���o�[
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%s"), _T(""));	//�ʂ��ԍ�
								lvi.iItem = CFileListCreatorDlg::m_xcList.GetItemCount();
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 0;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));	//�t�@�C���d�����ʃi���o�[

								index = CFileListCreatorDlg::m_xcList.InsertItem(&lvi); //err = 1;
							}

							//�ʂ��ԍ�
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%d"), index+1);	//�ʂ��ԍ�
								lvi.iItem = index;
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 1;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}
							CurrentStep = 2;
							//break;
						}else if( CurrentStep== 2){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);

							rstr2 = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>"))); //- GetStrLen_Func(_T("--->")
	                        
							//BOOL RedFLG;
							RedFLG = FALSE;
	                                
							CString RedTag1;

							RedTag1 = _T("<font color=\"red\">");
	                                
							CString  RedTag2;
							RedTag2 = _T("</font>");
	                                
							LONG RedIDX1;
							RedIDX1 = rstr.Find(RedTag1,myidx);
	                                
							LONG RedIDX2;
							RedIDX2 = rstr.Find(RedTag2,myidx);
	                            
							CString FormatDataStr;
							//FormatDataStr = _T("NORMAL,BLACK,");

							FormatDataStr = _T("BLACK,");

							if( RedIDX1 >= 0 && RedIDX2 >= 0){

								
								FormatDataStr = _T("RED,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());
								RedFLG = TRUE;
							}else{
								CString FormatDataStr;
								FormatDataStr = _T("BLACK,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
							}
	                                
							//CString FullPath;
	                        
							//LONG hiddenFullPathIDX1;
							//LONG hiddenFullPathIDX2;
	                                    
							hiddenFullPathIDX1 = rstr.Find(_T("<!---"),0);
							X = hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")+1);//+1
							hiddenFullPathIDX2 = rstr.Find(_T("--->"),X);
	                                    
							if (hiddenFullPathIDX1 >= 0 && hiddenFullPathIDX2 >= 0 ){

	  
								FullPath = rstr.Mid( hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")), hiddenFullPathIDX2 - hiddenFullPathIDX1 - GetStrLen_Func(_T("<!---")));
	                                                                                                                     
							}else{

							}
	                                    
							//BOOL BoldFLG;
							BoldFLG = FALSE;
	                                    
							LONG BoldIDX;
							BoldIDX = rstr2.Find(_T("<b>"), 0);
	                                   
							LONG BoldIDX2;
							BoldIDX2 = rstr2.Find(_T("</b>"),BoldIDX + GetStrLen_Func(_T("<b>")));
	                                    
							if (BoldIDX >= 0 && BoldIDX2 >= 0) {
	                                        
								rstr2 = rstr2.Mid(BoldIDX + GetStrLen_Func(_T("<b>")), BoldIDX2 - BoldIDX - GetStrLen_Func(_T("<b>")));                           
								FormatDataStr = _T("BOLD,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								//rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());

								BoldFLG = TRUE;

							}else{
								FormatDataStr = _T("NORMAL,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
								BoldFLG = FALSE;
							}


							// �t���p�X
							if (!err)
							{
								//lvi.mask = LVIF_TEXT;
								//lvi.lParam = m_id++;        // ID
								lvi.iItem = index;
								lvi.iSubItem = 2;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPath));
								//MessageBox (FullPath);
								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}	                                            
	                                            
							if(BoldFLG == TRUE ||  RedFLG == TRUE){
								// �t�@�C����
								if (!err)
								{									
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}
							}else{
								CString temp;
								temp = rstr2.Left(rstr2.Find(_T("<!---"),0));
								//MessageBox (temp);
								// �t�@�C����
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
								}
	                                        
								if( BoldFLG == TRUE ||  RedFLG == TRUE ){
									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}else{
									CString temp;
									temp =rstr2.Left(rstr2.Find(_T("<!---"),0));

									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}
							}
							X = hiddenFullPathIDX2 + GetStrLen_Func(_T("--->")) + GetStrLen_Func(_T("</td>"));


							CurrentStep = 3;

							//break;
						}else if( CurrentStep== 3){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);
	                    
							CString tempSize;
							if( myidx >= 0 && myidx2 >= 0 ){
								tempSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
							}else{
								tempSize = "";
							}
	                                
							LONG SizeNumIDX1;
							LONG SizeNumIDX2;
	                                
							SizeNumIDX1 = tempSize.Find(_T("<!---"),0);
							X = SizeNumIDX1 + GetStrLen_Func(_T("<!---"));
							SizeNumIDX2 = tempSize.Find(_T("--->"),X);

						
							CString myFileSize;

							if( SizeNumIDX1 >= 0 && SizeNumIDX2 >= 0 ) {


								myFileSize = tempSize.Mid(SizeNumIDX1 +GetStrLen_Func(_T("<!---")), SizeNumIDX2 - SizeNumIDX1 - GetStrLen_Func(_T("<!---")));

								
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 5;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}


								myFileSize = tempSize.Mid( 0, SizeNumIDX1);

								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}else{
								myFileSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}

							X = myidx + SizeNumIDX2 + GetStrLen_Func(_T("--->"));
	                                       
							CurrentStep = 4;
							//MessageBox (_T("1111111"));
							//break;
						}else if( CurrentStep== 4){
								
			          		myidx = rstr.Find(_T("<td>"),X);
			                X = myidx + GetStrLen_Func(_T("<td>"));
			                myidx2 = rstr.Find(_T("</td>"),X);

		                    CString tempDate;
			                    
			                if ( myidx >= 0 && myidx2 >= 0 ){
			                    tempDate = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
			                }else{
			                    tempDate = _T("");
			                }
			                    
								
			                LONG DateIDX1;
			                LONG DateIDX2;
			                                
			                DateIDX1 = tempDate.Find(_T("<!---") ,0);
			                X = DateIDX1 + GetStrLen_Func(_T("<!---"));
			                DateIDX2 = tempDate.Find(_T("--->") ,X);

			                                
							CString tempStr;

			                if(DateIDX1 >= 0 && DateIDX2 >= 0 ){

								tempStr = tempDate.Mid(DateIDX1 + GetStrLen_Func(_T("<!---")),DateIDX2 - DateIDX1 - GetStrLen_Func(_T("<!---")));
								//�C������
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 7;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}			                                   

								tempStr = tempDate.Mid(0,DateIDX1);
								//�C����
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 6;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}
			                }else{
								tempStr = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
								//�C����
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 6;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}
			                }

			                X = myidx + DateIDX2 + GetStrLen_Func(_T("--->"));

							CurrentStep = 5;
							//break; 
						}else if( CurrentStep== 5){
								
			          		myidx = rstr.Find(_T("<td>"),X);
			                X = myidx + GetStrLen_Func(_T("<td>"));
			                myidx2 = rstr.Find(_T("</td>"),X);

		                    CString tempStr ;
			                    
			                if ( myidx >= 0 && myidx2 >= 0 ){
			                    tempStr = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
			                }else{
			                    tempStr = _T("");
							}

			                if ( myidx >= 0 && myidx2 >= 0 ){
								//���l��
								if (!err)
								{	
									if(tempStr == _T("   ")){
										tempStr = _T("");
									}
									lvi.iItem = index;
									lvi.iSubItem = 8;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}			                                   

		
			                }

			                X = myidx2 + GetStrLen_Func(_T("</td>"));  // X = myidx + myidx2 + GetStrLen_Func(_T("--->")); //�ύX 2012.07.11

							CurrentStep = 6;
							//break; 
						}else if( CurrentStep== 6){
							//MaxCnt = MaxCnt + 1
							DoWithCnt = DoWithCnt + 1;
							CFileListCreatorDlg::ItemCount_Func(TRUE);
							CurrentStep = 7;
							//break;
						}else if( CurrentStep== 7){
							int stepIDX;
							for( stepIDX = 0; stepIDX <= 10; stepIDX++){
								CurrentStepCheck[stepIDX] = 0;
							}

							//X=rstr.GetLength();

							CurrentStep =1;//
							break;
							//goto label;
							
						}else{
							X = X + 1;
							//MessageBox (_T("1111111"));
							//break;
						}

						UpdateData(FALSE);
						CurrentStepCheck[CurrentStep] = CurrentStepCheck[CurrentStep] + 1;
	                        
						if( CurrentStepCheck[CurrentStep] >=2){
							ReadErrorFLG = TRUE;
							break;
						}
					}
				}


				CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE);
				UpdateWindow();

				if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1 || MiniWindowFLG == FALSE){
					m_xcStaticString.ShowWindow(SW_HIDE);
				}else{
					m_xcStaticString.ShowWindow(SW_SHOW);
				}

				CString tempStatus;
				tempStatus.Format(_T("HTML �C���|�[�g ���s�� ( %I64u / %I64u ) ") , DoWithCnt,TotalItemsCount);					
				StatusStringSet(tempStatus,0,FALSE);
				UpdateData(FALSE);

			}
		}
			
	}



	if (inGeneratorVer == _T("<!---FLC Generator Version 1.5.2--->")){  //���X�V�� �\�� //�����l�� ��\��

		while (!err) {
			if (ESCAPE_FLG == TRUE) break;

			if (stdFile.ReadString(rstr) == FALSE) err = 1;

			if (rstr!=_T("")){

				//CString tempStrForLen;
	 			LONG stepIDX;
				int CurrentStepCheck[11];
		    
				for(stepIDX = 0;stepIDX<=10; stepIDX++){
					CurrentStepCheck[stepIDX] = 0;
				}

        
	            
				//rstr = _
				//Replace(rstr, "<", "��")
	                
				//rstr = _
				//Replace(rstr, ">", "��")
	    
				//rstr.Replace(_T("&lt;"), _T("<"));
				//rstr.Replace(_T("&gt;"), _T(">"));
				//rstr.Replace(_T("&quot;"), _T("\""));
	   // 
				rstr.Replace(_T("&nbsp;"), _T(" "));
				//rstr.Replace(_T("&copy;"), _T("(c)"));
				//rstr.Replace(_T("&reg;"), _T("(r)")); 
				//rstr.Replace(_T("&amp;"), _T("&"));//�Ō�ɒu��

				CString FullPath;

				BOOL RedFLG;
				BOOL BoldFLG;

				CString rstr2;

				LONG hiddenFullPathIDX1;
				LONG hiddenFullPathIDX2;

				LONG X;
				LONG myidx;
				LONG CurrentStep;
	                    
				LONG myidx2;
				//LONG DoWithCnt;

				BOOL ReadErrorFLG = FALSE;

				if ((rstr.Find(_T("<tr>"),0) == 0 ) && (rstr.Find(_T("</tr>"),0) >= (rstr.GetLength() - GetStrLen_Func(_T("</tr>"))))){ //Len("</tr>")=5){
					myidx2 = 0;
					CurrentStep = 1;
	                    
					X = 0;
	
					while (X <= rstr.GetLength()-1){
						MSG msg; //�ǉ� 2011.10.12

						if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
							if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
								if (msg.wParam == VK_ESCAPE){
									ESCAPE_FLG = TRUE;
									break; //�I���B���b�Z�[�W���[�v�𔲂���B
								}
							}
							TranslateMessage(&msg);
							DispatchMessage(&msg);
							//continue;
						}

						//MessageBox (rstr);
						if( CurrentStep== 1){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(GetStrLen_Func(_T("</td>")),X);

							//Call myActivateFunc(6 + MaxCnt)
							//�d���i���o�[
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%s"), _T(""));	//�ʂ��ԍ�
								lvi.iItem = CFileListCreatorDlg::m_xcList.GetItemCount();
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 0;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));	//�t�@�C���d�����ʃi���o�[

								index = CFileListCreatorDlg::m_xcList.InsertItem(&lvi); //err = 1;
							}

							//�ʂ��ԍ�
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%d"), index+1);	//�ʂ��ԍ�
								lvi.iItem = index;
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 1;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}
							CurrentStep = 2;
							//break;
						}else if( CurrentStep== 2){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);

							rstr2 = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>"))); //- GetStrLen_Func(_T("--->")
	                        
							//BOOL RedFLG;
							RedFLG = FALSE;
	                                
							CString RedTag1;

							RedTag1 = _T("<font color=\"red\">");
	                                
							CString  RedTag2;
							RedTag2 = _T("</font>");
	                                
							LONG RedIDX1;
							RedIDX1 = rstr.Find(RedTag1,myidx);
	                                
							LONG RedIDX2;
							RedIDX2 = rstr.Find(RedTag2,myidx);
	                            
							CString FormatDataStr;
							//FormatDataStr = _T("NORMAL,BLACK,");

							FormatDataStr = _T("BLACK,");

							if( RedIDX1 >= 0 && RedIDX2 >= 0){

								
								FormatDataStr = _T("RED,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());
								RedFLG = TRUE;
							}else{
								CString FormatDataStr;
								FormatDataStr = _T("BLACK,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
							}
	                                
							//CString FullPath;
	                        
							//LONG hiddenFullPathIDX1;
							//LONG hiddenFullPathIDX2;
	                                    
							hiddenFullPathIDX1 = rstr.Find(_T("<!---"),0);
							X = hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")+1);//+1
							hiddenFullPathIDX2 = rstr.Find(_T("--->"),X);
	                                    
							if (hiddenFullPathIDX1 >= 0 && hiddenFullPathIDX2 >= 0 ){

	  
								FullPath = rstr.Mid( hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")), hiddenFullPathIDX2 - hiddenFullPathIDX1 - GetStrLen_Func(_T("<!---")));
	                                                                                                                     
							}else{

							}
	                                    
							//BOOL BoldFLG;
							BoldFLG = FALSE;
	                                    
							LONG BoldIDX;
							BoldIDX = rstr2.Find(_T("<b>"), 0);
	                                   
							LONG BoldIDX2;
							BoldIDX2 = rstr2.Find(_T("</b>"),BoldIDX + GetStrLen_Func(_T("<b>")));
	                                    
							if (BoldIDX >= 0 && BoldIDX2 >= 0) {
	                                        
								rstr2 = rstr2.Mid(BoldIDX + GetStrLen_Func(_T("<b>")), BoldIDX2 - BoldIDX - GetStrLen_Func(_T("<b>")));                           
								FormatDataStr = _T("BOLD,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								//rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());

								BoldFLG = TRUE;

							}else{
								FormatDataStr = _T("NORMAL,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
								BoldFLG = FALSE;
							}


							// �t���p�X
							if (!err)
							{
								//lvi.mask = LVIF_TEXT;
								//lvi.lParam = m_id++;        // ID
								lvi.iItem = index;
								lvi.iSubItem = 2;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPath));
								//MessageBox (FullPath);
								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}	                                            
	                                            
							if(BoldFLG == TRUE ||  RedFLG == TRUE){
								// �t�@�C����
								if (!err)
								{									
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}
							}else{
								CString temp;
								temp = rstr2.Left(rstr2.Find(_T("<!---"),0));
								//MessageBox (temp);
								// �t�@�C����
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
								}
	                                        
								if( BoldFLG == TRUE ||  RedFLG == TRUE ){
									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}else{
									CString temp;
									temp =rstr2.Left(rstr2.Find(_T("<!---"),0));

									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}
							}
							X = hiddenFullPathIDX2 + GetStrLen_Func(_T("--->")) + GetStrLen_Func(_T("</td>"));


							CurrentStep = 3;

							//break;
						}else if( CurrentStep== 3){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);
	                    
							CString tempSize;
							if( myidx >= 0 && myidx2 >= 0 ){
								tempSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
							}else{
								tempSize = "";
							}
	                                
							LONG SizeNumIDX1;
							LONG SizeNumIDX2;
	                                
							SizeNumIDX1 = tempSize.Find(_T("<!---"),0);
							X = SizeNumIDX1 + GetStrLen_Func(_T("<!---"));
							SizeNumIDX2 = tempSize.Find(_T("--->"),X);

						
							CString myFileSize;

							if( SizeNumIDX1 >= 0 && SizeNumIDX2 >= 0 ) {


								myFileSize = tempSize.Mid(SizeNumIDX1 +GetStrLen_Func(_T("<!---")), SizeNumIDX2 - SizeNumIDX1 - GetStrLen_Func(_T("<!---")));

								
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 5;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}


								myFileSize = tempSize.Mid( 0, SizeNumIDX1);

								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}else{
								myFileSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}

							X = myidx + SizeNumIDX2 + GetStrLen_Func(_T("--->"));
	                                       
							CurrentStep = 4;
							//MessageBox (_T("1111111"));
							//break;
						}else if( CurrentStep== 4){
								
			          			myidx = rstr.Find(_T("<td>"),X);
			                    X = myidx + GetStrLen_Func(_T("<td>"));
			                    myidx2 = rstr.Find(_T("</td>"),X);

		                        CString tempDate;
			                    
			                    if ( myidx >= 0 && myidx2 >= 0 ){
			                        tempDate = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
			                    }else{
			                        tempDate = _T("");
			                    }
			                    
								
			                    LONG DateIDX1;
			                    LONG DateIDX2;
			                                
			                    DateIDX1 = tempDate.Find(_T("<!---") ,0);
			                    X = DateIDX1 + GetStrLen_Func(_T("<!---"));
			                    DateIDX2 = tempDate.Find(_T("--->") ,X);

		                                
								CString tempStr;

			                    if(DateIDX1 >= 0 && DateIDX2 >= 0 ){

									tempStr = tempDate.Mid(DateIDX1 + GetStrLen_Func(_T("<!---")),DateIDX2 - DateIDX1 - GetStrLen_Func(_T("<!---")));
									//�C������
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 7;
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}			                                   

									tempStr = tempDate.Mid(0,DateIDX1);
									//�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 6;
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
			                    }else{
									tempStr = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
									//�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 6;
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
			                    }

			                    X = myidx + DateIDX2 + GetStrLen_Func(_T("--->"));

								CurrentStep = 5;
								//break; 
						}else if( CurrentStep== 5){
			                if(X >= 1){
			                    X = X - 1;
			                }								

			                LONG RemarksIDX1;
			                LONG RemarksIDX2;
			                                
			                RemarksIDX1 = rstr.Find(_T("<!---") ,X);
			                X = RemarksIDX1 + GetStrLen_Func(_T("<!---"));
			                RemarksIDX2 = rstr.Find(_T("--->") ,X);


			                if(RemarksIDX1 >= 0 && RemarksIDX2 >= 0 ){
								CString tempStr;

								tempStr = rstr.Mid(RemarksIDX1 + GetStrLen_Func(_T("<!---")),RemarksIDX2 - RemarksIDX1 - GetStrLen_Func(_T("<!---")));
								//���l��
								if (!err)
								{	
									if(tempStr == _T("   ")){
										tempStr = _T("");
									}
									lvi.iItem = index;
									lvi.iSubItem = 8;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}			                                   

		
			                }

			                X = RemarksIDX2 + GetStrLen_Func(_T("--->")); //X = myidx + RemarksIDX2 + GetStrLen_Func(_T("--->")); //�ύX 2012.07.11

							CurrentStep = 6;
							//break; 
						}else if( CurrentStep== 6){
							//MaxCnt = MaxCnt + 1
							DoWithCnt = DoWithCnt + 1;
							CFileListCreatorDlg::ItemCount_Func(TRUE);
							CurrentStep = 7;
							//break;
						}else if( CurrentStep== 7){
							int stepIDX;
							for( stepIDX = 0; stepIDX <= 10; stepIDX++){
								CurrentStepCheck[stepIDX] = 0;
							}

							//X=rstr.GetLength();

							CurrentStep =1;//
							break;
							//goto label;
							
						}else{
							X = X + 1;
							//MessageBox (_T("1111111"));
							//break;
						}
						UpdateData(FALSE);
						CurrentStepCheck[CurrentStep] = CurrentStepCheck[CurrentStep] + 1;
	                        
						if( CurrentStepCheck[CurrentStep] >=2){
							ReadErrorFLG = TRUE;
							break;
						}
					}
				}

				CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE);
				UpdateWindow();

				if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1 || MiniWindowFLG == FALSE){
					m_xcStaticString.ShowWindow(SW_HIDE);
				}else{
					m_xcStaticString.ShowWindow(SW_SHOW);
				}

				CString tempStatus;
				tempStatus.Format(_T("HTML �C���|�[�g ���s�� ( %I64u / %I64u ) ") , DoWithCnt,TotalItemsCount);					
				StatusStringSet(tempStatus,0,FALSE);
				UpdateData(FALSE);

			}
		}
			
	}


	if (inGeneratorVer == _T("<!---FLC Generator Version 1.5.3--->")){  //���X�V�� ��\��  //�����l�� �\��

		while (!err) {
			if (ESCAPE_FLG == TRUE) break;

			if (stdFile.ReadString(rstr) == FALSE) err = 1;

			if (rstr!=_T("")){

				//CString tempStrForLen;
	 			LONG stepIDX;
				int CurrentStepCheck[11];
		    
				for(stepIDX = 0;stepIDX<=10; stepIDX++){
					CurrentStepCheck[stepIDX] = 0;
				}

        
	            
				//rstr = _
				//Replace(rstr, "<", "��")
	                
				//rstr = _
				//Replace(rstr, ">", "��")
	    
				//rstr.Replace(_T("&lt;"), _T("<"));
				//rstr.Replace(_T("&gt;"), _T(">"));
				//rstr.Replace(_T("&quot;"), _T("\""));
	   // 
				rstr.Replace(_T("&nbsp;"), _T(" "));
				//rstr.Replace(_T("&copy;"), _T("(c)"));
				//rstr.Replace(_T("&reg;"), _T("(r)"));

				////&apos; 
				//rstr.Replace(_T("&amp;"), _T("&"));//�Ō�ɒu��

				CString FullPath;

				BOOL RedFLG;
				BOOL BoldFLG;

				CString rstr2;

				LONG hiddenFullPathIDX1;
				LONG hiddenFullPathIDX2;

				LONG X;
				LONG myidx;
				LONG CurrentStep;
	                    
				LONG myidx2;
				//LONG DoWithCnt;

				BOOL ReadErrorFLG = FALSE;

				if ((rstr.Find(_T("<tr>"),0) == 0 ) && (rstr.Find(_T("</tr>"),0) >= (rstr.GetLength() - GetStrLen_Func(_T("</tr>"))))){ //Len("</tr>")=5){
					myidx2 = 0;
					CurrentStep = 1;
	                    
					X = 0;
	
					while (X <= rstr.GetLength()-1){
						MSG msg; //�ǉ� 2011.10.12

						if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
							if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
								if (msg.wParam == VK_ESCAPE){
									ESCAPE_FLG = TRUE;
									break; //�I���B���b�Z�[�W���[�v�𔲂���B
								}
							}
							TranslateMessage(&msg);
							DispatchMessage(&msg);
							//continue;
						}

						//MessageBox (rstr);
						if( CurrentStep== 1){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(GetStrLen_Func(_T("</td>")),X);

							//Call myActivateFunc(6 + MaxCnt)
							//�d���i���o�[
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%s"), _T(""));	//�ʂ��ԍ�
								lvi.iItem = CFileListCreatorDlg::m_xcList.GetItemCount();
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 0;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));	//�t�@�C���d�����ʃi���o�[

								index = CFileListCreatorDlg::m_xcList.InsertItem(&lvi); //err = 1;
							}

							//�ʂ��ԍ�
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%d"), index+1);	//�ʂ��ԍ�
								lvi.iItem = index;
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 1;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}
							CurrentStep = 2;
							//break;
						}else if( CurrentStep== 2){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);

							rstr2 = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>"))); //- GetStrLen_Func(_T("--->")
	                        
							//BOOL RedFLG;
							RedFLG = FALSE;
	                                
							CString RedTag1;

							RedTag1 = _T("<font color=\"red\">");
	                                
							CString  RedTag2;
							RedTag2 = _T("</font>");
	                                
							LONG RedIDX1;
							RedIDX1 = rstr.Find(RedTag1,myidx);
	                                
							LONG RedIDX2;
							RedIDX2 = rstr.Find(RedTag2,myidx);
	                            
							CString FormatDataStr;
							//FormatDataStr = _T("NORMAL,BLACK,");

							FormatDataStr = _T("BLACK,");

							if( RedIDX1 >= 0 && RedIDX2 >= 0){

								
								FormatDataStr = _T("RED,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());
								RedFLG = TRUE;
							}else{
								CString FormatDataStr;
								FormatDataStr = _T("BLACK,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
							}
	                                
							//CString FullPath;
	                        
							//LONG hiddenFullPathIDX1;
							//LONG hiddenFullPathIDX2;
	                                    
							hiddenFullPathIDX1 = rstr.Find(_T("<!---"),0);
							X = hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")+1);//+1
							hiddenFullPathIDX2 = rstr.Find(_T("--->"),X);
	                                    
							if (hiddenFullPathIDX1 >= 0 && hiddenFullPathIDX2 >= 0 ){

	  
								FullPath = rstr.Mid( hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")), hiddenFullPathIDX2 - hiddenFullPathIDX1 - GetStrLen_Func(_T("<!---")));
	                                                                                                                     
							}else{

							}
	                                    
							//BOOL BoldFLG;
							BoldFLG = FALSE;
	                                    
							LONG BoldIDX;
							BoldIDX = rstr2.Find(_T("<b>"), 0);
	                                   
							LONG BoldIDX2;
							BoldIDX2 = rstr2.Find(_T("</b>"),BoldIDX + GetStrLen_Func(_T("<b>")));
	                                    
							if (BoldIDX >= 0 && BoldIDX2 >= 0) {
	                                        
								rstr2 = rstr2.Mid(BoldIDX + GetStrLen_Func(_T("<b>")), BoldIDX2 - BoldIDX - GetStrLen_Func(_T("<b>")));                           
								FormatDataStr = _T("BOLD,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								//rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());

								BoldFLG = TRUE;

							}else{
								FormatDataStr = _T("NORMAL,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
								BoldFLG = FALSE;
							}


							// �t���p�X
							if (!err)
							{
								//lvi.mask = LVIF_TEXT;
								//lvi.lParam = m_id++;        // ID
								lvi.iItem = index;
								lvi.iSubItem = 2;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPath));
								//MessageBox (FullPath);
								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}	                                            
	                                            
							if(BoldFLG == TRUE ||  RedFLG == TRUE){
								// �t�@�C����
								if (!err)
								{									
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}
							}else{
								CString temp;
								temp = rstr2.Left(rstr2.Find(_T("<!---"),0));
								//MessageBox (temp);
								// �t�@�C����
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
								}
	                                        
								if( BoldFLG == TRUE ||  RedFLG == TRUE ){
									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}else{
									CString temp;
									temp =rstr2.Left(rstr2.Find(_T("<!---"),0));

									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}
							}
							X = hiddenFullPathIDX2 + GetStrLen_Func(_T("--->")) + GetStrLen_Func(_T("</td>"));


							CurrentStep = 3;

							//break;
						}else if( CurrentStep== 3){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);
	                    
							CString tempSize;
							if( myidx >= 0 && myidx2 >= 0 ){
								tempSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
							}else{
								tempSize = "";
							}
	                                
							LONG SizeNumIDX1;
							LONG SizeNumIDX2;
	                                
							SizeNumIDX1 = tempSize.Find(_T("<!---"),0);
							X = SizeNumIDX1 + GetStrLen_Func(_T("<!---"));
							SizeNumIDX2 = tempSize.Find(_T("--->"),X);

							
							CString myFileSize;

							if( SizeNumIDX1 >= 0 && SizeNumIDX2 >= 0 ) {


								myFileSize = tempSize.Mid(SizeNumIDX1 +GetStrLen_Func(_T("<!---")), SizeNumIDX2 - SizeNumIDX1 - GetStrLen_Func(_T("<!---")));

								
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 5;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}


								myFileSize = tempSize.Mid( 0, SizeNumIDX1);

								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}else{
								myFileSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}

							X = myidx + SizeNumIDX2 + GetStrLen_Func(_T("--->"));
	                                       
							CurrentStep = 4;
							//break;
						}else if( CurrentStep== 4){

			                if(X >= 1){
			                    X = X - 1;
			                }

							//myidx = rstr.Find(_T("<td>"),X);
			                //X = myidx + GetStrLen_Func(_T("<td>"));
			                //myidx2 = rstr.Find(_T("</td>"),X);

		                    CString tempDate;
			                    
			                if ( myidx >= 0 && myidx2 >= 0 ){
			                    tempDate = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
			                }else{
			                    tempDate = _T("");
			                }
			                  
							
							LONG DateIDX1;
							LONG DateIDX2;
			                                
							DateIDX1 = rstr.Find(_T("<!---") ,X);
							X = DateIDX1 + GetStrLen_Func(_T("<!---"));
							DateIDX2 = rstr.Find(_T("--->") ,X);
	                                
							CString tempStr;

			                if(DateIDX1 >= 0 && DateIDX2 >= 0 ){
								tempStr = rstr.Mid(DateIDX1 + GetStrLen_Func(_T("<!---")),DateIDX2 - DateIDX1 - GetStrLen_Func(_T("<!---")));
								//�C����
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 6;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
								}
							}

							X = DateIDX2 + GetStrLen_Func(_T("--->"));


			                DateIDX1 = rstr.Find(_T("<!---") ,X);
			                X = DateIDX1 + GetStrLen_Func(_T("<!---"));
			                DateIDX2 = rstr.Find(_T("--->") ,X);

			                if(DateIDX1 >= 0 && DateIDX2 >= 0 ){
								tempStr = rstr.Mid(DateIDX1 + GetStrLen_Func(_T("<!---")),DateIDX2 - DateIDX1 - GetStrLen_Func(_T("<!---")));
								//�C������
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 7;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}
			                                    
			                }

							X = DateIDX2 + GetStrLen_Func(_T("--->"));

							CurrentStep = 5;
							//break; 
						}else if( CurrentStep== 5){
								
			          		myidx = rstr.Find(_T("<td>"),X);
			                X = myidx + GetStrLen_Func(_T("<td>"));
			                myidx2 = rstr.Find(_T("</td>"),X);

		                    CString tempStr ;
			                    
			                if ( myidx >= 0 && myidx2 >= 0 ){
			                    tempStr = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
			                }else{
			                    tempStr = _T("");
							}

			                if ( myidx >= 0 && myidx2 >= 0 ){
								//���l��
								if (!err)
								{	
									if(tempStr == _T("   ")){
										tempStr = _T("");
									}
									lvi.iItem = index;
									lvi.iSubItem = 8;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}			                                   

		
			                }

			                X = myidx2 + GetStrLen_Func(_T("</td>"));  // X = myidx + myidx2 + GetStrLen_Func(_T("--->")); //�ύX 2012.07.11

							CurrentStep = 6;
							//break; 
						}else if( CurrentStep== 6){
							//MaxCnt = MaxCnt + 1
							DoWithCnt = DoWithCnt + 1;
							CFileListCreatorDlg::ItemCount_Func(TRUE);
							CurrentStep = 7;
							//break;
						}else if( CurrentStep== 7){
							int stepIDX;
							for( stepIDX = 0; stepIDX <= 10; stepIDX++){
								CurrentStepCheck[stepIDX] = 0;
							}

							//X=rstr.GetLength();

							CurrentStep =1;//
							break;
							//goto label;
							
						}else{
							X = X + 1;
							//MessageBox (_T("1111111"));
							//break;
						}
						UpdateData(FALSE);
						CurrentStepCheck[CurrentStep] = CurrentStepCheck[CurrentStep] + 1;
	                        
						if( CurrentStepCheck[CurrentStep] >=2){
							ReadErrorFLG = TRUE;
							break;
						}
					}
				}

				CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE);
				UpdateWindow();

				if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1 || MiniWindowFLG == FALSE){
					m_xcStaticString.ShowWindow(SW_HIDE);
				}else{
					m_xcStaticString.ShowWindow(SW_SHOW);
				}

				CString tempStatus;
				tempStatus.Format(_T("HTML �C���|�[�g ���s�� ( %I64u / %I64u ) ") , DoWithCnt,TotalItemsCount);					
				StatusStringSet(tempStatus,0,FALSE);
				UpdateData(FALSE);

			}
		}
			
	}


	if (inGeneratorVer == _T("<!---FLC Generator Version 1.5.4--->")){  //���X�V�� ��\��  //�����l�� ��\��

		while (!err) {
			if (ESCAPE_FLG == TRUE) break;

			if (stdFile.ReadString(rstr) == FALSE) err = 1;

			if (rstr!=_T("")){

				//CString tempStrForLen;
	 			LONG stepIDX;
				int CurrentStepCheck[11];
		    
				for(stepIDX = 0;stepIDX<=10; stepIDX++){
					CurrentStepCheck[stepIDX] = 0;
				}

        
	            
				//rstr = _
				//Replace(rstr, "<", "��")
	                
				//rstr = _
				//Replace(rstr, ">", "��")
	    
				//rstr.Replace(_T("&lt;"), _T("<"));
				//rstr.Replace(_T("&gt;"), _T(">"));
				//rstr.Replace(_T("&quot;"), _T("\""));
	   // 
				rstr.Replace(_T("&nbsp;"), _T(" "));
				//rstr.Replace(_T("&copy;"), _T("(c)"));
				//rstr.Replace(_T("&reg;"), _T("(r)"));

				////&apos; 
				//rstr.Replace(_T("&amp;"), _T("&"));//�Ō�ɒu��

				CString FullPath;

				BOOL RedFLG;
				BOOL BoldFLG;

				CString rstr2;

				LONG hiddenFullPathIDX1;
				LONG hiddenFullPathIDX2;

				LONG X;
				LONG myidx;
				LONG CurrentStep;
	                    
				LONG myidx2;
				//LONG DoWithCnt;

				BOOL ReadErrorFLG = FALSE;

				if ((rstr.Find(_T("<tr>"),0) == 0 ) && (rstr.Find(_T("</tr>"),0) >= (rstr.GetLength() - GetStrLen_Func(_T("</tr>"))))){ //Len("</tr>")=5){
					myidx2 = 0;
					CurrentStep = 1;
	                    
					X = 0;
	
					while (X <= rstr.GetLength()-1){
						MSG msg; //�ǉ� 2011.10.12

						if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
							if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
								if (msg.wParam == VK_ESCAPE){
									ESCAPE_FLG = TRUE;
									break; //�I���B���b�Z�[�W���[�v�𔲂���B
								}
							}
							TranslateMessage(&msg);
							DispatchMessage(&msg);
							//continue;
						}

						//MessageBox (rstr);
						if( CurrentStep== 1){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(GetStrLen_Func(_T("</td>")),X);

							//Call myActivateFunc(6 + MaxCnt)
							//�d���i���o�[
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%s"), _T(""));	//�ʂ��ԍ�
								lvi.iItem = CFileListCreatorDlg::m_xcList.GetItemCount();
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 0;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));	//�t�@�C���d�����ʃi���o�[

								index = CFileListCreatorDlg::m_xcList.InsertItem(&lvi); //err = 1;
							}

							//�ʂ��ԍ�
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%d"), index+1);	//�ʂ��ԍ�
								lvi.iItem = index;
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 1;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}
							CurrentStep = 2;
							//break;
						}else if( CurrentStep== 2){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);

							rstr2 = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>"))); //- GetStrLen_Func(_T("--->")
	                        
							//BOOL RedFLG;
							RedFLG = FALSE;
	                                
							CString RedTag1;

							RedTag1 = _T("<font color=\"red\">");
	                                
							CString  RedTag2;
							RedTag2 = _T("</font>");
	                                
							LONG RedIDX1;
							RedIDX1 = rstr.Find(RedTag1,myidx);
	                                
							LONG RedIDX2;
							RedIDX2 = rstr.Find(RedTag2,myidx);
	                            
							CString FormatDataStr;
							//FormatDataStr = _T("NORMAL,BLACK,");

							FormatDataStr = _T("BLACK,");

							if( RedIDX1 >= 0 && RedIDX2 >= 0){

								
								FormatDataStr = _T("RED,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());
								RedFLG = TRUE;
							}else{
								CString FormatDataStr;
								FormatDataStr = _T("BLACK,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
							}
	                                
							//CString FullPath;
	                        
							//LONG hiddenFullPathIDX1;
							//LONG hiddenFullPathIDX2;
	                                    
							hiddenFullPathIDX1 = rstr.Find(_T("<!---"),0);
							X = hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")+1);//+1
							hiddenFullPathIDX2 = rstr.Find(_T("--->"),X);
	                                    
							if (hiddenFullPathIDX1 >= 0 && hiddenFullPathIDX2 >= 0 ){

	  
								FullPath = rstr.Mid( hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")), hiddenFullPathIDX2 - hiddenFullPathIDX1 - GetStrLen_Func(_T("<!---")));
	                                                                                                                     
							}else{

							}
	                                    
							//BOOL BoldFLG;
							BoldFLG = FALSE;
	                                    
							LONG BoldIDX;
							BoldIDX = rstr2.Find(_T("<b>"), 0);
	                                   
							LONG BoldIDX2;
							BoldIDX2 = rstr2.Find(_T("</b>"),BoldIDX + GetStrLen_Func(_T("<b>")));
	                                    
							if (BoldIDX >= 0 && BoldIDX2 >= 0) {
	                                        
								rstr2 = rstr2.Mid(BoldIDX + GetStrLen_Func(_T("<b>")), BoldIDX2 - BoldIDX - GetStrLen_Func(_T("<b>")));                           
								FormatDataStr = _T("BOLD,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								//rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());

								BoldFLG = TRUE;

							}else{
								FormatDataStr = _T("NORMAL,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
								BoldFLG = FALSE;
							}

							// �t���p�X
							if (!err)
							{
								//lvi.mask = LVIF_TEXT;
								//lvi.lParam = m_id++;        // ID
								lvi.iItem = index;
								lvi.iSubItem = 2;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPath));
								//MessageBox (FullPath);
								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}	                                            
	                                            
							if(BoldFLG == TRUE ||  RedFLG == TRUE){
								// �t�@�C����
								if (!err)
								{									
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}
							}else{
								CString temp;
								temp = rstr2.Left(rstr2.Find(_T("<!---"),0));
								//MessageBox (temp);
								// �t�@�C����
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
								}
	                                        
								if( BoldFLG == TRUE ||  RedFLG == TRUE ){
									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}else{
									CString temp;
									temp =rstr2.Left(rstr2.Find(_T("<!---"),0));

									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}
							}
							X = hiddenFullPathIDX2 + GetStrLen_Func(_T("--->")) + GetStrLen_Func(_T("</td>"));


							CurrentStep = 3;

							//break;
						}else if( CurrentStep== 3){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);
	                    
							CString tempSize;
							if( myidx >= 0 && myidx2 >= 0 ){
								tempSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
							}else{
								tempSize = "";
							}
	                                
							LONG SizeNumIDX1;
							LONG SizeNumIDX2;
	                                
							SizeNumIDX1 = tempSize.Find(_T("<!---"),0);
							X = SizeNumIDX1 + GetStrLen_Func(_T("<!---"));
							SizeNumIDX2 = tempSize.Find(_T("--->"),X);

						
							CString myFileSize;

							if( SizeNumIDX1 >= 0 && SizeNumIDX2 >= 0 ) {


								myFileSize = tempSize.Mid(SizeNumIDX1 +GetStrLen_Func(_T("<!---")), SizeNumIDX2 - SizeNumIDX1 - GetStrLen_Func(_T("<!---")));

								
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 5;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}


								myFileSize = tempSize.Mid( 0, SizeNumIDX1);

								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}else{
								myFileSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}

							X = myidx + SizeNumIDX2 + GetStrLen_Func(_T("--->"));
	                                       
							CurrentStep = 4;
							//break;
						}else if( CurrentStep== 4){

			                if(X >= 1){
			                    X = X - 1;
			                }

							//myidx = rstr.Find(_T("<td>"),X);
			                //X = myidx + GetStrLen_Func(_T("<td>"));
			                //myidx2 = rstr.Find(_T("</td>"),X);

		                    CString tempDate;
			                    
			                if ( myidx >= 0 && myidx2 >= 0 ){
			                    tempDate = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
			                }else{
			                    tempDate = _T("");
			                }
			                  
							
							LONG DateIDX1;
							LONG DateIDX2;
			                                
							DateIDX1 = rstr.Find(_T("<!---") ,X);
							X = DateIDX1 + GetStrLen_Func(_T("<!---"));
							DateIDX2 = rstr.Find(_T("--->") ,X);


							CString tempStr;

			                if(DateIDX1 >= 0 && DateIDX2 >= 0 ){
								tempStr = rstr.Mid(DateIDX1 + GetStrLen_Func(_T("<!---")),DateIDX2 - DateIDX1 - GetStrLen_Func(_T("<!---")));
								//�C����
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 6;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
								}
							}

							X = DateIDX2 + GetStrLen_Func(_T("--->"));


			                DateIDX1 = rstr.Find(_T("<!---") ,X);
			                X = DateIDX1 + GetStrLen_Func(_T("<!---"));
			                DateIDX2 = rstr.Find(_T("--->") ,X);

			                if(DateIDX1 >= 0 && DateIDX2 >= 0 ){
								tempStr = rstr.Mid(DateIDX1 + GetStrLen_Func(_T("<!---")),DateIDX2 - DateIDX1 - GetStrLen_Func(_T("<!---")));
								//�C������
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 7;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}
			                                    
			                }

							X = DateIDX2 + GetStrLen_Func(_T("--->"));

							CurrentStep = 5;
							//break; 
						}else if( CurrentStep== 5){
			                if(X >= 1){
			                    X = X - 1;
			                }								

			                LONG RemarksIDX1;
			                LONG RemarksIDX2;
			                                
			                RemarksIDX1 = rstr.Find(_T("<!---") ,X);
			                X = RemarksIDX1 + GetStrLen_Func(_T("<!---"));
			                RemarksIDX2 = rstr.Find(_T("--->") ,X);

			                if(RemarksIDX1 >= 0 && RemarksIDX2 >= 0 ){
								CString tempStr;

								tempStr = rstr.Mid(RemarksIDX1 + GetStrLen_Func(_T("<!---")),RemarksIDX2 - RemarksIDX1 - GetStrLen_Func(_T("<!---")));
								//���l��
								if (!err)
								{	
									if(tempStr == _T("   ")){
										tempStr = _T("");
									}
									lvi.iItem = index;
									lvi.iSubItem = 8;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}			                                   

		
			                }

							X = RemarksIDX2 + GetStrLen_Func(_T("--->")); //X = myidx + RemarksIDX2 + GetStrLen_Func(_T("--->")); //�ύX 2012.07.11

							CurrentStep = 6;
							//break; 
						}else if( CurrentStep== 6){
							//MaxCnt = MaxCnt + 1
							DoWithCnt = DoWithCnt + 1;
							CFileListCreatorDlg::ItemCount_Func(TRUE);
							CurrentStep = 7;
							//break;
						}else if( CurrentStep== 7){
							int stepIDX;
							for( stepIDX = 0; stepIDX <= 10; stepIDX++){
								CurrentStepCheck[stepIDX] = 0;
							}

							//X=rstr.GetLength();

							CurrentStep =1;//
							break;
							//goto label;
							
						}else{
							X = X + 1;
							//MessageBox (_T("1111111"));
							//break;
						}
						UpdateData(FALSE);
						CurrentStepCheck[CurrentStep] = CurrentStepCheck[CurrentStep] + 1;
	                        
						if( CurrentStepCheck[CurrentStep] >=2){
							ReadErrorFLG = TRUE;
							break;
						}
					}
				}

				CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE);
				UpdateWindow();

				if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1 || MiniWindowFLG == FALSE){
					m_xcStaticString.ShowWindow(SW_HIDE);
				}else{
					m_xcStaticString.ShowWindow(SW_SHOW);
				}

				CString tempStatus;
				tempStatus.Format(_T("HTML �C���|�[�g ���s�� ( %I64u / %I64u ) ") , DoWithCnt,TotalItemsCount);					
				StatusStringSet(tempStatus,0,FALSE);
				UpdateData(FALSE);

			}
		}
			
	}


	if (inGeneratorVer == _T("<!---FLC Generator Version 1.5.5--->")){  //���X�V�� �G�N�X�|�[�g���Ȃ�  //�����l�� �\��

		while (!err) {
			if (ESCAPE_FLG == TRUE) break;

			if (stdFile.ReadString(rstr) == FALSE) err = 1;

			if (rstr!=_T("")){

				//CString tempStrForLen;
	 			LONG stepIDX;
				int CurrentStepCheck[11];
		    
				for(stepIDX = 0;stepIDX<=10; stepIDX++){
					CurrentStepCheck[stepIDX] = 0;
				}

        
	            
				//rstr = _
				//Replace(rstr, "<", "��")
	                
				//rstr = _
				//Replace(rstr, ">", "��")
	    
				//rstr.Replace(_T("&lt;"), _T("<"));
				//rstr.Replace(_T("&gt;"), _T(">"));
				//rstr.Replace(_T("&quot;"), _T("\""));
	   // 
				rstr.Replace(_T("&nbsp;"), _T(" "));
				//rstr.Replace(_T("&copy;"), _T("(c)"));
				//rstr.Replace(_T("&reg;"), _T("(r)"));

				////&apos; 
				//rstr.Replace(_T("&amp;"), _T("&"));//�Ō�ɒu��

				CString FullPath;

				BOOL RedFLG;
				BOOL BoldFLG;

				CString rstr2;

				LONG hiddenFullPathIDX1;
				LONG hiddenFullPathIDX2;

				LONG X;
				LONG myidx;
				LONG CurrentStep;
	                    
				LONG myidx2;
				//LONG DoWithCnt;

				BOOL ReadErrorFLG = FALSE;

				if ((rstr.Find(_T("<tr>"),0) == 0 ) && (rstr.Find(_T("</tr>"),0) >= (rstr.GetLength() - GetStrLen_Func(_T("</tr>"))))){ //Len("</tr>")=5){
					myidx2 = 0;
					CurrentStep = 1;
	                    
					X = 0;
	
					while (X <= rstr.GetLength()-1){
						MSG msg; //�ǉ� 2011.10.12

						if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
							if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
								if (msg.wParam == VK_ESCAPE){
									ESCAPE_FLG = TRUE;
									break; //�I���B���b�Z�[�W���[�v�𔲂���B
								}
							}
							TranslateMessage(&msg);
							DispatchMessage(&msg);
							//continue;
						}

						//MessageBox (rstr);
						if( CurrentStep== 1){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(GetStrLen_Func(_T("</td>")),X);

							//Call myActivateFunc(6 + MaxCnt)
							//�d���i���o�[
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%s"), _T(""));	//�ʂ��ԍ�
								lvi.iItem = CFileListCreatorDlg::m_xcList.GetItemCount();
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 0;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));	//�t�@�C���d�����ʃi���o�[

								index = CFileListCreatorDlg::m_xcList.InsertItem(&lvi); //err = 1;
							}

							//�ʂ��ԍ�
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%d"), index+1);	//�ʂ��ԍ�
								lvi.iItem = index;
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 1;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}
							CurrentStep = 2;
							//break;
						}else if( CurrentStep== 2){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);

							rstr2 = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>"))); //- GetStrLen_Func(_T("--->")
	                        
							//BOOL RedFLG;
							RedFLG = FALSE;
	                                
							CString RedTag1;

							RedTag1 = _T("<font color=\"red\">");
	                                
							CString  RedTag2;
							RedTag2 = _T("</font>");
	                                
							LONG RedIDX1;
							RedIDX1 = rstr.Find(RedTag1,myidx);
	                                
							LONG RedIDX2;
							RedIDX2 = rstr.Find(RedTag2,myidx);
	                            
							CString FormatDataStr;
							//FormatDataStr = _T("NORMAL,BLACK,");

							FormatDataStr = _T("BLACK,");

							if( RedIDX1 >= 0 && RedIDX2 >= 0){

								
								FormatDataStr = _T("RED,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());
								RedFLG = TRUE;
							}else{
								CString FormatDataStr;
								FormatDataStr = _T("BLACK,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
							}
	                                
							//CString FullPath;
	                        
							//LONG hiddenFullPathIDX1;
							//LONG hiddenFullPathIDX2;
	                                    
							hiddenFullPathIDX1 = rstr.Find(_T("<!---"),0);
							X = hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")+1);//+1
							hiddenFullPathIDX2 = rstr.Find(_T("--->"),X);
	                                    
							if (hiddenFullPathIDX1 >= 0 && hiddenFullPathIDX2 >= 0 ){

	  
								FullPath = rstr.Mid( hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")), hiddenFullPathIDX2 - hiddenFullPathIDX1 - GetStrLen_Func(_T("<!---")));
	                                                                                                                     
							}else{

							}
	                                    
							//BOOL BoldFLG;
							BoldFLG = FALSE;
	                                    
							LONG BoldIDX;
							BoldIDX = rstr2.Find(_T("<b>"), 0);
	                                   
							LONG BoldIDX2;
							BoldIDX2 = rstr2.Find(_T("</b>"),BoldIDX + GetStrLen_Func(_T("<b>")));
	                                    
							if (BoldIDX >= 0 && BoldIDX2 >= 0) {
	                                        
								rstr2 = rstr2.Mid(BoldIDX + GetStrLen_Func(_T("<b>")), BoldIDX2 - BoldIDX - GetStrLen_Func(_T("<b>")));                           
								FormatDataStr = _T("BOLD,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								//rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());

								BoldFLG = TRUE;

							}else{
								FormatDataStr = _T("NORMAL,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
								BoldFLG = FALSE;
							}

							// �t���p�X
							if (!err)
							{
								//lvi.mask = LVIF_TEXT;
								//lvi.lParam = m_id++;        // ID
								lvi.iItem = index;
								lvi.iSubItem = 2;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPath));
								//MessageBox (FullPath);
								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}	                                            
	                                            
							if(BoldFLG == TRUE ||  RedFLG == TRUE){
								// �t�@�C����
								if (!err)
								{									
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}
							}else{
								CString temp;
								temp = rstr2.Left(rstr2.Find(_T("<!---"),0));
								//MessageBox (temp);
								// �t�@�C����
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
								}
	                                        
								if( BoldFLG == TRUE ||  RedFLG == TRUE ){
									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}else{
									CString temp;
									temp =rstr2.Left(rstr2.Find(_T("<!---"),0));

									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}
							}
							X = hiddenFullPathIDX2 + GetStrLen_Func(_T("--->")) + GetStrLen_Func(_T("</td>"));


							CurrentStep = 3;

							//break;
						}else if( CurrentStep== 3){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);
	                    
							CString tempSize;
							if( myidx >= 0 && myidx2 >= 0 ){
								tempSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
							}else{
								tempSize = "";
							}
	                                
							LONG SizeNumIDX1;
							LONG SizeNumIDX2;
	                                
							SizeNumIDX1 = tempSize.Find(_T("<!---"),0);
							X = SizeNumIDX1 + GetStrLen_Func(_T("<!---"));
							SizeNumIDX2 = tempSize.Find(_T("--->"),X);

							
							CString myFileSize;

							if( SizeNumIDX1 >= 0 && SizeNumIDX2 >= 0 ) {


								myFileSize = tempSize.Mid(SizeNumIDX1 +GetStrLen_Func(_T("<!---")), SizeNumIDX2 - SizeNumIDX1 - GetStrLen_Func(_T("<!---")));

								
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 5;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}


								myFileSize = tempSize.Mid( 0, SizeNumIDX1);

								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}else{
								myFileSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}

							X = myidx + SizeNumIDX2 + GetStrLen_Func(_T("--->"));
	                                       
							CurrentStep = 4;
							//break;
						}else if( CurrentStep== 4){

			                if(X >= 1){
			                    X = X - 1;
			                }

							CurrentStep = 5;
							//break; 
						}else if( CurrentStep== 5){
								
			          		myidx = rstr.Find(_T("<td>"),X);
			                X = myidx + GetStrLen_Func(_T("<td>"));
			                myidx2 = rstr.Find(_T("</td>"),X);

		                    CString tempStr ;
			                    
			                if ( myidx >= 0 && myidx2 >= 0 ){
			                    tempStr = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
			                }else{
			                    tempStr = _T("");
							}

			                if ( myidx >= 0 && myidx2 >= 0 ){
								//���l��
								if (!err)
								{	
									if(tempStr == _T("   ")){
										tempStr = _T("");
									}
									lvi.iItem = index;
									lvi.iSubItem = 8;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}			                                   

		
			                }

			                X = myidx2 + GetStrLen_Func(_T("</td>"));  // X = myidx + myidx2 + GetStrLen_Func(_T("--->")); //�ύX 2012.07.11

							CurrentStep = 6;
							//break; 
						}else if( CurrentStep== 6){
							//MaxCnt = MaxCnt + 1
							DoWithCnt = DoWithCnt + 1;
							CFileListCreatorDlg::ItemCount_Func(TRUE);
							CurrentStep = 7;
							//break;
						}else if( CurrentStep== 7){
							int stepIDX;
							for( stepIDX = 0; stepIDX <= 10; stepIDX++){
								CurrentStepCheck[stepIDX] = 0;
							}

							//X=rstr.GetLength();

							CurrentStep =1;//
							break;
							//goto label;
							
						}else{
							X = X + 1;
							//MessageBox (_T("1111111"));
							//break;
						}
						UpdateData(FALSE);
						CurrentStepCheck[CurrentStep] = CurrentStepCheck[CurrentStep] + 1;
	                        
						if( CurrentStepCheck[CurrentStep] >=2){
							ReadErrorFLG = TRUE;
							break;
						}
					}
				}

				CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE);
				UpdateWindow();

				if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1 || MiniWindowFLG == FALSE){
					m_xcStaticString.ShowWindow(SW_HIDE);
				}else{
					m_xcStaticString.ShowWindow(SW_SHOW);
				}

				CString tempStatus;
				tempStatus.Format(_T("HTML �C���|�[�g ���s�� ( %I64u / %I64u ) ") , DoWithCnt,TotalItemsCount);					
				StatusStringSet(tempStatus,0,FALSE);
				UpdateData(FALSE);

			}
		}
			
	}


	if (inGeneratorVer == _T("<!---FLC Generator Version 1.5.6--->")){  //���X�V�� �G�N�X�|�[�g���Ȃ�  //�����l�� ��\��

		while (!err) {
			if (ESCAPE_FLG == TRUE) break;

			if (stdFile.ReadString(rstr) == FALSE) err = 1;

			if (rstr!=_T("")){

				//CString tempStrForLen;
	 			LONG stepIDX;
				int CurrentStepCheck[11];
		    
				for(stepIDX = 0;stepIDX<=10; stepIDX++){
					CurrentStepCheck[stepIDX] = 0;
				}

        
	            
				//rstr = _
				//Replace(rstr, "<", "��")
	                
				//rstr = _
				//Replace(rstr, ">", "��")
	    
				//rstr.Replace(_T("&lt;"), _T("<"));
				//rstr.Replace(_T("&gt;"), _T(">"));
				//rstr.Replace(_T("&quot;"), _T("\""));
	   // 
				rstr.Replace(_T("&nbsp;"), _T(" "));
				//rstr.Replace(_T("&copy;"), _T("(c)"));
				//rstr.Replace(_T("&reg;"), _T("(r)"));

				////&apos; 
				//rstr.Replace(_T("&amp;"), _T("&"));//�Ō�ɒu��

				CString FullPath;

				BOOL RedFLG;
				BOOL BoldFLG;

				CString rstr2;

				LONG hiddenFullPathIDX1;
				LONG hiddenFullPathIDX2;

				LONG X;
				LONG myidx;
				LONG CurrentStep;
	                    
				LONG myidx2;
				//LONG DoWithCnt;

				BOOL ReadErrorFLG = FALSE;

				if ((rstr.Find(_T("<tr>"),0) == 0 ) && (rstr.Find(_T("</tr>"),0) >= (rstr.GetLength() - GetStrLen_Func(_T("</tr>"))))){ //Len("</tr>")=5){
					myidx2 = 0;
					CurrentStep = 1;
	                    
					X = 0;
	
					while (X <= rstr.GetLength()-1){
						MSG msg; //�ǉ� 2011.10.12

						if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
							if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
								if (msg.wParam == VK_ESCAPE){
									ESCAPE_FLG = TRUE;
									break; //�I���B���b�Z�[�W���[�v�𔲂���B
								}
							}
							TranslateMessage(&msg);
							DispatchMessage(&msg);
							//continue;
						}

						//MessageBox (rstr);
						if( CurrentStep== 1){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(GetStrLen_Func(_T("</td>")),X);

							//Call myActivateFunc(6 + MaxCnt)
							//�d���i���o�[
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%s"), _T(""));	//�ʂ��ԍ�
								lvi.iItem = CFileListCreatorDlg::m_xcList.GetItemCount();
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 0;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));	//�t�@�C���d�����ʃi���o�[

								index = CFileListCreatorDlg::m_xcList.InsertItem(&lvi); //err = 1;
							}

							//�ʂ��ԍ�
							if (!err)
							{
								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								str.Format(_T("%d"), index+1);	//�ʂ��ԍ�
								lvi.iItem = index;
								//lvi.lParam = m_id++;        // ID
								lvi.iSubItem = 1;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}
							CurrentStep = 2;
							//break;
						}else if( CurrentStep== 2){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);

							rstr2 = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>"))); //- GetStrLen_Func(_T("--->")
	                        
							//BOOL RedFLG;
							RedFLG = FALSE;
	                                
							CString RedTag1;

							RedTag1 = _T("<font color=\"red\">");
	                                
							CString  RedTag2;
							RedTag2 = _T("</font>");
	                                
							LONG RedIDX1;
							RedIDX1 = rstr.Find(RedTag1,myidx);
	                                
							LONG RedIDX2;
							RedIDX2 = rstr.Find(RedTag2,myidx);
	                            
							CString FormatDataStr;
							//FormatDataStr = _T("NORMAL,BLACK,");

							FormatDataStr = _T("BLACK,");

							if( RedIDX1 >= 0 && RedIDX2 >= 0){

								
								FormatDataStr = _T("RED,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());
								RedFLG = TRUE;
							}else{
								CString FormatDataStr;
								FormatDataStr = _T("BLACK,");
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
							}
	                                
							//CString FullPath;
	                        
							//LONG hiddenFullPathIDX1;
							//LONG hiddenFullPathIDX2;
	                                    
							hiddenFullPathIDX1 = rstr.Find(_T("<!---"),0);
							X = hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")+1);//+1
							hiddenFullPathIDX2 = rstr.Find(_T("--->"),X);
	                                    
							if (hiddenFullPathIDX1 >= 0 && hiddenFullPathIDX2 >= 0 ){

	  
								FullPath = rstr.Mid( hiddenFullPathIDX1 + GetStrLen_Func(_T("<!---")), hiddenFullPathIDX2 - hiddenFullPathIDX1 - GetStrLen_Func(_T("<!---")));
	                                                                                                                     
							}else{

							}
	                                    
							//BOOL BoldFLG;
							BoldFLG = FALSE;
	                                    
							LONG BoldIDX;
							BoldIDX = rstr2.Find(_T("<b>"), 0);
	                                   
							LONG BoldIDX2;
							BoldIDX2 = rstr2.Find(_T("</b>"),BoldIDX + GetStrLen_Func(_T("<b>")));
	                                    
							if (BoldIDX >= 0 && BoldIDX2 >= 0) {
	                                        
								rstr2 = rstr2.Mid(BoldIDX + GetStrLen_Func(_T("<b>")), BoldIDX2 - BoldIDX - GetStrLen_Func(_T("<b>")));                           
								FormatDataStr = _T("BOLD,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);

								//rstr2 = rstr.Mid( RedIDX1 + RedTag1.GetLength(), RedIDX2 - RedIDX1 - RedTag1.GetLength());

								BoldFLG = TRUE;

							}else{
								FormatDataStr = _T("NORMAL,") + FormatDataStr;
								lvi.iItem = index;
								lvi.iSubItem = 9;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

								CFileListCreatorDlg::m_xcList.SetItem(&lvi);

								UpdateData(FALSE);
								BoldFLG = FALSE;
							}


							// �t���p�X
							if (!err)
							{
								//lvi.mask = LVIF_TEXT;
								//lvi.lParam = m_id++;        // ID
								lvi.iItem = index;
								lvi.iSubItem = 2;
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPath));
								//MessageBox (FullPath);
								CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
							}	                                            
	                                            
							if(BoldFLG == TRUE ||  RedFLG == TRUE){
								// �t�@�C����
								if (!err)
								{									
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}
							}else{
								CString temp;
								temp = rstr2.Left(rstr2.Find(_T("<!---"),0));
								//MessageBox (temp);
								// �t�@�C����
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 3;			
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;
								}
	                                        
								if( BoldFLG == TRUE ||  RedFLG == TRUE ){
									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(rstr2));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}else{
									CString temp;
									temp =rstr2.Left(rstr2.Find(_T("<!---"),0));

									// �t�@�C����
									if (!err)
									{
										lvi.iItem = index;
										lvi.iSubItem = 3;			
										lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(temp));

										CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
									}
								}
							}
							X = hiddenFullPathIDX2 + GetStrLen_Func(_T("--->")) + GetStrLen_Func(_T("</td>"));


							CurrentStep = 3;

							//break;
						}else if( CurrentStep== 3){
							myidx = rstr.Find(_T("<td>"),X);
							X = myidx + GetStrLen_Func(_T("<td>"));
							myidx2 = rstr.Find(_T("</td>"),X);
	                    
							CString tempSize;
							if( myidx >= 0 && myidx2 >= 0 ){
								tempSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
							}else{
								tempSize = "";
							}
	                                
							LONG SizeNumIDX1;
							LONG SizeNumIDX2;
	                                
							SizeNumIDX1 = tempSize.Find(_T("<!---"),0);
							X = SizeNumIDX1 + GetStrLen_Func(_T("<!---"));
							SizeNumIDX2 = tempSize.Find(_T("--->"),X);

						
							CString myFileSize;

							if( SizeNumIDX1 >= 0 && SizeNumIDX2 >= 0 ) {


								myFileSize = tempSize.Mid(SizeNumIDX1 +GetStrLen_Func(_T("<!---")), SizeNumIDX2 - SizeNumIDX1 - GetStrLen_Func(_T("<!---")));

								
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 5;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}


								myFileSize = tempSize.Mid( 0, SizeNumIDX1);

								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}else{
								myFileSize = rstr.Mid(myidx + GetStrLen_Func(_T("<td>")), myidx2 - myidx - GetStrLen_Func(_T("<td>")));
								// �t�@�C���T�C�Y
								if (!err)
								{
									lvi.iItem = index;
									lvi.iSubItem = 4;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}	
							}

							X = myidx + SizeNumIDX2 + GetStrLen_Func(_T("--->"));
	                                       
							CurrentStep = 4;
							//break;
						}else if( CurrentStep== 4){

			                if(X >= 1){
			                    X = X - 1;
			                }

							CurrentStep = 5;
							//break; 
						}else if( CurrentStep== 5){
			                if(X >= 1){
			                    X = X - 1;
			                }								

			                LONG RemarksIDX1;
			                LONG RemarksIDX2;
			                                
			                RemarksIDX1 = rstr.Find(_T("<!---") ,X);
			                X = RemarksIDX1 + GetStrLen_Func(_T("<!---"));
			                RemarksIDX2 = rstr.Find(_T("--->") ,X);


			                if(RemarksIDX1 >= 0 && RemarksIDX2 >= 0 ){
								CString tempStr;

								tempStr = rstr.Mid(RemarksIDX1 + GetStrLen_Func(_T("<!---")),RemarksIDX2 - RemarksIDX1 - GetStrLen_Func(_T("<!---")));
								//���l��
								if (!err)
								{	
									if(tempStr == _T("   ")){
										tempStr = _T("");
									}
									lvi.iItem = index;
									lvi.iSubItem = 8;
									lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempStr));
									CFileListCreatorDlg::m_xcList.SetItem(&lvi); //err = 1;			
								}			                                   

		
			                }

							X = RemarksIDX2 + GetStrLen_Func(_T("--->")); //X = myidx + RemarksIDX2 + GetStrLen_Func(_T("--->")); //�ύX 2012.07.11

							CurrentStep = 6;
							//break; 
						}else if( CurrentStep== 6){
							//MaxCnt = MaxCnt + 1
							DoWithCnt = DoWithCnt + 1;
							CFileListCreatorDlg::ItemCount_Func(TRUE);
							CurrentStep = 7;
							//break;
						}else if( CurrentStep== 7){
							int stepIDX;
							for( stepIDX = 0; stepIDX <= 10; stepIDX++){
								CurrentStepCheck[stepIDX] = 0;
							}

							//X=rstr.GetLength();

							CurrentStep =1;//
							break;
							//goto label;
							
						}else{
							X = X + 1;
							//MessageBox (_T("1111111"));
							//break;
						}
						UpdateData(FALSE);
						CurrentStepCheck[CurrentStep] = CurrentStepCheck[CurrentStep] + 1;
	                        
						if( CurrentStepCheck[CurrentStep] >=2){
							ReadErrorFLG = TRUE;
							break;
						}
					}
				}

				CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE);
				UpdateWindow();

				if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1 || MiniWindowFLG == FALSE){
					m_xcStaticString.ShowWindow(SW_HIDE);
				}else{
					m_xcStaticString.ShowWindow(SW_SHOW);
				}

				CString tempStatus;
				tempStatus.Format(_T("HTML �C���|�[�g ���s�� ( %I64u / %I64u ) ") , DoWithCnt,TotalItemsCount);					
				StatusStringSet(tempStatus,0,FALSE);
				UpdateData(FALSE);

			}
		}
			
	}

	CFileListCreatorDlg::SetStrFormat_Func(); //�ǉ� 2012.06.01 //�d�v

	//CFileListCreatorDlg::Total_Bytes_Bold(); //�ǉ� 2012.07.11
	//CFileListCreatorDlg::Total_Bytes_Func(); //�ǉ� 2012.07.11
	//CFileListCreatorDlg::ItemCount_Func(FALSE); //�ǉ� 2012.07.11

	CFileListCreatorDlg::StrToTagSign();

	UpdateData(FALSE);

	 //(6)�N���[�Y(�����I)
	//fclose(fp);
	stdFile.Close();

	//stdFile.ReleaseBuffer(); //�ǉ� 2012.06.02 //�O�̂���

	_wsetlocale(LC_ALL, _T(""));
	return 1;
}


void CFileListCreatorDlg::importFileList(){
	ESCAPE_FLG = FALSE;

	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02


	StatusStringSet(_T("HTML �C���|�[�g��"),0,FALSE); //�ύX 2012.06.14
	CFileListCreatorDlg::GetStrFormat_Func();

	//if (AutoSaveFLG == FALSE ) 
	CString filter("List Files|*.htm; *.html||");
	CString         filePath, strBuf;
	POSITION        pos = NULL;

	POSITION		w_pos = NULL;

	StatusStringSet(_T("�C���|�[�g����t�@�C����I��ŉ����� (�����I����) "),0,TRUE);

	CFileDialog     selDlg(TRUE, NULL, NULL,	//http://q.hatena.ne.jp/1173014326 �V���[�g�J�b�g�t�@�C���̃����N��H��Ȃ��@OFN_NODEREFERENCELINKS
						OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_NODEREFERENCELINKS , filter);//OFN_NODEREFERENCELINKS �ǉ�
	int             err = 0, lbErr = 0;
    
	// �t�@�C�������X�g�p�������m��
	if (!err)
	{
		try
		{
			selDlg.GetOFN().lpstrFile = strBuf.GetBuffer(MAX_PATH *100);
			selDlg.GetOFN().nMaxFile = MAX_PATH *100;
		}
		catch (...) {err = 1;}
	}
	if (!err) if (selDlg.DoModal() != IDOK) err = 1;

	if(selDlg.GetStartPosition() !=NULL){
		w_pos = selDlg.GetStartPosition();
	}

	//ULONGLONG TotalItemsCount;
	TotalItemsCount = 0;
	DoWithCnt = 0;

	if (!err) if ((pos = selDlg.GetStartPosition()) == NULL) err = 1;
	if (!err)
	{
		
		while (pos)
		{
			filePath = selDlg.GetNextPathName(pos);
			if (!err)
			{	
				ULONGLONG tempCnt;

				tempCnt = CFileListCreatorDlg::FileListItemsCount(filePath);
				if(tempCnt == 0 ){
					//err = 1;
				}else{
					TotalItemsCount = TotalItemsCount + tempCnt;
				}

			}
			//if (err) break;
		}
		UpdateData(FALSE);
	}

	CFileListCreatorDlg::StatusStringSet(_T("HTML �C���|�[�g�ΏۃA�C�e�� �J�E���g�I��"),0,FALSE);
//--------------------------------------------------------------------------------------------

	CString str;
	str.Format(_T("%I64u �̃t�@�C��������܂���"),TotalItemsCount);

	//MessageBox (str);

    BOOL ReadErrorFLG = FALSE;
	DoWithCnt=0;

	if (!err) if ((pos = w_pos) == NULL) err = 1;
	if (!err)
	{
		
		while (pos)
		{
			filePath = selDlg.GetNextPathName(pos);
			if (!err)
			{	
				//lbErr = CFileListCreatorDlg::importFileList_Func(filePath);

				//MessageBox (filePath);
				int tempINT;
				tempINT = CFileListCreatorDlg::importFileList_Func(filePath,FALSE);
				if(tempINT == 0){
					//err = 1;
					ReadErrorFLG = TRUE;
				}

			}
			//if (err) break;
		}
		UpdateData(FALSE);
	}    
	//strBuf.ReleaseBuffer();//�R�����g�A�E�g//2011.05.31
    
    //If frmWizard1.cbAutoSort.Value = True Then
    //    Call Sort_Click
    //End If
   
    
    //CFileListCreatorDlg::StrToTagSign();

	CFileListCreatorDlg::Total_Bytes_Bold();
	CFileListCreatorDlg::Total_Bytes_Func();
	CFileListCreatorDlg::ItemCount_Func(FALSE);

	//CFileListCreatorDlg::SetStrFormat_Func(); //Func�̒���

	if( ReadErrorFLG == TRUE || TotalItemsCount == 0){
		if(AnyfileImport == FALSE){
			StatusStringSet(_T("�ꕔ�̃t�@�C�������X�g�t�@�C���łȂ��ׁA�ǂݍ��߂Ȃ������t�@�C��������܂�"),300,TRUE);
		}
	}else{
		StatusStringSet(_T("HTML �C���|�[�g ���������܂���"),300,TRUE);
	}

	if (TotalItemsCount>=1){
		ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

		CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

		if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
			strBuf.ReleaseBuffer(); //�ǉ� 2012.06.01 //�O�̂���
			DrawMenuBar();
			return;
		}

		if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
			m_Dlg->SetWindowText(_T("FileListCreator (*)"));
			SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24
		}
		
	}
//--------------------------------------------------------------------------------------------

	strBuf.ReleaseBuffer();
	DrawMenuBar();

    return;
}

////�u�����Ă��܂����H
CFileListCreatorDlg::CFileListCreatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileListCreatorDlg::IDD, pParent)
	, m_xvChkViewMode(FALSE)
	, m_xvStCount(_T(""))
	, m_xvChkSubFolder(TRUE)//��������
	, m_xvStatusString(_T(""))
	, m_xvTotal_Bytes(_T(""))
	, m_xvChkEasySelect(FALSE)
	, m_xvStrEasySelectMode(_T(""))
	, m_xvChkRedOnMode(FALSE) 
	, m_xvStrRedOnMode(_T(""))
	, m_xvChkAutoSave(FALSE)
	, m_xvEditItem(_T(""))
	, m_xvChkEditCellMode(FALSE)
	, m_xvStrEditCellMode(_T(""))
	, m_xvChkUseUNDO(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileListCreatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_xcList);
	DDX_Check(pDX, IDC_CHK_ViewMode, m_xvChkViewMode);
	DDX_Text(pDX, IDC_STATIC_ItemCnt, m_xvStCount);
	DDX_Check(pDX, IDC_CHK_Search_SubFolder, m_xvChkSubFolder);
	DDX_Text(pDX, IDC_STATIC_StatusString, m_xvStatusString);
	DDX_Text(pDX, IDC_STATIC_Total_Bytes, m_xvTotal_Bytes);
	DDX_Control(pDX, IDC_STATIC_DRAG_ON_ME, m_xcStaticString);
	DDX_Check(pDX, IDC_CHK_EasySelect, m_xvChkEasySelect);
	DDX_Text(pDX, IDC_STATIC_EasySelectMode, m_xvStrEasySelectMode);
	DDX_Check(pDX, IDC_CHK_RedOnMode, m_xvChkRedOnMode);//�ǉ�q
	DDX_Text(pDX, IDC_STATIC_RedOnMode, m_xvStrRedOnMode);//�ǉ�
	DDX_Check(pDX, IDC_CHK_AutoSave, m_xvChkAutoSave);
	DDX_Text(pDX, IDC_EDIT_Item, m_xvEditItem);
	DDX_Check(pDX, IDC_CHK_EditCellMode, m_xvChkEditCellMode);
	DDX_Text(pDX, IDC_STATIC_EditCellMode, m_xvStrEditCellMode);
	DDX_Check(pDX, IDC_CHK_UseUNDO, m_xvChkUseUNDO);
}

BEGIN_MESSAGE_MAP(CFileListCreatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_Import, &CFileListCreatorDlg::OnBnClickedBtnImport)
	//ON_BN_CLICKED(IDC_BTN_Export, &CFileListCreatorDlg::OnBnClickedBtnExport)
	ON_BN_CLICKED(IDC_BTN_Export, &CFileListCreatorDlg::OnBnClickedBtnExport)
	ON_BN_CLICKED(IDC_BTN_Test, &CFileListCreatorDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_CHK_ViewMode, &CFileListCreatorDlg::OnBnClickedChkViewmode)
	ON_BN_CLICKED(IDC_BTN_StepSearch, &CFileListCreatorDlg::OnBnClickedBtnStepsearch)
	ON_BN_CLICKED(IDC_BTN_Restore, &CFileListCreatorDlg::OnBnClickedBtnRestore)
	ON_BN_CLICKED(IDC_BTN_PackageSearch, &CFileListCreatorDlg::OnBnClickedBtnPackagesearch)
	ON_BN_CLICKED(IDC_CHK_Search_SubFolder, &CFileListCreatorDlg::OnBnClickedChkSearchSubfolder)
	ON_STN_CLICKED(IDC_STATIC_StatusString, &CFileListCreatorDlg::OnStnClickedStaticStatusstring)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &CFileListCreatorDlg::OnLvnItemchangedList)
	ON_BN_CLICKED(IDC_BTN_Sort, &CFileListCreatorDlg::OnBnClickedBtnSort)
//	ON_NOTIFY(NM_RDBLCLK, IDC_LIST, &CFileListCreatorDlg::OnNMRDblclkList)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, &CFileListCreatorDlg::OnNMRClickList)
	ON_COMMAND(ID_MENU_MyMessage, &CFileListCreatorDlg::OnMenuMymessage)
	ON_BN_CLICKED(IDC_BTN_Clear, &CFileListCreatorDlg::OnBnClickedBtnClear)
	ON_COMMAND(ID_MENU_Clear_Selected_Items, &CFileListCreatorDlg::OnMenuDeleteSelectedRows)
	ON_COMMAND(ID_FILE_IMPORT, &CFileListCreatorDlg::OnFileImport)
	ON_COMMAND(ID_FILE_EXPORT, &CFileListCreatorDlg::OnFileExport)
	ON_COMMAND(ID_SEARCH_PACKAGESEARCH, &CFileListCreatorDlg::OnSearchPackagesearch)
	ON_COMMAND(ID_SEARCH_STEPSEARCH, &CFileListCreatorDlg::OnSearchStepsearch)
	ON_COMMAND(ID_EDIT_RESTORE, &CFileListCreatorDlg::OnEditRestore)
	ON_COMMAND(ID_EDITLIST_SORT, &CFileListCreatorDlg::OnEditlistSort)
	ON_COMMAND(ID_Menu_DeleteRow, &CFileListCreatorDlg::OnMenuDeleterow)
	ON_COMMAND(ID_OPTION_MYMESSAGE, &CFileListCreatorDlg::OnOptionMymessage)
	ON_COMMAND(ID_FILE_QUIT, &CFileListCreatorDlg::OnFileQuit)
	ON_COMMAND(ID_MENU_OpenByExplorer, &CFileListCreatorDlg::OnMenuOpenbyexplorer)
	ON_COMMAND(ID_OPENBY_CONNECTEDAPPLICATION, &CFileListCreatorDlg::OnOpenbyConnectedapplication)
	ON_COMMAND(ID_OPEN_EXPLORER, &CFileListCreatorDlg::OnOpenExplorer)
	ON_COMMAND(ID_MENU_Play_Selected_Music, &CFileListCreatorDlg::OnMenuPlaySelectedMusic)
	ON_COMMAND(ID_OPENBY_MEDIAPLAYER, &CFileListCreatorDlg::OnOpenbyMediaplayer)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_MENU_SelectAll, &CFileListCreatorDlg::OnMenuSelectall)
	ON_COMMAND(ID_EDITLIST_SELECTALL, &CFileListCreatorDlg::OnEditlistSelectall)
	ON_COMMAND(ID_EDIT_DELFILETYPE, &CFileListCreatorDlg::OnEditDelfiletype)
	ON_COMMAND(ID_MENU_DEL_FileType, &CFileListCreatorDlg::OnMenuDelFiletype)
	ON_COMMAND(ID_MENU_Restore_List_Information, &CFileListCreatorDlg::OnMenuRestoreListInformation)
	ON_COMMAND(ID_EDITLIST_ADDDIRSTR, &CFileListCreatorDlg::OnEditlistAdddirstr)
	ON_COMMAND(ID_MENU_AddDirectorySTR, &CFileListCreatorDlg::OnMenuAdddirectorystr)
	ON_COMMAND(ID_OPTION_VERSION, &CFileListCreatorDlg::OnOptionVersion)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_SORT_SORTITEMSBYFILENAME, &CFileListCreatorDlg::OnSortSortitemsbyfilename)
	ON_COMMAND(ID_SORT_SORTITEMSBYDATASIZE, &CFileListCreatorDlg::OnSortSortitemsbydatasize)
	ON_COMMAND(ID_SORT_SORTITEMSBYDATE, &CFileListCreatorDlg::OnSortSortitemsbydate)
	ON_COMMAND(ID_SORT_SORTITEMSBYPATHNAME, &CFileListCreatorDlg::OnSortSortitemsbypathname)
	ON_COMMAND(ID_SORT_SORTITEMSBYREPETITIONNUM, &CFileListCreatorDlg::OnSortSortitemsbyrepetitionnum)
	ON_COMMAND(ID_EDITLIST_SET_SEQ_NO, &CFileListCreatorDlg::OnEditlistSetSequentialNum)
	ON_COMMAND(ID_OPENBY_LINKFILEOPEN, &CFileListCreatorDlg::OnOpenbyLinkfileopen)
	ON_BN_CLICKED(IDC_CHK_EasySelect, &CFileListCreatorDlg::OnBnClickedChkEasyselect)
	ON_COMMAND(ID_COPY_EASYSELECT, &CFileListCreatorDlg::OnCopyEasyselect)
	ON_COMMAND(ID_COPY_EASYSELECTOFF, &CFileListCreatorDlg::OnCopyEasyselectoff)
	ON_COMMAND(ID_MENU_EmphasisByBold, &CFileListCreatorDlg::OnMenuEmphasisbybold)
	ON_COMMAND(ID_MENU_Emphasized_Format_Cancellation, &CFileListCreatorDlg::OnMenuEmphasizedFormatCancellation)
	ON_COMMAND(ID_EDITSELECTEDITEM_BOLD, &CFileListCreatorDlg::OnEditselecteditemBold)
	ON_BN_CLICKED(IDC_CHK_RedOnMode, &CFileListCreatorDlg::OnBnClickedChkRedonmode)
	ON_COMMAND(ID_OPTION_TIPS, &CFileListCreatorDlg::OnOptionTips)
	ON_COMMAND(ID_MENU_EmphasisByRed, &CFileListCreatorDlg::OnMenuEmphasisbyred)
	ON_COMMAND(ID_EDITSELECTEDITEM_RED, &CFileListCreatorDlg::OnEditselecteditemRed)
	ON_COMMAND(ID_MENU_Expand_List_File, &CFileListCreatorDlg::OnMenuExpandListFile)
	ON_COMMAND(ID_MENU_Play_Emphasized_Music, &CFileListCreatorDlg::OnMenuPlayEmphasizedMusic)
	ON_COMMAND(ID_MENU_Exclude_NonEmphasized_Items, &CFileListCreatorDlg::OnMenuExcludeNonemphasizedItems)
	ON_COMMAND(ID_SORT_SORTITEMSBYSTRFORMAT, &CFileListCreatorDlg::OnSortSortitemsbystrformat)
	ON_COMMAND(ID_SORT_MERGE, &CFileListCreatorDlg::OnSortMerge)
	ON_COMMAND(ID_COPY_COPY, &CFileListCreatorDlg::OnCopyCopy)
	ON_COMMAND(ID_ITUNES_ALBUMLIST, &CFileListCreatorDlg::OnItunesAlbumlist)
	ON_COMMAND(ID_ITUNES_ADDARTISTSTR, &CFileListCreatorDlg::OnItunesAddartiststr)
	ON_COMMAND(ID_EDITLIST_REPLACE, &CFileListCreatorDlg::OnEditlistReplace)
	ON_COMMAND(ID_MENU_SelectAllCancellation, &CFileListCreatorDlg::OnMenuSelectallcancellation)
	ON_COMMAND(ID_FILTER_DATEFILTER, &CFileListCreatorDlg::OnFilterDatefilter)
	ON_BN_CLICKED(IDCANCEL, &CFileListCreatorDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHK_AutoSave, &CFileListCreatorDlg::OnBnClickedChkAutosave)
	ON_COMMAND(ID_AUTOSAVE_AUTOSAVEON, &CFileListCreatorDlg::OnAutosaveAutosaveon)
	ON_COMMAND(ID_AUTOSAVE_AUTOSAVEOFF, &CFileListCreatorDlg::OnAutosaveAutosaveoff)
	ON_BN_CLICKED(IDOK, &CFileListCreatorDlg::OnBnClickedOk)
	ON_COMMAND(ID_MENU_FILE_SAVE, &CFileListCreatorDlg::OnMenuFileSave)
	ON_COMMAND(ID_FILE_RECOVERY, &CFileListCreatorDlg::OnFileRecovery)
	ON_COMMAND(ID_MENU_FILE_PRINT, &CFileListCreatorDlg::OnMenuFilePrint)
	ON_COMMAND(ID_FILTER_KEYWORDS, &CFileListCreatorDlg::OnFilterKeywords)
	ON_BN_CLICKED(ID_BTN_NoSaveQuit, &CFileListCreatorDlg::OnBnClickedBtnNosavequit)
	ON_COMMAND(ID_OPTION_PreferenceFileClear, &CFileListCreatorDlg::OnOptionPreferencefileclear)
	ON_NOTIFY(NM_CLICK, IDC_LIST, &CFileListCreatorDlg::OnNMClickList)
	ON_BN_CLICKED(ID_BTN_Quit, &CFileListCreatorDlg::OnBnClickedBtnQuit)
	ON_EN_CHANGE(IDC_EDIT_Item, &CFileListCreatorDlg::OnEnChangeEditItem)
	ON_EN_KILLFOCUS(IDC_EDIT_Item, &CFileListCreatorDlg::OnEnKillfocusEditItem)
	ON_BN_CLICKED(IDC_CHK_EditCellMode, &CFileListCreatorDlg::OnBnClickedChkEditcellmode)
	ON_BN_CLICKED(ID_BTN_SetSEQ_NUM, &CFileListCreatorDlg::OnBnClickedBtnSetseqNum)
	ON_COMMAND(ID_MENU_Expand_MUSIC_List_File, &CFileListCreatorDlg::OnMenuExpandMusicListFile)
	ON_COMMAND(ID_REPEATEDITEMCHECK_BYDATASIZE, &CFileListCreatorDlg::OnRepeateditemcheckBydatasize)
	ON_COMMAND(ID_REPEATEDITEMCHECK_BYFILENAME, &CFileListCreatorDlg::OnRepeateditemcheckByfilename)
	ON_COMMAND(ID_REPEATEDITEMCHECK_BYDATE, &CFileListCreatorDlg::OnRepeateditemcheckBymodifytime)
	ON_COMMAND(ID_REPEATEDITEMCHECK_BYALLINFO, &CFileListCreatorDlg::OnRepeateditemcheckByallinfo)
	ON_BN_CLICKED(ID_BTN_CurrentDirectoryOpen, &CFileListCreatorDlg::OnBnClickedBtnCurrentdirectoryopen)
	ON_COMMAND(ID_OPTION_CURRENTDIRECTORYOPEN, &CFileListCreatorDlg::OnOptionCurrentdirectoryopen)
	ON_COMMAND(ID_EDITLIST_CLEARREPETITIONNUM, &CFileListCreatorDlg::OnEditlistClearrepetitionnum)
	ON_COMMAND(ID_EDITLIST_CLEARREMARKSCOLUMN, &CFileListCreatorDlg::OnEditlistClearremarkscolumn)
	ON_COMMAND(ID_LANGUAGE_JAPANESE, &CFileListCreatorDlg::OnLanguageJapanese)
	ON_COMMAND(ID_LANGUAGE_ENGLISH, &CFileListCreatorDlg::OnLanguageEnglish)
	ON_COMMAND(ID_OPENBY_VIRTUALBROWSER, &CFileListCreatorDlg::OnOpenbyVirtualbrowser)
	ON_COMMAND(ID_OPTION_FILEPATHLIMITCHECK, &CFileListCreatorDlg::OnOptionFilepathlimitcheck)
	ON_COMMAND(ID_EDITLIST_UNDO, &CFileListCreatorDlg::OnEditlistUndo)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST, &CFileListCreatorDlg::OnLvnDeleteitemList)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST, &CFileListCreatorDlg::OnLvnItemchangingList)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST, &CFileListCreatorDlg::OnLvnColumnclickList)
	ON_NOTIFY(LVN_INSERTITEM, IDC_LIST, &CFileListCreatorDlg::OnLvnInsertitemList)
	ON_NOTIFY(LVN_DELETEALLITEMS, IDC_LIST, &CFileListCreatorDlg::OnLvnDeleteallitemsList)
	ON_BN_CLICKED(ID_BTN_CellSizeFix, &CFileListCreatorDlg::OnBnClickedBtnCellsizefix)
	ON_COMMAND(ID_Menu_SetClipboardText, &CFileListCreatorDlg::OnMenuSetclipboardtext)
	ON_COMMAND(ID_Menu_GetClipboardText, &CFileListCreatorDlg::OnMenuGetclipboardtext)
	ON_COMMAND(ID_Menu_DeleteCell, &CFileListCreatorDlg::OnMenuDeletecell)
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_BTN_MiniWindow, &CFileListCreatorDlg::OnBnClickedBtnMiniwindow)
	ON_BN_CLICKED(ID_BTN_RedrawWindow, &CFileListCreatorDlg::OnBnClickedBtnRedrawwindow)
	ON_BN_CLICKED(IDC_CHK_UseUNDO, &CFileListCreatorDlg::OnBnClickedChkUseundo)
//	ON_NOTIFY(LVN_ENDSCROLL, IDC_LIST, &CFileListCreatorDlg::OnLvnEndScrollList)
ON_COMMAND(ID_MENU_Cancel, &CFileListCreatorDlg::OnMenuCancel)
END_MESSAGE_MAP()

///*
BOOL CFileListCreatorDlg::OnInitDialog()
{
    
	//CDialogEx::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	ShowWindow(SWP_SHOWWINDOW);// SW_MINIMIZE �� SWP_SHOWWINDOW �ɕς���

	CDialogEx::OnInitDialog();

    // TODO: �������������ɒǉ����܂�



	UNDO_FLG = TRUE;

	ShellExecuteOpenFLG = FALSE;

	ListInsertItemFLG = FALSE; //TRUE�̎��̓X�N���[�����ARedrawWindow();���Ȃ�

	//UseUNDO_FLG = TRUE;
	//m_xvChkUseUNDO = TRUE;

	//CString myStr = _T("Test");
    {
        int        err = 0;

        if (!err) err = ListInit();        // ���X�g�R���g���[��������

		CellSizeFixMode = _T("Init");
		CFileListCreatorDlg::OnBnClickedBtnCellsizefix();

		//if (!err) err = CFileListCreatorDlg::ListInsertItem(myStr);  // ���X�g�A�C�e���}��
    }
	
	::GetWindowRect( m_hWnd, &initWindowSize );
	this->ScreenToClient( &initWindowSize );

	::GetWindowRect( m_hWnd, &initWindowSize2 );
	//this->ScreenToClient( &initWindowSize2 ); //�ϊ����Ȃ�

	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_STATIC_DRAG_ON_ME ), &rectSTATIC_DRAG_ON_ME ); //�ǉ� 2012.07.02
	this->ScreenToClient( &rectSTATIC_DRAG_ON_ME );

	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_LIST ), &initListSize );
	this->ScreenToClient( &initListSize );

	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_BTN_Import ), &rectBTN_Import );
	this->ScreenToClient( &rectBTN_Import );

	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_BTN_Export ), &rectBTN_Export );
	this->ScreenToClient( &rectBTN_Export );

	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_BTN_Restore ), &rectBTN_Restore );
	this->ScreenToClient( &rectBTN_Restore );

	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_BTN_Sort ), &rectBTN_Sort );
	this->ScreenToClient( &rectBTN_Sort );


	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_BTN_PackageSearch ), &rectBTN_PackageSearch );
	this->ScreenToClient( &rectBTN_PackageSearch );

	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_BTN_StepSearch ), &rectBTN_StepSearch );
	this->ScreenToClient( &rectBTN_StepSearch );

	::GetWindowRect( ::GetDlgItem( m_hWnd, ID_BTN_CurrentDirectoryOpen ), &rectBTN_CurrentDirectoryOpen );
	this->ScreenToClient( &rectBTN_CurrentDirectoryOpen );


	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_BTN_Clear ), &rectBTN_Clear );
	this->ScreenToClient( &rectBTN_Clear );


	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_CHK_RedOnMode ), &rectCHK_RedOnMode );
	this->ScreenToClient( &rectCHK_RedOnMode );

	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_CHK_EasySelect ), &rectCHK_EasySelect );
	this->ScreenToClient( &rectCHK_EasySelect );

	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_CHK_EditCellMode ), &rectCHK_EditCellMode );
	this->ScreenToClient( &rectCHK_EditCellMode );


	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_STATIC_RedOnMode ), &rectSTATIC_RedOnMode );
	this->ScreenToClient( &rectSTATIC_RedOnMode );

	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_STATIC_EasySelectMode ), &rectSTATIC_EasySelectMode );
	this->ScreenToClient( &rectSTATIC_EasySelectMode );

	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_STATIC_EditCellMode ), &rectSTATIC_EditCellMode );
	this->ScreenToClient( &rectSTATIC_EditCellMode );


	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_STATIC_RedOnModeFrame ), &rectSTATIC_RedOnModeFrame );
	this->ScreenToClient( &rectSTATIC_RedOnModeFrame );

	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_STATIC_EasySelectFrame ), &rectSTATIC_EasySelectFrame );
	this->ScreenToClient( &rectSTATIC_EasySelectFrame );

	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_STATIC_EditCellModeFrame ), &rectSTATIC_EditCellModeFrame );
	this->ScreenToClient( &rectSTATIC_EditCellModeFrame );


	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_CHK_Search_SubFolder ), &rectCHK_Search_SubFolder );
	this->ScreenToClient( &rectCHK_Search_SubFolder );

	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_CHK_AutoSave ), &rectCHK_AutoSave );
	this->ScreenToClient( &rectCHK_AutoSave );

	::GetWindowRect( ::GetDlgItem( m_hWnd, ID_BTN_CellSizeFix ), &rectBTN_CellSizeFix );
	this->ScreenToClient( &rectBTN_CellSizeFix );


	::GetWindowRect( ::GetDlgItem( m_hWnd, ID_BTN_SetSEQ_NUM ), &rectBTN_SetSEQ_NUM );
	this->ScreenToClient( &rectBTN_SetSEQ_NUM );

	::GetWindowRect( ::GetDlgItem( m_hWnd, ID_BTN_NoSaveQuit ), &rectBTN_NoSaveQuit );
	this->ScreenToClient( &rectBTN_NoSaveQuit );

	::GetWindowRect( ::GetDlgItem( m_hWnd, ID_BTN_Quit ), &rectBTN_Quit );
	this->ScreenToClient( &rectBTN_Quit );

	::GetWindowRect( ::GetDlgItem( m_hWnd, ID_BTN_RedrawWindow ), &rectBTN_RedrawWindow );
	this->ScreenToClient( &rectBTN_RedrawWindow );


	::GetWindowRect( ::GetDlgItem( m_hWnd, ID_BTN_MiniWindow ), &rectBTN_MiniWindow );
	this->ScreenToClient( &rectBTN_MiniWindow );

	MiniWindowFLG = TRUE;

	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_CHK_UseUNDO ), &rectCHK_UseUNDO );
	this->ScreenToClient( &rectCHK_UseUNDO );

	ListDataNoChange_FLG = TRUE; //�ǉ� 2012.05.13 //AutoImportFileList()�ŏ�����
	//AfxGetMainWnd()->SetWindowText(_T("FileListCreator")); //�ǉ� 2012.05.13

	//http://atashi.net/inu/ja/notes/stl_vector_sort.html

	PrevListPtr = new ListItemStruct;
	NowListPtr = new ListItemStruct;
	WorkListPtr = new ListItemStruct;


	m_xvChkViewMode = FALSE;
	m_xvChkSubFolder = TRUE;
	
	m_xvChkEasySelect = FALSE;
	//m_xvStrEasySelectMode = _T("");
	UpdateData(FALSE);

	m_xvChkRedOnMode = FALSE;
	//m_xvStrRedOnMode = _T("");
	UpdateData(FALSE);


	m_xvChkEditCellMode = FALSE;
	UpdateData(FALSE);

	g_RadioModifyDate=1;
	g_RadioRemarksColumn=2;
	g_ChkCopyOn=TRUE;
	g_ChkRedOn=TRUE;

	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	//BoldAndRedInversion = FALSE;

	LastSelectedRow = -1;
	LastSelectedColumn = -1;
	//NotInversion = FALSE; //TRUE�̎��t�@�C�����E���l���̕ҏW���́A�i���������ԕ����́j���]���Ȃ�

	//ListDBLCLK_FLG = FALSE;
	SelectALLFLG  = FALSE;  //���ׂĂ�I������Ƃ��͍Œ���̏����̂ݍs��

	g_NoDrawFLG = FALSE; //TRUE�̎��A���X�g��`�悵�Ȃ�

	BoldByteSum = 0;
	BolditemCount = 0;

	//MessageBox(((CFileListCreatorApp*)AfxGetApp())->m_lpCmdLine);
	//
	//((CFileListCreatorApp*)AfxGetApp())->m_lpCmdLine;
	
	AnyfileImport = FALSE;

	AutoSaveMode_ReadOrWrite_Func(_T("read"));
	UseUNDO_Mode_ReadOrWrite_Func(_T("read"));

	AutoImportFileList();

	SetStrFormat_Func();

	LastImportFileName = _T("");

	CString TempStr;
	CString FileName;

	FileName =_T("");
	int i=0;

	BOOL QuotStartFLG = FALSE;

	int StartIDX = 0;
	int EndIDX = 0;

	BOOL SpaceStartFLG = FALSE;

	//BOOL FirstFLG = TRUE;
	TempStr = ((CFileListCreatorApp*)AfxGetApp())->m_lpCmdLine;
	//MessageBox(TempStr);


	DoWithCnt = 0;
	TotalItemsCount = 0;


	importFileResult = IDNO;
	SkipFLG = FALSE;

	//m_xcStaticString.ShowWindow(SW_SHOW);
	//UpdateData(FALSE);
	//UpdateWindow();

	//CFileListCreatorDlg *m_ShowDlg;
	//m_ShowDlg->Create(IDD_FILELISTCREATOR_DIALOG, NULL );

	//HWND SetActiveWindow(HWND hWnd);

	int myResult;
	CFileSpecsDlg m_dlg;
	
	if(TempStr!=_T("")){
		myResult = IDNO;
		myResult = MessageBox(_T("�A�C�e�� (�t�H���_��t�@�C��) ���h���b�v����܂����B�t�H���_�ɑ΂��Ă̓����I�����ĉ������B\r\n\r\n�u�͂��v�t�@�C���̎�ނȂǂōi�荞�݂܂��B\r\n�u�������v�h���b�v���ꂽ�t�H���_�̒��g�����ׂă��X�g�Ɏ�荞�݂܂��B") ,_T("��荞�݊m�F"), MB_YESNOCANCEL );

		int importFileResult = IDNO;
		SkipFLG = FALSE;

		if(myResult	== IDYES){
			//���[�_��
			m_dlg.DoModal();
			if(m_dlg.TargetFileSpecs == _T("")){
				CFileListCreatorDlg::StatusStringSet(_T("FileSpecsDlg : ���[�U�[�ɂ��L�����Z��"),300,TRUE);
				return FALSE;
			}

			if(m_dlg.TargetFileSpecs == _T("<<error>>")){
				CFileListCreatorDlg::StatusStringSet(_T("FileSpecsDlg : �������`���Ō����Ώۂ��w�肵�Ă�������"),300,TRUE);
				return FALSE;
			}
		}
	}
	while (i<=TempStr.GetLength()-1){
		//TempStr = ((CFileListCreatorApp*)AfxGetApp())->m_lpCmdLine;

		MSG msg; //�ǉ� 2011.10.12
		if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
			if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
				if (msg.wParam == VK_ESCAPE){
					ESCAPE_FLG = TRUE;
					break; //�I���B���b�Z�[�W���[�v�𔲂���B
				}
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			//continue;
		}

		if (TempStr.Mid(i,1) == _T("\"")){
			if(QuotStartFLG == FALSE){
				QuotStartFLG  = TRUE;
				StartIDX = i;

			}else if (QuotStartFLG == TRUE){
				QuotStartFLG = FALSE;
				EndIDX = i;

				FileName = TempStr.Mid(StartIDX+1,EndIDX-StartIDX-1);
				i++;

				if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE)== 1 && SkipFLG == FALSE){
					importFileResult = MessageBox(_T("�������̃��X�g�t�@�C�������o����܂����B�C���|�[�g���s���A���X�g��W�J���܂����H"),_T("�C���|�[�g�m�F"), MB_YESNOCANCEL );
					//if ( importFileResult == IDYES ){
					//	MessageBox(_T("�������烊�X�g��W�J���܂��B\r\n�uOK�v�������āA���΂炭���҂��������B"),_T("��荞�݊J�n"), MB_OK );
					//}			
					SkipFLG = TRUE;
				}

				//if ( importFileResult == IDYES ){
				//	CFileListCreatorDlg::importFileList_Func(FileName,FALSE);
				//}

				//if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE) == 0 ||importFileResult !=IDYES ){
				//	CFileListCreatorDlg::PackageSearch_Func(FileName,_T("*.*;")); //; ��Y�ꂸ��
				//}
		

				if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE) == 1 && importFileResult == IDYES) {
					CFileListCreatorDlg::importFileList_Func(FileName,FALSE);
				}else if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE) == 0 && myResult == IDYES){
					CFileListCreatorDlg::PackageSearch_Func(FileName,m_dlg.TargetFileSpecs);
				}else if (importFileResult !=IDYES ){
					CFileListCreatorDlg::PackageSearch_Func(FileName,_T("*.*;"));  //; ��Y�ꂸ��
				}

				CFileListCreatorDlg::ItemCount_Func(TRUE);
			}
		}

		if(QuotStartFLG == FALSE){
			if(SpaceStartFLG == FALSE && TempStr.Mid(i,1) != _T(" ")){
				SpaceStartFLG  = TRUE;
				StartIDX = i;
			}else if ((TempStr.Find(_T(" "),0) == NULL  || i ==TempStr.GetLength()-1 )){
				EndIDX = i;				
				FileName = TempStr.Mid(StartIDX,EndIDX-StartIDX + 1);

				if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE)== 1 && SkipFLG == FALSE){
					importFileResult = MessageBox(_T("�������̃��X�g�t�@�C�������o����܂����B�C���|�[�g���s���A���X�g��W�J���܂����H"),_T("�C���|�[�g�m�F"), MB_YESNOCANCEL );
/*					if ( importFileResult == IDYES ){
						MessageBox(_T("�������烊�X�g��W�J���܂��B\r\n�uOK�v�������āA���΂炭���҂��������B"),_T("��荞�݊J�n"), MB_OK );
					}	*/					
					SkipFLG = TRUE;
				}

				if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE) == 1 && importFileResult == IDYES) {
					CFileListCreatorDlg::importFileList_Func(FileName,FALSE);
				}else if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE) == 0 && myResult == IDYES){
					CFileListCreatorDlg::PackageSearch_Func(FileName,m_dlg.TargetFileSpecs);
				}else if (importFileResult !=IDYES ){
					CFileListCreatorDlg::PackageSearch_Func(FileName,_T("*.*;"));  //; ��Y�ꂸ��
				}

				CFileListCreatorDlg::ItemCount_Func(TRUE);
				break;
			}else if ((TempStr.Mid(i,1) == _T(" ") || i ==TempStr.GetLength()-1 ) && ( SpaceStartFLG == TRUE )){
				SpaceStartFLG = FALSE;
				EndIDX = i;
				
				FileName = TempStr.Mid(StartIDX,EndIDX-StartIDX);

				if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE)== 1 && SkipFLG == FALSE){
					importFileResult = MessageBox(_T("�������̃��X�g�t�@�C�������o����܂����B�C���|�[�g���s���A���X�g��W�J���܂����H"),_T("�C���|�[�g�m�F"), MB_YESNOCANCEL );
/*					if ( importFileResult == IDYES ){
						MessageBox(_T("�������烊�X�g��W�J���܂��B\r\n�uOK�v�������āA���΂炭���҂��������B"),_T("��荞�݊J�n"), MB_OK );
					}		*/				
					SkipFLG = TRUE;
				}

				if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE) == 1 && importFileResult == IDYES) {
					CFileListCreatorDlg::importFileList_Func(FileName,FALSE);
				}else if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE) == 0 && myResult == IDYES){
					CFileListCreatorDlg::PackageSearch_Func(FileName,m_dlg.TargetFileSpecs);
				}else if (importFileResult !=IDYES ){
					CFileListCreatorDlg::PackageSearch_Func(FileName,_T("*.*;"));  //; ��Y�ꂸ��
				}
				CFileListCreatorDlg::ItemCount_Func(TRUE);
			}
		}
		i++;
	}

	if (TempStr !=_T("")){
		CFileListCreatorDlg::StatusStringSet(_T("�A�C�e�����������܂���"),300,TRUE);
		CFileListCreatorDlg::SetStrFormat_Func();
		//CFileListCreatorDlg::Total_Bytes_Func();

		ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13
		AfxGetMainWnd()->SetWindowText(_T("FileListCreator (*)")); //�ǉ� 2012.05.13

	}

	//if ((CFileListCreatorApp*)AfxGetApp())->m_lpCmdLine)

	//LastPrevItemCount  = CFileListCreatorDlg::m_xcList.GetItemCount();

	CFileListCreatorDlg::Total_Bytes_Bold();
	CFileListCreatorDlg::Total_Bytes_Func();
	CFileListCreatorDlg::ItemCount_Func(FALSE);

	SelectedLanguage = _T("Japanese");

	CFileListCreatorDlg::OnLanguageJapanese();

	DragAcceptFiles();//Drag & Drop����
	UpdateData(FALSE);

	//CFileListCreatorDlg::m_color = RGB(220, 220, 220);
	//Invalidate();

	//SetTextColor(m_xcStaticString,m_color);
	//CFileListCreatorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//CFileListCreatorDlg::OnCtlColor(NULL,m_xcStaticString,m_color);

    return TRUE;
}
//*/

void CFileListCreatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CFileListCreatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	//UpdateWindow();
}


// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CFileListCreatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// ���X�g�R���g���[��������
int CFileListCreatorDlg::ListInit(void)
{
    LVCOLUMN    lvc;//�ύX2011.05.13
    int         i;
    //TCHAR       caption[][32] = {_T("���i"), _T("�P��"), _T("��")};
	TCHAR		caption[][32] = {_T("�d��No."), _T("No."), _T("�t�@�C���p�X"), _T("�t�@�C����"),_T("�o�C�g"), _T("���o�C�g"),_T("�C����"),_T("�C������"),_T("���l��"),_T("�������")};
    const int   clmNum = sizeof caption /sizeof caption[0];
    int         err = 0;


	BoldByteSum = 0;
	BolditemCount = 0;

    //m_xcList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	
	//m_xcList.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT |
    //LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);

	m_xcList.SetExtendedStyle( LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT |
    LVS_EX_GRIDLINES); //LVS_EX_CHECKBOXES | //�R�����g�� 2012.05.19

    lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;    // �L���t���O
    for (i = 0; i < clmNum; i++)
    {
        lvc.iSubItem    = i;            // �T�u�A�C�e���ԍ�
        lvc.pszText     = caption[i];   // ���o���e�L�X�g
		switch(i){
			case 0:
				lvc.cx          = 80;          // ����
				break;
			case 1:
				lvc.cx          = 80;          // ����
				break;
			case 2:
				lvc.cx          = 0;          // ����
				break;
			case 3:
				lvc.cx          = 470;          // ����
				break;
			case 4:
				lvc.cx          = 80;          // ����
				break;
			case 5:
				lvc.cx          = 0;          // ����
				break;
			case 6:
				lvc.cx          = 110;          // ����
				break;
			case 7:
				lvc.cx          = 0;          // ����
				break;
			case 8:
				lvc.cx          = 110;          // ����
				break;
			case 9:
				lvc.cx          = 0;          // ����
				break;
			default:
				MessageBox(_T("�s���ȗ�ł��B"));
				break;
			
		}
        if (m_xcList.InsertColumn(i, &lvc) == -1) {err = 1; break;}

    }
	//m_xcList.SetItemData(nItem,11);
	
	CFileListCreatorDlg::ItemCount_Func(TRUE);

    return err;
}

//InsertString


// ���X�g�A�C�e���}��
int CFileListCreatorDlg::ListInsertItem(CString FullPathString)
{	
	ListInsertItemFLG = TRUE; //TRUE�̎��̓X�N���[�����ARedrawWindow();���Ȃ�

	//LVITEM       lvi;
	int          i, index = 0;
	int          err = 0;
	CString      str;	

	if(FullPathString==_T("Test")){
		return 1;

		struct
		{
			TCHAR	RepetitionNum[30];	//�t�@�C���d�����ʃi���o�[
			int		Num;		//�ʂ��ԍ�
			TCHAR	FullPath[256];	//�t�@�C���p�X
			TCHAR	FileName[256];	//�t�@�C����
			TCHAR	ApproximateByte[50];	//�����悻�̃f�[�^�T�C�Y//�o�C�g
			long	AccurateByte;		//���ۂ̃f�[�^�T�C�Y//���o�C�g
			TCHAR	ModifyDate[20];		//�C����
			//CTime	ModifyTime;		//�C������
			TCHAR	ModifyTime[20];		//�C������
			TCHAR	RemarksColumn[100];		//���l��
		} item[] = 
		{
			{_T(""),1,_T("H:\\_iTunes Music_�y�ۊǌɁz\\_Tunes Music (192kbps)\\_SINGLE (192kbps MP3)\\20th Century - 01 �I������Ȃ���A�L�~����Ȃ���.mp3"),_T(""),_T("6MB"),6297985,_T("2009/4/1"),_T("2009/4/1  1:05:18")},
			{_T(""),2,_T("D:\\_iTunes Music_�y�ۊǌɁz\\_Tunes Music (192kbps)\\_SINGLE (192kbps MP3)\\AAA - 01 Heart and Soul.mp3"),_T("AAA - 01 Heart and Soul.mp3"),_T(""),6351340,_T("2010/2/25"),_T("2010/2/25  15:08:13")},
			{_T(""),3,_T("D:\\_iTunes Music_�y�ۊǌɁz\\_Tunes Music (192kbps)\\_SINGLE (192kbps MP3)\\AAA - 01 MIRAGE.mp3"),_T("AAA - 01 MIRAGE.mp3"),_T("4MB"), 4663519,_T(""),_T("2009/4/1  1:05:50")},
		};
		//int          err = 0;
		
		const int    itemNum = sizeof item /sizeof item[0];

		//MessageBox(itemNum);

		for (i = 0; i < itemNum; i++)
		{
			lvi.mask = LVIF_TEXT; //���K�v  // | LVCF_SUBITEM�����Ă͂Ȃ�Ȃ� //�d�v 2012.05.31

			if (!err)
			{
				//lvi.mask = LVIF_TEXT | LVIF_PARAM;
				lvi.iItem = i;
				lvi.iSubItem = 0;
				lvi.pszText = item[i].RepetitionNum;	//�t�@�C���d�����ʃi���o�[
				//if ((index = CFileListCreatorDlg::m_xcList.InsertItem(&lvi)) == -1) err = 1;
			}
	
			if (!err)
			{
				//lvi.mask = LVIF_TEXT | LVIF_PARAM;
				str.Format(_T("%d"), item[i].Num);	//�ʂ��ԍ�
				lvi.iItem = index;
				lvi.iSubItem = 1;
				lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));
				if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
			}
			

           
			if (!err)
			{
				//lvi.mask = LVIF_TEXT | LVIF_PARAM;
            	lvi.iItem = index;
	 			lvi.iSubItem = 2;
            	lvi.pszText = item[i].FullPath;	//�t�@�C���p�X
            	if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
			}

			if (!err)
			{
				//lvi.mask = LVIF_TEXT | LVIF_PARAM;
            	lvi.iItem = index;
	 			lvi.iSubItem = 3;
            	lvi.pszText = item[i].FileName;	//�t�@�C����
            	if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
			}

			if (!err)
			{
				//lvi.mask = LVIF_TEXT | LVIF_PARAM;
            	lvi.iItem = index;
	 			lvi.iSubItem = 4;
            	lvi.pszText = item[i].ApproximateByte;	//�����悻�̃f�[�^�T�C�Y
            	if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
			}

			if (!err)
			{
				//lvi.mask = LVIF_TEXT | LVIF_PARAM;
            	lvi.iItem = index;
				lvi.iSubItem = 5;
				str.Format(_T("%d"), item[i].AccurateByte);	//���ۂ̃f�[�^�T�C�Y
				lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));
				if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
			}

			if (!err)
			{
				//lvi.mask = LVIF_TEXT | LVIF_PARAM;
            	lvi.iItem = index;
	 			lvi.iSubItem = 6;
            	lvi.pszText = item[i].ModifyDate;		//�C����
            	if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
			}

			if (!err)
			{
				//lvi.mask = LVIF_TEXT | LVIF_PARAM;
            	lvi.iItem = index;
	 			lvi.iSubItem =7;
            	lvi.pszText = item[i].ModifyTime;		//�C������
            	if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
			}

			if (!err)
			{
				//lvi.mask = LVIF_TEXT | LVIF_PARAM;
            	lvi.iItem = index;
	 			lvi.iSubItem =8;
            	lvi.pszText = item[i].RemarksColumn;		//���l��
            	if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
			}
			//MessageBox(_T("IN-LOOP"));
			if (err) break;
		}
	}else{
		//LVITEM        lvi;
		//int           index;
		//int           err = 0;

		UpdateData();
		lvi.mask = LVIF_TEXT; // | LVCF_SUBITEM�����Ă͂Ȃ�Ȃ� //�d�v 2012.05.31

		//�d���i���o�[
		if (!err)
		{
			//lvi.mask = LVIF_TEXT | LVIF_PARAM;
			str.Format(_T("%s"), _T(""));	//�ʂ��ԍ�
			lvi.iItem = CFileListCreatorDlg::m_xcList.GetItemCount();
			//lvi.lParam = m_id++;        // ID
			lvi.iSubItem = 0;
			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));	//�t�@�C���d�����ʃi���o�[

			if ((index = CFileListCreatorDlg::m_xcList.InsertItem(&lvi)) == -1) err = 1;
		}

		//�ʂ��ԍ�
		if (!err)
		{
			//lvi.mask = LVIF_TEXT | LVIF_PARAM;
			str.Format(_T("%d"), index+1);	//�ʂ��ԍ�
			lvi.iItem = index;
			//lvi.lParam = m_id++;        // ID
			lvi.iSubItem = 1;
			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));

			if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
		}

		BOOL LengthOver = FALSE;

		// �t���p�X
		if (!err)
		{
			//lvi.mask = LVIF_TEXT;
			//lvi.lParam = m_id++;        // ID
			lvi.iItem = index;
			lvi.iSubItem = 2;

			if (FullPathString.GetLength() > 260){
				FullPathString = FullPathString.Left(260); //�ǉ� 2013.02.08
				LengthOver = TRUE;
			}

			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPathString));

			if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
		}

		CString myFileName;
		CString myFileSize;
		ULONGLONG myLongFileSize;
		CString myDate;

		CString tempDate;	

		myFileName="";
		myFileSize = "";
		myLongFileSize = 0;
		myDate = "";


		CTime cTime;

		if (LengthOver == FALSE){  //�ǉ� 2013.02.08
			CFile* pFile = NULL;
			// Constructing a CFile object with this override may throw
			// a CFile exception, and won't throw any other exceptions.
			// Calling CString::Format() may throw a CMemoryException,
			// so we have a catch block for such exceptions, too. Any
			// other exception types this function throws will be
			// routed to the calling function.

			try
			{
				//CFile pfile;

				// try to open the file
				CFile pFile(FullPathString, CFile::modeRead  | CFile::shareDenyNone);

				ULONGLONG dwLength = pFile.GetLength();
				myLongFileSize = dwLength;
				myFileSize.Format(_T("%I64u"), dwLength);

				myFileName = pFile.GetFileName();
				//myFileName = FullPathToFileName(FullPathString);
				CFileStatus status;

				if(pFile.GetStatus(status))    // virtual member function
				{
				   //TRACE(_T("�C���� = %s\n"), status.m_mtime);
				   //MessageBox(status.m_mtime);
				
					//http://msdn.microsoft.com/ja-jp/library/29btb3sw.aspx //�͈͊O�̎��A�u�p�����[�^���Ԉ���Ă��܂��B�v�Ƃ����G���[�𓊂���
					cTime = status.m_mtime;
					myDate = cTime.Format(_T("%Y/%m/%d %H:%M:%S")); //Format(tdate, "yyyy/mm/dd")
														//Format(tdate, "yyyy/mm/dd hh:mm:ss")
					tempDate = myDate;
				
				}	
				//AfxMessageBox(myFileSize);

				//// print out path name and title information
				//_tprintf_s(_T("Path is : \"%s\"\n"),
					//(LPCTSTR) myFile.GetFilePath());
				//_tprintf_s(_T("Name is : \"%s\"\n"),
					//(LPCTSTR) myFile.GetFileName());
				//_tprintf_s(_T("Title is: \"%s\"\n"), 
					//(LPCTSTR) myFile.GetFileTitle());

				//MessageBox(myFile.GetFileName());
			 
				// close the file handle
				pFile.Close();
			}
			catch (CFileException* pEx)
			{
				// if an error occurs, just make a message box

				//pEx->ReportError();  //�A���[�g�͏o���Ȃ�
				pEx->Delete();
				myFileName ="";
				myFileSize = "";
				myLongFileSize = 0;

			   // We can't recover from this memory exception, so we'll
			   // just terminate the app without any cleanup. Normally,
			   // an application should do everything it possibly can to
			   // clean up properly and _not_ call AfxAbort().
			   ////AfxAbort();
			}

			// If an exception occurs in the CFile constructor,
			// the language will free the memory allocated by new
			// and will not complete the assignment to pFile.
			// Thus, our clean-up code needs to test for NULL.
			if (pFile != NULL)
			{
			   pFile->Close();
			   delete pFile;
			} 
		}

		//if (FullPathString.Right(1)==_T("\\")){
		//	myFileName = FullPathString.Left(FullPathString.GetLength()-2);
		//	myFileName.Mid(myFileName.ReverseFind(_T('\\'))+1);
		//}

		// �t�@�C����
		if (!err)
		{
			lvi.iItem = index;
			lvi.iSubItem = 3;			
			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileName));

		//lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPathToFileName(FullPathString);
			if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;			
		}

		// �����悻�̃t�@�C���T�C�Y
		if (!err)
		{
			lvi.iItem = index;
			lvi.iSubItem = 4;
			CString tempSize;//�Ȃ����ϐ����͂��ނƏ�肭����

			//TRACE(_T("!!!!%I64u\n"),myLongFileSize);

			tempSize = ByteCalculation(myLongFileSize,FALSE);
			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempSize));
			//MessageBox(ByteCalculation(myLongFileSize));
		//lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPathToFileName(FullPathString);
			if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;			
		}

		// �t�@�C���T�C�Y
		if (!err)
		{
			lvi.iItem = index;
			lvi.iSubItem = 5;
			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

		//lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPathToFileName(FullPathString);
			if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;			
		}
		//MessageBox(_T("IN-LOOP"));

		//�C����
		tempDate = cTime.Format(_T("%Y/%m/%d"));
		if (!err)
		{
			lvi.iItem = index;
			lvi.iSubItem = 6;
			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempDate));
			//MessageBox(ByteCalculation(myLongFileSize));
		//lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPathToFileName(FullPathString);
			if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;			
		}

		//�C������
		tempDate = cTime.Format(_T("%Y/%m/%d %H:%M:%S"));
		if (!err)
		{
			lvi.iItem = index;
			lvi.iSubItem = 7;
			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempDate));
			//MessageBox(ByteCalculation(myLongFileSize));
		//lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPathToFileName(FullPathString);
			if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;			
		}

		//http://oshiete.goo.ne.jp/qa/1638451.html

		//setlocale( LC_CTYPE, "jpn" );

		wchar_t wbuf[1024];
		char buf[1024];
		int buflen;
		lstrcpyW(wbuf,const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPathString)));
		buflen = WideCharToMultiByte(CP_ACP,0,wbuf,-1,buf,0,NULL,NULL);
		WideCharToMultiByte(CP_ACP,0,(LPCWSTR)wbuf,-1,buf,buflen,NULL,NULL);

		int nLen = strlen(buf);

		//http://www.c-lang.net/functions/mblen.html

		//int nLen = FullPathString.GetLength() * sizeof(TCHAR);

		//http://www.kab-studio.biz/Programing/Codian/MxA/09.html

		//http://oshiete.goo.ne.jp/qa/7150644.html
		if (nLen>255){
			if (!err)
			{
				CString str;

				str.Format(_T("%d �o�C�g"),nLen);

				//lvi.mask = LVIF_TEXT | LVIF_PARAM;
				lvi.iItem = index;
	 			lvi.iSubItem =8;
				//lvi.pszText = _T("�[������p�X");		//���l��
				lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("�[������p�X")));		//���l��
				if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
			}
		}

		//delete[] lpsz;

		CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE);
		UpdateWindow();

		m_xcList.SetItemData(index,11);

		if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1 || MiniWindowFLG == FALSE){
			m_xcStaticString.ShowWindow(SW_HIDE);
		}else{
			m_xcStaticString.ShowWindow(SW_SHOW);
		}

		CFileListCreatorDlg::ItemCount_Func(TRUE);
	}

	//UpdateData(true);


	CFileListCreatorDlg::ItemCount_Func(TRUE);


	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return 0;
	}

	if (ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
		//SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24
	}

	ListInsertItemFLG = FALSE; //TRUE�̎��̓X�N���[�����ARedrawWindow();���Ȃ�

	return err;
}

void CFileListCreatorDlg::OnBnClickedBtnImport()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	//MessageBox(_T("Import��������܂����B"));
	CFileListCreatorDlg::importFileList();
}

void CFileListCreatorDlg::OnBnClickedBtnExport()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		StatusStringSet(_T("Export ���s��"),0,FALSE); //�ύX 2012.06.14

		HTML_Dlg m_dlg;
	
		if(m_dlg.DoModal()==IDOK){
			//CFileListCreatorDlg::SelectALL_CancellationFunc(); //�R�����g�� 2012.06.01

			//g_NoDrawFLG = TRUE;
			CFileListCreatorDlg::ExportFileList(FALSE);
			//g_NoDrawFLG = FALSE;
		}else{
			CFileListCreatorDlg::StatusStringSet(_T("Export �L�����Z��"),0,TRUE);
			//g_NoDrawFLG = FALSE;
		}

		delete m_dlg;
	}
}


void CFileListCreatorDlg::OnBnClickedBtnTest()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	//MessageBox(_T("Test��������܂����B"));

	if(CFileListCreatorDlg::myIsDigit_Func(_T("1"))==TRUE){
		MessageBox( _T("���l�ł�"));
	}else{
		MessageBox( _T("�����������Ă��܂�"));
	}

	CFileListCreatorDlg::Total_Bytes_Bold();
	CFileListCreatorDlg::Total_Bytes_Func();
	CFileListCreatorDlg::ItemCount_Func(TRUE);

	//UpdateData(FALSE);

	//LPDRAWITEMSTRUCT lpDrawItemStruct;

	//CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	//CFont *pFont = pDC->GetCurrentFont();

	//CMylistCtrl MyList_CLASS;

	////http://msdn.microsoft.com/ja-jp/library/zhcs623h.aspx
	//if (NULL != MyList_CLASS.pFont)
	//{
	//	LOGFONT lf;
	//	MyList_CLASS.pFont->GetLogFont(&lf);
	//	//TRACE(_T("Typeface name of font = %s\n"), lf.lfFaceName);
	//	if(lf.lfWeight == FW_BOLD){
	//		MessageBox(_T("�������ł�"));
	//	}	
	//
	//}

	//if(m_xcList.GetItemData(1)== (FW_BOLD + RGB(0,0,0))){
	//	MessageBox(_T("�����������ł�"));
	//}	

	CFileListCreatorDlg::GetStrFormat_Func();


	//http://www.geocities.jp/ky_webid/win32c/021.html
	//http://oshiete.goo.ne.jp/qa/4165655.html
	// http://oshiete.goo.ne.jp/qa/5746038.html
	// ���X�g�R���g���[����FONT���擾 VC++ MFC�@-VB -.Net "LogFont"
	// ���X�g�R���g���[���� �t�H���g���擾 VC++ MFC�@-VB -.Net


	return;
}

void CFileListCreatorDlg::OnBnClickedChkViewmode()
{
	//UpdateData();
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	if (m_xvChkViewMode){
		LVCOLUMN    lvc;
		int         i;
		//TCHAR		caption[][32] = {_T("�d��No."), _T("No."), _T("�t�@�C���p�X"), _T("�t�@�C����"),_T("�o�C�g"), _T("���o�C�g"),_T("�C����"),_T("�C������")};
		//const int   clmNum = sizeof caption /sizeof caption[0];
		int         err = 0;

		//m_xcList.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT |
		//LVS_EX_GRIDLINES);

		lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;    // �L���t���O
		for (i = 0; i < 9; i++)
		{
			lvc.iSubItem    = i;            // �T�u�A�C�e���ԍ�
			//lvc.pszText     = caption[i];   // ���o���e�L�X�g
			switch(i){
				case 0:
				case 1:
					lvc.cx          = 80;          // ����
					break;
				case 2:
					lvc.cx          = 500;          // ����
					break;
				case 3:
					lvc.cx          = 0;          // ����
					break;
				case 4:
					lvc.cx          = 80;          // ����
					break;
				case 5:
					lvc.cx          = 0;          // ����
					break;
				case 6:
					lvc.cx          = 70;          // ����
					break;
				case 7:
					lvc.cx          = 0;          // ����
					break;
				case 8:
					lvc.cx          = 80;          // ����
					break;
				case 9:
					lvc.cx          = 0;          // ����
					break;
				default:
					MessageBox(_T("�s���ȗ�ł��B"));
					break;
			
			}
			//if (m_xcList.InsertColumn(i, &lvc) == -1) {err = 1; break;}
			//MessageBox(_T("SizeChange"));
		}
		UpdateData();
	}
}


void CFileListCreatorDlg::OnBnClickedBtnStepsearch()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	//.Visible = FALSE;

	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	ESCAPE_FLG = FALSE;

	TotalItemsCount = 0; //�ǉ� 2012.04.07
	DoWithCnt = 0; //�ǉ� 2012.04.07
	SkipFLG = FALSE; //�ǉ� 2012.04.07

	importFileResult = IDNO; //�ǉ� 2012.04.07


	StatusStringSet(_T("StepSearch ���s��"),0,FALSE); //�ύX 2012.06.14

	CString filter("ALL Files |*.*|Audio Files|*.mp3; *.wma; *.m4a|Document Files|*.xls; *.doc; *.ppt|Image Files|*.jpg; *.jpeg; *.gif; *.png; *.bmp|Movie Files|*.mpg; *.mpeg; *.asf; *.avi; *.mov; *.wmv; *.flv|Text Files|*.txt; *.text|HTML Files|*.html; *.htm|PlayLIST Files|*.m3u; *.wpl||");
	CString         filePath, strBuf;
	POSITION        pos = NULL;
	CFileDialog     selDlg(TRUE, NULL, NULL,	//http://q.hatena.ne.jp/1173014326 �V���[�g�J�b�g�t�@�C���̃����N��H��Ȃ��@OFN_NODEREFERENCELINKS
						OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_NODEREFERENCELINKS , filter);//OFN_NODEREFERENCELINKS �ǉ�
	int             err = 0, lbErr = 0;
    
	// �t�@�C�������X�g�p�������m��
	if (!err)
	{
		try
		{
			selDlg.GetOFN().lpstrFile = strBuf.GetBuffer(MAX_PATH *100);
			selDlg.GetOFN().nMaxFile = MAX_PATH *100;
		}
		catch (...) {err = 1;}
	}

	//�� ���X�g�t�@�C���W�J�� �A�C�e�����J�E���g�� ��

	if (!err) if (selDlg.DoModal() != IDOK) err = 1;
	if (!err) if ((pos = selDlg.GetStartPosition()) == NULL) err = 1;
	if (!err)
	{


		while (pos)
		{
			MSG msg; //�ǉ� 2011.10.12
			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			//MessageBox();
			filePath = selDlg.GetNextPathName(pos);
			if (!err)
			{	
				if (CFileListCreatorDlg::importFileList_Func(filePath,TRUE)== 1 && SkipFLG == FALSE){
					importFileResult = MessageBox(_T("�������̃��X�g�t�@�C�������o����܂����B�C���|�[�g���s���A���X�g��W�J���܂����H"),_T("�C���|�[�g�m�F"), MB_YESNOCANCEL );
					SkipFLG = TRUE;
				}

				//lbErr = CFileListCreatorDlg::ListInsertItem(filePath);
				//if (lbErr == LB_ERR || lbErr == LB_ERRSPACE) err = 1;

				if(CFileListCreatorDlg::importFileList_Func(filePath,TRUE) == 1){		
					ULONGLONG tempCnt;

					tempCnt = CFileListCreatorDlg::FileListItemsCount(filePath);
					if( tempCnt == 0 ){
						//TotalItemsCount ++;
					}else{
						TotalItemsCount = TotalItemsCount + tempCnt;
					}
				}
			}
			if (err) break;
		}
		UpdateData(FALSE);
	}

	//�����X�g�t�@�C���W�J�� �A�C�e�����J�E���g�� ��

	
	BOOL CntFLG = FALSE;

	//�����X�g�t�@�C���W�J �� �A�C�e���ǉ� �� ��	//�ǉ� 2012.04.07

	pos = selDlg.GetStartPosition(); //�ēx������
	
	//if (!err) if (selDlg.DoModal() != IDOK) err = 1; //�ǉ� 2012.12.01

	if (!err) if ((pos = selDlg.GetStartPosition()) == NULL) err = 1;
	if (!err)
	{
		while (pos)
		{
			MSG msg; //�ǉ� 2011.10.12
			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			//MessageBox();
			filePath = selDlg.GetNextPathName(pos);
			if (!err)
			{	


				if (importFileResult == IDYES){
					if (CFileListCreatorDlg::importFileList_Func(filePath,TRUE) == 1){
						CFileListCreatorDlg::importFileList_Func(filePath,FALSE);
						CntFLG = TRUE;
					}
					if (CFileListCreatorDlg::importFileList_Func(filePath,TRUE) == 0){
						lbErr = CFileListCreatorDlg::ListInsertItem(filePath);
						CntFLG = TRUE;
					}
				}

				if(importFileResult !=IDYES){
					lbErr = CFileListCreatorDlg::ListInsertItem(filePath);
					CntFLG = TRUE;
				}
				if (lbErr == LB_ERR || lbErr == LB_ERRSPACE) err = 1;

			}
			if (err) break;
		}
		UpdateData(FALSE);
	}

	//�� ���X�g�t�@�C���W�J �� �A�C�e���ǉ� �� ��	//�ǉ� 2012.04.07

	if (!err) if ((pos = selDlg.GetStartPosition()) == NULL) err = 1; //�ǉ� 2012.12.01

	if (CntFLG == TRUE && err != 1){
		ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

		CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

		if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
			return;
		}

		if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
			m_Dlg->SetWindowText(_T("FileListCreator (*)"));
			SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24
		}
	}

	strBuf.ReleaseBuffer();

	CFileListCreatorDlg::StatusStringSet(_T("StepSearch �I��"),300,TRUE);

	//CFileListCreatorDlg::Total_Bytes_Func();//�ǉ� 2011.10.13

	CFileListCreatorDlg::Total_Bytes_Bold(); //�ǉ� 2012.07.11
	CFileListCreatorDlg::Total_Bytes_Func(); //�ǉ� 2012.07.11
	CFileListCreatorDlg::ItemCount_Func(FALSE); //�ǉ� 2012.07.11

	DrawMenuBar();
    return;

}

void CFileListCreatorDlg::RestoreFunc(int index){
	//�y��Łz�t�@�C�������݂��邩�H���m���߂�B

	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

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

	lvi.mask = LVIF_TEXT;// | LVIF_PARAM;

	//�d���i���o�[
	if (!err)
	{
		//lvi.mask = LVIF_TEXT | LVIF_PARAM;
		str.Format(_T("%s"), _T(""));	//�ʂ��ԍ�
		lvi.iItem = index;
		//lvi.lParam = m_id++;        // ID
		lvi.iSubItem = 0;
		lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));	//�t�@�C���d�����ʃi���o�[

		if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
	}

	//�ʂ��ԍ�
	if (!err)
	{
		//lvi.mask = LVIF_TEXT | LVIF_PARAM;
		str.Format(_T("%d"), index+1);	//�ʂ��ԍ�
		lvi.iItem = index;
		//lvi.lParam = m_id++;        // ID
		lvi.iSubItem = 1;
		lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));

		if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
	}
	// �t���p�X
	if (!err)
	{

		FullPathString =CFileListCreatorDlg::m_xcList.GetItemText(index,2);
		if (FullPathString !=_T("")){
			FullPathString.Replace(_T("%"),_T("%%"));
		}
		//if(FullPathString ==_T("")){
		//myFileName = FullPathToFileName(FullPathString);
		//}
		//TRACE(FullPathString);
		//if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
	}


	if(FullPathString.Right(1)!=_T("\\")){
	//// �t�@�C����
	//if (!err)
	//{
	//	lvi.iItem = index;
	//	lvi.iSubItem = 3;			
	//	lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPathToFileName(FullPathString)));
	//	//if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;			
	//}

		// �t�@�C���T�C�Y
		if (!err)
		{
			myLongFileSize = CStringToLong(CFileListCreatorDlg::m_xcList.GetItemText(index, 5));
			//if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;			
		}

		CTime cTime;
		CFile* pFile = NULL;
		CString workDate;

		if(FullPathString != _T("")){
			myFileName = FullPathToFileName(FullPathString);
			myFileName.Replace(_T("%%"),_T("%"));
		}

		workDate = CFileListCreatorDlg::m_xcList.GetItemText(index, 7);
		if(workDate != _T("")){
			COleDateTime pd;
			//char * p = tempDate;
			if( pd.ParseDateTime( workDate ))
			{
				myDate = pd.Format(_T("%Y/%m/%d"));
			//cTime = pd;

				myTime = pd.Format(_T("%Y/%m/%d %H:%M:%S")); //Format(tdate, "yyyy/mm/dd")
											//Format(tdate, "yyyy/mm/dd hh:mm:ss")
			//tempDate = myDate;
			}
			else
			{
				TRACE("��͕s�\\n");
			}
		}
		myFileSize.Format(_T("%I64u"), CFileListCreatorDlg::m_xcList.GetItemText(index, 5));
		

		try
		{
			CFile pFile(FullPathString, CFile::modeRead  | CFile::shareDenyNone);

			ULONGLONG dwLength = pFile.GetLength();
			//if (myLongFileSize==-1){
				myLongFileSize = dwLength;
				myFileSize.Format(_T("%I64u"), dwLength);
			//}else{
			//	myFileSize.Format(_T("%I64u"), myLongFileSize);
			//}


			//if(FullPathString == _T("")){
				myFileName = pFile.GetFileName();
			//}else{
			//	myFileName = FullPathToFileName(FullPathString);
			//}

			CFileStatus status;

			if(pFile.GetStatus(status))    // virtual member function
			{
				//TRACE(_T("�C���� = %s\n"), status.m_mtime);
				//MessageBox(status.m_mtime);

				//�C������
				if (!err)
				{
					workDate = CFileListCreatorDlg::m_xcList.GetItemText(index, 7);
					if(workDate == _T("")) {
						cTime = status.m_mtime;
						myDate = cTime.Format(_T("%Y/%m/%d")); //Format(tdate, "yyyy/mm/dd")
						myTime = cTime.Format(_T("%Y/%m/%d %H:%M:%S"));						//Format(tdate, "yyyy/mm/dd hh:mm:ss")
						//tempDate = myDate;
					}else{
						//http://homepage1.nifty.com/MADIA/vc/vc_bbs/200412/200412_04120032.html
						  
							COleDateTime pd;
							//char * p = tempDate;
							if( pd.ParseDateTime( workDate ))
							{
							myDate = pd.Format(_T("%Y/%m/%d"));
							//cTime = pd;

							myTime = pd.Format(_T("%Y/%m/%d %H:%M:%S")); //Format(tdate, "yyyy/mm/dd")
															//Format(tdate, "yyyy/mm/dd hh:mm:ss")
							//tempDate = myDate;
							}
							else
							{
							TRACE("��͕s�\\n");
							}

						//cTime =  pd.Format(_T("%Y/%m/%d %H:%M:%S"));
					}

					//if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;			
				}

			}	
			//workDate == _T("");
			pFile.Close();
		}
		catch (CFileException* pEx)
		{
			//pEx->ReportError();
			pEx->Delete();

			//myFileName =_T("");
			//myFileSize = _T("");
			//myLongFileSize = -1;
			//workDate == _T("");

			////if( FullPathString != _T("")){
			//	myFileName = FullPathToFileName(FullPathString);
			//	workDate = CFileListCreatorDlg::m_xcList.GetItemText(index, 7);
			//	COleDateTime pd;
			//	// HTTP �̃w�b�_�����������t������B
			//	//char * p = tempDate;
			//	if( pd.ParseDateTime( workDate ))
			//		{
			//			myDate = pd.Format(_T("%Y/%m/%d"));
			//		//cTime = pd;

			//			myTime = pd.Format(_T("%Y/%m/%d %H:%M:%S")); //Format(tdate, "yyyy/mm/dd")
			//										//Format(tdate, "yyyy/mm/dd hh:mm:ss")
			//		//tempDate = myDate;
			//		}
			//		else
			//		{
			//			TRACE("��͕s�\\n");
			//		}

			//	//cTime =  pd.Format(_T("%Y/%m/%d %H:%M:%S"));
			//	//}
			//	//myFileSize;

		}

		if (pFile != NULL)
		{
			
			pFile->Close();
			delete pFile;
		} 
		
		TRACE(FullPathString);

		// �t�@�C����
		if (!err)
		{
			lvi.iItem = index;
			lvi.iSubItem = 3;			
			if (myFileName!=_T("")){
				lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileName));
				if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
			}

		}

		//http://oshiete.goo.ne.jp/qa/3399080.html?from=navi_ranking

		CString wFullPathString = FullPathString;
		wFullPathString.Replace(_T("\\"),_T("\\\\"));

		// �����悻�̃t�@�C���T�C�Y
		if (!err)
		{
			if ( PathFileExists(wFullPathString) ){

				lvi.iItem = index;
				lvi.iSubItem = 4;
				CString tempSize;

				//TRACE(_T("!!!!%I64u\n"),myLongFileSize);
				tempSize = ByteCalculation(myLongFileSize,FALSE);
			
				if (myLongFileSize !=0 && tempSize!=_T("")){
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempSize));
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
				}
			}
		}

		// �t�@�C���T�C�Y
		if (!err)
		{
			if ( PathFileExists(wFullPathString) ){

				lvi.iItem = index;
				lvi.iSubItem = 5;

				if (myLongFileSize !=0 && myFileSize!=_T("")){
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
				}

			}
		}
		//MessageBox(_T("IN-LOOP"));

		//�C������
		//tempDate = cTime.Format(_T("%Y/%m/%d %H:%M:%S"));
		if (!err)
		{
			if ( PathFileExists(wFullPathString) ){

				lvi.iItem = index;
				lvi.iSubItem = 7;
				if (myTime!=_T("")){
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myTime));
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
				}
			}
		}

		//�C����
		//tempDate = cTime.Format(_T("%Y/%m/%d"));
		if (!err)
		{
			if ( PathFileExists(wFullPathString) ){
				lvi.iItem = index;
				lvi.iSubItem = 6;
				if (myDate!=_T("")){
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myDate));
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
				}
			}
		}
	}else{//if(FullPathString.Right(1)==_T("\\")){ 
        int editIDX;
                
        editIDX = 0;
                
		int tempEditIDX;
    
		//FullPathString.Replace(_T("\\\\"),_T("\\"));

		if (FullPathString.GetLength() >= 2){
            if(FullPathString.GetLength() == 2){
                editIDX = 0;
			}else{
                tempEditIDX = myReverseFind(FullPathString,_T("\\"),FullPathString.GetLength()-2);
				//MessageBox(FullPathString.Mid(tempEditIDX));
				
                if(tempEditIDX - 1 >= 0){
                    tempEditIDX = myReverseFind(FullPathString,_T("\\"), tempEditIDX - 1) + 1;
					//MessageBox(FullPathString.Mid(tempEditIDX-1,1));
                    if (tempEditIDX >= 0){
                        editIDX = myReverseFind(FullPathString,_T("\\"), tempEditIDX ) + 1;
					}else{
                        editIDX = 0;
					}
                }else{
                    editIDX = 0;
				}
			}
		}
                        
    
        CString tempStr2;
                
        tempStr2 = FullPathString.Mid(editIDX, FullPathString.GetLength() - editIDX);
		//MessageBox(tempStr2);
    
        if(tempStr2.GetLength() >= 0){
            if(tempStr2.Right(1) == _T("\\")){
                tempStr2 = tempStr2.Mid(0, tempStr2.GetLength() - 1);
			}
		}
    
    
		tempStr2.Replace(_T("\\"),_T(" - "));
		myFileName = tempStr2;

		// �t�@�C����
		if (!err)
		{
			lvi.iItem = index;
			lvi.iSubItem = 3;			
			//lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileName));
			if (myFileName!=_T("")){
				lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileName));
			}
			if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;			
		}

		ULONGLONG tempByte = 0;
		tempByte = inFolder_Byte(FullPathString, _T("*.*"), 0);
		

		//http://oshiete.goo.ne.jp/qa/3399080.html?from=navi_ranking

		CString wFullPathString = FullPathString;
		wFullPathString.Replace(_T("\\"),_T("\\\\"));

		// �����悻�̃t�@�C���T�C�Y
		if (!err)
		{
			if ( PathIsDirectory(wFullPathString) ){

				lvi.iItem = index;
				lvi.iSubItem = 4;
				CString tempSize;

				//TRACE(_T("!!!!%I64u\n"),myLongFileSize);

				tempSize = ByteCalculation(tempByte,FALSE);
				if(tempByte !=0 && tempSize!=_T("")){
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempSize));
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
				}
			}
		}


		// �t�@�C���T�C�Y
		if (!err)
		{
			if ( PathIsDirectory(wFullPathString) ){
				lvi.iItem = index;
				lvi.iSubItem = 5;
				CString tempSize;

				tempSize.Format(_T("%I64u"),tempByte);
				if(tempByte !=0 && tempSize!=_T("")){
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempSize));
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
				}
			}
		}


		CTime tempTime = 0;
        
        tempTime = inFolder_Date(FullPathString, _T("*.*"), 0);


		if (CFileListCreatorDlg::m_xcList.GetItemText(index,7)==_T("")){
			//�C������
			CString myTime;
			myTime=_T("");

			myTime = tempTime.Format(_T("%Y/%m/%d %H:%M:%S"));
			if (!err)
			{
				lvi.iItem = index;
				lvi.iSubItem = 7;
				if(myTime!=_T("")){
					if ( PathIsDirectory(wFullPathString) ){

						lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myTime));
						if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
					}
				}
			}
		}

		if (CFileListCreatorDlg::m_xcList.GetItemText(index,6)==_T("")){
			//�C����
			CString myDate;
			myDate=_T("");
			myDate = tempTime.Format(_T("%Y/%m/%d"));
			if (!err)
			{
				lvi.iItem = index;
				lvi.iSubItem = 6;
				if(myDate!=_T("")){
					if ( PathIsDirectory(wFullPathString) ){

						lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myDate));
						if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
					}
				}
			}
		}
	}

	CString tempCnt;
	tempCnt = _T("");

	tempCnt.Format(_T("%d"),index + 1);
	tempCnt=tempCnt + _T(" items");

	m_xvStCount = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempCnt));
	//CFileListCreatorDlg::m_xcList.EnsureVisible(index-1, FALSE);

	UpdateData(FALSE);
	//tempDate = "";
}


void CFileListCreatorDlg::OnBnClickedBtnRestore()
{

	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	ESCAPE_FLG = FALSE;

	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		StatusStringSet(_T("Restore ���s��"),0,FALSE); //�ύX 2012.06.14

		int myResult;
		if(m_xcList.GetSelectedCount()==0){
			myResult = MessageBox(_T("�A�C�e�����I������Ă��܂���B���X�g�シ�ׂẴt�@�C�����A�t�@�C���T�C�Y�A�C�����̏��𕜋A���܂����H"),_T("Restore"),MB_YESNOCANCEL);
			if (myResult==IDYES){
				int index = 0;

				while(index < CFileListCreatorDlg::m_xcList.GetItemCount()){

					MSG msg; //�ǉ� 2011.10.12
					if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
						if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
							if (msg.wParam == VK_ESCAPE){
								ESCAPE_FLG = TRUE;
								break; //�I���B���b�Z�[�W���[�v�𔲂���B
							}
						}
						TranslateMessage(&msg);
						DispatchMessage(&msg);
						//continue;
					}

					RestoreFunc(index);
					index++;
				}
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("Restore �L�����Z��"),300,FALSE);
				return;
			}
		}
		if(m_xcList.GetSelectedCount()>=1){
			myResult = MessageBox(_T("�I�����ꂽ�A�C�e���̏��𕜋A���܂����H"),_T("Restore"),MB_YESNOCANCEL);
			if (myResult==IDYES){
				int index = -1;

				while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
				        (index, LVNI_ALL | LVNI_SELECTED)) != -1){

					MSG msg; //�ǉ� 2011.10.12
					if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
						if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
							if (msg.wParam == VK_ESCAPE){
								ESCAPE_FLG = TRUE;
								break; //�I���B���b�Z�[�W���[�v�𔲂���B
							}
						}
						TranslateMessage(&msg);
						DispatchMessage(&msg);
						//continue;
					}

					RestoreFunc(index);
				}
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("Restore �L�����Z��"),300,FALSE);
				return;
			}
		}
	}
	Total_Bytes_Bold();
	Total_Bytes_Func();
	ItemCount_Func(FALSE);

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
		//SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24
	}

	CFileListCreatorDlg::StatusStringSet(_T("Restore �I���F���A"),0,TRUE);

	///////////////////////////////////////////////////////////////
}

void CFileListCreatorDlg::PackageSearch_Items(CString myPathname ,CString strFileSpec,BOOL GetItemsCntFLG)
{

	CString tempPathName = myPathname + _T("\\")+ strFileSpec;
	//CString strWildcard =  _T("\\*.*") ;
   
	CFileFind finder;
    BOOL         bWorking = finder.FindFile(tempPathName);
    CString      str;

	StatusStringSet(_T("PackageSearch �����Ώ� �� " + strFileSpec),0,FALSE); //�ύX 2012.06.14

   // build a string with wildcards

   // start working for files
   //BOOL bWorking = finder.FindFile(strWildcard);

	int err = 0;

   while (bWorking)
   {
	  if (ESCAPE_FLG == FALSE){  //�ǉ� if���ǉ� 2012.05.11
			bWorking = finder.FindNextFile();
	  }else{
		  break;
	  }
      // skip . and .. files; otherwise, we'd
	  // recur infinitely!
      if (finder.IsDots()) continue;


		MSG msg; //�ǉ� 2011.10.12
		if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
			if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
				if (msg.wParam == VK_ESCAPE){
					ESCAPE_FLG = TRUE;
					break; //�I���B���b�Z�[�W���[�v�𔲂���B
				}
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			//continue;
		}


		err = finder.IsDirectory();

		if (!err){
		
			CString str = finder.GetFilePath();

			CString strFileSpec2 = strFileSpec; 
			if(strFileSpec2 != _T("")){
				strFileSpec2.Replace(_T("*."),_T("")); 
			}
			//Like���Z�q���g���Ȃ��̂ŁA�g���q�𒼐ڔ�r(��)�����B
			// *.htm; *.html; �����t�@�C������d�Ƀq�b�g���Ă��܂��̂�
			// *.*; �̏ꍇ�������ɒǉ�

			if (CFileListCreatorDlg::importFileList_Func(str,TRUE)== 1 && SkipFLG == FALSE){
				importFileResult = MessageBox(_T("�������̃��X�g�t�@�C�������o����܂����B�C���|�[�g���s���A���X�g��W�J���܂����H"),_T("�C���|�[�g�m�F"), MB_YESNOCANCEL );
				SkipFLG = TRUE;
			}

			if (GetItemsCntFLG == TRUE){  //���̏����́A�t�H���_����H�����ꍇ�ƁA�t�@�C���{�̂��q�b�g�����ꍇ�A����ʂ���B��d�ɃJ�E���g���Ȃ��I
				if(CFileListCreatorDlg::importFileList_Func(str,TRUE) == 1 && (str.Right(strFileSpec2.GetLength())==strFileSpec2 || strFileSpec == _T("*.*") )){ 
					ULONGLONG tempCnt;

					tempCnt = CFileListCreatorDlg::FileListItemsCount(str);
					if( tempCnt == 0 ){
						//TotalItemsCount ++;
					}else{
						TotalItemsCount = TotalItemsCount + tempCnt;
					}

				}
			}else{
				if (importFileResult == IDYES){
					if (CFileListCreatorDlg::importFileList_Func(str,TRUE) == 1 && str.Right(strFileSpec2.GetLength())==strFileSpec2){
						CFileListCreatorDlg::importFileList_Func(str,FALSE);						
					}else{
						if(CFileListCreatorDlg::importFileList_Func(str,TRUE) == 1 && isFileFLG(str,strFileSpec)==TRUE && strFileSpec == _T("*.*")){
							CFileListCreatorDlg::importFileList_Func(str,FALSE);
						}else if(str.Right(strFileSpec2.GetLength())==strFileSpec2 || strFileSpec == _T("*.*")){
							CFileListCreatorDlg::ListInsertItem(str);
						}
					}
				}else{
					if (CFileListCreatorDlg::importFileList_Func(str,TRUE) == 0 || importFileResult !=IDYES){
						if(str.Right(strFileSpec2.GetLength())==strFileSpec2 || strFileSpec == _T("*.*")){
							CFileListCreatorDlg::ListInsertItem(str);
						}
					}
				}
			}
		}
   }
   finder.Close();

   err = 0;

	if(m_xvChkSubFolder == TRUE){ //�T�u�t�H���_������

		CString strWildcard = _T("\\*.*"); 

		//CFileFind    finder;
		//BOOL         bWorking = finder.FindFile(myPathname + strWildcard);
		//CString      str;
		bWorking = finder.FindFile(myPathname + strWildcard);

		// �T�u�f�B���N�g�����������A�ċA�Ăяo��
		while (bWorking)
		{
			MSG msg; //�ǉ� 2011.10.12
			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						ESCAPE_FLG = TRUE;
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			//if (finder.IsDots()) continue;

			//err = ListInsertItem(finder.GetFilePath(), 
			//    finder.GetFileName(), finder.IsDirectory());

			
			if (ESCAPE_FLG == FALSE){  //�ǉ� if���ǉ� 2012.05.11
				bWorking = finder.FindNextFile();
			}else{
				break;
			}

			if (finder.IsDots()) continue;
			
			err = finder.IsDirectory();

			if (err){
				CString str;
				str = finder.GetFilePath();
				//if (isDirectoryFLG(str)==TRUE){
					CFileListCreatorDlg::PackageSearch_Items(str,strFileSpec,GetItemsCntFLG); 
				//}
			}
		}
		finder.Close();
    
		UpdateData(FALSE);
	}
}

void CFileListCreatorDlg::PackageSearch_Func(CString myPathname, CString strFileSpec)
{   

	ESCAPE_FLG = FALSE; //�K�v 2012.05.20
	//SkipFLG = FALSE; //�ǉ� 2012.07.09 //�R�����g�� 2012.07.11
	
	BOOL ALL_FileSpecs;
	ALL_FileSpecs = FALSE;

	if (strFileSpec.Find(_T("*.*;"),0)>=0) ALL_FileSpecs = TRUE;

    //TotalItemsCount = 0; //�R�����g�� 2012/07.26
    if (strFileSpec == _T(""))
	{
		//if(MessageBox(_T("�����ΏۂƂȂ�g���q��1�ȏ����Ă�������") ,_T("������"), MB_YESNO )== IDYES  ){
		//	CFileListCreatorDlg::OnBnClickedBtnPackagesearch();
		//}
	}

	CString strBuff2 = _T("");

	LONG k;

	k = 0; //VBA�F1 �� VC�F�O�ɓY�����ύX

	//myPathname.Replace(_T("\\"),_T("\\\\"));

	if (strFileSpec != _T("")){
		if(isDirectoryFLG(myPathname)==FALSE){
			ListInsertItem(myPathname);
		}
	}
	//myPathname.Replace(_T("\\\\"),_T("\\"));

	while (k <= strFileSpec.GetLength() -1 ){
		if (ESCAPE_FLG == TRUE) break;  //�ǉ� 2011.10.12

		if (strFileSpec.Mid(k,1) == _T(";")) {
			if(ALL_FileSpecs == TRUE){
				if(isDirectoryFLG(myPathname)==TRUE && (strBuff2!=_T("*.html") && strBuff2!=_T("*.htm"))){ 
					CFileListCreatorDlg::PackageSearch_Items(myPathname, strBuff2,TRUE);
				}
			}else{
				//CFileListCreatorDlg::PackageSearch_Func(myPathname,strBuff2);
				if(isDirectoryFLG(myPathname)==TRUE ){ //�ǉ� 2012.06.14
					CFileListCreatorDlg::PackageSearch_Items(myPathname, strBuff2,TRUE);
				}
			}
			strBuff2 = _T("");
		}else{
			strBuff2 = strBuff2 + strFileSpec.Mid(k,1);
		}
		k = k + 1;
	}

	k = 0;

	while (k <= strFileSpec.GetLength() -1 ){
		if (ESCAPE_FLG == TRUE) break;  //�ǉ� 2011.10.12

		if (strFileSpec.Mid(k,1) == _T(";")) {
			//CFileListCreatorDlg::PackageSearch_Func(myPathname,strBuff2);
			//if(isDirectoryFLG(myPathname)==TRUE){
			//	CFileListCreatorDlg::PackageSearch_Items(myPathname, strBuff2,FALSE);
			//}
			if(ALL_FileSpecs == TRUE){
				if(isDirectoryFLG(myPathname)==TRUE && (strBuff2!=_T("*.html") && strBuff2!=_T("*.htm"))){ 
					CFileListCreatorDlg::PackageSearch_Items(myPathname, strBuff2,FALSE);
				}
			}else{
				if(isDirectoryFLG(myPathname)==TRUE ){ 
					CFileListCreatorDlg::PackageSearch_Items(myPathname, strBuff2,FALSE);
				}
			}
			strBuff2 = _T("");
		}else{
			strBuff2 = strBuff2 + strFileSpec.Mid(k,1);
		}
		k = k + 1;
	}

	//if (TotalItemsCount>=1){
		ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

		CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

		if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
			return;
		}

		if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
			m_Dlg->SetWindowText(_T("FileListCreator (*)"));
			SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24
		}
	//}

	ALL_FileSpecs = FALSE;
}

void CFileListCreatorDlg::OnBnClickedBtnPackagesearch()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	DoWithCnt = 0; //�ǉ� 2012.07.11
	TotalItemsCount = 0; //�ǉ� 2012.07.11

	//ESCAPE_FLG = FALSE;

	StatusStringSet(_T("PackageSearch ���s��"),0,FALSE); //�ύX 2012.06.14

	int myResult;
    
	if (m_xvChkSubFolder == FALSE){
		myResult = MessageBox(_T("�T�u�t�H���_���������Ȃ��ݒ�ɂȂ��Ă��܂��B�T�u�t�H���_���������܂����H\r\n(�T�u�t�H���_�Ƃ͌��݂̃f�B���N�g���ɂ���z���̂��ׂẴt�H���_���w���܂�)") ,_T("�Ċm�F"), MB_YESNO );
		if(myResult	== IDYES  ){
			m_xvChkSubFolder = TRUE;
			//http://www.ujasiri.com/prglib/vc/compo/vc_chkboxsap.html
			
			CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_Search_SubFolder);
			chkbox1->SetCheck(1);

			UpdateData(FALSE);
		}else{
			m_xvChkSubFolder = FALSE;
			//http://www.ujasiri.com/prglib/vc/compo/vc_chkboxsap.html
			
			CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_Search_SubFolder);
			chkbox1->SetCheck(0);

			UpdateData(FALSE);
		}
	}

	//���[�_��
	CFileSpecsDlg m_dlg;
	m_dlg.DoModal();


	if(m_dlg.TargetFileSpecs == _T("")){
		CFileListCreatorDlg::StatusStringSet(_T("FileSpecsDlg : ���[�U�[�ɂ��L�����Z��"),300,TRUE);
		delete m_dlg;
		return;
	}

	if(m_dlg.TargetFileSpecs == _T("<<error>>")){
		CFileListCreatorDlg::StatusStringSet(_T("FileSpecsDlg : �������`���Ō����Ώۂ��w�肵�Ă�������"),300,TRUE);
		delete m_dlg;
		return;
	}

	TCHAR  szFolder[MAX_PATH];

	if( GetOpenFolderName( AfxGetMainWnd()->m_hWnd, NULL, szFolder, MAX_PATH ) == IDOK )
	{
		SkipFLG = FALSE; //�ǉ� 2012.07.11
		CFileListCreatorDlg::PackageSearch_Func(CString(szFolder),m_dlg.TargetFileSpecs);
	}
	delete m_dlg;

	//CFileListCreatorDlg::Total_Bytes_Func();//�ǉ� 2011.10.13

	CFileListCreatorDlg::Total_Bytes_Bold(); //�ǉ� 2012.07.11
	CFileListCreatorDlg::Total_Bytes_Func(); //�ǉ� 2012.07.11
	CFileListCreatorDlg::ItemCount_Func(FALSE); //�ǉ� 2012.07.11

	CFileListCreatorDlg::StatusStringSet(_T("PackageSearch �I��"),300,TRUE);
}


void CFileListCreatorDlg::OnBnClickedChkSearchSubfolder()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	if (m_xvChkSubFolder == FALSE){
		m_xvChkSubFolder = TRUE;
	}else{
		m_xvChkSubFolder = FALSE;
	}
}


void CFileListCreatorDlg::OnStnClickedStaticStatusstring()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

}


void CFileListCreatorDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	

	//if (LastSelectedColumn == 2 || LastSelectedColumn == 3 || LastSelectedColumn == 8){
	//	if (  ( pNMLV->uChanged == LVIF_PARAM && pNMLV->uNewState == 0 && pNMLV->uOldState == 0)
	//		|| ( pNMLV->uChanged == LVIF_STATE && pNMLV->uNewState == 4096 && pNMLV->uOldState == 0 )
	//		||  ( pNMLV->uChanged == LVIF_STATE && pNMLV->uNewState == 0 && pNMLV->uOldState == (LVIS_FOCUSED | LVIS_SELECTED) )){ 
	//		//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������

	//http://isobe.exblog.jp/996027/

	//http://q.hatena.ne.jp/1180853478


	//TRACE(_T("=============================================================================\r\n"));
	//CString tempStr;
	//tempStr.Format(_T("OnLvnItem changed List iItem: %d,iSubItem: %d, lParam: %d, uChanged: %d, uNewState: %d, uOldState: %d\n"), pNMLV->iItem, pNMLV->iSubItem, pNMLV->lParam, pNMLV->uChanged, pNMLV->uNewState, pNMLV->uOldState);
	////MessageBox(tempStr);

	//TRACE(tempStr);

	////CString tempStr;
	//tempStr.Format(_T("(LVIS_FOCUSED | LVIS_SELECTED): %d,(!LVIS_FOCUSED | !LVIS_SELECTED): %d, !(LVIS_FOCUSED | LVIS_SELECTED): %d, \n"), (LVIS_FOCUSED | LVIS_SELECTED), (!LVIS_FOCUSED | !LVIS_SELECTED), !(LVIS_FOCUSED | LVIS_SELECTED));
	////MessageBox(tempStr);

	//TRACE(tempStr);

	//TRACE(_T("=============================================================================\r\n"));

	////LVITEM       lvi;
	//int          index = 0;
	//int          err = 0;
	//CString      CurStr;	
	//CString      FullPathString;

	//BOOL LengthOver = FALSE;

	//UpdateData();
	//lvi.mask = LVIF_TEXT;			

	//index = pNMLV->iItem;

	//int ColumnNum;

	//for (ColumnNum = 0;ColumnNum <= 8;ColumnNum++){
	//	CurStr = CFileListCreatorDlg::m_xcList.GetItemText(index,ColumnNum);

	//	if (CurStr!=_T("")) {
	//		lvi.iItem =index;
	//		lvi.iSubItem = ColumnNum;

	//		//MessageBox(RemarksColumnStr);

	//		if (CurStr.GetLength() > 260){
	//			CurStr = CurStr.Left(260);
	//			//LengthOver = TRUE;
	//			CFileListCreatorDlg::StatusStringSet(_T("���X�g�{�b�N�X���̊i�[�������������I�[�o�[���܂���\r\n(������260������؂���܂�)"),0,TRUE);
	//			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(CurStr));
	//			CFileListCreatorDlg::m_xcList.SetItem(&lvi);
	//			UpdateData(FALSE);
	//		}
	//	}
	//}

	*pResult = 0;

}

////http://msdn.microsoft.com/ja-jp/library/b4ceh1za.aspx

//http://www.alpha-net.ne.jp/users2/uk413/vc/VCT_LVitemsort.html
//keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������
int CALLBACK CFileListCreatorDlg::CompareFunc(LPARAM param1, LPARAM param2, LPARAM param3)
{
	// static�����o�֐��Ȃ̂ŁAGetParent()�Őe�E�B���h�E���擾���邱�Ƃ͂ł��Ȃ�
	CFileListCreatorDlg* pDlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������

	// ��r�����Q�̃A�C�e������u�������v�̕�������擾����
	// 2�s�ڂ̃t���p�X�����Ƀ\�[�g
	CString str_1 = pDlg->m_xcList.GetItemText(param1, pDlg->keyColumn); //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������

	CString str_2 = pDlg->m_xcList.GetItemText(param2, pDlg->keyColumn);
	
	int iReturn;

	if(pDlg->keyColumn == 5 || pDlg->keyColumn == 1){//�f�[�^�T�C�Y�Ń\�[�g
		//ret.Format(_T("%.3f%s"), dblSize,_T("TB"));
		//CFileListCreatorDlg::CStringToLong(

		// strcmp���g���Ȃ�A�~���̏ꍇ��str1��str2���t�ɂ��Ȃ���΂Ȃ�Ȃ�
		//int iReturn;
		if( !param3 ){
			if ( pDlg->CStringToLong(str_1) >= pDlg->CStringToLong(str_2)){
				iReturn = TRUE;
			}else{
				iReturn = FALSE;
			}
			//iReturn = _tcscmp( lpsz_1, lpsz_2 ); // ����
		}else{
			if ( pDlg->CStringToLong(str_1) <= pDlg->CStringToLong(str_2)){
				iReturn = TRUE;
			}else{
				iReturn = FALSE;
			}
			//iReturn = _tcscmp( lpsz_2, lpsz_1 ); // �~��
		}
		// strcmp���g���Ȃ�A�~���̏ꍇ��str1��str2���t�ɂ��Ȃ���΂Ȃ�Ȃ�
		//int iReturn;
		if( !param3 ){
			if ( pDlg->CStringToLong(str_1) >= pDlg->CStringToLong(str_2)){
				iReturn = TRUE;
			}else{
				iReturn = FALSE;
			}
			//iReturn = _tcscmp( lpsz_1, lpsz_2 ); // ����
		}else{
			if ( pDlg->CStringToLong(str_1) <= pDlg->CStringToLong(str_2)){
				iReturn = TRUE;
			}else{
				iReturn = FALSE;
			}
			//iReturn = _tcscmp( lpsz_2, lpsz_1 ); // �~��
		}
	}else if(pDlg->keyColumn == 0){ //�d��NO �Ń\�[�g
		// strcmp���g���Ȃ�A�~���̏ꍇ��str1��str2���t�ɂ��Ȃ���΂Ȃ�Ȃ�
		//int iReturn;

		if( !param3 ){
			if(str_1==_T("")){
				str_1 = _T("0");
			}
			if(str_2==_T("")){
				str_2 = _T("0");
			}
			if ( pDlg->CStringToLong(str_1) >= pDlg->CStringToLong(str_2)){
				iReturn = TRUE;
			}else{
				iReturn = FALSE;
			}
			//iReturn = _tcscmp( lpsz_1, lpsz_2 ); // ����
		}else{
			if ( pDlg->CStringToLong(str_1) <= pDlg->CStringToLong(str_2)){
				iReturn = TRUE;
			}else{
				iReturn = FALSE;
			}
			//iReturn = _tcscmp( lpsz_2, lpsz_1 ); // �~��
		}
	}else{
		int     sizeOfString_1 = (str_1.GetLength() + 1);
		LPTSTR  lpsz_1 = new TCHAR[ sizeOfString_1 ];
		_tcscpy_s(lpsz_1, sizeOfString_1, str_1);

		int     sizeOfString_2 = (str_2.GetLength() + 1);
		LPTSTR  lpsz_2 = new TCHAR[ sizeOfString_2 ];
		_tcscpy_s(lpsz_2, sizeOfString_2, str_2);

		// strcmp���g���Ȃ�A�~���̏ꍇ��str1��str2���t�ɂ��Ȃ���΂Ȃ�Ȃ�
		//int iReturn;
		if( !param3 )
			iReturn = _tcscmp( lpsz_1, lpsz_2 ); // ����
		else
			iReturn = _tcscmp( lpsz_2, lpsz_1 ); // �~��

		delete[] lpsz_1;
		delete[] lpsz_2;
	}
	return iReturn;
}

void CFileListCreatorDlg::RenumberItem()
{
	LV_ITEM lvi;
	CString str;

	// m_list1��CListCtrl�^��DDX�ϐ��ŁA�\�[�g���s�����X�g�r���[�R���g���[���̃I�u�W�F�N�g�ł�����̂Ƃ���
	for( int i = 0; i < m_xcList.GetItemCount(); i++ ) {
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_PARAM;
		lvi.lParam = i;		// �����Ŕԍ����A�C�e���Ɏw�肷��
		
		m_xcList.SetItem(&lvi);
	}
}

void CFileListCreatorDlg::OnBnClickedBtnSort()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{

		//�R�����g�� 2012.07.12 Merge_Func()�ł��\�[�g���Ă���̂ŏd��

		//CFileListCreatorDlg::GetStrFormat_Func();

		//StatusStringSet(_T("Sort ���s��"),0,FALSE); //�ύX 2012.06.14

		//RenumberItem();				// SortItems�֐����Ăяo���O�ɂ͕K�����s

		//keyColumn = 2;//keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������
		//static BOOL bSort = FALSE;			// static�Œ�`���邱��
		//m_xcList.SortItems(CompareFunc, bSort);

		//if (bSort == FALSE) { 
		//	CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(����)"),300,TRUE);
		//}else{
		//	CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�~��)"),300,TRUE);
		//}
		//SortColumnDrawCaption(keyColumn, bSort);
		//bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���

		//CFileListCreatorDlg::m_xcList.EnsureVisible(0, FALSE);

		//CFileListCreatorDlg::SetStrFormat_Func();
		Merge_Func();
	}

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
		//SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24
	}
	
	//SortItems�֐��̑�Q�����Ɏw�肵��bSort�̒l�́A
	//��r�֐�CompareFunc�̂R�Ԗڂ̈���param3�ɓn�����B
	//�܂�A�P��ڂ�bSort�̒l��FALSE�Ȃ̂�param3��FALSE�i���Ȃ킿0�j
	//�ƂȂ�A�����\�[�g���s����B 
	
	//�܂��Q��ڂ�bSort��TRUE�ɂȂ��Ă���̂�param3��TRUE�i��0�j�ƂȂ�A
	///�~���Ń\�[�g�����Ƃ����킯�ł���B
}

void CFileListCreatorDlg::Merge_Func(){
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		CFileListCreatorDlg::GetStrFormat_Func();

		LastPrevItemCount = m_xcList.GetItemCount();
		CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

		StatusStringSet(_T("Sort ���s��"),0,FALSE); //�ύX 2012.06.14

		RenumberItem();				// SortItems�֐����Ăяo���O�ɂ͕K�����s

		keyColumn = 2;//keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������
		//static BOOL bSort = FALSE;			// static�Œ�`���邱��
		m_xcList.SortItems(CompareFunc, FALSE);

		//if (bSort == FALSE) { 
		//	CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(����)"),300,FALSE);
		//}else{
		//	CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�~��)"),300,FALSE);
		//}
		//bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���

		//CFileListCreatorDlg::m_xcList.EnsureVisible(0, FALSE);

		CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(����)"),300,FALSE);


		CFileListCreatorDlg::StatusStringSet(_T("Merge ���s��"),300,FALSE);

		CFileListCreatorDlg::SetStrFormat_Func();

		//LVITEM       lvi;
		int          index = 0;
		int          err = 0;
		CString      str;	
		CString      FullPathString;

		BOOL LengthOver = FALSE;

		UpdateData();
		lvi.mask = LVIF_TEXT;

		CString CurValue = _T("");
		CString NextValue = _T("");

		int j = 0;

		while (index+1<=CFileListCreatorDlg::m_xcList.GetItemCount()-1 && j<CFileListCreatorDlg::m_xcList.GetItemCount()-1){
			
			MSG msg; //�ǉ� 2012.04.04
			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						ESCAPE_FLG = TRUE;
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue; //�t�@�C�����R�s�[����Ƃ��̓R�����g��
			}
			
			CurValue = CFileListCreatorDlg::m_xcList.GetItemText(index,2);
			j = index + 1;
			NextValue = CFileListCreatorDlg::m_xcList.GetItemText(j,2);


			CString RemarksColumnStr;
			RemarksColumnStr = _T("");

			if (CFileListCreatorDlg::m_xcList.GetItemText(index,8)!=_T("")){
				RemarksColumnStr = CFileListCreatorDlg::m_xcList.GetItemText(index,8);
			}

			while(index<j && CurValue == NextValue){
				if (ESCAPE_FLG == TRUE) break;//���̕����ł����[�v�𔲂���悤�A�t���O�Ő��䂷��//�ǉ� 2012.04.04

				int FormatDataNum1;
				FormatDataNum1 = CFileListCreatorDlg::m_xcList.GetItemData(index);	

				int FormatDataNum2;
				FormatDataNum2 = CFileListCreatorDlg::m_xcList.GetItemData(j);	

				//FormatDataStr = _T("NORMAL,BLACK,");

				if(FormatDataNum1 == 11){
					//FormatDataStr = _T("NORMAL,BLACK,");
					if(FormatDataNum2 == 11){
						//FormatDataStr = _T("NORMAL,BLACK,");

					}else if(FormatDataNum2 == 12){
						//FormatDataStr = _T("BOLD,BLACK,");
						FormatDataNum1 = 12;
					}else if(FormatDataNum2 == 21){
						//FormatDataStr = _T("NORMAL,RED,");
						FormatDataNum1 = 21;

					}else if(FormatDataNum2 == 22){
						//FormatDataStr = _T("BOLD,RED,");
						FormatDataNum1 = 22;

					}
				}else if(FormatDataNum1 == 12){
					//FormatDataStr = _T("BOLD,BLACK,");
					if(FormatDataNum2 == 11){
						//FormatDataStr = _T("NORMAL,BLACK,");

					}else if(FormatDataNum2 == 12){
						//FormatDataStr = _T("BOLD,BLACK,");

					}else if(FormatDataNum2 == 21){
						//FormatDataStr = _T("NORMAL,RED,");
						FormatDataNum1 = 22;

					}else if(FormatDataNum2 == 22){
						//FormatDataStr = _T("BOLD,RED,");
						FormatDataNum1 = 22;

					}
				}else if(FormatDataNum1 == 21){
					//FormatDataStr = _T("NORMAL,RED,");
					if(FormatDataNum2 == 11){
						//FormatDataStr = _T("NORMAL,BLACK,");

					}else if(FormatDataNum2 == 12){
						//FormatDataStr = _T("BOLD,BLACK,");
						FormatDataNum1 = 22;

					}else if(FormatDataNum2 == 21){
						//FormatDataStr = _T("NORMAL,RED,");

					}else if(FormatDataNum2 == 22){
						//FormatDataStr = _T("BOLD,RED,");
						FormatDataNum1 = 22;

					}
				}else if(FormatDataNum1 == 22){
					//FormatDataStr = _T("BOLD,RED,");
					if(FormatDataNum2 == 11){
						//FormatDataStr = _T("NORMAL,BLACK,");
					}else if(FormatDataNum2 == 12){
						//FormatDataStr = _T("BOLD,BLACK,");

					}else if(FormatDataNum2 == 21){
						//FormatDataStr = _T("NORMAL,RED,");

					}else if(FormatDataNum2 == 22){
						//FormatDataStr = _T("BOLD,RED,");
					}
				}

				//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
				
				//���l������ 2012.04.18

				if (CFileListCreatorDlg::m_xcList.GetItemText(j,8)!=_T("")){
					if (RemarksColumnStr == _T("")) {
						RemarksColumnStr = CFileListCreatorDlg::m_xcList.GetItemText(j,8);
					}else{
						RemarksColumnStr = RemarksColumnStr + _T(",") + CFileListCreatorDlg::m_xcList.GetItemText(j,8);
					}

					//CString debugStr;
					//debugStr = _T("");

					//debugStr.Format(_T("index = %d j = %d item = %s RemarksColumnStr = %s"),index,j,CFileListCreatorDlg::m_xcList.GetItemText(j,8),RemarksColumnStr);

					//MessageBox (debugStr,MB_OK);
				}

				CFileListCreatorDlg::m_xcList.SetItemData(index,FormatDataNum1);

				CFileListCreatorDlg::m_xcList.DeleteItem(j);
				NextValue = CFileListCreatorDlg::m_xcList.GetItemText(j,2);
				//j++;
			}

			if (index>= 0 && (index <= CFileListCreatorDlg::m_xcList.GetItemCount()-1)){
				if (RemarksColumnStr!=_T("")) {
					lvi.iItem =index;
					lvi.iSubItem = 8;//���l��

					//MessageBox(RemarksColumnStr);

					if (RemarksColumnStr.GetLength() > 260){
						RemarksColumnStr = RemarksColumnStr.Left(260);
						LengthOver = TRUE;
					}

					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(RemarksColumnStr));
					CFileListCreatorDlg::m_xcList.SetItem(&lvi);
					UpdateData(FALSE);
				}
			}


			if (j<=CFileListCreatorDlg::m_xcList.GetItemCount()-1){
				CString tempCnt;
				tempCnt = "";

				tempCnt.Format(_T("%d"),j+1);
				tempCnt=tempCnt + _T(" items");

				CFileListCreatorDlg::StatusStringSet(_T("Merge ���s��: ") + tempCnt,0,FALSE);
				CFileListCreatorDlg::m_xcList.EnsureVisible(j, FALSE); //�ǉ� 2012.04.04  //�R�����g�� 2012.06.10
			}

			index++;
			UpdateData(FALSE);
		}

		CFileListCreatorDlg::Total_Bytes_Bold();
		CFileListCreatorDlg::Total_Bytes_Func();
		CFileListCreatorDlg::ItemCount_Func(TRUE);

		ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

		CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

		if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
			return;
		}

		if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
			m_Dlg->SetWindowText(_T("FileListCreator (*)"));
			SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24
		}

		CFileListCreatorDlg::StatusStringSet(_T("Merge �I��"),300,TRUE);

		if (LengthOver == TRUE){
			CFileListCreatorDlg::StatusStringSet(_T("���l���̊i�[�������������I�[�o�[���܂���\r\n(������260������ �e�L�X�g��؂���܂�)"),0,TRUE);
		}
	}
}

void CFileListCreatorDlg::OnNMRClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	
//http://social.msdn.microsoft.com/Forums/en/vcgeneral/thread/1791d4d5-a1c4-4eab-8e2b-d11b718e5a41


    //LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;

		int nItem;
		int nSubItem;

		nItem = pNMItemActivate->iItem;
		nSubItem = pNMItemActivate->iSubItem;

		LastSelectedRow  = nItem;
		LastSelectedColumn = nSubItem;

	if ( m_xvChkEditCellMode == FALSE ) {
		POINT point;

		::GetCursorPos(&point);

		// "�E�N���b�N"
			CMenu    *popupMenuP = NULL;
			CMenu    cMenu;
			int      err = 0;
    
			if (SelectedLanguage == _T("Japanese")) {
				// ���j���[�����[�h
				if (!err) if (!cMenu.LoadMenu(IDR_MENU1)) err = 1;
			}else if (SelectedLanguage == _T("English")){
				// ���j���[�����[�h
				if (!err) if (!cMenu.LoadMenu(IDR_MENU3)) err = 1;
			}

			// �T�u���j���[���擾
			if (!err) if ((popupMenuP = cMenu.GetSubMenu(0)) == NULL) err = 1;
			// ���j���[���|�b�v�A�b�v
			if (!err)
			{
				ClientToScreen(&point);
				if (!popupMenuP->TrackPopupMenu(
					TPM_LEFTBUTTON, point.x-100, point.y-100, this)) err = 1; //-100�ɂ���
			}
			// ���j���[��j��
			cMenu.DestroyMenu();
    
			CDialog::OnRButtonUp(TPM_LEFTALIGN, point);
	
			*pResult = 0;
	}else{
		CFileListCreatorDlg::StatusStringSet(_T("�Z���f�[�^�̕ҏW���ł�"),300,TRUE);
	}

	return;
}

void CFileListCreatorDlg::OnMenuMymessage()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	if (SelectedLanguage == _T("Japanese")) {
		// http://code.msdn.microsoft.com/windowsdesktop/Windows-howto-203dcb68

		// �o�[�W�������̎擾 
		OSVERSIONINFO OSver; 
		OSver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
		GetVersionEx(&OSver); 
 
		// ���� Windows 7 �ȍ~�̃o�[�W�����œ����������Ƃ� 
		if((OSver.dwMajorVersion == 6 && OSver.dwMinorVersion >= 1) || OSver.dwMajorVersion > 6) 
		{ 
			//MessageBox(NULL, _T("Windows 7 �ȍ~"), _T("�o�[�W�������"), MB_OK);
			SpeakFunc(_T("�����p���肪�Ƃ��������܂����I"));
		}else{
			SpeakFunc(_T("Thank you for using File List Creator!"));
		}
	}else if (SelectedLanguage == _T("English")){

		// �o�[�W�������̎擾 
		OSVERSIONINFO OSver; 
		OSver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
		GetVersionEx(&OSver); 
 
		// ���� Windows 7 �ȍ~�̃o�[�W�����œ����������Ƃ� 
		if((OSver.dwMajorVersion == 6 && OSver.dwMinorVersion >= 1) || OSver.dwMajorVersion > 6) 
		{ 
			//MessageBox(NULL, _T("Windows 7 �ȍ~"), _T("�o�[�W�������"), MB_OK);
			SpeakFunc(_T("Thank you for use of FileListCreator!"));
		}else{
			SpeakFunc(_T("Thank you for using File List Creator!"));
		}
	}


	CFileListCreatorDlg::m_xvStatusString = _T("");

    CString tmpString1;
    
    tmpString1 = _T("����̓��A�v���̂����p�����҂����Ă��܂��B");
    
    CString tmpString2;
    
    tmpString2 = _T("");

	int i;

    for(i = 0; i < tmpString1.GetLength(); i++ ){

		tmpString2 = tmpString2 + tmpString1.Mid(i,1);

		CFileListCreatorDlg::m_xvStatusString = tmpString2;
		UpdateData(FALSE);

		Sleep(100);
	}
}

void CFileListCreatorDlg::DeleteSelectedRows_Func(){
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

    int        index = -1;
    CString    str;

	int myCnt = 0;

    while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
        (index, LVNI_ALL | LVNI_SELECTED)) != -1)
    {
		myCnt++;
    }
	
	int myResult;
	CString tempCnt;

	if(myCnt==0){
		myResult = MessageBox(_T("���ׂĂ��폜���܂����H"),_T("Deletion range confirmation"),MB_YESNOCANCEL);
		if(myResult == IDYES){

			// Delete all of the items from the list view control.
			CFileListCreatorDlg::m_xcList.DeleteAllItems();
			//ASSERT(m_myListCtrl.GetItemCount() == 0);

			CFileListCreatorDlg::StatusStringSet(_T("���ׂč폜���܂���"),300,TRUE);

			tempCnt = _T("");

			tempCnt.Format(_T("%d"),CFileListCreatorDlg::m_xcList.GetItemCount());
			tempCnt=tempCnt + _T(" items");

			m_xvStCount = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempCnt));
			//CFileListCreatorDlg::m_xcList.EnsureVisible(index-1, FALSE);
			UpdateData(FALSE);
		}
	}else if(myCnt>=1){
		myResult = MessageBox(_T("���ݑI������Ă���s�̃f�[�^���폜���܂����H"),_T("Deletion range confirmation"),MB_YESNOCANCEL);
		if(myResult == IDYES){
			index = -1;
			while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
				(index, LVNI_ALL | LVNI_SELECTED)) != -1)
			{

				CFileListCreatorDlg::m_xcList.DeleteItem(index);
				index--;
			}

			//CString tempCnt;
			tempCnt = _T("");

			tempCnt.Format(_T("%d"),myCnt);
			tempCnt=tempCnt + _T(" �s�̃f�[�^���폜���܂���");

			CFileListCreatorDlg::StatusStringSet(tempCnt,300,TRUE);

			tempCnt = "";

			tempCnt.Format(_T("%d"),CFileListCreatorDlg::m_xcList.GetItemCount());
			tempCnt=tempCnt + _T(" items");

			m_xvStCount = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempCnt));
			//CFileListCreatorDlg::m_xcList.EnsureVisible(index-1, FALSE);
			UpdateData(FALSE);

		}else if(myResult == IDNO){

		}
	}

	if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1 || MiniWindowFLG == FALSE){
		m_xcStaticString.ShowWindow(SW_HIDE);
	}else{
		m_xcStaticString.ShowWindow(SW_SHOW);
	}

	CFileListCreatorDlg::Total_Bytes_Bold();
	CFileListCreatorDlg::Total_Bytes_Func();
	CFileListCreatorDlg::ItemCount_Func(TRUE);

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}

	::SetFocus(::GetDlgItem(m_hWnd,IDC_LIST));
	//If vbYes = MsgBox("�L�[���[�h�⃊�v���C�X ���[�h�A���t�t�B���^���Ȃǂ��폜���܂����H", vbYesNoCancel + vbInformation, "Warning...") Then
}

void CFileListCreatorDlg::OnBnClickedBtnClear()
{
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		CFileListCreatorDlg::DeleteSelectedRows_Func();
	}
}

void CFileListCreatorDlg::OnMenuDeleteSelectedRows()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		CFileListCreatorDlg::DeleteSelectedRows_Func();
	}
}


void CFileListCreatorDlg::OnFileImport()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	OnBnClickedBtnImport();
}


void CFileListCreatorDlg::OnFileExport()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	OnBnClickedBtnExport();
}


void CFileListCreatorDlg::OnSearchPackagesearch()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	OnBnClickedBtnPackagesearch();
}


void CFileListCreatorDlg::OnSearchStepsearch()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	OnBnClickedBtnStepsearch();
}


void CFileListCreatorDlg::OnEditRestore()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	OnBnClickedBtnRestore();
}


void CFileListCreatorDlg::OnEditlistSort()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	OnBnClickedBtnSort();
}


void CFileListCreatorDlg::OnMenuDeleterow()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	OnBnClickedBtnClear();
}


void CFileListCreatorDlg::OnOptionMymessage()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	OnMenuMymessage();
}


void CFileListCreatorDlg::OnFileQuit()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	AutoSaveMode_ReadOrWrite_Func(_T("write"));
	UseUNDO_Mode_ReadOrWrite_Func(_T("write"));

	if(m_xvChkAutoSave == FALSE && m_xcList.GetItemCount() >= 1) {
		int myResult = MessageBox(_T("���X�g�t�@�C����ۑ������ɏI�����܂����H"),_T("Quit confirmation"),MB_YESNOCANCEL);
		if(myResult == IDYES){

			//prevData = NULL;
			//free(nowData);
			//nowData = NULL;
			//free(workData);
			//workData = NULL;

			CDialogEx::OnCancel();
		}
	}else{

		//free(prevData);
		//prevData = NULL;
		//free(nowData);
		//nowData = NULL;
		//free(workData);
		//workData = NULL;

		OnBnClickedOk();
	}
	//EndDialog(IDCANCEL);
}


CString CFileListCreatorDlg::CurrentDirFunc(CString tempPath,BOOL LocalDirFLG){
    //'CurDir�͎g��Ȃ�
    if(tempPath == _T("")){
		return _T("");
	}
    
    //If Dir(tempPath) = "" Then
    //    CurrentDirFunc = ""
    //    Exit Function
    //End If

	BOOL ExistsFLG = FALSE;

	if(LocalDirFLG == TRUE){
		if ( PathFileExists(tempPath) ){
			// �t�@�C���͑��݂���
			ExistsFLG = TRUE;
		}
		else{
			// �t�@�C���͑��݂��Ȃ�
		}

		if ( PathIsDirectory(tempPath) ){
			// �f�B���N�g���͑��݂���
			ExistsFLG = TRUE;
		}
		else{
			// �f�B���N�g���͑��݂��Ȃ�
		}
	}else{
		ExistsFLG = TRUE;
	}

	int SearchIDX = 0;
	int i = 0;

	if(ExistsFLG == TRUE){
		for( i = tempPath.GetLength()-1; i >= 0; i--){
			SearchIDX = tempPath.Find(_T("\\"),i);
			if(SearchIDX >= 0){
				break;
			}
		}
		tempPath = tempPath.Left(SearchIDX);
		return tempPath;
	}

	return _T("");
}

//http://msdn.microsoft.com/ja-jp/library/scx99850(v=VS.100).aspx
void CFileListCreatorDlg::SearchFileRecurse(CString pstr)
{
   CFileFind finder;

   // build a string with wildcards
   CString strWildcard(pstr);
   strWildcard += _T("\\*.*");

   // start working for files
   BOOL bWorking = finder.FindFile(strWildcard);

   //if(pstr.Right(strWildcard.GetLength())!=_T("\\*.*")){
		//CFileListCreatorDlg::ListInsertItem(pstr);
   //}
   while (bWorking)
   {
      bWorking = finder.FindNextFile();
      // skip . and .. files; otherwise, we'd
	  // recur infinitely!
      if (finder.IsDots())
         continue;

		// if it's a directory, recursively search it

		if (finder.IsDirectory())
		 {
			CString str = finder.GetFilePath();
		 
			 //TRACE(_T("%s\n"), (LPCTSTR)str);
			SearchFileRecurse(str);
		}else{
			CString str = finder.GetFilePath();
			CFileListCreatorDlg::ListInsertItem(str);
		}
   }
   finder.Close();
}

BOOL CFileListCreatorDlg::isFileFLG(CString pstr,CString strFileSpec)
{
   CFileFind finder;

   // build a string with wildcards
   CString strWildcard(pstr);
   strWildcard += _T("\\") + strFileSpec;

   // start working for files
   BOOL bWorking = finder.FindFile(strWildcard);

   while (bWorking)
   {
      bWorking = finder.FindNextFile();
      // skip . and .. files; otherwise, we'd
      // recur infinitely!

      if (finder.IsDots())
         return FALSE;

		// if it's a directory, recursively search it

		if (finder.IsDirectory())
		 {
			return FALSE;
		 }
   }

   return TRUE;

   finder.Close();
}

BOOL CFileListCreatorDlg::isDirectoryFLG(CString pstr)
{
   CFileFind finder;

   // build a string with wildcards
   CString strWildcard(pstr);
   strWildcard += _T("\\*.*");

   // start working for files
   BOOL bWorking = finder.FindFile(strWildcard);


   while (bWorking)
   {
      bWorking = finder.FindNextFile();
      // skip . and .. files; otherwise, we'd
      // recur infinitely!

      if (finder.IsDots())
         return TRUE; //�f�B���N�g���Ƃ݂Ȃ�

		// if it's a directory, recursively search it

		if (finder.IsDirectory())
		 {
			return TRUE;
		 }
   }

   return FALSE;

   finder.Close();
}

//�f�B���N�g���ł��邩�ǂ����̊m�F
 static BOOL IsDirectory(const WIN32_FIND_DATA& wfd)
 {
	 //�Ⴄ
	 if(::_tcscmp(wfd.cFileName, TEXT(".")) == 0)
	 return FALSE;

	 //�Ⴄ
	 if(::_tcscmp(wfd.cFileName, TEXT("..")) == 0)
	 return FALSE;

	 //FILE_ATTRIBUTE_DIRECTORY�t���O������΃f�B���N�g��
	 return (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
 }

void CFileListCreatorDlg::MenuOpenBy_Func(int mySwitch){

	ESCAPE_FLG = FALSE;

	CFileListCreatorDlg::StatusStringSet(_T("�t�@�C���̃I�[�v���O�������s���Ă��܂�"),300,FALSE);

	CString FolderPath;
	CString FileName;
	int myCnt = 0;

	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		if(CFileListCreatorDlg::m_xcList.GetSelectedCount() < 1 && mySwitch != 3 ){
			CFileListCreatorDlg::StatusStringSet(_T("EasySelect �� �ԕ��� ���[�h��OFF�ɂ��܂���"),300,FALSE); //�ǉ� 2012.07.12

			m_xvChkEasySelect = FALSE;
			m_xvStrEasySelectMode = _T("�F�@������ ���ҏW");
			UpdateData(FALSE);
		
			m_xvChkRedOnMode = FALSE;
			m_xvStrRedOnMode = _T("�F�@�ԕ��� ���ҏW");

			UpdateData(FALSE);

			if (LastSelectedRow ==  -1){
				CFileListCreatorDlg::StatusStringSet(_T("�P�ȏ�̃t�@�C����I�����Ă�������"),300,TRUE);
				return;
			}else{
				m_xcList.SetItemState(LastSelectedRow,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
				LVIS_FOCUSED | LVIS_SELECTED,    // ���
				LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N
			}
		}

		int index = -1;
		CString str;
		CString AudioItems =_T("");

		while ((index = CFileListCreatorDlg::m_xcList.GetNextItem(index, LVNI_ALL | LVNI_SELECTED)) != -1)
		{
			//MSG msg; //�ǉ� 2011.10.12
			//if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
			//	if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
			//		if (msg.wParam == VK_ESCAPE){
			//			ESCAPE_FLG = TRUE;
			//			break; //�I���B���b�Z�[�W���[�v�𔲂���B
			//		}
			//	}
			//	TranslateMessage(&msg);
			//	DispatchMessage(&msg);
			//	//continue; //�t�@�C�����R�s�[����Ƃ��̓R�����g��
			//}
			//if (ESCAPE_FLG == TRUE) break;

			int matchPathCnt = 0;
			int matchFolderCnt = 0;

			CString FullPath;

			FullPath = CFileListCreatorDlg::m_xcList.GetItemText(index, 2);//�t���p�X�� 2�Ԗ�
			
			FileName = FullPathToFileName(FullPath);

			FolderPath = CurrentDirFunc(FullPath,TRUE);

			int w_index = index;

			if (FolderPath != _T("")){
				
				//int w_index = index;

				CString tempFullPath;
				CString tempFileName;
				CString tempFolderPath;

				while ((w_index = CFileListCreatorDlg::m_xcList.GetNextItem(w_index, LVNI_ALL | LVNI_SELECTED)) != -1){
					//MSG msg; //�ǉ� 2011.10.12
					//if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
					//	if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					//		if (msg.wParam == VK_ESCAPE){
					//			ESCAPE_FLG = TRUE;
					//			break; //�I���B���b�Z�[�W���[�v�𔲂���B
					//		}
					//	}
					//	TranslateMessage(&msg);
					//	DispatchMessage(&msg);
					//	//continue; //�t�@�C�����R�s�[����Ƃ��̓R�����g��
					//}
					///if (ESCAPE_FLG == TRUE) break;

					tempFullPath = CFileListCreatorDlg::m_xcList.GetItemText(w_index, 2);
					tempFileName = FullPathToFileName(tempFullPath);
					tempFolderPath = CurrentDirFunc(tempFullPath,TRUE);//�t���p�X�� 2�Ԗ�

					if(w_index != index){
						if((FolderPath == tempFolderPath) && mySwitch != 3){
							matchFolderCnt++;
							//break;
						}
						if((FullPath == tempFullPath) && mySwitch == 3){
							matchPathCnt++;
							//break;
						}
					}
				}
				//AudioItems.Left(AudioItems.GetLength()-1);
				
						switch(mySwitch){
							case 1:
								if (matchFolderCnt == 0){
									if(FolderPath !=_T("")){
				
										FolderPath.Replace(_T("\\"),_T("\\\\"));
										//http://oshiete.goo.ne.jp/qa/976818.html
									}

									if(FullPath.Right(1)!=_T("\\")){
										//���G�N�X�v���[���ŊJ��
										//ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), _T("/select,"+ FileName) , FolderPath , SW_SHOWNORMAL );

										SetCurrentDirectory(FolderPath); //�K�v 2012.06,22
										//���G�N�X�v���[���ŊJ��
										ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), _T("/select,.\\" + FileName) , FolderPath, SW_SHOWNORMAL );
									}else{
										ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), FullPath , NULL , SW_SHOWNORMAL );
									}
								}
								break;
							case 2:
								if (matchFolderCnt == 0){
									if(FolderPath !=_T("")){
				
										FolderPath.Replace(_T("\\"),_T("\\\\"));
										//http://oshiete.goo.ne.jp/qa/976818.html
									}
									if(FullPath.Right(1)!=_T("\\")){
										//���֘A�t����ꂽ�v���O�����ŊJ��
										ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), FileName , FolderPath , SW_SHOWNORMAL );
									}else{									
										ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), FullPath , NULL , SW_SHOWNORMAL );
									}
									//http://dobon.net/vb/dotnet/process/openexplore.html
									//}
								}
								break;
							case 3: //�����f�B�A�v���C���ŊJ��
								if (matchPathCnt == 0){
									if(FullPath.Right(1)!=_T("\\")){
										if (myStrToLower_Func(FullPath.Right(4)) == _T(".m3u")){
											AudioItems = ReadOrWritePlayList_Func(_T("m3u_read"),FullPath,AudioItems,FullPathToFileName(FullPath)); //�ύX 2012.07.12
										}else if (myStrToLower_Func(FullPath.Right(4)) == _T(".wpl")){
											ReadOrWritePlayList_Func(_T("wpl_write"),FullPath,AudioItems,FullPathToFileName(FullPath));
											AudioItems = ReadOrWritePlayList_Func(_T("wpl_read"),FullPath,AudioItems,FullPathToFileName(FullPath));
										}else{
											AudioItems +=_T(" \"") + FullPath + _T("\"");
											//AudioItems = ReadOrWritePlayList_Func(_T("m3u_read"),FullPath,AudioItems,_T(""));
										}
									}else{
										//��ō쐬
										AudioItems += inFolder_AllFile(FullPath,_T("*.mp3"),_T(""));
										AudioItems += inFolder_AllFile(FullPath,_T("*.wma"),_T(""));
										AudioItems += inFolder_AllFile(FullPath,_T("*.wav"),_T(""));

										AudioItems += inFolder_AllFile(FullPath,_T("*.mpg"),_T(""));
										AudioItems += inFolder_AllFile(FullPath,_T("*.mpeg"),_T(""));
										AudioItems += inFolder_AllFile(FullPath,_T("*.wmv"),_T(""));
										AudioItems += inFolder_AllFile(FullPath,_T("*.asf"),_T(""));
										AudioItems += inFolder_AllFile(FullPath,_T("*.avi"),_T(""));

										//AudioItems = ReadOrWritePlayList_Func(_T("m3u_read"),FullPath,AudioItems,_T(""));
									}
									//AudioItems.Replace(_T("\\"),_T("\\\\"));
								}
								break;
							case 4:
								//if (matchFolderCnt == 0){
									if(FolderPath !=_T("")){
				
										FolderPath.Replace(_T("\\"),_T("\\\\"));
										//http://oshiete.goo.ne.jp/qa/976818.html
									}

									if(FileName.Right(4)==_T(".lnk")){
										//��Link�t�@�C�����J���i�֘A�t����ꂽ�v���O�����ŊJ���j
										ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), FileName , FolderPath , SW_SHOWNORMAL );
										//http://dobon.net/vb/dotnet/process/openexplore.html									
									}else if(FullPath.Right(1)==_T("\\")){
										ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), FullPath , NULL , SW_SHOWNORMAL );
									}
								//}
								break;
							default:
								break;					
						}
				
				}
					
			}
			if(mySwitch == 3){
				//MessageBox(AudioItems);
				//�����f�B�A�v���C���ŊJ��
				//CString tempCurDir;

				//tempCurDir = GetCurrentDirectory();  //�K�v


				ReadOrWritePlayList_Func(_T("m3u_write"),_T(""),AudioItems,_T("temp.flc"));
				CString m3uFile = _T("");
				
				m3uFile = _T("\"") + ReadOrWritePlayList_Func(_T("m3u_read_temp"),_T(""),AudioItems,_T("temp.flc.m3u")) + _T("\"");

				//DWORD GetFullPathName(
				//	LPCTSTR FileName,
				//	DWORD PathNameSize,
				//	LPTSTR PathName,
				//	LPTSTR *FilePart);

				//SetCurrentDirectory(_T("C:\\"));  //�ǉ� 2012.06.21

				//ShellExecute( NULL, _T("open"), _T("C:/Program Files/Windows Media Player/wmplayer.exe"), _T("\"") + FolderPath + _T("\\") + FileName + _T("\"") , NULL , SW_SHOWNORMAL );
				ShellExecute( NULL, _T("open"), _T("C:\\Program Files\\Windows Media Player\\wmplayer.exe"), m3uFile , NULL , SW_SHOWNORMAL );
				//http://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q1352351333
				//ShellExecute(
				//	NULL,
				//	"open",
				//	fullpass,
				//	"C:/Program Files/Windows Media Player/wmplayer.exe",
				//	NULL,
				//	SW_SHOW
				//	);
			
				//http://www.sm.rim.or.jp/~shishido/cprocess.html

	/*			PROCESS_INFORMATION pi;
				STARTUPINFO si;

				ZeroMemory(&si,sizeof(si));
				si.cb=sizeof(si);

				LPTSTR progPath = new TCHAR[MAX_PATH + 1];
				ZeroMemory(progPath,sizeof(TCHAR)*MAX_PATH + 1);

				_tcscpy(progPath,_T("C:\\Program Files\\Windows Media Player\\wmplayer.exe"));

				CreateProcess(NULL,progPath,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,
				NULL,NULL,&si,&pi);*/

				//MessageBox(m3uFile);
				//DeleteFile(m3uFile);

				if (IDYES==MessageBox(_T("�v���C���X�g��ۑ����܂����H"),_T("�v���C���X�g�ۑ�"), MB_YESNOCANCEL )){			
					////���[�_���X�P
					//CDialog *m_pDlg;
					//m_pDlg = new DateFilterDlg(this);
					//m_pDlg->Create(IDD_DIALOG_InputBox);

					//m_pDlg->ShowWindow(true);

					//���[�_��
					InputBoxDlg m_dlg;
					//m_dlg.DoModal();

					//FileName = InputBox("�t�@�C���ɖ��O�����ĉ������B", "���O�����ĕۑ�", CreateDateTime)

					if (m_dlg.DoModal()==IDOK){
						FileName = _T("");
						FileName = m_dlg.ExportFileName;
					}else{
						FileName = _T("");
					}
					if (FileName != _T("")){
						ReadOrWritePlayList_Func(_T("m3u_write"),_T(""),AudioItems,FileName);
					}

					CFileListCreatorDlg::StatusStringSet(_T("�v���C���X�g��ۑ����܂���"),300,TRUE);
					return;
				}
			}
		myCnt++;
	}

	switch(mySwitch){
		case 1:
			CFileListCreatorDlg::StatusStringSet(_T("�t�@�C���̃I�[�v�������s���܂��� \r\n (���΂炭���҂�������)"),300,FALSE);
			break;
		case 2:
			CFileListCreatorDlg::StatusStringSet(_T("�t�@�C���̃I�[�v�������s���܂��� \r\n (�����̉��y�t�@�C�����J���ꍇ�́A�u���f�B�A�v���C���[����J���v�����s���ĉ�����)"),300,FALSE);
			break;
		case 3:
			CFileListCreatorDlg::StatusStringSet(_T("�t�@�C���̃I�[�v�������s���܂��� \r\n (���f�B�A�v���C���[���N�����܂�)"),300,FALSE);
			break;
		case 4:
			CFileListCreatorDlg::StatusStringSet(_T("�t�@�C���̃I�[�v�������s���܂��� \r\n (�����N�t�@�C���̂݊J���܂�)"),300,FALSE);
			break;
		default:
			break;					
	}
	
	
	if(myCnt == 0) {
		CFileListCreatorDlg::StatusStringSet(_T("�A�C�e����I�����Ă�������"),300,TRUE);
	}else{
		//���֘A�t����ꂽ�v���O�����ŊJ��
		//CString FileName;	
	}
}


void CFileListCreatorDlg::OnMenuOpenbyexplorer()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	MenuOpenBy_Func(1);
}


void CFileListCreatorDlg::OnOpenbyConnectedapplication()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	MenuOpenBy_Func(2);
}


void CFileListCreatorDlg::OnOpenExplorer()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	MenuOpenBy_Func(1);
}


void CFileListCreatorDlg::OnMenuPlaySelectedMusic()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	MenuOpenBy_Func(3);
}


void CFileListCreatorDlg::OnOpenbyMediaplayer()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	MenuOpenBy_Func(3);
}


void CFileListCreatorDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	
	ESCAPE_FLG = FALSE;

	CFileListCreatorDlg::GetStrFormat_Func();

	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	CDialogEx::OnDropFiles(hDropInfo);
	//http://mailsrv.nara-edu.ac.jp/~asait/visual_cpp/dialog2/drop/drop.htm

	CFileListCreatorDlg::StatusStringSet(_T("���X�g�Ƀh���b�O�����A�C�e�����������ł�"),300,FALSE);

    TCHAR FileName[_MAX_PATH];
    int NameSize = sizeof(FileName);
    int FileNumber;
    CString str;
    int i;

    FileNumber = ::DragQueryFile(hDropInfo, 0xffffffff, FileName, NameSize);
    //str.Format(_T("�h���b�v���ꂽ�t�@�C���̐� =%d"), FileNumber);
    //AfxMessageBox(str);
		
	TotalItemsCount = 0;
	DoWithCnt = 0;

	ULONGLONG tempCnt;
	tempCnt = 0;

	int myResult;
	myResult = IDNO;
	
	BOOL FileOnlyFLG = TRUE;

	for(i=0; i<FileNumber; i++){
		DragQueryFile(hDropInfo, i, FileName, NameSize);
		if( CFileListCreatorDlg::isFileFLG(FileName,_T("*.*"))==TRUE ){

		}else{
			FileOnlyFLG = FALSE;
		}
	}

	if (FileOnlyFLG == FALSE) {
		str.Format(_T("%d �̃A�C�e�� (�t�H���_��t�@�C��) ���h���b�v����܂����B�t�H���_�ɑ΂��Ă̓����I�����ĉ������B\r\n\r\n�u�͂��v�t�@�C���̎�ނȂǂōi�荞�݂܂��B\r\n�u�������v�h���b�v���ꂽ�t�H���_�̒��g�����ׂă��X�g�Ɏ�荞�݂܂��B"), FileNumber);
		myResult = MessageBox(str ,_T("��荞�݊m�F"), MB_YESNOCANCEL );
	}

	CFileSpecsDlg m_dlg;

	int importFileResult = IDNO;
	SkipFLG = FALSE;

	if(myResult	== IDYES){
		//���[�_��
		m_dlg.DoModal();
		if(m_dlg.TargetFileSpecs == _T("")){
			CFileListCreatorDlg::StatusStringSet(_T("FileSpecsDlg : ���[�U�[�ɂ��L�����Z��"),300,TRUE);
			return;
		}

		if(m_dlg.TargetFileSpecs == _T("<<error>>")){
			CFileListCreatorDlg::StatusStringSet(_T("FileSpecsDlg : �������`���Ō����Ώۂ��w�肵�Ă�������"),300,TRUE);
			return;
		}
	//--------------------------------------------------------------------------------------------
		CFileListCreatorDlg::StatusStringSet(_T("HTML �C���|�[�g�ΏۃA�C�e�� �J�E���g��"),0,FALSE);
		//ULONGLONG TotalItemsCount;
		//TotalItemsCount = 0;

		for(i=0; i<FileNumber; i++){
			DragQueryFile(hDropInfo, i, FileName, NameSize);
			//ULONGLONG tempCnt;
			tempCnt = 0;

			tempCnt = CFileListCreatorDlg::FileListItemsCount(FileName);
			if( tempCnt == 0 ){
				//TotalItemsCount ++;
			}else{
				TotalItemsCount = TotalItemsCount + tempCnt;
			}
		}
		//TotalItemsCount = TotalItemsCount / 2;
		//CFileListCreatorDlg::StatusStringSet(_T("HTML �C���|�[�g�ΏۃA�C�e�� �J�E���g�I��"),0,FALSE);
	//--------------------------------------------------------------------------------------------
		for(i=0; i<FileNumber; i++){
			DragQueryFile(hDropInfo, i, FileName, NameSize);
			if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE)== 1 && SkipFLG == FALSE){
				importFileResult = MessageBox(_T("�������̃��X�g�t�@�C�������o����܂����B�C���|�[�g���s���A���X�g��W�J���܂����H"),_T("�C���|�[�g�m�F"), MB_YESNOCANCEL );
				SkipFLG = TRUE;
			}

			if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE) == 1 && importFileResult == IDYES) {
				CFileListCreatorDlg::importFileList_Func(FileName,FALSE);
			}else if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE) == 0){
				CFileListCreatorDlg::PackageSearch_Func(FileName,m_dlg.TargetFileSpecs);
			}else if (importFileResult !=IDYES ){
				CFileListCreatorDlg::PackageSearch_Func(FileName,_T("*.*;"));  //; ��Y�ꂸ��
			}
		}
	}else if(myResult == IDNO){
		//m_dlg.DoModal();
		////--------------------------------------------------------------------------------------------
			CFileListCreatorDlg::StatusStringSet(_T("HTML �C���|�[�g�ΏۃA�C�e�� �J�E���g��"),0,FALSE);
			//TotalItemsCount = 0;

			for(i=0; i<FileNumber; i++){
				DragQueryFile(hDropInfo, i, FileName, NameSize);
				//ULONGLONG tempCnt;
				tempCnt = 0;

				tempCnt = CFileListCreatorDlg::FileListItemsCount(FileName);
				if( tempCnt == 0 ){
					//TotalItemsCount++;
				}else{
					TotalItemsCount = TotalItemsCount + tempCnt;
				}
			}
			//TotalItemsCount = TotalItemsCount / 2;
		//	CFileListCreatorDlg::StatusStringSet(_T("HTML �C���|�[�g�ΏۃA�C�e�� �J�E���g�I��"),0,FALSE);
		//--------------------------------------------------------------------------------------------
		for(i=0; i<FileNumber; i++){
			DragQueryFile(hDropInfo, i, FileName, NameSize);

			if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE)== 1 && SkipFLG == FALSE){
				importFileResult = MessageBox(_T("�������̃��X�g�t�@�C�������o����܂����B�C���|�[�g���s���A���X�g��W�J���܂����H"),_T("�C���|�[�g�m�F"), MB_YESNOCANCEL );
				SkipFLG = TRUE;
			}

			if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE) == 1 && importFileResult == IDYES) {
				CFileListCreatorDlg::importFileList_Func(FileName,FALSE);
			}else if (CFileListCreatorDlg::importFileList_Func(FileName,TRUE) == 0){
				CFileListCreatorDlg::PackageSearch_Func(FileName,_T("*.*;"));
			}else if (importFileResult !=IDYES ){
				CFileListCreatorDlg::PackageSearch_Func(FileName,_T("*.*;"));  //; ��Y�ꂸ��
			}
			//AfxMessageBox(FileName);
		}
	}else if(myResult == IDCANCEL){
		CFileListCreatorDlg::StatusStringSet(_T("����̓L�����Z������܂���"),300,TRUE);
		return;
	}

	str.Format(_T("%d �̃A�C�e�� (�t�H���_��t�@�C��) ���h���b�v"), FileNumber);
	CFileListCreatorDlg::StatusStringSet(str,300,TRUE);

	CFileListCreatorDlg::SetStrFormat_Func();

	CFileListCreatorDlg::Total_Bytes_Bold();
	CFileListCreatorDlg::Total_Bytes_Func();
	CFileListCreatorDlg::ItemCount_Func(FALSE);

	if (FileNumber>=1){
		ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

		CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

		if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
			return;
		}

		if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
			m_Dlg->SetWindowText(_T("FileListCreator (*)"));
			SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24
		}
	}

	delete m_dlg;
	//CFileListCreatorDlg::StatusStringSet(_T("PackageSearch �I��"),300,TRUE);

    ::DragFinish( hDropInfo );
    //CFrameWnd::OnDropFiles(hDropInfo);
}


void CFileListCreatorDlg::OnMenuSelectall()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	SelectALL_Func();
}


void CFileListCreatorDlg::OnEditlistSelectall()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	SelectALL_Func();
}


void CFileListCreatorDlg::OnEditDelfiletype()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	DEL_FileType_Func();
}


void CFileListCreatorDlg::OnMenuDelFiletype()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	DEL_FileType_Func();
}


void CFileListCreatorDlg::OnMenuRestoreListInformation()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	OnBnClickedBtnRestore();
}


void CFileListCreatorDlg::OnEditlistAdddirstr()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	AddDirectorySTR_Func();
}


void CFileListCreatorDlg::OnMenuAdddirectorystr()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	AddDirectorySTR_Func();
}


void CFileListCreatorDlg::OnOptionVersion()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


HBRUSH CFileListCreatorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ������ DC �̑�����ύX���Ă��������B

	//http://soheeya.net/programming/vctips/control_static.html
    //���@�@
    if(pWnd->m_hWnd == GetDlgItem(IDC_STATIC_DRAG_ON_ME)->m_hWnd){
        pDC->SetBkColor(RGB(255, 255, 255));
        pDC->SetTextColor(RGB(100, 100, 100));
    }

	// TODO:  ����l���g�p�������Ȃ��ꍇ�͕ʂ̃u���V��Ԃ��܂��B
	return hbr;
}


void CFileListCreatorDlg::OnSortSortitemsbyfilename()
{
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		CFileListCreatorDlg::GetStrFormat_Func();

		LastPrevItemCount = m_xcList.GetItemCount();
		CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

		StatusStringSet(_T("Sort ���s��"),0,FALSE); //�ύX 2012.06.14
		RenumberItem();				// SortItems�֐����Ăяo���O�ɂ͕K�����s

		keyColumn = 3; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������
		static BOOL bSort = FALSE;			// static�Œ�`���邱��
		m_xcList.SortItems(CompareFunc, bSort);

		if (bSort == FALSE) { 
			CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�t�@�C���� �~��)"),300,TRUE);
		}else{
			CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�t�@�C���� ����)"),300,TRUE);
		}
		SortColumnDrawCaption(keyColumn, bSort);
		bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���

		CFileListCreatorDlg::SortEnsureVisible_Func();

		CFileListCreatorDlg::SetStrFormat_Func();
	}

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}
}


void CFileListCreatorDlg::OnSortSortitemsbydatasize()
{
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		CFileListCreatorDlg::GetStrFormat_Func();

		LastPrevItemCount = m_xcList.GetItemCount();
		CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

		StatusStringSet(_T("Sort ���s��"),0,FALSE); //�ύX 2012.06.14
		RenumberItem();				// SortItems�֐����Ăяo���O�ɂ͕K�����s

		keyColumn = 5; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������ // �f�[�^�T�C�Y��4�ɂ���
		static BOOL bSort = FALSE;			// static�Œ�`���邱��
		m_xcList.SortItems(CompareFunc, bSort);

		if (bSort == FALSE) { 
			CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�f�[�^�T�C�Y ����)"),300,TRUE);
		}else{
			CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�f�[�^�T�C�Y �~��)"),300,TRUE);
		}
		SortColumnDrawCaption(4, bSort); //�ύX 2012.05.24
		bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���

		CFileListCreatorDlg::SortEnsureVisible_Func();

		CFileListCreatorDlg::SetStrFormat_Func();
	}

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}
}


void CFileListCreatorDlg::OnSortSortitemsbydate()
{
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		CFileListCreatorDlg::GetStrFormat_Func();

		LastPrevItemCount = m_xcList.GetItemCount();
		CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

		StatusStringSet(_T("Sort ���s��"),0,FALSE); //�ύX 2012.06.14
		RenumberItem();				// SortItems�֐����Ăяo���O�ɂ͕K�����s

		keyColumn = 7; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������
		static BOOL bSort = FALSE;			// static�Œ�`���邱��
		m_xcList.SortItems(CompareFunc, bSort);

		if (bSort == FALSE) { 
			CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�C���� ����)"),300,TRUE);
		}else{
			CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�C���� �~��)"),300,TRUE);
		}
		SortColumnDrawCaption(6, bSort); //�ύX 2012.05.24
		bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���

		CFileListCreatorDlg::SortEnsureVisible_Func();

		CFileListCreatorDlg::SetStrFormat_Func();
	}

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}
}


void CFileListCreatorDlg::OnSortSortitemsbypathname()
{
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		CFileListCreatorDlg::GetStrFormat_Func();

		LastPrevItemCount = m_xcList.GetItemCount();
		CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

		StatusStringSet(_T("Sort ���s��"),0,FALSE); //�ύX 2012.06.14
		RenumberItem();				// SortItems�֐����Ăяo���O�ɂ͕K�����s

		keyColumn = 2; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������
		static BOOL bSort = FALSE;			// static�Œ�`���邱��
		m_xcList.SortItems(CompareFunc, bSort);

		if (bSort == FALSE) { 
			CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�t�@�C���p�X ����)"),300,TRUE);
		}else{
			CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�t�@�C���p�X �~��)"),300,TRUE);
		}
		SortColumnDrawCaption(keyColumn, bSort);
		bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���

		CFileListCreatorDlg::SortEnsureVisible_Func();

		CFileListCreatorDlg::SetStrFormat_Func();
	}

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
		//SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24 //�R�����g�� 2012.05.25
	}
}


void CFileListCreatorDlg::OnSortSortitemsbyrepetitionnum()
{
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		CFileListCreatorDlg::GetStrFormat_Func();

		LastPrevItemCount = m_xcList.GetItemCount();
		CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

		StatusStringSet(_T("Sort ���s��"),0,FALSE); //�ύX 2012.06.14
		RenumberItem();				// SortItems�֐����Ăяo���O�ɂ͕K�����s

		keyColumn = 0; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������ // �f�[�^�T�C�Y��4�ɂ���
		static BOOL bSort = TRUE;			// static�Œ�`���邱�� //�d���i���o�[�������悤�ɏ�ɂs�q�t�d
		m_xcList.SortItems(CompareFunc, bSort);

		if (bSort == FALSE) { 
			CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�d���A�C�e�� ����)"),300,TRUE);
		}else{
			CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�d���A�C�e�� �~��)"),300,TRUE);
		}
		SortColumnDrawCaption(keyColumn, bSort);
		//bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���

		CFileListCreatorDlg::SortEnsureVisible_Func();

		CFileListCreatorDlg::SetStrFormat_Func();
	}

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}
}


void CFileListCreatorDlg::OnEditlistSetSequentialNum()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	SetSEQ_NUM_Func(TRUE);

}


void CFileListCreatorDlg::OnOpenbyLinkfileopen()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	MenuOpenBy_Func(4);
}


void CFileListCreatorDlg::OnBnClickedChkEasyselect()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	//LastPrevItemCount = m_xcList.GetItemCount();
	//CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	if (m_xvChkEasySelect == FALSE){
		m_xvChkEasySelect = TRUE;

		::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
		::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

		CFileListCreatorDlg::StatusStringSet(_T("���݂̃��X�g�̒����瑾�����ɂ����A�C�e������̃t�H���_�ɃR�s�[���܂� \r\n (�A�C�e�����N���b�N���đ������ɂ��ĉ�����)"),300,TRUE);
		m_xvStrEasySelectMode = _T("�F�@�������I�����[�h");
		UpdateData(FALSE);


		CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_EditCellMode);
		//�`�F�b�N���O��
		chkbox1->SetCheck(0);
		m_xvChkEditCellMode = FALSE;

		m_xvStrEditCellMode = _T("�F�@�ʏ탂�[�h");
		UpdateData(FALSE);	

		if(m_xcList.GetSelectedCount() > 1){
			int myCnt = 0;
			int index = -1;
			while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
				(index, LVNI_ALL | LVNI_SELECTED)) != -1)
			{
				int FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

				if(FormatDataNum == 11){
					//FormatDataStr = _T("NORMAL,BLACK,");
					FormatDataNum = 12;
				}

				if(FormatDataNum == 12){
					//FormatDataStr = _T("BOLD,BLACK,");

				}
		
				if(FormatDataNum == 21){
					//FormatDataStr = _T("NORMAL,RED,");
					FormatDataNum = 22;
				}

				if(FormatDataNum == 22){
					//FormatDataStr = _T("BOLD,RED,");
				}

				CFileListCreatorDlg::m_xcList.SetItemData(index,FormatDataNum);
				//ListView_Update(m_xcList, index);

				m_xcList.SetItemState(index,     // ��t�H�[�J�X����I����Ԃɂ������A�C�e���̃C���f�b�N�X
				!LVIS_FOCUSED | !LVIS_SELECTED,    // ���
				LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N

				myCnt++;
			}



			CString tempCnt;
			tempCnt = _T("");
			if(myCnt>=1){ //�ǉ� 2012.06.14
				tempCnt.Format(_T("%d"),myCnt);
				tempCnt=tempCnt + _T(" ���̃A�C�e���ɑ�����(�������)���Z�b�g���܂���");
			}else{
				tempCnt=tempCnt + _T("�A�C�e�����I������Ă��Ȃ����߁A������(�������)���Z�b�g�ł��܂���");
			}
			CFileListCreatorDlg::StatusStringSet(tempCnt,300,TRUE);

			CFileListCreatorDlg::Total_Bytes_Bold(); //�ǉ� 2012.07.11 //�d�v BoldItem��2�d�ɃJ�E���g�����ꍇ�����邪�A�t�H�[�J�X���͂����Ă���̂Ŗ��Ȃ�
			CFileListCreatorDlg::Total_Bytes_Func(); //�ǉ� 2012.07.11
			CFileListCreatorDlg::ItemCount_Func(FALSE); //�ǉ� 2012.07.11
		}
	}else{
		m_xvChkEasySelect = FALSE;

		CFileListCreatorDlg::StatusStringSet(_T("EasySelect ���[�h��OFF�ɂ��܂��� �� Copy�@�\�����s���Ă�������"),300,FALSE);
		m_xvStrEasySelectMode = _T("�F�@������ ���ҏW");
		UpdateData(FALSE);	
	}

	//UpdateWindow();
	RedrawWindow();

}


void CFileListCreatorDlg::OnCopyEasyselect()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}
	m_xvChkEasySelect = TRUE;

	CFileListCreatorDlg::StatusStringSet(_T("���݂̃��X�g�̒����瑾�����ɂ����A�C�e������̃t�H���_�ɃR�s�[���܂� \r\n (�A�C�e�����N���b�N���đ������ɂ��ĉ�����)"),300,TRUE);
	m_xvStrEasySelectMode = _T("�F�@�������I�����[�h");
	UpdateData(FALSE);
}


void CFileListCreatorDlg::OnCopyEasyselectoff()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}
	m_xvChkEasySelect = FALSE;

	CFileListCreatorDlg::StatusStringSet(_T("EasySelect ���[�h��OFF�ɂ��܂��� �� Copy�@�\�����s���Ă�������"),300,FALSE);
	m_xvStrEasySelectMode = _T("�F�@������ ���ҏW");
	UpdateData(FALSE);
}


void CFileListCreatorDlg::OnMenuEmphasisbybold()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	if( CFileListCreatorDlg::m_xcList.GetItemCount() <=0){
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

    int        index = -1;
    CString    str;

	int myCnt = 0;

    while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
        (index, LVNI_ALL | LVNI_SELECTED)) != -1)
    {

		myCnt++;
    }
	
	int myResult;
	CString tempCnt;

	if(myCnt==0){
		myResult = MessageBox(_T("���ׂẴA�C�e���ɑ�����(�������)���Z�b�g���܂����H"),_T("Selected Items To Bold"),MB_YESNOCANCEL);
		if(myResult == IDYES){
			UpdateData(FALSE);
			index = 0;
			while(index < CFileListCreatorDlg::m_xcList.GetItemCount())
			{
				int FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

				if(FormatDataNum == 11){
					//FormatDataStr = _T("NORMAL,BLACK,");
					FormatDataNum = 12;
				}

				if(FormatDataNum == 12){
					//FormatDataStr = _T("BOLD,BLACK,");

				}
		
				if(FormatDataNum == 21){
					//FormatDataStr = _T("NORMAL,RED,");
					FormatDataNum = 22;
				}

				if(FormatDataNum == 22){
					//FormatDataStr = _T("BOLD,RED,");
				}

				CFileListCreatorDlg::m_xcList.SetItemData(index,FormatDataNum);

				//ListView_Update(m_xcList, index); //�R�����g�� 2012.06.15
				index++;
			}
			CFileListCreatorDlg::StatusStringSet(_T("���ׂĂɃA�C�e���̑�����(�������)�ɃZ�b�g���܂���"),300,TRUE);

		}
	}else if(myCnt>=1){
		//myResult = MessageBox(_T("���ݑI������Ă���A�C�e���̑�����(�������)�ɃZ�b�g���܂����H"),_T(Selected Items To Bold"),MB_YESNOCANCEL);
		//myResult == IDYES;
		//if(myResult == IDYES){
			//m_xvChkEasySelect = TRUE;
			//g_ChkCopyOn = TRUE;
			//m_xvStrEasySelectMode = _T("�F�@�������I�����[�h");
			//UpdateData(FALSE);


			//CFileListCreatorDlg::GetStrFormat_Func();

			int myCnt = 0;
			index = -1;
			while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
			    (index, LVNI_ALL | LVNI_SELECTED)) != -1)
			{
				int FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

				if(FormatDataNum == 11){
					//FormatDataStr = _T("NORMAL,BLACK,");
					FormatDataNum = 12;
				}

				if(FormatDataNum == 12){
					//FormatDataStr = _T("BOLD,BLACK,");

				}
		
				if(FormatDataNum == 21){
					//FormatDataStr = _T("NORMAL,RED,");
					FormatDataNum = 22;
				}

				if(FormatDataNum == 22){
					//FormatDataStr = _T("BOLD,RED,");
				}

				CFileListCreatorDlg::m_xcList.SetItemData(index,FormatDataNum);
				//ListView_Update(m_xcList, index);
				myCnt++;
			}

			//CString tempCnt;
			tempCnt = _T("");
			if(myCnt>=1){ //�ǉ� 2012.06.14
				tempCnt.Format(_T("%d"),myCnt);
				tempCnt=tempCnt + _T(" ���̃A�C�e���ɑ�����(�������)���Z�b�g���܂���");
			}else{
				tempCnt=tempCnt + _T("�A�C�e�����I������Ă��Ȃ����߁A������(�������)���Z�b�g�ł��܂���");
			}
			CFileListCreatorDlg::StatusStringSet(tempCnt,300,TRUE);
			//CFileListCreatorDlg::SetStrFormat_Func();
		//}else if(myResult == IDNO){

		//}
	}

		m_xvChkRedOnMode = FALSE;
		m_xvStrRedOnMode = _T("�F�@�ԕ��� ���ҏW");
		UpdateData(FALSE);	

		m_xvChkEasySelect = FALSE;
		m_xvStrEasySelectMode = _T("�F�@������ ���ҏW");
		UpdateData(FALSE);

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}

	//m_Dlg->Total_Bytes_Bold(); //�d�v //�R�����g�� 2012.07.12
	//m_Dlg->Total_Bytes_Func();
	//m_Dlg->ItemCount_Func(FALSE);

	//http://oshiete.goo.ne.jp/qa/112210.html
	//::InvalidateRect(0,0,false); //��ʑS�̂ɍĕ`���v��
	//http://oshiete.goo.ne.jp/qa/200500.html
	//SendMessage(editBox, WM_KILLFOCUS, 0, 0L);

}


void CFileListCreatorDlg::OnMenuEmphasizedFormatCancellation()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if( CFileListCreatorDlg::m_xcList.GetItemCount() <=0){
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

    int        index = -1;
    CString    str;

	int myCnt = 0;

    while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
        (index, LVNI_ALL | LVNI_SELECTED)) != -1)
    {

		myCnt++;
    }
	
	int myResult;
	CString tempCnt;

	if(myCnt==0){
		myResult = MessageBox(_T("���ׂĂ̐ԐF�E������(�������)���������܂����H"),_T("Emphasized Format Cancellation"),MB_YESNOCANCEL);
		if(myResult == IDYES){
			m_xvChkEasySelect = FALSE;
			m_xvChkRedOnMode = FALSE;

			m_xvStrEasySelectMode = _T("�F�@������ ���ҏW");
			m_xvStrRedOnMode = _T("�F�@�ԕ��� ���ҏW");
			UpdateData(FALSE);
			index = 0;
			while(index < CFileListCreatorDlg::m_xcList.GetItemCount())
			{
				CFileListCreatorDlg::m_xcList.SetItemData(index,11);
				//ListView_Update(m_xcList, index); //�R�����g�� 2012.05.31 //XP�΍�
				index++;
			}
			CFileListCreatorDlg::StatusStringSet(_T("���ׂĂ̐ԐF�E������ (�������) ���������܂���"),300,TRUE);

		}
	}else if(myCnt>=1){
		//myResult = MessageBox(_T("���ݑI������Ă���A�C�e���̐ԐF�E������(�������)���������܂����H"),_T("Emphasized Format Cancellation"),MB_YESNOCANCEL);
		//myResult == IDYES;
		//if(myResult == IDYES){
			m_xvChkEasySelect = FALSE;
			m_xvChkRedOnMode = FALSE;

			m_xvStrEasySelectMode = _T("�F�@������ ���ҏW");
			m_xvStrRedOnMode = _T("�F�@�ԕ��� ���ҏW");

			int myCnt = 0;
			index = -1;
			while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
			    (index, LVNI_ALL | LVNI_SELECTED)) != -1)
			{
				CFileListCreatorDlg::m_xcList.SetItemData(index,11);
				//ListView_Update(m_xcList, index); //�R�����g�� 2012.05.31 //XP�΍�
				myCnt++;
			}

			//CString tempCnt;
			tempCnt = _T("");
			if(myCnt>=1){ //�ǉ� 2012.06.14
				tempCnt.Format(_T("%d"),myCnt);
				tempCnt=tempCnt + _T(" ���̃A�C�e���̐ԐF�E������ (�������) ���������܂���");
			}else{
				tempCnt=_T("�A�C�e�����I������Ă��Ȃ����߁A�ԐF�E������ (�������) �������ł��܂���");
			}
			CFileListCreatorDlg::StatusStringSet(tempCnt,300,TRUE);

		//}else if(myResult == IDNO){

		//}
	}

	Total_Bytes_Bold();
	Total_Bytes_Func();
	ItemCount_Func(FALSE);

	RedrawWindow(); //�ǉ� 2012.05.31 //XP�΍�

	CFileListCreatorDlg::Total_Bytes_Bold();


	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}
	//UpdateWindow();
}


void CFileListCreatorDlg::OnEditselecteditemBold()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	CFileListCreatorDlg::OnMenuEmphasisbybold();
}


void CFileListCreatorDlg::OnBnClickedChkRedonmode()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	//LastPrevItemCount = m_xcList.GetItemCount();
	//CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	if (m_xvChkRedOnMode == FALSE){
		m_xvChkRedOnMode = TRUE;
		CFileListCreatorDlg::StatusStringSet(_T("�A�C�e�����N���b�N���Đԕ����ɂ��ĉ�����)"),300,TRUE);
		m_xvStrRedOnMode = _T("�F�@�ԕ������[�h");

		CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_EditCellMode);
		//�`�F�b�N���O��
		chkbox1->SetCheck(0);
		m_xvChkEditCellMode = FALSE;

		::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
		::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);

		m_xvStrEditCellMode = _T("�F�@�ʏ탂�[�h");
		UpdateData(FALSE);	

		UpdateData(FALSE);
	}else{
		m_xvChkRedOnMode = FALSE;
		CFileListCreatorDlg::StatusStringSet(_T("�ԕ������[�h��OFF�ɂ��܂��� �� Copy�@�\�����s���Ă�������"),300,FALSE);
		m_xvStrRedOnMode = _T("�F�@�ԕ��� ���ҏW");

		UpdateData(FALSE);	
	}
	RedrawWindow();
}

void CFileListCreatorDlg::GetStrFormat_Func(){
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	//LVITEM       lvi;
	int          index = 0;

	UpdateData();
	lvi.mask = LVIF_TEXT;  // | LVCF_SUBITEM�����Ă͂Ȃ�Ȃ� //�d�v 2012.05.31
	CString FormatDataStr;

	while (index < CFileListCreatorDlg::m_xcList.GetItemCount()){
		//ULONGLONG FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

		int FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

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


		lvi.iItem = index;
		lvi.iSubItem = 9;
		lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

		CFileListCreatorDlg::m_xcList.SetItem(&lvi);

		UpdateData(FALSE);
		index++;
	}
	//RedrawWindow();
}

void CFileListCreatorDlg::SetStrFormat_Func(){

	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	//LVITEM       lvi;
	int          index = 0;


	UpdateData();
	lvi.mask = LVIF_TEXT;  // | LVCF_SUBITEM�����Ă͂Ȃ�Ȃ� //�d�v 2012.05.31
	CString FormatDataStr;

	while (index < CFileListCreatorDlg::m_xcList.GetItemCount()){
		//ULONGLONG FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

		int FormatDataNum =11;
		CString FormatDataStr = CFileListCreatorDlg::m_xcList.GetItemText(index,9);

		if (FormatDataStr == _T("NORMAL,BLACK,")){
			FormatDataNum = 11;
		}

		if (FormatDataStr == _T("BOLD,BLACK,")){
			FormatDataNum = 12;
		}


		if (FormatDataStr == _T("NORMAL,RED,")){
			FormatDataNum = 21;
		}

		if (FormatDataStr == _T("BOLD,RED,")){
			FormatDataNum = 22;
		}

		CFileListCreatorDlg::m_xcList.SetItemData(index,FormatDataNum);
		//CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE);
		//UpdateWindow();
		UpdateData(FALSE);
		index++;
	}
	RedrawWindow();
}

void CFileListCreatorDlg::SetFormatNumToStr_Items(int index){
	//LVITEM       lvi;
	//int          index = 0;


	UpdateData();
	lvi.mask = LVIF_TEXT;
	CString FormatDataStr;

	if (index==-1){
		index = 0;

		while (index < CFileListCreatorDlg::m_xcList.GetItemCount()){
			//ULONGLONG FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

			int FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

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


			lvi.iItem = index;
			lvi.iSubItem = 9;			

			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));
			CFileListCreatorDlg::m_xcList.SetItem(&lvi);

			UpdateData(FALSE);
			//index++;
		}
	}else{
		int FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

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


		lvi.iItem = index;
		lvi.iSubItem = 9;			

		lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));
		CFileListCreatorDlg::m_xcList.SetItem(&lvi);
		UpdateData(FALSE);
	}
	//RedrawWindow();
}

int CFileListCreatorDlg::GetStrLen_Func(CString tempStr){
	if(tempStr == _T(""))return 0;

	return tempStr.GetLength();
}


void CFileListCreatorDlg::OnOptionTips()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

		//���[�_���X�P
		CDialog *m_pDlg;
		m_pDlg = new TipsInfo(this);
		m_pDlg->Create(IDD_DIALOG_Tips);

		m_pDlg->ShowWindow(true);
}


void CFileListCreatorDlg::OnMenuEmphasisbyred()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	if( CFileListCreatorDlg::m_xcList.GetItemCount() <=0){
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

    int        index = -1;
    CString    str;

	int myCnt = 0;

    while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
        (index, LVNI_ALL | LVNI_SELECTED)) != -1)
    {

		myCnt++;
    }
	
	int myResult;
	CString tempCnt;

	if(myCnt==0){
		myResult = MessageBox(_T("���ׂẴA�C�e���ɐԕ���(�������)���Z�b�g���܂����H"),_T("Selected Items To Bold"),MB_YESNOCANCEL);
		if(myResult == IDYES){

			UpdateData(FALSE);
			index = 0;
			while(index < CFileListCreatorDlg::m_xcList.GetItemCount())
			{
				int FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

				if(FormatDataNum == 11){
					//FormatDataStr = _T("NORMAL,BLACK,");
					FormatDataNum = 21;
				}

				if(FormatDataNum == 12){
					//FormatDataStr = _T("BOLD,BLACK,");
					FormatDataNum = 22;

				}
		
				if(FormatDataNum == 21){
					//FormatDataStr = _T("NORMAL,RED,");
				}

				if(FormatDataNum == 22){
					//FormatDataStr = _T("BOLD,RED,");
				}

				CFileListCreatorDlg::m_xcList.SetItemData(index,FormatDataNum);

				//ListView_Update(m_xcList, index); //�R�����g�� 2012.06.15
				index++;
			}
			CFileListCreatorDlg::StatusStringSet(_T("���ׂĂɃA�C�e���̐ԕ���(�������)�ɃZ�b�g���܂���"),300,TRUE);

		}
	}else if(myCnt>=1){
			//m_xvChkRedOnMode = TRUE;
			//g_ChkRedOn = TRUE;
			//m_xvStrRedOnMode = _T("�F�@�ԕ����I�����[�h");
			//UpdateData(FALSE);


			//CFileListCreatorDlg::GetStrFormat_Func();

			int myCnt = 0;
			index = -1;
			while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
			    (index, LVNI_ALL | LVNI_SELECTED)) != -1)
			{
				int FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

				if(FormatDataNum == 11){
					//FormatDataStr = _T("NORMAL,BLACK,");
					FormatDataNum = 21;
				}

				if(FormatDataNum == 12){
					//FormatDataStr = _T("BOLD,BLACK,");
					FormatDataNum = 22;

				}
		
				if(FormatDataNum == 21){
					//FormatDataStr = _T("NORMAL,RED,");
				}

				if(FormatDataNum == 22){
					//FormatDataStr = _T("BOLD,RED,");
				}

				CFileListCreatorDlg::m_xcList.SetItemData(index,FormatDataNum);
				//ListView_Update(m_xcList, index);
				myCnt++;
			}

			//CString tempCnt;

			tempCnt = _T("");
			if(myCnt>=1){ //�ǉ� 2012.06.14
				tempCnt.Format(_T("%d"),myCnt);
				tempCnt=tempCnt + _T(" ���̃A�C�e���ɐԕ���(�������)���Z�b�g���܂���");
			}else{
				tempCnt=_T("�A�C�e�����I������Ă��Ȃ����߁A�ԕ���(�������)���Z�b�g�ł��܂���");
			}
			CFileListCreatorDlg::StatusStringSet(tempCnt,300,TRUE);
			//CFileListCreatorDlg::SetStrFormat_Func();
		//}else if(myResult == IDNO){

		//}
	}


		m_xvChkRedOnMode = FALSE;
		m_xvStrRedOnMode = _T("�F�@�ԕ��� ���ҏW");
		UpdateData(FALSE);	

		m_xvChkEasySelect = FALSE;
		m_xvStrEasySelectMode = _T("�F�@������ ���ҏW");
		UpdateData(FALSE);

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}


	//http://oshiete.goo.ne.jp/qa/112210.html
	//::InvalidateRect(0,0,false); //��ʑS�̂ɍĕ`���v��
	//http://oshiete.goo.ne.jp/qa/200500.html
	//SendMessage(editBox, WM_KILLFOCUS, 0, 0L);
}


void CFileListCreatorDlg::OnEditselecteditemRed()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	CFileListCreatorDlg::OnMenuEmphasisbyred();
}

void CFileListCreatorDlg::OnMenuExpandListFile()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if( CFileListCreatorDlg::m_xcList.GetItemCount() <=0){
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	ESCAPE_FLG = FALSE;

    int        index = -1;
    CString    str;
    CString 	tempPath;
	tempPath=_T("");
	int myCnt = 0;

	TotalItemsCount = 0;
	DoWithCnt = 0;

	importFileResult = IDNO;

	SkipFLG = FALSE;

	index = -1;

    while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
        (index, LVNI_ALL | LVNI_SELECTED)) != -1)
    {

		ULONGLONG tempCnt;
		//tempCnt =0;

		tempCnt = CFileListCreatorDlg::FileListItemsCount(CFileListCreatorDlg::m_xcList.GetItemText(index,2));

		if( tempCnt == 0 ){
			//TotalItemsCount ++;
		}else{
			TotalItemsCount = TotalItemsCount + tempCnt;
		}
		myCnt++;
    }

	if(myCnt==0){

		importFileResult = MessageBox(_T("���ׂẴ��X�g�t�@�C����W�J���܂����H"),_T("�C���|�[�g�m�F"), MB_YESNOCANCEL );
		if ( importFileResult == IDYES ){
			index = 0;

			while (index < CFileListCreatorDlg::m_xcList.GetItemCount())
			{

				ULONGLONG tempCnt;

				tempPath = CFileListCreatorDlg::m_xcList.GetItemText(index,2);

				if (CFileListCreatorDlg::importFileList_Func(tempPath,TRUE)== 1){
					m_xcList.SetItemState(index,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
					LVIS_FOCUSED | LVIS_SELECTED,    // ���
					LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N

					tempCnt = CFileListCreatorDlg::FileListItemsCount(tempPath);

					TotalItemsCount = TotalItemsCount + tempCnt;

					myCnt++;
				}else{
					m_xcList.SetItemState(index,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
					!LVIS_SELECTED,    // ��� //��I�����
					LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N
				}
				index ++;
			}
		}
	}

	//int myResult;
	CString tempCnt;

	if(myCnt==0){
		CFileListCreatorDlg::StatusStringSet(_T("���X�g�t�@�C���͌��o����܂���ł���"),300,TRUE);
	}else if(myCnt>=1){

		UpdateData(FALSE);

		int index = -1;

		myCnt = 0;
		//index = -1;
		while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
			(index, LVNI_ALL | LVNI_SELECTED)) != -1)
		{

			tempPath = CFileListCreatorDlg::m_xcList.GetItemText(index,2);

			if ( CFileListCreatorDlg::importFileList_Func(tempPath,TRUE)== 1){
				CFileListCreatorDlg::importFileList_Func(tempPath,FALSE);
				myCnt++;
			}else{
				m_xcList.SetItemState(index,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
				!LVIS_SELECTED,    // ��� //��I�����
				LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N
			}

			//CFileListCreatorDlg::ItemCount_Func(TRUE);
		}

		tempCnt = _T("");

		if(myCnt>=1) { //�ǉ� 2012.06.14
			tempCnt.Format(_T("%d"),myCnt);
			tempCnt=tempCnt + _T(" ���̃��X�g��W�J���܂���");
		}else{
			tempCnt=tempCnt + _T("���X�g���������� �W�J�ł��܂���");
		}
		CFileListCreatorDlg::StatusStringSet(tempCnt,300,TRUE);
		CFileListCreatorDlg::SetStrFormat_Func();

		CFileListCreatorDlg::Total_Bytes_Bold();
		CFileListCreatorDlg::Total_Bytes_Func();
		CFileListCreatorDlg::ItemCount_Func(TRUE);

		index = -1;

		index = CFileListCreatorDlg::m_xcList.GetNextItem(index, LVNI_ALL | LVNI_SELECTED);
		CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE);

		
		
		ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

		CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

		if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
			return;
		}

		if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
			m_Dlg->SetWindowText(_T("FileListCreator (*)"));
			SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24
		}
		
	}
}

void CFileListCreatorDlg::PlayEmphasizedMusic(){
	if( CFileListCreatorDlg::m_xcList.GetItemCount() <=0){
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	CFileListCreatorDlg::StatusStringSet(_T("�t�@�C���̃I�[�v���O�������s���Ă��܂�"),300,FALSE);


	CFileListCreatorDlg::GetStrFormat_Func();
	//CFileListCreatorDlg::SetStrFormat_Func();

	CString FullPath;
	CString FolderPath;
	CString FileName;

	int FormatDataNum;

	CString AudioItems; // = _T("");

	int myCnt = 0;
	int index;

	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		
		index = 0;
		myCnt = 0;
		while (index <= CFileListCreatorDlg::m_xcList.GetItemCount()-1){
			//CFileListCreatorDlg::m_xcList.SetItemData(index,FormatDataNum);

			FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

			if(FormatDataNum == 11){
				//FormatDataStr = _T("NORMAL,BLACK,");
			}

			if(FormatDataNum == 12){
				//FormatDataStr = _T("BOLD,BLACK,");
				myCnt++;
			}

			if(FormatDataNum == 21){
				//FormatDataStr = _T("NORMAL,RED,");
				myCnt++;
			}

			if(FormatDataNum == 22){
				//FormatDataStr = _T("BOLD,RED,");
				myCnt++;
			}
			index++;
		}
		
		if(myCnt < 1){
			CFileListCreatorDlg::StatusStringSet(_T("�P�ȏ�̃t�@�C���𑾕������ԕ����ɂ��ĉ����� \r\n (��ʉ��������́uEasySelect for Copy�v��uRED�v���g���ĉ�����) "),300,TRUE);
			return;
		}

		index = 0;
		CString str;
		//CString AudioItems =_T("");
		myCnt = 0;

		while (index <= CFileListCreatorDlg::m_xcList.GetItemCount()-1){
			FullPath = CFileListCreatorDlg::m_xcList.GetItemText(index, 2);//�t���p�X�� 2�Ԗ�
			FileName = FullPathToFileName(FullPath);
			FolderPath = CurrentDirFunc(FullPath,TRUE);

			FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

			if (FormatDataNum == 12 || FormatDataNum == 21 || FormatDataNum == 22){
				if(FullPath.Right(1)!=_T("\\")){
					if (myStrToLower_Func(FullPath.Right(4)) == _T(".m3u")){
						AudioItems = ReadOrWritePlayList_Func(_T("m3u_read"),FullPath,AudioItems,FullPathToFileName(FullPath)); //�ύX 2012.07.12
					}else if (myStrToLower_Func(FullPath.Right(4)) == _T(".wpl")){
						ReadOrWritePlayList_Func(_T("wpl_write"),FullPath,AudioItems,FullPathToFileName(FullPath));
						AudioItems = ReadOrWritePlayList_Func(_T("wpl_read"),FullPath,AudioItems,FullPathToFileName(FullPath));
					}else{
						AudioItems +=_T(" \"") + FullPath + _T("\"");
						//AudioItems = ReadOrWritePlayList_Func(_T("m3u_read"),FullPath,AudioItems,_T(""));
					}
				}else{
					//��ō쐬
					AudioItems += inFolder_AllFile(FullPath,_T("*.mp3"),_T(""));
					AudioItems += inFolder_AllFile(FullPath,_T("*.wma"),_T(""));
					AudioItems += inFolder_AllFile(FullPath,_T("*.wav"),_T(""));

					AudioItems += inFolder_AllFile(FullPath,_T("*.mpg"),_T(""));
					AudioItems += inFolder_AllFile(FullPath,_T("*.mpeg"),_T(""));
					AudioItems += inFolder_AllFile(FullPath,_T("*.wmv"),_T(""));
					AudioItems += inFolder_AllFile(FullPath,_T("*.asf"),_T(""));
					AudioItems += inFolder_AllFile(FullPath,_T("*.avi"),_T(""));
				}
				myCnt++;
			}
			index++;
		}
		//myCnt++;
	}


	CFileListCreatorDlg::StatusStringSet(_T("�t�@�C���̃I�[�v�������s���܂��� \r\n (���f�B�A�v���C���[���N�����܂�)"),300,FALSE);
	if(myCnt == 0) {
		CFileListCreatorDlg::StatusStringSet(_T("�A�C�e����I�����Ă�������"),300,TRUE);
	}else{
		ReadOrWritePlayList_Func(_T("m3u_write"),_T(""),AudioItems,_T("temp.flc"));
		CString m3uFile = _T("");
				
		m3uFile = _T("\"") + ReadOrWritePlayList_Func(_T("m3u_read_temp"),_T(""),AudioItems,_T("temp.flc.m3u")) + _T("\"");

		ShellExecute( NULL, _T("open"), _T("C:\\Program Files\\Windows Media Player\\wmplayer.exe"), m3uFile , NULL , SW_SHOWNORMAL );
			

		//ShellExecute( NULL, _T("open"), _T("C:\\Program Files\\Windows Media Player\\wmplayer.exe"), AudioItems , NULL , SW_SHOWNORMAL );

		if (IDYES==MessageBox(_T("�v���C���X�g��ۑ����܂����H"),_T("�v���C���X�g�ۑ�"), MB_YESNOCANCEL )){			
			//���[�_��
			InputBoxDlg m_dlg;
			//m_dlg.DoModal();

			//FileName = InputBox("�t�@�C���ɖ��O�����ĉ������B", "���O�����ĕۑ�", CreateDateTime)

			if (m_dlg.DoModal()==IDOK){
				FileName = _T("");
				FileName = m_dlg.ExportFileName;
			}else{
				FileName = _T("");
			}
			if (FileName != _T("")){
				ReadOrWritePlayList_Func(_T("m3u_write"),_T(""),AudioItems,FileName);
			}


				////http://rararahp.cool.ne.jp/vc/vctips/api.htm
				//// ���s�t�@�C���̃t���p�X�擾
				//TCHAR szPath[_MAX_PATH];
				//GetModuleFileName( NULL, szPath, MAX_PATH);

				//CString CurDir;
				//CurDir = szPath;

				////CFileListCreatorDlg CFileListCreatorDlg_CLASS;
				//CurDir = CurrentDirFunc(CurDir,TRUE);

				//if(CurDir!=_T("")){
				//	CurDir.Replace(_T("\\"),_T("\\\\"));
				//}
				//CurDir = CurDir + _T("\\FileListCreator(LIST)");
				//if(CreateDirectory(CurDir,NULL)){

				//}
				//else {
			
				//}

				//DeleteFile(CurDir + _T("\\temp.flc.m3u")); //http://www.ujasiri.com/prglib/vc/filectrl/vc_delfile.html

			CFileListCreatorDlg::StatusStringSet(_T("�v���C���X�g��ۑ����܂���"),300,TRUE);
			return;
		}
				
	}
}

void CFileListCreatorDlg::OnMenuPlayEmphasizedMusic()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	PlayEmphasizedMusic();
}



void CFileListCreatorDlg::ExcludeNonEmphasizedItems(){
	CFileListCreatorDlg::StatusStringSet(_T("�������ꂽ�A�C�e���ȊO���폜���܂�"),300,FALSE);

	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	CFileListCreatorDlg::GetStrFormat_Func();
			
	CString FullPath;
	CString FolderPath;
	CString FileName;

	int FormatDataNum;

	CString AudioItems = _T("");

	int myCnt = 0;
	int index;

	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		
		LastPrevItemCount = m_xcList.GetItemCount();
		CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

		index = 0;
		myCnt = 0;
		while (index <= CFileListCreatorDlg::m_xcList.GetItemCount()-1){
			FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

			if(FormatDataNum == 11){
				//FormatDataStr = _T("NORMAL,BLACK,");
			}

			if(FormatDataNum == 12){
				//FormatDataStr = _T("BOLD,BLACK,");
				myCnt++;
			}

			if(FormatDataNum == 21){
				//FormatDataStr = _T("NORMAL,RED,");
				myCnt++;
			}

			if(FormatDataNum == 22){
				//FormatDataStr = _T("BOLD,RED,");
				myCnt++;
			}
			index++;
		}
		
		if(myCnt < 1){
			CFileListCreatorDlg::StatusStringSet(_T("���������ԕ����ŋ������ꂽ�A�C�e���͂���܂���ł��� \r\n (��������ɂ́A��ʉ��������́uEasySelect for Copy�v��uRED�v���g���ĉ�����) "),300,TRUE);
			return;
		}

		index = 0;
		CString str;
		//CString AudioItems =_T("");
		myCnt = 0;

		while (index <= CFileListCreatorDlg::m_xcList.GetItemCount()-1){


			FullPath = CFileListCreatorDlg::m_xcList.GetItemText(index, 2);//�t���p�X�� 2�Ԗ�
			FileName = FullPathToFileName(FullPath);
			FolderPath = CurrentDirFunc(FullPath,TRUE);

			FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

			if (FormatDataNum == 12 || FormatDataNum == 21 || FormatDataNum == 22){
	
			}else{
				CFileListCreatorDlg::m_xcList.DeleteItem(index);
				index--;
				myCnt++;
				CFileListCreatorDlg::ItemCount_Func(TRUE);
			}
			index++;
		}
		//myCnt++;
	}

	if (myCnt >= 1){
		CFileListCreatorDlg::Total_Bytes_Bold();
		CFileListCreatorDlg::Total_Bytes_Func();
		CFileListCreatorDlg::ItemCount_Func(TRUE);
		CString str;

		str.Format(_T("%d �̃A�C�e�����폜���܂���"),myCnt );
		CFileListCreatorDlg::StatusStringSet(str,300,TRUE);


		ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

		CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

		if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
			return;
		}

		if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
			m_Dlg->SetWindowText(_T("FileListCreator (*)"));
			//SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24
		}
	}else{
		CFileListCreatorDlg::Total_Bytes_Bold();
		CFileListCreatorDlg::Total_Bytes_Func();
		CFileListCreatorDlg::ItemCount_Func(TRUE);

		CFileListCreatorDlg::StatusStringSet(_T("��������Ă��Ȃ��A�C�e���͂P���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
	}

}
void CFileListCreatorDlg::OnMenuExcludeNonemphasizedItems()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	ExcludeNonEmphasizedItems();
}


void CFileListCreatorDlg::Total_Bytes_Bold(){
	ESCAPE_FLG = FALSE;

    ///Call StatusStringSet("")
	

	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),0,FALSE);
		BoldByteSum = 0;
		BolditemCount = 0;
	}else{
    
		BoldByteSum = 0;
		BolditemCount = 0;
    
		//ULONGLONG byteItemIDX;

		int index = 0;

		while (index <= CFileListCreatorDlg::m_xcList.GetItemCount()-1){

			MSG msg; //�ǉ� 2011.10.12
			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						ESCAPE_FLG = TRUE;
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			int FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);

			if (FormatDataNum == 12 ||  FormatDataNum == 22){
				if(myIsDigit_Func(CFileListCreatorDlg::m_xcList.GetItemText(index, 5)) ==TRUE){//�t�@�C���T�C�Y �� 5�Ԗ�
					BoldByteSum = BoldByteSum + CStringToLong(CFileListCreatorDlg::m_xcList.GetItemText(index, 5));
					BolditemCount = BolditemCount + 1;
				}
			}

			index++;
		}
	}
}

void CFileListCreatorDlg::OnSortSortitemsbystrformat()
{

	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		CFileListCreatorDlg::GetStrFormat_Func();

		LastPrevItemCount = m_xcList.GetItemCount();
		CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

		StatusStringSet(_T("Sort ���s��"),0,FALSE); //�ύX 2012.06.14

		RenumberItem();				// SortItems�֐����Ăяo���O�ɂ͕K�����s

		keyColumn = 9;//keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������ 9:�������
		static BOOL bSort = FALSE;			// static�Œ�`���邱��
		m_xcList.SortItems(CompareFunc, bSort);

		if (bSort == FALSE) { 
			CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(����)"),300,TRUE);
		}else{
			CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�~��)"),300,TRUE);
		}
		SortColumnDrawCaption(keyColumn, bSort);
		bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���

		//CFileListCreatorDlg::m_xcList.EnsureVisible(0, FALSE);
		CFileListCreatorDlg::SortEnsureVisible_Func();

		CFileListCreatorDlg::SetStrFormat_Func();

	}

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
		//SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24 //�R�����g�� 2012.05.25
	}
}


void CFileListCreatorDlg::OnSortMerge()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	CFileListCreatorDlg::Merge_Func();
}

void CFileListCreatorDlg::CopyFolder_Items(CString strTrgDir,CString strFileSpec ,BOOL CopyMode, CString tempCopyToSavePath){
	ESCAPE_FLG = FALSE;

	//FilesCount = Bold_CNT_IDX;
	strTrgDir.Replace(_T("\\"),_T("\\\\"));

	CString tempPathName = strTrgDir + strFileSpec;
	//CString strWildcard =  _T("\\*.*") ;
     
	CFileFind finder;
    BOOL         bWorking = finder.FindFile(tempPathName);
    CString      str;

	int err = 0;

	
   while (bWorking)
   {

	MSG msg; //�ǉ� 2011.10.12
	if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
		if(msg.hwnd != GetDlgItem(IDC_LIST)->m_hWnd ){
			if (msg.wParam == VK_ESCAPE){
				ESCAPE_FLG = TRUE;
				break; //�I���B���b�Z�[�W���[�v�𔲂���B
			}
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		//continue; //�t�@�C�����R�s�[����Ƃ��̓R�����g��
	}

      bWorking = finder.FindNextFile();
      // skip . and .. files; otherwise, we'd
	  // recur infinitely!
      if (finder.IsDots()) continue;

		err = finder.IsDirectory();


		CString FullPathString1 = finder.GetFilePath();
		CString FullPathString2 = FullPathString1;

		BOOL ExistFlg = TRUE;
		int workIDX1;
		int workIDX2;
		int workIDX3;
		int SearchIDX;

		CString FolderPath;
		FolderPath=_T("");

		//if(FullPathString2.Right(1)!=_T("\\")){
		//	FolderPath = FullPathString2.Left(myReverseFind(FullPathString2,_T("\\"),FullPathString2.GetLength()-1)+1);
		//}else{
		//	FolderPath = FullPathString2;
		//}
		
		if(FullPathString2.Right(1)!=_T("\\")){
			ExistFlg = TRUE;
			SearchIDX = myReverseFind(FullPathString2,_T("\\"),FullPathString2.GetLength()-1);

			if (SearchIDX <=0){
				ExistFlg = FALSE;
			}
            
			workIDX1 = SearchIDX;
			SearchIDX = myReverseFind(FullPathString2,_T("\\"), workIDX1 - 1);
			if (SearchIDX <=0){
				ExistFlg = FALSE;
			}
		
 			workIDX2 = SearchIDX;
			SearchIDX = myReverseFind(FullPathString2,_T("\\"), workIDX2 - 1);
			if (SearchIDX <=0){
				ExistFlg = FALSE;
			}

			workIDX3 = SearchIDX;
			//FileName = CopyToSavePath + FolderName + _T("\\") +  FullPathString2.Mid(FullPathString2.ReverseFind(_T('\\'))+1);
			if (ExistFlg==TRUE) {
				FolderPath = FullPathString2.Mid(SearchIDX +1, workIDX1 - workIDX3 -1);

				//myFileName = FolderPath;
				FolderPath.Replace(_T("\\"), _T(" - "));

				FullPathString2 = tempCopyToSavePath + _T("\\") + FolderPath + _T("\\") + FullPathToFileName(FullPathString1);


				FullPathString1.Replace(_T("\\"),_T("\\\\")); 
				FullPathString2.Replace(_T("\\"),_T("\\\\"));
			}
		}


		if(CreateDirectory(tempCopyToSavePath + _T("\\") + FolderPath ,NULL)){

		}else{
			
		}
		//if (!err){
			if(CopyMode==TRUE){
				if ( PathFileExists(FullPathString1)){
				//�t�@�C�����R�s�[����(�㏑���R�s�[������)
					if (ESCAPE_FLG == FALSE){
						CopyFile(static_cast<LPCTSTR>(FullPathString1),static_cast<LPCTSTR>(FullPathString2), FALSE);
						CString str;
						str.Format(_T("�������̃t�@�C�����w�肵���t�H���_�ɃR�s�[�� (%d/%d) ") ,Bold_CNT_IDX ,Bold_SUM_CNT);
						CFileListCreatorDlg::StatusStringSet(str,0,FALSE);						
						Bold_CNT_IDX = Bold_CNT_IDX + 1;
					}
				}
			}else{
				Bold_SUM_CNT = Bold_SUM_CNT + 1;
			}
		//}
   }
   finder.Close();
}

void CFileListCreatorDlg::Copy_Func()
{
	ESCAPE_FLG = FALSE;

    //easySelectFLG = FALSE
    //iTunesAlbumCheckFLG = FALSE

    CFileListCreatorDlg::StatusStringSet(_T("�R�s�[�@�\���s��"),300,FALSE);
    
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	if( CFileListCreatorDlg::m_xcList.GetItemCount() <=0){
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}


	//int Bold_SUM_CNT;
    Bold_SUM_CNT = 0;
	//
	//int  Bold_CNT_IDX;
	Bold_CNT_IDX = 0;
	
	//LVITEM       lvi;
	int          index = 0;


	UpdateData();
	lvi.mask = LVIF_TEXT;
	CString FormatDataStr;

	int i;

    for (i = 0 ; i<=CFileListCreatorDlg::m_xcList.GetItemCount()-1;i++){
		CString strTrgDir = CFileListCreatorDlg::m_xcList.GetItemText(i,2);

		int FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(i);

		FormatDataStr = _T("NORMAL,BLACK,");

		if(FormatDataNum == 11){
			FormatDataStr = _T("NORMAL,BLACK,");
		}

		if(FormatDataNum == 12){
			FormatDataStr = _T("BOLD,BLACK,");
			Bold_SUM_CNT = Bold_SUM_CNT + 1;
		}
		
		if(FormatDataNum == 21){
			FormatDataStr = _T("NORMAL,RED,");
		}

		if(FormatDataNum == 22){
			FormatDataStr = _T("BOLD,RED,");
			Bold_SUM_CNT = Bold_SUM_CNT + 1;
		}
    }

    if(Bold_SUM_CNT==0){
		CFileListCreatorDlg::StatusStringSet(_T("EasySelect ���g�p���āA�R�s�[�������A�C�e���𑾕����ɂ��ĉ�����"),300,TRUE);
		return;
	}

	Merge_Func();


	BOOL FileNameOnListFLG;
	FileNameOnListFLG = FALSE;

	if ( CheckFileName() == TRUE) {
		int myResult;

		myResult = MessageBox(_T("���X�g��̃t�@�C���������ꂩ��R�s�[����o�̓t�@�C�����Ƃ��܂����H"),_T("�o�̓t�@�C����"),MB_YESNOCANCEL);
		if(myResult==IDYES){
			FileNameOnListFLG = TRUE;
		}
	}

	int myResult;

    myResult = MessageBox(_T("�R�s�[�����t�@�C���̕ۑ�����w�肵�܂����H\r\n�u�������v��I�������ꍇ�́A�}�C�h�L�������g�Ȃǂ�\r\n�f�t�H���g�t�H���_�ɕۑ�����܂��B\r\n\r\n(�\���ȋ󂫗e�ʂ�����t�H���_���w�肵�ĉ������B) "),_T("�ۑ��� �w��"),MB_YESNOCANCEL);

	CString myPathname=_T("");

	if(myResult==IDYES){
		CFileListCreatorDlg::StatusStringSet(_T("�ۑ��� �w��"),300,FALSE);
		UpdateData(FALSE);

		//int myResult;


		TCHAR  szFolder[MAX_PATH];

		if( GetOpenFolderName( AfxGetMainWnd()->m_hWnd, NULL, szFolder, MAX_PATH ) == IDOK )
		{
			myPathname = CString(szFolder);
			//myPathname.Replace(_T("\\"),_T("\\\\"));
		}

		//http://msdn.microsoft.com/ja-jp/library/cc429308.aspx
		//http://airparklab.ifdef.jp/airpark/tips/api.html

		ULARGE_INTEGER unFreeBytesAvailable;
		ULARGE_INTEGER unTotalNumberOfBytes;
		ULARGE_INTEGER unTotalNumberOfFreeBytes;
		BOOL bRet = GetDiskFreeSpaceEx( szFolder, &unFreeBytesAvailable, &unTotalNumberOfBytes, &unTotalNumberOfFreeBytes );
		if( bRet ){
			// unFreeBytesAvailable.QuadPart;     �Ăяo���������p�ł���o�C�g��
			// unTotalNumberOfBytes.QuadPart;     �f�B�X�N�S�̂̃o�C�g��
			// unTotalNumberOfFreeBytes.QuadPart; �f�B�X�N�S�̂̋󂫃o�C�g��

			Total_Bytes_Bold();

			CFileListCreatorDlg::StatusStringSet(_T("�ۑ���h���C�u�̋󂫗e�ʁF " + ByteCalculation(unTotalNumberOfFreeBytes.QuadPart,TRUE)) ,300,FALSE);
			UpdateData(FALSE);

			if(BoldByteSum >= unTotalNumberOfFreeBytes.QuadPart){
				int myResult;

				myResult = MessageBox(_T("�ۑ���h���C�u�� �󂫗e�ʂ� " + ByteCalculation(BoldByteSum - unTotalNumberOfFreeBytes.QuadPart,TRUE) + " �s�����Ă��܂��B�����𑱍s���܂����H"),_T("�󂫗e�ʕs��"),MB_YESNOCANCEL);

				if(myResult!=IDYES){
					return;
				}

			}
		}

		if(myPathname==_T("")){
			CFileListCreatorDlg::StatusStringSet(_T("�R�s�[�@�\�L�����Z��"),300,TRUE);
			return;
		}else{
			CFileListCreatorDlg::StatusStringSet(_T("�ۑ��� ����"),300,FALSE);
		}
	}

	//int i;
    CString FolderName;
    CString CopyToSavePath;

    if (myResult == IDYES ){
        
        //Call GetFolderPath//
        if (myPathname != _T("")){
            if (myPathname.Right(1) != _T("\\")){
                CopyToSavePath = myPathname + _T("\\");
            }else if (myPathname.Right(1) == _T("\\")){
                CopyToSavePath = myPathname;
            }

			myPathname.Replace(_T("\\"),_T("\\\\"));
            
			if (myPathname == _T("")){
               CopyToSavePath = WindowsFolder_Func() + _T("\\\\");
               //return;
            }
            
            //Worksheets("WORK").Cells(4, 2).Value = CopyToSavePath
            myPathname = _T("");
        }
   }else if (myResult == IDNO){
        //if(myPathname != _T("")){
            //if (myPathname == _T("")){
               CopyToSavePath = WindowsFolder_Func() + _T("\\\\");
            //}
            myPathname = _T("");
        //}

		CopyToSavePath.Replace(_T("\\\\"),_T("\\"));

    }else if (myResult == IDCANCEL || myPathname == _T("") ){
        CFileListCreatorDlg::StatusStringSet(_T("�R�s�[�@�\�L�����Z��"),300,TRUE);
        return;
    }

    FolderName = _T("FLC-") + CreateDateTime(1);

	if(CreateDirectory(CopyToSavePath + FolderName,NULL)){

	}else{
			
	}

	//int Bold_SUM_CNT;
    Bold_SUM_CNT = 0;
	//
	//int  Bold_CNT_IDX;
	Bold_CNT_IDX = 0;
	
	//LVITEM       lvi;
	//int          index = 0;
	index = 0;

	UpdateData();
	lvi.mask = LVIF_TEXT;
	//CString FormatDataStr;

	//int i;

    for (i = 0 ; i<=CFileListCreatorDlg::m_xcList.GetItemCount()-1;i++){
		CString strTrgDir = CFileListCreatorDlg::m_xcList.GetItemText(i,2);

		int FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(i);

		FormatDataStr = _T("NORMAL,BLACK,");

		if(FormatDataNum == 11){
			FormatDataStr = _T("NORMAL,BLACK,");
		}

		if(FormatDataNum == 12){
			FormatDataStr = _T("BOLD,BLACK,");
			if (strTrgDir.Right(1)==_T("\\")){
				CopyFolder_Items(strTrgDir, _T("*.*"), FALSE, (CopyToSavePath + FolderName));
			}else{
				Bold_SUM_CNT = Bold_SUM_CNT + 1;
			}
		}
		
		if(FormatDataNum == 21){
			FormatDataStr = _T("NORMAL,RED,");
		}

		if(FormatDataNum == 22){
			FormatDataStr = _T("BOLD,RED,");
			if (strTrgDir.Right(1)==_T("\\")){
				CopyFolder_Items(strTrgDir, _T("*.*"), FALSE, (CopyToSavePath + FolderName));
			}else{
				Bold_SUM_CNT = Bold_SUM_CNT + 1;
			}
		}

		if (FormatDataNum == 12 || FormatDataNum == 22){

		}
    }
    
	CString FileName;

	Bold_CNT_IDX = 0;
    
	for (i = 0;i<=CFileListCreatorDlg::m_xcList.GetItemCount()-1;i++){

		MSG msg; //�ǉ� 2011.10.12
		if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
			if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
				if (msg.wParam == VK_ESCAPE){
					ESCAPE_FLG = TRUE;
					break; //�I���B���b�Z�[�W���[�v�𔲂���B
				}
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			//continue; //�t�@�C�����R�s�[����Ƃ��̓R�����g��
		}

		int FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(i);

		if(FormatDataNum == 12 || FormatDataNum == 22){
			CString strTrgDir = CFileListCreatorDlg::m_xcList.GetItemText(i,2);

			if (strTrgDir.Right(1)==_T("\\")){
				CopyFolder_Items(strTrgDir, _T("*.*"), TRUE, (CopyToSavePath + FolderName));
			}
			if (Bold_CNT_IDX <= Bold_SUM_CNT) {
				CString str;
				str.Format(_T("�������̃t�@�C�����w�肵���t�H���_�ɃR�s�[�� (%d/%d) ") ,Bold_CNT_IDX ,Bold_SUM_CNT);
				CFileListCreatorDlg::StatusStringSet(str,0,FALSE);
			}

			//http://www.ujasiri.com/prglib/vc/filectrl/vc_CopyFile/vc_CopyFile.html

			CString FullPathString = CFileListCreatorDlg::m_xcList.GetItemText(i,2);

			//http://oshiete.goo.ne.jp/qa/3399080.html?from=navi_ranking

			if ( PathFileExists(FullPathString)){
			//�t�@�C�����R�s�[����(�㏑���R�s�[������)
				if ( FileNameOnListFLG == TRUE ){
					CString tempFileName;
					tempFileName = CFileListCreatorDlg::m_xcList.GetItemText(i,3);
					tempFileName = ProhibitFileName(tempFileName,TRUE);
					FileName = CopyToSavePath + FolderName + _T("\\") + tempFileName;
				}else{
					FileName = CopyToSavePath + FolderName + _T("\\") + FullPathString.Mid(FullPathString.ReverseFind(_T('\\'))+1);
				}
				myResult = CopyFile(static_cast<LPCTSTR>(FullPathString),static_cast<LPCTSTR>(FileName), FALSE);
				if (Bold_CNT_IDX <= Bold_SUM_CNT) {
					CString str;
					str.Format(_T("�������̃t�@�C�����w�肵���t�H���_�ɃR�s�[�� (%d/%d) ") ,Bold_CNT_IDX ,Bold_SUM_CNT);
					CFileListCreatorDlg::StatusStringSet(str,0,FALSE);
				}
				Bold_CNT_IDX = Bold_CNT_IDX + 1;
			} 
		}

		if (Bold_CNT_IDX <= Bold_SUM_CNT) {
			CString str;
			str.Format(_T("�������̃t�@�C�����w�肵���t�H���_�ɃR�s�[�� (%d/%d) ") ,Bold_CNT_IDX ,Bold_SUM_CNT);
			CFileListCreatorDlg::StatusStringSet(str,0,FALSE);
		}
    }
    

    if(Bold_SUM_CNT >= 1){

		if(Bold_CNT_IDX == 0){
			CFileListCreatorDlg::StatusStringSet(_T("EasySelect �ő������ɂ����t�@�C�����P�������݂��܂���"),300,TRUE);
			CString FolderPath;
		
			FolderPath = CopyToSavePath + FolderName + _T("\\");

			//http://oshiete.goo.ne.jp/qa/976818.html
		
			FileName.Replace(_T("\\"),_T("\\\\"));
			FolderPath.Replace(_T("\\"),_T("\\\\"));

			//DeleteFile(FolderPath //http://www.ujasiri.com/prglib/vc/filectrl/vc_delfile.html
		
			RemoveDirectory(FolderPath); //http://oshiete.goo.ne.jp/qa/2899033.html
		
			//if ( PathIsDirectory(FolderPath) ) {  //http://oshiete.goo.ne.jp/qa/3399080.html?from=navi_ranking
			//	//http://msdn.microsoft.com/ja-jp/library/cc422072.aspx
			//	//���G�N�X�v���[���ŊJ��
			//	//ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"),  _T("/select,") + FullPathToFileName(FileName) , FolderPath, SW_SHOWNORMAL );
			//	ShellExecute(NULL, _T("open"), FolderPath, NULL, NULL, SW_SHOWNORMAL);
			//}
			return;
		}

		MessageBox(FolderName + _T(" �Ƃ����t�H���_�Ƀt�@�C�����R�s�[���܂���"), _T("�R�s�[�I��"), MB_OK);
        CString FolderPath;
		
		FolderPath = CopyToSavePath + FolderName + _T("\\");

		//http://oshiete.goo.ne.jp/qa/976818.html
		
		FileName.Replace(_T("\\"),_T("\\\\"));
		FolderPath.Replace(_T("\\"),_T("\\\\"));

		//http://msdn.microsoft.com/ja-jp/library/cc422072.aspx
		//���G�N�X�v���[���ŊJ��
		//ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"),  _T("/select,") + FullPathToFileName(FileName) , FolderPath, SW_SHOWNORMAL );
		ShellExecute(NULL, _T("open"), FolderPath, NULL, NULL, SW_SHOWNORMAL);
    }else{
		CFileListCreatorDlg::StatusStringSet(_T("EasySelect ���g�p���āA�R�s�[�������A�C�e���𑾕����ɂ��ĉ�����"),300,TRUE);
        CString FolderPath;
		
		FolderPath = CopyToSavePath + FolderName + _T("\\");

		//http://oshiete.goo.ne.jp/qa/976818.html
		
		FileName.Replace(_T("\\"),_T("\\\\"));
		FolderPath.Replace(_T("\\"),_T("\\\\"));

		//DeleteFile(FolderPath //http://www.ujasiri.com/prglib/vc/filectrl/vc_delfile.html
		
		RemoveDirectory(FolderPath); //http://oshiete.goo.ne.jp/qa/2899033.html
		
		//if ( PathIsDirectory(FolderPath) ) {  //http://oshiete.goo.ne.jp/qa/3399080.html?from=navi_ranking
		//	//http://msdn.microsoft.com/ja-jp/library/cc422072.aspx
		//	//���G�N�X�v���[���ŊJ��
		//	//ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"),  _T("/select,") + FullPathToFileName(FileName) , FolderPath, SW_SHOWNORMAL );
		//	ShellExecute(NULL, _T("open"), FolderPath, NULL, NULL, SW_SHOWNORMAL);
		//}
	}
}

void CFileListCreatorDlg::OnCopyCopy()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	Copy_Func();
}

CTime CFileListCreatorDlg::item_Date(CString FullPathString, CString strFileSpec)
{
	//LVITEM       lvi;
	int          index = 0;
	int          err = 0;
	CString      str;	

	CString myFileName;
	CString myFileSize;
	ULONGLONG myLongFileSize;
	CString myDate;

	CString tempDate;	

	myFileName=_T("");
	myFileSize=_T("");
	myLongFileSize=0;
	myDate=_T("");

	CTime cTime;

	CFile* pFile = NULL;

	try
	{
		//CFile pfile;

		// try to open the file
		CFile pFile(FullPathString, CFile::modeRead  | CFile::shareDenyNone);

		myFileName = pFile.GetFileName();
		//myFileName = FullPathToFileName(FullPathString);
		CFileStatus status;

		if(pFile.GetStatus(status))    // virtual member function
		{
			//TRACE(_T("�C���� = %s\n"), status.m_mtime);
			//MessageBox(status.m_mtime);
			cTime = status.m_mtime;
			myDate = cTime.Format(_T("%Y/%m/%d %H:%M:%S")); //Format(tdate, "yyyy/mm/dd")
												//Format(tdate, "yyyy/mm/dd hh:mm:ss")
			tempDate = myDate;
		}	
		pFile.Close();
	}
	catch (CFileException* pEx)
	{

		//pEx->ReportError();  //�A���[�g�͏o���Ȃ�
		pEx->Delete();
		myFileName ="";
		myFileSize = "";
		myLongFileSize = 0;
	}

	if (pFile != NULL)
	{
		pFile->Close();
		delete pFile;
	}

	return cTime;

}

ULONGLONG CFileListCreatorDlg::item_Byte(CString FullPathString, CString strFileSpec)
{
	//LVITEM       lvi;
	int          index = 0;
	int          err = 0;
	CString      str;	

	CString myFileName;
	CString myFileSize;
	ULONGLONG myLongFileSize;
	CString myDate;

	CString tempDate;	

	myFileName=_T("");
	myFileSize=_T("");
	myLongFileSize=0;
	myDate=_T("");

	CTime cTime;

	CFile* pFile = NULL;

	try
	{
		//CFile pfile;

		// try to open the file
		CFile pFile(FullPathString, CFile::modeRead  | CFile::shareDenyNone);

		ULONGLONG dwLength = pFile.GetLength();
		myLongFileSize = dwLength;
		myFileSize.Format(_T("%I64u"), dwLength);

		pFile.Close();
	}
	catch (CFileException* pEx)
	{

		//pEx->ReportError();  //�A���[�g�͏o���Ȃ�
		pEx->Delete();
		myFileName ="";
		myFileSize = "";
		myLongFileSize = 0;
	}

	if (pFile != NULL)
	{
		pFile->Close();
		delete pFile;
	}

	return myLongFileSize;

}

CTime CFileListCreatorDlg::inFolder_Date(CString strTrgDir, CString strFileSpec, CTime RecentlyDate){

	CString tempPathName = strTrgDir + _T("\\")+ strFileSpec;

	CFileFind finder;
    BOOL         bWorking = finder.FindFile(tempPathName);
    CString      str;

	StatusStringSet(_T("�t�H���_���A�C�e�����o���@�� ���t���擾"),0,FALSE); //�ύX 2012.06.14

	int err = 0;

   while (bWorking)
   {
      bWorking = finder.FindNextFile();
      // skip . and .. files; otherwise, we'd
	  // recur infinitely!
      if (finder.IsDots()) continue;

		err = finder.IsDirectory();
		
		CString str = finder.GetFilePath();
		
		if (!err){
            if ( RecentlyDate <= item_Date(str,_T("*.*"))){
                RecentlyDate = item_Date(str,_T("*.*"));
			}
		}else{
			RecentlyDate = inFolder_Date(str,strFileSpec,RecentlyDate);
		}
   }
   finder.Close();
   return RecentlyDate;
}


ULONGLONG CFileListCreatorDlg::inFolder_Byte(CString strTrgDir, CString strFileSpec, ULONGLONG tempSumByte){
	CString tempPathName = strTrgDir + _T("\\")+ strFileSpec;

	CFileFind finder;
    BOOL         bWorking = finder.FindFile(tempPathName);
    CString      str;

	StatusStringSet(_T("�t�H���_���A�C�e�����o���@�� �f�[�^�T�C�Y�擾"),0,FALSE); //�ύX 2012.06.14


	int err = 0;

   while (bWorking)
   {
      bWorking = finder.FindNextFile();
      // skip . and .. files; otherwise, we'd
	  // recur infinitely!
      if (finder.IsDots()) continue;

		err = finder.IsDirectory();
		
		CString str = finder.GetFilePath();
		
		if (!err){
			tempSumByte += item_Byte(str,_T("*.*"));
		}else{
			tempSumByte = inFolder_Byte(str,strFileSpec,tempSumByte);
		}
   }
   finder.Close();
   return tempSumByte;
}

CString CFileListCreatorDlg::inFolder_AllFile(CString strTrgDir, CString strFileSpec, CString tempFiles){

	CString tempPathName = strTrgDir + _T("\\")+ strFileSpec;

	CFileFind finder;

//    CString	retTempFiles

    BOOL         bWorking = finder.FindFile(tempPathName);
    CString      str;

	StatusStringSet(_T("�t�H���_���A�C�e�����o��"),0,FALSE); //�ύX 2012.06.14

	int err = 0;

   while (bWorking)
   {

		MSG msg; //�ǉ� 2011.10.12
		if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
			if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
				if (msg.wParam == VK_ESCAPE){
					ESCAPE_FLG = TRUE;
					break; //�I���B���b�Z�[�W���[�v�𔲂���B
				}
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			//continue; //�t�@�C�����R�s�[����Ƃ��̓R�����g��
		}

      bWorking = finder.FindNextFile();
      // skip . and .. files; otherwise, we'd
	  // recur infinitely!
      if (finder.IsDots()) continue;

		err = finder.IsDirectory();
		
		CString str = finder.GetFilePath();
		
		if (!err){
			tempFiles = tempFiles + _T(" \"") + str + _T("\"");
		}else{
			tempFiles = inFolder_AllFile(str,strFileSpec,tempFiles);
		}
   }

//	retTempFiles
   finder.Close();
   return tempFiles;
}

void CFileListCreatorDlg::iTunesAlbumList_Items(int index)
{
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

    //iTunesAlbumCheckFLG = True

    int workIDX1;
	int workIDX2;
	int workIDX3;

    CString workStr;
    
    BOOL ExistFlg;
    ExistFlg = TRUE;

	UpdateData();
	lvi.mask = LVIF_TEXT;

	// �t���p�X
	if (!err)
	{

		FullPathString =CFileListCreatorDlg::m_xcList.GetItemText(index,2);
		if (FullPathString !=_T("")){
			//FullPathString.Replace(_T("%"),_T("%%"));
		}
	}
        
    if(FullPathString != _T("")){
        CString FolderPath;
        int SearchIDX;
		if(FullPathString.Right(1)!=_T("\\")){
			FolderPath = FullPathString.Left(myReverseFind(FullPathString,_T("\\"),FullPathString.GetLength()-1)+1);
		}else{
			FolderPath = FullPathString;
		}
		
		if(FullPathString.Right(1)!=_T("\\")){
			SearchIDX = myReverseFind(FullPathString,_T("\\"),FullPathString.GetLength()-1);

			if (SearchIDX <=0){
				ExistFlg = FALSE;
			}
            
			workIDX1 = SearchIDX;
			SearchIDX = myReverseFind(FullPathString,_T("\\"), workIDX1 - 1);
			if (SearchIDX <=0){
				ExistFlg = FALSE;
			}
		
 			workIDX2 = SearchIDX;
			SearchIDX = myReverseFind(FullPathString,_T("\\"), workIDX2 - 1);
			if (SearchIDX <=0){
				ExistFlg = FALSE;
			}

			workIDX3 = SearchIDX;
    
			if (ExistFlg == TRUE){
				if (!err)
				{
					lvi.iItem = index;
					lvi.iSubItem = 2;			
					if (FolderPath!=_T("")){
						lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FolderPath));
					}
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;			
				}

				FullPathString = FullPathString.Mid(SearchIDX +1, workIDX1 - workIDX3 -1);

				//myFileName = FolderPath;
				FullPathString.Replace(_T("\\"), _T(" - "));
				myFileName = FullPathString;
				// �t�@�C����
				if (!err)
				{
					lvi.iItem = index;
					lvi.iSubItem = 3;
					if (myFileName!=_T("")){
						lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileName));
					}
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;			
				}
			}
		}
	}

	CString tempCnt;
	tempCnt = _T("");

	tempCnt.Format(_T("%d"),index + 1);
	tempCnt=tempCnt + _T(" items");

	m_xvStCount = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempCnt));
	UpdateData(FALSE);
}

void CFileListCreatorDlg::iTunesAlbumList_Func(){
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		StatusStringSet(_T("iTunes Album�� �`�F�b�N ���s��"),0,FALSE); //�ύX 2012.06.14

		LastPrevItemCount = m_xcList.GetItemCount();
		CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

		int myResult;
		if(m_xcList.GetSelectedCount()==0){
			myResult = MessageBox(_T("�A�C�e�����I������Ă��܂���B���X�g�シ�ׂẴA�C�e�����ȗ������܂����H"),_T("iTunesAlbumList"),MB_YESNOCANCEL);
			if (myResult==IDYES){
				int index = 0;

				while(index < CFileListCreatorDlg::m_xcList.GetItemCount()){
					iTunesAlbumList_Items(index);
					index++;
				}
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("iTunes Album�� �`�F�b�N �L�����Z��"),300,FALSE);
				return;
			}
		}
		if(m_xcList.GetSelectedCount()>=1){
			myResult = MessageBox(_T("���X�g�シ�ׂẴA�C�e�����ȗ������܂����H\r\n(�u�������v�������� �I�����ꂽ�A�C�e���̂݊ȗ���)"),_T("iTunesAlbumList"),MB_YESNOCANCEL);
			if (myResult==IDYES){
				int index = 0;

				while(index < CFileListCreatorDlg::m_xcList.GetItemCount()){
					iTunesAlbumList_Items(index);
					index++;
				}
			}else if (myResult==IDNO){
				int index = -1;

				while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
				        (index, LVNI_ALL | LVNI_SELECTED)) != -1){
					iTunesAlbumList_Items(index);
				}
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("iTunes Album�� �`�F�b�N �L�����Z��"),300,FALSE);
				return;
			}
		}
	}


	Merge_Func();

	inFolder_Func();

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}

	CFileListCreatorDlg::StatusStringSet(_T("iTunes Album�� �`�F�b�N �I��"),300,TRUE);

}



void CFileListCreatorDlg::inFolder_Func(){
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

	UpdateData();
	lvi.mask = LVIF_TEXT;

	int index = 0;

	while(index < CFileListCreatorDlg::m_xcList.GetItemCount()){
		MSG msg; //�ǉ� 2012.04.04
		if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
			if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
				if (msg.wParam == VK_ESCAPE){
					ESCAPE_FLG = TRUE;
					break; //�I���B���b�Z�[�W���[�v�𔲂���B
				}
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			//continue; //�t�@�C�����R�s�[����Ƃ��̓R�����g��
		}

		// �t���p�X
		if (!err)
		{

			FullPathString =CFileListCreatorDlg::m_xcList.GetItemText(index,2);
			if (FullPathString !=_T("")){
				FullPathString.Replace(_T("%"),_T("%%"));
			}
		}
        
		if(FullPathString != _T("")){

			ULONGLONG tempByte = 0;
			tempByte = inFolder_Byte(FullPathString, _T("*.*"), 0);

			// �����悻�̃t�@�C���T�C�Y
			if (!err)
			{
				lvi.iItem = index;
				lvi.iSubItem = 4;
				CString tempSize;

				//TRACE(_T("!!!!%I64u\n"),myLongFileSize);

				tempSize = ByteCalculation(tempByte,FALSE);
				if(tempByte !=0 && tempSize!=_T("")){
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempSize));
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
				}
			}


			// �t�@�C���T�C�Y
			if (!err)
			{
				lvi.iItem = index;
				lvi.iSubItem = 5;
				CString tempSize;

				tempSize.Format(_T("%I64u"),tempByte);
				if(tempByte !=0 && tempSize!=_T("")){
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempSize));
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
				}
			}


			CTime tempTime = 0;
        
			tempTime = inFolder_Date(FullPathString, _T("*.*"), 0);


			if (CFileListCreatorDlg::m_xcList.GetItemText(index,7)==_T("")){
				//�C������
				CString myTime;
				myTime=_T("");

				myTime = tempTime.Format(_T("%Y/%m/%d %H:%M:%S"));
				if (!err)
				{
					lvi.iItem = index;
					lvi.iSubItem = 7;
					if(myTime!=_T("")){
						lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myTime));
						if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
					}
				}
			}

			if (CFileListCreatorDlg::m_xcList.GetItemText(index,6)==_T("")){
				//�C����
				CString myDate;
				myDate=_T("");
				myDate = tempTime.Format(_T("%Y/%m/%d"));
				if (!err)
				{
					lvi.iItem = index;
					lvi.iSubItem = 6;
					if(myDate!=_T("")){
						lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myDate));
						if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
					}
				}
			}
			//FullPathString.Replace(_T("%%"),_T("%"));
			index++;
		}
	}

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}
}

void CFileListCreatorDlg::OnItunesAlbumlist()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	CFileListCreatorDlg::iTunesAlbumList_Func();
}


void CFileListCreatorDlg::iTunes_Add_Artist_Func(BOOL FileOutputFLG){
	ESCAPE_FLG = FALSE;

	if ( FileOutputFLG == TRUE ){
		if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
			CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
			return;
		}else{

			LastPrevItemCount = m_xcList.GetItemCount();
			CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

			int myResult;

			myResult = IDCANCEL;

			CString CopyToSavePath;

			if(m_xcList.GetSelectedCount()>=1){
				myResult = MessageBox(_T("�t�@�C�����ɃA�[�e�B�X�g����t�����A���̃t�@�C�����R�s�[���܂��B\r\n\r\n�t�@�C���̕ۑ�����w�肵�܂����H\r\n�u�������v��I�������ꍇ�́A�}�C�h�L�������g�Ȃǂ̃f�t�H���g�t�H���_�ɕۑ�����܂��B\r\n\r\n\r\n (�\���ȋ󂫗e�ʂ�����t�H���_���w�肵�ĉ������B)"),_T("�ۑ���ݒ�m�F"),MB_YESNOCANCEL);

				CFileListCreatorDlg::StatusStringSet(_T("���y�t�@�C�����ҏW ���s��"),300,TRUE);
			}else{
				MessageBox(_T("�t�@�C����I����Ԃɂ��ĉ�����"),_T("��I��"),MB_YESNOCANCEL);
				return;
			}

			CString myPathname;

			CString FolderName;
			//CString CopyToSavePath;

			int Add_Artist_SUM_CNT;
			Add_Artist_SUM_CNT = 0;
			//
			int  Add_Artist_CNT_IDX;
			Add_Artist_CNT_IDX = 0;

			if (myResult==IDYES){


				TCHAR  szFolder[MAX_PATH];

				if( GetOpenFolderName( AfxGetMainWnd()->m_hWnd, NULL, szFolder, MAX_PATH ) == IDOK )
				{
					myPathname = CString(szFolder);
				}
			}

			if (myResult == IDYES ){
        
				//Call GetFolderPath//
				if (myPathname != _T("")){
					if (myPathname.Right(1) != _T("\\")){
						CopyToSavePath = myPathname + _T("\\");
					}else if (myPathname.Right(1) == _T("\\")){
						CopyToSavePath = myPathname;
					}

					myPathname.Replace(_T("\\"),_T("\\\\"));
            
					if (myPathname == _T("")){
					   CopyToSavePath = WindowsFolder_Func() + _T("\\\\");
					   //return;
					}
					myPathname = _T("");
				}
		   }else if (myResult == IDNO){

				CopyToSavePath = WindowsFolder_Func() + _T("\\\\");
				myPathname = _T("");

				CopyToSavePath.Replace(_T("\\\\"),_T("\\"));

			}else if (myResult == IDCANCEL || myPathname == _T("") ){
				CFileListCreatorDlg::StatusStringSet(_T("���y�t�@�C�����ҏW �L�����Z��"),300,TRUE);
				return;
			}
            
			FolderName = _T("Music_") + CreateDateTime(1);

			if(CreateDirectory(CopyToSavePath + FolderName,NULL)){

			}else{
			
			}
	
			//LVITEM       lvi;
			//int          index = 0;


			UpdateData();
			lvi.mask = LVIF_TEXT;
			CString FormatDataStr;

			//int i;


			if(m_xcList.GetSelectedCount()>=1){
				Add_Artist_SUM_CNT = m_xcList.GetSelectedCount();
			}

				//iTunesAlbumList_Items(index);

    
			CString FileName;

			Add_Artist_CNT_IDX = 0;

			int index = -1;

			while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
					(index, LVNI_ALL | LVNI_SELECTED)) != -1){

				MSG msg; //�ǉ� 2011.10.12
				if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
					if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
						if (msg.wParam == VK_ESCAPE){
							ESCAPE_FLG = TRUE;
							break; //�I���B���b�Z�[�W���[�v�𔲂���B
						}
					}
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					//continue; //�t�@�C�����R�s�[����Ƃ��̓R�����g��
				}

				CString FullPathString = CFileListCreatorDlg::m_xcList.GetItemText(index,2);

				if (FullPathString.Right(1)==_T("\\")){
					//CopyFolder_items(strTrgDir, _T("*.*"), TRUE, (CopyToSavePath + FolderName));
				}

				//http://www.ujasiri.com/prglib/vc/filectrl/vc_CopyFile/vc_CopyFile.html

				//============================================================

				CString myTempPath;
                        
				myTempPath = CFileListCreatorDlg::iTunes_Add_Artist_Items(FileOutputFLG,FullPathString,_T(""),(CopyToSavePath + FolderName),FALSE);
				FileName = myTempPath;

				//============================================================

				FullPathString.Replace(_T("\\"),_T("\\\\"));
				FileName.Replace(_T("\\"),_T("\\\\"));

				//http://oshiete.goo.ne.jp/qa/3399080.html?from=navi_ranking

				if ( PathFileExists(FullPathString)){
				//�t�@�C�����R�s�[����(�㏑���R�s�[������)
					myResult = CopyFile(static_cast<LPCTSTR>(FullPathString),static_cast<LPCTSTR>(FileName), FALSE);
					CString str;
					str.Format(_T("�t�@�C�����ɃA�[�e�B�X�g����t�����R�s�[�� (%d/%d) ") ,Add_Artist_CNT_IDX ,Add_Artist_SUM_CNT);
					CFileListCreatorDlg::StatusStringSet(str,0,FALSE);
					Add_Artist_CNT_IDX = Add_Artist_CNT_IDX + 1;
				}

				CString str;
				str.Format(_T("�t�@�C�����ɃA�[�e�B�X�g����t�����R�s�[�� (%d/%d) ") ,Add_Artist_CNT_IDX ,Add_Artist_SUM_CNT);
				CFileListCreatorDlg::StatusStringSet(str,0,FALSE);
			}
			if(Add_Artist_SUM_CNT >= 1){
				if(Add_Artist_CNT_IDX == 0){
					CFileListCreatorDlg::StatusStringSet(_T("�I�������A�C�e���̓��[�J���h���C�u�ɂP�������݂��܂���"),300,TRUE);
				}else{
					CFileListCreatorDlg::StatusStringSet(_T("��t�H���_�����J�n"),300,TRUE);
				}

					CString FileName;

					Add_Artist_CNT_IDX = 0;

					int index = -1;

					while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
							(index, LVNI_ALL | LVNI_SELECTED)) != -1){

						MSG msg; //�ǉ� 2011.10.12
						if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
							if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
								if (msg.wParam == VK_ESCAPE){
									ESCAPE_FLG = TRUE;
									break; //�I���B���b�Z�[�W���[�v�𔲂���B
								}
							}
							TranslateMessage(&msg);
							DispatchMessage(&msg);
							//continue; //�t�@�C�����R�s�[����Ƃ��̓R�����g��
						}

						CString FullPathString = CFileListCreatorDlg::m_xcList.GetItemText(index,2);

						if (FullPathString.Right(1)==_T("\\")){
							//CopyFolder_items(strTrgDir, _T("*.*"), TRUE, (CopyToSavePath + FolderName));
						}

						//http://www.ujasiri.com/prglib/vc/filectrl/vc_CopyFile/vc_CopyFile.html

						//============================================================

						CString myTempPath;
                        
						CFileListCreatorDlg::iTunes_Add_Artist_Items(FileOutputFLG,FullPathString,_T(""),(CopyToSavePath + FolderName),TRUE);
						Add_Artist_CNT_IDX++;

						CString str;
						str.Format(_T("��t�H���_���������폜�� (%d/%d) ") ,Add_Artist_CNT_IDX ,Add_Artist_SUM_CNT);
						CFileListCreatorDlg::StatusStringSet(str,0,FALSE);
					}


					CString FolderPath;
		
					FolderPath = CopyToSavePath + FolderName + _T("\\");

					//http://oshiete.goo.ne.jp/qa/976818.html
		
					FileName.Replace(_T("\\"),_T("\\\\"));
					FolderPath.Replace(_T("\\"),_T("\\\\"));

					//DeleteFile(FolderPath //http://www.ujasiri.com/prglib/vc/filectrl/vc_delfile.html
		
					RemoveDirectory(FolderPath); //http://oshiete.goo.ne.jp/qa/2899033.html

					// �f�B���N�g�����ꊇ�폜����
					// http://www.mfc-programming.com/2011/etc/mfc307.html

					//CString dir = FolderPath;
					//dir += "?";
					//dir.SetAt(dir.GetLength()-1,0);
 
					//SHFILEOPSTRUCT drive;
					//drive.hwnd  = this->m_hWnd;       // �E�B���h�E�n���h��
					//drive.wFunc = FO_DELETE;        // ���s���鑀��
					//drive.pFrom = dir;          // �Ώۃt�@�C����
					//drive.pTo   = NULL;         // �ړI�t�@�C����
					//drive.fFlags=  FOF_ALLOWUNDO ;   // �t���O
 
					//SHFileOperation(&drive);


					if ( PathIsDirectory(FolderPath) ) {  //http://oshiete.goo.ne.jp/qa/3399080.html?from=navi_ranking
						//http://msdn.microsoft.com/ja-jp/library/cc422072.aspx
						CFileListCreatorDlg::StatusStringSet(FolderName + _T(" �Ƃ����t�H���_�Ƀt�@�C�����R�s�[���܂���"),0,FALSE);
						
						MessageBox(FolderName + _T(" �Ƃ����t�H���_�Ƀt�@�C�����R�s�[���܂���"), _T("���y�t�@�C�����ҏW �I��"), MB_OK);
						
						CString FolderPath;
		
						FolderPath = CopyToSavePath + FolderName + _T("\\");
						FileName.Replace(_T("\\"),_T("\\\\"));
						FolderPath.Replace(_T("\\"),_T("\\\\"));

						//http://msdn.microsoft.com/ja-jp/library/cc422072.aspx
						//���G�N�X�v���[���ŊJ��
						//ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"),  _T("/select,") + FullPathToFileName(FileName) , FolderPath, SW_SHOWNORMAL );
						ShellExecute(NULL, _T("open"), FolderPath, NULL, NULL, SW_SHOWNORMAL);
					}else{
						CFileListCreatorDlg::StatusStringSet(_T("�I�������A�C�e���̓��[�J���h���C�u�ɂP�������݂��܂���"),300,TRUE);
					}
					//return;
			}
		}
		//Bold_CNT_IDX = 0;
		//Bold_SUM_CNT = 0;

		//Call StatusStringSet("")
    
		//Worksheets("WORK").Cells(4, 2).Value = ""  ''�ۑ���p�X���폜
	}else if (FileOutputFLG == FALSE){

		::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
		::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

		//LVITEM       lvi;
		int          err = 0;	
		CString      FullPathString;
		CString      myFileName;	

		lvi.mask = LVIF_TEXT;// | LVIF_PARAM;


   		int        index = -1;
    		CString    str;

		int myCnt = 0;

		while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
			(index, LVNI_ALL | LVNI_SELECTED)) != -1)
		{

			myCnt++;
		}
	
		int myResult;
		CString tempCnt;

		if(myCnt==0){
			myResult = MessageBox(_T("���X�g�シ�ׂẴA�C�e���ɃA�[�e�B�X�g����t�^���܂����H"),_T("�A�[�e�B�X�g�� �t�^"),MB_YESNOCANCEL);
			if(myResult == IDYES){
				index = 0;
				while(index < CFileListCreatorDlg::m_xcList.GetItemCount())
				{
					err = 0;
					FullPathString =_T("");
					myFileName=_T("");

					// �t���p�X
					if (!err)
					{
						FullPathString = CFileListCreatorDlg::m_xcList.GetItemText(index,2);
						//FullPathString.Replace(_T("%"),_T("%%"));
					}

					// �t�@�C����
					if (!err)
					{
						myFileName = CFileListCreatorDlg::m_xcList.GetItemText(index,3);
						//FullPathString.Replace(_T("%"),_T("%%"));
					}

				
					myFileName = iTunes_Add_Artist_Items(FALSE, FullPathString, myFileName, _T(""),FALSE);

					if (!err)
					{
						//lvi.mask = LVIF_TEXT | LVIF_PARAM;
			            lvi.iItem = index;
				 		lvi.iSubItem = 3;
						lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileName));//�t�@�C����
			            if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
					}
					index++;
				}
				CFileListCreatorDlg::StatusStringSet(_T("�A�[�e�B�X�g����t�^���܂���"),300,TRUE);

			}
		}else if(myCnt>=1){
			int myCnt = 0;
			index = -1;
			while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
				(index, LVNI_ALL | LVNI_SELECTED)) != -1)
			{
				err = 0;
				FullPathString =_T("");
				myFileName=_T("");

				// �t���p�X
				if (!err)
				{
					FullPathString = CFileListCreatorDlg::m_xcList.GetItemText(index,2);
					//FullPathString.Replace(_T("%"),_T("%%"));
				}

				// �t�@�C����
				if (!err)
				{
					myFileName = CFileListCreatorDlg::m_xcList.GetItemText(index,3);
					//FullPathString.Replace(_T("%"),_T("%%"));
				}

				
				myFileName = iTunes_Add_Artist_Items(FALSE, FullPathString, myFileName, _T(""),FALSE);

				if (!err)
				{
					//lvi.mask = LVIF_TEXT | LVIF_PARAM;
			        lvi.iItem = index;
				 	lvi.iSubItem = 3;
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileName));//�t�@�C����
			        if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
				}

				myCnt++;
			}

			//CString tempCnt;
			tempCnt = _T("");
			if(myCnt>=1){ //�ǉ� 2012.06.14
				tempCnt.Format(_T("%d"),myCnt);
				tempCnt=tempCnt + _T(" ���̃A�C�e���ɃA�[�e�B�X�g����t�^���܂���");
			}else{
				tempCnt=_T("�A�C�e�����I������Ă��Ȃ����߁A�A�[�e�B�X�g����t�^�ł��܂���");
			}
			CFileListCreatorDlg::StatusStringSet(tempCnt,300,TRUE);
		}
	}
}


CString CFileListCreatorDlg::iTunes_Add_Artist_Items(BOOL FileOutputFLG, CString inFile, CString tempFileName, CString myFolderPath, BOOL DEL_FolderFLG){

	if(DEL_FolderFLG == TRUE){
		FileOutputFLG = TRUE;
	}

	if ( FileOutputFLG == TRUE ) {
		BOOL ExistFlg;
    
		ExistFlg = TRUE;


		int SearchIDX;

		SearchIDX = myReverseFind(inFile, _T("\\"),inFile.GetLength()-1);
		if(SearchIDX < 0){
			ExistFlg = FALSE;
		}

		int workIDX1;
		workIDX1 = SearchIDX;

		SearchIDX = myReverseFind(inFile, _T("\\"),workIDX1 - 1);
		if(SearchIDX < 0){
			ExistFlg = FALSE;
		}

		int workIDX2;
		workIDX2 = SearchIDX;
    
		SearchIDX = myReverseFind(inFile, _T("\\"),workIDX2 - 1);
		if(SearchIDX < 0){
			ExistFlg = FALSE;
		}

		int workIDX3;
		workIDX3 = SearchIDX;
		if(SearchIDX < 0){
			ExistFlg = FALSE;
		}

		CString tempDir;
                
		if(ExistFlg == TRUE){
			CString tempArtist;
			tempArtist = inFile.Mid(workIDX3 + 1, workIDX2 - workIDX3 - 1);
			tempArtist = tempArtist + _T(" - ") + inFile.Mid(myReverseFind(inFile,_T("\\"), inFile.GetLength()-1) + 1);

			tempDir = inFile.Mid(workIDX2 + 1, workIDX1 - workIDX2 - 1);

			if(CreateDirectory(myFolderPath + _T("\\") + tempDir + _T("\\") , NULL)){

			}else{
			
			}

			if(DEL_FolderFLG == TRUE){
				CString FolderPath;

				FolderPath = myFolderPath + _T("\\") + tempDir + _T("\\");

				//http://oshiete.goo.ne.jp/qa/976818.html
		
				FolderPath.Replace(_T("\\"),_T("\\\\"));

				//DeleteFile(FolderPath //http://www.ujasiri.com/prglib/vc/filectrl/vc_delfile.html
		
				RemoveDirectory(FolderPath); //http://oshiete.goo.ne.jp/qa/2899033.html

				return FolderPath;
			}

			return myFolderPath + _T("\\") + tempDir + _T("\\") + tempArtist;
		}else{
			return inFile;
		}
	}else{ // if ( FileOutputFLG == FALSE ) {

		BOOL ExistFlg;
    
		ExistFlg = TRUE;


		int SearchIDX;

		SearchIDX = myReverseFind(inFile, _T("\\"),inFile.GetLength()-1);
		if(SearchIDX < 0){
			ExistFlg = FALSE;
		}

		int workIDX1;
		workIDX1 = SearchIDX;

		SearchIDX = myReverseFind(inFile, _T("\\"),workIDX1 - 1);
		if(SearchIDX < 0){
			ExistFlg = FALSE;
		}

		int workIDX2;
		workIDX2 = SearchIDX;
    
		SearchIDX = myReverseFind(inFile, _T("\\"),workIDX2 - 1);
		if(SearchIDX < 0){
			ExistFlg = FALSE;
		}

		int workIDX3;
		workIDX3 = SearchIDX;
		if(SearchIDX < 0){
			ExistFlg = FALSE;
		}
                
		if(ExistFlg == TRUE){
			CString tempArtist;
			tempArtist = inFile.Mid(workIDX3 + 1, workIDX2 - workIDX3 - 1);
			tempArtist = tempArtist + _T(" - ") + tempFileName;

			return tempArtist;
		}else{
			return tempFileName;
		}
	}

}

void CFileListCreatorDlg::OnItunesAddartiststr()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if( CFileListCreatorDlg::m_xcList.GetItemCount() <=0){
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	if(m_xcList.GetItemCount() >= 1) {
		int myResult;

		myResult = MessageBox(_T("���X�g��̃t�@�C�����ɃA�[�e�B�X�g����t�^���܂����H\r\n\r\n�u�͂��v���X�g��̃t�@�C�����ɃA�[�e�B�X�g����t�^\r\n�u�������v�t�@�C������ύX������Ńt�@�C�����R�s�[") ,_T("�����I��"), MB_YESNOCANCEL );
		
		if (myResult == IDNO){
			iTunes_Add_Artist_Func(TRUE);
		}else if (myResult == IDYES){
			iTunes_Add_Artist_Func(FALSE);
		}
	}
}


void CFileListCreatorDlg::OnEditlistReplace()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	FindIDX = -1;

	//���[�_���X�P
	CDialog *m_pDlg;
	m_pDlg = new ReplaceDlg(this);
	m_pDlg->Create(IDD_DIALOG_Replace);

	m_pDlg->ShowWindow(true);

	////���[�_��
	//ReplaceDlg m_dlg;
	//m_dlg.DoModal();
}


void CFileListCreatorDlg::OnMenuSelectallcancellation()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	SelectALL_CancellationFunc();
}

CString CFileListCreatorDlg::fileUpdatedRecently(CString fpath,int workRow)
{
	//�y��Łz�t�@�C�������݂��邩�H���m���߂�B

	CFileListCreatorDlg::StatusStringSet(_T("���t�����㏑��"),0,FALSE);

	//LVITEM       lvi;
	//int          index = 0;
	int          err = 0;
	CString      str;	
	CString      FullPathString;

	CString myFileName;
	CString myFileSize;
	//ULONGLONG myLongFileSize;

	CString myDate;
	CString myTime;

	CString tempDate;	

	FullPathString =_T("");

	myFileName=_T("");
	//myFileSize = _T("");
	//myLongFileSize = -1;
	myDate = _T("");
	myTime = _T("");


	//http://oshiete.goo.ne.jp/qa/3399080.html?from=navi_ranking �Ńt�H���_��t�@�C���̑��݊m�F������



	CTime cTime;
	CFile* pFile = NULL;
	CString workDate;

	FullPathString = fpath;

	workDate=_T("");

	lvi.mask = LVIF_TEXT;// | LVIF_PARAM;

	if(FullPathString.Right(1)!=_T("\\")){
		try
		{
			//FullPathString.Replace(_T("%%"),_T("%"));

			CFile pFile(FullPathString, CFile::modeRead  | CFile::shareDenyNone);

			FullPathString.Replace(_T("%"),_T("%%"));

			CFileStatus status;

			if(pFile.GetStatus(status))    // virtual member function
			{

				//�C������
				if (!err)
				{
					workDate = CFileListCreatorDlg::m_xcList.GetItemText(workRow, 7);
					if(workDate == _T("")) {
						cTime = status.m_mtime;
						myDate = cTime.Format(_T("%Y/%m/%d")); //Format(tdate, "yyyy/mm/dd")
						myTime = cTime.Format(_T("%Y/%m/%d %H:%M:%S"));						//Format(tdate, "yyyy/mm/dd hh:mm:ss")
						//tempDate = myDate;
					}else{
						//http://homepage1.nifty.com/MADIA/vc/vc_bbs/200412/200412_04120032.html
						  
						COleDateTime pd;
						if( pd.ParseDateTime( workDate ))
						{
							myDate = pd.Format(_T("%Y/%m/%d"));

							myTime = pd.Format(_T("%Y/%m/%d %H:%M:%S")); //Format(tdate, "yyyy/mm/dd")
															//Format(tdate, "yyyy/mm/dd hh:mm:ss"
						}
						else
						{
							TRACE("��͕s�\\n");
						}
					}			
				}

			}	
			pFile.Close();
		}
		catch (CFileException* pEx)
		{
			//pEx->ReportError();
			pEx->Delete();

			//myFileName =_T("");
			//myFileSize = _T("");
			//myLongFileSize = -1;
			//workDate == _T("");

		}

		if (pFile != NULL)
		{
			
			pFile->Close();
			delete pFile;
		} 
	


		//if (CFileListCreatorDlg::m_xcList.GetItemText(workRow,7)==_T("")){			//�C������
			if (!err)
			{
				lvi.iItem = workRow;
				lvi.iSubItem = 7;
				if(myTime!=_T("")){
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myTime));
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
				}
			}
		//}

		//if (CFileListCreatorDlg::m_xcList.GetItemText(workRow,6)==_T("")){			//�C����
			if (!err)
			{
				lvi.iItem = workRow;
				lvi.iSubItem = 6;
				if(myDate!=_T("")){
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myDate));
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
				}
			}
		//}

		TRACE(FullPathString);
		UpdateData(FALSE);
	}else{//if(FullPathString.Right(1)==_T("\\")){                    

		CTime tempTime = 0;
        
        tempTime = inFolder_Date(FullPathString, _T("*.*"), 0);


		//if (CFileListCreatorDlg::m_xcList.GetItemText(workRow,7)==_T("")){
			//�C������
			CString myTime;
			myTime=_T("");

			myTime = tempTime.Format(_T("%Y/%m/%d %H:%M:%S"));
			if (!err)
			{
				lvi.iItem = workRow;
				lvi.iSubItem = 7;
				if(myTime!=_T("")){
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myTime));
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
				}
			}
		//}

		//if (CFileListCreatorDlg::m_xcList.GetItemText(workRow,6)==_T("")){
			//�C����
			CString myDate;
			myDate=_T("");
			myDate = tempTime.Format(_T("%Y/%m/%d"));
			if (!err)
			{
				lvi.iItem = workRow;
				lvi.iSubItem = 6;
				if(myDate!=_T("")){
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(myDate));
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
				}
			}
		//}
		UpdateData(FALSE);
	}

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return _T("");
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}

	CFileListCreatorDlg::StatusStringSet(_T("���t�����㏑���F�I��"),0,FALSE);
	return myTime;
}

CTime CFileListCreatorDlg::CStringToDate(CString strDate)
{
    //http://sphere42.mlexp.com/techlib/2011/02/vc.html

	if (strDate != _T("")) {
		 COleDateTime oleTime;
		 if ( oleTime.ParseDateTime(strDate) ) {
			 return (time_t)oleTime; //(CTime) //http://oshiete.goo.ne.jp/qa/6579646.html
		 }else{
			 
		 }
	}
	
	//MessageBox(_T("�s���ȓ��t�F") + strDate);

	return CTime(0);
}

void CFileListCreatorDlg::OnFilterDatefilter()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	//LastPrevItemCount = m_xcList.GetItemCount();
	//CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	//���[�_���X�P
	CDialog *m_pDlg;
	m_pDlg = new DateFilterDlg(this);
	m_pDlg->Create(IDD_DIALOG_DateFilter);

	m_pDlg->ShowWindow(true);
}


int CFileListCreatorDlg::SetToRed(int FormatDataNum)
{

	if(FormatDataNum == 11){
		//FormatDataStr = _T("NORMAL,BLACK,");
		FormatDataNum = 21;
	}

	if(FormatDataNum == 12){
		//FormatDataStr = _T("BOLD,BLACK,");
		FormatDataNum = 22;
	}

	if(FormatDataNum == 21){
		//FormatDataStr = _T("NORMAL,RED,");
		FormatDataNum = 21;
	}

	if(FormatDataNum == 22){
		//FormatDataStr = _T("BOLD,RED,");
		FormatDataNum = 22;
	}
	return FormatDataNum;
}

int CFileListCreatorDlg::SetToBold(int FormatDataNum)
{
	if(FormatDataNum == 11){
		//FormatDataStr = _T("NORMAL,BLACK,");
		FormatDataNum = 12;
	}

	if(FormatDataNum == 12){
		//FormatDataStr = _T("BOLD,BLACK,");
		FormatDataNum = 12;
	}

	if(FormatDataNum == 21){
		//FormatDataStr = _T("NORMAL,RED,");
		FormatDataNum = 22;
	}

	if(FormatDataNum == 22){
		//FormatDataStr = _T("BOLD,RED,");
		FormatDataNum = 22;
	}

	return FormatDataNum;
}

int CFileListCreatorDlg::SetToBoldAndRedInversion(int workRow)
{
	int FormatDataNum;

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return FALSE;
	}

	int	index = -1;
	int	LastSelected = -1;

	if (workRow==-1){
		//index = -1;
		//while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
		//	(index,LVNI_SELECTED)) != -1)
		//{
		//	if (index != -1){
		//		LastSelected = index;
		//	}
		//}
		//if (LastSelected!=-1){
		//	//if (m_xcList.GetItemState(LastSelected,LVIS_FOCUSED | LVIS_SELECTED) == TRUE){
		//		FormatDataNum = m_Dlg->m_xcList.GetItemData(LastSelected);
		//	//}
		//}
	}else{
		FormatDataNum = m_Dlg->m_xcList.GetItemData(workRow);
	}


	if ( m_xvChkEasySelect == TRUE ){
		if (FormatDataNum == 12){
			FormatDataNum = 11; //�m�[�}����
		}else if(FormatDataNum == 22){
			FormatDataNum = 21; //�m�[�}����
		}else if(FormatDataNum == 11){
			FormatDataNum = 12; //��������
		}else if(FormatDataNum == 21 ){ 
			FormatDataNum = 22; //��������
		}else{
			FormatDataNum = 11;
		}
	}
	

	//if ( m_xvChkRedOnMode == TRUE ){
	//	if(FormatDataNum == 21){
	//		FormatDataNum = 11; //���F��
	//	}else if(FormatDataNum == 22){
	//		FormatDataNum = 12; //���F��
	//	}else if (FormatDataNum == 11){
	//		FormatDataNum == 21; //�ԐF��
	//	}else if (FormatDataNum == 12){
	//		FormatDataNum = 22; //�ԐF��
	//	}else{
	//		FormatDataNum = 11;
	//	}
	//}

	if (workRow!=-1){
		//if (m_xcList.GetItemState(LastSelected,LVIS_FOCUSED | LVIS_SELECTED) == TRUE){
			m_Dlg->m_xcList.SetItemData(workRow,FormatDataNum);

			CString FormatDataStr = _T("NORMAL,BLACK,");

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

			//LVITEM       lvi;

			lvi.iItem = workRow;
			lvi.iSubItem = 9;
			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

			m_Dlg->m_xcList.SetItem(&lvi);
			UpdateData(FALSE);

			m_Dlg->SetStrFormat_Func();

			m_Dlg->Total_Bytes_Bold();
			m_Dlg->Total_Bytes_Func();
			m_Dlg->ItemCount_Func(TRUE);
		//}
	}

	//}
	//if(FormatDataNum == 11){
	//	//FormatDataStr = _T("NORMAL,BLACK,");
	//}

	//if(FormatDataNum == 12){
	//	//FormatDataStr = _T("BOLD,BLACK,");
	//}

	//if(FormatDataNum == 21){
	//	//FormatDataStr = _T("NORMAL,RED,");
	//}

	//if(FormatDataNum == 22){
	//	//FormatDataStr = _T("BOLD,RED,");
	//}

	return FormatDataNum;
}

void CFileListCreatorDlg::OnBnClickedCancel()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	if(m_xcList.GetItemCount() >= 1) {
		if (ListDataNoChange_FLG == TRUE){ //�ǉ� 2012.05.13
			CFileListCreatorDlg::StatusStringSet(_T("See you, again!!"),0,TRUE);

			AutoSaveMode_ReadOrWrite_Func(_T("write"));
			UseUNDO_Mode_ReadOrWrite_Func(_T("write"));

			delete PrevListPtr; //�ǉ� 2012.05.13
			delete NowListPtr; //�ǉ� 2012.05.13
			delete WorkListPtr; //�ǉ� 2012.05.13

			CDialogEx::OnOK();

		}else{
			int myResult = MessageBox(_T("���X�g�t�@�C����ۑ����Ă���I�����܂����H"),_T("Quit confirmation"),MB_YESNOCANCEL);
			if(myResult == IDYES){
				OnMenuFileSave();
			
				CFileListCreatorDlg::StatusStringSet(_T("AutoSave ����"),0,FALSE);
				//CFileListCreatorDlg::StatusStringSet(_T("See you, again!!"),500,TRUE);

				AutoSaveMode_ReadOrWrite_Func(_T("write"));
				UseUNDO_Mode_ReadOrWrite_Func(_T("write"));

				delete PrevListPtr; //�ǉ� 2012.05.13
				delete NowListPtr; //�ǉ� 2012.05.13
				delete WorkListPtr; //�ǉ� 2012.05.13

				CDialogEx::OnOK();
			}else if(myResult == IDNO){
				CDialogEx::OnOK();
			}

		}
	}else{
		OnMenuFileSave();

		delete PrevListPtr; //�ǉ� 2012.05.13
		delete NowListPtr; //�ǉ� 2012.05.13
		delete WorkListPtr; //�ǉ� 2012.05.13

		CDialogEx::OnOK();
	}

}

////http://msdn.microsoft.com/ja-jp/library/2d9cs4b6(v=VS.100).aspx
//void CFileListCreatorDlg::OnCancel(){
//	CDialog::OnCancel();
//}


//http://hp.vector.co.jp/authors/VA023539/tips/dialog/001.htm
//LRESULT CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);
//

//http://f12.aaa.livedoor.jp/~qsrqst/newc/sdk5-9.html
//http://rararahp.cool.ne.jp/cgi-bin/lng/vc/vclng.cgi?print+200711/07110073.txt
//http://wisdom.sakura.ne.jp/system/winapi/win32/win66.html
//http://www.kumei.ne.jp/c_lang/sdk3/sdk_292.htm
//http://www.geocities.jp/ky_webid/win32c/031.html
//http://www13.plala.or.jp/kmaeda/winc/esc.htm


void CFileListCreatorDlg::OnBnClickedChkAutosave()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	//http://www.ujasiri.com/prglib/vc/compo/vc_chkboxsap.html
	CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_AutoSave);
	
	if(chkbox1->GetCheck()){
		m_xvChkAutoSave = TRUE;
		//chkbox1->SetCheck(0);
	}else{
		m_xvChkAutoSave = FALSE;
		//chkbox1->SetCheck(1);
	}
}


void CFileListCreatorDlg::OnAutosaveAutosaveon()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_AutoSave);
	
	m_xvChkAutoSave = TRUE;
	chkbox1->SetCheck(1);
}


void CFileListCreatorDlg::OnAutosaveAutosaveoff()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_AutoSave);
	
	m_xvChkAutoSave = FALSE;
	chkbox1->SetCheck(0);
}


void CFileListCreatorDlg::AutoSaveMode_ReadOrWrite_Func(CString mySwitch)
{
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	CString WriteData1;

	if (mySwitch == _T("write")){ //write
		CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_AutoSave);
		
		if(chkbox1->GetCheck()){
			//chkbox1->SetCheck(0);
			WriteData1 = _T("AutoSaveON");
		}else{
			//chkbox1->SetCheck(1);
			WriteData1 = _T("AutoSaveOFF");
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
			if (!stdFile1.Open(CurDir + _T("\\AutoSave.dat"), 
				CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::modeNoTruncate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText
		}
		if (mySwitch == _T("write")){
			if (!stdFile1.Open(CurDir + _T("\\AutoSave.dat"), 
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



	if(mySwitch == _T("read")){ //read
		int k;
		k = 0;
		CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_AutoSave);

		if (stdFile1.ReadString(rstr) == FALSE) err = 1;
		if(!err){
			if (rstr==_T("") || rstr==_T("AutoSaveON")){
				chkbox1->SetCheck(1);
				m_Dlg->m_xvChkAutoSave = TRUE;
			}else{
				chkbox1->SetCheck(0);
				m_Dlg->m_xvChkAutoSave = FALSE;
			}
		}else{
			chkbox1->SetCheck(1);
			m_Dlg->m_xvChkAutoSave = TRUE;
		}

		// (6)�N���[�Y(�����I)
		stdFile1.Close();
	}
}

void CFileListCreatorDlg::UseUNDO_Mode_ReadOrWrite_Func(CString mySwitch)
{
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	CString WriteData1;

	if (mySwitch == _T("write")){ //write
		CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_UseUNDO);
		
		if(chkbox1->GetCheck()){
			//chkbox1->SetCheck(0);
			WriteData1 = _T("UseUNDO_ON");
		}else{
			//chkbox1->SetCheck(1);
			WriteData1 = _T("UseUNDO_OFF");
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
			if (!stdFile1.Open(CurDir + _T("\\UseUNDO.dat"), 
				CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::modeNoTruncate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText
		}
		if (mySwitch == _T("write")){
			if (!stdFile1.Open(CurDir + _T("\\UseUNDO.dat"), 
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



	if(mySwitch == _T("read")){ //read
		int k;
		k = 0;
		CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_UseUNDO);

		if (stdFile1.ReadString(rstr) == FALSE) err = 1;
		if(!err){
			if (rstr==_T("") || rstr==_T("UseUNDO_OFF")){
				chkbox1->SetCheck(0);
				m_Dlg->m_xvChkUseUNDO = FALSE;
			}else{
				chkbox1->SetCheck(1);
				m_Dlg->m_xvChkUseUNDO = TRUE;
			}
		}else{
			chkbox1->SetCheck(0);
			m_Dlg->m_xvChkUseUNDO = FALSE;
		}

		// (6)�N���[�Y(�����I)
		stdFile1.Close();
	}
}

void CFileListCreatorDlg::OnBnClickedOk()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	if (m_xvChkAutoSave == TRUE){
		//CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

		//if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		//	return;
		//}

		//m_xvRadioModifyDate=1;
		//m_xvRadioRemarksColumn=2;
		//m_xvChkCopyOn=TRUE;
		//m_xvChkRedOn=TRUE;

		//m_Dlg->g_RadioModifyDate=1;
		//m_Dlg->g_RadioRemarksColumn=2; //��ŕς���
		//m_Dlg->g_ChkCopyOn=TRUE;
		//m_Dlg->g_ChkRedOn=TRUE;

		//m_Dlg->GetStrFormat_Func();
		//m_Dlg->ExportFileList(TRUE);
		//m_Dlg->SetStrFormat_Func();
		if (ListDataNoChange_FLG == TRUE){ //�ǉ� 2012.05.13
			CFileListCreatorDlg::StatusStringSet(_T("See you, again!!"),0,TRUE);

			AutoSaveMode_ReadOrWrite_Func(_T("write"));
			UseUNDO_Mode_ReadOrWrite_Func(_T("write"));

			delete PrevListPtr; //�ǉ� 2012.05.13
			delete NowListPtr; //�ǉ� 2012.05.13
			delete WorkListPtr; //�ǉ� 2012.05.13
			
			CDialogEx::OnOK();
		}else{

			OnMenuFileSave();
			
			CFileListCreatorDlg::StatusStringSet(_T("AutoSave ����"),0,FALSE);
			//CFileListCreatorDlg::StatusStringSet(_T("See you, again!!"),500,TRUE);

			AutoSaveMode_ReadOrWrite_Func(_T("write"));
			UseUNDO_Mode_ReadOrWrite_Func(_T("write"));

			delete PrevListPtr; //�ǉ� 2012.05.13
			delete NowListPtr; //�ǉ� 2012.05.13
			delete WorkListPtr; //�ǉ� 2012.05.13

			CDialogEx::OnOK();
		}
	}else{
		AutoSaveMode_ReadOrWrite_Func(_T("write"));
		UseUNDO_Mode_ReadOrWrite_Func(_T("write"));

		delete PrevListPtr; //�ǉ� 2012.05.13
		delete NowListPtr; //�ǉ� 2012.05.13
		delete WorkListPtr; //�ǉ� 2012.05.13

		CDialogEx::OnOK();
	}
}


void CFileListCreatorDlg::OnMenuFileSave()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->g_RadioModifyDate=0;  //�C�����\��
	m_Dlg->g_RadioRemarksColumn=0; //���l���\��
	m_Dlg->g_ChkCopyOn=TRUE;
	m_Dlg->g_ChkRedOn=TRUE;

	m_Dlg->GetStrFormat_Func();
	m_Dlg->ExportFileList(TRUE);
	m_Dlg->SetStrFormat_Func();

	ListDataNoChange_FLG = TRUE; //�ǉ� 2012.05.13

	m_Dlg->SetWindowText(_T("FileListCreator"));

	//CDialogEx::OnOK();
}


void CFileListCreatorDlg::AutoImportFileList(){
	//http://rararahp.cool.ne.jp/vc/vctips/api.htm
	// ���s�t�@�C���̃t���p�X�擾
	TCHAR szPath[_MAX_PATH];
	GetModuleFileName( NULL, szPath, MAX_PATH);

	//// �t���p�X�𕪉�
	//TCHAR szDir[_MAX_DIR];
	//TCHAR szDrive[_MAX_DRIVE];
	//TCHAR szFName[_MAX_FNAME];
	//TCHAR szExt[_MAX_EXT];
	//_splitpath(szPath,szDrive,szDir,szFName,szExt);
	//
	//// �t�H���_�A�t�@�C�����擾
	//TCHAR szFilePath[_MAX_PATH];
	//TCHAR szFileName[_MAX_PATH];
	//sprintf(szFilePath,"%s%s",szDrive,szDir);
	//sprintf(szFileName,"%s%s",szFName,szExt);

	ESCAPE_FLG = FALSE;

	CString CurDir;
	CurDir = szPath;

	CurDir = CurrentDirFunc(CurDir,TRUE);
	if (CurDir !=_T("")){
		CurDir.Replace(_T("\\"),_T("\\\\"));
	}

	CString importFilePath;

	importFilePath = CurDir + _T("\\\\") + _T("FileListCreator(Pref)") + _T("\\\\") + _T("AutoSave.html");
	
	if ( PathFileExists(importFilePath) ){
		DoWithCnt = 0;
		TotalItemsCount = CFileListCreatorDlg::FileListItemsCount(importFilePath); //�ǉ� 2012.07.26
	}

	if ( PathFileExists(importFilePath) ){
		CFileListCreatorDlg::importFileList_Func(importFilePath,FALSE);

		CFileListCreatorDlg::SetStrFormat_Func(); //�ǉ� 2012.04.04
		CFileListCreatorDlg::Total_Bytes_Bold(); //�ǉ� 2012.04.04
		CFileListCreatorDlg::Total_Bytes_Func(); //�ǉ� 2012.04.04
		CFileListCreatorDlg::ItemCount_Func(TRUE); //�ǉ� 2012.04.04
	}

	ListDataNoChange_FLG = TRUE; //�ǉ� 2012.05.13
	//AfxGetMainWnd()->SetWindowText(_T("FileListCreator")); //�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	m_Dlg->SetWindowText(_T("FileListCreator"));
}

void CFileListCreatorDlg::OnFileRecovery()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	int myResult = MessageBox(_T("���݂̃��X�g�t�@�C�����폜���āA�O��̃f�[�^�ŕ��A���܂����H"),_T("Recovery confirmation"),MB_YESNOCANCEL);
	if(myResult == IDYES){

		// Delete all of the items from the list view control.
		CFileListCreatorDlg::m_xcList.DeleteAllItems();
		//ASSERT(m_myListCtrl.GetItemCount() == 0);

		CFileListCreatorDlg::StatusStringSet(_T("���ׂč폜���܂���"),300,TRUE);
		CString tempCnt;
		tempCnt = _T("");

		tempCnt.Format(_T("%d"),CFileListCreatorDlg::m_xcList.GetItemCount());
		tempCnt=tempCnt + _T(" items");

		m_xvStCount = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempCnt));
		//CFileListCreatorDlg::m_xcList.EnsureVisible(index-1, FALSE);
		UpdateData(FALSE);

		AutoImportFileList();
		SetStrFormat_Func();

		ListDataNoChange_FLG = TRUE; //�ǉ� 2012.05.13
		//AfxGetMainWnd()->SetWindowText(_T("FileListCreator")); //�ǉ� 2012.05.13

		CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

		if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
			return;
		}

		m_Dlg->SetWindowText(_T("FileListCreator"));
	}
}


CString CFileListCreatorDlg::myStrToLower_Func(CString FileSpecStr)
{
//http://oshiete.goo.ne.jp/qa/6356162.html

	 int i;
	//StringToCharFunc(FileSpecStr)

 	int     sizeOfString = (FileSpecStr.GetLength() + 1);
	LPTSTR  lpsz = new TCHAR[ sizeOfString ];
	_tcscpy_s(lpsz, sizeOfString, FileSpecStr);
	//... modify lpsz as much as you want
	//return lpsz[sizeOfString];
	//delete[] lpsz;

	 for(i=0;i<sizeOfString;i++){
		 if(lpsz[i]=='\0')/*������̏I���Ȃ甲����*/{
			break;
		 }else if(isupper(lpsz[i])){
			lpsz[i]=tolower(lpsz[i]);
		 //else if(islower(lpsz[i]))
			//lpsz[i]=toupper(lpsz[i]);
		}
	 }

	 CString RetStr;
	 RetStr = lpsz;
	 return RetStr;
	 delete[] lpsz;
}

CString CFileListCreatorDlg::ReadOrWritePlayList_Func(CString mySwitch,CString FilePath,CString BuffList,CString SaveFileName)
{
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return _T("");
	}


	CStdioFile    stdFile1;
	CString       wstr, rstr;
	LPTSTR        rstrBuf = NULL;
	int           err = 0;

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
	CurDir = CurDir + _T("\\FileListCreator(LIST)");
	if(CreateDirectory(CurDir,NULL)){

	}
	else {
			
	}

	//MessageBox (CurDir + _T("\\") + SaveFileName + _T(".flc"));
	// (1)�ǂݏ����p�ɃI�[�v��
	if (!err)
	{
		//http://www.g-ishihara.com/mfc_fi_01.htm
		if (mySwitch == _T("m3u_read_temp")){
			//if (!stdFile1.Open(CurDir + _T("\\") + _T("temp.flc.m3u"),
			//	CFile::modeReadWrite | CFile::shareDenyNone | 
			//	CFile::modeCreate | CFile::modeNoTruncate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText  //CFile::modeNoTruncate //�R�����g�� 2012.07.12
		}

		if (mySwitch == _T("m3u_read")){
			if (!stdFile1.Open(CurDir + _T("\\") + SaveFileName, //_T(".m3u"), //�폜 2012.07.12
				CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::modeNoTruncate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText  //CFile::modeNoTruncate //�R�����g�� 2012.07.12
		}

		if (mySwitch == _T("wpl_read")){
			if (!stdFile1.Open(CurDir + _T("\\") + SaveFileName + _T(".flc"),
				CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::modeNoTruncate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText
		}
		if (mySwitch == _T("wpl_write")){
			if (!stdFile1.Open(CurDir + _T("\\") + SaveFileName + _T(".flc"),
				CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText
		}
		if (mySwitch == _T("m3u_write")){
			if (!stdFile1.Open(CurDir + _T("\\") + SaveFileName + _T(".m3u"),  
				CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText
		}
	}


	if(mySwitch == _T("m3u_write")){ //write //��ŃR�[�f�B���O
		CString PlayListData=_T("");

		CString TempStr;
		CString FileName;

		FileName =_T("");
		int i=0;
		int StartIDX = 0;
		int EndIDX = 0;

		BOOL QuotStartFLG = FALSE;
		BOOL SpaceStartFLG = FALSE;

		TempStr = BuffList;

		while (i<=TempStr.GetLength()-1){
			//TempStr = BuffList; //�R�����g�� 2012.07.12

			if (TempStr.Mid(i,1) == _T("\"")){
				if(QuotStartFLG == FALSE){
					QuotStartFLG  = TRUE;
					StartIDX = i;

				}else if (QuotStartFLG == TRUE){
					QuotStartFLG = FALSE;
					EndIDX = i;

					FileName = TempStr.Mid(StartIDX+1,EndIDX-StartIDX-1);
					i++;
					//������FileName���������镶�������ĉ������I
					PlayListData = PlayListData + _T("\n") + _T("#EXTINF:0,") + FileName.Mid(myReverseFind(FileName, _T("\\"),FileName.GetLength()-1) + 1) + _T("\n") + FileName + _T("\n");
				}
			}
			i++;
		}

		// (2)��������
		if (!err)
		{
			wstr = PlayListData;

			TRY {stdFile1.WriteString(wstr);}
			CATCH (CFileException, eP) {err = 1;}
			END_CATCH
		}
		// (6)�N���[�Y(�����I)
		stdFile1.Close();
		
		CString FolderPath = CurDir + _T("\\");
		CString SavePath = CurDir + _T("\\") + SaveFileName + _T(".m3u");

		//FolderPath.Replace(_T("\\"),_T("\\\\"));
		//SavePath.Replace(_T("\\"),_T("\\\\"));

		//if(FullPath.Right(1)!=_T("\\")){
			//���G�N�X�v���[���ŊJ��
			if (SaveFileName!=_T("temp.flc")){
				ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), _T("/select,") + SaveFileName + _T(".m3u") , FolderPath , SW_SHOWNORMAL );
			}
		//}else{
		//	ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), FullPath , NULL , SW_SHOWNORMAL );
		//}
	
		return _T("");
	}

	if (mySwitch == _T("m3u_read_temp")){
		//// (6)�N���[�Y(�����I)
		//stdFile1.Close();
		return  CurDir + _T("\\") + _T("temp.flc.m3u");
	}


	if(mySwitch == _T("m3u_read")){ //read
		CString inputData;
		inputData = BuffList;

		while (!err) {
			if (stdFile1.ReadString(rstr) == FALSE) err = 1;
			if (rstr!=_T("")){
				if (rstr != _T("#EXTM3U") && rstr.Left(GetStrLen_Func(_T("#EXTINF:0"))) != _T("#EXTINF:0")){
					inputData +=_T(" \"") + rstr + _T("\"");
				}
			}
		}
		
		// (6)�N���[�Y(�����I)
		stdFile1.Close();

		//MessageBox(inputData);

		return inputData;
	}

	if(mySwitch == _T("wpl_write")){ //write //��ŃR�[�f�B���O
	//http://www.sutosoft.com/oldroom/devdiary/20020504.html
		
		//setlocale(LC_CTYPE, "");

		CStringA src;
		CStringA dest;
		
		CFile file;
		 if (file.Open(FilePath, CFile::modeRead)) {
 			DWORD iLength = file.GetLength();
 			file.Read(src.GetBuffer(iLength), iLength);
 			file.Close();
 			src.ReleaseBuffer(iLength);
 	
 			// �t�@�C������ǂݍ���ł邪�AUTF-8 �� BOM(EF, BB, BF)�̈����͑��v���H
 			//
 			static const BYTE utf8_bom[3] = { 0xEF, 0xBB, 0xBF };
 	
 			if (::strncmp(src, reinterpret_cast<const char*>(utf8_bom), 3) == 0) {
 				src.Delete(0, 3);
 			}
 	
 			//CStringA dest;
 			if (UTF8ToShiftJIS(src, &dest)) {
 				// �����R�[�h�� S-JIS �Ȃ̂ŁAANSI�o�[�W�����𖾎��I�Ɏg�p����K�v������
 				// (MessageBox �ł͂Ȃ��āAMessageBoxA)
 				//
 				//::MessageBoxA(m_hWnd, dest, "�Ă���", MB_OK);
 			}
		 }

		//http://www.s-cradle.com/developer/sophiaframework/sf_reference/ref.SFXTextEncoding.html
		//UTF8ToShiftJIS( SFXAnsiStringConstRef source , SFXAnsiStringPtr destination );
		//�����G���R�[�h�� UTF-8 ���� Shift_JIS �ɕϊ����܂��B


		// (2)��������
		if (!err)
		{
			wstr = dest;

			TRY {stdFile1.WriteString(wstr);}
			CATCH (CFileException, eP) {err = 1;}
			END_CATCH
		}

		// (6)�N���[�Y(�����I)
		stdFile1.Close();

		return _T("");
	}

	if(mySwitch == _T("wpl_read")){ //read
		CString inputData;
		inputData = BuffList;

		while (!err) {
			if (stdFile1.ReadString(rstr) == FALSE) err = 1;
			if (rstr!=_T("")){
				CString myTag;
				myTag =_T("<media src=\"");

				int startIDX=0;
				int EndIDX=0;

				startIDX = rstr.Find(myTag,0);
				if (startIDX >= 0 && (startIDX + myTag.GetLength() <= rstr.GetLength())){
					EndIDX = rstr.Find(_T("\""),startIDX + myTag.GetLength() + 1);
					if (EndIDX >= 0 && EndIDX - startIDX - myTag.GetLength() >= 1) {
						CString tempStr; 
						
						tempStr = rstr.Mid(startIDX + myTag.GetLength(), EndIDX - startIDX - myTag.GetLength());
					//================== �����Q�� ==================
						tempStr.Replace(_T("&apos;"), _T("'"));
						tempStr.Replace(_T("&cric;"), _T("^"));
						tempStr.Replace(_T("&tilde;"), _T("~"));
						tempStr.Replace(_T("&ndash;"), _T("-"));
						tempStr.Replace(_T("&lsquo;"), _T("�e"));
						tempStr.Replace(_T("&rsquo;"), _T("�f"));
						tempStr.Replace(_T("&sbquo;"), _T(","));
						tempStr.Replace(_T("&amp;"), _T("&")); //�Ō�H

	//'                    tempStr = Replace(tempStr, "&ensp;", "[]")
	//'                    tempStr = Replace(tempStr, "&emsp;", "[]")
    
					//================== �����Q�� END ==================
						if(tempStr.Left(2)!=_T("..")){
							inputData +=_T(" \"") + tempStr + _T("\"");
						}else if (tempStr.Left(2)==_T("..")){
							CString tempPath;
							tempStr.Replace(_T("..\\"),_T(""));
							int AlphabetNum = _T('A');				
							switch(AlphabetNum){
								case _T('A'):
									tempPath = _T("A:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('B'):
									tempPath = _T("B:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('C'):
									tempPath = _T("C:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('D'):
									tempPath = _T("D:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('E'):
									tempPath = _T("E:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('F'):
									tempPath = _T("F:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('G'):
									tempPath = _T("G:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('H'):
									tempPath = _T("H:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('I'):
									tempPath = _T("I:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('J'):
									tempPath = _T("J:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('K'):
									tempPath = _T("K:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('L'):
									tempPath = _T("L:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('M'):
									tempPath = _T("M:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('N'):
									tempPath = _T("N:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('O'):
									tempPath = _T("O:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('P'):
									tempPath = _T("P:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('Q'):
									tempPath = _T("Q:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('R'):
									tempPath = _T("R:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('S'):
									tempPath = _T("S:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('T'):
									tempPath = _T("T:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('U'):
									tempPath = _T("U:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('V'):
									tempPath = _T("V:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('W'):
									tempPath = _T("W:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('X'):
									tempPath = _T("X:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('Y'):
									tempPath = _T("Y:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('Z'):
									tempPath = _T("Z:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								default:
									CFileListCreatorDlg::StatusStringSet(_T("Z�h���C�u�܂ŒT�����܂������A�������̑��΃p�X����΃p�X�ɕϊ��ł��܂���ł���"),300,TRUE);
									break;
							}
							if (PathFileExists(tempPath)) inputData +=_T(" \"") + tempPath + _T("\"");
						}
					}
				}
			}
		}

		stdFile1.Close();

		//http://www.ujasiri.com/prglib/vc/filectrl/vc_delfile.html

		DeleteFile(CurDir + _T("\\") + SaveFileName + _T(".flc"));

		return inputData;

		// (6)�N���[�Y(�����I)
	}

	return _T("");
}

//CString CFileListCreatorDlg::PlayList_Read(CString tempPath,CString BuffList){
//	//http://oshiete.goo.ne.jp/qa/6356162.html
//
//	//http://www.sutosoft.com/oldroom/devdiary/20020504.html
//  ��BOOL UTF8ToShiftJIS(const CString& src, CString* dest)��

// http://oshiete.goo.ne.jp/qa/6908823.html
BOOL CFileListCreatorDlg::UTF8ToShiftJIS(const CStringA& src, CStringA* dest)
{
 	// UTF-8 -> Unicode
 	//
 	int iWideLength = ::MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
 	if (iWideLength == 0) return FALSE;
 	
 	CStringW temp;
 	
 	int iLength = ::MultiByteToWideChar(CP_UTF8, 0, src, -1, temp.GetBuffer(iWideLength), iWideLength);
 	temp.ReleaseBuffer();
 	
 	if (iLength == 0) return FALSE;
 	
 	// Unicode -> S-JIS �́ACString �W���̕ϊ����g�p����B
 	// ������肪����ꍇ�́A::WideCharToMultiByte �̎g�p����������B
 	//
 	*dest = temp;
 	
 	return TRUE;
}


//http://chaichan.web.infoseek.co.jp/qa6500/qa6595.htm

////http://www.sutosoft.com/oldroom/devdiary/20020504.html

////http://rararahp.cool.ne.jp/cgi-bin/lng/vc/vclng.cgi?print+200612/06120010.txt

//http://oshiete.goo.ne.jp/qa/5607357.html


/* http://d.hatena.ne.jp/shikaku/20090519/p3
��[CPP][VC]LPCSTR�Ȃǂ�VC++�̕���킵����`�̈Ӗ�

�ꌩ���̕s����VC++�I���W�i����`�B��[���݂�ΈႢ��������B���O	�Ӗ�
LP	���i�|�C���^�j
C	const
TSTR	TCHAR(char)
STR	char
WSTR	WCHAR(���j�R�[�h�p�F2byte)


�䂦�ɒ�`	����
LPSTR	char*
LPCSTR	const char*
LPTSTR	TCHAR*
LPCTSTR	const TCHAR*
LPWSTR	WCHAR*
LPCWSTR	const WCHAR*


�ƂȂ�B*/

void CFileListCreatorDlg::OnMenuFilePrint()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		MessageBox(_T("����@�\�́A���X�g��HTML��Export���Ă���AInternet Explorer�Ȃǂ̃u���E�U�[���������Ă��������B(���݂̃A�C�e�����͂O�Ȃ̂ŁA�܂��̓A�C�e�������X�g�ɒǉ����ĉ�����)") ,_T("����@�\�ɂ���"),MB_OK);
		return;
	}else{

	int myResult;
	myResult = MessageBox(_T("����@�\�́A���X�g��HTML��Export���Ă���AInternet Explorer�Ȃǂ̃u���E�U�[���������Ă��������B���݂̃f�[�^��Export���܂����H") ,_T("����@�\�ɂ���"),MB_YESNOCANCEL );

		if (IDYES == myResult){

			StatusStringSet(_T("Export ���s��"),0,FALSE); //�ύX 2012.06.14

			g_NoDrawFLG = TRUE;

			HTML_Dlg m_dlg;
	
			if(m_dlg.DoModal()==IDOK){
				CFileListCreatorDlg::ExportFileList(FALSE);
			}

			g_NoDrawFLG = FALSE;

			delete m_dlg;
			
			CFileListCreatorDlg::StatusStringSet(_T("Export �I��"),300,TRUE);

			//RedrawWindow(); //�ǉ� 2012.05.04
		}
	}
}


void CFileListCreatorDlg::OnFilterKeywords()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	//LastPrevItemCount = m_xcList.GetItemCount();
	//CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	//���[�_���X�P
	CDialog *m_pDlg;
	m_pDlg = new KeywordDlg(this);
	m_pDlg->Create(IDD_DIALOG_Keywords);

	m_pDlg->ShowWindow(true);
}

//http://wisdom.sakura.ne.jp/system/winapi/windata1.html
//http://wisdom.sakura.ne.jp/system/winapi/win32/win32.html
BOOL CFileListCreatorDlg::PreTranslateMessage(MSG* pMsg) 
{

	//LVITEM       lvi;
	int err;

	switch (pMsg->message) {

	//  case WM_NOTIFY://http://forums.codeguru.com/showthread.php?p=1179627
	//http://grepwin.googlecode.com/svn-history/r196/trunk/src/SearchDlg.cpp

	//http://gurigumi.s349.xrea.com/programming/visualcpp/sdk_dialog_listview3.html

	//http://www.kumei.ne.jp/c_lang/sdk3/sdk_227.htm



	case WM_SIZE:
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	//case WM_MOUSEWHEEL: //http://hpcgi1.nifty.com/MADIA/Vcbbs/wwwlng.cgi?print+200504/05040028.txt
		//if((short)HIWORD(wParam) > 0)
		//{
		//	// �z�C�[����������ɃX�N���[������
		//}
		//else
		//if((short)HIWORD(wParam) < 0)
		//{
		//	// �z�C�[�����������ɃX�N���[������
		//}

		//if (m_xcList.GetSelectedCount()>=1 && ListInsertItemFLG == FALSE){
		//	RedrawWindow();  //�ǉ� 2012.06.21 //XP�΍�  //�}�E�X�̓����H
		//}

		//return 0;
	case WM_KEYUP:
		if(pMsg->hwnd == GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
			if (pMsg->wParam == VK_RETURN){
				if (LastSelectedRow!=-1 && LastSelectedColumn!=-1) {

					lvi.mask = LVIF_TEXT;// | LVIF_PARAM; //�f�[�^�̍X�V���ɕK�v�I�I

					lvi.iItem = LastSelectedRow;
					lvi.iSubItem = LastSelectedColumn;
					
					::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT_Item)); //�ǉ� 2012.05.20

					CString UpadateItem;
					((CEdit*)GetDlgItem(IDC_EDIT_Item))->GetWindowText(UpadateItem);

					CString LastEditStr = m_xcList.GetItemText(LastSelectedRow,LastSelectedColumn);

					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(UpadateItem));
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
					UpdateData(FALSE);
					StatusStringSet(_T("�Z���̃f�[�^���X�V���܂���"),0,TRUE);

					if (LastEditStr != UpadateItem) {
						ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13
						AfxGetMainWnd()->SetWindowText(_T("FileListCreator (*)")); //�ǉ� 2012.05.13
					}
					EditCellShow(LastSelectedRow ,LastSelectedColumn);//�R�����g�� 2012.05.20
					//((CEdit*)GetDlgItem(IDC_EDIT_Item))->SetWindowText(UpadateItem); //�ǉ� 2012.05.13
					UpdateData(FALSE);
				}
				return 0;
			}
		}
		if(pMsg->hwnd == GetDlgItem(IDC_LIST)->m_hWnd ){
			if (pMsg->wParam == WM_VSCROLL){
				if (LastSelectedRow!=-1 && LastSelectedColumn!=-1) {
					//::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
					//::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08
					EditCellShow(LastSelectedRow ,LastSelectedColumn);
				}
				//UpdateData(FALSE);  //�ǉ� 2012.06.14 //XP�΍� ��
				//RedrawWindow();  //�ǉ� 2012.06.14 //XP�΍�ɂȂ�Ȃ� �~
				return 0;
			}
		}
		break;

		////http://www.geocities.jp/ky_webid/win32c/026.html

	//case WM_RBUTTONDOWN:
	//	break;
	//	return 0;
	//case WM_RBUTTONUP:
	//	break;
	//	return 0;
	//http://www.coara.or.jp/~tkuri/D/034.htm
	case WM_KEYDOWN:
		if(pMsg->hwnd == GetDlgItem(IDC_LIST)->m_hWnd || pMsg->hwnd == GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
			if (pMsg->wParam == VK_F2){
				if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
					CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŕҏW���[�h�ɐ؂�ւ����܂���"),300,TRUE);
					return 0;
				}
				if (m_xvChkEditCellMode == FALSE){
					m_xvChkEditCellMode = TRUE;

					//::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);

					//LastSelectedRow = -1;
					//LastSelectedColumn = -1;

					CFileListCreatorDlg::StatusStringSet(_T("�t�@�C���� �� ���l�� �� �ҏW���[�h�ɂȂ�܂��� (�Z�����N���b�N���邩�A�N���b�N�� ���L�[�őf�����ړ��AEnter�Ŋm��)"),300,TRUE);
					m_xvStrEditCellMode = _T("�F�@�ҏW���[�h");
					UpdateData(FALSE);

					CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_EasySelect);
					//�`�F�b�N���O��
					chkbox1->SetCheck(0);
					m_xvChkEasySelect = FALSE;

					CButton* chkbox2 = (CButton*)GetDlgItem(IDC_CHK_RedOnMode); //�ǉ� 2012.04.17
					//�`�F�b�N���O��
					chkbox2->SetCheck(0);
					m_xvChkRedOnMode = FALSE;

					//::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
					//::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

					m_xvStrEasySelectMode = _T("");
					m_xvStrRedOnMode = _T(""); //�ǉ� 2012.04.17
					UpdateData(FALSE);	

					//EditCellShow(LastSelectedRow ,LastSelectedColumn);
				}

				EditCellShow(LastSelectedRow ,LastSelectedColumn);
				return 0;
			}
		}

		if(pMsg->hwnd == GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
			if (pMsg->wParam == VK_ESCAPE){
				EditCellShow(LastSelectedRow ,LastSelectedColumn);
				CFileListCreatorDlg::StatusStringSet(_T("�f�[�^�̓��͂��L�����Z�����܂���"),0,FALSE);
				return 0;
			}
		}

		if ( ::GetKeyState( VK_CONTROL ) < 0 ) {
			if (pMsg->wParam == VK_DELETE){
				if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
					CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
					return 0;
				}else{
					CFileListCreatorDlg::DeleteSelectedCells_Func();
					return 0;
				}
			}

			switch ( (int)pMsg->wParam ) {
			case _T('A'):
				if( pMsg->hwnd == GetDlgItem(IDC_LIST)->m_hWnd || CellSizeFixMode == _T("FilePath")){
					/* �S�I�� */
					::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
					::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08
					SelectALL_Func();
				}

				if( pMsg->hwnd == GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					CString EditData;
					((CEdit*)GetDlgItem(IDC_EDIT_Item))->GetWindowText(EditData);
					((CEdit*)GetDlgItem(IDC_EDIT_Item))->SetSel(0,EditData.GetLength());
				}
				break;
			case _T('S'):
				/* �ۑ� */
				OnMenuFileSave();
			
				CFileListCreatorDlg::StatusStringSet(_T("�t�@�C����ۑ����܂���"),300,FALSE);
				break;
			case _T('F'):
				/* ���� */
				::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
				::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

				//::ShowWindow(::GetDlgItem(m_hWnd,IDD_DIALOG_Replace),SW_HIDE);//�ǉ�2011.10.14

				FindIDX = -1;

				//���[�_���X�P
				CDialog *m_pDlg;
				m_pDlg = new ReplaceDlg(this);
				m_pDlg->Create(IDD_DIALOG_Replace);

				m_pDlg->ShowWindow(true);
				break;
			//case _T('G'):
			//	/* �������� */

			case _T('Z'):
				/* �A���h�D */
				if(pMsg->hwnd == GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					CString UpadateItem;

					UpadateItem = m_xcList.GetItemText(LastSelectedRow,LastSelectedColumn);
					((CEdit*)GetDlgItem(IDC_EDIT_Item))->GetWindowText(UpadateItem);

					StatusStringSet(_T("�ҏW���̕����𕜋A���܂���"),300,TRUE);
				}else{
					if (m_xvChkUseUNDO == FALSE) {
						CFileListCreatorDlg::StatusStringSet(_T("UNDO�@�\���L���ɂȂ��Ă��܂���\r\n( �uUse UNDO/REDO�v�Ƀ`�F�b�N�����Ă������� )"),0,TRUE);
					}else{
						if (ESCAPE_FLG == FALSE) {
							ESCAPE_FLG = TRUE;
							StatusStringSet(_T("���s���̏������~���܂���"),300,TRUE);
						}
						OnEditlistUndo();
						ESCAPE_FLG = FALSE;
					}
				}
				break;
			//case _T('X'):
			//	/* �J�b�g */
			//	break;
			case _T('C'): //�ǉ� 2012.05.25
				/* �R�s�[ */
				if(pMsg->hwnd == GetDlgItem(IDC_LIST)->m_hWnd ){
					if ( m_xvChkEasySelect == TRUE || m_xvChkRedOnMode == TRUE || m_xvChkEditCellMode == TRUE) { //�ǉ� 2012.05.26
						int myResult;
						myResult = MessageBox(_T("EasySelect���[�h�E�ԐF�}�[�L���O���[�h�E�ҏW���[�h�ł́A�R�s�[�ł��܂���B�ʏ탂�[�h�ɕύX���܂����H") ,_T("���[�h�m�F"), MB_YESNOCANCEL );


						if (IDYES == myResult){
							CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_EasySelect);
							//�`�F�b�N���O��
							chkbox1->SetCheck(0);
							m_xvChkEasySelect = FALSE;

							CButton* chkbox2 = (CButton*)GetDlgItem(IDC_CHK_RedOnMode); //�ǉ� 2012.04.17
							//�`�F�b�N���O��
							chkbox2->SetCheck(0);
							m_xvChkRedOnMode = FALSE;

							CButton* chkbox3 = (CButton*)GetDlgItem(IDC_CHK_EditCellMode); //�ǉ� 2012.05.26
							//�`�F�b�N���O��
							chkbox3->SetCheck(0);
							m_xvChkEditCellMode = FALSE;

							m_xvStrEasySelectMode = _T(""); //�ǉ� 2012.05.26
							m_xvStrRedOnMode = _T("");
							m_xvStrEditCellMode = _T("�F�@�ʏ탂�[�h");

							::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE); //�ǉ�2012.05.30
							::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE); //�ǉ�2012.05.30

							UpdateData(FALSE);
							//RedrawWindow();
						}
						//return 0;
					}
				}
				//StatusStringSet(_T("�ʏ탂�[�h�̂ݎg�p�ł��܂�"),300,TRUE);

				if(pMsg->hwnd == GetDlgItem(IDC_LIST)->m_hWnd ){
					if ( m_xvChkEditCellMode == FALSE ) {
						if (LastSelectedRow!=-1 && LastSelectedColumn!=-1) {
							CString CopyText;
							CopyText= CFileListCreatorDlg::m_xcList.GetItemText(LastSelectedRow,LastSelectedColumn);
							CFileListCreatorDlg::SetClipboardText(const_cast<LPTSTR>(static_cast<LPCTSTR>(CopyText)));
							StatusStringSet(_T("���Ō�ɃN���b�N�����Z���̕������R�s�[���܂�����\r\n" + CopyText),0,FALSE);
						}
					}
				}

				//EditCellShow(LastSelectedRow ,LastSelectedColumn);
				break;
			case _T('V'): //�ǉ� 2012.05.25
				/* �y�[�X�g */
				if(pMsg->hwnd == GetDlgItem(IDC_LIST)->m_hWnd ){
					if ( m_xvChkEasySelect == TRUE || m_xvChkRedOnMode == TRUE || m_xvChkEditCellMode == TRUE) { //�ǉ� 2012.05.26
						int myResult;
						myResult = MessageBox(_T("EasySelect���[�h�E�ԐF�}�[�L���O���[�h�E�ҏW���[�h�ł́A�y�[�X�g�ł��܂���B�ʏ탂�[�h�ɕύX���܂����H") ,_T("���[�h�m�F"), MB_YESNOCANCEL );

						if (IDYES == myResult){
							CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_EasySelect);
							//�`�F�b�N���O��
							chkbox1->SetCheck(0);
							m_xvChkEasySelect = FALSE;

							CButton* chkbox2 = (CButton*)GetDlgItem(IDC_CHK_RedOnMode); //�ǉ� 2012.04.17
							//�`�F�b�N���O��
							chkbox2->SetCheck(0);
							m_xvChkRedOnMode = FALSE;

							CButton* chkbox3 = (CButton*)GetDlgItem(IDC_CHK_EditCellMode); //�ǉ� 2012.05.26
							//�`�F�b�N���O��
							chkbox3->SetCheck(0);
							m_xvChkEditCellMode = FALSE;

							m_xvStrEasySelectMode = _T(""); //�ǉ� 2012.05.26
							m_xvStrRedOnMode = _T("");
							m_xvStrEditCellMode = _T("�F�@�ʏ탂�[�h");

							::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE); //�ǉ�2012.05.30
							::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE); //�ǉ�2012.05.30

							UpdateData(FALSE);
							//RedrawWindow();
						}
						//return 0;
					}
				}
				UpdateData();
				lvi.mask = LVIF_TEXT;  // | LVCF_SUBITEM�����Ă͂Ȃ�Ȃ� //�d�v 2012.05.31
//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������

				if(pMsg->hwnd == GetDlgItem(IDC_LIST)->m_hWnd ){
					if ( m_xvChkEditCellMode == FALSE ) {
						if (LastSelectedRow!=-1 && LastSelectedColumn!=-1) {
							if (LastSelectedColumn == 3 || LastSelectedColumn == 8){
								if(m_xcList.GetSelectedCount()>=1){

									LastPrevItemCount = m_xcList.GetItemCount();
									CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

									int index = -1;

									while ((index = m_xcList.GetNextItem
											(index, LVNI_ALL | LVNI_SELECTED)) != -1){
											CString CopyText;
											CopyText= CFileListCreatorDlg::m_xcList.GetItemText(LastSelectedRow,LastSelectedColumn); //�ǉ� 2012.05.26
											CopyText= CFileListCreatorDlg::GetClipboardText(CopyText);


											lvi.iItem = index;
											//lvi.lParam = m_id++;        // ID
											lvi.iSubItem = LastSelectedColumn;
											lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(CopyText));

											if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
											UpdateData(FALSE);
									}

									if (LastSelectedColumn == 3){
										StatusStringSet(_T("�t�@�C������ �Ƀf�[�^��\��t���܂���"),0,TRUE);
									}
									if (LastSelectedColumn == 8){
										StatusStringSet(_T("���l�� �Ƀf�[�^��\��t���܂���"),0,TRUE);
									}
								}
							}else{
								StatusStringSet(_T("�t�@�C���� �� ���l�� �ɂ̂� �f�[�^��\��t���鎖���ł��܂�"),300,TRUE);
								return 0;
							}
						}
					}
				}

				ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

				if (ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
					SetWindowText(_T("FileListCreator (*)"));
					if(pMsg->hwnd == GetDlgItem(IDC_LIST)->m_hWnd ){
						SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24
					}
				}
				break;


			case _T('Q'):
				/* �I�� */

				if (ESCAPE_FLG == FALSE) { //�ǉ� 2012.05.03
					ESCAPE_FLG = TRUE;
					StatusStringSet(_T("���s���̏������~���܂���"),300,TRUE);
				}

				//if (IDYES == myResult){
					//�t�@�C���ۑ�����
					AutoSaveMode_ReadOrWrite_Func(_T("write"));
					UseUNDO_Mode_ReadOrWrite_Func(_T("write"));

					if (m_xvChkAutoSave == TRUE){
						OnMenuFileSave();

						//free(prevData);
						//prevData = NULL;
						//free(nowData);
						//nowData = NULL;
						//free(workData);
						//workData = NULL;

						EndDialog(FALSE);
					}else{
						//free(prevData);
						//prevData = NULL;
						//free(nowData);
						//nowData = NULL;
						//free(workData);
						//workData = NULL;

						EndDialog(FALSE);
					}
				//}
				break;

			case _T('D'):
				//���[�_���X�P
				CFileListCreatorDlg::OnFilterDatefilter();
				break;

			case _T('K'):
				//���[�_���X�P
				CFileListCreatorDlg::OnFilterKeywords();
				break;

			
			case _T('L'):
				CFileListCreatorDlg::ChangeLanguage();
				break;

			case _T('I'):
				if(pMsg->hwnd == GetDlgItem(IDC_LIST)->m_hWnd){ //Ctrl + Delete �̌�Ŏ��s
					if(AnyfileImport == FALSE){
						int myResult;
						myResult = MessageBox(_T("�ߋ��̃o�[�W�����ō�������X�g�t�@�C������荞�߂郂�[�h�ɂ��܂����H\r\n�������AFileListCreator�ō���Ă��Ȃ��t�@�C������荞�񂾏ꍇ�A�G���[�ɂȂ�\��������܂��B") ,_T("�C���|�[�g�m�F"), MB_YESNOCANCEL );

						if (IDYES == myResult){
							AnyfileImport = TRUE;
							StatusStringSet(_T("�ߋ��̃o�[�W�����ō�������X�g�t�@�C������荞�߂�悤�ɂ��܂���\r\n(�߂��ꍇ�́A�ēx Ctrl + I �������ĉ�����)"),0,TRUE);

							//CFileListCreatorDlg::importFileList();
						}else{
							StatusStringSet(_T("�ʏ�̎�荞�݃��[�h�ł�"),0,FALSE);
						}
					}else{
						AnyfileImport = FALSE;
						StatusStringSet(_T("�ʏ�̎�荞�݃��[�h�ɖ߂��܂���"),0,TRUE);
					}
				}
				break;

			default:
				//ReplaceDlg ReplaceDlg_CLASS;
				/* ���̑� */
				break;
			}
			return 0;
		}


		if(pMsg->hwnd == GetDlgItem(IDC_LIST)->m_hWnd){ //Ctrl + Delete �̌�Ŏ��s
			if (pMsg->wParam == VK_DELETE){
				DeleteSelectedRows_Func();
				return 0;
			}
		}

		if ( m_xvChkEditCellMode == TRUE ) {
			if(pMsg->hwnd == GetDlgItem(IDC_LIST)->m_hWnd || pMsg->hwnd == GetDlgItem(IDC_EDIT_Item)->m_hWnd){
				if (pMsg->wParam == VK_DOWN){
					if (LastSelectedRow < CFileListCreatorDlg::m_xcList.GetItemCount() -1){
						LastSelectedRow++;
						EditCellShow(LastSelectedRow ,LastSelectedColumn);
						StatusStringSet(_T("����������܂���"),0,FALSE);
					}else{
						StatusStringSet(_T("���X�g�̍ŏI�s�ɒB���܂���"),300,TRUE);
					}
					break;
				}
				if (pMsg->wParam == VK_UP){
					if (LastSelectedRow >= 1){
						LastSelectedRow--;
						EditCellShow(LastSelectedRow ,LastSelectedColumn);
						StatusStringSet(_T("����������܂���"),0,FALSE);
					}else{
						StatusStringSet(_T("���X�g�̐擪�ɒB���܂���"),300,TRUE);
					}
					break;
				}
				//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
				if (pMsg->wParam == VK_RIGHT){
					if (LastSelectedColumn==3){
						LastSelectedColumn = 8;
						EditCellShow(LastSelectedRow ,LastSelectedColumn);
						StatusStringSet(_T("����������܂���"),0,FALSE);
					}else if (LastSelectedColumn==8){
						if (LastSelectedRow < CFileListCreatorDlg::m_xcList.GetItemCount() -1){
							LastSelectedRow++;

							LastSelectedColumn = 3;
							EditCellShow(LastSelectedRow ,LastSelectedColumn);
							StatusStringSet(_T("����������܂���"),0,FALSE);
						}else{
							StatusStringSet(_T("���X�g�̍ŏI�s�ɒB���܂���"),300,TRUE);
						}
					}
					break;
				}
				//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
				if (pMsg->wParam == VK_LEFT){
					if (LastSelectedColumn==3){
						if (LastSelectedRow >= 1){
							LastSelectedRow--;

							LastSelectedColumn = 8;
							EditCellShow(LastSelectedRow ,LastSelectedColumn);
							StatusStringSet(_T("����������܂���"),0,FALSE);
						}else{
							StatusStringSet(_T("���X�g�̐擪�ɒB���܂���"),300,TRUE);
						}
					}else if (LastSelectedColumn==8){
						LastSelectedColumn = 3;
						EditCellShow(LastSelectedRow ,LastSelectedColumn);
						StatusStringSet(_T("����������܂���"),0,FALSE);
					}
					break;
				}
			}
		}

		return 0;
	case WM_LBUTTONDBLCLK:
		if(pMsg->hwnd == GetDlgItem(IDC_LIST)->m_hWnd || pMsg->hwnd == GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
			if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
				CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŕҏW���[�h�ɐ؂�ւ����܂���"),300,TRUE);
				return 0;
			}
			if (m_xvChkEditCellMode == FALSE){
				m_xvChkEditCellMode = TRUE;

				//::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);

				//LastSelectedRow = -1;
				//LastSelectedColumn = -1;

				CFileListCreatorDlg::StatusStringSet(_T("�t�@�C���� �� ���l�� �� �ҏW���[�h�ɂȂ�܂��� (�Z�����N���b�N���邩�A�N���b�N�� ���L�[�őf�����ړ��AEnter�Ŋm��)"),300,TRUE);
				m_xvStrEditCellMode = _T("�F�@�ҏW���[�h");
				UpdateData(FALSE);

				CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_EasySelect);
				//�`�F�b�N���O��
				chkbox1->SetCheck(0);
				m_xvChkEasySelect = FALSE;

				CButton* chkbox2 = (CButton*)GetDlgItem(IDC_CHK_RedOnMode); //�ǉ� 2012.04.17
				//�`�F�b�N���O��
				chkbox2->SetCheck(0);
				m_xvChkRedOnMode = FALSE;

				//::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
				//::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

				m_xvStrEasySelectMode = _T("");
				m_xvStrRedOnMode = _T(""); //�ǉ� 2012.04.17
				UpdateData(FALSE);	

				EditCellShow(LastSelectedRow ,LastSelectedColumn);
				return 0;
			}else{
				m_xvChkEditCellMode = FALSE;

				::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
				::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08
				//LastSelectedRow = -1;
				//LastSelectedColumn = -1;

				CFileListCreatorDlg::StatusStringSet(_T("�ʏ�̃��[�h�ł� (�Z�����̃e�L�X�g�͕ҏW�ł��܂���)"),300,TRUE);
				m_xvStrEditCellMode = _T("�F�@�ʏ탂�[�h");
				UpdateData(FALSE);	
			}
			RedrawWindow();
			break;
		}
		return 0;
	}

	return CDialog::PreTranslateMessage (pMsg);

}

void CFileListCreatorDlg::OnBnClickedBtnNosavequit()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	//free(prevData);
	//prevData = NULL;
	//free(nowData);
	//nowData = NULL;
	//free(workData);
	//workData = NULL;

	CDialogEx::OnOK();
}


void CFileListCreatorDlg::PreferenceFileClear_Func()
{

	CStdioFile    stdFile1;
	CString       wstr, rstr;
	LPTSTR        rstrBuf = NULL;
	int           err = 0;

	// (1)�ǂݏ����p�ɃI�[�v��

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
	CurDir = CurrentDirFunc(CurDir,TRUE);

	if(CurDir!=_T("")){
		CurDir.Replace(_T("\\"),_T("\\\\"));
	}
	CurDir = CurDir + _T("\\FileListCreator(Pref)");
	if(CreateDirectory(CurDir,NULL)){

	}
	else {
			
	}

	if (!stdFile1.Open(CurDir + _T("\\AutoSave.dat"), 
		CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeTex


	// (2)��������
	if (!err)
	{
		wstr = _T("");//������

		TRY {stdFile1.WriteString(wstr);}
		CATCH (CFileException, eP) {err = 1;}
		END_CATCH
	}
	// (6)�N���[�Y(�����I)
	stdFile1.Close();

	//===========================================================================================

	if (!stdFile1.Open(CurDir + _T("\\AutoSave.html"), 
		CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeTex


	// (2)��������
	if (!err)
	{
		wstr = _T("");//������

		TRY {stdFile1.WriteString(wstr);}
		CATCH (CFileException, eP) {err = 1;}
		END_CATCH
	}
	// (6)�N���[�Y(�����I)
	stdFile1.Close();

	//===========================================================================================

	if (!stdFile1.Open(CurDir + _T("\\AutoSave.txt"), 
		CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeTex


	// (2)��������
	if (!err)
	{
		wstr = _T("");//������

		TRY {stdFile1.WriteString(wstr);}
		CATCH (CFileException, eP) {err = 1;}
		END_CATCH
	}
	// (6)�N���[�Y(�����I)
	stdFile1.Close();

	//===========================================================================================

	if (!stdFile1.Open(CurDir + _T("\\EndDate.dat"), 
		CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeTex


	// (2)��������
	if (!err)
	{
		wstr = _T("");//������

		TRY {stdFile1.WriteString(wstr);}
		CATCH (CFileException, eP) {err = 1;}
		END_CATCH
	}
	// (6)�N���[�Y(�����I)
	stdFile1.Close();

	//===========================================================================================

	if (!stdFile1.Open(CurDir + _T("\\FileSpecs.dat"), 
		CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeTex


	// (2)��������
	if (!err)
	{
		wstr = _T("");//������

		TRY {stdFile1.WriteString(wstr);}
		CATCH (CFileException, eP) {err = 1;}
		END_CATCH
	}
	// (6)�N���[�Y(�����I)
	stdFile1.Close();

	//===========================================================================================

	if (!stdFile1.Open(CurDir + _T("\\InputFileName.dat"), 
		CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeTex


	// (2)��������
	if (!err)
	{
		wstr = _T("");//������

		TRY {stdFile1.WriteString(wstr);}
		CATCH (CFileException, eP) {err = 1;}
		END_CATCH
	}
	// (6)�N���[�Y(�����I)
	stdFile1.Close();

	//===========================================================================================


	if (!stdFile1.Open(CurDir + _T("\\KeywordNG_BOX.dat"), 
		CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeTex


	// (2)��������
	if (!err)
	{
		wstr = _T("");//������

		TRY {stdFile1.WriteString(wstr);}
		CATCH (CFileException, eP) {err = 1;}
		END_CATCH
	}
	// (6)�N���[�Y(�����I)
	stdFile1.Close();

	//===========================================================================================

	if (!stdFile1.Open(CurDir + _T("\\KeywordOK_BOX.dat"), 
		CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeTex


	// (2)��������
	if (!err)
	{
		wstr = _T("");//������

		TRY {stdFile1.WriteString(wstr);}
		CATCH (CFileException, eP) {err = 1;}
		END_CATCH
	}
	// (6)�N���[�Y(�����I)
	stdFile1.Close();

	//===========================================================================================

	if (!stdFile1.Open(CurDir + _T("\\ReplaceBOX.dat"), 
		CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeTex


	// (2)��������
	if (!err)
	{
		wstr = _T("");//������

		TRY {stdFile1.WriteString(wstr);}
		CATCH (CFileException, eP) {err = 1;}
		END_CATCH
	}
	// (6)�N���[�Y(�����I)
	stdFile1.Close();

	//===========================================================================================

	if (!stdFile1.Open(CurDir + _T("\\SearchBOX.dat"), 
		CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeTex


	// (2)��������
	if (!err)
	{
		wstr = _T("");//������

		TRY {stdFile1.WriteString(wstr);}
		CATCH (CFileException, eP) {err = 1;}
		END_CATCH
	}
	// (6)�N���[�Y(�����I)
	stdFile1.Close();

	//===========================================================================================

	if (!stdFile1.Open(CurDir + _T("\\StartDate.dat"), 
		CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeTex


	// (2)��������
	if (!err)
	{
		wstr = _T("");//������

		TRY {stdFile1.WriteString(wstr);}
		CATCH (CFileException, eP) {err = 1;}
		END_CATCH
	}
	// (6)�N���[�Y(�����I)
	stdFile1.Close();

	//===========================================================================================

	if (!stdFile1.Open(CurDir + _T("\\TargetDate.dat"), 
		CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeTex


	// (2)��������
	if (!err)
	{
		wstr = _T("");//������

		TRY {stdFile1.WriteString(wstr);}
		CATCH (CFileException, eP) {err = 1;}
		END_CATCH
	}
	// (6)�N���[�Y(�����I)
	stdFile1.Close();

	//===========================================================================================

	if (!stdFile1.Open(CurDir + _T("\\UseUNDO.dat"), 
		CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeTex


	// (2)��������
	if (!err)
	{
		wstr = _T("");//������

		TRY {stdFile1.WriteString(wstr);}
		CATCH (CFileException, eP) {err = 1;}
		END_CATCH
	}
	// (6)�N���[�Y(�����I)
	stdFile1.Close();

	//===========================================================================================


	//===========================================================================================

	if (!stdFile1.Open(CurDir + _T("\\SpeakText.vbs"), 
		CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeTex


	// (2)��������
	if (!err)
	{
		wstr = _T("");//������

		TRY {stdFile1.WriteString(wstr);}
		CATCH (CFileException, eP) {err = 1;}
		END_CATCH
	}
	// (6)�N���[�Y(�����I)
	stdFile1.Close();

	//===========================================================================================
}

void CFileListCreatorDlg::OnOptionPreferencefileclear()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	int myResult;
	myResult = MessageBox(_T("�S�ݒ�t�@�C�������������܂����H") ,_T("�������m�F"), MB_YESNOCANCEL );

	if (IDYES == myResult){
		//�t�@�C���ۑ�����
		CFileListCreatorDlg::PreferenceFileClear_Func();

		CFileListCreatorDlg::StatusStringSet(_T("�S�ݒ�t�@�C�������������܂���"),300,TRUE);
	}
}

//http://www.codeproject.com/KB/list/editing_subitems_in_listcontrol.aspx
void CFileListCreatorDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	//if (m_xvChkEditCellMode == TRUE) ::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_SHOW);//�ǉ�2011.10.08

	//NotInversion = TRUE; //�������E�ԐF �Ƃ��ɔ��]���Ȃ�

    Invalidate();  //�R�����g�����Ȃ���΂Ȃ�Ȃ��H�H

    //HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
    RECT rect;
    //get the row number

	int nItem;
	int nSubItem;

    nItem = temp->iItem;
    //get the column number

    nSubItem = temp->iSubItem;


	LastSelectedRow  = nItem;
	LastSelectedColumn = nSubItem;

	if (m_xvChkEasySelect == TRUE){
        ::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),
            SW_HIDE);
		
		RedrawWindow();//�ǉ� 2011.10.09//XP�}�V����EasySelect�ĕ`��΍�
		return;
	}

	//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
	//LastSelectedRow  = nItem;
	//if(nSubItem==3 || nSubItem==8){
	//	LastSelectedColumn = nSubItem;
	//}else{
	//	LastSelectedColumn = -1;
	//}

	if ( m_xvChkEditCellMode==FALSE ) {
		::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
		::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08
        return ;
	}


	//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
    if((nSubItem == 0 || nSubItem == -1 || nItem == -1) || (nSubItem != 3 && nSubItem != 8)){ //2011.09.22�ύX
		::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
		::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08
        return ;
	}

	 //�ǉ� 2012.05.20
	m_xcList.SetItemState(LastSelectedRow,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X //�ǉ� 2012.05.20
	!LVIS_FOCUSED | !LVIS_SELECTED,    // ���
	LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N

	// ���������狳���Ē�����������

	HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST);

    //Get the Rectange of the listControl
    ListView_GetSubItemRect(hWnd1,nItem,
        nSubItem,LVIR_BOUNDS,&rect);

	CString str = m_xcList.GetItemText(nItem,nSubItem);

	//if (m_xvChkEditCellMode == TRUE){
	//	if (LastSelectedRow!=-1 && LastSelectedColumn!=-1) {
	//		m_xvEditItem = m_xcList.GetItemText(LastSelectedRow,LastSelectedColumn); //�ǉ� 2012.05.27 //OnEnChangeEditItem����ړ�
	//		//::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT_Item));
	//	}
	//}

	RECT rect1;
	RECT rect2;

	// ListView�̗̈�擾
	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_LIST ), &rect1 ); //w��啶���ɂ��܂����B�������Ƃ�ł��݂܂���B
	// �_�C�A���O�̗̈�擾
	::GetWindowRect( m_hWnd, &rect2 );

	// �_�C�A���O�̃N���C�A���g���W�ɕϊ�
	this->ScreenToClient( &rect1 );  //Scren �� Screen �ɒ����܂����A���ׂċL���őł��Ă鏊�������ł��I
	this->ScreenToClient( &rect2 );

	int x = rect1.left - rect2.left;

    if(nItem != -1) 
    ::SetWindowPos(::GetDlgItem(m_hWnd,IDC_EDIT_Item),
		//HWND_TOP,rect.left+x,rect.top+4,//�ύX�O
		HWND_TOP,rect.left + x,
			rect.top + rect1.top + 2,
        rect.right-rect.left - 3,
        rect.bottom-rect.top -1,NULL);
    ::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_SHOW);

    ::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT_Item));

	//::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT_Item),_T("")); //�ǉ� 2012.05.20
	//if (str!=_T("")){ //�ǉ� 2012.05.20
		//Set the listItem text in the EditBox
		::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT_Item),str);
	//}

	if(nItem != -1) 
	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow), //��� IDC_STATIC_Arrow �̏�ɁA�O���b�h�����`�悳��Ă��܂��܂���
		HWND_TOP,rect.left + x - 17,
			rect.top + rect1.top + 4,
					17,
					12 ,NULL);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_SHOW);//�ǉ�2011.10.08
	// �������܂ŋ����Ē�����������

	UpdateData(FALSE);  //�ǉ� 2012.06.14 //XP�΍� ��
    *pResult = 0;
}



void CFileListCreatorDlg::EditCellShow(int workRow,int workColumn)
{
	//http://oshiete.goo.ne.jp/qa/7124281.html

	if (m_xvChkEasySelect == TRUE){
        ::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),
            SW_HIDE);
		return;
	}

	if (m_xvChkEditCellMode == TRUE){
		CFileListCreatorDlg::StatusStringSet(_T("�t�@�C���� �� ���l�� �� �ҏW���[�h�ɂȂ�܂��� \r\n (�Z�����N���b�N���邩�A�N���b�N�� ���L�[�őf�����ړ��AEnter�Ŋm��)"),0,FALSE);
	}

	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08
	::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT_Item),_T("")); //�R�����g�� 2012.05.20

	m_xcList.SetItemState(workRow,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
	!LVIS_FOCUSED | !LVIS_SELECTED,    // ���
	LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N
	//UpdateWindow();

    //Invalidate();  //�R�����g�����Ȃ���΂Ȃ�Ȃ�

    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST);
    RECT rect;

	int nItem;
	int nSubItem;

    nItem = workRow;
    nSubItem = workColumn;

	LastSelectedRow  = nItem;
	LastSelectedColumn = nSubItem;

	////0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
    if((nSubItem == 0 || nSubItem == -1 || nItem == -1) || (nSubItem != 3 && nSubItem != 8)){ //2011.09.22�ύX
		//::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
		//::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08
  //      return ;
		nSubItem = 3;
		LastSelectedColumn = nSubItem;

		if (nItem == -1) {//�ǉ�2011.11.10
			::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);//�ǉ�2011.11.10
			::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.11.10
			return;
		}
	}

    //::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),
    //    SW_HIDE);

	CFileListCreatorDlg::m_xcList.EnsureVisible(nItem, FALSE);

    //Retrieve the text of the selected subItem 

    //from the list

    //CString str = GetItemText(hWnd1,nItem ,
    //    nSubItem);

    //RECT rect1,rect2;
    // this macro is used to retrieve the Rectanle 
    // of the selected SubItem

	//CString str = m_xcList.GetItemText(nItem,nSubItem);


	// http://oshiete.goo.ne.jp/qa/7124281.html
	
	// ���������狳���Ē�����������

    //Get the Rectange of the listControl
    ListView_GetSubItemRect(hWnd1,nItem,
        nSubItem,LVIR_BOUNDS,&rect);

	CString str = m_xcList.GetItemText(nItem,nSubItem);

	//LastEditStr = str;

	RECT rect1;
	RECT rect2;

	//rect2 = rect1;

	// ListView�̗̈�擾
	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_LIST ), &rect1 );
	// �_�C�A���O�̗̈�擾
	::GetWindowRect( m_hWnd, &rect2 );

	// �_�C�A���O�̃N���C�A���g���W�ɕϊ�
	this->ScreenToClient( &rect1 );
	this->ScreenToClient( &rect2 );

	int x = rect1.left - rect2.left;

    if(nItem != -1) 
    ::SetWindowPos(::GetDlgItem(m_hWnd,IDC_EDIT_Item),
		//HWND_TOP,rect.left+x,rect.top+4,//�ύX�O
		HWND_TOP,rect.left + x,
			rect.top + rect1.top + 2,
        rect.right-rect.left - 3,
        rect.bottom-rect.top -1,NULL);
    ::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_SHOW);

    ::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT_Item));

    //Set the listItem text in the EditBox
    ::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT_Item),str);

	if(nItem != -1) 
	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),
		HWND_TOP,rect.left + x - 17,
			rect.top + rect1.top + 4,
					17,
					12 ,NULL);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_SHOW);//�ǉ�2011.10.08
	// �������܂ŋ����Ē�����������



 //   ::SetWindowPos(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),//�ǉ�2011.10.08
	//	//HWND_TOP,rect.left+x,rect.top+4,//�ύX�O
	//	HWND_TOP,rect.left + x - 17,
	//		rect.top + rect1.top + 2,
 //       17,
 //       12 ,NULL);
	//::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_SHOW);//�ǉ�2011.10.08
	UpdateData(FALSE);  //�ǉ� 2012.06.14 //XP�΍� ��
}

void CFileListCreatorDlg::OnBnClickedBtnQuit()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	//free(prevData);
	//prevData = NULL;
	//free(nowData);
	//nowData = NULL;
	//free(workData);
	//workData = NULL;

	if (m_xvChkAutoSave == TRUE){
		if (ListDataNoChange_FLG == TRUE){ //�ǉ� 2012.05.13
			CFileListCreatorDlg::StatusStringSet(_T("See you, again!!"),0,TRUE);
			
			AutoSaveMode_ReadOrWrite_Func(_T("write"));
			UseUNDO_Mode_ReadOrWrite_Func(_T("write"));

			CDialogEx::OnOK();
		}else{
			OnMenuFileSave();
			
			CFileListCreatorDlg::StatusStringSet(_T("AutoSave ����"),0,FALSE);
			//CFileListCreatorDlg::StatusStringSet(_T("See you, again!!"),500,TRUE);

			AutoSaveMode_ReadOrWrite_Func(_T("write"));
			UseUNDO_Mode_ReadOrWrite_Func(_T("write"));

			CDialogEx::OnOK();

		}
	}else{	
		AutoSaveMode_ReadOrWrite_Func(_T("write"));
		UseUNDO_Mode_ReadOrWrite_Func(_T("write"));

		CDialogEx::OnOK();
	}
			///EndDialog(FALSE); //�ύX 2012.05.26
			//AfxGetMainWnd()->PostMessage(WM_CLOSE);
}


void CFileListCreatorDlg::OnEnChangeEditItem()
{
	// TODO:  ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A���̃R���g���[����
	// ���̒ʒm�𑗐M����ɂ́ACDialogEx::OnInitDialog() �֐����I�[�o�[���C�h���A
	// CRichEditCtrl().SetEventMask() ��
	// OR ��Ԃ� ENM_CHANGE �t���O���}�X�N�ɓ���ČĂяo���K�v������܂��B

	// TODO:  �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����Ă��������B

	CString CurStr ;
	((CEdit*)GetDlgItem(IDC_EDIT_Item))->GetWindowText(CurStr);

	if (CurStr!=_T("")) {
		if (CurStr.GetLength() > 260){
			CurStr = CurStr.Left(260);
			//LengthOver = TRUE;
			CFileListCreatorDlg::StatusStringSet(_T("���X�g�{�b�N�X���̊i�[�������������I�[�o�[���܂���\r\n(������260������ �e�L�X�g��؂���܂�)"),0,TRUE);
			((CEdit*)GetDlgItem(IDC_EDIT_Item))->SetWindowText(CurStr);
			UpdateData(FALSE);
		}
	}

	if (m_xvChkEditCellMode == TRUE){
		if (LastSelectedRow!=-1 && LastSelectedColumn!=-1) {
			m_xvEditItem = m_xcList.GetItemText(LastSelectedRow,LastSelectedColumn);
			//::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT_Item));
		}
	}
	//::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT_Item));
}


void CFileListCreatorDlg::OnEnKillfocusEditItem()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	//::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
}


void CFileListCreatorDlg::OnBnClickedChkEditcellmode()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	//LastPrevItemCount = m_xcList.GetItemCount();
	//CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	if (m_xvChkEditCellMode == FALSE){
		m_xvChkEditCellMode = TRUE;

		//::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);

		//LastSelectedRow = -1;
		//LastSelectedColumn = -1;

		CFileListCreatorDlg::StatusStringSet(_T("�t�@�C���� �� ���l�� �� �ҏW���[�h�ɂȂ�܂��� \r\n (�Z�����N���b�N���邩�A�N���b�N�� ���L�[�őf�����ړ��AEnter�Ŋm��)"),300,TRUE);
		m_xvStrEditCellMode = _T("�F�@�ҏW���[�h");
		UpdateData(FALSE);

		CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_EasySelect);
		//�`�F�b�N���O��
		chkbox1->SetCheck(0);
		m_xvChkEasySelect = FALSE;

		CButton* chkbox2 = (CButton*)GetDlgItem(IDC_CHK_RedOnMode); //�ǉ� 2012.04.17
		//�`�F�b�N���O��
		chkbox2->SetCheck(0);
		m_xvChkRedOnMode = FALSE;

		::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
		::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

		m_xvStrEasySelectMode = _T("");
		m_xvStrRedOnMode = _T(""); //�ǉ� 2012.04.17
		UpdateData(FALSE);	

		EditCellShow(LastSelectedRow ,LastSelectedColumn);
	}else{
		m_xvChkEditCellMode = FALSE;

		::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
		::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

		//LastSelectedRow = -1;
		//LastSelectedColumn = -1;

		CFileListCreatorDlg::StatusStringSet(_T("�ʏ�̃��[�h�ł� (�Z�����̃e�L�X�g�͕ҏW�ł��܂���)"),300,FALSE);
		m_xvStrEditCellMode = _T("�F�@�ʏ탂�[�h");
		UpdateData(FALSE);	
	}
	RedrawWindow();
}


void CFileListCreatorDlg::OnBnClickedBtnSetseqNum()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	SetSEQ_NUM_Func(TRUE);
}

BOOL CFileListCreatorDlg::CheckRemarksColumn(){
	//_wsetlocale(LC_ALL, _T("jpn"));
	StatusStringSet(_T("���l���̃f�[�^�`�F�b�N��"),0,FALSE);

	//LVITEM       lvi;
	CString      str;	
	
	lvi.mask =  LVIF_TEXT ;// | LVIF_PARAM; //�f�[�^�̍X�V���ɕK�v�I�I

    
	int workRow;

	workRow = 0;
    
	BOOL ExistFLG = FALSE;

	while (workRow < CFileListCreatorDlg::m_xcList.GetItemCount()){

	     	//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������

		int columnIDX=8;
	        
		CString tempStr;
		tempStr = CFileListCreatorDlg::m_xcList.GetItemText(workRow,columnIDX);

		if (tempStr!=_T("")){
			ExistFLG = TRUE;
			break;
		}
		workRow = workRow + 1;
	}
	//_wsetlocale(LC_ALL, _T(""));

	StatusStringSet(_T("���l���̃`�F�b�N����"),0,FALSE);
	return ExistFLG;
}

BOOL CFileListCreatorDlg::CheckFileName(){
	//_wsetlocale(LC_ALL, _T("jpn"));
	StatusStringSet(_T("�t�@�C���� �`�F�b�N��"),0,FALSE);

	//LVITEM       lvi;
	CString      str;	
	
	lvi.mask =  LVIF_TEXT ;// | LVIF_PARAM; //�f�[�^�̍X�V���ɕK�v�I�I

    
	int workRow;

	workRow = 0;
    
	BOOL ChangeFLG = FALSE;

	while (workRow < CFileListCreatorDlg::m_xcList.GetItemCount()){

	     	//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������

		int FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(workRow);

		if( FormatDataNum == 12 || FormatDataNum == 22 ){
			CString FileName;
			FileName = CFileListCreatorDlg::m_xcList.GetItemText(workRow,3);

			CString FullPathString;
			FullPathString = CFileListCreatorDlg::m_xcList.GetItemText(workRow,2);

			if (FileName != FullPathToFileName(FullPathString)){
				ChangeFLG = TRUE;
				break;
			}
		}
		workRow = workRow + 1;
	}
	//_wsetlocale(LC_ALL, _T(""));

	StatusStringSet(_T("�t�@�C���� �`�F�b�N����"),0,FALSE);
	return ChangeFLG;
}

void CFileListCreatorDlg::OnMenuExpandMusicListFile()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if( CFileListCreatorDlg::m_xcList.GetItemCount() <=0){
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	ESCAPE_FLG = FALSE;

    int        index = -1;
    //CString    str;
    CString 	tempPath;
	tempPath=_T("");
	int myCnt = 0;

	CString tempCnt;


	index = -1;

    while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
        (index, LVNI_ALL | LVNI_SELECTED)) != -1)
    {
		if ( myStrToLower_Func(m_xcList.GetItemText(index,2).Right(GetStrLen_Func(_T(".m3u")))) == _T(".m3u") || myStrToLower_Func(m_xcList.GetItemText(index,2).Right(GetStrLen_Func(_T(".wpl")))) == _T(".wpl") || myStrToLower_Func(m_xcList.GetItemText(index,2).Right(GetStrLen_Func(_T(".txt")))) == _T(".txt") ){
			myCnt++;
		}
    }

	if(myCnt==0){

		importFileResult = MessageBox(_T("���ׂẴv���C���X�g��W�J���܂����H"),_T("�W�J�m�F"), MB_YESNOCANCEL );
		if ( importFileResult == IDYES ){
			index = 0;

			while (index < CFileListCreatorDlg::m_xcList.GetItemCount())
			{
				if (ESCAPE_FLG == TRUE) break;

				MSG msg; //�ǉ� 2011.10.22

				if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
					if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
						if (msg.wParam == VK_ESCAPE){
							ESCAPE_FLG = TRUE;
							break; //�I���B���b�Z�[�W���[�v�𔲂���B
						}
					}
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					//continue;
				}

				tempPath = CFileListCreatorDlg::m_xcList.GetItemText(index,2);

				if ( myStrToLower_Func(m_xcList.GetItemText(index,2).Right(GetStrLen_Func(_T(".m3u")))) == _T(".m3u") || myStrToLower_Func(m_xcList.GetItemText(index,2).Right(GetStrLen_Func(_T(".wpl")))) == _T(".wpl") || myStrToLower_Func(m_xcList.GetItemText(index,2).Right(GetStrLen_Func(_T(".txt")))) == _T(".txt") ){
					if ( myStrToLower_Func(m_xcList.GetItemText(index,2).Right(GetStrLen_Func(_T(".txt")))) == _T(".txt") ) {
						if ( iTunesPlayList_Import_Func( tempPath, _T("CheckMusicListFile") ) == TRUE ) {
							m_xcList.SetItemState(index,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
							LVIS_FOCUSED | LVIS_SELECTED,    // ���
							LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N

							CFileListCreatorDlg::ExpandMusicListFile_Func(tempPath);
							myCnt++;
						}else{
							m_xcList.SetItemState(index,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
							!(LVIS_FOCUSED | LVIS_SELECTED),    // ���
							LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N
						}
					}else{ // *.m3u *.wpl
						m_xcList.SetItemState(index,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
						LVIS_FOCUSED | LVIS_SELECTED,    // ���
						LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N

						CFileListCreatorDlg::ExpandMusicListFile_Func(tempPath);
						myCnt++;
					}
				}else{
					m_xcList.SetItemState(index,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
					!LVIS_SELECTED,    // ��� //��I�����
					LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N
				}
				index ++;
			}
		}
	}else if(myCnt>=1){

		UpdateData(FALSE);

		int index = -1;

		myCnt = 0;
		//index = -1;
		while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
			(index, LVNI_ALL | LVNI_SELECTED)) != -1)
		{
			if (ESCAPE_FLG == TRUE) break;

			MSG msg; //�ǉ� 2011.10.22

			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						ESCAPE_FLG = TRUE;
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			tempPath = CFileListCreatorDlg::m_xcList.GetItemText(index,2);

			if ( myStrToLower_Func(m_xcList.GetItemText(index,2).Right(GetStrLen_Func(_T(".m3u")))) == _T(".m3u") || myStrToLower_Func(m_xcList.GetItemText(index,2).Right(GetStrLen_Func(_T(".wpl")))) == _T(".wpl") || myStrToLower_Func(m_xcList.GetItemText(index,2).Right(GetStrLen_Func(_T(".txt")))) == _T(".txt") ){
					if ( myStrToLower_Func(m_xcList.GetItemText(index,2).Right(GetStrLen_Func(_T(".txt")))) == _T(".txt") ) {
						if ( iTunesPlayList_Import_Func( tempPath, _T("CheckMusicListFile") ) == TRUE ) {
							m_xcList.SetItemState(index,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
							LVIS_FOCUSED | LVIS_SELECTED,    // ���
							LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N

							CFileListCreatorDlg::ExpandMusicListFile_Func(tempPath);
							myCnt++;
						}else{
							m_xcList.SetItemState(index,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
							!(LVIS_FOCUSED | LVIS_SELECTED),    // ���
							LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N
						}
					}else{ // *.m3u *.wpl
						CFileListCreatorDlg::ExpandMusicListFile_Func(tempPath);
						myCnt++;
					}
			}else{ 
				m_xcList.SetItemState(index,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
				!LVIS_SELECTED,    // ��� //��I�����
				LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N
			}

			//CFileListCreatorDlg::ItemCount_Func(TRUE);
		}
	}

	tempCnt = _T("");
	if(myCnt>=1){ //�ǉ� 2012.06.14
		tempCnt.Format(_T("%d"),myCnt);
		tempCnt=tempCnt + _T(" ���̃v���C���X�g��W�J���܂���");
	}else{
		tempCnt=_T("�v���C���X�g���������߁A���X�g��W�J�ł��܂���");
	}
	CFileListCreatorDlg::StatusStringSet(tempCnt,300,TRUE);
	CFileListCreatorDlg::SetStrFormat_Func();

	CFileListCreatorDlg::Total_Bytes_Bold();
	CFileListCreatorDlg::Total_Bytes_Func();
	CFileListCreatorDlg::ItemCount_Func(TRUE);

	if (myCnt>=1){
		ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

		CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

		if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
			return;
		}

		if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
			m_Dlg->SetWindowText(_T("FileListCreator (*)"));
			SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24
		}
	}

	index = -1;

	index = CFileListCreatorDlg::m_xcList.GetNextItem(index, LVNI_ALL | LVNI_SELECTED);
		CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE);
}

void CFileListCreatorDlg::ExpandMusicListFile_Func(CString MusicListFilePath)
{

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}


	CStdioFile    stdFile1;
	CString       wstr, rstr;
	LPTSTR        rstrBuf = NULL;
	int           err = 0;

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
	CurDir = CurDir + _T("\\FileListCreator(LIST)");
	if(CreateDirectory(CurDir,NULL)){

	}
	else {
			
	}

	CString SaveFileName;
	SaveFileName = FullPathToFileName(MusicListFilePath);

	//MessageBox (CurDir + _T("\\") + SaveFileName + _T(".flc"));
	//http://www.g-ishihara.com/mfc_fi_01.htm



	if ( myStrToLower_Func(MusicListFilePath.Right(GetStrLen_Func(_T(".m3u")))) == _T(".m3u") ){
		err = 0;

		if (!stdFile1.Open(MusicListFilePath,
			CFile::modeReadWrite | CFile::shareDenyNone | 
			CFile::modeCreate | CFile::modeNoTruncate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText

		while (!err) {
			MSG msg; //�ǉ� 2011.10.22

			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						ESCAPE_FLG = TRUE;
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			if (stdFile1.ReadString(rstr) == FALSE) err = 1;
			if (rstr!=_T("")){
				if (rstr != _T("#EXTM3U") && rstr.Left(GetStrLen_Func(_T("#EXTINF:0"))) != _T("#EXTINF:0")){
					if( PathFileExists(rstr) ){
						ListInsertItem(rstr);
					}
				}
			}
		}
		
		// (6)�N���[�Y(�����I)
		stdFile1.Close();

		return;
	}

	if ( myStrToLower_Func(MusicListFilePath.Right(GetStrLen_Func(_T(".wpl")))) == _T(".wpl") ){
		if (!stdFile1.Open(CurDir + _T("\\") + SaveFileName + _T(".flc"),
			CFile::modeReadWrite | CFile::shareDenyNone | 
			CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText

		err = 0;
	//http://www.sutosoft.com/oldroom/devdiary/20020504.html
		
		//setlocale(LC_CTYPE, "");

		CStringA src;
		CStringA dest;
		
		CFile file;
		 if (file.Open(MusicListFilePath, CFile::modeRead)) {
 			DWORD iLength = file.GetLength();
 			file.Read(src.GetBuffer(iLength), iLength);
 			file.Close();
 			src.ReleaseBuffer(iLength);
 	
 			// �t�@�C������ǂݍ���ł邪�AUTF-8 �� BOM(EF, BB, BF)�̈����͑��v���H
 			//
 			static const BYTE utf8_bom[3] = { 0xEF, 0xBB, 0xBF };
 	
 			if (::strncmp(src, reinterpret_cast<const char*>(utf8_bom), 3) == 0) {
 				src.Delete(0, 3);
 			}
 	
 			//CStringA dest;
 			if (UTF8ToShiftJIS(src, &dest)) {
 				// �����R�[�h�� S-JIS �Ȃ̂ŁAANSI�o�[�W�����𖾎��I�Ɏg�p����K�v������
 				// (MessageBox �ł͂Ȃ��āAMessageBoxA)
 				//
 				//::MessageBoxA(m_hWnd, dest, "�Ă���", MB_OK);
 			}
		 }

		//http://www.s-cradle.com/developer/sophiaframework/sf_reference/ref.SFXTextEncoding.html
		//UTF8ToShiftJIS( SFXAnsiStringConstRef source , SFXAnsiStringPtr destination );
		//�����G���R�[�h�� UTF-8 ���� Shift_JIS �ɕϊ����܂��B


		// (2)��������
		if (!err)
		{
			wstr = dest;

			TRY {stdFile1.WriteString(wstr);}
			CATCH (CFileException, eP) {err = 1;}
			END_CATCH
		}

		// (6)�N���[�Y(�����I)
		stdFile1.Close();



		if (!stdFile1.Open(CurDir + _T("\\") + SaveFileName + _T(".flc"),
			CFile::modeReadWrite | CFile::shareDenyNone | 
			CFile::modeCreate | CFile::modeNoTruncate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText

		err = 0;

		while (!err) {
			MSG msg; //�ǉ� 2011.10.22

			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
				if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
					if (msg.wParam == VK_ESCAPE){
						ESCAPE_FLG = TRUE;
						break; //�I���B���b�Z�[�W���[�v�𔲂���B
					}
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//continue;
			}

			if (stdFile1.ReadString(rstr) == FALSE) err = 1;
			if (rstr!=_T("")){
				CString myTag;
				myTag =_T("<media src=\"");

				int startIDX=0;
				int EndIDX=0;

				startIDX = rstr.Find(myTag,0);
				if (startIDX >= 0 && (startIDX + myTag.GetLength() <= rstr.GetLength())){
					EndIDX = rstr.Find(_T("\""),startIDX + myTag.GetLength() + 1);
					if (EndIDX >= 0 && EndIDX - startIDX - myTag.GetLength() >= 1) {
						CString tempStr; 
                
						tempStr = rstr.Mid(startIDX + myTag.GetLength(), EndIDX - startIDX - myTag.GetLength());
					//================== �����Q�� ==================
						tempStr.Replace(_T("&apos;"), _T("'"));
						tempStr.Replace(_T("&cric;"), _T("^"));
						tempStr.Replace(_T("&tilde;"), _T("~"));
						tempStr.Replace(_T("&ndash;"), _T("-"));
						tempStr.Replace(_T("&lsquo;"), _T("�e"));
						tempStr.Replace(_T("&rsquo;"), _T("�f"));
						tempStr.Replace(_T("&sbquo;"), _T(","));
						tempStr.Replace(_T("&amp;"), _T("&")); //�Ō�H

	//'                    tempStr = Replace(tempStr, "&ensp;", "[]")
	//'                    tempStr = Replace(tempStr, "&emsp;", "[]")
    
					//================== �����Q�� END ==================
						if(tempStr.Left(2)!=_T("..")){
							//inputData +=_T(" \"") + tempStr + _T("\"");
							if( PathFileExists(tempStr) ){
								ListInsertItem(tempStr);
							}
						}else if (tempStr.Left(2)==_T("..")){
							CString tempPath;
							tempStr.Replace(_T("..\\"),_T(""));
							int AlphabetNum = _T('A');				
							switch(AlphabetNum){
								case _T('A'):
									tempPath = _T("A:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('B'):
									tempPath = _T("B:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('C'):
									tempPath = _T("C:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('D'):
									tempPath = _T("D:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('E'):
									tempPath = _T("E:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('F'):
									tempPath = _T("F:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('G'):
									tempPath = _T("G:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('H'):
									tempPath = _T("H:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('I'):
									tempPath = _T("I:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('J'):
									tempPath = _T("J:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('K'):
									tempPath = _T("K:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('L'):
									tempPath = _T("L:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('M'):
									tempPath = _T("M:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('N'):
									tempPath = _T("N:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('O'):
									tempPath = _T("O:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('P'):
									tempPath = _T("P:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('Q'):
									tempPath = _T("Q:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('R'):
									tempPath = _T("R:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('S'):
									tempPath = _T("S:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('T'):
									tempPath = _T("T:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('U'):
									tempPath = _T("U:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('V'):
									tempPath = _T("V:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('W'):
									tempPath = _T("W:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('X'):
									tempPath = _T("X:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('Y'):
									tempPath = _T("Y:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								case _T('Z'):
									tempPath = _T("Z:\\")+tempStr;
									if (PathFileExists(tempPath)) break;
								default:
									CFileListCreatorDlg::StatusStringSet(_T("Z�h���C�u�܂ŒT�����܂������A�������̑��΃p�X����΃p�X�ɕϊ��ł��܂���ł���"),300,TRUE);
									break;
							}
							if (PathFileExists(tempPath)) ListInsertItem(tempPath);
						}
					}
				}
			}
		}

		stdFile1.Close();

		//http://www.ujasiri.com/prglib/vc/filectrl/vc_delfile.html

		DeleteFile(CurDir + _T("\\") + SaveFileName + _T(".flc"));

		// (6)�N���[�Y(�����I)

		return;
	}


	if ( myStrToLower_Func(MusicListFilePath.Right(GetStrLen_Func(_T(".txt")))) == _T(".txt") ){
		iTunesPlayList_Import_Func( MusicListFilePath, _T("ExpandMusicListFile") );
		return;
	}

	//CFileListCreatorDlg::Total_Bytes_Bold();
	//CFileListCreatorDlg::Total_Bytes_Func();
	//CFileListCreatorDlg::ItemCount_Func(FALSE);

	return;
}


void CFileListCreatorDlg::OnRepeateditemcheckBydatasize()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
	SameItemCheck(_T("SameItemCheck_By_DataSize"));

}



void CFileListCreatorDlg::OnRepeateditemcheckByfilename()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	SameItemCheck(_T("SameItemCheck_BY_FileName"));
}

void CFileListCreatorDlg::OnRepeateditemcheckBymodifytime()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	SameItemCheck(_T("SameItemCheck_By_ModifyTime"));
}


void CFileListCreatorDlg::OnRepeateditemcheckByallinfo()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	SameItemCheck(_T("SameItemCheck_By_ALL_INFO"));
}

void CFileListCreatorDlg::SameItemCheck(CString mySwitch)
{

	//CString str;
	//str.Format(_T("%d"),INT_MAX);
	//MessageBox (str);

	//LVITEM	   lvi;
	int		  index = 0;

	UpdateData();
	lvi.mask = LVIF_TEXT;

	CString FullPathString;
	CString myFileName;

	index = 0;
	while (index < CFileListCreatorDlg::m_xcList.GetItemCount()){
		lvi.iItem = index;
		lvi.iSubItem = 0;			

		lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("")));
		CFileListCreatorDlg::m_xcList.SetItem(&lvi);
		index++;
	}


	//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
	//StatusStringSet(_T("�t�@�C�����A�t�@�C���e�ʁA�C�������ɂ��A�d���`�F�b�N"),0,FALSE);

	//int LastRow = CFileListCreatorDlg::m_xcList.GetItemCount();

	struct itemStruct
	{
		CString	RepetitionNum;	//�t�@�C���d�����ʃi���o�[

		//int		Num;		//�ʂ��ԍ�
		CString	FullPath;	//�t�@�C���p�X
		CString	FileName;	//�t�@�C����
		//CString	ApproximateByte;	//�����悻�̃f�[�^�T�C�Y//�o�C�g
		CString	AccurateByte;		//���ۂ̃f�[�^�T�C�Y//���o�C�g
		
		//TCHAR	ModifyDate[20];		//�C����
		//CTime	ModifyTime;		//�C������
		
		CString	ModifyTime;		//�C������
		
		//TCHAR	RemarksColumn[100];		//���l��
	//} item[] = 
	//	{_T(""),_T(""),_T(""),_T(""),_T(""),
	};
	//http://www13.plala.or.jp/kmaeda/cpp_cli/newstr.htm
	
	//http://www-watt.mech.eng.osaka-u.ac.jp/~tasai/cp/lec1.html


	itemStruct *item;
	item = new itemStruct[CFileListCreatorDlg::m_xcList.GetItemCount()];

	int i;

	//MessageBox(itemNum);

	for (i = 0; i < CFileListCreatorDlg::m_xcList.GetItemCount(); i++) //������
	{

		item[i].RepetitionNum = _T(""); //�t�@�C���d�����ʃi���o�[
		item[i].FileName = _T(""); //�t�@�C����
		item[i].AccurateByte = _T(""); //�f�[�^�T�C�Y
		item[i].ModifyTime = _T(""); //�C������
	}

//http://homepage2.nifty.com/assua/aosite/cpp/cpp_intro/cpb12.html

//C++�̏ꍇ�F
//struct Test{
//int n;
//char ch;
//};
//
//Test *p = new Test;
//delete p;

    //CString myitem[33333][4];
    int cc;
	int dd;

	//  for( cc = 0;cc<33333;cc++){
	//      myitem[cc][0] = _T(""); //�t�@�C���d�����ʃi���o�[
	//      myitem[cc][1] = _T(""); //�t�@�C����
	//		myitem[cc][2] = _T(""); //�f�[�^�T�C�Y
	//		myitem[cc][3] = _T(""); //�C������
	//}

    cc = 1;
    dd = 1; //�R�����g��

	if(mySwitch == _T("SameItemCheck_BY_FileName")){
		//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
		StatusStringSet(_T("�t�@�C�����ɂ��A�d���`�F�b�N"),0,FALSE);
		index = 0;

		while (index < CFileListCreatorDlg::m_xcList.GetItemCount()){
			//ULONGLONG FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);
			//if(item[index].FileName != _T("Same Path")){
				/////item[index].RepetitionNum = _T("");
			//}

			FullPathString = CFileListCreatorDlg::m_xcList.GetItemText(index,2);

			if(FullPathString != _T("")){
				if (FullPathString.Right(1) ==_T("\\")){
					item[index].FileName = FullPathToFileName(FullPathString.Left(FullPathString.GetLength()-1)); //�ǉ� 2012.04.04
				}else{
					item[index].FileName = FullPathToFileName(FullPathString);
				}
			}
			//item[index].FileName = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileName));

			for (dd = 0; dd < index; dd++){
				if (item[dd].FileName == item[index].FileName){
					if (item[index].RepetitionNum != _T("")){
						item[dd].RepetitionNum = item[index].RepetitionNum;
						//" �d���ԍ����Ɋ��ɏd���m�����A�����Ă���Ƃ�"
					}else{
						//cc // " �C���N�������gcc"
							CString str;
							if (cc>=INT_MAX){
								str = _T("MAX-Value");
							}else{
								str.Format(_T("%d"),cc);
							}

							item[index].RepetitionNum = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));
							if (item[dd].RepetitionNum != item[index].RepetitionNum){
								cc++;
							}

					}

					lvi.iItem = index;
					lvi.iSubItem = 0;			

					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(item[index].RepetitionNum));
					CFileListCreatorDlg::m_xcList.SetItem(&lvi);
					UpdateData(FALSE);
					
 					lvi.iItem = dd;
					lvi.iSubItem = 0;			

					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(item[index].RepetitionNum));
					CFileListCreatorDlg::m_xcList.SetItem(&lvi);
					UpdateData(FALSE);
				}
			}
			CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE); //�ǉ� 2012.04.04
			index++;

			UpdateData(FALSE);
		}
	}else if(mySwitch == _T("SameItemCheck_By_DataSize")){
		//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
		StatusStringSet(_T("�t�@�C���e�ʂɂ��A�d���`�F�b�N"),0,FALSE);
		index = 0;

		while (index < CFileListCreatorDlg::m_xcList.GetItemCount()){
			//ULONGLONG FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);
			//if(item[index].FileName != _T("Same Path")){
				/////item[index].RepetitionNum = _T("");
			//}

			//FullPathString =CFileListCreatorDlg::m_xcList.GetItemText(index,2);

			//if(FullPathString != _T("")){
			//	myFileName = FullPathToFileName(FullPathString);
			//	//myFileName.Replace(_T("%%"),_T("%"));
			//}


			//CString myFileSize;

			item[index].AccurateByte = CFileListCreatorDlg::m_xcList.GetItemText(index,5);

			//item[index].AccurateByte = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

			for (dd = 0; dd < index; dd++){
				if (item[dd].AccurateByte == item[index].AccurateByte){
					if (item[index].RepetitionNum != _T("")){
						item[dd].RepetitionNum = item[index].RepetitionNum;
						//" �d���ԍ����Ɋ��ɏd���m�����A�����Ă���Ƃ�"
					}else{
						//cc // " �C���N�������gcc"
							CString str;
							if (cc>=INT_MAX){
								str = _T("MAX-Value");
							}else{
								str.Format(_T("%d"),cc);
							}
							item[index].RepetitionNum = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));
							if (item[dd].RepetitionNum != item[index].RepetitionNum){
								cc++;
							}

					}

					lvi.iItem = index;
					lvi.iSubItem = 0;			

					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(item[index].RepetitionNum));
					CFileListCreatorDlg::m_xcList.SetItem(&lvi);
					UpdateData(FALSE);
					
 					lvi.iItem = dd;
					lvi.iSubItem = 0;			

					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(item[index].RepetitionNum));
					CFileListCreatorDlg::m_xcList.SetItem(&lvi);
					UpdateData(FALSE);
				}
			}
			CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE); //�ǉ� 2012.04.04
			index++;

			UpdateData(FALSE);
		}
	}else if(mySwitch == _T("SameItemCheck_By_ModifyTime")){
		//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
		StatusStringSet(_T("�t�@�C���C�������ɂ��A�d���`�F�b�N"),0,FALSE);
		index = 0;

		while (index < CFileListCreatorDlg::m_xcList.GetItemCount()){
			//ULONGLONG FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);
			//if(item[index].FileName != _T("Same Path")){
				/////item[index].RepetitionNum = _T("");
			//}

			FullPathString =CFileListCreatorDlg::m_xcList.GetItemText(index,2);

			if(FullPathString != _T("")){
				myFileName = FullPathToFileName(FullPathString);
				//myFileName.Replace(_T("%%"),_T("%"));
			}


			//CString myFileSize;

			////item[index].AccurateByte = CFileListCreatorDlg::m_xcList.GetItemText(index,5);

			//item[index].AccurateByte = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));


			//CString myTime;

			item[index].ModifyTime = CFileListCreatorDlg::m_xcList.GetItemText(index,7);

			//item[index].ModifyTime = const_cast<LPTSTR>(static_cast<LPCTSTR>(myTime));

			for (dd = 0; dd < index; dd++){
				if (item[dd].ModifyTime == item[index].ModifyTime){
					if (item[index].RepetitionNum != _T("")){
						item[dd].RepetitionNum = item[index].RepetitionNum;
						//" �d���ԍ����Ɋ��ɏd���m�����A�����Ă���Ƃ�"
					}else{
						//cc // " �C���N�������gcc"
							CString str;
							if (cc>=INT_MAX){
								str = _T("MAX-Value");
							}else{
								str.Format(_T("%d"),cc);
							}
							item[index].RepetitionNum = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));
							if (item[dd].RepetitionNum != item[index].RepetitionNum){
								cc++;
							}

					}

					lvi.iItem = index;
					lvi.iSubItem = 0;			

					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(item[index].RepetitionNum));
					CFileListCreatorDlg::m_xcList.SetItem(&lvi);
					UpdateData(FALSE);
					
 					lvi.iItem = dd;
					lvi.iSubItem = 0;			

					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(item[index].RepetitionNum));
					CFileListCreatorDlg::m_xcList.SetItem(&lvi);
					UpdateData(FALSE);
				}
			}
			CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE); //�ǉ� 2012.04.04
			index++;

			UpdateData(FALSE);
		}
	}else if(mySwitch == _T("SameItemCheck_By_ALL_INFO")){
		//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
		StatusStringSet(_T("�t�@�C�����A�t�@�C���e�ʁA�C�������ɂ��A�d���`�F�b�N"),0,FALSE);
		index = 0;

		while (index < CFileListCreatorDlg::m_xcList.GetItemCount()){
			//ULONGLONG FormatDataNum = CFileListCreatorDlg::m_xcList.GetItemData(index);
			//if(item[index].FileName != _T("Same Path")){
				/////item[index].RepetitionNum = _T("");
			//}

			FullPathString =CFileListCreatorDlg::m_xcList.GetItemText(index,2);

			if(FullPathString != _T("")){
				if (FullPathString.Right(1) ==_T("\\")){
					item[index].FileName = FullPathToFileName(FullPathString.Left(FullPathString.GetLength()-1)); //�ǉ� 2012.04.04
				}else{
					item[index].FileName = FullPathToFileName(FullPathString);
				}
			}

			//item[index].FileName = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileName));

			//CString myFileSize;

			item[index].AccurateByte = CFileListCreatorDlg::m_xcList.GetItemText(index,5);

			//item[index].AccurateByte = const_cast<LPTSTR>(static_cast<LPCTSTR>(myFileSize));

			//CString myTime;

			item[index].ModifyTime = CFileListCreatorDlg::m_xcList.GetItemText(index,7);

			//item[index].ModifyTime = const_cast<LPTSTR>(static_cast<LPCTSTR>(myTime));

			for (dd = 0; dd < index; dd++){
				if (item[dd].FileName == item[index].FileName && item[dd].AccurateByte == item[index].AccurateByte && item[dd].ModifyTime == item[index].ModifyTime){
					if (item[index].RepetitionNum != _T("")){
						item[dd].RepetitionNum = item[index].RepetitionNum;
						//" �d���ԍ����Ɋ��ɏd���m�����A�����Ă���Ƃ�"
					}else{
						//cc // " �C���N�������gcc"
							CString str;
							if (cc>=INT_MAX){
								str = _T("MAX-Value");
							}else{
								str.Format(_T("%d"),cc);
							}
							item[index].RepetitionNum = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));
							if (item[dd].RepetitionNum != item[index].RepetitionNum){
								cc++;
							}

					}

					lvi.iItem = index;
					lvi.iSubItem = 0;			

					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(item[index].RepetitionNum));
					CFileListCreatorDlg::m_xcList.SetItem(&lvi);
					UpdateData(FALSE);
					
 					lvi.iItem = dd;
					lvi.iSubItem = 0;			

					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(item[index].RepetitionNum));
					CFileListCreatorDlg::m_xcList.SetItem(&lvi);
					UpdateData(FALSE);
				}
			}
			CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE); //�ǉ� 2012.04.04
			index++;

			UpdateData(FALSE);
		}
	}
	RedrawWindow();  //�ǉ�2011.12.10 //XP�΍�F�ĕ`��
	
	CFileListCreatorDlg::OnSortSortitemsbyrepetitionnum(); //�ǉ� 2012.04.04
	
	//for (i = 0; i < CFileListCreatorDlg::m_xcList.GetItemCount(); i++) //������
	//{
		//delete item[];
	//}
	delete [] item;

	//free(array);//�Y�ꂸ��
}



void CFileListCreatorDlg::OnBnClickedBtnCurrentdirectoryopen()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	_wsetlocale(LC_ALL, _T("jpn"));

	//// �J�����g�f�B���N�g���̎擾
	//TCHAR szCurrentDir[_MAX_PATH];
	//GetCurrentDirectory(_MAX_PATH,szCurrentDir);
	
	//CString CurDir;
	//CurDir = szCurrentDir;

	//http://rararahp.cool.ne.jp/vc/vctips/api.htm
	// ���s�t�@�C���̃t���p�X�擾
	TCHAR szPath[_MAX_PATH];
	GetModuleFileName( NULL, szPath, MAX_PATH);

	////http://rararahp.cool.ne.jp/vc/vctips/api.htm
	//// �J�����g�t�H���_���擾����
	//TCHAR szCurrentDir[_MAX_PATH];
	//GetCurrentDirectory(_MAX_PATH,szCurrentDir);

	//// �t���p�X�𕪉�
	//TCHAR szDir[_MAX_DIR];
	//TCHAR szDrive[_MAX_DRIVE];
	//TCHAR szFName[_MAX_FNAME];
	//TCHAR szExt[_MAX_EXT];
	//_splitpath(szPath,szDrive,szDir,szFName,szExt);
	//
	//// �t�H���_�A�t�@�C�����擾
	//TCHAR szFilePath[_MAX_PATH];
	//TCHAR szFileName[_MAX_PATH];
	//sprintf(szFilePath,"%s%s",szDrive,szDir);
	//sprintf(szFileName,"%s%s",szFName,szExt);

	CString CurDir;
	CurDir = szPath;

	CurDir = CurrentDirFunc(CurDir,TRUE);
	if (CurDir !=_T("")){
		CurDir.Replace(_T("\\"),_T("\\\\"));
	}


	//http://gurizuri0505.halfmoon.jp/develop/cplusplus/cstdiofile
	 _wsetlocale(LC_ALL, _T(""));

	TRACE("��%S��",CurDir);

	//FolderPath.Replace(_T("\\"),_T("\\\\"));
	//http://oshiete.goo.ne.jp/qa/976818.html
	////���G�N�X�v���[���ŊJ��
	//ShellExecute(NULL, _T("open"), CurDir, NULL, NULL, SW_SHOWNORMAL);


	SetCurrentDirectory(CurDir);  //�K�v
	//���G�N�X�v���[���ŊJ��
	ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), _T(".\\") , NULL, SW_SHOWNORMAL );




	////���G�N�X�v���[���ŊJ��
	//ShellExecute( NULL, _T("explore"), CurDir +_T("\\\\") , NULL , NULL, SW_SHOWNORMAL );

	//ShellExecute( NULL, _T("open"), CurDir, szPath , NULL , SW_SHOWNORMAL );
	//ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\EXPLORER.EXE"), szPath , NULL, SW_SHOWNORMAL );
}


void CFileListCreatorDlg::OnOptionCurrentdirectoryopen()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	CFileListCreatorDlg::OnBnClickedBtnCurrentdirectoryopen();
}


void CFileListCreatorDlg::OnEditlistClearrepetitionnum()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		//LVITEM	   lvi;
		int		  index = 0;

		UpdateData();
		lvi.mask = LVIF_TEXT;

		index = 0;

		BOOL ExistFLG = FALSE;

		while (index < CFileListCreatorDlg::m_xcList.GetItemCount()){
			//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
			lvi.iItem = index;
			lvi.iSubItem = 0;			

			if ( CFileListCreatorDlg::m_xcList.GetItemText(index, 0) != _T("") ){
				ExistFLG = TRUE;
			}
			index++;
		}

		if (ExistFLG == FALSE) {
			StatusStringSet(_T("�d���i���o�[�̗��ɂ̓f�[�^�������Ă��܂���"),0,TRUE);
			return;
		}
	}

	int myResult;
	myResult = MessageBox(_T("�d���i���o�[�����ׂč폜���܂����H") ,_T("�폜�m�F"), MB_YESNOCANCEL );


	if (IDYES == myResult){
		StatusStringSet(_T("�d���i���o�[���폜��"),0,FALSE);

		//LVITEM	   lvi;
		int		  index = 0;

		UpdateData();
		lvi.mask = LVIF_TEXT;

		index = 0;
		while (index < CFileListCreatorDlg::m_xcList.GetItemCount()){
			//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
			lvi.iItem = index;
			lvi.iSubItem = 0;			

			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("")));
			CFileListCreatorDlg::m_xcList.SetItem(&lvi);
			index++;
		}
		StatusStringSet(_T("�d���i���o�[���폜���܂���"),300,TRUE);
		RedrawWindow(); //�ǉ� 2012.04.05 //XP�΍�
	}else{
		StatusStringSet(_T("�d���i���o�[�̍폜���L�����Z�����܂���"),300,TRUE);
		return;
	}

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}
}


void CFileListCreatorDlg::OnEditlistClearremarkscolumn()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		//LVITEM	   lvi;
		int		  index = 0;

		UpdateData();
		lvi.mask = LVIF_TEXT;

		index = 0;

		BOOL ExistFLG = FALSE;

		while (index < CFileListCreatorDlg::m_xcList.GetItemCount()){
			//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
			lvi.iItem = index;
			lvi.iSubItem = 8;			

			if ( CFileListCreatorDlg::m_xcList.GetItemText(index, 8) != _T("") ){
				ExistFLG = TRUE;
			}
			index++;
		}

		if (ExistFLG == FALSE) {
			StatusStringSet(_T("���l���ɂ̓f�[�^�������Ă��܂���"),0,TRUE);
			return;
		}
	}

	int myResult;
	myResult = MessageBox(_T("���l���̕��������ׂč폜���܂����H") ,_T("�폜�m�F"), MB_YESNOCANCEL );


	if (IDYES == myResult){
		LastPrevItemCount = m_xcList.GetItemCount();
		CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

		StatusStringSet(_T("���l�����폜��"),0,FALSE);

		//LVITEM	   lvi;
		int		  index = 0;

		UpdateData();
		lvi.mask = LVIF_TEXT;

		index = 0;
		while (index < CFileListCreatorDlg::m_xcList.GetItemCount()){
			//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
			lvi.iItem = index;
			lvi.iSubItem = 8;			

			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("")));
			CFileListCreatorDlg::m_xcList.SetItem(&lvi);
			index++;
		}
		StatusStringSet(_T("���l�����폜���܂���"),300,TRUE);
		RedrawWindow(); //�ǉ� 2012.04.05 //XP�΍�
	}else{
		StatusStringSet(_T("���l���̍폜���L�����Z�����܂���"),300,TRUE);
		return;
	}


	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}
}


void CFileListCreatorDlg::OnLanguageJapanese()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B


    CMenu    cMenu;
    int      err = 0;
    

    // ���j���[�����[�h
    if (!err) if (!cMenu.LoadMenu(IDR_MENU2)) err = 1;

    SetMenu(&cMenu); //http://www.gidforums.com/t-17869.html

	//cMenu.DestroyMenu();

	SelectedLanguage = _T("Japanese");	
	
	//http://rarara.cafe.coocan.jp/cgi-bin/lng/vc/vclng.cgi?print+200609/06090009.txt


	// CMainFrame�N���X�ȊO�Ȃ�΁AAfxGetMainWnd()->GetMenu()�Ŏ擾����B this->AfxGetMainWnd()->GetMenu()
	CMenu* pMenu = &cMenu; //�ύX 2012.04.14
	CMenu* pSubMenu;
	CMenu* pSubMenu2;
	CMenu* pSubMenu3;

	UINT id;

	id = pMenu->GetMenuItemID( 0 );
	pMenu->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "�t�@�C�� (&F)" ) );

		pSubMenu = pMenu->GetSubMenu( 0 );

		id = pSubMenu->GetMenuItemID( 0 );
		pSubMenu->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "���X�g��荞�� (&I)" ) );

		id = pSubMenu->GetMenuItemID( 1 );
		pSubMenu->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "���X�g�o�� (&E)" ) );

		id = pSubMenu->GetMenuItemID( 2 );
		pSubMenu->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "�R�s�[ (&C)" ) );

		id = pSubMenu->GetMenuItemID( 3 );
		pSubMenu->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "��� (&P)" ) );

		id = pSubMenu->GetMenuItemID( 4 );
		pSubMenu->ModifyMenu( 4, MF_BYPOSITION | MF_STRING, id, TEXT( "�t�@�C�����A (&R)" ) );

		id = pSubMenu->GetMenuItemID( 5 );
		pSubMenu->ModifyMenu( 5, MF_BYPOSITION | MF_STRING, id, TEXT( "�����ۑ� (&A)" ) );

			pSubMenu2 = pSubMenu->GetSubMenu( 5 );

			id = pSubMenu2->GetMenuItemID( 0 );
			pSubMenu2->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "�I��(&O)" ) );

			id = pSubMenu2->GetMenuItemID( 1 );
			pSubMenu2->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "�I�t" ) );

		id = pSubMenu->GetMenuItemID( 6 );
		pSubMenu->ModifyMenu( 6, MF_BYPOSITION | MF_STRING, id, TEXT( "�ۑ� (&S) (Ctrl + S)" ) );

		id = pSubMenu->GetMenuItemID( 7 );
		pSubMenu->ModifyMenu( 7, MF_BYPOSITION | MF_STRING, id, TEXT( "�I��(&Q) (Ctrl + Q)" ) );

	id = pMenu->GetMenuItemID( 0 );
	pMenu->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "���� (&S)" ) );

		pSubMenu = pMenu->GetSubMenu( 1 );

		id = pSubMenu->GetMenuItemID( 0 );
		pSubMenu->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "�ꊇ���� (&P)" ) );

		id = pSubMenu->GetMenuItemID( 1 );
		pSubMenu->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "�������� (&S)" ) );

	id = pMenu->GetMenuItemID( 0 );
	pMenu->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "���X�g�ҏW (&E)" ) );

		pSubMenu = pMenu->GetSubMenu( 2 );

		id = pSubMenu->GetMenuItemID( 0 );
		pSubMenu->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "���ɖ߂� (&U) (Ctrl + Z)" ) );

		id = pSubMenu->GetMenuItemID( 1 );
		pSubMenu->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "�t�@�C����񕜋A (&R)" ) );

		id = pSubMenu->GetMenuItemID( 2 );
		pSubMenu->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "�g���q���폜 (&D)" ) );

		id = pSubMenu->GetMenuItemID( 3 );
		pSubMenu->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "�f�B���N�g�����t�� (&A)" ) );

		id = pSubMenu->GetMenuItemID( 4 );
		pSubMenu->ModifyMenu( 4, MF_BYPOSITION | MF_STRING, id, TEXT( "���ׂđI�� (Ctrl + A)" ) );

		id = pSubMenu->GetMenuItemID( 5 );
		pSubMenu->ModifyMenu( 5, MF_BYPOSITION | MF_STRING, id, TEXT( "���ׂĂ̑I�������� (&C)" ) );

		id = pSubMenu->GetMenuItemID( 6 );
		pSubMenu->ModifyMenu( 6, MF_BYPOSITION | MF_STRING, id, TEXT( "�A�C�e���� �������u�� (Ctrl + F)" ) );

		id = pSubMenu->GetMenuItemID( 7 );
		pSubMenu->ModifyMenu( 7, MF_BYPOSITION | MF_STRING, id, TEXT( "�A�ԕt�^ (&N)" ) );

		id = pSubMenu->GetMenuItemID( 8 );
		pSubMenu->ModifyMenu( 8, MF_BYPOSITION | MF_STRING, id, TEXT( "�d���i���o�[���폜" ) );

		id = pSubMenu->GetMenuItemID( 9 );
		pSubMenu->ModifyMenu( 9, MF_BYPOSITION | MF_STRING, id, TEXT( "���l�����폜" ) );

		id = pSubMenu->GetMenuItemID( 10 );
		pSubMenu->ModifyMenu( 10, MF_BYPOSITION | MF_STRING, id, TEXT( "��������Ă��Ȃ��A�C�e�����폜 (&E)" ) );

		id = pSubMenu->GetMenuItemID( 11 );
		pSubMenu->ModifyMenu( 11, MF_BYPOSITION | MF_STRING, id, TEXT( "�\�[�g�ƃ}�[�W (&S)" ) );

			pSubMenu2 = pSubMenu->GetSubMenu( 11 );

			id = pSubMenu2->GetMenuItemID( 0 );
			pSubMenu2->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "�d���i���o�[�Ń\�[�g (&N)" ) );

			id = pSubMenu2->GetMenuItemID( 1 );
			pSubMenu2->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "�t�@�C�����Ń\�[�g (&F)" ) );

			id = pSubMenu2->GetMenuItemID( 2 );
			pSubMenu2->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "�f�[�^�T�C�Y�Ń\�[�g (&S)" ) );

			id = pSubMenu2->GetMenuItemID( 3 );
			pSubMenu2->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "���t�Ń\�[�g (&D)" ) );

			id = pSubMenu2->GetMenuItemID( 4 );
			pSubMenu2->ModifyMenu( 4, MF_BYPOSITION | MF_STRING, id, TEXT( "�p�X���Ń\�[�g (&P)" ) );

			id = pSubMenu2->GetMenuItemID( 5 );
			pSubMenu2->ModifyMenu( 5, MF_BYPOSITION | MF_STRING, id, TEXT( "�������Ń\�[�g" ) );

			id = pSubMenu2->GetMenuItemID( 6 );
			pSubMenu2->ModifyMenu( 6, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) );

			id = pSubMenu2->GetMenuItemID( 7 );
			pSubMenu2->ModifyMenu( 7, MF_BYPOSITION | MF_STRING, id, TEXT( "�}�[�W (&M)" ) );

		id = pSubMenu->GetMenuItemID( 12 );
		pSubMenu->ModifyMenu( 12, MF_BYPOSITION | MF_STRING, id, TEXT( "�d���t�@�C���`�F�b�N" ) );

			pSubMenu2 = pSubMenu->GetSubMenu( 12 );

			id = pSubMenu2->GetMenuItemID( 0 );
			pSubMenu2->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "�t�@�C�����Ń`�F�b�N (&F)" ) );

			id = pSubMenu2->GetMenuItemID( 1 );
			pSubMenu2->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "�f�[�^�T�C�Y�Ń`�F�b�N (&D)" ) );

			id = pSubMenu2->GetMenuItemID( 2 );
			pSubMenu2->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "�C�������Ń`�F�b�N (&T)" ) );

			id = pSubMenu2->GetMenuItemID( 3 );
			pSubMenu2->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "��L�R�̏��Ń`�F�b�N (&A)" ) );

		id = pSubMenu->GetMenuItemID( 13 );
		pSubMenu->ModifyMenu( 13, MF_BYPOSITION | MF_STRING, id, TEXT( "iTunes�ŊǗ����ꂽ�t�@�C���ɑ΂���... (&I)" ) );

			pSubMenu2 = pSubMenu->GetSubMenu( 13 );

			id = pSubMenu2->GetMenuItemID( 0 );
			pSubMenu2->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "�A�[�e�B�X�g���t�^" ) );

			id = pSubMenu2->GetMenuItemID( 1 );
			pSubMenu2->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "�A���o�����X�g�쐬" ) );

		id = pSubMenu->GetMenuItemID( 14 );
		pSubMenu->ModifyMenu( 14, MF_BYPOSITION | MF_STRING, id, TEXT( "�t�B���^�[�ōi�荞�� (&F)" ) );

			pSubMenu2 = pSubMenu->GetSubMenu( 14 );

			id = pSubMenu2->GetMenuItemID( 0 );
			pSubMenu2->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "���t�t�B���^�[ (&D) (Ctrl + D)" ) );

			id = pSubMenu2->GetMenuItemID( 1 );
			pSubMenu2->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "�L�[���[�h�t�B���^�[ (&K) (Ctrl + K)" ) );

	id = pMenu->GetMenuItemID( 0 );
	pMenu->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "�I���A�C�e����...(&I)" ) );

		pSubMenu = pMenu->GetSubMenu( 3 );

		id = pSubMenu->GetMenuItemID( 0 );
		pSubMenu->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "�R�s�[ (&C) (Ctrl + C)" ) ); //�ǉ� 2012.05.30

		id = pSubMenu->GetMenuItemID( 1 );
		pSubMenu->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "�\��t�� (&P) (Ctrl + V)" ) ); //�ǉ� 2012.05.30

		id = pSubMenu->GetMenuItemID( 2 );
		pSubMenu->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "�Z���폜 (&D) (Ctrl + Delete)" ) ); //�ǉ� 2012.05.31

		id = pSubMenu->GetMenuItemID( 3 );
		pSubMenu->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "�s�폜 (Delete)" ) ); //�ύX 2012.05.31

		id = pSubMenu->GetMenuItemID( 4 );
		pSubMenu->ModifyMenu( 4, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) ); //�ǉ� 2012.05.30

		id = pSubMenu->GetMenuItemID( 5 );
		pSubMenu->ModifyMenu( 5, MF_BYPOSITION | MF_STRING, id, TEXT( "�������� (&B)" ) );

		id = pSubMenu->GetMenuItemID( 6 );
		pSubMenu->ModifyMenu( 6, MF_BYPOSITION | MF_STRING, id, TEXT( "�ԕ����� (&R)" ) );

		id = pSubMenu->GetMenuItemID( 7 );
		pSubMenu->ModifyMenu( 7, MF_BYPOSITION | MF_STRING, id, TEXT( "���������� (&C)" ) );

		id = pSubMenu->GetMenuItemID( 8 );
		pSubMenu->ModifyMenu( 8, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) );

		id = pSubMenu->GetMenuItemID( 9 );
		pSubMenu->ModifyMenu( 9, MF_BYPOSITION | MF_STRING, id, TEXT( "���X�g�t�@�C���W�J (&E)" ) );

		id = pSubMenu->GetMenuItemID( 10 );
		pSubMenu->ModifyMenu( 10, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) );

		id = pSubMenu->GetMenuItemID( 11 );
		pSubMenu->ModifyMenu( 11, MF_BYPOSITION | MF_STRING, id, TEXT( "���y�v���C���X�g�W�J (&M)" ) );

	id = pMenu->GetMenuItemID( 0 );
	pMenu->ModifyMenu( 4, MF_BYPOSITION | MF_STRING, id, TEXT( "�R�s�[ (&C)" ) );

		pSubMenu = pMenu->GetSubMenu( 4 );

		id = pSubMenu->GetMenuItemID( 0 );
		pSubMenu->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "�C�[�W�[�Z���N�g�I�� (&O)" ) );

		id = pSubMenu->GetMenuItemID( 1 );
		pSubMenu->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "�C�[�W�[�Z���N�g�I�t" ) );

		id = pSubMenu->GetMenuItemID( 2 );
		pSubMenu->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "�R�s�[ (&C)" ) );

	id = pMenu->GetMenuItemID( 0 );
	pMenu->ModifyMenu( 5, MF_BYPOSITION | MF_STRING, id, TEXT( "�\�[�g (&S)" ) );

		pSubMenu = pMenu->GetSubMenu( 5 );

		id = pSubMenu->GetMenuItemID( 0 );
		pSubMenu->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "�d���i���o�[�Ń\�[�g (&N)" ) );

		id = pSubMenu->GetMenuItemID( 1 );
		pSubMenu->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "�t�@�C�����Ń\�[�g (&F)" ) );

		id = pSubMenu->GetMenuItemID( 2 );
		pSubMenu->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "�f�[�^�T�C�Y�Ń\�[�g (&S)" ) );

		id = pSubMenu->GetMenuItemID( 3 );
		pSubMenu->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "���t�Ń\�[�g (&D)" ) );

		id = pSubMenu->GetMenuItemID( 4 );
		pSubMenu->ModifyMenu( 4, MF_BYPOSITION | MF_STRING, id, TEXT( "�p�X���Ń\�[�g (&P)" ) );

		id = pSubMenu->GetMenuItemID( 5 );
		pSubMenu->ModifyMenu( 5, MF_BYPOSITION | MF_STRING, id, TEXT( "�������Ń\�[�g" ) );

		id = pSubMenu->GetMenuItemID( 6 );
		pSubMenu->ModifyMenu( 6, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) );

		id = pSubMenu->GetMenuItemID( 7 );
		pSubMenu->ModifyMenu( 7, MF_BYPOSITION | MF_STRING, id, TEXT( "�}�[�W (&M)" ) );

	id = pMenu->GetMenuItemID( 0 );
	pMenu->ModifyMenu( 6, MF_BYPOSITION | MF_STRING, id, TEXT( "�J�� (&O)" ) );

		pSubMenu = pMenu->GetSubMenu( 6 );

		id = pSubMenu->GetMenuItemID( 0 );
		pSubMenu->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "�G�N�X�v���[���[�ŊJ�� (&E)" ) );

		id = pSubMenu->GetMenuItemID( 1 );
		pSubMenu->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "���f�B�A�v���C���[�ŊJ�� (&M)" ) );

		id = pSubMenu->GetMenuItemID( 2 );
		pSubMenu->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "�֘A�t�����ꂽ�A�v���ŊJ�� (&C)" ) );

		id = pSubMenu->GetMenuItemID( 3 );
		pSubMenu->ModifyMenu( 3, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) );

		id = pSubMenu->GetMenuItemID( 4 );
		pSubMenu->ModifyMenu( 4, MF_BYPOSITION | MF_STRING | MF_GRAYED, id, TEXT( "�o�[�`���� �u���E�U�[ (&V)" ) );

		id = pSubMenu->GetMenuItemID( 5 );
		pSubMenu->ModifyMenu( 5, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) );

		id = pSubMenu->GetMenuItemID( 6 );
		pSubMenu->ModifyMenu( 6, MF_BYPOSITION | MF_STRING, id, TEXT( "�V���[�g�J�b�g���J�� (&L)" ) );

		id = pSubMenu->GetMenuItemID( 7 );
		pSubMenu->ModifyMenu( 7, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) );

		id = pSubMenu->GetMenuItemID( 8 );
		pSubMenu->ModifyMenu( 8, MF_BYPOSITION | MF_STRING, id, TEXT( "�������ꂽ���y���J�� (&P)" ) );

	id = pMenu->GetMenuItemID( 0 );
	pMenu->ModifyMenu( 7, MF_BYPOSITION | MF_STRING, id, TEXT( "�I�v�V���� (&O)" ) );

		pSubMenu = pMenu->GetSubMenu( 7 );

		id = pSubMenu->GetMenuItemID( 0 );
		pSubMenu->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "�o�[�W���� (&V)" ) );

		id = pSubMenu->GetMenuItemID( 1 );
		pSubMenu->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "�֗��ȏ�� (&T)" ) );

		id = pSubMenu->GetMenuItemID( 2 );
		pSubMenu->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "���b�Z�[�W (&M)" ) );

		id = pSubMenu->GetMenuItemID( 3 );
		pSubMenu->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "���� (&L)" ) );


			pSubMenu2 = pSubMenu->GetSubMenu( 3 );
			
			id = pSubMenu2->GetMenuItemID( 0 );
			pSubMenu2->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "�p�� (&E) (Ctrl + L)" ) );

			id = pSubMenu2->GetMenuItemID( 1 );
			pSubMenu2->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "���{�� (&J)" ) );


		id = pSubMenu->GetMenuItemID( 4 );
		pSubMenu->ModifyMenu( 4, MF_BYPOSITION | MF_STRING, id, TEXT( "�S�ݒ�t�@�C���N���A (&P)" ) );

		id = pSubMenu->GetMenuItemID( 5 );
		pSubMenu->ModifyMenu( 5, MF_BYPOSITION | MF_STRING, id, TEXT( "���A�v��������t�H���_���J�� (&O)" ) );

		id = pSubMenu->GetMenuItemID( 6 );
		pSubMenu->ModifyMenu( 6, MF_BYPOSITION | MF_STRING, id, TEXT( "�t�@�C���p�X�̐����`�F�b�N (&C)" ) );

	id = pMenu->GetMenuItemID( 0 );
	pMenu->ModifyMenu( 8, MF_BYPOSITION | MF_STRING, id, TEXT( "ALL FUNC (&A)" ) );

		pSubMenu = pMenu->GetSubMenu( 8 );

		id = pSubMenu->GetMenuItemID( 0 );
		pSubMenu->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "File (&F)" ) );

			pSubMenu2 = pSubMenu->GetSubMenu( 0 );
			
			id = pSubMenu2->GetMenuItemID( 0 );
			pSubMenu2->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "Import (&I)" ) );

			id = pSubMenu2->GetMenuItemID( 1 );
			pSubMenu2->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "Export (&E)" ) );

			id = pSubMenu2->GetMenuItemID( 2 );
			pSubMenu2->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "Copy (&C)" ) );

			id = pSubMenu2->GetMenuItemID( 3 );
			pSubMenu2->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "Print (&P)" ) );

			id = pSubMenu2->GetMenuItemID( 4 );
			pSubMenu2->ModifyMenu( 4, MF_BYPOSITION | MF_STRING, id, TEXT( "Recovery (&R)" ) );

			id = pSubMenu2->GetMenuItemID( 5 );
			pSubMenu2->ModifyMenu( 5, MF_BYPOSITION | MF_STRING, id, TEXT( "Auto Save (&A)" ) );

				pSubMenu3 = pSubMenu2->GetSubMenu( 5 );

				id = pSubMenu3->GetMenuItemID( 0 );
				pSubMenu3->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "AutoSaveON (&O)" ) );

				id = pSubMenu3->GetMenuItemID( 1 );
				pSubMenu3->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "AutoSaveOFF" ) );

			id = pSubMenu2->GetMenuItemID( 6 );
			pSubMenu2->ModifyMenu( 6, MF_BYPOSITION | MF_STRING, id, TEXT( "Save (&S) (Ctrl + S)" ) );

			id = pSubMenu2->GetMenuItemID( 7 );
			pSubMenu2->ModifyMenu( 7, MF_BYPOSITION | MF_STRING, id, TEXT( "Quit (&Q) (Ctrl + Q)" ) );

		id = pSubMenu->GetMenuItemID( 1 );
		pSubMenu->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "Search (&S)" ) );

			pSubMenu2 = pSubMenu->GetSubMenu( 1 );
			
			id = pSubMenu2->GetMenuItemID( 0 );
			pSubMenu2->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "PackageSearch (&P)" ) );

			id = pSubMenu2->GetMenuItemID( 1 );
			pSubMenu2->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "StepSearch (&S)" ) );

		id = pSubMenu->GetMenuItemID( 2 );
		pSubMenu->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "Edit LIST (&E)" ) );

			pSubMenu2 = pSubMenu->GetSubMenu( 2 );
			
			id = pSubMenu2->GetMenuItemID( 0 );
			pSubMenu2->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "UNDO (&U) (Ctrl + Z)" ) );

			id = pSubMenu2->GetMenuItemID( 1 );
			pSubMenu2->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "Restore (&R)" ) );

			id = pSubMenu2->GetMenuItemID( 2 );
			pSubMenu2->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "DEL FileType (&D)" ) );

			id = pSubMenu2->GetMenuItemID( 3 );
			pSubMenu2->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "Add Dir Str (&A)" ) );

			id = pSubMenu2->GetMenuItemID( 4 );
			pSubMenu2->ModifyMenu( 4, MF_BYPOSITION | MF_STRING, id, TEXT( "Select ALL (Ctrl + A)" ) );

			id = pSubMenu2->GetMenuItemID( 5 );
			pSubMenu2->ModifyMenu( 5, MF_BYPOSITION | MF_STRING, id, TEXT( "Select ALL Cancellation (&C)" ) );

			id = pSubMenu2->GetMenuItemID( 6 );
			pSubMenu2->ModifyMenu( 6, MF_BYPOSITION | MF_STRING, id, TEXT( "Find / Replace Item Name (Ctrl + F)" ) );

			id = pSubMenu2->GetMenuItemID( 7 );
			pSubMenu2->ModifyMenu( 7, MF_BYPOSITION | MF_STRING, id, TEXT( "Set Sequential Num (&N)" ) );

			id = pSubMenu2->GetMenuItemID( 8 );
			pSubMenu2->ModifyMenu( 8, MF_BYPOSITION | MF_STRING, id, TEXT( "Clear RepetitionNum" ) );

			id = pSubMenu2->GetMenuItemID( 9 );
			pSubMenu2->ModifyMenu( 9, MF_BYPOSITION | MF_STRING, id, TEXT( "Clear RemarksColumn" ) );

			id = pSubMenu2->GetMenuItemID( 10 );
			pSubMenu2->ModifyMenu( 10, MF_BYPOSITION | MF_STRING, id, TEXT( "Exclude Non-Emphasized Items (&E)" ) );

			id = pSubMenu2->GetMenuItemID( 11 );
			pSubMenu2->ModifyMenu( 11, MF_BYPOSITION | MF_STRING, id, TEXT( "Sort + Merge (&S)" ) );


				pSubMenu3 = pSubMenu2->GetSubMenu( 11 );

				id = pSubMenu3->GetMenuItemID( 0 );
				pSubMenu3->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "Sort Items by RepetitionNum (&N)" ) );

				id = pSubMenu3->GetMenuItemID( 1 );
				pSubMenu3->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "Sort Items by FileName (&F)" ) );

				id = pSubMenu3->GetMenuItemID( 2 );
				pSubMenu3->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "Sort Items by DataSize (&S)" ) );

				id = pSubMenu3->GetMenuItemID( 3 );
				pSubMenu3->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "Sort Items by Date (&D)" ) );

				id = pSubMenu3->GetMenuItemID( 4 );
				pSubMenu3->ModifyMenu( 4, MF_BYPOSITION | MF_STRING, id, TEXT( "Sort Items by PathName (&P)" ) );

				id = pSubMenu3->GetMenuItemID( 5 );
				pSubMenu3->ModifyMenu( 5, MF_BYPOSITION | MF_STRING, id, TEXT( "Sort Items by StrFormat" ) );

				id = pSubMenu3->GetMenuItemID( 6 );
				pSubMenu3->ModifyMenu( 6, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) );

				id = pSubMenu3->GetMenuItemID( 7 );
				pSubMenu3->ModifyMenu( 7, MF_BYPOSITION | MF_STRING, id, TEXT( "Merge (&M)" ) );


			id = pSubMenu2->GetMenuItemID( 12 );
			pSubMenu2->ModifyMenu( 12, MF_BYPOSITION | MF_STRING, id, TEXT( "Same Item Check" ) );

				pSubMenu3 = pSubMenu2->GetSubMenu( 12 );

				id = pSubMenu3->GetMenuItemID( 0 );
				pSubMenu3->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "BY FileName (&F)" ) );

				id = pSubMenu3->GetMenuItemID( 1 );
				pSubMenu3->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "By DataSize (&D)" ) );

				id = pSubMenu3->GetMenuItemID( 2 );
				pSubMenu3->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "BY ModifyTime (&T)" ) );

				id = pSubMenu3->GetMenuItemID( 3 );
				pSubMenu3->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "By ALL INFO (&A)" ) );


			id = pSubMenu2->GetMenuItemID( 13 );
			pSubMenu2->ModifyMenu( 13, MF_BYPOSITION | MF_STRING, id, TEXT( "iTunes (&I)" ) );

				pSubMenu3 = pSubMenu2->GetSubMenu( 13 );

				id = pSubMenu3->GetMenuItemID( 0 );
				pSubMenu3->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "Add Artist Str" ) );

				id = pSubMenu3->GetMenuItemID( 1 );
				pSubMenu3->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "AlbumList" ) );

			
			id = pSubMenu2->GetMenuItemID( 14 );
			pSubMenu2->ModifyMenu( 14, MF_BYPOSITION | MF_STRING, id, TEXT( "Filter (&F)" ) );


				pSubMenu3 = pSubMenu2->GetSubMenu( 14 );

				id = pSubMenu3->GetMenuItemID( 0 );
				pSubMenu3->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "Date Filter(&D) (Ctrl + D)" ) );

				id = pSubMenu3->GetMenuItemID( 1 );
				pSubMenu3->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "Keywords Filter(&K) (Ctrl + K)" ) );


		id = pSubMenu->GetMenuItemID( 3 );
		pSubMenu->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "Edit Selected Item (&I)" ) );

			pSubMenu2 = pSubMenu->GetSubMenu( 3 );
			

			id = pSubMenu2->GetMenuItemID( 0 );
			pSubMenu2->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "Copy (&C) (Ctrl + C)" ) ); //�ǉ� 2012.05.30

			id = pSubMenu2->GetMenuItemID( 1 );
			pSubMenu2->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "Paste (&P) (Ctrl + V)" ) ); //�ǉ� 2012.05.30

			id = pSubMenu2->GetMenuItemID( 2 );
			pSubMenu2->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "Delete Cell (&D) (Ctrl + Delete)" ) ); //�ǉ� 2012.05.31

			id = pSubMenu2->GetMenuItemID( 3 );
			pSubMenu2->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "Delete Row (Delete)" ) ); //�ύX 2012.05.30

			id = pSubMenu2->GetMenuItemID( 4 );
			pSubMenu2->ModifyMenu( 4, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) ); //�ǉ� 2012.05.30

			id = pSubMenu2->GetMenuItemID( 5 );
			pSubMenu2->ModifyMenu( 5, MF_BYPOSITION | MF_STRING, id, TEXT( "Bold (&B)" ) );

			id = pSubMenu2->GetMenuItemID( 6 );
			pSubMenu2->ModifyMenu( 6, MF_BYPOSITION | MF_STRING, id, TEXT( "Red (&R)" ) );

			id = pSubMenu2->GetMenuItemID( 7 );
			pSubMenu2->ModifyMenu( 7, MF_BYPOSITION | MF_STRING, id, TEXT( "Emphasized Format Cancellation (&C)" ) );

			id = pSubMenu2->GetMenuItemID( 8 );
			pSubMenu2->ModifyMenu( 8, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) );

			id = pSubMenu2->GetMenuItemID( 9 );
			pSubMenu2->ModifyMenu( 9, MF_BYPOSITION | MF_STRING, id, TEXT( "Expand List File (&E)" ) );

			id = pSubMenu2->GetMenuItemID( 10 );
			pSubMenu2->ModifyMenu( 10, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) );

			id = pSubMenu2->GetMenuItemID( 11 );
			pSubMenu2->ModifyMenu( 11, MF_BYPOSITION | MF_STRING, id, TEXT( "Expand Music List File (&M)" ) );

			
		id = pSubMenu->GetMenuItemID( 4 );
		pSubMenu->ModifyMenu( 4, MF_BYPOSITION | MF_STRING, id, TEXT( "Copy (&C)" ) );

			pSubMenu2 = pSubMenu->GetSubMenu( 4 );
			
			id = pSubMenu2->GetMenuItemID( 0 );
			pSubMenu2->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "EasySelect ON (&O)" ) );

			id = pSubMenu2->GetMenuItemID( 1 );
			pSubMenu2->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "EasySelect OFF" ) );

			id = pSubMenu2->GetMenuItemID( 2 );
			pSubMenu2->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "Copy (&C)" ) );


		id = pSubMenu->GetMenuItemID( 5 );
		pSubMenu->ModifyMenu( 5, MF_BYPOSITION | MF_STRING, id, TEXT( "Sort By... (&S)" ) );

			pSubMenu2 = pSubMenu->GetSubMenu( 5 );

			id = pSubMenu2->GetMenuItemID( 0 );
			pSubMenu2->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "Sort Items by RepetitionNum (&N)" ) );

			id = pSubMenu2->GetMenuItemID( 1 );
			pSubMenu2->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "Sort Items by FileName (&F)" ) );

			id = pSubMenu2->GetMenuItemID( 2 );
			pSubMenu2->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "Sort Items by DataSize (&S)" ) );

			id = pSubMenu2->GetMenuItemID( 3 );
			pSubMenu2->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "Sort Items by Date (&D)" ) );

			id = pSubMenu2->GetMenuItemID( 4 );
			pSubMenu2->ModifyMenu( 4, MF_BYPOSITION | MF_STRING, id, TEXT( "Sort Items by PathName (&P)" ) );

			id = pSubMenu2->GetMenuItemID( 5 );
			pSubMenu2->ModifyMenu( 5, MF_BYPOSITION | MF_STRING, id, TEXT( "Sort Items by StrFormat" ) );

			id = pSubMenu2->GetMenuItemID( 6 );
			pSubMenu2->ModifyMenu( 6, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) );

			id = pSubMenu2->GetMenuItemID( 7 );
			pSubMenu2->ModifyMenu( 7, MF_BYPOSITION | MF_STRING, id, TEXT( "Merge (&M)" ) );


		id = pSubMenu->GetMenuItemID( 6 );
		pSubMenu->ModifyMenu( 6, MF_BYPOSITION | MF_STRING, id, TEXT( "Open By... (&O)" ) );

			pSubMenu2 = pSubMenu->GetSubMenu( 6 );

			id = pSubMenu2->GetMenuItemID( 0 );
			pSubMenu2->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "Explorer (&E)" ) );

			id = pSubMenu2->GetMenuItemID( 1 );
			pSubMenu2->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "MediaPlayer (&M)" ) );

			id = pSubMenu2->GetMenuItemID( 2 );
			pSubMenu2->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "ConnectedApplication (&C)" ) );

			id = pSubMenu2->GetMenuItemID( 3 );
			pSubMenu2->ModifyMenu( 3, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) );

			id = pSubMenu2->GetMenuItemID( 4 );
			pSubMenu2->ModifyMenu( 4, MF_BYPOSITION | MF_STRING | MF_GRAYED, id, TEXT( "VirtualBrowser (&V)" ) );

			id = pSubMenu2->GetMenuItemID( 5 );
			pSubMenu2->ModifyMenu( 5, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) );

			id = pSubMenu2->GetMenuItemID( 6 );
			pSubMenu2->ModifyMenu( 6, MF_BYPOSITION | MF_STRING, id, TEXT( "Link File Open (&L)" ) );

			id = pSubMenu2->GetMenuItemID( 7 );
			pSubMenu2->ModifyMenu( 7, MF_BYPOSITION | MF_SEPARATOR, id, TEXT( "" ) );

			id = pSubMenu2->GetMenuItemID( 8 );
			pSubMenu2->ModifyMenu( 8, MF_BYPOSITION | MF_STRING, id, TEXT( "Play Emphasized Music (&P)" ) );


		id = pSubMenu->GetMenuItemID( 7 );
		pSubMenu->ModifyMenu( 7, MF_BYPOSITION | MF_STRING, id, TEXT( "Option (&O)" ) );

			pSubMenu2 = pSubMenu->GetSubMenu( 7 );

			id = pSubMenu2->GetMenuItemID( 0 );
			pSubMenu2->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "Version (&V)" ) );

			id = pSubMenu2->GetMenuItemID( 1 );
			pSubMenu2->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "Tips (&T)" ) );

			id = pSubMenu2->GetMenuItemID( 2 );
			pSubMenu2->ModifyMenu( 2, MF_BYPOSITION | MF_STRING, id, TEXT( "Message from T (&M)" ) );


			id = pSubMenu2->GetMenuItemID( 3 );
			pSubMenu2->ModifyMenu( 3, MF_BYPOSITION | MF_STRING, id, TEXT( "Language (&L)" ) );


				pSubMenu3 = pSubMenu2->GetSubMenu( 3 );

				id = pSubMenu3->GetMenuItemID( 0 );
				pSubMenu3->ModifyMenu( 0, MF_BYPOSITION | MF_STRING, id, TEXT( "English (&E) (Ctrl + L)" ) );

				id = pSubMenu3->GetMenuItemID( 1 );
				pSubMenu3->ModifyMenu( 1, MF_BYPOSITION | MF_STRING, id, TEXT( "Japanese (&J)" ) );


			id = pSubMenu2->GetMenuItemID( 4 );
			pSubMenu2->ModifyMenu( 4, MF_BYPOSITION | MF_STRING, id, TEXT( "PreferenceFile:Clear (&P)" ) );


			id = pSubMenu2->GetMenuItemID( 5 );
			pSubMenu2->ModifyMenu( 5, MF_BYPOSITION | MF_STRING, id, TEXT( "CurrentDirectory:Open (&O)" ) );

			id = pSubMenu2->GetMenuItemID( 6 );
			pSubMenu2->ModifyMenu( 6, MF_BYPOSITION | MF_STRING, id, TEXT( "FilePathLimitCheck (&C)" ) );

	pMenu->DestroyMenu();
	pSubMenu->DestroyMenu();
	pSubMenu2->DestroyMenu();
	pSubMenu3->DestroyMenu();

	DrawMenuBar();
}


void CFileListCreatorDlg::OnLanguageEnglish()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

    CMenu    cMenu;
    int      err = 0;
    
    // ���j���[�����[�h
    if (!err) if (!cMenu.LoadMenu(IDR_MENU2)) err = 1;

	SetMenu(&cMenu); //http://www.gidforums.com/t-17869.html

	SelectedLanguage = _T("English");

	//============================================== XP�΍� (MF_GRAYED) ===================================================

	// CMainFrame�N���X�ȊO�Ȃ�΁AAfxGetMainWnd()->GetMenu()�Ŏ擾����B this->AfxGetMainWnd()->GetMenu()
	CMenu* pMenu = &cMenu; //�ύX 2012.04.14
	CMenu* pSubMenu;
	CMenu* pSubMenu2;
	CMenu* pSubMenu3;

	UINT id;

	id = pMenu->GetMenuItemID( 0 );
	pMenu->ModifyMenu( 6, MF_BYPOSITION | MF_STRING, id, TEXT( "Open By... (&O)" ) );

		pSubMenu = pMenu->GetSubMenu( 6 );


		id = pSubMenu->GetMenuItemID( 4 );
		pSubMenu->ModifyMenu( 4, MF_BYPOSITION | MF_STRING | MF_GRAYED, id, TEXT( "VirtualBrowser (&V)" ) );


	id = pMenu->GetMenuItemID( 0 );
	pMenu->ModifyMenu( 8, MF_BYPOSITION | MF_STRING, id, TEXT( "���ׂĂ̋@�\ (&A)" ) );

		pSubMenu = pMenu->GetSubMenu( 8 );

		id = pSubMenu->GetMenuItemID( 6 );
		pSubMenu->ModifyMenu( 6, MF_BYPOSITION | MF_STRING, id, TEXT( "�J�� (&O)" ) );

			pSubMenu2 = pSubMenu->GetSubMenu( 6 );


			id = pSubMenu2->GetMenuItemID( 4 );
			pSubMenu2->ModifyMenu( 4, MF_BYPOSITION | MF_STRING | MF_GRAYED, id, TEXT( "�o�[�`���� �u���E�U�[ (&V)" ) );

	pMenu->DestroyMenu();
	pSubMenu->DestroyMenu();
	pSubMenu2->DestroyMenu();
	pSubMenu3->DestroyMenu();

	DrawMenuBar();
	//=========================================================================================================

	// ���j���[��j��
    //cMenu.DestroyMenu();

	//http://social.msdn.microsoft.com/Forums/en-US/vcgeneral/thread/24f3924a-053a-4c9d-91c1-7af278353374/

	//DrawMenuBar();
}

void CFileListCreatorDlg::ChangeLanguage()
{
	if (SelectedLanguage == _T("Japanese")) {
		CFileListCreatorDlg::OnLanguageEnglish();
		CFileListCreatorDlg::StatusStringSet(_T("���j���[���p��ɕύX���܂��� (�ēx Ctrl + L �������Ɠ��{��ɂȂ�܂�)"),0,FALSE);
	}else if (SelectedLanguage == _T("English")){
		CFileListCreatorDlg::OnLanguageJapanese();
		CFileListCreatorDlg::StatusStringSet(_T("���j���[����{��ɕύX���܂��� (�ēx Ctrl + L �������Ɖp��ɂȂ�܂�)"),0,FALSE);
	}else{
		CFileListCreatorDlg::OnLanguageEnglish();
		CFileListCreatorDlg::StatusStringSet(_T("���j���[���p��ɕύX���܂��� (Ctrl + L �𐄂��Ɠ��{��ɂȂ�܂�)"),0,FALSE);
	}
}

void CFileListCreatorDlg::OnOpenbyVirtualbrowser()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	MessageBox(_T("���@�\�͍쐬���ł��B"),_T("FileList Creator"),MB_OK);
}


void CFileListCreatorDlg::OnOptionFilepathlimitcheck()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	//LVITEM       lvi;
	int          i, index = 0;
	int          err = 0;
	CString FullPathString;

	CString SeparateDirectoryStr;

	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	UpdateData();
	lvi.mask = LVIF_TEXT;

	BOOL ErrFLG;

	ErrFLG = FALSE;

	while (index < CFileListCreatorDlg::m_xcList.GetItemCount()){

		//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������

		FullPathString = CFileListCreatorDlg::m_xcList.GetItemText(index,2);

		if (FullPathString!=_T("")){
			//http://oshiete.goo.ne.jp/qa/1638451.html

			//setlocale( LC_CTYPE, "jpn" );

			wchar_t wbuf[1024];
			char buf[1024];
			int buflen;
			lstrcpyW(wbuf,const_cast<LPTSTR>(static_cast<LPCTSTR>(FullPathString)));
			buflen = WideCharToMultiByte(CP_ACP,0,wbuf,-1,buf,0,NULL,NULL);
			WideCharToMultiByte(CP_ACP,0,(LPCWSTR)wbuf,-1,buf,buflen,NULL,NULL);

			int nLen = strlen(buf);

			//http://www.c-lang.net/functions/mblen.html

			//int nLen = FullPathString.GetLength() * sizeof(TCHAR);

			//http://www.kab-studio.biz/Programing/Codian/MxA/09.html

			//http://oshiete.goo.ne.jp/qa/7150644.html
			if (nLen>255){
				if (!err)
				{
					CString str;

					str.Format(_T("%d �o�C�g"),nLen);

					//lvi.mask = LVIF_TEXT | LVIF_PARAM;
					lvi.iItem = index;
	 				lvi.iSubItem =8;
					//lvi.pszText = _T("�[������p�X");		//���l��
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("�[������p�X")));		//���l��
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
				}
				ErrFLG = TRUE;
			}

			i=0;
			SeparateDirectoryStr=_T("");

			int StartIDX = 0;
			int EndIDX = 0;

			while ( i < FullPathString.GetLength()){
				//http://oshiete.goo.ne.jp/qa/1638451.html

				//setlocale( LC_CTYPE, "jpn" );
				
				if( FullPathString.Mid(i,1)==_T("\\")|| i == FullPathString.GetLength()-1) {
					EndIDX = i;
					if (i == FullPathString.GetLength()-1){
						SeparateDirectoryStr = FullPathString.Mid(StartIDX+1,EndIDX-StartIDX);
					}else{
						SeparateDirectoryStr = FullPathString.Mid(StartIDX+1,EndIDX-StartIDX-1);
					}

					StartIDX = i;

					if (SeparateDirectoryStr !=_T("")){
						wchar_t wbuf[1024];
						char buf[1024];
						int buflen;
						lstrcpyW(wbuf,const_cast<LPTSTR>(static_cast<LPCTSTR>(SeparateDirectoryStr)));
						buflen = WideCharToMultiByte(CP_ACP,0,wbuf,-1,buf,0,NULL,NULL);
						WideCharToMultiByte(CP_ACP,0,(LPCWSTR)wbuf,-1,buf,buflen,NULL,NULL);

						int nLen = strlen(buf);

						//http://www.c-lang.net/functions/mblen.html

						//int nLen = FullPathString.GetLength() * sizeof(TCHAR);

						//http://www.kab-studio.biz/Programing/Codian/MxA/09.html

						//http://oshiete.goo.ne.jp/qa/7150644.html
						if (nLen>31 * 2){ //�l�����@�g�e�r  �R�P����(31Byte)�̐������󂯂� iTunes�����l�H
							if (!err)
							{
								CString str;

								str.Format(_T("%d Byte:�t�H���_���܂��̓t�@�C���������߂��܂�"),nLen);

								//lvi.mask = LVIF_TEXT | LVIF_PARAM;
								lvi.iItem = index;
	 							lvi.iSubItem =8;
								//lvi.pszText = _T("�[������p�X");		//���l��
								lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(str));		//���l��
								if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
							}
							ErrFLG = TRUE;
						}
					}
				}
				i++;
			}
		}
		//delete[] lpsz;

		CFileListCreatorDlg::m_xcList.EnsureVisible(index, FALSE);
		UpdateWindow();

		index++;
	}

	if( ErrFLG == TRUE ){
		CFileListCreatorDlg::StatusStringSet(_T("�G���[��������܂��� \r\n (iTunes�Ȃǂ̉��y�\�t�g�ɂ����ēǍ��G���[����������\��������܂�)"),300,TRUE);
	}else{
		CFileListCreatorDlg::StatusStringSet(_T("���X�g�� �S�ẴA�C�e���ɂ����ăG���[��������܂���ł���"),300,TRUE);
	}
	//m_xcList.SetItemData(index,11);

	//if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1)m_xcStaticString.ShowWindow(SW_HIDE);

	//CFileListCreatorDlg::ItemCount_Func(TRUE);

	//CFileListCreatorDlg::Total_Bytes_Func();
	//CFileListCreatorDlg::m_xcList,InsertString(0,lvi);
	//CMylistCtrl::DrawItem(LVITEM lvi);
	RedrawWindow();
	return;
}


void CFileListCreatorDlg::CreateWorkArray(){

}

void CFileListCreatorDlg::OnEditlistUndo()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if (m_xvChkUseUNDO == FALSE) CFileListCreatorDlg::StatusStringSet(_T("UNDO�@�\���L���ɂȂ��Ă��܂���\r\n( �uUse UNDO/REDO�v�Ƀ`�F�b�N�����Ă������� )"),0,TRUE);

	if (m_xvChkUseUNDO == FALSE) return;


	//http://oshiete.goo.ne.jp/qa/7451265.html
	if (UNDO_FLG == TRUE){
		
		//vecNow.clear();
		//copy( vecWork.begin(), vecWork.end(), back_inserter( vecNow ) );

		LastNowItemCount = CFileListCreatorDlg::m_xcList.GetItemCount();
		CFileListCreatorDlg::push_back_Func(LastNowItemCount,_T("nowData"));
	}else if (UNDO_FLG == FALSE) {
		LastPrevItemCount = CFileListCreatorDlg::m_xcList.GetItemCount();
		CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("PrevData"));
	}

	LastNowItemCount = CFileListCreatorDlg::m_xcList.GetItemCount(); //�ޔ�
	m_xcList.DeleteAllItems();


	if (UNDO_FLG == TRUE) {
		//LastPrevItemCount = CFileListCreatorDlg::m_xcList.GetItemCount();
		CFileListCreatorDlg::pop_Func(LastPrevItemCount,_T("prevData"));
	}else{
		//LastNowItemCount = CFileListCreatorDlg::m_xcList.GetItemCount();
		CFileListCreatorDlg::pop_Func(LastNowItemCount,_T("nowData"));
	}


	CFileListCreatorDlg::SetStrFormat_Func();

	CFileListCreatorDlg::Total_Bytes_Bold();
	CFileListCreatorDlg::Total_Bytes_Func();
	CFileListCreatorDlg::ItemCount_Func(TRUE);


	if(CFileListCreatorDlg::m_xcList.GetItemCount() >= LastSelectedRow){
		m_xcList.EnsureVisible(LastSelectedRow, FALSE);

		m_xcList.SetItemState(LastSelectedRow,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
		LVIS_FOCUSED | LVIS_SELECTED,    // ���
		LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N
	}else{
		m_xcList.EnsureVisible(0, FALSE);
	}

	if (UNDO_FLG == TRUE){
		CFileListCreatorDlg::StatusStringSet(_T("UNDO �I��"),0,TRUE);
	}else{
		CFileListCreatorDlg::StatusStringSet(_T("REDO �I��"),0,TRUE);
	}
	
	if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1 || MiniWindowFLG == FALSE){
		m_xcStaticString.ShowWindow(SW_HIDE);
	}else{
		m_xcStaticString.ShowWindow(SW_SHOW);
	}

	RedrawWindow();

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
		SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24
	}
	

	UNDO_FLG = !UNDO_FLG;
	return;

	//http://okwave.jp/qa/q1093585.html
}

void CFileListCreatorDlg::pop_Func(int ItemCount,CString targetName){

	//if (m_xvChkUseUNDO == FALSE) CFileListCreatorDlg::StatusStringSet(_T("UNDO�@�\���L���ɂȂ��Ă��܂���\r\n( �uUse UNDO/REDO�v�Ƀ`�F�b�N�����Ă������� )"),0,TRUE);

	if (m_xvChkUseUNDO == FALSE) return;

	UpdateData();
	lvi.mask = LVIF_TEXT;

    int ItemNo = 0;
    int SubItemNo = 0;
    int err = 0;

	if (UNDO_FLG == TRUE){
		CFileListCreatorDlg::StatusStringSet(_T("UNDO ���s��"),0,FALSE);
	}else{
		CFileListCreatorDlg::StatusStringSet(_T("REDO ���s��"),0,FALSE);
	}

	if (targetName==_T("prevData")){
		//ItemNo = 0;

		
		vector<ListItemStruct>::iterator it = vecPrev.begin();
		while( it != vecPrev.end() ) //&&  ItemNo < LastPrevItemCount
		{
			//if (LastPrevItemCount==0) break;
			//BOOL NoFullPathFLG = FALSE;
			SubItemNo=0;
			
			while (SubItemNo<=9){
				//if (!err)
				{

					CString outData;


					switch (SubItemNo){
						case 0:
							outData = vecPrev[ItemNo].RepetitionNum;
							break;
						case 1:
							outData = vecPrev[ItemNo].Num;
							break;
						case 2:
							outData = vecPrev[ItemNo].FullPath;
							break;
						case 3:
							outData = vecPrev[ItemNo].FileName;
							break;
						case 4:
							outData = vecPrev[ItemNo].ApproximateByte;
							break;
						case 5:
							outData = vecPrev[ItemNo].AccurateByte;
							break;
						case 6:
							outData = vecPrev[ItemNo].ModifyDate;
							break;
						case 7:
							outData = vecPrev[ItemNo].ModifyTime;
							break;
						case 8:
							outData = vecPrev[ItemNo].RemarksColumn;
							break;
						case 9:
							outData = vecPrev[ItemNo].FormatDataStr;
							break;
					}
					
				
					lvi.iItem = ItemNo;
					lvi.iSubItem = SubItemNo;
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(outData));
					
					if (SubItemNo==0){
						if (!m_xcList.InsertItem(&lvi)) err = 1;
					}else{
						if (!m_xcList.SetItem(&lvi)) err = 1;
					}


					//http://homepage2.nifty.com/well/STL.html#ITERATOR
					//http://www.geocities.co.jp/bleis_tift/cpp/stl.html
					//vector<ListItemStruct>::iterator it =ItemNo;
				}
				//if ( NoFullPathFLG== TRUE )	CFileListCreatorDlg::m_xcList.DeleteItem(ItemNo);
				SubItemNo++;
			}
			ItemNo++;
			++it;
		}
	}


	if (targetName==_T("nowData")){
		//http://www.geocities.jp/ky_webid/cpp/library/022.html

		//vecNow.clear();
		//copy( vecWork.begin(), vecWork.end(), back_inserter( vecNow ) );

		vector<ListItemStruct>::iterator it = vecNow.begin();
		while( it != vecNow.end() ) // &&  ItemNo < LastNowItemCount
		{
			//if (LastPrevItemCount==0) break;
			//BOOL NoFullPathFLG = FALSE;
			SubItemNo=0;
			
			while (SubItemNo<=9){
				//if (!err)
				{

					CString outData;

					switch (SubItemNo){
						case 0:
							outData = vecNow[ItemNo].RepetitionNum;
							break;
						case 1:
							outData = vecNow[ItemNo].Num;
							break;
						case 2:
							outData = vecNow[ItemNo].FullPath;
							break;
						case 3:
							outData = vecNow[ItemNo].FileName;
							break;
						case 4:
							outData = vecNow[ItemNo].ApproximateByte;
							break;
						case 5:
							outData = vecNow[ItemNo].AccurateByte;
							break;
						case 6:
							outData = vecNow[ItemNo].ModifyDate;
							break;
						case 7:
							outData = vecNow[ItemNo].ModifyTime;
							break;
						case 8:
							outData = vecNow[ItemNo].RemarksColumn;
							break;
						case 9:
							outData = vecNow[ItemNo].FormatDataStr;
							break;
					}
					
				
					lvi.iItem = ItemNo;
					lvi.iSubItem = SubItemNo;
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(outData));
					
					if (SubItemNo==0){
						if (!m_xcList.InsertItem(&lvi)) err = 1;
					}else{
						if (!m_xcList.SetItem(&lvi)) err = 1;
					}
				}
				//if ( NoFullPathFLG== TRUE )	CFileListCreatorDlg::m_xcList.DeleteItem(ItemNo);
				SubItemNo++;
			}
			ItemNo++;
			++it;
		}
	}
}
///void CFileListCreatorDlg::DuplicateList(CMylistCtrl *outList, CMylistCtrl *inList){
void CFileListCreatorDlg::push_back_Func(int ItemCount,CString targetName){

	//if (m_xvChkUseUNDO == FALSE) CFileListCreatorDlg::StatusStringSet(_T("UNDO�@�\���L���ɂȂ��Ă��܂���\r\n( �uUse UNDO/REDO�v�Ƀ`�F�b�N�����Ă������� )"),0,TRUE);

	if (m_xvChkUseUNDO == FALSE && ShellExecuteOpenFLG == FALSE) return; //ShellExecuteOpenFLG = FALSE; //���P�̍� //��Œ��� //�ǉ� 2012.06.14

	g_NoDrawFLG = TRUE;
	//http://atashi.net/inu/ja/notes/stl_vector_sort.html
	//http://www.geocities.jp/ky_webid/cpp/library/002.html

	if (UNDO_FLG == TRUE){
		CFileListCreatorDlg::StatusStringSet(_T("UNDO�f�[�^ �ޔ�"),0,FALSE);
	}else{
		CFileListCreatorDlg::StatusStringSet(_T("REDO�f�[�^ �ޔ�"),0,FALSE);
	}

	int iTemp = 1;
	int iCount = CFileListCreatorDlg::m_xcList.GetItemCount();

	if (targetName==_T("prevData")){
		UNDO_FLG = TRUE;

		int ItemNo;
		int SubItemNo;
		//int err = 0;

		vecPrev.clear(); //��Ŋm�F

		ItemNo = 0;
		while ( ItemNo < ItemCount )
		{
			SubItemNo=0;
			while (SubItemNo<=9){
				//if (!err)
				{
					

					if (SubItemNo == 9 )CFileListCreatorDlg::SetFormatNumToStr_Items(ItemNo);

					CString inData;

					inData = CString(m_xcList.GetItemText(ItemNo, SubItemNo));
					
					switch (SubItemNo){
						case 0:
							PrevListPtr->RepetitionNum = inData;
							//strcpy(PrevListPtr->RepetitionNum,inData);
							break;
						case 1:
							PrevListPtr->Num = inData;
							break;
						case 2:
							PrevListPtr->FullPath = inData;
							break;
						case 3:
							PrevListPtr->FileName = inData;
							break;
						case 4:
							PrevListPtr->ApproximateByte = inData;
							break;
						case 5:
							PrevListPtr->AccurateByte = inData;
							break;
						case 6:
							PrevListPtr->ModifyDate = inData;
							break;
						case 7:
							PrevListPtr->ModifyTime = inData;
							break;
						case 8:
							PrevListPtr->RemarksColumn = inData;
							break;
						case 9:
							PrevListPtr->FormatDataStr = inData;
							break;
					}
				}
				SubItemNo++;
			}

			//http://oshiete.goo.ne.jp/qa/6624666.html

			//vector<ListItemStruct>::iterator it = vecPrev.begin() + ItemNo;
			//vecPrev.erase(it);

			vector<ListItemStruct>::iterator it = vecPrev.begin();
			advance(it,ItemNo); // #include <iterator> needed.  //��������폜

			vecPrev.push_back( *PrevListPtr );//�V�����f�[�^����
			ItemNo++;

			if (UNDO_FLG == TRUE){
				CString tempStatus;
				tempStatus.Format(_T("UNDO�f�[�^ �ޔ� ( %d / %d ) ") , iTemp,iCount);					
				StatusStringSet(tempStatus,0,FALSE);
				UpdateData(FALSE);
				iTemp++;
			}else{
				CString tempStatus;
				tempStatus.Format(_T("REDO�f�[�^ �ޔ� ( %d / %d ) ") , iTemp,iCount);					
				StatusStringSet(tempStatus,0,FALSE);
				UpdateData(FALSE);
				iTemp++;
			}
		}

		//// �e�X�g�\��
		//for ( int i = 0; i < vecPrev.size(); i ++ ) {
		//	MessageBox( _T("vecPrev: ") + vecPrev[i].FullPath ); //�yA�z
		//}
	}


	if (targetName==_T("nowData")){
		UNDO_FLG = TRUE;

		int ItemNo;
		int SubItemNo;
		//int err = 0;


		vecNow.clear(); //��Ŋm�F

		ItemNo = 0;
		while ( ItemNo < ItemCount )
		{
			SubItemNo=0;
			while (SubItemNo<=9){
				//if (!err)
				{
					

					if (SubItemNo == 9 )CFileListCreatorDlg::SetFormatNumToStr_Items(ItemNo);

					CString inData;

					inData = CString(m_xcList.GetItemText(ItemNo, SubItemNo));
					
					switch (SubItemNo){
						case 0:
							NowListPtr->RepetitionNum = inData;
							//strcpy(NowListPtr->RepetitionNum,inData);
							break;
						case 1:
							NowListPtr->Num = inData;
							break;
						case 2:
							NowListPtr->FullPath = inData;
							break;
						case 3:
							NowListPtr->FileName = inData;
							break;
						case 4:
							NowListPtr->ApproximateByte = inData;
							break;
						case 5:
							NowListPtr->AccurateByte = inData;
							break;
						case 6:
							NowListPtr->ModifyDate = inData;
							break;
						case 7:
							NowListPtr->ModifyTime = inData;
							break;
						case 8:
							NowListPtr->RemarksColumn = inData;
							break;
						case 9:
							NowListPtr->FormatDataStr = inData;
							break;
					}
				}
				SubItemNo++;
			}

			//http://oshiete.goo.ne.jp/qa/6624666.html

			//vector<ListItemStruct>::iterator it = vecNow.begin() + ItemNo;
			//vecNow.erase(it);

			vector<ListItemStruct>::iterator it = vecNow.begin();
			advance(it,ItemNo); // #include <iterator> needed.  //��������폜

			vecNow.push_back( *NowListPtr );//�V�����f�[�^����
			ItemNo++;

			if (UNDO_FLG == TRUE){
				CString tempStatus;
				tempStatus.Format(_T("UNDO�f�[�^ �ޔ� ( %d / %d ) ") , iTemp,iCount);					
				StatusStringSet(tempStatus,0,FALSE);
				UpdateData(FALSE);
				iTemp++;
			}else{
				CString tempStatus;
				tempStatus.Format(_T("REDO�f�[�^ �ޔ� ( %d / %d ) ") , iTemp,iCount);					
				StatusStringSet(tempStatus,0,FALSE);
				UpdateData(FALSE);
				iTemp++;
			}
		}

		//// �e�X�g�\��
		//for ( int i = 0; i < vecNow.size(); i ++ ) {
		//	MessageBox( _T("vecNow: ") + vecNow[i].FullPath ); //�yA�z
		//}
	}


	if (targetName==_T("workData")){
		int ItemNo;
		int SubItemNo;
		//int err = 0;


		vecWork.clear(); //��Ŋm�F

		ItemNo = 0;
		while ( ItemNo < ItemCount )
		{
			SubItemNo=0;
			while (SubItemNo<=9){
				//if (!err)
				{
					

					if (SubItemNo == 9 )CFileListCreatorDlg::SetFormatNumToStr_Items(ItemNo);

					CString inData;

					inData = CString(m_xcList.GetItemText(ItemNo, SubItemNo));
					
					switch (SubItemNo){
						case 0:
							WorkListPtr->RepetitionNum = inData;
							//strcpy(WorkListPtr->RepetitionNum,inData);
							break;
						case 1:
							WorkListPtr->Num = inData;
							break;
						case 2:
							WorkListPtr->FullPath = inData;
							break;
						case 3:
							WorkListPtr->FileName = inData;
							break;
						case 4:
							WorkListPtr->ApproximateByte = inData;
							break;
						case 5:
							WorkListPtr->AccurateByte = inData;
							break;
						case 6:
							WorkListPtr->ModifyDate = inData;
							break;
						case 7:
							WorkListPtr->ModifyTime = inData;
							break;
						case 8:
							WorkListPtr->RemarksColumn = inData;
							break;
						case 9:
							WorkListPtr->FormatDataStr = inData;
							break;
					}
				}
				SubItemNo++;
			}
			//http://oshiete.goo.ne.jp/qa/6624666.html

			//vector<ListItemStruct>::iterator it = vecWork.begin() + ItemNo;
			//vecWork.erase(it);

			vector<ListItemStruct>::iterator it = vecWork.begin();
			advance(it,ItemNo); // #include <iterator> needed.  //��������폜

			vecWork.push_back( *WorkListPtr );//�V�����f�[�^����
			ItemNo++;

			if (UNDO_FLG == TRUE){
				CString tempStatus;
				tempStatus.Format(_T("UNDO�f�[�^ �ޔ� ( %d / %d ) ") , iTemp,iCount);					
				StatusStringSet(tempStatus,0,FALSE);
				UpdateData(FALSE);
				iTemp++;
			}else{
				CString tempStatus;
				tempStatus.Format(_T("REDO�f�[�^ �ޔ� ( %d / %d ) ") , iTemp,iCount);					
				StatusStringSet(tempStatus,0,FALSE);
				UpdateData(FALSE);
				iTemp++;
			}
		}

		//// �e�X�g�\��
		//for ( int i = 0; i < vecWork.size(); i ++ ) {
		//	MessageBox( _T("vecWork: ") + vecWork[i].FullPath ); //�yA�z
		//}
	}
	g_NoDrawFLG = FALSE;
}



void CFileListCreatorDlg::malloc_Func(int ItemCount,CString targetName){
	////http://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q1117611511
	////http://blogs.wankuma.com/jitta/archive/2008/12/16/164045.aspx
	//
	////if (targetName=_T("prevPrevData")){
	////	PrevPrevItemCount = ItemCount;

	////	if( PrevPrevItemCount == 0 ) {
	////		prevData = (ListItemStruct*)malloc(sizeof(ListItemStruct));
	////		if (prevData == NULL) { return; }
	////	} else {
	////		prevData = (ListItemStruct*)realloc(prevData,sizeof(ListItemStruct)*PrevPrevItemCount+1);
	////		if (prevData == NULL) {
	////			free(prevData);
	////			prevData = NULL;
	////		}
	////	}

	////	//PrevPrevItemCount++;
	////}

	//if (targetName=_T("prevData")){
	//	//LastPrevItemCount = ItemCount;
}

void CFileListCreatorDlg::DuplicateList(){
	
	::SetFocus(::GetDlgItem(m_hWnd,IDC_LIST));


	LastPrevItemCount  = CFileListCreatorDlg::m_xcList.GetItemCount();

	CFileListCreatorDlg::malloc_Func(LastPrevItemCount,_T("prevData"));

	UpdateData();
	lvi.mask = LVIF_TEXT;

	::SetFocus(::GetDlgItem(m_hWnd,IDC_LIST));

	return;

//	//w_m_xcList = m_xcList;
//	//m_xcList = m_xcList2;
//	//m_xcList2 = w_m_xcList;
}

void CFileListCreatorDlg::OnLvnDeleteitemList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B


	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13
	////http://q.hatena.ne.jp/1180853478
	//AfxGetMainWnd()->SetWindowText(_T("FileListCreator (*)")); //�ǉ� 2012.05.13

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}

	*pResult = 0;
}


void CFileListCreatorDlg::OnLvnItemchangingList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	//LVITEM lvItem;
	//lvItem.mask			= LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_INDENT |  LVCF_SUBITEM; //�ǉ� 2012.05.16 LVCF_SUBITEM�ǉ�


	//CString tempStr;
	//tempStr.Format(_T("OnLvnItem changing List iItem: %d,iSubItem: %d, lParam: %d, uChanged: %d, uNewState: %d, uOldState: %d\n"), pNMLV->iItem, pNMLV->iSubItem, pNMLV->lParam, pNMLV->uChanged, pNMLV->uNewState, pNMLV->uOldState);
	////MessageBox(tempStr);

	//TRACE(tempStr);


	//LVITEM       lvi;
	int          index = 0;
	int          err = 0;
	CString      CurStr;	
	CString      FullPathString;

	BOOL LengthOver = FALSE;

	UpdateData();
	lvi.mask = LVIF_TEXT;			

	index = pNMLV->iItem;

	int ColumnNum;

	for (ColumnNum = 0;ColumnNum <= 8;ColumnNum++){
		CurStr = CFileListCreatorDlg::m_xcList.GetItemText(index,ColumnNum);

		if (CurStr!=_T("")) {
			lvi.iItem =index;
			lvi.iSubItem = ColumnNum;

			//MessageBox(RemarksColumnStr);

			if (CurStr.GetLength() > 260){
				CurStr = CurStr.Left(260);
				//LengthOver = TRUE;
				CFileListCreatorDlg::StatusStringSet(_T("���X�g�{�b�N�X���̊i�[�������������I�[�o�[���܂���\r\n(������260������ �e�L�X�g��؂���܂�)"),0,TRUE);
				lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(CurStr));
				CFileListCreatorDlg::m_xcList.SetItem(&lvi);
				UpdateData(FALSE);
			}
		}
	}

	*pResult = 0;
}


void CFileListCreatorDlg::OnLvnColumnclickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	if (m_xvChkEditCellMode == TRUE){
		if (LastSelectedRow!=-1 && LastSelectedColumn!=-1) {
			lvi.mask = LVIF_TEXT;// | LVIF_PARAM; //�f�[�^�̍X�V���ɕK�v�I�I

			lvi.iItem = LastSelectedRow;
			lvi.iSubItem = LastSelectedColumn;
					
			::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT_Item)); //�ǉ� 2012.05.20

			CString UpadateItem;
			((CEdit*)GetDlgItem(IDC_EDIT_Item))->GetWindowText(UpadateItem);

			CString LastEditStr = m_xcList.GetItemText(LastSelectedRow,LastSelectedColumn);

			if (LastEditStr != UpadateItem) {

				int myResult;
				myResult = MessageBox(_T("�ҏW���̃f�[�^���m�肵�Ă���\�[�g���������s���܂����H\r\n�u�͂��v�f�[�^�X�V���\�[�g����\r\n�u�������v�f�[�^���X�V�����Ƀ\�[�g����\r\n�u�L�����Z���v�f�[�^�̍X�V���\�[�g�����s���Ȃ�") ,_T("�ۑ��m�F"), MB_YESNOCANCEL );

				if (IDYES == myResult){
					lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(UpadateItem));
					if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) //err = 1;
					UpdateData(FALSE);

					StatusStringSet(_T("�Z���̃f�[�^���X�V���܂���"),0,TRUE);

					LastSelectedRow=-1;
					//LastSelectedColumn=-1;
				}else if (IDCANCEL == myResult){
					return;
				}
			}
			CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_EditCellMode);
			//�`�F�b�N���O��
			chkbox1->SetCheck(0);

			m_xvChkEditCellMode = FALSE;

			::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
			::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08


			CFileListCreatorDlg::StatusStringSet(_T("�ʏ�̃��[�h�ł� (�Z�����̃e�L�X�g�͕ҏW�ł��܂���)"),0,TRUE);
			m_xvStrEditCellMode = _T("�F�@�ʏ탂�[�h");
			UpdateData(FALSE);

			::SetFocus(::GetDlgItem(m_hWnd,IDC_LIST)); //�ǉ� 2012.05.20
		}
	}

	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	//::SetFocus(::GetDlgItem(m_hWnd,IDC_LIST)); //�ǉ� 2012.05.24

	CFileListCreatorDlg::GetStrFormat_Func();

	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

	StatusStringSet(_T("Sort ���s��"),0,FALSE); //�ύX 2012.06.14
	RenumberItem();				// SortItems�֐����Ăяo���O�ɂ͕K�����s

	//pNMLV->iSubItem;
//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������


	switch(pNMLV->iSubItem){
	case 0:
		{
			keyColumn = 0; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������ // �f�[�^�T�C�Y��4�ɂ���
			static BOOL bSort = TRUE;			// static�Œ�`���邱�� //�d���i���o�[�������悤�ɏ�ɂs�q�t�d
			m_xcList.SortItems(CompareFunc, bSort);

			if (bSort == FALSE) { 
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�d���A�C�e�� ����)"),0,TRUE);
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�d���A�C�e�� �~��)"),0,TRUE);
			}
			SortColumnDrawCaption(pNMLV->iSubItem, bSort);
			//bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���
		}
		break;

	case 1:
		{
			keyColumn = 1; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������ // �f�[�^�T�C�Y��4�ɂ���
			static BOOL bSort = FALSE;			// static�Œ�`���邱��
			m_xcList.SortItems(CompareFunc, bSort);

			if (bSort == FALSE) { 
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�A�� ����)"),0,TRUE);
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�A�� �~��)"),0,TRUE);
			}
			SortColumnDrawCaption(pNMLV->iSubItem, bSort);
			bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���
		}
		break;

	case 2:
		{
			keyColumn = 2; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������
			static BOOL bSort = FALSE;			// static�Œ�`���邱��
			m_xcList.SortItems(CompareFunc, bSort);

			if (bSort == FALSE) { 
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�t�@�C���p�X ����)"),0,TRUE);
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�t�@�C���p�X �~��)"),0,TRUE);
			}
			SortColumnDrawCaption(pNMLV->iSubItem, bSort);
			bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���
		}
		break;

	case 3:
		{
			keyColumn = 3; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������
			static BOOL bSort = FALSE;			// static�Œ�`���邱��
			m_xcList.SortItems(CompareFunc, bSort);

			if (bSort == FALSE) { 
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�t�@�C���� �~��)"),0,TRUE);
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�t�@�C���� ����)"),0,TRUE);
			}
			SortColumnDrawCaption(pNMLV->iSubItem, bSort);
			bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���
		}
		break;

	case 4:
		{
			keyColumn = 5; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������ // �f�[�^�T�C�Y��4�ɂ���
			static BOOL bSort = FALSE;			// static�Œ�`���邱��
			m_xcList.SortItems(CompareFunc, bSort);

			if (bSort == FALSE) { 
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�f�[�^�T�C�Y ����)"),0,TRUE);
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�f�[�^�T�C�Y �~��)"),0,TRUE);
			}
			SortColumnDrawCaption(pNMLV->iSubItem, bSort);
			bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���
		}
		break;
	case 5:
		{
			keyColumn = 5; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������ // �f�[�^�T�C�Y��4�ɂ���
			static BOOL bSort = FALSE;			// static�Œ�`���邱��
			m_xcList.SortItems(CompareFunc, bSort);

			if (bSort == FALSE) { 
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�f�[�^�T�C�Y ����)"),0,TRUE);
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�f�[�^�T�C�Y �~��)"),0,TRUE);
			}
			SortColumnDrawCaption(pNMLV->iSubItem, bSort);
			bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���
		}
		break;

	case 6:
		{
			keyColumn = 7; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������
			static BOOL bSort = FALSE;			// static�Œ�`���邱��
			m_xcList.SortItems(CompareFunc, bSort);

			if (bSort == FALSE) { 
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�C���� ����)"),0,TRUE);
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�C���� �~��)"),0,TRUE);
			}
			SortColumnDrawCaption(pNMLV->iSubItem, bSort);
			bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���
		}
		break;
	case 7:
		{
			keyColumn = 7; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������
			static BOOL bSort = FALSE;			// static�Œ�`���邱��
			m_xcList.SortItems(CompareFunc, bSort);

			if (bSort == FALSE) { 
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�C���� ����)"),0,TRUE);
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�C���� �~��)"),0,TRUE);
			}
			SortColumnDrawCaption(pNMLV->iSubItem, bSort);
			bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���
		}
		break;
	case 8:
		{
			keyColumn = 8; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������
			static BOOL bSort = FALSE;			// static�Œ�`���邱��
			m_xcList.SortItems(CompareFunc, bSort);

			if (bSort == FALSE) { 
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(���l�� ����)"),0,TRUE);
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(���l�� �~��)"),0,TRUE);
			}
			SortColumnDrawCaption(pNMLV->iSubItem, bSort);
			bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���
		}
		break;
	case 9:
		{
			keyColumn = 9;//keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������ 9:�������
			static BOOL bSort = FALSE;			// static�Œ�`���邱��
			m_xcList.SortItems(CompareFunc, bSort);

			if (bSort == FALSE) { 
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(���� ����)"),0,TRUE);
			}else{
				CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(���� �~��)"),0,TRUE);
			}
			SortColumnDrawCaption(pNMLV->iSubItem, bSort);
			bSort = !bSort;				// bSort��FALSE�Ȃ�TRUE�ATRUE�Ȃ�FALSE�ɂ���
		}
		break;
	}

	//CFileListCreatorDlg::m_xcList.EnsureVisible(0, FALSE);
	CFileListCreatorDlg::SortEnsureVisible_Func(); //�ǉ� 2012.06.01

	CFileListCreatorDlg::SetStrFormat_Func();

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}


	*pResult = 0;
}


void CFileListCreatorDlg::SortColumnDrawCaption(int workColumn, BOOL SortFLG){

	LVCOLUMN    lvc;//�ύX2011.05.13
    int         i;

	TCHAR	caption[][32] = {_T("�d��No."), _T("No."), _T("�t�@�C���p�X"), _T("�t�@�C����"),_T("�o�C�g"), _T("���o�C�g"),_T("�C����"),_T("�C������"),_T("���l��"),_T("�������")};
    const int   clmNum = sizeof caption /sizeof caption[0];
    int         err = 0;

	m_xcList.SetExtendedStyle( LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT |
    LVS_EX_GRIDLINES); //LVS_EX_CHECKBOXES | //�R�����g�� 2012.05.19

	//::SetFocus(::GetDlgItem(m_hWnd,IDC_LIST)); //�ǉ� 2012.05.24

    lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;    // �L���t���O
    for (i = 0; i < clmNum; i++)
    {
		lvc.iSubItem    = i;            // �T�u�A�C�e���ԍ�
        lvc.pszText     = caption[i];   // ���o���e�L�X�g

		if (i == workColumn) {
		//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������


			switch(workColumn){
			case 0:
				{
					//keyColumn = 0; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������ // �f�[�^�T�C�Y��4�ɂ���

					if (SortFLG == FALSE) { 
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�d���A�C�e�� ����)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("�d��No. ��")));
					}else{
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�d���A�C�e�� �~��)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("�d��No. ��")));
					}
				}
				break;


			case 1:
				{
					//keyColumn = 1; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������ // �f�[�^�T�C�Y��4�ɂ���

					if (SortFLG == FALSE) { 
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�A�� ����)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("No. ��")));
					}else{
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�A�� �~��)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("No. ��")));
					}
				}
				break;

			case 2:
				{
					//keyColumn = 2; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������

					if (SortFLG == FALSE) { 
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�t�@�C���p�X ����)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("�t�@�C���p�X ��")));
					}else{
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�t�@�C���p�X �~��)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("�t�@�C���p�X ��")));
					}
				}
				break;

			case 3:
				{
					//keyColumn = 3; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������

					if (SortFLG == FALSE) { 
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�t�@�C���� �~��)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("�t�@�C���� ��")));
					}else{
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�t�@�C���� ����)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("�t�@�C���� ��")));
					}
				}
				break;

			case 4:
				{
					//keyColumn = 5; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������ // �f�[�^�T�C�Y��4�ɂ���

					if (SortFLG == FALSE) { 
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�f�[�^�T�C�Y ����)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("�o�C�g ��")));
					}else{
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�f�[�^�T�C�Y �~��)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("�o�C�g ��")));
					}
				}
				break;
			case 5:
				{
					//keyColumn = 5; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������ // �f�[�^�T�C�Y��4�ɂ���

					if (SortFLG == FALSE) { 
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�f�[�^�T�C�Y ����)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("���o�C�g ��")));
					}else{
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�f�[�^�T�C�Y �~��)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("���o�C�g ��")));
					}
				}
				break;

			case 6:
				{
					//keyColumn = 7; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������

					if (SortFLG == FALSE) { 
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�C���� ����)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("�C���� ��")));
					}else{
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�C���� �~��)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("�C���� ��")));
					}
				}
				break;
			case 7:
				{
					//keyColumn = 7; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������

					if (SortFLG == FALSE) { 
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�C���� ����)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("�C������ ��")));
					}else{
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(�C���� �~��)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("�C������ ��")));
					}
				}
				break;
			case 8:
				{
					//keyColumn = 8; //keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������

					if (SortFLG == FALSE) { 
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(���l�� ����)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("���l�� ��")));
					}else{
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(���l�� �~��)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("���l�� ��")));
					}
				}
				break;
			case 9:
				{
					//keyColumn = 9;//keyColumn 2:�t���p�X 3:�t�@�C���� 5:�f�[�^�T�C�Y 7:�C������ 9:�������

					if (SortFLG == FALSE) { 
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(���� ����)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("������� ��")));
					}else{
						//CFileListCreatorDlg::StatusStringSet(_T("Sort �I���F(���� �~��)"),300,TRUE);
						lvc.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("������� ��")));
					}
				}
				break;
			}
		}

		lvc.cx = m_xcList.GetColumnWidth(i);
		m_xcList.SetColumn(i, &lvc);
		UpdateData(FALSE);
	}
	//RedrawWindow();
}

void CFileListCreatorDlg::OnLvnInsertitemList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	//SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24

	*pResult = 0;
}


void CFileListCreatorDlg::OnLvnDeleteallitemsList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24

	*pResult = 0;
}


void CFileListCreatorDlg::OnBnClickedBtnCellsizefix()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	RECT rect1;
	//RECT rect2;

	// ListView�̗̈�擾
	::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_LIST ), &rect1 );

	// �_�C�A���O�̃N���C�A���g���W�ɕϊ�
	this->ScreenToClient( &rect1 );

    LVCOLUMN    lvc;//�ύX2011.05.13
    int         i;
	TCHAR		caption[][32] = {_T("�d��No."), _T("No."), _T("�t�@�C���p�X"), _T("�t�@�C����"),_T("�o�C�g"), _T("���o�C�g"),_T("�C����"),_T("�C������"),_T("���l��"),_T("�������")};
    const int   clmNum = sizeof caption /sizeof caption[0];
    int         err = 0;

	int LIST_WIDTH;


	LIST_WIDTH = rect1.right - rect1.left - 25 ; //�X�N���[���o�[�̑傫���A�Q�T�Ƃ��Ĉ���


	int FileName_WIDTH_SUM;
	FileName_WIDTH_SUM = (80 + 80 + 0 + 470 + 80 + 0 + 110 + 0 + 110 + 0);

	int FilePath_WIDTH_SUM;
	FilePath_WIDTH_SUM = (80 + 80 + 600 + 0 + 80 + 0 + 110 + 0 + 110 + 0);

	int tempSum;
	tempSum = 0;
	//double Ratio_WIDTH;

	m_xcList.SetExtendedStyle( LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT |
    LVS_EX_GRIDLINES); //LVS_EX_CHECKBOXES | //�R�����g�� 2012.05.19

    lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;    // �L���t���O

	if (CellSizeFixMode == _T("Init")){
		CellSizeFixMode = _T("FileName");
	}else if (CellSizeFixMode == _T("FileName")){
		CellSizeFixMode = _T("FilePath");	
	}else if (CellSizeFixMode == _T("FilePath")){
		CellSizeFixMode = _T("FileName");
	}

	//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������

	if (CellSizeFixMode == _T("FileName")){
		for (i = 0; i < clmNum; i++)
		{
			lvc.iSubItem    = i;            // �T�u�A�C�e���ԍ�
			lvc.pszText     = caption[i];   // ���o���e�L�X�g
			switch(i){
				case 0:
					lvc.cx          =  LIST_WIDTH  * 80 / FileName_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 1:
					lvc.cx          = LIST_WIDTH  * 80 / FileName_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 2:
					lvc.cx          = LIST_WIDTH  * 0 / FileName_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 3:
					lvc.cx          = LIST_WIDTH  * 470 / FileName_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 4:
					lvc.cx          = LIST_WIDTH  * 80 / FileName_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 5:
					lvc.cx          = LIST_WIDTH  * 0 / FileName_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 6:
					lvc.cx          = LIST_WIDTH  * 110 / FileName_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 7:
					lvc.cx          = LIST_WIDTH  * 0 / FileName_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 8:
					lvc.cx          = LIST_WIDTH - tempSum;
					//lvc.cx          = LIST_WIDTH  * 110 / FileName_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 9:
					lvc.cx          = LIST_WIDTH  * 0 / FileName_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				default:
					MessageBox(_T("�s���ȗ�ł��B"));
					break;
			
			}
			m_xcList.SetColumn(i, &lvc);
			UpdateData(FALSE);
		}

		CFileListCreatorDlg::StatusStringSet(_T("�ʏ탂�[�h�ŃZ���̃T�C�Y�𒲐����܂���"),0,FALSE);

	}else if (CellSizeFixMode == _T("FilePath")){
		::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
		::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

		for (i = 0; i < clmNum; i++)
		{
			lvc.iSubItem    = i;            // �T�u�A�C�e���ԍ�
			lvc.pszText     = caption[i];   // ���o���e�L�X�g
			switch(i){
				case 0:
					lvc.cx          = LIST_WIDTH  * 80 / FilePath_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 1:
					lvc.cx          = LIST_WIDTH  * 80 / FilePath_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 2:
					lvc.cx          = LIST_WIDTH  * 600 / FilePath_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 3:
					lvc.cx          = LIST_WIDTH  * 0 / FilePath_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 4:
					lvc.cx          = LIST_WIDTH  * 80 / FilePath_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 5:
					lvc.cx          = LIST_WIDTH  * 0 / FilePath_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 6:
					lvc.cx          = LIST_WIDTH  * 110 / FilePath_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 7:
					lvc.cx          = LIST_WIDTH  * 0 / FilePath_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 8:
					lvc.cx          = LIST_WIDTH - tempSum;
					//lvc.cx          = LIST_WIDTH  * 110 / FilePath_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				case 9:
					lvc.cx          = LIST_WIDTH  * 0 / FilePath_WIDTH_SUM;          // ����
					tempSum += lvc.cx;
					break;
				default:
					MessageBox(_T("�s���ȗ�ł��B"));
					break;
			
			}
			m_xcList.SetColumn(i, &lvc);
			UpdateData(FALSE);
		}

		CFileListCreatorDlg::StatusStringSet(_T("�t���p�X���[�h�ŃZ���̃T�C�Y�𒲐����܂���\r\n(�p�X����ҏW����ɂ� Ctrl+F �Ńe�L�X�g�u�����ĉ�����)"),0,FALSE);
	}
	RedrawWindow(); //�ǉ� 2012.07.02
}


////http://www.sutosoft.com/oldroom/devdiary/old/dev200006.html
//BOOL CFileListCreatorDlg::SetClipboardText(LPCTSTR mes) 
//{ 

//} 

//http://rejoice.jugem.jp/?eid=57
//BOOL CFileListCreatorDlg::SetClipboardText(CString cs){

//}

//http://www.alpha-net.ne.jp/users2/uk413/vc/VCT_Clip.html
//http://www11.ocn.ne.jp/~ikalu/win32api/0014.html
BOOL CFileListCreatorDlg::SetClipboardText(LPCTSTR lpszText)
{
	//HWND  hWnd = ::GetDesktopWindow(); //�ǉ� 2012.05.26

	//if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
	//	CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
	//	return 0;
	//}

	// �N���b�v�{�[�h�Ƀe�L�X�g����������
    if(!::OpenClipboard(NULL)) { //�ύX NULL��hWnd
        //MessageBoxA(NULL,
        //    "���̃E�B���h�E�����ɃN���b�v�{�[�h���J���Ă���Ȃǂ̌����� Clipboard �֐��͎��s�܂����B",
        //    "error_message", MB_OK | MB_ICONERROR);

		StatusStringSet(_T("�G���[�F���̃E�B���h�E�����ɃN���b�v�{�[�h���J���Ă��܂�"),0,FALSE);
        return 0;
    }
    if(!::EmptyClipboard()) {
        // �N���b�v�{�[�h����ɂ��A�N���b�v�{�[�h���̃f�[�^�̃n���h�����������B
        // �����ɁA�N���b�v�{�[�h���J�����E�B���h�E�ɁA�N���b�v�{�[�h�̏��L����^����B
        //MessageBoxA(NULL,
        //    "���̃E�B���h�E�����ɃN���b�v�{�[�h���J���Ă���Ȃǂ̌����� Clipboard �֐��͎��s�܂����B",
        //    "error_message", MB_OK | MB_ICONERROR);
		StatusStringSet(_T("�G���[�F���̃E�B���h�E�����ɃN���b�v�{�[�h���J���Ă��܂�"),0,FALSE);
        return 0;
    };

    int length = lstrlenW(lpszText) * sizeof(TCHAR) + sizeof(TCHAR);
    HGLOBAL    hGlobal = GlobalAlloc(GHND | GMEM_DDESHARE, length);
    TCHAR* clipInText = (TCHAR*)GlobalLock(hGlobal);
    
	//lstrcpyW(clipInText, lpszText);
    memcpy(clipInText, lpszText, length);
    ::GlobalUnlock(hGlobal);

    if(!::SetClipboardData(CF_UNICODETEXT, clipInText)) {
        ::GlobalFree(hGlobal);
        ::CloseClipboard();
        return 0;
    }
    CloseClipboard();

	return 0;
}

//http://www.alpha-net.ne.jp/users2/uk413/vc/VCT_Clip.html
CString CFileListCreatorDlg::GetClipboardText(CString strText)
{
	//HWND  hWnd = ::GetDesktopWindow(); //�ǉ� 2012.05.26

	//CString strText;
	//strText.Empty();

	//if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
	//	CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
	//	return strText;
	//}

	// �N���b�v�{�[�h�̃I�[�v��
	if( !::OpenClipboard(NULL) )//�ύX NULL��hWnd
		return strText;

	// �N���b�v�{�[�h�Ƀe�L�X�g�f�[�^�������Ă��邩�𒲂ׂ�


	if( ::IsClipboardFormatAvailable(CF_UNICODETEXT)){
		// �N���b�v�{�[�h����f�[�^���擾���AstrText�փR�s�[
		HANDLE hMem = ::GetClipboardData(CF_UNICODETEXT);

		//if (hMem!=NULL){//�ǉ� 2012.05.26
			LPTSTR pMem = (LPTSTR)::GlobalLock(hMem);
			::lstrcpy((LPTSTR)(LPCTSTR)strText, pMem); //http://msdn.microsoft.com/ja-jp/library/ey142t48(v=vs.80).aspx //http://www.ruche-home.net/program/tips/unicode
			::GlobalUnlock(hMem);
			//::GlobalFree(hMem);//�ǉ� 2012.05.26
		//}
		::CloseClipboard();//�ǉ� 2012/05.30 //http://sgry.jp/blog/tag/programming/page/2/ //�K�v
		return strText;
	}else if( ::IsClipboardFormatAvailable(CF_TEXT)){
		// �N���b�v�{�[�h����f�[�^���擾���AstrText�փR�s�[
		HANDLE hMem = ::GetClipboardData(CF_TEXT);

		//if (hMem!=NULL){//�ǉ� 2012.05.26
			LPTSTR pMem = (LPTSTR)::GlobalLock(hMem);
			::lstrcpy((LPTSTR)(LPCTSTR)strText, pMem); //http://msdn.microsoft.com/ja-jp/library/ey142t48(v=vs.80).aspx //http://www.ruche-home.net/program/tips/unicode
			::GlobalUnlock(hMem);
			//::GlobalFree(hMem);//�ǉ� 2012.05.26
		//}
		::CloseClipboard();//�ǉ� 2012/05.30 //http://sgry.jp/blog/tag/programming/page/2/ //�K�v
		return strText;
	}else{
		::CloseClipboard();//�ǉ� 2012/05.26 //http://sgry.jp/blog/tag/programming/page/2/ //�K�v
		return strText;
	}




}

void CFileListCreatorDlg::OnMenuSetclipboardtext()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	//::SetFocus(::GetDlgItem(m_hWnd,IDC_LIST));

	//HWND hwnd = GetSafeHwnd();
	
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	//if(hwnd == GetDlgItem(IDC_LIST)->m_hWnd ){
		if ( m_xvChkEasySelect == TRUE || m_xvChkRedOnMode == TRUE || m_xvChkEditCellMode == TRUE) { //�ǉ� 2012.05.26
			int myResult;
			myResult = MessageBox(_T("EasySelect���[�h�E�ԐF�}�[�L���O���[�h�E�ҏW���[�h�ł́A�R�s�[�ł��܂���B�ʏ탂�[�h�ɕύX���܂����H") ,_T("���[�h�m�F"), MB_YESNOCANCEL );

			if (IDYES == myResult){
				CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_EasySelect);
				//�`�F�b�N���O��
				chkbox1->SetCheck(0);
				m_xvChkEasySelect = FALSE;

				CButton* chkbox2 = (CButton*)GetDlgItem(IDC_CHK_RedOnMode); //�ǉ� 2012.04.17
				//�`�F�b�N���O��
				chkbox2->SetCheck(0);
				m_xvChkRedOnMode = FALSE;

				CButton* chkbox3 = (CButton*)GetDlgItem(IDC_CHK_EditCellMode); //�ǉ� 2012.05.26
				//�`�F�b�N���O��
				chkbox3->SetCheck(0);
				m_xvChkEditCellMode = FALSE;

				m_xvStrEasySelectMode = _T(""); //�ǉ� 2012.05.26
				m_xvStrRedOnMode = _T("");
				m_xvStrEditCellMode = _T("�F�@�ʏ탂�[�h");

				::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE); //�ǉ�2012.05.30
				::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE); //�ǉ�2012.05.30

				UpdateData(FALSE);
				//RedrawWindow();
			}
			//return;
		}
	//}

	//::SetFocus(::GetDlgItem(m_hWnd,IDC_LIST));

	//if(hwnd == GetDlgItem(IDC_LIST)->m_hWnd ){
		if (m_xvChkEditCellMode == FALSE){
			if (LastSelectedRow!=-1 && LastSelectedColumn!=-1) {
				CString CopyText;
				CopyText= CFileListCreatorDlg::m_xcList.GetItemText(LastSelectedRow,LastSelectedColumn);
				CFileListCreatorDlg::SetClipboardText(const_cast<LPTSTR>(static_cast<LPCTSTR>(CopyText)));
				StatusStringSet(_T("���Ō�ɃN���b�N�����Z���̕������R�s�[���܂�����\r\n" + CopyText),0,FALSE);
			}
		}
	//}

}


void CFileListCreatorDlg::OnMenuGetclipboardtext()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	//::SetFocus(::GetDlgItem(m_hWnd,IDC_LIST));
	//HWND hwnd = GetSafeHwnd();

	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}

	//if(hwnd == GetDlgItem(IDC_LIST)->m_hWnd ){
		//MessageBox(_T("in"));
		if ( m_xvChkEasySelect == TRUE || m_xvChkRedOnMode == TRUE || m_xvChkEditCellMode == TRUE) { //�ǉ� 2012.05.26
			int myResult;
			myResult = MessageBox(_T("EasySelect���[�h�E�ԐF�}�[�L���O���[�h�E�ҏW���[�h�ł́A�y�[�X�g�ł��܂���B�ʏ탂�[�h�ɕύX���܂����H") ,_T("���[�h�m�F"), MB_YESNOCANCEL );

			if (IDYES == myResult){
				CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_EasySelect);
				//�`�F�b�N���O��
				chkbox1->SetCheck(0);
				m_xvChkEasySelect = FALSE;

				CButton* chkbox2 = (CButton*)GetDlgItem(IDC_CHK_RedOnMode); //�ǉ� 2012.04.17
				//�`�F�b�N���O��
				chkbox2->SetCheck(0);
				m_xvChkRedOnMode = FALSE;

				CButton* chkbox3 = (CButton*)GetDlgItem(IDC_CHK_EditCellMode); //�ǉ� 2012.05.26
				//�`�F�b�N���O��
				chkbox3->SetCheck(0);
				m_xvChkEditCellMode = FALSE;

				m_xvStrEasySelectMode = _T(""); //�ǉ� 2012.05.26
				m_xvStrRedOnMode = _T("");
				m_xvStrEditCellMode = _T("�F�@�ʏ탂�[�h");

				::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE); //�ǉ�2012.05.30
				::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE); //�ǉ�2012.05.30

				UpdateData(FALSE);
				//RedrawWindow();
			}
			//return;
		}
	//}
	int err;

	UpdateData();
	lvi.mask = LVIF_TEXT; // | LVCF_SUBITEM�����Ă͂Ȃ�Ȃ� //�d�v 2012.05.31
//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������

	//if(hwnd == GetDlgItem(IDC_LIST)->m_hWnd ){
	if (m_xvChkEditCellMode == FALSE){
		if (LastSelectedRow!=-1 && LastSelectedColumn!=-1) {
			if (LastSelectedColumn == 3 || LastSelectedColumn == 8){
				if(m_xcList.GetSelectedCount()>=1){

					LastPrevItemCount = m_xcList.GetItemCount();
					CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

					int index = -1;

					while ((index = m_xcList.GetNextItem
							(index, LVNI_ALL | LVNI_SELECTED)) != -1){
							CString CopyText;
							CopyText= CFileListCreatorDlg::m_xcList.GetItemText(LastSelectedRow,LastSelectedColumn); //�ǉ� 2012.05.26
							CopyText= CFileListCreatorDlg::GetClipboardText(CopyText);

							lvi.iItem = index;
							//lvi.lParam = m_id++;        // ID
							lvi.iSubItem = LastSelectedColumn;
							lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(CopyText));

							if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
							UpdateData(FALSE);
					}

					if (LastSelectedColumn == 3){
						StatusStringSet(_T("�t�@�C������ �Ƀf�[�^��\��t���܂���"),0,TRUE);
					}
					if (LastSelectedColumn == 8){
						StatusStringSet(_T("���l�� �Ƀf�[�^��\��t���܂���"),0,TRUE);
					}
				}
			}else{
				StatusStringSet(_T("�t�@�C���� �� ���l�� �ɂ̂� �f�[�^��\��t���鎖���ł��܂�"),300,TRUE);
				return;
			}
		}

	}

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	if (ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		SetWindowText(_T("FileListCreator (*)"));
		SortColumnDrawCaption(-1,FALSE); //�ǉ� 2012.05.24
	}
}


void CFileListCreatorDlg::DeleteSelectedCells_Func(){
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ�2011.10.08

	if (LastSelectedColumn!=3 && LastSelectedColumn!=8){
		MessageBox(_T("�u�t�@�C�����v�u���l���v�̂ݍ폜�ł��܂��B�����Z�����폜�\�ł��B"),_T("�폜�ΏۊO�ʒm"),MB_OK);
		return;
	}

	LastPrevItemCount = m_xcList.GetItemCount();
	CFileListCreatorDlg::push_back_Func(LastPrevItemCount,_T("prevData")); //�ύX 2012.05.02

    int        index = -1;
    CString    str;

	int myCnt = 0;

    while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
        (index, LVNI_ALL | LVNI_SELECTED)) != -1)
    {
		myCnt++;
    }
	

	int err;

	int myResult;
	CString tempCnt;

	if ( LastSelectedColumn == 3 ){
		myResult = MessageBox(_T("���ݑI������Ă���Z�� (�t�@�C������) ���폜���܂����H"),_T("Deletion range confirmation"),MB_YESNOCANCEL);
	}

	if ( LastSelectedColumn == 8 ){
		myResult = MessageBox(_T("���ݑI������Ă���Z�� (���l��) ���폜���܂����H"),_T("Deletion range confirmation"),MB_YESNOCANCEL);
	}

	if(myResult == IDYES){
		index = -1;
		while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
			(index, LVNI_ALL | LVNI_SELECTED)) != -1)
		{

			lvi.iItem = index;
			//lvi.lParam = m_id++;        // ID
			lvi.iSubItem = LastSelectedColumn;
			lvi.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(_T("")));

			if (!CFileListCreatorDlg::m_xcList.SetItem(&lvi)) err = 1;
			UpdateData(FALSE);
		}

		tempCnt = _T("");

		if(myCnt>=1){ //�ǉ� 2012,06.14
			tempCnt.Format(_T("%d"),myCnt);
			tempCnt=tempCnt + _T(" ���̃A�C�e�����폜���܂���");
		}else{
			tempCnt=_T("�A�C�e�����I������Ă��Ȃ����߁A�A�C�e�����폜�ł��܂���");
		}
		CFileListCreatorDlg::StatusStringSet(tempCnt,300,TRUE);

		tempCnt = "";

		tempCnt.Format(_T("%d"),CFileListCreatorDlg::m_xcList.GetItemCount());
		tempCnt=tempCnt + _T(" items");

		m_xvStCount = const_cast<LPTSTR>(static_cast<LPCTSTR>(tempCnt));
		//CFileListCreatorDlg::m_xcList.EnsureVisible(index-1, FALSE);
		UpdateData(FALSE);
	}

	if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1 || MiniWindowFLG == FALSE){
		m_xcStaticString.ShowWindow(SW_HIDE);
	}else{
		m_xcStaticString.ShowWindow(SW_SHOW);
	}

	CFileListCreatorDlg::Total_Bytes_Bold();
	CFileListCreatorDlg::Total_Bytes_Func();
	CFileListCreatorDlg::ItemCount_Func(TRUE);

	ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
		m_Dlg->SetWindowText(_T("FileListCreator (*)"));
	}

	::SetFocus(::GetDlgItem(m_hWnd,IDC_LIST));
}


void CFileListCreatorDlg::OnMenuDeletecell()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if(CFileListCreatorDlg::m_xcList.GetItemCount() < 1) {
		CFileListCreatorDlg::StatusStringSet(_T("�f�[�^���Ȃ��̂ŉ����s���܂���ł���"),300,TRUE);
		return;
	}else{
		CFileListCreatorDlg::DeleteSelectedCells_Func();
	}
}

void CFileListCreatorDlg::SortEnsureVisible_Func()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	CFileListCreatorDlg::m_xcList.EnsureVisible(0, FALSE);

	//LVITEM	   lvi;
	int		  index = 0;

	index = -1;
	while ((index = CFileListCreatorDlg::m_xcList.GetNextItem
		(index, LVNI_ALL | LVNI_SELECTED)) != -1)
	{

		m_xcList.EnsureVisible(index, FALSE);

		//m_xcList.SetItemState(index,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
		//LVIS_FOCUSED | LVIS_SELECTED,    // ���
		//LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N
		UpdateData(FALSE);
	}
	//RedrawWindow(); //�ǉ� 2012.04.05 //XP�΍�
}

void CFileListCreatorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B


	//RECT CurRect;

	::GetWindowRect( m_hWnd, &CurRect );
	this->ScreenToClient( &CurRect );

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_LIST),
		HWND_TOP,CurRect.left + 20,
			initListSize.top,
		CurRect.right-CurRect.left - 20*2,
		initListSize.bottom-initListSize.top + (CurRect.bottom - initWindowSize.bottom) ,NULL);

	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_Item),SW_HIDE);//�ǉ� 2012.06.28
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_HIDE);//�ǉ� 2012.06.28

	//CFileListCreatorDlg::StatusStringSet(_T("�ʏ�̃��[�h�ł� (�Z�����̃e�L�X�g�͕ҏW�ł��܂���)"),300,TRUE);
	//m_xvStrEditCellMode = _T("�F�@�ʏ탂�[�h");
	//UpdateData(FALSE);


	RECT workRect;

	workRect = rectSTATIC_DRAG_ON_ME;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_STATIC_DRAG_ON_ME),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom)/2,
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	if(CurRect.bottom <= workRect.bottom + 40){
		::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_DRAG_ON_ME),SW_HIDE);
	}


	workRect = rectBTN_Import;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_BTN_Import),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	workRect = rectBTN_Export;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_BTN_Export),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	workRect = rectBTN_Restore;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_BTN_Restore),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	workRect = rectBTN_Sort;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_BTN_Sort),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);


	workRect = rectBTN_PackageSearch;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_BTN_PackageSearch),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);


	workRect = rectBTN_StepSearch;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_BTN_StepSearch),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	workRect = rectBTN_CurrentDirectoryOpen;

	::SetWindowPos(::GetDlgItem(m_hWnd,ID_BTN_CurrentDirectoryOpen),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);


	workRect = rectBTN_Clear;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_BTN_Clear),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);


	workRect = rectCHK_RedOnMode;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_CHK_RedOnMode),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	workRect = rectCHK_EasySelect;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_CHK_EasySelect),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	workRect = rectCHK_EditCellMode;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_CHK_EditCellMode),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);


	workRect = rectSTATIC_RedOnMode;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_STATIC_RedOnMode),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	workRect = rectSTATIC_EasySelectMode;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_STATIC_EasySelectMode),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	workRect =rectSTATIC_EditCellMode;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_STATIC_EditCellMode),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);


	workRect = rectSTATIC_RedOnModeFrame;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_STATIC_RedOnModeFrame),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	workRect = rectSTATIC_EasySelectFrame;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_STATIC_EasySelectFrame),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	workRect = rectSTATIC_EditCellModeFrame;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_STATIC_EditCellModeFrame),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);


	workRect = rectCHK_Search_SubFolder;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_CHK_Search_SubFolder),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	workRect = rectCHK_AutoSave;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_CHK_AutoSave),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	workRect = rectBTN_CellSizeFix;

	::SetWindowPos(::GetDlgItem(m_hWnd,ID_BTN_CellSizeFix),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);


	workRect = rectBTN_SetSEQ_NUM;

	::SetWindowPos(::GetDlgItem(m_hWnd,ID_BTN_SetSEQ_NUM),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	workRect = rectBTN_NoSaveQuit;

	::SetWindowPos(::GetDlgItem(m_hWnd,ID_BTN_NoSaveQuit),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	workRect = rectBTN_Quit;

	::SetWindowPos(::GetDlgItem(m_hWnd,ID_BTN_Quit),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);


	workRect = rectBTN_MiniWindow;

	::SetWindowPos(::GetDlgItem(m_hWnd,ID_BTN_MiniWindow),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	workRect = rectBTN_RedrawWindow;

	::SetWindowPos(::GetDlgItem(m_hWnd,ID_BTN_RedrawWindow),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);
	

	workRect = rectCHK_UseUNDO;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_CHK_UseUNDO),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom),
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);


	RedrawWindow();
	//CFileListCreatorDlg::StatusStringSet(_T("�uCellSizeFix�v�{�^���ŃZ�����𒲐����鎖���ł��܂�\r\n(�����x�� �t���p�X�^�t�@�C���� �̃��[�h������ւ��܂�)"),0,FALSE);

	//::ShowWindow(::GetDlgItem(m_hWnd,IDC_LIST),SW_SHOW);
	//GetDlgItem( IDC_LIST )->MoveWindow( &rect1, TRUE );
}


void CFileListCreatorDlg::OnBnClickedBtnMiniwindow()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (MiniWindowFLG == TRUE){
		m_xcStaticString.ShowWindow(SW_HIDE);

		m_Dlg->SetWindowPos(NULL,initWindowSize2.left,
			initWindowSize2.top,
			 (initWindowSize2.right-initWindowSize2.left) / 3,
			 (initWindowSize2.bottom-initWindowSize2.top )  * 2 / 3 ,NULL);
		MiniWindowFLG = FALSE;

		CString myStr;
		myStr = _T("Full-Window");
		((CButton*)GetDlgItem(ID_BTN_MiniWindow))->SetWindowText(myStr);
	}else{
		m_Dlg->SetWindowPos(NULL,initWindowSize2.left,
			initWindowSize2.top,
			 (initWindowSize2.right-initWindowSize2.left),
			 (initWindowSize2.bottom-initWindowSize2.top ),NULL);
		MiniWindowFLG = TRUE;

		CString myStr;
		myStr = _T("Mini-Window");
		((CButton*)GetDlgItem(ID_BTN_MiniWindow))->SetWindowText(myStr);

		if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1 || MiniWindowFLG == FALSE){
			m_xcStaticString.ShowWindow(SW_HIDE);
		}else{
			m_xcStaticString.ShowWindow(SW_SHOW);
		}
	}
}


void CFileListCreatorDlg::OnBnClickedBtnRedrawwindow()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	Total_Bytes_Bold();
	Total_Bytes_Func();
	ItemCount_Func(FALSE);

	if(CFileListCreatorDlg::m_xcList.GetItemCount() >= 1 || MiniWindowFLG == FALSE){
		m_xcStaticString.ShowWindow(SW_HIDE);
	}else{
		m_xcStaticString.ShowWindow(SW_SHOW);
	}

	RECT workRect;

	workRect = rectSTATIC_DRAG_ON_ME;

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_STATIC_DRAG_ON_ME),
		HWND_TOP,workRect.left,
			workRect.top + (CurRect.bottom - initWindowSize.bottom)/2,
		workRect.right-workRect.left,
		workRect.bottom-workRect.top,NULL);

	if(CurRect.bottom <= workRect.bottom + 40){
		::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_DRAG_ON_ME),SW_HIDE);
	}

	CFileListCreatorDlg::StatusStringSet(_T("�E�B���h�E�S�̂��ĕ`�悵�܂���"),0,TRUE);
	RedrawWindow();
}


void CFileListCreatorDlg::OnBnClickedChkUseundo()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

	//http://www.ujasiri.com/prglib/vc/compo/vc_chkboxsap.html
	CButton* chkbox1 = (CButton*)GetDlgItem(IDC_CHK_UseUNDO);
	
	if(chkbox1->GetCheck()){
		m_xvChkUseUNDO = TRUE;
		//chkbox1->SetCheck(0);
	}else{
		m_xvChkUseUNDO = FALSE;
		//chkbox1->SetCheck(1);
	}
}

void CFileListCreatorDlg::SpeakFunc(CString myText)
{

	_wsetlocale(LC_ALL, L"Japanese");

	//if (SelectedLanguage == _T("Japanese")) {

	//}else if (SelectedLanguage == _T("English")){

	//}

	CStdioFile    stdFile;
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

		//// �t���p�X�𕪉�
		//TCHAR szDir[_MAX_DIR];
		//TCHAR szDrive[_MAX_DRIVE];
		//TCHAR szFName[_MAX_FNAME];
		//TCHAR szExt[_MAX_EXT];
		//_splitpath(szPath,szDrive,szDir,szFName,szExt);
		//
		//// �t�H���_�A�t�@�C�����擾
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

		if (!stdFile.Open(CurDir + _T("\\SpeakText.vbs"), 
			CFile::modeReadWrite | CFile::shareDenyNone | 
			CFile::modeCreate | CFile::typeText)) err = 1;// | CFile::modeNoTruncate | CFile::typeText


		// (2)��������
		if (!err)
		{
			wstr = _T("CreateObject(\"SAPI.SpVoice\").Speak \"") +  myText + _T("\"");
			
			//CreateObject("SAPI.SpVoice").Speak "�������������蕶"

			TRY {stdFile.WriteString(wstr);}
			CATCH (CFileException, eP) {err = 1;}
			END_CATCH
		}


		// (6)�N���[�Y(�����I)
		stdFile.Close();
		
		if (!err)
		{
			ShellExecute( NULL, _T("open"), _T("C:\\WINDOWS\\System32\\WScript.exe"), _T("\"") + CurDir + _T("\\SpeakText.vbs") + _T("\"") , NULL , SW_SHOWNORMAL );
		}
	}

	_wsetlocale(LC_ALL, L"");
}


BOOL CFileListCreatorDlg::iTunesPlayList_Import_Func(CString FullPath,CString mySwitch)
{
	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return FALSE;
	}

	
	FullPath.Replace(_T("\\"),_T("\\\\"));


	//if ( PathFileExists( FullPath ) ){

	//}else{
	//	//return FALSE;
	//}

	CString       wstr, rstr;
	int           err = 0;

	// (1)�ǂݏ����p�ɃI�[�v��
	if (!err)
	{
		if ( PathFileExists( FullPath ) ){
			FILE *fp;
			_tfopen_s(&fp,FullPath, _T("r, ccs=UNICODE"));
			CStdioFile stdFile1(fp);

			err = 0;
			int k;
			k = 0;
			while (!err) {
				MSG msg; //�ǉ� 2011.10.22

				if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) ) { // ���b�Z�[�W���擾�����ꍇ0�ȊO���Ԃ�
					if(msg.hwnd != GetDlgItem(IDC_EDIT_Item)->m_hWnd ){
						if (msg.wParam == VK_ESCAPE){
							ESCAPE_FLG = TRUE;
							break; //�I���B���b�Z�[�W���[�v�𔲂���B
						}
					}
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					//continue;
				}

				if (stdFile1.ReadString(rstr) == FALSE) err = 1;

				if (!err && (k==0)){
					CString tempStr;
					tempStr = _T("");
					tempStr = rstr.Mid(myReverseFind(rstr, _T("\t"),rstr.GetLength()-1) + 1);

					//MessageBox(tempStr,_T("TRACE"), MB_YESNOCANCEL );

					if ( mySwitch == _T("CheckMusicListFile") ){
						if ( tempStr != _T("�ꏊ") ){
							stdFile1.Close();
							fclose(fp);
							return FALSE;
						}else{
							stdFile1.Close();
							fclose(fp);
							return TRUE;
						}
					}

				}

				if (!err && (k>=1)){
					if ( mySwitch == _T("ExpandMusicListFile") ){
						CString tempPath;
						tempPath = _T("");
						tempPath = rstr.Mid(myReverseFind(rstr, _T("\t"),rstr.GetLength()-1) + 1);

						if ( PathFileExists( tempPath ) ){
							ListInsertItem(tempPath);
						}
					}
				}

				k++;
			}

			// (6)�N���[�Y(�����I)
			stdFile1.Close();
			fclose(fp);
		}
	}
	return TRUE;
}

//void CFileListCreatorDlg::OnLvnEndScrollList(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// ���̋@�\�� Internet Explorer 5.5 ������ȍ~�̃o�[�W������K�v�Ƃ��܂��B
//	// �V���{�� _WIN32_IE �� >= 0x0560 �ɂȂ�Ȃ���΂Ȃ�܂���B
//	LPNMLVSCROLL pStateChanged = reinterpret_cast<LPNMLVSCROLL>(pNMHDR);
//	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
//	*pResult = 0;
//}


void CFileListCreatorDlg::OnMenuCancel()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	//OnCancel();

	//::SetFocus(::GetDlgItem(m_hWnd,IDC_LIST));

	CFileListCreatorDlg::StatusStringSet(_T("�E�N���b�N���j���[���L�����Z�����܂���"),0,TRUE);

	//PostMessage(WM_KEYDOWN, VK_ESCAPE, 0);;

	//// �E�B���h�E���烁�j���[�o�[���폜
	//SetMenu( IDR_MENU1, NULL );
	//// ���j���[�o�[���\�[�X��j������
	//DestroyMenu( hMenu );

	//PostMessage(WM_NULL); // ���̏������Y�ꂸ�ɁI
    return;
}
