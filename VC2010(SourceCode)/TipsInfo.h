#pragma once


// TipsInfo ダイアログ

class TipsInfo : public CDialogEx
{
	DECLARE_DYNAMIC(TipsInfo)

public:
	TipsInfo(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~TipsInfo();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_Tips };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};
