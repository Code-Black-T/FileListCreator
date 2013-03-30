#pragma once


// AllYesOrNoDlg ダイアログ

class AllYesOrNoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AllYesOrNoDlg)

public:
	AllYesOrNoDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~AllYesOrNoDlg();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_AllYesOrNo };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};
