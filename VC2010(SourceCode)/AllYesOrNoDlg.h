#pragma once


// AllYesOrNoDlg �_�C�A���O

class AllYesOrNoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AllYesOrNoDlg)

public:
	AllYesOrNoDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~AllYesOrNoDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_AllYesOrNo };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
};
