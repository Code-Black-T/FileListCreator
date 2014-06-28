#pragma once
#include "afxwin.h"

//static CString TargetFileSpecs;

// CFileSpecsDlg ダイアログ

class CFileSpecsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileSpecsDlg)
public:
	CFileSpecsDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CFileSpecsDlg();
	virtual BOOL OnInitDialog();//T追加
// ダイアログ データ
	enum { IDD = IDD_DIALOG_FileSpecs };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CString TargetFileSpecs;
	CString EditFileSpecs;
	CComboBox m_xcCombo_FileSpec;
	
	void ExistCheckFunc();
	void ReadOrWriteComboData_Func(CString);

	afx_msg void OnBnClickedButtonDefault();

	afx_msg void OnBnClickedOk();

	static BOOL Audio_AddFLG;
	static BOOL Movie_AddFLG;
	static BOOL Image_AddFLG;
	static BOOL Document_AddFLG;
	static BOOL Zip_AddFLG;
	static BOOL HTML_AddFLG;
	static BOOL TXT_AddFLG;
	static BOOL Play_LIST_AddFLG;
	CString Office2007_FileTypes;
	int myResult;

	void setFileSpecsFunc(CString, BOOL);
	afx_msg void OnBnClickedButtonFilespecAudio();
	afx_msg void OnBnClickedButtonFilespecMovie();
	afx_msg void OnBnClickedButtonFilespecImage();
	afx_msg void OnBnClickedButtonFilespecDocument();
	afx_msg void OnBnClickedButtonFilespecZip();
	afx_msg void OnBnClickedButtonFilespecHtml();
	afx_msg void OnBnClickedButtonFilespecTxt();
	afx_msg void OnBnClickedButtonFilespecPlaylist();
	afx_msg void OnBnClickedButtonFilespecAll();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnSpecclear();
};
