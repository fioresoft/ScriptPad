#pragma once
#include <windows.h>
#include <atlbase.h>
#include <atlcom.h>
#include <atlcomcli.h>
#include <ScriptSite.h>
#include "beeper2026_i.h"
#include "ScriptHost5.h"

//void GetScriptEngines(CSimpleArray<CString>& vv);

class CMyScriptSite :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CScriptSiteImpl
{
	CComQIPtr<IBeeperObj2026> m_spBeeper;
	CComQIPtr<IScriptHostApp> m_spApp;
public:
	CMyScriptSite()
	{
		
	}
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CMyScriptSite)
		COM_INTERFACE_ENTRY(IActiveScriptSite)
		COM_INTERFACE_ENTRY(IActiveScriptSiteWindow)
	END_COM_MAP()
	HRESULT Init(CComPtr<IDispatch> spApp,CComPtr<IDispatch> spBeeper,LPCTSTR lang,HWND hwnd) {
		m_spBeeper = spBeeper;
		m_spApp = spApp;
		HRESULT hr = Initiate(lang, hwnd);
		if (SUCCEEDED(hr)) {
			//hr = AddObject(_T("beeper"), FALSE, TRUE);
			hr = AddObject(_T("app"), FALSE, TRUE);
		}
		ATLASSERT(SUCCEEDED(hr));
		return hr;
	}
	STDMETHOD(LookupNamedItem)(LPCOLESTR pstrName, LPUNKNOWN* ppunkItem)
	{
		CComBSTR name = pstrName;
		HRESULT hr = TYPE_E_ELEMENTNOTFOUND;

		/*
		if (name == OLESTR("beeper")) {
			ATLASSERT(ppunkItem != NULL);
			hr = m_spBeeper->QueryInterface(IID_IBeeperObj2026,(void **) ppunkItem);
		}
		*/
		if (name == OLESTR("app")) {
			ATLASSERT(ppunkItem != NULL);
			hr = m_spApp->QueryInterface(IID_IScriptHostApp, (void**)ppunkItem);
		}
		return hr;
	}
	STDMETHOD(GetItemInfo)(LPCOLESTR pstrName, DWORD dwMask, LPUNKNOWN* ppunkItem, LPTYPEINFO* ppTypeInfo)
	{
		CComPtr<IUnknown> spUnk;
		HRESULT hr = LookupNamedItem(pstrName, &spUnk);

		if (SUCCEEDED(hr)) {
			if (dwMask & SCRIPTINFO_ITYPEINFO) {
				CComPtr<ITypeInfo> spTI;
				CComQIPtr<IProvideClassInfo> spPCI = spUnk;
				if (!!spPCI) {
					// Got IProvideClassInfo interface so use it
					hr = spPCI->GetClassInfo(&spTI);
					spPCI.Release();
				}
				else {
					// Try for IDispatch::GetTypeInfo
					CComQIPtr<IDispatch> spDisp = spUnk;
					if (!!spDisp) {
						hr = spDisp->GetTypeInfo(0, LOCALE_SYSTEM_DEFAULT, &spTI);
						spDisp.Release();
					}
				}
				*ppTypeInfo = spTI.Detach();
			}
			if (dwMask & SCRIPTINFO_IUNKNOWN) {
				hr = spUnk->QueryInterface(IID_IUnknown, (void **)ppunkItem);
			}
		}
		return hr;
	}
};

