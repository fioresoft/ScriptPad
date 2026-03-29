#include "stdafx.h"
#include <atldlgs.h>
#include <atlctrls.h>
#include "resource.h"
#include "AboutDlg.h"
#include "EditorWnd.h"
#include "MainFrm.h"
#include "Pane.h"
#include "view.h"

LRESULT CPane::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CreateEditor();
	HRESULT hr = CComObject<CMyScriptSite>::CreateInstance(&m_pSite);
	ATLASSERT(SUCCEEDED(hr));
	m_pSite->AddRef();
	hr = CComObject<CScriptHostApp>::CreateInstance(&m_pApp);
	if (SUCCEEDED(hr)) {
		m_pApp->AddRef();
		m_pApp->Init(m_pFrame->m_hWnd, m_output);
	}
	ATLASSERT(SUCCEEDED(hr));
	m_pFrame->SetLanguage(_T(".vbs"));
	m_editor.SendMessage(SCI_SETMARGINTYPEN, 0, SC_MARGIN_NUMBER);
	m_editor.SendMessage(SCI_SETMARGINWIDTHN, 0, 40);

	return 0;
}
LRESULT CPane::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_pSite->Terminate();
	m_pSite->Release();
	m_pSite = NULL;
	m_pApp->Release();
	m_pApp = NULL;
	int idx = m_pFrame->m_view.GetActivePage();
	if(idx >= 0)
		m_pFrame->m_view.SetPageData(idx, NULL);
	return 0;
}
void CPane::SetPath(const CPath& path)
{
	m_path = path;
	int nPos = m_path.FindFileName();
	CString title = m_path.m_strPath.Right(m_path.m_strPath.GetLength() - nPos);
	m_pFrame->m_view.SetPageTitle(m_pFrame->m_view.GetActivePage(), title);
	m_pFrame->SetLanguage(path.GetExtension());
	SetLanguage(path.GetExtension());
}

void CPane::SetLanguage(LPCTSTR lang)
{
	HRESULT hr = S_OK;
	m_language = lang;
	if (!m_language.CompareNoCase(_T(".vbs")))
		m_language = _T("vbscript");
	else if (!m_language.CompareNoCase(_T(".js")))
		m_language = _T("jscript");
	else if (!m_language.CompareNoCase(_T(".pys")))
		m_language = _T("python");
	else if (!m_language.CompareNoCase(_T(".py")))
		m_language = _T("python");

	if (m_pSite) {
		HRESULT hr = m_pSite->Terminate();
	}
	if (SUCCEEDED(hr)) {
		m_pSite->Release();
		m_pSite = NULL;
		hr = CComObject<CMyScriptSite>::CreateInstance(&m_pSite);
		if (SUCCEEDED(hr)) {
			m_pSite->AddRef();
			if (m_pApp == NULL) {
				hr = CComObject<CScriptHostApp>::CreateInstance(&m_pApp);
				m_pApp->AddRef();
				m_pApp->Init(m_pFrame->m_hWnd, m_output);
			}
			CComPtr<IDispatch> spApp = (IDispatch*)(IScriptHostApp*)m_pApp;
			CComPtr<IDispatch> disp;	// TODO eliminar o beeper
			hr = m_pSite->Init(spApp, disp, m_language, m_hWnd);
			spApp.Detach();
		}
	}
	ATLASSERT(SUCCEEDED(hr));
}