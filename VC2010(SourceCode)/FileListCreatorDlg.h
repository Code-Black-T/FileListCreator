
// FileListCreatorDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "MylistCtrl.h"

//▼vector 用 2012.05.02▼
//#include <stdio.h>
#include <sys/types.h>

#include <algorithm>
#include <string>
#include <vector>

#include <iterator>

using namespace std;
//▲vector 用 2012.05.02▲

//#include <stdio.h> //追加 2012.04.30
//#include <stdlib.h> //追加 2012.04.30

//#include "windows.h" //追加

// CFileListCreatorDlg ダイアログ
class CFileListCreatorDlg : public CDialogEx
{
// コンストラクション
public:
	CFileListCreatorDlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
	enum { IDD = IDD_FILELISTCREATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();

	//virtual void OnCancel(); //T追加 //http://msdn.microsoft.com/ja-jp/library/kw3wtttf.aspx
	
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg); //追加2011.09.16

//T追加
private:
	CString FLC_CurrentVersion;

public:
	afx_msg void OnBnClickedBtnImport();
	afx_msg void OnBnClickedBtnExport();
	afx_msg void OnBnClickedBtnTest();
	//CString  FullPathToFileName(CString );

	int ListInsertItem(CString);
	int ListInit(void);

	void DEL_FileType_Func();

	void AddDirectorySTR_Func();
	void AddDirectorySTR_Items(int);

	//void PackageSearch_Func(CString, CString);
	//int PackageSearch_Items(CString, CString);
	afx_msg void OnBnClickedChkViewmode();
	afx_msg void OnBnClickedBtnStepsearch();

	afx_msg void OnBnClickedBtnRestore();
	afx_msg void OnBnClickedBtnPackagesearch();

	//LVCOLUMN    lvc;//追加2011.05.13
	//LVITEM		lvi;//追加2011.05.13
	CString StatusStringSet(CString,int,BOOL);

	long CStringToLong(CString);
	BOOL g_NoDrawFLG; //TRUEの時、リストを描画しない
	BOOL SelectALLFLG; //すべてを選択するときは最低限の処理のみ行う

	CString CFileListCreatorDlg::CreateDateTime(int mySwitch);//mySwitch//1:ファイル名に付与する日時//2:現在の時間を表示

	CMylistCtrl m_xcList;
	//CMylistCtrl m_xcList2;
	//CMylistCtrl w_m_xcList;
	
	typedef struct ListItemStruct {
		//int *i;
		CString	RepetitionNum;	//ファイル重複識別ナンバー
		CString	Num;		//通し番号
		CString	FullPath;	//ファイルパス
		CString	FileName;	//ファイル名
		CString	ApproximateByte;	//おおよそのデータサイズ//バイト
		CString	AccurateByte;		//実際のデータサイズ//実バイト
		CString	ModifyDate;		//修正日
		CString	ModifyTime;		//修正時間
		CString	RemarksColumn;		//備考欄
		CString FormatDataStr;
		//item():
		//~item();
	};

	std::vector<ListItemStruct> vecPrev;
	std::vector<ListItemStruct> vecNow;
	std::vector<ListItemStruct> vecWork;

	//ListItemStruct *prevData;
	//ListItemStruct *nowData;
	//ListItemStruct *workData;

	ListItemStruct *PrevListPtr;
	ListItemStruct *NowListPtr;
	ListItemStruct *WorkListPtr;

	void push_back_Func(int ItemCount,CString targetName);
	void pop_Func(int ItemCount,CString targetName);

	void malloc_Func(int ItemCount,CString targetName); //コメント化 2012.05.02
	//void SwapListData(CMylistCtrl &outList, CMylistCtrl &inList);
	//void DuplicateList(CMylistCtrl *outList, CMylistCtrl *inList); //追加 2012.04.27
	
	void DuplicateList(); //追加 2012.04.29 //コメント化 2012.05.02
	void CreateWorkArray(); //コメント化 2012.05.02

	int LastPrevItemCount;
	int LastNowItemCount;
	int LastWorkItemCount;
	//int PrevPrevItemCount;

