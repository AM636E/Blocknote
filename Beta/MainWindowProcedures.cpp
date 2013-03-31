#include "Prototypes.h"
HWND cEdit = 0;
BOOL OnCreate( HWND hWnd, LPCREATESTRUCT lpCS )
{
	g_isNew = true;
	isSaved = false;
	isChanged = false;

	hEdit = CreateWindow( "edit", 0, 
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL |
		WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL |
		ES_AUTOVSCROLL, 0, 0, 0, 0, hWnd, ( HMENU ) H_EDIT, 0, 0 );

	OnCommand( hWnd, IDM_FILE_NEW, 0, 0 );

	return TRUE;
}

void OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	MoveWindow( hEdit, 0, 0, cx, cy, TRUE );
}


void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch( id )
	{
	case IDM_FILE_NEW:
		{
			if( isChanged )
			{
				if( MessageBox( hWnd, "File not saved. Save?", "Caution", MB_YESNO | MB_ICONQUESTION ) == IDOK )
				{
					OnCommand( hWnd, IDM_FILE_SAVE, hwndCtl, codeNotify );
				}
			}
			SetWindowText( hWnd, "Untitled - CryptNote" );
			SetWindowText( hEdit, 0 );
			g_isNew = true;			

			break;
		}
	case IDM_FILE_OPEN:
		{
			FillOpenSave( ofn, hWnd, "Text Files\0*.txt", "txt" );			

			if( !isFromList )
			{
				GetOpenFileName( &ofn );
			}
			else
			{
				strcpy( ofn.lpstrFile, history[ historyIndex ].c_str( ) );
			}

			char * inf =  GetInfFromFile( ofn.lpstrFile );
			if( !inf )
			{
				MessageBox( hWnd, "Cant read file", "Error", MB_OK );
			}
			else
			{
				SetWindowText( hEdit, inf );

				swap( g_text, inf );

				char *onlyName = ofn.lpstrFile + GetLastCharPos( ofn.lpstrFile, '\\' ) + 1;

				char *title = new char[ strlen( onlyName ) + strlen( " - CryptNote" ) + 1 ];

				strcpy( title, onlyName );
				strcat( title, " - CryptNote" );				

				SetWindowText( hWnd, title );

				g_isNew = false;
			}

			break;
		}
	case IDM_FILE_SAVE:
		{
			if( g_isNew )
			{
				OnCommand( hWnd, IDM_FILE_SAVE_AS, hwndCtl, codeNotify );
				g_isNew = false;
			}
			else
			{
				SaveFile( hEdit, ofn.lpstrFile );
			}

			char *txt = GetTextFromEdit( hWnd );// mark that file is saved

			int pos = GetLastCharPos( txt, '*' );

			txt[ pos ] = ' ';

			SetWindowText( hWnd, txt );

			char *t = GetTextFromEdit( hEdit );
			swap( g_text, t );
			isChanged = false;
			break;
		}
	case IDM_FILE_SAVE_AS:
		{
			FillOpenSave( ofn, hWnd, "All Files\0*.*", "*.*" );

			if( GetSaveFileName( &ofn ) == TRUE )
			{
				SaveFile( hEdit, ofn.lpstrFile );
			}

			char *onlyName = ofn.lpstrFile + GetLastCharPos( ofn.lpstrFile, '\\' ) + 1;

			char *title = new char[ strlen( onlyName ) + strlen( " - CryptNote" ) + 1 ];

			strcpy( title, onlyName );
			strcat( title, " - CryptNote" );

			SetWindowText( hWnd, title );

			break;
		}
	case IDM_EDIT_CLEAR:
		{
			SetWindowText( hEdit, "" );

			break;		
		}
	case IDM_EDIT_CODE_DECODE:
		{
			char *text = GetTextFromEdit( hEdit );

			text = CodeDecodeText( text );

			SetWindowText( hEdit, text );
			OnCommand( hWnd, H_EDIT, hwndCtl, EN_UPDATE );
			
			if( ofn.lpstrFile )
			{
				AddStrToList( history, ofn.lpstrFile );
			}

			break;
		}
	case IDM_EDIT_FIND_REPLACE:
		{			
			if( !IsWindow( hFRDialog ) )
			{
				hFRDialog = CreateDialog( GetModuleHandle( 0 ), MAKEINTRESOURCE( IDD_FIND_REPLACE ), hWnd, ( DLGPROC ) FindReplaceDlgProc );

				ShowWindow( hFRDialog, SW_SHOW );
			}

			hFRDialog = 0;

			break;
		}
	case IDM_FILE_EXIT:
		{
			SendMessage( hWnd, WM_DESTROY, 0, 0 );
			break;
		}
	case IDM_VIEW_REGISTER:
		{			
			if( !IsWindow( hRegDlg ) )
			{
				hRegDlg = CreateDialog( GetModuleHandle( 0 ), MAKEINTRESOURCE( IDD_REGISTER ), hWnd, ( DLGPROC ) RegisterDlgProc );
				ShowWindow( hRegDlg, SW_SHOW );				
			}		

			break;		
		}
	case IDM_EDIT_HISTORY:
		{
			if( !IsWindow( hHistoryDlg ) )
			{
				hHistoryDlg = CreateDialog( GetModuleHandle( 0 ), MAKEINTRESOURCE( IDD_HISTORY ), hWnd, ( DLGPROC )HistoryDlgProc );
				ShowWindow( hRegDlg, SW_SHOW );
			}

			break;
		}
	case H_EDIT:
		{
			switch( codeNotify )
			{
			case EN_UPDATE:
				{
					char *txt = GetTextFromEdit( hWnd );

					int pos = GetLastCharPos( txt, '-' );

					txt[ pos - 1 ] = '*';

					SetWindowText( hWnd, txt );

					isChanged = true;

					break;
				}
			case EN_ERRSPACE:
				{
					MessageBox( 0, "Buffer is full", "Take easy man!", MB_OK );

					if( !g_isNew )
					{
						SaveFile( hEdit, ofn.lpstrFile );
					}
					else
					{
						OnCommand( hWnd, IDM_FILE_SAVE_AS, hwndCtl, codeNotify );
					}

					SetWindowText( hWnd, 0 );

					break;
				}

			}

			break;
		}
	}	
}

