#pragma once
#include "stdafx.h"
#include "EditorWnd.h"

class CMainFrame;
class COutput;

class CPane :public CWindowImpl<CPane>
{
	EditorWindow m_editor;
	CComObject<CMyScriptSite>* m_pSite;
	CComObject<CScriptHostApp>* m_pApp;
	CComQIPtr<IActiveScriptSite> m_spSite;
	CPath m_path;
	COutput& m_output;
	CMainFrame* m_pFrame;
	CString m_language; // VBScript,JScript,Python
public:
	CPane(CMainFrame* pFrame, COutput& output) :m_pSite(nullptr), m_pApp(nullptr), m_output(output),
		m_pFrame(pFrame),m_editor(pFrame)
	{

	}
	DECLARE_WND_CLASS(NULL);
	BEGIN_MSG_MAP(CPane)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		COMMAND_ID_HANDLER(ID_DEBUG_STARTED, OnDebugStarted)
		COMMAND_ID_HANDLER(ID_DEBUG_PARSE, OnDebugParse)
		COMMAND_ID_HANDLER(ID_DEBUG_CONNECTED, OnDebugConnected)
		COMMAND_ID_HANDLER(ID_DEBUG_DISCONNECTED, OnDebugDisconnected)
		COMMAND_ID_HANDLER(ID_DEBUG_CLOSED, OnDebugClosed)
		CHAIN_MSG_MAP_MEMBER(m_editor)
	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CRect rc;
		GetClientRect(&rc);
		m_editor.MoveWindow(0, 0, rc.Width(), rc.Height());
		return 0;
	}
	LRESULT OnDebugStarted(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HRESULT hr = m_pSite->SetStarted();
		ATLASSERT(SUCCEEDED(hr));
		return 0;
	}
	LRESULT OnDebugConnected(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HRESULT hr = m_pSite->SetConnected();
		ATLASSERT(SUCCEEDED(hr));
		return 0;
	}
	LRESULT OnDebugParse(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int len = m_editor.SendMessage(SCI_GETTEXTLENGTH, 0, 0);
		std::string text(len + 1, '\0');
		m_editor.SendMessage(SCI_GETTEXT, len + 1, (LPARAM)text.data());
		CStringW wide = utf8_to_wide_char(text.c_str());

		HRESULT hr = m_pSite->AddScript(wide);
		ATLASSERT(SUCCEEDED(hr));
		return 0;
	}
	LRESULT OnDebugDisconnected(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HRESULT hr = m_pSite->SetDisconnected();
		ATLASSERT(SUCCEEDED(hr));
		return 0;
	}
	LRESULT OnDebugClosed(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		HRESULT hr = m_pSite->SetTerminated();
		ATLASSERT(SUCCEEDED(hr));
		return 0;
	}
	EditorWindow& GetEditor()
	{
		return m_editor;
	}
	void SetLanguage(LPCTSTR lang);
	CComObject<CScriptHostApp>* GetApp()
	{
		return m_pApp;
	}
	CComObject<CMyScriptSite>* GetSite()
	{
		return m_pSite;
	}
	void SetPath(const CPath& path);
	LPCTSTR GetLanguage(void)
	{
		return m_language;
	}
	BOOL CreateEditor()
	{
		m_editor.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | \
			WS_HSCROLL);
		return m_editor.IsWindow();
	}

};