	//BOOL BoldModeFLG;
	CStatic m_xcStaticString;//IDC_STATIC_DRAG_ON_ME
	//HBRUSH CFileListCreatorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	CString Total_Bytes_Func();
	CString ItemCount_Func(BOOL);
	CString ProhibitFileName(CString, BOOL);

	//BOOL CopyFile(LPCTSTR SrcFile, LPCTSTR DestFile, BOOL Exists);

	void Merge_Func();
	//TCHAR CFileListCreatorDlg::StringToCharFunc(CString);
	void Copy_Func();

	void CopyFolder_Items(CString strTrgDir,CString strFileSpec ,BOOL CopyMode, CString tempCopyToSavePath);

	int myReverseFind(CString,CString,int);
	CString m_xvStCount;
	CString m_xvTotal_Bytes;
	int keyColumn;
	void SetSEQ_NUM_Func(BOOL NotConfirm);
	void SetSEQ_NUM_Items(int);
	void OnEditlistSetSequentialNum();
	CString AddTagFunc(int,int);
	CString CurrentDirFunc(CString,BOOL);
	void SearchFileRecurse(CString);
	BOOL isFileFLG(CString,CString);
	BOOL isDirectoryFLG(CString);
	void RestoreFunc(int);
	//CString TargetFileSpecs;
	void PackageSearch_Items(CString, CString,BOOL);
	void PackageSearch_Func(CString, CString);
	//TCHAR  TargetPath[MAX_PATH];
	//afx_msg void OnBnClickedOk();//
	//afx_msg void OnBnClickedOk(CString);
	BOOL m_xvChkViewMode;
	BOOL m_xvChkSubFolder;
	afx_msg void OnBnClickedChkSearchSubfolder();
	CString m_xvStatusString;
	afx_msg void OnStnClickedStaticStatusstring();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnSort();

	ULONGLONG BoldByteSum;
	ULONGLONG BolditemCount;

	int Bold_CNT_IDX;
	int Bold_SUM_CNT;

	BOOL SkipFLG;
	//BOOL SkipFLG2;

	void Total_Bytes_Bold();
	int GetStrLen_Func(CString);

	int importFileResult;

	ULONGLONG DoWithCnt;
	ULONGLONG TotalItemsCount;

	CString outGeneratorVer;
	void GetStrFormat_Func();
	void SetStrFormat_Func();
	void ExportFileList(BOOL AutoSaveFLG); //削除 BOOL ReExportFLG
	void ExportFileList_Func(CString saveDir, CString FileName); //追加 2012.04.22

	void ExcludeNonEmphasizedItems();
	BOOL myIsDigit_Func(CString);
	CString inGeneratorVer;
	ULONGLONG FileListItemsCount(CString);
	int importFileList_Func(CString,BOOL);
	void importFileList();
	void StrToTagSign();

	void AutoImportFileList();
	// Sort items by associated lParam
	//static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	//void SortFunc();

	void PlayEmphasizedMusic();

	//TCHAR StringToCharFunc(CString);
	static int CALLBACK CompareFunc(LPARAM param1, LPARAM param2, LPARAM param3);
	void RenumberItem();
	//afx_msg void OnNMRDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuMymessage();

	afx_msg void DeleteSelectedRows_Func();//変更 2012.05.31
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnMenuDeleteSelectedRows();//変更 2012.05.31
	afx_msg void OnFileImport();
	afx_msg void OnFileExport();
	afx_msg void OnSearchPackagesearch();
	afx_msg void OnSearchStepsearch();
	afx_msg void OnEditRestore();
	afx_msg void OnEditlistSort();
	afx_msg void OnMenuDeleterow();//変更 2012.05.31
	afx_msg void OnOptionMymessage();
	afx_msg void OnFileQuit();
	afx_msg void MenuOpenBy_Func(int);
	afx_msg void OnMenuOpenbyexplorer();
	afx_msg void OnOpenbyConnectedapplication();
	afx_msg void OnOpenExplorer();
	afx_msg void OnMenuPlaySelectedMusic();
	afx_msg void OnOpenbyMediaplayer();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnMenuSelectall();
	afx_msg void OnEditlistSelectall();
	afx_msg void OnEditDelfiletype();
	afx_msg void OnMenuDelFiletype();
	afx_msg void OnMenuRestoreListInformation();
	afx_msg void OnEditlistAdddirstr();
	afx_msg void OnMenuAdddirectorystr();
	afx_msg void OnOptionVersion();
	COLORREF m_color;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSortSortitemsbyfilename();
	afx_msg void OnSortSortitemsbydatasize();
	afx_msg void OnSortSortitemsbydate();
	afx_msg void OnSortSortitemsbypathname();
	afx_msg void OnSortSortitemsbyrepetitionnum();
	afx_msg void OnEditlistRenumber();
	afx_msg void OnOpenbyLinkfileopen();
	//int LastClickItem;
	BOOL m_xvChkEasySelect;
	CString m_xvStrEasySelectMode;
	BOOL m_xvChkRedOnMode;
	CString m_xvStrRedOnMode;

