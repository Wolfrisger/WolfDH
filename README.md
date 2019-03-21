# WolfDH
Wolf C++ Driver Helper Namespace

Just a Simple Driver Helper to use C++ Vector, map and string/wstring in Win32 Driver. Currently uses for printer only.

1.template<class T> class WFvector
a normal vector with no single delete function (yet)

2.template<class _Key, class _Data> class WFSimpleMap
a simple map with no delete function

3.class WFstring
a wchar_t* string

4.class WFcstring
a char* string

usage:

	#include <WolfDriverHelper.h>
	using namespace WolfDH;

	int main()
	{
		WFvector<int> vec1{1,2,3};
		WFvector<int> vec2 = {1,2,3};
		WFstring str = L"TEST";
		WFcstring cstr = "TEST";
		WFvector<WFstring> vecstr{L"Test", L"Test2"};
		WFSimpleMap<int, WFstring> mapIS = {{1,L"ABC"}, {2, DEF}};

		vec1.Add(3);
		for(auto& num :vec1)
		{
			//...
		}
		vec1.clear();
	}
	
5.class WolfWin32Dlg
a MFC like dialog class for Win32 program

usage:

in header:

	#include "WolfWin32Dlg.h"

	class CYourDlg : public CWolfWin32Dlg
	{
		DCL_WWDLGPROC(CYourDlg)
	public:
	virtual BOOL Procf(UINT uMsg, WPARAM wParam, LPARAM lParam);	//your proc function
	}

Implement:

	IMP_WWDLGPROC(CYourDlg)
	BOOL CYourDlg::Procf(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_INITDIALOG:
			//...
			break;
		case WM_DESTROY:
			//...
			break;
		}
	}
