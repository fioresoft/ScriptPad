#pragma once
#include "stdafx.h"
#include "resource.h"
#include <atlbase.h>
#include <atlwin.h>
#include <atlstr.h>
#include <string>
#include "Scintilla.h"
#include "SciLexer.h"
#include "ILexer.h"
#include "Lexilla.h"
#include "setvbscriptlexer.h"
#include "utf8.h"   
#include <WinFile.h>
#include <DataBuffer.h>
#include <atlpath.h>

#define SH_FILTER _T("vbscript\0*.vbs\0jscript\0*.js\0python script\0*.pys\0python\0*.py\0all files\0*.*\0\0")


/*
void SetVbScriptLexer(HWND hSci) {
    ILexer5* pLexer = CreateLexer("vbscript");
    SendMessage(hSci, SCI_SETILEXER, 0, (sptr_t)pLexer);
}
*/
extern CAppModule _Module;
class CMainFrame;

template<class TEdit>
class CEditFileCommands
{
	CMainFrame* m_pFrame;
public:
	BEGIN_MSG_MAP(CEditFileCommands<TEdit>)
		ALT_MSG_MAP(2)
		COMMAND_ID_HANDLER(ID_FILE_SAVE, OnFileSave)
		COMMAND_ID_HANDLER(ID_FILE_SAVE_AS, OnFileSaveAs)
		COMMAND_ID_HANDLER(ID_FILE_OPEN, OnFileOpen)
		COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNew)
		COMMAND_CODE_HANDLER(EN_CHANGE, OnEditChange)
	END_MSG_MAP()
public:
	CEditFileCommands(CMainFrame* pFrame) :m_pFrame(pFrame)
	{
		m_bDirty = false;
	}
private:
	bool m_bDirty;
	CPath m_path;
	BOOL ShowFileOpen()
	{
		COMDLG_FILTERSPEC filter[] = { \
			_T("vbscript files"),_T("*.vbs"),
			_T("jscript files"), _T("*.js"),
			_T("python script files"), _T("*.pys"),
			_T("python files"), _T("*.py"),
			_T("all files"), _T("*.*")\
		};
		CShellFileOpenDialog dlg((CString&)m_path,6208UL,(LPCWSTR)0,
			filter,5); 
		BOOL res = FALSE;



		if (IDOK == dlg.DoModal()) {
			LPTSTR buf = m_path.m_strPath.GetBufferSetLength(256);
			HRESULT hr = dlg.GetFilePath(buf,256);
			if (SUCCEEDED(hr)) {
				TEdit* pEdit = (TEdit*)this;
#ifdef _DEBUG
				pEdit->MessageBox((LPCTSTR)m_path);
				pEdit->MessageBox(m_path.GetExtension());
#endif
				res = TRUE;
			}
			m_path.m_strPath.ReleaseBuffer();
		}
		return res;
	}
	BOOL ShowFileSave() {
		BOOL res = FALSE;
		COMDLG_FILTERSPEC filter[] = { \
			_T("vbscript files"),_T("*.vbs"),
			_T("jscript files"), _T("*.js"),
			_T("python script files"), _T("*.ps"),
			_T("python files"), _T("*.py"),
			_T("all files"), _T("*.*")\
		};
		CShellFileSaveDialog dlg;

		if (IDOK == dlg.DoModal()) {
			LPTSTR buf = m_path.m_strPath.GetBufferSetLength(256);
			HRESULT hr = dlg.GetFilePath(buf,256);
			if (SUCCEEDED(hr)) {
				res = TRUE;
			}
		}
		return res;
	}
	BOOL SaveToPath()
	{
		NO5TL::CWinFile wf;
		TEdit* pEdit = (TEdit*)this;
		CString s;
		NO5TL::CDataBuffer<char> db;

		s = pEdit->GetWindowText();
		CStringA ss = CT2A(s);
		db.Add((LPBYTE)(LPCSTR)ss, ss.GetLength());
		db.AddNull();
		BOOL res = FALSE;

		if (wf.Create(m_path, CREATE_ALWAYS)) {
			if (res = wf.Write(db)) {
				m_bDirty = false;
				res = TRUE;
			}
		}
		return res;
	}