	afx_msg void OnBnClickedChkEasyselect();
	afx_msg void OnCopyEasyselect();
	afx_msg void OnCopyEasyselectoff();

	afx_msg void OnMenuEmphasisbybold();
	afx_msg void OnMenuEmphasizedFormatCancellation();
	afx_msg void OnEditselecteditemBold();

	afx_msg void OnBnClickedChkRedonmode();
	afx_msg void OnStnClickedStaticRedonmode();

	int g_RadioModifyDate;
	int g_RadioRemarksColumn;

	int g_RadioENCODING_SELECT; //追加 2012.04.21

	BOOL g_ChkCopyOn;
	BOOL g_ChkRedOn;
	afx_msg void OnOptionTips();
	afx_msg void OnMenuEmphasisbyred();
	afx_msg void OnEditselecteditemRed();
	afx_msg void OnMenuExpandListFile();
	afx_msg void OnImportListFile();
	afx_msg void OnMenuPlayEmphasizedMusic();
	afx_msg void OnMenuExcludeNonemphasizedItems();
	afx_msg void OnSortSortitemsbystrformat();
	afx_msg void OnSortMerge();
	afx_msg void OnCopyCopy();

	CTime item_Date(CString FullPathString ,CString strFileSpec);
	CTime inFolder_Date(CString strTrgDir, CString strFileSpec, CTime RecentlyDate);

	ULONGLONG item_Byte(CString FullPathString, CString strFileSpec);
	ULONGLONG inFolder_Byte(CString strTrgDir, CString strTrgFile, ULONGLONG tempSumByte);

	void iTunesAlbumList_Items(int);
	void iTunesAlbumList_Func();
	void inFolder_Func();
	CString iTunes_Add_Artist_Items(BOOL FileOutputFLG, CString inFile, CString tempFileName, CString myFolderPath, BOOL DEL_FolderFLG);
	void iTunes_Add_Artist_Func(BOOL FileOutputFLG);

	afx_msg void OnItunesAlbumlist();
	afx_msg void OnItunesAddartiststr();
	afx_msg void OnEditlistReplace();
	afx_msg void OnMenuSelectallcancellation();

	CString fileUpdatedRecently(CString fpath,int workRow);
	CTime CStringToDate(CString strDate);
	afx_msg void OnFilterDatefilter();
	int SetToRed(int);
	int SetToBold(int);
	afx_msg void OnBnClickedCancel();
	void SetFormatNumToStr_Items(int);

	void SelectALL_Func();
	void SelectALL_CancellationFunc();

	CString inFolder_AllFile(CString strTrgDir, CString strFileSpec, CString tempFiles);
	BOOL m_xvChkAutoSave;
	afx_msg void OnBnClickedChkAutosave();
	afx_msg void OnAutosaveAutosaveon();
	afx_msg void OnAutosaveAutosaveoff();

	void AutoSaveMode_ReadOrWrite_Func(CString mySwitch);
	afx_msg void OnBnClickedOk();
	afx_msg void OnMenuFileSave();
	afx_msg void OnFileRecovery();

