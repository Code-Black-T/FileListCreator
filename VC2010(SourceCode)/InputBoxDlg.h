#pragma once
#include "afxwin.h"


// InputBoxDlg ダイアログ

class InputBoxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InputBoxDlg)

public:
	InputBoxDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~InputBoxDlg();

	virtual BOOL OnInitDialog();//T追加

// ダイアログ データ
	enum { IDD = IDD_DIALOG_InputBox };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_xcCombo_InputFileName;
	CString KeepTime;
	
	CString KeepFileNameStr; //追加 2012.12.01
	
	CString ExportFileName;

	void ExistCheckFunc(CString mySwitch);
	void ReadOrWriteComboData_Func(CString mySwitch);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnFilenameClear();
	afx_msg void OnBnClickedBtnAlbumlist();
	afx_msg void OnBnClickedBtnSinglelist();
	afx_msg void OnBnClickedBtntoday();
	afx_msg void OnBnClickedBtnLastimportname();
	CComboBox m_xcCombo_For_X;
	afx_msg void OnCbnSelchangeComboForX();
	int InputBoxDlg::StrMatchMBS( const TCHAR *Ptn, const TCHAR *Str ); //追加 2012.12.01
};
