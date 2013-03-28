#include "Prototypes.h"

void WriteVectorToList( const vector< string > vect, HWND list )
{
	for( int i = 0; i < vect.size( ); i ++ )
	{
		SendMessage( list, LB_ADDSTRING, 0, ( LPARAM ) vect[ i ].c_str( ) );
	}
}

BOOL OnHistoryInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam)
{
	hHistoryList = CreateWindow(
		"listbox",
		"",
		LBS_STANDARD | WS_VSCROLL | WS_CHILD,
		0, 0,
		200, 100,
		hDlg,
		( HMENU )IDL_HISTORY_LIST,
		0, 0 );

	CreateWindow(
		"button",
		"OK",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		50, 50,
		50, 50,
		hDlg,
		( HMENU ) IDOK,
		0, 0 );

	WriteVectorToList( history, hHistoryList );

	return TRUE;
}

void OnHistoryCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
	HWND par = GetParent( hDlg );

	hEdit = GetWindow( par, GW_CHILD );

	switch( id )
	{
	case IDOK:
		{
			int index = SendMessage( hHistoryList, LB_GETCURSEL, 0, 0 );

			if( index < history.size( ) )
			{
				char *text = GetInfFromFile( history[ index ].c_str( ) );
				if( text )
				{
					SetWindowText( hEdit, text );
				}
				else
				{
					MessageBox( 0, "cant open file", "Error" , MB_OK );
				}
			}
			else
			{			

			}

			break;
		}
	}
}