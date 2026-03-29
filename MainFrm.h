// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include <atlframe.h>
#include <atlctrls.h>
#include "resource.h"
#include "ClipBoard.h"
#include "utf8.h"
#include "ScriptHostApp.h"
#include "setvbscriptlexer.h"
#include "Pane.h"


class COutput : public CWindowImpl<COutput,CEdit>, public CEditCommands<COutput>
{
public:
	BEGIN_MSG_MAP(COutput)
		CHAIN_MSG_MAP_ALT(CEditCommands<COutput>,1)
	END_MSG_MAP()

	BOOL CanPaste()
	{
		// TODO check clipboard for text
		NO5TL::CClipBoard cb(m_hWnd);

		return cb.IsFormatAvailable(CF_TEXT);
	}
};

class CMainFrame :
	public CFrameWindowImpl<CMainFrame>,
	public CUpdateUI<CMainFrame>,
	public CMessageFilter, 
	public CIdleHandler,
	public CEditFileCommands<EditorWindow>
{
	
	CString m_language; // extension with dot
	CStatusBarCtrl m_status;
	CCommandBarCtrl m_CmdBar;
	CHorSplitterWindow m_client;
	COutput m_output;
	//CPaneContainer m_pane;
	CToolBarCtrl m_toolbar, m_toolbar2;
public:
	CTabView m_view;
private:

	// TODO this should be in the CPane window
	void RunScript(const char* codeUtf8, HWND hWnd) {
		CStringW wide = utf8_to_wide_char(codeUtf8);

		if (GetPane()) {
			HRESULT hr = GetPane()->GetSite()->Run();
			if (SUCCEEDED(hr)) {
				hr = GetPane()->GetSite()->AddScript(wide);
			}
			ATLASSERT(SUCCEEDED(hr));
		}
	}
	BOOL CreatePaneContainer()
	{
		/*
		BOOL res = FALSE;

		if (m_client.IsWindow()) {
			m_pane.Create(m_hWnd);
			if (m_output.IsWindow()) {
				m_pane.SetClient(m_output);
				m_pane.SetTitle(_T("output"));
				res = TRUE;
			}
		}
		return res;
		*/
		return TRUE;
	}
	BOOL CreateTabView(HWND hWndParent)
	{
		m_view.Create(m_client,rcDefault, (LPCTSTR)0, WS_CHILD | WS_VISIBLE | \
			WS_CLIPCHILDREN | WS_CLIPSIBLINGS, WS_EX_CLIENTEDGE);
		return m_view.IsWindow();
	}

public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)
	CMainFrame():CEditFileCommands<EditorWindow>(this)
	{
		//
	}

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if (CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
			return TRUE;

		if(GetPane())
			return GetPane()->GetEditor().PreTranslateMessage(pMsg);
		return FALSE;
	}

	virtual BOOL OnIdle()
	{
		CPane* pPane = nullptr;
		int idx = m_view.GetActivePage();
		if(idx >= 0)
			pPane = (CPane *)m_view.GetPageData(idx);

		if (pPane && pPane->IsWindow()) {
			// CUT and COPY depend on selection
			BOOL canCut = (GetFocus() == pPane->GetEditor().m_hWnd) ?\
				pPane->GetEditor().CanCut() : m_output.CanCut();
			BOOL canCopy = (GetFocus() == pPane->GetEditor().m_hWnd) ? \
				pPane->GetEditor().CanCopy() :m_output.CanCopy();
			UIEnable(ID_EDIT_CUT, canCut);
			UIEnable(ID_EDIT_COPY, canCopy);

			// PASTE depends on clipboard contents
			BOOL canPaste = (GetFocus() == pPane->GetEditor().m_hWnd) ? \
				pPane->GetEditor().CanPaste() :m_output.CanPaste();
			UIEnable(ID_EDIT_PASTE, canPaste);
			UIEnable(ID_SCRIPT_RUN, pPane->GetEditor().GetWindowTextLength() != 0);
			UISetCheck(ID_VIEW_TOOLBAR, m_toolbar.IsWindowVisible());
			UISetCheck(ID_VIEW_STATUSBAR, m_status.IsWindowVisible());
			UISetCheck(ID_VIEW_OUTPUT, m_output.IsWindowVisible());
		}

		UIUpdateToolBar(TRUE);   // apply changes to toolbar/menubar
		return TRUE;             // keep getting idle calls

	}

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		UPDATE_ELEMENT(ID_EDIT_CUT, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_EDIT_COPY, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_EDIT_PASTE, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_VIEW_TOOLBAR,UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_STATUSBAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_OUTPUT, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()


	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_TIMER,OnTimer)
		COMMAND_ID_HANDLER(ID_FILE_NEW,OnFileNew)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(ID_SCRIPT_RUN, OnScriptRun)
		COMMAND_ID_HANDLER(ID_SCRIPT_STOP, OnScriptStop)
		COMMAND_RANGE_HANDLER(ID_LANGUAGE_JSCRIPT, ID_LANGUAGE_PYTHONSCRIPT, OnLanguage)
		COMMAND_ID_HANDLER(ID_LANGUAGE_JSCRIPT, OnLanguageJScript)
		COMMAND_ID_HANDLER(ID_LANGUAGE_VBSCRIPT, OnLanguageVBScript)
		COMMAND_ID_HANDLER(ID_LANGUAGE_PYTHONSCRIPT, OnLanguagePython)
		//COMMAND_ID_HANDLER(ID_PANE_CLOSE,OnPaneClose)
		COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR,OnViewToolbar)
		COMMAND_ID_HANDLER(ID_VIEW_STATUSBAR, OnViewStatusbar)
		COMMAND_ID_HANDLER(ID_VIEW_OUTPUT, OnViewOutput)
		COMMAND_ID_HANDLER(ID_FILE_NEW,OnFileNew)
		if (GetFocus() == m_output) {
			CHAIN_COMMANDS_MEMBER(m_output)
		}
		else if (GetPane() /* && GetPane()->GetEditor().m_hWnd == GetFocus()*/) {
			CHAIN_COMMANDS_MEMBER(GetPane()->GetEditor())
		}
		//CHAIN_COMMANDS_ALT(CEditFileCommands<EditorWindow>,2)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

	CPane* GetPane()
	{
		if (m_view.IsWindow()) {
			int idx = m_view.GetActivePage();
			if (idx >= 0) {
				CPane* pane = (CPane*)m_view.GetPageData(idx);
				return pane;
			}
		}
		return NULL;
	}
	void SetLanguage(LPCTSTR ext)
	{
		if (lstrcmpi(m_language, ext)) {
			CMenuHandle menu = m_CmdBar.GetMenu();
			CMenuHandle pop = menu.GetSubMenu(2);
			WORD id = ID_LANGUAGE_VBSCRIPT;
			HRESULT hr = S_OK;
			if (SUCCEEDED(hr)) {
				LPCTSTR lang = _T("VBScript");

				if (!lstrcmpi(ext, _T(".vbs")) || !lstrlen(ext)) {
					lang = _T("VBScript");
					id = ID_LANGUAGE_VBSCRIPT;
					const char* keywords =
						"and byref byval call case class const dim do each else elseif end "
						"erase error event exit explicit false for function get goto if in let loop "
						"me new next not nothing on option or property private public redim rem "
						"select set sub then true until wend while with";

					if (GetPane()) {
						SetVbScriptLexer(GetPane()->GetEditor().m_hWnd);
						GetPane()->GetEditor().SendMessage(SCI_SETKEYWORDS, 0, (LPARAM)keywords);
					}

				}
				else if (!lstrcmpi(ext, _T(".js"))) {
					lang = _T("JScript");
					id = ID_LANGUAGE_JSCRIPT;
					const char* words =
						"break case catch continue debugger default delete do else finally for "
						"function if in instanceof new return switch this throw try typeof var "
						"void while with true false null undefined";

					if (GetPane()) {
						SetJSLexer(GetPane()->GetEditor().m_hWnd);
						GetPane()->GetEditor().SendMessage(SCI_SETKEYWORDS, 0, (LPARAM)words);
					}

				}
				else if (!lstrcmpi(ext, _T(".pys")) || !lstrcmpi(ext, _T(".py"))) {
					lang = _T("python");
					id = ID_LANGUAGE_PYTHONSCRIPT;
					const char* words = "False None True and as assert async await break class continue def del " "elif else except finally for from global if import in is lambda nonlocal " "not or pass raise return try while with yield";
					if (GetPane()) {
						SetPythonLexer(GetPane()->GetEditor().m_hWnd);
						GetPane()->GetEditor().SendMessage(SCI_SETKEYWORDS, 0, (LPARAM)words);
					}

				}
				m_language = lang;
				pop.CheckMenuRadioItem(ID_LANGUAGE_JSCRIPT,
					ID_LANGUAGE_PYTHONSCRIPT, id, MF_BYCOMMAND);
				if (SUCCEEDED(hr)) {
					m_status.SetText(0, m_language);
				}
			}
		}
	}
	LPCTSTR GetLanguage()
	{
		return m_language;
	}
	void SetPath(CPath path)
	{
		if (GetPane())
			GetPane()->SetPath(path);
		m_status.SetText(1, (LPCTSTR)path, SBT_POPOUT);
	}

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
		m_toolbar.Attach(hWndToolBar);

		CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
		AddSimpleReBarBand(hWndCmdBar);
		AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

		HWND hToolBar2 = CreateSimpleToolBarCtrl(m_hWnd, IDR_TOOLBAR1, TRUE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);
		AddSimpleReBarBand(hToolBar2,NULL,TRUE);
		m_toolbar2.Attach(hToolBar2);

		CreateSimpleStatusBar();
		m_status.Attach(m_hWndStatusBar);
		UIAddToolBar(hWndToolBar);
		UIAddToolBar(hToolBar2);
		UIAddMenuBar(m_CmdBar);
		

		m_hWndClient = m_client.Create(m_hWnd,0,0,CControlWinTraits::GetWndStyle(0),
			CControlWinTraits::GetWndExStyle(WS_EX_CLIENTEDGE));
		//m_view.Create(m_client, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);
		BOOL res = CreateTabView(m_hWnd);
		ATLASSERT(res);
		if (res) {
			OnFileNew(0, 0, NULL, res);
		}
		m_output.Create(m_client, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS |ES_LEFT | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL, WS_EX_CLIENTEDGE);
		//res = CreatePaneContainer();
		ATLASSERT(res);
		m_client.SetSplitterPanes(m_view, m_output);
		//CRect rc; GetClientRect(&rc);
		//m_client.SetSplitterDefaultPosPct(70);
		m_client.SetSplitterPosPct(70);
		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);
		UIUpdateToolBar(TRUE);
		SetLanguage(_T(".vbs"));

		CRect rc; GetClientRect(&rc);
		int parts[] = { rc.Width() / 2,rc.Width() };
		m_status.SetParts(2, parts);

		
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
		if(GetPane())
			GetPane()->GetApp()->Fire_OnTimer(wParam);
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
	LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CPane* pPane = new CPane(this, m_output);
		pPane->Create(m_view, rcDefault, 0, WS_CHILD | WS_VISIBLE | \
			WS_VSCROLL | WS_HSCROLL);
		m_view.AddPage(pPane->m_hWnd, _T("Editor"));
		int idx = m_view.GetActivePage();
		m_view.SetPageData(idx, pPane);
		pPane->SetLanguage(_T(".vbs"));
		SetLanguage(_T(".vbs"));
		return 0;
	}
	LRESULT OnScriptRun(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if (GetPane())
		{
			EditorWindow& editor = GetPane()->GetEditor();
			int len = editor.SendMessage(SCI_GETTEXTLENGTH, 0, 0);
			std::string text(len + 1, '\0');
			editor.SendMessage(SCI_GETTEXT, len + 1, (LPARAM)text.data());
			CComQIPtr<IDispatch> spApp = (IDispatch*)(IScriptHostApp*)(GetPane()->GetApp());
			CComPtr<IDispatch> spBeeper;

			GetPane()->GetSite()->Init(spApp, spBeeper,m_language, m_hWnd);
			GetPane()->GetApp()->Init(m_hWnd, m_output);
			RunScript(text.c_str(), m_hWnd);
		}
		return 0;

	}
	LRESULT OnScriptStop(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if (GetPane()) {
			GetPane()->GetSite()->Terminate();
		}
		return 0;
	}
	LRESULT OnLanguageVBScript(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if (GetPane()) {
			SetLanguage(_T(".vbs"));
			GetPane()->SetLanguage(_T(".vbs"));
		}
		return 0;
	}
	LRESULT OnLanguageJScript(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if (GetPane()) {
			SetLanguage(_T(".js"));
			GetPane()->SetLanguage(_T(".js"));
		}
		return 0;
	}
	LRESULT OnLanguagePython(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if (GetPane()) {
			SetLanguage(_T(".pys"));
			GetPane()->SetLanguage(_T(".pys"));
		}
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
	void OnUpdateUI(UINT, WPARAM, LPARAM, BOOL&)
	{
		if (GetPane()) {
			// CUT and COPY depend on selection
			BOOL canCut = GetPane()->GetEditor().CanCut();
			BOOL canCopy = GetPane()->GetEditor().CanCopy();

			UIEnable(ID_EDIT_CUT, canCut);
			UIEnable(ID_EDIT_COPY, canCopy);

			// PASTE depends on clipboard contents
			BOOL canPaste = GetPane()->GetEditor().CanPaste();
			UIEnable(ID_EDIT_PASTE, canPaste);
		}
	}
	LRESULT OnViewToolbar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled)
	{
		static BOOL bVisible = TRUE;

		bVisible = !bVisible;
		if (bVisible) {
			m_toolbar.ShowWindow(SW_SHOW);
		}
		else
			m_toolbar.ShowWindow(SW_HIDE);
		
		return 0;
	}
	LRESULT OnViewStatusbar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled)
	{
		BOOL bNew = !::IsWindowVisible(m_status);
		::ShowWindow(m_status, bNew ? SW_SHOWNOACTIVATE : SW_HIDE);
		UISetCheck(ID_VIEW_STATUSBAR, bNew);
		UpdateLayout();
		return 0;
	}
	LRESULT OnViewOutput(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled)
	{
		BOOL bNew = !::IsWindowVisible(m_output);
		::ShowWindow(m_output, bNew ? SW_SHOWNOACTIVATE : SW_HIDE);
		UISetCheck(ID_VIEW_OUTPUT, bNew);
		UpdateLayout();
		
		if (bNew) {
			m_client.SetSinglePaneMode();
			m_client.SetSplitterPanes(m_view, m_output);
			m_client.SetSplitterPosPct(70);
		}
		else {
			m_client.SetSinglePaneMode(SPLIT_PANE_TOP);
		}
		return 0;
	}
	
};

