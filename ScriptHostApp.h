#pragma once
#include <atlstr.h>
#include <MyString.h>
#include "resource.h"
#include "ScriptHost5.h"
#include "_IScriptHostAppEvents_CP.h"
class ATL_NO_VTABLE CScriptHostApp :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CProxy_IScriptHostAppEvents<CScriptHostApp>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CScriptHostApp>,
	public IProvideClassInfo2Impl<&CLSID_ScriptHostApp, &DIID__IScriptHostAppEvents,&LIBID_ScriptHost,1,1>,
	public IDispatchImpl<IScriptHostApp, &IID_IScriptHostApp>,
	public IDispatchImpl<_IScriptHostAppEvents, &__uuidof(_IScriptHostAppEvents)>
{
	CWindow wndFrame, wndOutput;

	//DECLARE_REGISTRY_RESOURCEID(IDR_NO5IRCOBJ)
	DECLARE_REGISTRY_RESOURCEID(IDR_REGISTRY1);

	DECLARE_NOT_AGGREGATABLE(CScriptHostApp)

	BEGIN_COM_MAP(CScriptHostApp)
		COM_INTERFACE_ENTRY(IScriptHostApp)
		COM_INTERFACE_ENTRY2(IDispatch, IScriptHostApp)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY(_IScriptHostAppEvents)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CScriptHostApp)
		CONNECTION_POINT_ENTRY(__uuidof(_IScriptHostAppEvents))
	END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	void Init(HWND hWndMainFrame, HWND hWndOutput) {
		ITypeLib* ptl = NULL;
		HRESULT hr = LoadTypeLib(OLESTR("ScriptHost5.tlb"),&ptl);
		//HRESULT hr = LoadRegTypeLib(LIBID_ScriptHost, 1, 0, LOCALE_ALL, &ptl);
		if (SUCCEEDED(hr)) {
			ptl->Release();
			//hr = UpdateRegistry(FALSE);
		}
		ATLASSERT(SUCCEEDED(hr));
		if (FAILED(hr)) {
			MessageBox(GetDesktopWindow(), NO5TL::GetErrorDesc(hr), _T("Title"), MB_ICONERROR);
		}
		wndFrame = hWndMainFrame;
		wndOutput = hWndOutput;
	}
	// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		// TODO
		return S_OK;
	}
	STDMETHOD(Output)(BSTR msg)
	{
		HRESULT hr = S_OK;
		CComBSTR bstr = msg;
		CString s = bstr;
		CEdit edit(wndOutput.m_hWnd);
		edit.AppendText(s);
		return hr;
	}
	STDMETHOD(SetTimer)(LONG id, LONG ms, LONG* pRes)
	{
		if (ms == 0) {
			wndFrame.KillTimer(id);
			return S_OK;
		}
		*pRes = wndFrame.SetTimer(id, ms);
		return S_OK;
	}
	STDMETHOD(Beep)(LONG ms, LONG f)
	{
		::Beep(f, ms);
		return S_OK;
	}
	STDMETHOD(Box)(BSTR msg)
	{
		CString s = msg;
		wndFrame.MessageBox(s);
		return S_OK;
	}
};