	CString myStrToLower_Func(CString FileSpecStr);
	CString ReadOrWritePlayList_Func(CString mySwitch,CString FilePath,CString BuffList,CString SaveFileName);
	//BOOL UTF8ToShiftJIS(const CString &src, CString *dest);
	BOOL UTF8ToShiftJIS(const CStringA& src, CStringA* dest);
	//char szShiftJis[MAX_PATH];
	//char bufUTF8[MAX_PATH];
	//char bufShiftJis[MAX_PATH];
	//CString ShiftJisToUTF8(CString bufUTF8);
	//CString UTF8ToShiftJis(CString bufUTF8);
	afx_msg void OnMenuFilePrint();
	afx_msg void OnFilterKeywords();

	int SetToBoldAndRedInversion(int workRow);

	int	LastSelectedRow;
	int LastSelectedColumn;

	//BOOL NotInversion; //TRUEの時ファイル名・備考欄の編集中は、（太文字＆赤文字は）反転しない


	//BOOL ListDBLCLK_FLG;
	//static WNDPROC PrevProc; //http://questionbox.jp.msn.com/qa1207033.html

	//LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp );
//private:
     //static LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
     //LRESULT WindowProc( HWND, UINT, WPARAM, LPARAM );
     //static unsigned __stdcall Thread(  void * );

	//int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,PSTR lpCmdLine , int nCmdShow );
	//void WINAPI WinMainCRTStartup(void);
	//CWinApp:: InitInstance
	
	//int APIENTRY WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,PSTR lpCmdLine , int nCmdShow );

	afx_msg void OnBnClickedBtnNosavequit();

	void PreferenceFileClear_Func();
	afx_msg void OnOptionPreferencefileclear();
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnQuit();
	CString m_xvEditItem;
	afx_msg void OnEnChangeEditItem();
	afx_msg void OnEnKillfocusEditItem();

	void EditCellShow(int workRow,int workColumn);
	BOOL m_xvChkEditCellMode;
	CString m_xvStrEditCellMode;
	afx_msg void OnBnClickedChkEditcellmode();

	BOOL ESCAPE_FLG;
	afx_msg void OnBnClickedBtnSetseqNum();

	int FindIDX;
	BOOL CheckRemarksColumn();
	BOOL CheckFileName();
	afx_msg void OnMenuExpandMusicListFile();
	void ExpandMusicListFile_Func(CString MusicListFilePath);
	void SameItemCheck(CString mySwitch);
	afx_msg void OnRepeateditemcheckBydatasize();
	afx_msg void OnRepeateditemcheckByfilename();
	afx_msg void OnRepeateditemcheckBymodifytime();
	afx_msg void OnRepeateditemcheckByallinfo();

	CString LastImportFileName;
	//CString LastExportSaveDir; //削除 2012.04.22
	//CString LastExportFileName; //削除 2012.04.22

	CString FullPathToFileName(CString FullPathStr);
	afx_msg void OnBnClickedBtnCurrentdirectoryopen();
	afx_msg void OnOptionCurrentdirectoryopen();
	afx_msg void OnEditlistClearrepetitionnum();
	afx_msg void OnEditlistClearremarkscolumn();
	afx_msg void OnLanguageJapanese();
	afx_msg void OnLanguageEnglish();

	CString SelectedLanguage;
	void ChangeLanguage();
	afx_msg void OnOpenbyVirtualbrowser();
	afx_msg void OnOptionFilepathlimitcheck();
	afx_msg void OnEditlistUndo();

	LVITEM       lvi; //追加 2012.04.25
	//LVITEM       lvi2; //追加 2012.04.25
	LVITEM       temp_lvi; //追加 2012.04.25

	//http://sa.eei.eng.osaka-u.ac.jp/tatsumi/tani_prog/malloc.html



	//BOOL NewPrevDataFLG;
	//BOOL NewNowDataFLG;
	//BOOL NewWorkDataDataFLG;

	BOOL UNDO_FLG;

	BOOL ListDataNoChange_FLG; //追加 2012.05.13

	//BOOL FOCUSED_and_SELECTED; //追加 2012.05.16

	//ListItemStruct prevData[1000];
	//ListItemStruct nowData;
	//ListItemStruct workData;

	//void CFileListCreatorDlg::transferListData(const ListItemStruct& workListData);
	//void DuplicateList(CMylistCtrl &outList, CMylistCtrl &inList);
	afx_msg void OnLvnDeleteitemList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangingList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickList(NMHDR *pNMHDR, LRESULT *pResult);

