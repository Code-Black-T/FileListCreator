#include "StdAfx.h"


//�ǉ���
#include "FileListCreator.h"

#include "FileListCreatorDlg.h"

#include <ctype.h>//�ǉ�
#include "afxwin.h"//�ǉ�

#include "FileSpecsDlg.h"
#include "afxdialogex.h"
//�ǉ���

#include "MylistCtrl.h"

CMylistCtrl::CMylistCtrl(void)
{
	//LastClickItem=-1;
}


CMylistCtrl::~CMylistCtrl(void)
{
}


//static HFONT CreateMyFont(int nBold)//�ǉ� 2011.05.13
// {
//	//�f�B�t�H���g�t�H���g���Q�b�g����
// HFONT hFontDef = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
//
//	//�t�H���g�̏ڍׂ��󂯎��\���̃o�b�t�@
// LOGFONT lf;
//
//	//�t�H���g�n���h������ڍׂ��󂯎��
// GetObject(hFontDef, sizeof(lf), &lf);
//
// //���̃����o�Ƀt�H���g�̑�����ݒ肷��
// lf.lfWeight = nBold;
//
// //�t�H���g�̍쐬
// return CreateFontIndirect(&lf);
// }

void CMylistCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct){

	// TODO:  �w�肳�ꂽ���ڂ�`�悷�邽�߂̃R�[�h��ǉ����Ă��������B
	//�ǉ� 2011.05.13


	//http://rararahp.cool.ne.jp/cgi-bin/lng/vc/vclng.cgi?print+201103/11030005.txt

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->g_NoDrawFLG == TRUE){
		return;
	}

	//��http://dejibouzu.com/page/2/�@��


	CDC*		pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect		rect;
	rect = ( CRect)lpDrawItemStruct->rcItem;

	int			nItem = lpDrawItemStruct->itemID;
	TCHAR		szBuff[MAX_PATH];
	CRect		nRect;
	int			nCnt = 0;

	int			nIndentPix;
	CHeaderCtrl *Head = GetHeaderCtrl();
	int			nMax = Head->GetItemCount();

	//�������
	CString FormatDataStr;

	while( nMax > nCnt )
	{
		nIndentPix = 0;

		//�A�C�e���擾�̂��߂̐ݒ�
		LVITEM lvItem;
		lvItem.mask			= LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_INDENT; //�ǉ� 2012.05.16 LVCF_SUBITEM�ǉ� ;//�ǉ����Ă��Ӗ����Ȃ�����2011.05.14	| LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
		lvItem.iItem		= nItem;
		lvItem.iSubItem		= nCnt;
		lvItem.pszText		= szBuff;
		lvItem.cchTextMax	= sizeof(szBuff);
		lvItem.stateMask	= LVIS_FOCUSED | LVIS_SELECTED;//-1�� LVIS_SELECTED�ɕύX2011.05.14

		//m_Dlg->m_xcList.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

		if( m_Dlg->m_xcList.GetItem(&lvItem) == TRUE ){
			if( nCnt == 0){
				//�A�C�e���̏ꍇ
				m_Dlg->m_xcList.GetItemRect( nItem, &nRect, LVIR_BOUNDS);
				//m_Dlg->m_xcList.SetItemData(nItem,11);
			}else{
				//�T�u�A�C�e���̏ꍇ
				m_Dlg->m_xcList.GetSubItemRect( nItem, nCnt, LVIR_BOUNDS, nRect);
			}

			//if ( m_phbrBkColor ){
				//�J���[�e�[�u���Ƀu���V���쐬����Ă���Ȃ�w�i��`��
				//if ( m_phbrBkColor[ nCnt * GetItemCount()  + nItem] )
				//{
					//�A�C�e���̏ꍇ �`��ӏ����A�C�e�������݂̂ɏC��
					if( nCnt == 0 ){
						nRect.right = m_Dlg->m_xcList.GetColumnWidth( 0 );
					//}else if ( nCnt == 3 || nCnt == 8) { //�ǉ� 2011.10.09
					//	nRect.right = m_Dlg->m_xcList.GetColumnWidth( nCnt );
					}
					//FillRect( pDC->m_hDC, &nRect, m_phbrBkColor[ nCnt * GetItemCount()  + nItem ] );
				//}
			//}

//http://www.crimson-systems.com/tips/t003.htm
//http://oshiete.goo.ne.jp/qa/6645218.html
//http://www.tcn.zaq.ne.jp/zxcvbnm/projectc/vcpp/colortextcombo.htm

//===============�����Ē���������=======================

CFont fontBold, *pfontOld;
 LOGFONT lf;
  pDC->GetCurrentFont()->GetLogFont(&lf);
    // �`�擮�삪�S�̂̍ĕ`��������́A
    // �I����Ԃ��ω������ꍇ
  
  //http://lhsp.s206.xrea.com/misc/ownerdraw.html
  //http://msdn.microsoft.com/ja-jp/library/92fhtw0f(v=VS.100).aspx



		if( lpDrawItemStruct->itemAction & ( ODA_DRAWENTIRE | ODA_SELECT )) {
				// �R���g���[���̏�Ԃ��I�����ꂽ��Ԃ̏ꍇ

			if( lpDrawItemStruct->itemState & ODS_SELECTED ){
					 // �I������Ă���ꍇ�̕`��

				int FormatDataNum;

				if(nCnt == 0){
					FormatDataNum = m_Dlg->m_xcList.GetItemData(nItem);
					pDC->SetBkMode(OPAQUE);
					//pDC->SetBkColor(RGB(255,255,255));
					if(FormatDataNum == 11){
						//FormatDataStr = _T("NORMAL,BLACK,");
						lf.lfWeight = FW_NORMAL;
						pDC->SetTextColor(RGB(0,0,0));
					}

					if(FormatDataNum == 12){
						//FormatDataStr = _T("BOLD,BLACK,");
						lf.lfWeight = FW_BOLD;
						pDC->SetTextColor(RGB(0,0,0));
					}

					if(FormatDataNum == 21){
						//FormatDataStr = _T("NORMAL,RED,");
						lf.lfWeight = FW_NORMAL;
						pDC->SetTextColor(RGB(255,0,0));/*�����̐F*/
					}

					if(FormatDataNum == 22){
						//FormatDataStr = _T("BOLD,RED,");
						lf.lfWeight = FW_BOLD;
						pDC->SetTextColor(RGB(255,0,0));/*�����̐F*/
					}

					UpdateData(FALSE);
				}

				if( nCnt == 0){
					if(m_Dlg->m_xvChkEasySelect == TRUE){
						if(lf.lfWeight == FW_BOLD){
							if(m_Dlg->m_xcList.GetSelectedCount()==1){
								if (m_Dlg->SelectALLFLG  == FALSE ){
								//if(m_Dlg->NotInversion == FALSE){ //�t�@�C�����E���l����ҏW���鎞�́A���]���Ȃ�
									lf.lfWeight = FW_NORMAL;
								//}
								}
							}
						}else{
							lf.lfWeight = FW_BOLD;
						}

						m_Dlg->m_xcList.SetItemState(nItem,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
						!LVIS_FOCUSED | !LVIS_SELECTED,    // ���
						LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N

						m_Dlg->ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

						if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
							m_Dlg->SetWindowText(_T("FileListCreator (*)"));
						}
					}
				}

				//pDC->FillSolidRect(&lpDrawItemStruct->rcItem,RGB(0,0,255));/*�����̌��̐F�i�w�i�ƈꏏ�ɂ��Ƃ��ׂ��j*/
				pDC->SetBkMode(OPAQUE);
				pDC->SetBkColor(RGB(200,200,200));//�I�����ꂽ���̔w�i�F
				//pDC->SetTextColor(RGB(255,255,255));/*�����̐F*/

				if( nCnt == 0){   //�ύX 2012.04.17
					if(m_Dlg->m_xvChkRedOnMode == TRUE){
						if(pDC->GetTextColor() == RGB(255,0,0)){
							if(m_Dlg->m_xcList.GetSelectedCount()==1){
								if (m_Dlg->SelectALLFLG  == FALSE ){
								//if(m_Dlg->NotInversion == FALSE){ //�t�@�C�����E���l����ҏW���鎞�́A���]���Ȃ�
									pDC->SetTextColor(RGB(0,0,0));/*�����̐F*/
								//}
								}
							}
						}else{
							pDC->SetTextColor(RGB(255,0,0));/*�����̐F*/
						}
						m_Dlg->m_xcList.SetItemState(nItem,     // �t�H�[�J�X���I����Ԃɂ������A�C�e���̃C���f�b�N�X
						!LVIS_FOCUSED | !LVIS_SELECTED,    // ���
						LVIS_FOCUSED | LVIS_SELECTED);    // �}�X�N

						m_Dlg->ListDataNoChange_FLG = FALSE;//�ǉ� 2012.05.13

						if (m_Dlg->ListDataNoChange_FLG == FALSE){  //�ǉ� 2012.05.13
							m_Dlg->SetWindowText(_T("FileListCreator (*)"));
						}
					}
				}

				if( nCnt == 0){
					FormatDataNum = 0;

					if (lf.lfWeight == FW_NORMAL){
						FormatDataNum = FormatDataNum + 1;
					}else if(lf.lfWeight == FW_BOLD){
						FormatDataNum = FormatDataNum + 2;
					}else{
						FormatDataNum = FormatDataNum + 0;
					}

					if(pDC->GetTextColor()==RGB(0,0,0)){
						FormatDataNum = FormatDataNum + 10;
					}else if (pDC->GetTextColor()==RGB(255,0,0)){
						FormatDataNum = FormatDataNum + 20;
					}else{
						FormatDataNum = FormatDataNum + 0;
					}

					m_Dlg->m_xcList.SetItemData(nItem,FormatDataNum);

					if (m_Dlg->SelectALLFLG == FALSE){
						m_Dlg->Total_Bytes_Bold();
						m_Dlg->Total_Bytes_Func();
						m_Dlg->ItemCount_Func(FALSE);
					}
					m_Dlg->LastSelectedRow  = nItem; //�ǉ� 2012.06.01
					//m_Dlg->LastSelectedColumn = nCnt; //�c���Ȃ�

				//===================================================
				}

					//0:�t�@�C���d�����ʃi���o�[ 1:�ʂ��ԍ� 2:�t���p�X 3:�t�@�C���� 4:�����悻�̃f�[�^�T�C�Y 5:�f�[�^�T�C�Y 6:�C���� 7:�C������ 8:���l�� 9:�������
				//m_Dlg->LastSelectedRow  = nItem;
				//if(nCnt==3 || nCnt==8){


			}else{ // �I������Ă��Ȃ�(�H)�ꍇ�̕`��
				//if( lpDrawItemStruct->itemState & ODS_FOCUS ){
				//	m_Dlg->LastSelectedColumn = nItem; //�c��
				//}

				int FormatDataNum = m_Dlg->m_xcList.GetItemData(nItem);
				pDC->SetBkMode(OPAQUE);
				pDC->SetBkColor(RGB(255,255,255));
				if(FormatDataNum == 11){
					//FormatDataStr = _T("NORMAL,BLACK,");
					lf.lfWeight = FW_NORMAL;
					pDC->SetTextColor(RGB(0,0,0));
				}

				if(FormatDataNum == 12){
					//FormatDataStr = _T("BOLD,BLACK,");
					lf.lfWeight = FW_BOLD;
					pDC->SetTextColor(RGB(0,0,0));
				}

				if(FormatDataNum == 21){
					//FormatDataStr = _T("NORMAL,RED,");
					lf.lfWeight = FW_NORMAL;
					pDC->SetTextColor(RGB(255,0,0));/*�����̐F*/
				}

				if(FormatDataNum == 22){
					//FormatDataStr = _T("BOLD,RED,");
					lf.lfWeight = FW_BOLD;
					pDC->SetTextColor(RGB(255,0,0));/*�����̐F*/
				}

				UpdateData(FALSE);

			}

		}else{// �I������Ă��Ȃ��ꍇ�̕`��

				int FormatDataNum = m_Dlg->m_xcList.GetItemData(nItem);
				pDC->SetBkMode(OPAQUE);
				//pDC->SetBkColor(RGB(255,255,255));
				if(FormatDataNum == 11){
					//FormatDataStr = _T("NORMAL,BLACK,");
					lf.lfWeight = FW_NORMAL;
					pDC->SetTextColor(RGB(0,0,0));
				}

				if(FormatDataNum == 12){
					//FormatDataStr = _T("BOLD,BLACK,");
					lf.lfWeight = FW_BOLD;
					pDC->SetTextColor(RGB(0,0,0));
				}

				if(FormatDataNum == 21){
					//FormatDataStr = _T("NORMAL,RED,");
					lf.lfWeight = FW_NORMAL;
					pDC->SetTextColor(RGB(255,0,0));/*�����̐F*/
				}

				if(FormatDataNum == 22){
					//FormatDataStr = _T("BOLD,RED,");
					lf.lfWeight = FW_BOLD;
					pDC->SetTextColor(RGB(255,0,0));/*�����̐F*/
				}



				UpdateData(FALSE);
		}

  	//http://msdn.microsoft.com/ja-jp/library/936147y4(v=VS.100).aspx
	// Set the data of each item to be equal to its index.
	//for (int i = 0; i < m_myListCtrl.GetItemCount(); i++)
	//{
	//	m_myListCtrl.SetItemData(i, i);
	//}


	//http://grayhole.blogspot.com/2010_08_01_archive.html
	//http://rararahp.cool.ne.jp/cgi-bin/lng/vc/vclng.cgi?print+200408/04080071.txt
	//http://support.microsoft.com/kb/250614/ja
	//http://msdn.microsoft.com/ja-jp/library/936147y4(v=VS.100).aspx

 fontBold.CreateFontIndirect(&lf);

 //pfontOld =
(CFont*)pDC->SelectObject(&fontBold);

//pDC->SelectObject(pfontOld);

 
	//CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	//CFont *pFont = pDC->GetCurrentFont();

	////http://msdn.microsoft.com/ja-jp/library/zhcs623h.aspx



//==================================================================
			//�e�L�X�g�`��

			int FormatDataNum = m_Dlg->m_xcList.GetItemData(nItem);

			pDC->SetBkMode(OPAQUE);
			//pDC->SetBkColor(RGB(255,255,255));
			if(FormatDataNum == 11){
				//FormatDataStr = _T("NORMAL,BLACK,");
				lf.lfWeight = FW_NORMAL;
				pDC->SetTextColor(RGB(0,0,0));
			}

			if(FormatDataNum == 12){
				//FormatDataStr = _T("BOLD,BLACK,");
				lf.lfWeight = FW_BOLD;
				pDC->SetTextColor(RGB(0,0,0));
			}

			if(FormatDataNum == 21){
				//FormatDataStr = _T("NORMAL,RED,");
				lf.lfWeight = FW_NORMAL;
				pDC->SetTextColor(RGB(255,0,0));/*�����̐F*/
			}

			if(FormatDataNum == 22){
				//FormatDataStr = _T("BOLD,RED,");
				lf.lfWeight = FW_BOLD;
				pDC->SetTextColor(RGB(255,0,0));/*�����̐F*/
			}



			if( nCnt == 9){  //�R�����g�� 2012.05.15
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

				lvItem.iItem = nItem;
				lvItem.iSubItem = 9;
				lvItem.pszText = const_cast<LPTSTR>(static_cast<LPCTSTR>(FormatDataStr));

				m_Dlg->m_xcList.SetItem(&lvItem);
				//UpdateData(FALSE);
				UpdateWindow();
			}


				CString outText;
				outText = lvItem.pszText;

				nRect.left += 10;//�ύX2011.05.14
				nRect.top +=2;//�ύX2011.05.14

				//pDC->DrawText(outText, &nRect, DT_VCENTER | DT_LEFT  );
				pDC->DrawText(outText, &nRect, DT_VCENTER | DT_LEFT  );


			////if (m_Dlg->m_xvChkEditCellMode == TRUE) ::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_SHOW);//�ǉ�2011.10.08

				////http://www.page.sannet.ne.jp/mtoga/lang/cv/bih-m_40.htm


			UpdateData(FALSE);
			UpdateWindow();

		}
		++nCnt;
	}

	//m_Dlg->GetStrFormat_Func();
	//��http://dejibouzu.com/page/2/ ��


	//http://www9.plala.or.jp/sayox/vc/vc14.html
	//http://msdn.microsoft.com/ja-jp/library/1w31a26y(v=VS.100).aspx


	//http://rararahp.cool.ne.jp/cgi-bin/lng/vc/vclng.cgi?print+200204/02040004.txt

	//http://oshiete.goo.ne.jp/qa/1125503.html

	//http://msdn.microsoft.com/ja-jp/library/Cc428474

 //http://oshiete.goo.ne.jp/qa/5948646.html
 //http://oshiete.goo.ne.jp/qa/1382911.html
 //�� http://oshiete.goo.ne.jp/qa/4165655.html
//�� http://bingobingobingo.blog49.fc2.com/category4-1.html

}


///////////////////////////////////////////////////////////////////////////////
// GetBold  //http://www.opengle.com/codeview/XHotJWgzMRw/trunk/XListCtrl/XListCtrl/XListCtrl.cpp.html
//BOOL CMylistCtrl::GetBold(int nItem, int nSubItem) //2011.05.22�ǉ�
//{

//}