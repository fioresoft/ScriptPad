#include "stdafx.h"
#include <atlstr.h>
#include <MyString.h>
#include "Scintilla.h"
#include "ILexer.h"
#include "Lexilla.h"
#include "setvbscriptlexer.h"

typedef ILexer5* (*CreateLexerFn)(const char*);
void SetScriptLexer(HWND hSci, LPCTSTR language);

void SetVbScriptLexer(HWND hSci) {
    SetScriptLexer(hSci, _T("vbscript"));
}
void SetJSLexer(HWND hSci)
{
    SetScriptLexer(hSci, _T("js"));
    //SendMessage(hSci, SCI_SETLEXER, SCLEX_JAVASCRIPT, 0);
    //SendMessage(hSci, SCI_SETLEXER, SCLEX_CPP, 0);

}

void SetPythonLexer(HWND hSci)
{
    SetScriptLexer(hSci, _T("python"));
}

void SetScriptLexer(HWND hSci,LPCTSTR language)
{
// Carrega lexilla.dll
    HMODULE hLexilla = LoadLibrary(L"lexilla.dll");
    if (!hLexilla) {
        MessageBox(NULL, L"Não encontrou lexilla.dll", L"Erro", MB_ICONERROR);
        return;
    }

    // Obtém CreateLexer
    CreateLexerFn fnCreateLexer =
        (CreateLexerFn)GetProcAddress(hLexilla, "CreateLexer");

    if (!fnCreateLexer) {
        MessageBox(NULL, L"CreateLexer não encontrado em lexilla.dll", L"Erro", MB_ICONERROR);
        return;
    }

    // Cria o lexer 
    ILexer5* pLexer = fnCreateLexer(CT2A(language));
    if (!pLexer) {
        ::MessageBox(GetDesktopWindow(), NO5TL::GetErrorDesc(GetLastError()), _T("erro"), MB_ICONERROR);
    }
    // Aplica no Scintilla
    SendMessage(hSci, SCI_SETILEXER, 0, (sptr_t)pLexer);

}