public:
	LRESULT OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		TEdit* pEdit = (TEdit*)this;
		BOOL res = TRUE;
		int choice = IDNO;

		if (m_bDirty && pEdit->GetWindowTextLength()) {
			CString question;
			question.LoadStringW(IDS_SAVE);

			if (IDYES == (choice = pEdit->MessageBox(question, NULL, MB_YESNOCANCEL))) {
				CString path = m_path;
				if (path.IsEmpty()) {
					OnFileSaveAs(0, 0, 0, res);
				}
				else {
					OnFileSave(0, 0, 0, res);
				}
			}
		}
		if (choice != IDCANCEL && ShowFileOpen()) {
			NO5TL::CWinFile wf;
			BOOL res = wf.Create(m_path, OPEN_EXISTING, GENERIC_READ);

			if (res) {
				NO5TL::CDataBuffer<char> db;

				res = wf.ReadAll<char>(db, 0);
				if (res) {
					db.AddNull();
					TEdit* pEdit = (TEdit*)this;

					pEdit->SetWindowText(CA2T(db.GetData()));
					m_pFrame->SetPath(m_path);
					m_bDirty = false;
				}
			}
		}
		return 0;
	}
	LRESULT OnFileSaveAs(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if (ShowFileSave()) {
			if (SaveToPath()) {
				m_bDirty = false;
				m_pFrame->SetPath(m_path);
			}
		}
		return 0;
	}
	LRESULT OnFileSave(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if (m_path.GetExtension().IsEmpty()) {
			BOOL b;
			return OnFileSaveAs(0, 0, 0, b);
		}
		if (SaveToPath())
			m_bDirty = false;
		return 0;
	}
	LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		TEdit* pEdit = (TEdit*)this;
		BOOL res = TRUE;
		int choice;

		if (m_bDirty && pEdit->GetWindowTextLength()) {
			CString question;
			question.LoadStringW(IDS_SAVE);
			if (IDYES == (choice = pEdit->MessageBox(question, NULL, MB_YESNOCANCEL))) {
				CString path = m_path;
				if (path.IsEmpty()) {
					OnFileSaveAs(0, 0, 0, res);
				}
				else {
					OnFileSave(0, 0, 0, res);
				}
				pEdit->SetWindowText(_T(""));
				m_path.m_strPath = _T("");
				m_pFrame->SetPath(m_path);
			}
			else if (choice == IDNO) {
				pEdit->SetWindowText(_T(""));
			}

		}
		else
			pEdit->SetWindowText(_T(""));
		return 0;
	}
	LRESULT OnEditChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		m_bDirty = true;
		return 0;
	}
};
class CMainFrame;