	void SortColumnDrawCaption(int workColumn, BOOL SortFLG); //追加 2012.05.24
	//CString LastEditStr;//追加 2012.05.20
	afx_msg void OnLvnInsertitemList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnDeleteallitemsList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnCellsizefix();

	CString CellSizeFixMode;

	BOOL SetClipboardText(LPCTSTR lpszText);
	CString GetClipboardText(CString strText);
	//BOOL CFileListCreatorDlg::SetClipboardText(CString cs);
	afx_msg void OnMenuSetclipboardtext();
	afx_msg void OnMenuGetclipboardtext();

	void DeleteSelectedCells_Func();
	afx_msg void OnMenuDeletecell();

	void SortEnsureVisible_Func();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	RECT initWindowSize;
	RECT initListSize;

	RECT rectBTN_Import;
	RECT rectBTN_Export;
	RECT rectBTN_Restore;
	RECT rectBTN_Sort;
	RECT rectBTN_PackageSearch;
	RECT rectBTN_StepSearch;
	RECT rectBTN_CurrentDirectoryOpen;
	RECT rectBTN_Clear;
	RECT rectCHK_RedOnMode;
	RECT rectCHK_EasySelect;
	RECT rectCHK_EditCellMode;
	RECT rectSTATIC_RedOnMode;
	RECT rectSTATIC_EasySelectMode;
	RECT rectSTATIC_EditCellMode;
	RECT rectSTATIC_RedOnModeFrame;
	RECT rectSTATIC_EasySelectFrame;
	RECT rectSTATIC_EditCellModeFrame;
	RECT rectCHK_Search_SubFolder;
	RECT rectCHK_AutoSave;
	RECT rectBTN_CellSizeFix;
	RECT rectBTN_SetSEQ_NUM;
	RECT rectBTN_NoSaveQuit;
	RECT rectBTN_Quit;
	RECT rectBTN_RedrawWindow;

	RECT rectCHK_UseUNDO;

	RECT rectSTATIC_DRAG_ON_ME;

	RECT CurRect; //publicに変更 2012.07.02


	RECT rectBTN_MiniWindow;
	BOOL MiniWindowFLG;
	RECT initWindowSize2;
	afx_msg void OnBnClickedBtnMiniwindow();
	afx_msg void OnBnClickedBtnRedrawwindow();

	//BOOL UseUNDO_FLG;
	BOOL m_xvChkUseUNDO;
	afx_msg void OnBnClickedChkUseundo();

	void UseUNDO_Mode_ReadOrWrite_Func(CString mySwitch);

	BOOL ShellExecuteOpenFLG;
//	afx_msg void OnLvnEndScrollList(NMHDR *pNMHDR, LRESULT *pResult);

	BOOL ListInsertItemFLG; //TRUEの時はスクロール時、RedrawWindow();しない //XP対策

	BOOL AnyfileImport;

	void SpeakFunc(CString myText);
	BOOL iTunesPlayList_Import_Func(CString FullPath,CString mySwitch);
	//BOOL ALL_FileSpecs;
	afx_msg void OnMenuCancel();

	void PressArrowKeyToSave();  //追加 2014.06.20
	int RemoveFileToTrash();  //追加 2014.06.20

	BOOL CtrlEnterMSG;  //追加 2014.06.28
};




//class CFileSpecsDlg : public CDialogEx
//{
//   // Construct the dialog box passing the 
//   // ID of the dialog template resource
//   CDialog CFileSpecsDlg(IDD_DIALOG_FileSpecs);
//
//   // Create and show the dialog box
//   INT_PTR nRet = -1;
//   nRet = CFileSpecsDlg.DoModal();
//
//   // Handle the return value from DoModal
//   switch (nRet)
//   {
//      case -1: 
//         AfxMessageBox(_T("Dialog box could not be created!"));
//         break;
//      case IDABORT:
//         // Do something
//         break;
//      case IDOK:
//         // Do something
//         break;
//      case IDCANCEL:
//         // Do something
//         break;
//      default:
//         // Do something
//         break;
//   };
//}