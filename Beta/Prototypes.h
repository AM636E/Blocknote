#pragma once
#include "Globals.h"
#include "resource.h"

//Main window procedures :
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnSize(HWND hwnd, UINT state, int cx, int cy);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnDestroy( HWND hWnd );
//...
LRESULT CALLBACK RegisterDlgProc( HWND hDlgProc, UINT message, WPARAM wParam, LPARAM lParam );
//Register dialog Procedures:
LRESULT CALLBACK FindReplaceDlgProc( HWND hDlfProc, UINT message, WPARAM wParam, LPARAM lParam );
BOOL OnRegInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam);
void OnRegCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify);
//...

//Find / Replace dialog procedures
LRESULT CALLBACK FindReplaceDlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam );
BOOL OnFRInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam);
void OnFRCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify);
//...

//History dialog:
LRESULT CALLBACK HistoryDlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam );
BOOL OnHistoryInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam);
void OnHistoryCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify);
//...

int GetCountOfCharacters( const char *filename );

char *GetInfFromFile( const char *filename );

bool WriteNSaveFile( const char *filename, const char *inf );

void FillOpenSave( OPENFILENAME& ofn, HWND hOwner, char *filter, char *defext );
void SaveFile( HWND hwndEdit, char *filename );
char *GetTextFromEdit( HWND hEdit );

char *CodeDecodeText( const char* text );
char *DecodeText( const char* text, int password );

int GetLastCharPos( const char* str, const char ch );

void AddStrToList( vector< string >& list, const char *str );
void WriteVectorToList( const vector< string > vect, HWND list );
