#include "StdAfx.h"


//追加▼
#include "FileListCreator.h"

#include "FileListCreatorDlg.h"

#include <ctype.h>//追加
#include "afxwin.h"//追加

#include "FileSpecsDlg.h"
#include "afxdialogex.h"
//追加▲

#include "MylistCtrl.h"

CMylistCtrl::CMylistCtrl(void)
{
	//LastClickItem=-1;
}


CMylistCtrl::~CMylistCtrl(void)
{
}


//static HFONT CreateMyFont(int nBold)//追加 2011.05.13
// {
//	//ディフォルトフォントをゲットする
// HFONT hFontDef = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
//
//	//フォントの詳細を受け取る構造体バッファ
// LOGFONT lf;
//
//	//フォントハンドルから詳細を受け取る
// GetObject(hFontDef, sizeof(lf), &lf);
//
// //このメンバにフォントの太さを設定する
// lf.lfWeight = nBold;
//
// //フォントの作成
// return CreateFontIndirect(&lf);
// }

void CMylistCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct){

	// TODO:  指定された項目を描画するためのコードを追加してください。
	//追加 2011.05.13


	//http://rararahp.cool.ne.jp/cgi-bin/lng/vc/vclng.cgi?print+201103/11030005.txt

	CFileListCreatorDlg* m_Dlg = (CFileListCreatorDlg*)AfxGetMainWnd();

	if( (m_Dlg==NULL)||(m_Dlg->GetSafeHwnd()==NULL) ){
		return;
	}

	if (m_Dlg->g_NoDrawFLG == TRUE){
		return;
	}

	//★http://dejibouzu.com/page/2/　▼


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

	//書式情報
	CString FormatDataStr;

	while( nMax > nCnt )
	{
		nIndentPix = 0;

		//アイテム取得のための設定
		LVITEM lvItem;
		lvItem.mask			= LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_INDENT; //追加 2012.05.16 LVCF_SUBITEM追加 ;//追加しても意味がなかった2011.05.14	| LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
		lvItem.iItem		= nItem;
		lvItem.iSubItem		= nCnt;
		lvItem.pszText		= szBuff;
		lvItem.cchTextMax	= sizeof(szBuff);
		lvItem.stateMask	= LVIS_FOCUSED | LVIS_SELECTED;//-1を LVIS_SELECTEDに変更2011.05.14

		//m_Dlg->m_xcList.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

		if( m_Dlg->m_xcList.GetItem(&lvItem) == TRUE ){
			if( nCnt == 0){
				//アイテムの場合
				m_Dlg->m_xcList.GetItemRect( nItem, &nRect, LVIR_BOUNDS);
				//m_Dlg->m_xcList.SetItemData(nItem,11);
			}else{
				//サブアイテムの場合
				m_Dlg->m_xcList.GetSubItemRect( nItem, nCnt, LVIR_BOUNDS, nRect);
			}

			//if ( m_phbrBkColor ){
				//カラーテーブルにブラシが作成されているなら背景を描画
				//if ( m_phbrBkColor[ nCnt * GetItemCount()  + nItem] )
				//{
					//アイテムの場合 描画箇所をアイテム部分のみに修正
					if( nCnt == 0 ){
						nRect.right = m_Dlg->m_xcList.GetColumnWidth( 0 );
					//}else if ( nCnt == 3 || nCnt == 8) { //追加 2011.10.09
					//	nRect.right = m_Dlg->m_xcList.GetColumnWidth( nCnt );
					}
					//FillRect( pDC->m_hDC, &nRect, m_phbrBkColor[ nCnt * GetItemCount()  + nItem ] );
				//}
			//}

//http://www.crimson-systems.com/tips/t003.htm
//http://oshiete.goo.ne.jp/qa/6645218.html
//http://www.tcn.zaq.ne.jp/zxcvbnm/projectc/vcpp/colortextcombo.htm

//===============教えて頂いた部分=======================

CFont fontBold, *pfontOld;
 LOGFONT lf;
  pDC->GetCurrentFont()->GetLogFont(&lf);
    // 描画動作が全体の再描画もしくは、
    // 選択状態が変化した場合
  
  //http://lhsp.s206.xrea.com/misc/ownerdraw.html
  //http://msdn.microsoft.com/ja-jp/library/92fhtw0f(v=VS.100).aspx



		if( lpDrawItemStruct->itemAction & ( ODA_DRAWENTIRE | ODA_SELECT )) {
				// コントロールの状態が選択された状態の場合

			if( lpDrawItemStruct->itemState & ODS_SELECTED ){
					 // 選択されている場合の描画

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
						pDC->SetTextColor(RGB(255,0,0));/*文字の色*/
					}

					if(FormatDataNum == 22){
						//FormatDataStr = _T("BOLD,RED,");
						lf.lfWeight = FW_BOLD;
						pDC->SetTextColor(RGB(255,0,0));/*文字の色*/
					}

					UpdateData(FALSE);
				}

				if( nCnt == 0){
					if(m_Dlg->m_xvChkEasySelect == TRUE){
						if(lf.lfWeight == FW_BOLD){
							if(m_Dlg->m_xcList.GetSelectedCount()==1){
								if (m_Dlg->SelectALLFLG  == FALSE ){
								//if(m_Dlg->NotInversion == FALSE){ //ファイル名・備考欄を編集する時は、反転しない
									lf.lfWeight = FW_NORMAL;
								//}
								}
							}
						}else{
							lf.lfWeight = FW_BOLD;
						}

						m_Dlg->m_xcList.SetItemState(nItem,     // フォーカス＆選択状態にしたいアイテムのインデックス
						!LVIS_FOCUSED | !LVIS_SELECTED,    // 状態
						LVIS_FOCUSED | LVIS_SELECTED);    // マスク

						m_Dlg->ListDataNoChange_FLG = FALSE;//追加 2012.05.13

						if (m_Dlg->ListDataNoChange_FLG == FALSE){  //追加 2012.05.13
							m_Dlg->SetWindowText(_T("FileListCreator (*)"));
						}
					}
				}

				//pDC->FillSolidRect(&lpDrawItemStruct->rcItem,RGB(0,0,255));/*文字の後ろの色（背景と一緒にしとくべき）*/
				pDC->SetBkMode(OPAQUE);
				pDC->SetBkColor(RGB(200,200,200));//選択された時の背景色
				//pDC->SetTextColor(RGB(255,255,255));/*文字の色*/

				if( nCnt == 0){   //変更 2012.04.17
					if(m_Dlg->m_xvChkRedOnMode == TRUE){
						if(pDC->GetTextColor() == RGB(255,0,0)){
							if(m_Dlg->m_xcList.GetSelectedCount()==1){
								if (m_Dlg->SelectALLFLG  == FALSE ){
								//if(m_Dlg->NotInversion == FALSE){ //ファイル名・備考欄を編集する時は、反転しない
									pDC->SetTextColor(RGB(0,0,0));/*文字の色*/
								//}
								}
							}
						}else{
							pDC->SetTextColor(RGB(255,0,0));/*文字の色*/
						}
						m_Dlg->m_xcList.SetItemState(nItem,     // フォーカス＆選択状態にしたいアイテムのインデックス
						!LVIS_FOCUSED | !LVIS_SELECTED,    // 状態
						LVIS_FOCUSED | LVIS_SELECTED);    // マスク

						m_Dlg->ListDataNoChange_FLG = FALSE;//追加 2012.05.13

						if (m_Dlg->ListDataNoChange_FLG == FALSE){  //追加 2012.05.13
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
					m_Dlg->LastSelectedRow  = nItem; //追加 2012.06.01
					//m_Dlg->LastSelectedColumn = nCnt; //残さない

				//===================================================
				}

					//0:ファイル重複識別ナンバー 1:通し番号 2:フルパス 3:ファイル名 4:おおよそのデータサイズ 5:データサイズ 6:修正日 7:修正時間 8:備考欄 9:書式情報
				//m_Dlg->LastSelectedRow  = nItem;
				//if(nCnt==3 || nCnt==8){


			}else{ // 選択されていない(？)場合の描画
				//if( lpDrawItemStruct->itemState & ODS_FOCUS ){
				//	m_Dlg->LastSelectedColumn = nItem; //残す
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
					pDC->SetTextColor(RGB(255,0,0));/*文字の色*/
				}

				if(FormatDataNum == 22){
					//FormatDataStr = _T("BOLD,RED,");
					lf.lfWeight = FW_BOLD;
					pDC->SetTextColor(RGB(255,0,0));/*文字の色*/
				}

				UpdateData(FALSE);

			}

		}else{// 選択されていない場合の描画

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
					pDC->SetTextColor(RGB(255,0,0));/*文字の色*/
				}

				if(FormatDataNum == 22){
					//FormatDataStr = _T("BOLD,RED,");
					lf.lfWeight = FW_BOLD;
					pDC->SetTextColor(RGB(255,0,0));/*文字の色*/
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
			//テキスト描画

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
				pDC->SetTextColor(RGB(255,0,0));/*文字の色*/
			}

			if(FormatDataNum == 22){
				//FormatDataStr = _T("BOLD,RED,");
				lf.lfWeight = FW_BOLD;
				pDC->SetTextColor(RGB(255,0,0));/*文字の色*/
			}



			if( nCnt == 9){  //コメント化 2012.05.15
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

				nRect.left += 10;//変更2011.05.14
				nRect.top +=2;//変更2011.05.14

				//pDC->DrawText(outText, &nRect, DT_VCENTER | DT_LEFT  );
				pDC->DrawText(outText, &nRect, DT_VCENTER | DT_LEFT  );


			////if (m_Dlg->m_xvChkEditCellMode == TRUE) ::ShowWindow(::GetDlgItem(m_hWnd,IDC_STATIC_Arrow),SW_SHOW);//追加2011.10.08

				////http://www.page.sannet.ne.jp/mtoga/lang/cv/bih-m_40.htm


			UpdateData(FALSE);
			UpdateWindow();

		}
		++nCnt;
	}

	//m_Dlg->GetStrFormat_Func();
	//★http://dejibouzu.com/page/2/ ▲


	//http://www9.plala.or.jp/sayox/vc/vc14.html
	//http://msdn.microsoft.com/ja-jp/library/1w31a26y(v=VS.100).aspx


	//http://rararahp.cool.ne.jp/cgi-bin/lng/vc/vclng.cgi?print+200204/02040004.txt

	//http://oshiete.goo.ne.jp/qa/1125503.html

	//http://msdn.microsoft.com/ja-jp/library/Cc428474

 //http://oshiete.goo.ne.jp/qa/5948646.html
 //http://oshiete.goo.ne.jp/qa/1382911.html
 //★ http://oshiete.goo.ne.jp/qa/4165655.html
//★ http://bingobingobingo.blog49.fc2.com/category4-1.html

}


///////////////////////////////////////////////////////////////////////////////
// GetBold  //http://www.opengle.com/codeview/XHotJWgzMRw/trunk/XListCtrl/XListCtrl/XListCtrl.cpp.html
//BOOL CMylistCtrl::GetBold(int nItem, int nSubItem) //2011.05.22追加
//{

//}