void OnDestroy( HWND hWnd )
{
	if( isChanged )
	{
		if( MessageBox( hWnd, "Save changes ?", "File modified", MB_YESNO | MB_ICONQUESTION ) == IDOK )
		{
			OnCommand( hWnd, IDM_FILE_SAVE_AS, 0, 0 );
		}
	}

	PostQuitMessage( 0 );
}

int GetCountOfCharacters( const char *filename )
{
	ifstream file( filename );

	if( !file )
	{
		return false;
	}

	char ch = 0;
	int len = 0;

	while( !file.eof( ) )
	{
		if( ( ch = file.get( ) ) == 10 )
		{
			len += 2;
		}
		else
		{
			len ++;
		}
	}

	file.close( );

	return len + 1;
}

char *GetInfFromFile( const char *filename )
{
	ifstream file( filename );

	if( !file )
	{
		return 0;
	}

	int len = GetCountOfCharacters( filename );

	char* inf = new char[ len + 1 ];
	int i = 0;

	char ch = 0;	

	while( !file.eof( ) )
	{
		ch = file.get( );

		if( ch == 10 )
		{
			inf[ i ] = 13;
			inf[ i + 1 ] = 10;

			i += 2;
		}
		else
		{
			inf[ i ++ ] = ch;
		}
	}

	inf[ i ] = '\0';

	file.close( );

	return inf;
}

bool WriteNSaveFile( const char* filename, const char *inf )
{
	ofstream file( filename );

	if( !file )
	{
		return false;
	}

	file << inf ;

	file.close( );

	return true;
}

void FillOpenSave( OPENFILENAME& ofn, HWND hOwner, char *filter, char *defext )
{
	ZeroMemory( &ofn, sizeof( OPENFILENAME ) );

	ofn.lStructSize = sizeof( OPENFILENAME );
	ofn.hwndOwner = hOwner;
	ofn.lpstrDefExt = defext;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = openFileName;
	ofn.nMaxFile = 256;
	ofn.Flags = OFN_CREATEPROMPT;
}

void SaveFile( HWND hwndEdit, char *filename )
{
	int len = GetWindowTextLength( hEdit );
	char *ch = new char[ len  + 1 ];

	GetWindowText( hEdit, ch, len );

	WriteNSaveFile( ofn.lpstrFile, ch );

	isSaved = true;

	ofstream file( filename );

	file << ch;

	file.close( );
}

bool isCoded = true;

char *CodeDecodeText( const char *text )
{
	static int PASSWORD = 0;
	if( isCoded )
	{
		srand( time( 0 ) );

		PASSWORD = 255 + rand( ) % 1000;
	}

	int len = strlen( text );
	char *codedText = new char[ len + 2 ];

	int i = 0;
	for( i = 0; i < len; i ++ )
	{
		codedText[ i ] = text[ i ] ^ PASSWORD;
	}

	codedText[ i ] = 0;

	isCoded = !isCoded;

	return codedText;
}

int GetLastCharPos( const char* str, const char ch )
{
	int len = strlen( str );

	int pos = 0;

	for( pos = len - 1; str[ pos ] != ch; pos -- );

	return pos;
}

void AddStrToList( vector< string >& list, const char *str )
{
	for( int i = 0; i < list.size( ); i ++ )
	{
		if( !strcmp( list[ i ].c_str( ), str ) );
		{
			return ;
		}
	}

	list.push_back( str );
}