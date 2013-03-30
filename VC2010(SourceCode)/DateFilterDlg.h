#pragma once
#include "afxwin.h"


// DateFilterDlg �_�C�A���O

class DateFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DateFilterDlg)

public:
	DateFilterDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~DateFilterDlg();

	virtual BOOL OnInitDialog();//T�ǉ�

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_DateFilter };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	virtual BOOL PreTranslateMessage(MSG* pMsg); //�ǉ�2012.04.04
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_xcCombo_StartDate;
	CComboBox m_xcCombo_EndDate;
	CComboBox m_xcCombo_TargetDate;

	BOOL DateMatch(int workRow, CString mySwitch,CString strTargetDate,CString strStartDate,CString strEndDate);
	void EmphasisByDate(CString mySwitch);

	void ExistCheckFunc(CString mySwitch);
	void ReadOrWriteComboData_Func(CString mySwitch);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnTargetred();
	afx_msg void OnBnClickedBtnOverwritedate();
	afx_msg void OnBnClickedBtnTargetbold();
	afx_msg void OnBnClickedBtnExcludelist1();
	afx_msg void OnBnClickedBtnExcludelist2();
	afx_msg void OnBnClickedBtnFormatcancellation();
	afx_msg void OnBnClickedBtnAlldateclear();
	afx_msg void OnBnClickedBtnDateSettoday();
	afx_msg void OnBnClickedCancel();
	BOOL m_xvChkDateSpan;
	BOOL m_xvChkTargetDate;
	afx_msg void OnBnClickedCheckDatespan();
	afx_msg void OnBnClickedCheckTargetdate();
	afx_msg void OnCbnSetfocusComboStartdate();
	afx_msg void OnCbnSetfocusComboEnddate();
	afx_msg void OnCbnSetfocusComboTargetdate();
};