class EditorWindow : public CWindowImpl<EditorWindow>,
	public CEditFileCommands<EditorWindow>,
	public CEditCommands<EditorWindow>,
	public CMessageFilter
{
public:
	DECLARE_WND_SUPERCLASS(NULL,_T("Scintilla"))
	CMainFrame* m_pFrame;

	EditorWindow(CMainFrame* pFrame) :CEditFileCommands<EditorWindow>(pFrame),
		m_pFrame(pFrame)
	{
		//
	}


    BEGIN_MSG_MAP(EditorWindow)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_NOTIFY, OnNotify)
        MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_DESTROY,OnDestroy)
		CHAIN_MSG_MAP_ALT(CEditCommands<EditorWindow>, 1)
		CHAIN_MSG_MAP_ALT(CEditFileCommands<EditorWindow>,2)
    END_MSG_MAP()

	LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL& bHandled) {

		//SendMessage(hSci, SCI_SETLEXER, SCLEX_VBSCRIPT, 0);
		LRESULT res = DefWindowProc();

		SendMessage(SCI_STYLESETFORE, SCE_B_KEYWORD, RGB(0, 0, 255));
		SendMessage(SCI_STYLESETFORE, SCE_B_STRING, RGB(163, 21, 21));
		SendMessage(SCI_STYLESETFORE, SCE_B_COMMENT, RGB(0, 128, 0));

		CMessageLoop *loop = _Module.GetMessageLoop();
		loop -> AddMessageFilter(this);

		return res;
	}
	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return FALSE;
	}

    std::string BuildAutoList(const char* prefix) {
        const char* words =
            "and byref byval call case class const dim do each else elseif end "
            "erase error event exit explicit false for function get goto if in let loop "
            "me new next not nothing on option or property private public redim rem "
            "select set sub then true until wend while with";

        std::string list;
        std::istringstream iss(words);
        std::string w;

        while (iss >> w) {
            if (w.rfind(prefix, 0) == 0) {
                if (!list.empty()) list += " ";
                list += w;
            }
        }
        return list;
    }
	std::string BuildAutoListJScript(const char* prefix) {
		const char* words =
			"break case catch continue debugger default delete do else finally for "
			"function if in instanceof new return switch this throw try typeof var "
			"void while with true false null undefined";

		std::string list;
		std::istringstream iss(words);
		std::string w;

		while (iss >> w) {
			if (w.rfind(prefix, 0) == 0) {
				if (!list.empty()) list += " ";
				list += w;
			}
		}
		return list;
	}

	std::string BuildAutoListPython(const char* prefix) {
		const char* words =
			"False None True and as assert async await break class continue def del "
			"elif else except finally for from global if import in is lambda nonlocal "
			"not or pass raise return try while with yield";

		std::string list;
		std::istringstream iss(words);
		std::string w;

		while (iss >> w) {
			if (w.rfind(prefix, 0) == 0) {
				if (!list.empty()) list += " ";
				list += w;
			}
		}
		return list;
	}



	void ShowAutoComplete();

	LRESULT OnDestroy(UINT, WPARAM wParam, LPARAM, BOOL& bHandled)
	{
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		pLoop->RemoveMessageFilter(this);
		bHandled = FALSE;
		return 0;
	}

    LRESULT OnNotify(UINT, WPARAM, LPARAM lParam, BOOL&) {
        SCNotification* scn = (SCNotification*)lParam;

        if (scn->nmhdr.hwndFrom == m_hWnd && scn->nmhdr.code == SCN_CHARADDED) {
            char ch = (char)scn->ch;
            if (isalnum((unsigned char)ch))
                ShowAutoComplete();
        }
        return 0;
    }

    LRESULT OnKeyDown(UINT, WPARAM wParam, LPARAM, BOOL& bHandled) {
        if ((GetKeyState(VK_CONTROL) & 0x8000) && wParam == 'R') {
            int len = SendMessage( SCI_GETTEXTLENGTH, 0, 0);
            std::string text(len + 1, '\0');
            SendMessage(SCI_GETTEXT, len + 1, (LPARAM)text.data());

            //RunVbScript(text.c_str(),m_hWnd);
        }
        else
            bHandled = FALSE;
        return 0;
    }
    BOOL SetWindowText(LPCTSTR psz)
    {
        CStringA utf8 = wide_to_utf8_char(psz);
		SendMessage(SCI_SETTEXT, (WPARAM)0, (LPARAM)(LPCSTR)utf8);
		return TRUE;
    }
    int GetWindowTextLength()
    {
        return SendMessage(SCI_GETTEXTLENGTH);
    }
    CStringA GetWindowText(void)
    {
        int len = GetWindowTextLength();
        CStringA s;
        LPCSTR p = s.GetBufferSetLength(len + 1);
        SendMessage(SCI_GETTEXT, (WPARAM)(len + 1),(LPARAM)p);
        return s;
    }
	void Copy()
	{
		SendMessage(SCI_COPY);
	}
	void Cut()
	{
		SendMessage(SCI_CUT);
	}
	void Paste()
	{
		SendMessage(SCI_PASTE);
	}
	void Undo()
	{
		SendMessage(SCI_UNDO);
	}
	void SetSel(int start, int end)
	{
		SendMessage(SCI_SETSEL, (WPARAM)start, (LPARAM)end);
	}
	void Clear()
	{
		SendMessage(SCI_CLEAR);
	}
	bool HasSelection()
	{
		return SendMessage(SCI_GETSELECTIONEND) > SendMessage(SCI_GETSELECTIONSTART);
	}
	bool CanCut()
	{
		return HasSelection();
	}
	bool CanCopy()
	{
		return CanCut();
	}
	bool CanPaste()
	{
		return SendMessage(SCI_CANPASTE) ? true : false;
	}
};
