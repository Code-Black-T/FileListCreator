#pragma once
#include "afxwin.h"


// KeywordDlg ダイアログ

class KeywordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(KeywordDlg)

public:
	KeywordDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~KeywordDlg();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_Keywords };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	
	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog(); //追加2011.08.17
	virtual BOOL PreTranslateMessage(MSG* pMsg); //追加2011.09.02

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnBnClickedBtnTargetbold();
	CComboBox m_xcCombo_OK_BOX;
	CComboBox m_xcCombo_NG_BOX;

	void ExistCheckFunc(CString mySwitch);
	void ReadOrWriteComboData_Func(CString mySwitch);

	DWORD dwSel_OK;
	DWORD dwSel_NG;
	CString LastFocus;
	void InsertStrIntoKeywords(CString str);
	afx_msg void OnBnClickedBtnAsterisk();

	CString keywords_OK_Str;
	CString keywords_NG_Str;

	CString Keywords_OK_Array[100];
	CString Keywords_NG_Array[100];

	int OK_index;
	int NG_index;

	BOOL Split_And_SetArray_Func();
	
	int KeywordDlg::StrMatchMBS( const TCHAR *Ptn, const TCHAR *Str);
	//int StrMatchMBS( const unsigned char *Ptn, const unsigned char *Str );

	BOOL keywords_OK(CString targetStr,CString in_Str);
	BOOL keywords_NG(CString targetStr,CString in_Str);

	BOOL KeywordDlg::SameKeyword();

	//LRESULT CALLBACK WndProc(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp);
	//int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,
	//			PSTR lpCmdLine , int nCmdShow );

	//BOOL keywords_Match(int workRow, CString mySwitch);
	void EmphasisByKeywords(CString mySwitch);
	//void EmphasisByKeywords(CString mySwitch);

	afx_msg void OnCbnEditchangeComboOkBox();
	afx_msg void OnCbnKillfocusComboOkBox();
	afx_msg void OnCbnSelchangeComboOkBox();
	afx_msg void OnCbnSetfocusComboOkBox();
	afx_msg void OnCbnEditupdateComboOkBox();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCbnEditchangeComboNgBox();
	afx_msg void OnCbnSetfocusComboNgBox();
	afx_msg void OnCbnKillfocusComboNgBox();
	afx_msg void OnBnClickedBtnSpace();
	afx_msg void OnBnClickedBtnQuestionmark();
	afx_msg void OnBnClickedBtnPathseparator();
	afx_msg void OnBnClickedBtnDoublequotationmark();
	afx_msg void OnBnClickedBtnTargetred();
	BOOL m_xvChkFuzzySearch;
	afx_msg void OnBnClickedCheckFuzzysearchOn();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnTargetbold();
	afx_msg void OnBnClickedBtnExcludelist1();
	afx_msg void OnBnClickedBtnExcludelist2();
	afx_msg void OnBnClickedBtnFormatcancellation();
	afx_msg void OnBnClickedBtnKeywordsClear();
	afx_msg void OnBnClickedBtnHyphen();
	afx_msg void OnBnClickedBtnSlash();
	afx_msg void OnBnClickedBtnUnderscore();
	afx_msg void OnBnClickedBtnPeriod();
	BOOL m_xvChkKeywordFullPath;
	afx_msg void OnBnClickedChkKeywordfullpath();
	afx_msg void OnBnClickedKeywordsUndo();
};
