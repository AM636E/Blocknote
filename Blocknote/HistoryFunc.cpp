#include "File.h"

void WriteVectorToList( const vector< string > vect, HWND list )
{
	for(auto i = 0; i < vect.size( ); i ++ )
	{
		SendMessage( list, LB_ADDSTRING, 0, reinterpret_cast<LPARAM >(vect[i].c_str( )) );
	}
}
HWND hwndHistory = 0;
BOOL OnHistoryInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam)
{
	hwndHistory = CreateWindow(
		"listbox",
		"",
		WS_VSCROLL | WS_BORDER | WS_CHILD | WS_VISIBLE,
		0, 0,
		300, 400,
		hDlg,
		0, 0, 0 );

	string a;
	string b;

	CreateWindow(
		"button",
		"OK",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		350, 0,
		60, 60,		
		hDlg,
		( HMENU ) IDOK,
		0, 0 );

	CreateWindow(
		"button",
		" Cancel ",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		350, 70,
		60, 60,
		hDlg,
		( HMENU ) IDCANCEL,
		0, 0 );

	
	vector< string > lines = GetLinesFromFile( HISTORY_FILE );
	WriteVectorToList( lines, hwndHistory );
	//SendMessage( hHistoryList, LB_ADDSTRING, 0, ( LPARAM ) " Hei " );

	return TRUE;
}

File file;

char GetPassChar( int index )
{
	ifstream rfile( PASSWD_FILE );

	char ch = 0;
	int i = 0;

	while( !rfile.eof( ) && i ++ <= index )
	{
		rfile >> ch;
	}

	rfile.close( );

	return ch;
}

void OnHistoryCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
	HWND par = GetParent( hDlg );

	hEdit = GetWindow( par, GW_CHILD );

	switch( id )
	{
	case IDOK:
		{
			int index = SendMessage( hwndHistory, LB_GETCURSEL, 0, 0 );

			int len = SendMessage( hwndHistory, LB_GETTEXTLEN, index, 0 );
			char* filename = new char[ len + 1 ];
			SendMessage( hwndHistory, LB_GETTEXT, index, ( LPARAM ) filename );

			filename[ strlen( filename ) ] = 0;
			file.isNew = false;			
			
			file.Open( filename );			
			file.Show( hEdit, par );
			file.SetPasschar( GetPassChar( index ) );

			file.isCrypted = true;

			break;
		}
	case IDCANCEL:
		{
			EndDialog( hDlg, 0 );
			hHistoryDlg = 0;

			break;
		}
	}
}