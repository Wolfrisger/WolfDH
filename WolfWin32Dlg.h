//
#pragma once

#ifndef LPARAM
#include <windef.h>
#endif
#include "WolfDriverHelper.h"

#define DCL_WWDLGPROC(classname) \
static classname* m_instance;\
static BOOL CALLBACK Proc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) \
{\
	m_instance->CMH(hDlg);\
	return m_instance->Procf(uMsg, wParam, lParam);\
}\

#define IMP_WWDLGPROC(classname) \
classname OBJ##classname;\
classname* classname::m_instance = &OBJ##classname;\

class CWolfWin32Dlg
{
	//use DCL_WWDLGPROC to implement static Proc function (public)
public:
	//comfirm member handle
	void CMH(HWND hDlg)
	{
		m_hDlg = hDlg;
	}
	virtual BOOL Procf(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	HWND GetSafeHwnd()
	{
		return m_hDlg;
	}
protected:
	CWolfWin32Dlg() : m_hDlg() {}
	virtual void Release() = 0;
	virtual void InitDialog() = 0;
	//retargeting
	inline auto SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		return ::SendMessage(m_hDlg, Msg, wParam, lParam);
	}
	inline auto PostMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		return ::PostMessage(m_hDlg, Msg, wParam, lParam);
	}
	inline auto SendDlgItemMessage(int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		return ::SendDlgItemMessage(m_hDlg, nIDDlgItem, Msg, wParam, lParam);
	}
	inline auto GetDlgItem(int id)
	{
		return ::GetDlgItem(m_hDlg, id);
	}
	inline auto SetDlgItemText(int id, LPCWSTR lpStr)
	{
		return ::SetDlgItemText(m_hDlg, id, lpStr);
	}
	inline auto GetDlgItemText(int id, LPWSTR lpStr, int cchMax)
	{
		return ::GetDlgItemText(m_hDlg, id, lpStr, cchMax);
	}
	inline auto SetDlgItemInt(int nIDDlgItem, UINT uValue, BOOL bSigned)
	{
		return ::SetDlgItemInt(m_hDlg, nIDDlgItem, uValue, bSigned);
	}
	inline auto GetDlgItemInt(int nIDDlgItem, BOOL* lpTranslated, BOOL bSigned)
	{
		return ::GetDlgItemInt(m_hDlg, nIDDlgItem, lpTranslated, bSigned);
	}
	inline auto CheckRadioButton(int nIDFirstButton, int nIDLastButton, int nIDCheckButton)
	{
		return ::CheckRadioButton(m_hDlg, nIDFirstButton, nIDLastButton, nIDCheckButton);
	}
	inline auto CheckDlgButton(int nIDButton, UINT uCheck)
	{
		return ::CheckDlgButton(m_hDlg, nIDButton, uCheck);
	}
	inline auto IsDlgButtonChecked(int nIDButton)
	{
		return ::IsDlgButtonChecked(m_hDlg, nIDButton);
	}
	auto GetDlgItemText(int id)
	{
		TCHAR buf[256];
		GetDlgItemText(id, buf, 256);
		return WolfDH::WFstring(buf);
	}
	inline auto SetWindowLongPtr(int nIndex, LONG_PTR dwNewLong)
	{
		return ::SetWindowLongPtr(m_hDlg, nIndex, dwNewLong);
	}
	inline auto GetWindowLongPtr(int nIndex)
	{
		return ::GetWindowLongPtr(m_hDlg, nIndex);
	}
	inline auto GetParent()
	{
		return ::GetParent(m_hDlg);
	}
	inline auto PropSheetChanged()
	{
		return PropSheet_Changed(GetParent(), m_hDlg);
	}
	inline auto ClientToScreen(POINT& point)
	{
		return ::ClientToScreen(m_hDlg, &point);
	}
	inline auto ClientToScreen(POINT* point)
	{
		return ::ClientToScreen(m_hDlg, point);
	}
	inline auto EndDialog(INT_PTR result)
	{
		return ::EndDialog(m_hDlg, result);
	}
	HWND m_hDlg;
}; 
