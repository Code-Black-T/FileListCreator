#pragma once


// TipsInfo �_�C�A���O

class TipsInfo : public CDialogEx
{
	DECLARE_DYNAMIC(TipsInfo)

public:
	TipsInfo(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~TipsInfo();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_Tips };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
};
