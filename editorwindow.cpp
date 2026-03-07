#include "stdafx.h"
#include <atldlgs.h>
#include <atlpath.h>
#include "resource.h"
#include "EditorWnd.h"
#include "AboutDlg.h"
#include "MainFrm.h"

void EditorWindow::ShowAutoComplete() 
{
	int pos = SendMessage(SCI_GETCURRENTPOS, 0, 0);
	int start = SendMessage(SCI_WORDSTARTPOSITION, pos, TRUE);
	int len = pos - start;

	if (len <= 0) return;

	char buf[128] = { 0 };
	Sci_TextRange tr;
	tr.chrg.cpMin = start;
	tr.chrg.cpMax = pos;
	tr.lpstrText = buf;

	SendMessage(SCI_GETTEXTRANGE, 0, (LPARAM)&tr);

	CString lang = m_pFrame->GetLanguage();
	std::string list;

	if (!lang.CompareNoCase(_T("vbscript"))) {
		list = BuildAutoList(buf);
		if (!list.empty())
			SendMessage(SCI_AUTOCSHOW, len, (LPARAM)list.c_str());
	}
	else if (!lang.CompareNoCase(_T("jscript"))) {
		list = BuildAutoListJScript(buf);
		if (!list.empty())
			SendMessage(SCI_AUTOCSHOW, len, (LPARAM)list.c_str());
	}
	else if (!lang.CompareNoCase(_T("python"))) {
		list = BuildAutoListPython(buf);
		if (!list.empty())
			SendMessage(SCI_AUTOCSHOW, len, (LPARAM)list.c_str());
	}
}