#pragma once
#include "afxwin.h"


// ReplaceDlg �_�C�A���O

class ReplaceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ReplaceDlg)

public:
	ReplaceDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~ReplaceDlg();

	virtual BOOL OnInitDialog();//T�ǉ�

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_Replace };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	
	virtual BOOL PreTranslateMessage(MSG* pMsg); //�ǉ�2011.10.14
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_xcCombo_SearchBOX;
	CComboBox m_xcCombo_ReplaceBOX;

	int MatchCNT;

	void ExistCheckFunc(CString mySwitch);
	void ReadOrWriteComboData_Func(CString mySwitch);
	void ReplaceFunc(int index,CString SearchStr,CString ReplaceStr);

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnReplaceClear();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnReplaceGetfilename();
	afx_msg void OnBnClickedBtnExchange();
	afx_msg void OnBnClickedBtnReplaceGetfilename2();
	afx_msg void OnBnClickedBtnSearch();
	afx_msg void OnBnClickedBtnReplace();
	afx_msg void OnCbnEditchangeComboSearchbox();
	afx_msg void OnCbnSelchangeComboSearchbox();
	BOOL m_xvChkReplaceFullPath;
	afx_msg void OnBnClickedChkReplacefullpath();
};
