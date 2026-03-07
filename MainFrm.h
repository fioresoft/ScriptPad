// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "resource.h"
#include "utf8.h"
#include "ScriptHostApp.h"

class COutput : public CWindowImpl<COutput,CEdit>, public CEditCommands<COutput>
{
public:
	BEGIN_MSG_MAP(COutput)
		CHAIN_MSG_MAP_ALT(CEditCommands<COutput>,1)
	END_MSG_MAP()

	BOOL CanPaste()
	{
		// TODO check clipboard for text
		return TRUE;
	}
};

class CMainFrame :
	public CFrameWindowImpl<CMainFrame>,
	public CUpdateUI<CMainFrame>,
	public CMessageFilter, public CIdleHandler
{
	CComObject<CMyScriptSite>* m_pSite;
	CComQIPtr<IBeeperObj2026> m_spBeeper;
	CComQIPtr<IActiveScriptSite> m_spSite;
	CComObject<CScriptHostApp>* m_pApp;
	CPath m_path;
	CString m_language; // extension with dot
	EditorWindow m_view;
	CStatusBarCtrl m_status;
	CCommandBarCtrl m_CmdBar;
	CHorSplitterWindow m_client;
	COutput m_output;


	void RunScript(const char* codeUtf8, HWND hWnd) {
		CStringW wide = utf8_to_wide_char(codeUtf8);

		HRESULT hr = m_pSite->Run(); 
		if (SUCCEEDED(hr)) {
			hr = m_pSite->AddScript(wide);
		}
		ATLASSERT(SUCCEEDED(hr));
	}


public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)
	CMainFrame() :m_view(this),m_pApp(NULL)
	{
		//
	}

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if (CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
			return TRUE;

		return m_view.PreTranslateMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		
			// CUT and COPY depend on selection
		BOOL canCut = (GetFocus() == m_view.m_hWnd) ? m_view.CanCut() : \
			m_output.CanCut();
		BOOL canCopy = (GetFocus() == m_view.m_hWnd) ? m_view.CanCopy() : \
			m_output.CanCopy();
			UIEnable(ID_EDIT_CUT, canCut);
			UIEnable(ID_EDIT_COPY, canCopy);

			// PASTE depends on clipboard contents
			BOOL canPaste = (GetFocus() == m_view.m_hWnd) ? m_view.CanPaste() : \
				m_output.CanPaste();
			UIEnable(ID_EDIT_PASTE, canPaste);

			UIUpdateToolBar(TRUE);   // apply changes to toolbar/menubar
			return TRUE;             // keep getting idle calls

	}

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		UPDATE_ELEMENT(ID_EDIT_CUT, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_EDIT_COPY, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_EDIT_PASTE, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
	END_UPDATE_UI_MAP()


	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_TIMER,OnTimer)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(ID_SCRIPT_RUN, OnScriptRun)
		COMMAND_ID_HANDLER(ID_SCRIPT_STOP, OnScriptStop)
		COMMAND_RANGE_HANDLER(ID_LANGUAGE_JSCRIPT, ID_LANGUAGE_PYTHONSCRIPT, OnLanguage)
		COMMAND_ID_HANDLER(ID_LANGUAGE_JSCRIPT, OnLanguageJScript)
		COMMAND_ID_HANDLER(ID_LANGUAGE_VBSCRIPT, OnLanguageVBScript)
		COMMAND_ID_HANDLER(ID_LANGUAGE_PYTHONSCRIPT, OnLanguagePython)
		COMMAND_ID_HANDLER(ID_DEBUG_STARTED,OnDebugStarted)
		COMMAND_ID_HANDLER(ID_DEBUG_PARSE, OnDebugParse)
		COMMAND_ID_HANDLER(ID_DEBUG_CONNECTED, OnDebugConnected)
		COMMAND_ID_HANDLER(ID_DEBUG_DISCONNECTED, OnDebugDisconnected)
		COMMAND_ID_HANDLER(ID_DEBUG_CLOSED, OnDebugClosed)
		NOTIFY_CODE_HANDLER(SCN_CHARADDED, OnSciNotify)
		if(GetFocus() == m_output)
			CHAIN_COMMANDS_MEMBER(m_output)
		CHAIN_COMMANDS_MEMBER(m_view)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// create command bar window
		HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
		// attach menu
		m_CmdBar.AttachMenu(GetMenu());
		// load command bar images
		m_CmdBar.LoadImages(IDR_MAINFRAME);
		// remove old menu
		SetMenu(NULL);

		HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

		CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
		AddSimpleReBarBand(hWndCmdBar);
		AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

		HWND hToolBar2 = CreateSimpleToolBarCtrl(m_hWnd, IDR_TOOLBAR1, TRUE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);
		AddSimpleReBarBand(hToolBar2,NULL,TRUE);

		CreateSimpleStatusBar();
		m_status.Attach(m_hWndStatusBar);
		UIAddToolBar(hWndToolBar);
		UIAddToolBar(hToolBar2);
		UIAddMenuBar(m_CmdBar);
		

		m_hWndClient = m_client.Create(m_hWnd);
		m_view.Create(m_client, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);

		ATLASSERT(m_view.IsWindow());
		m_output.Create(m_client, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS |ES_LEFT | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL, WS_EX_CLIENTEDGE);
		m_client.SetSplitterPanes(m_view, m_output);
		//CRect rc; GetClientRect(&rc);
		m_client.SetSplitterDefaultPosPct(70);
		m_client.SetSplitterPosPct(70);
		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);
		UIUpdateToolBar(TRUE);

		HRESULT hr = CComObject<CMyScriptSite>::CreateInstance(&m_pSite);
		ATLASSERT(SUCCEEDED(hr));
		m_spSite = m_pSite;
		hr = m_spBeeper.CoCreateInstance(OLESTR("my.beeperobj2026"));
		if (SUCCEEDED(hr)) {
			CComQIPtr<IDispatch> spBeeper = m_spBeeper;
		}
		hr = CComObject<CScriptHostApp>::CreateInstance(&m_pApp);
		if (SUCCEEDED(hr)) {
			CComQIPtr<IDispatch> spBeeper = m_spBeeper;
			CComQIPtr<IDispatch> spApp = (IDispatch *)(IScriptHostApp *)m_pApp;
			hr = m_pSite->Init(spApp, spBeeper, _T("VBScript"), m_hWnd);
			m_pApp->Init(m_hWnd, m_output.m_hWnd);
			m_pApp->AddRef();
		}
		ATLASSERT(SUCCEEDED(hr));
		SetLanguage(_T(".vbs"));

		m_view.SendMessage(SCI_SETMARGINTYPEN, 0, SC_MARGIN_NUMBER); 
		m_view.SendMessage(SCI_SETMARGINWIDTHN, 0, 40);

		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		// unregister message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(this);
		pLoop->RemoveIdleHandler(this);

		bHandled = FALSE;
		return 1;
	}

	LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		m_pApp->Fire_OnTimer(wParam);
		return 0;
	}

	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		PostMessage(WM_CLOSE);
		return 0;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}
	LRESULT OnScriptRun(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int len = m_view.SendMessage(SCI_GETTEXTLENGTH, 0, 0);
		std::string text(len + 1, '\0');
		m_view.SendMessage(SCI_GETTEXT, len + 1, (LPARAM)text.data());
		CComQIPtr<IDispatch> spApp = (IDispatch *)(IScriptHostApp *)m_pApp;
		CComPtr<IDispatch> spBeeper;

		m_pSite->Init(spApp, spBeeper, GetLanguage(), m_hWnd);
		RunScript(text.c_str(), m_hWnd);
		return 0;

	}
	LRESULT OnScriptStop(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		m_pSite->Terminate();
		return 0;
	}
	LRESULT OnLanguageVBScript(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		SetLanguage(_T(".vbs"));
		return 0;
	}
	LRESULT OnLanguageJScript(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		SetLanguage(_T(".js"));
		return 0;
	}
	LRESULT OnLanguagePython(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		SetLanguage(_T(".pys"));
		return 0;
	}
	LRESULT OnLanguage(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& bHandled)
	{
		CMenuHandle menu = m_CmdBar.GetMenu();
		CMenuHandle pop = menu.GetSubMenu(2);

		pop.CheckMenuRadioItem(ID_LANGUAGE_JSCRIPT, ID_LANGUAGE_PYTHONSCRIPT,
			wID, MF_BYCOMMAND);
		bHandled = FALSE;
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
		int len = m_view.SendMessage(SCI_GETTEXTLENGTH, 0, 0);
		std::string text(len + 1, '\0');
		m_view.SendMessage(SCI_GETTEXT, len + 1, (LPARAM)text.data());
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

	LRESULT OnSciNotify(int, LPNMHDR pnmh, BOOL&)
	{ 
		SCNotification* scn = (SCNotification*)pnmh;
		if (scn->nmhdr.code == SCN_CHARADDED)
			m_view.ShowAutoComplete(); 
		return 0; 
	}
	void OnUpdateUI(UINT, WPARAM, LPARAM, BOOL&)
	{
		// CUT and COPY depend on selection
		BOOL canCut = m_view.CanCut();
		BOOL canCopy = m_view.CanCopy();

		UIEnable(ID_EDIT_CUT, canCut);
		UIEnable(ID_EDIT_COPY, canCopy);

		// PASTE depends on clipboard contents
		BOOL canPaste = m_view.CanPaste();
		UIEnable(ID_EDIT_PASTE, canPaste);
	}

	void SetPath(const CPath& path)
	{
		m_path = path;
		int nPos = m_path.FindFileName();
		CString title = m_path.m_strPath.Right(m_path.m_strPath.GetLength() - nPos);
		SetWindowText(title);
		SetLanguage(path.GetExtension());
	}
	void SetLanguage(LPCTSTR ext)
	{
		if (lstrcmpi(m_language, ext)) {
			//HRESULT hr = CComObject <CMyScriptSite>::CreateInstance(&m_pSite);
			CMenuHandle menu = m_CmdBar.GetMenu();
			CMenuHandle pop = menu.GetSubMenu(2);
			WORD id = ID_LANGUAGE_VBSCRIPT;
			HRESULT hr = S_OK;
			if (SUCCEEDED(hr)) {
				LPCTSTR lang = _T("");

				if (!lstrcmpi(ext, _T(".vbs")) || !lstrlen(ext)) {
					lang = _T("VBScript");
					id = ID_LANGUAGE_VBSCRIPT;
					const char* keywords =
						"and byref byval call case class const dim do each else elseif end "
						"erase error event exit explicit false for function get goto if in let loop "
						"me new next not nothing on option or property private public redim rem "
						"select set sub then true until wend while with";

						SetVbScriptLexer(m_view.m_hWnd);
						m_view.SendMessage(SCI_SETKEYWORDS, 0, (LPARAM)keywords);
						
				}
				else if (!lstrcmpi(ext, _T(".js"))) {
					lang = _T("JScript");
					id = ID_LANGUAGE_JSCRIPT;
					const char* words =
							"break case catch continue debugger default delete do else finally for "
							"function if in instanceof new return switch this throw try typeof var "
							"void while with true false null undefined";

					SetJSLexer(m_view.m_hWnd);
					m_view.SendMessage(SCI_SETKEYWORDS, 0, (LPARAM)words);

				}
				else if (!lstrcmpi(ext, _T(".pys")) || !lstrcmpi(ext,_T(".py"))) {
					lang = _T("python");
					id = ID_LANGUAGE_PYTHONSCRIPT;
					const char* words = "False None True and as assert async await break class continue def del " "elif else except finally for from global if import in is lambda nonlocal " "not or pass raise return try while with yield";
					SetPythonLexer(m_view.m_hWnd);
					m_view.SendMessage(SCI_SETKEYWORDS, 0, (LPARAM)words);
					
				}
				m_status.SetText(0, lang);
				pop.CheckMenuRadioItem(ID_LANGUAGE_JSCRIPT,
					ID_LANGUAGE_PYTHONSCRIPT, id, MF_BYCOMMAND);
				//if (lstrcmpi(m_language, lang)) {
					//m_spSite = m_pSite;
				CComQIPtr<IDispatch> disp;// = m_spBeeper;
				CComQIPtr<IDispatch> spApp = (IDispatch *)(IScriptHostApp *)m_pApp;
				hr = m_pSite->Terminate();
				if (SUCCEEDED(hr)) {
					hr = m_pSite->Init(spApp,disp, lang, m_hWnd);
					if (SUCCEEDED(hr))
						m_language = lang;
				}
				ATLASSERT(SUCCEEDED(hr));
			}

		}
	}
	LPCTSTR GetLanguage(void)
	{
		return m_language;
	}
};
