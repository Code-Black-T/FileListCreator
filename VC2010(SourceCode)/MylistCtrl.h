#pragma once
#include "afxcmn.h"
class CMylistCtrl :
	public CListCtrl
{
public:
	CMylistCtrl(void);
	~CMylistCtrl(void);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);/*lpDrawItemStruct*/
};

