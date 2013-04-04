#pragma once


// HTML_Dlg ダイアログ

class HTML_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(HTML_Dlg)

public:
	HTML_Dlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~HTML_Dlg();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_HTML_Export };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	int m_xvRadioModifyDate;
	int m_xvRadioRemarksColumn;
	afx_msg void OnBnClickedButtonDefault2();
	int m_xvRadioENCODING_SELECT; //追加 2012.04.21

	BOOL m_xvChkCopyOn;
	BOOL m_xvChkRedOn;
	afx_msg void OnBnClickedCheckCopyFuncOn();
	afx_msg void OnBnClickedCheckStrredOn();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadioRemarkscolumnvisible();
	afx_msg void OnBnClickedRadioRemarkscolumninvisible();
	afx_msg void OnBnClickedCancel();
};
