#include "Prototypes.h"



HWND hFind = 0, hReplace = 0;



BOOL OnFRInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam)

{

	HWND label1 = 0, label2 = 0;

	HWND hFindButton = 0, hReplaceButton = 0, hReplaceAllButton = 0, hCancel = 0;

	HWND hCheckRegister = 0;



	CreateWindow(

		"static",

		"Find:",

		WS_CHILD | WS_VISIBLE | SS_RIGHT,

		10, 10,

		50, 30,

		hDlg,

		0, 0, 0 );



	hFind = CreateWindow(

		"edit",

		"",

		WS_CHILD | WS_VISIBLE | SS_LEFT | ES_LEFT | WS_BORDER | ES_AUTOHSCROLL,

		75, 10,

		300, 20,

		hDlg,

		0, 0, 0 );



	CreateWindow(

		"static",

		"Replace:",

		WS_CHILD | WS_VISIBLE | SS_LEFT,

		10, 40,

		60, 30,

		hDlg,		

		0, 0, 0 );



	hReplace = CreateWindow(

		"edit",

		"",

		WS_CHILD | WS_VISIBLE | SS_LEFT | ES_LEFT | WS_BORDER | ES_AUTOHSCROLL,

		75, 40,

		300, 20,

		hDlg,

		0, 0, 0 );



	char *buttonCaps[] =

	{

		"Find",

		"Find Next",

		"Replace",

		"Replace All",

		"Cancel"

	};

	int j = 10;

	int k = 0;

	for( int i = IDB_FIND; i <= IDB_CANCEL; i ++ )

	{

		CreateWindow(

			"button",

			buttonCaps[ k ],

			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

			400, j,

			80, 20,

			hDlg,

			( HMENU ) i,

			0, 0 );



		j += 30;

		k ++;

	}



	CreateWindow(

		"button",

		"Check register",

		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,

		75, j - 30,

		115, 30,

		hDlg,

		( HMENU ) IDB_CHECK_REGISTER,

		0, 0 );



	return TRUE;

}



char *GetTextFromEdit( HWND hEdit )

{

	int len = GetWindowTextLength( hEdit );



	char *pCh = new char[ len + 2 ];



	GetWindowText( hEdit, pCh, len + 1 );



	return pCh;

}



#define TEXT_NOT_FOUND -1



int FindTextInEdit( HWND hEdit, const char *findWhat )

{

	g_text = GetTextFromEdit( hEdit );



	char *ptr = strstr( g_text, findWhat );



	return ( !ptr ) ? TEXT_NOT_FOUND : ( ptr - g_text );

}



int FindText( char* szWhere, const char* szWhat )

{

	char *find = strstr( szWhere, szWhat );



	if( strlen( szWhere ) == strlen( szWhat ) )

		return TEXT_NOT_FOUND;



	return ( find == 0 ) ? TEXT_NOT_FOUND :

		( find - szWhere );

}



void StrToLower( char *str )

{

	int i = 0;



	while( str[ i ] )

	{

		str[ i ] = tolower( str[ i ] );



		i ++;

	}

}



void OnFRCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)

{

	static char *toFind = 0;

	static char *toReplace = 0;



	static int findPos = 0;

	static bool isEndFound = false;

	static bool isCheckRegister = false;

	

	HWND par = GetParent( hDlg );



	hEdit = GetWindow( par, GW_CHILD );

	

	static char *text = 0;

	

	switch( id )

	{

	case IDB_FIND:

		{

			text = GetTextFromEdit( hEdit );



			if( !isCheckRegister )

			{

				StrToLower( text );

			}



			toFind = GetTextFromEdit( hFind );

			

			findPos = FindText( text, toFind );



			if( findPos == TEXT_NOT_FOUND )

			{

				MessageBox( hDlg, "Text not found. Starting from beginning", "Not Found", MB_OK );



				isEndFound = true;



				findPos = 0;

			}

			else

			{

				SetFocus( hEdit );

				SendMessage( hEdit, EM_SETSEL, findPos, findPos + strlen( toFind ) );

			}



			break;

		}

	case IDB_FIND_NEXT:

		{

			text = GetTextFromEdit( hEdit );



			if( !isCheckRegister )

			{

				StrToLower( text );

			}



			toFind = GetTextFromEdit( hFind );



			if( findPos > 0 )

				int v = 0;			



			int findResult = FindText( text + findPos, toFind );



			if( findResult != TEXT_NOT_FOUND )

				findPos += findResult;			



			if( findResult != TEXT_NOT_FOUND )

			{

				SetFocus( hEdit );

				SendMessage( hEdit, EM_SETSEL, findPos, findPos + strlen( toFind ) );



				findPos += strlen( toFind );								

			}

			else

			{				

				findPos = 0;			

			}

			

			break;

		}

	case IDB_REPLACE:

		{

			OnFRCommand( hDlg, IDB_FIND, hwndCtl, codeNotify );



			toReplace = GetTextFromEdit( hReplace );



			if( toReplace == 0 )

				return ;

			if( isEndFound )

				return ;

			SetFocus( hEdit );

			SendMessage( hEdit, EM_REPLACESEL, 0, ( LPARAM ) toReplace );			



			break;

		}

	case IDB_REPLACE_ALL:

		{		

			text = GetTextFromEdit( hEdit );



			while( !isEndFound )

			{				

				OnFRCommand( hDlg, IDB_REPLACE, 0, 0 );

			}

			MessageBox( hDlg, "All ocupence seems to be replaced", "Seems to be done", MB_OK );

			findPos = 0;

			isEndFound = false;



			break;

		}

	case IDB_CHECK_REGISTER:

		{

			isCheckRegister = !isCheckRegister;



			break;

		}

	case IDB_CANCEL:

		{

			EndDialog( hDlg, 0 );

		}

	}

}

