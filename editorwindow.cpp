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
		const char* jsKeywords =
			"break case catch class const continue debugger default delete do else export extends "
			"finally for function if import in instanceof let new return super switch this throw "
			"try typeof var void while with yield await async "
			"true false null undefined "
			"Array Boolean Date Error Function JSON Math Number Object RegExp String Symbol Map Set WeakMap WeakSet "
			"console window document globalThis Promise Reflect Proxy Intl";

		SendMessage(SCI_AUTOCSETIGNORECASE, true, 0);
		SendMessage(SCI_AUTOCSETSEPARATOR, ' ', 0);
		SendMessage(SCI_AUTOCSETMAXHEIGHT, 12, 0);
		SendMessage(SCI_AUTOCSETMAXWIDTH, 50, 0);


		list = BuildAutoListJScript(buf,jsKeywords);
		if (!list.empty())
			SendMessage(SCI_AUTOCSHOW, len, (LPARAM)list.c_str());
	}
	else if (!lang.CompareNoCase(_T("python"))) {
		list = BuildAutoListPython(buf);
		if (!list.empty())
			SendMessage(SCI_AUTOCSHOW, len, (LPARAM)list.c_str());
	}
}