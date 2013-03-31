#include "Prototypes.h"

static LPCSTR szRadioName[] =
{
	"Like in sentences",
	"downcase",
	"UPPERCASE",
	"Begin With Uppercase",
	"rEVERSE REGISTER"
};

BOOL OnRegInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam)
{
	int j = 0;
	for( int i = IDRB_LIKE_IN_SENTENCES; i <= IDRB_REVERSE_REGISTER; i ++ )
	{
		CreateWindow(
			"button",
			szRadioName[ i - IDRB_LIKE_IN_SENTENCES ],
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			0, j,
			550, 30,
			hDlg,
			( HMENU ) i,
			0, 0 );

		j += 30;
	}

	CreateWindow(
		"button",
		"OK",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		30, j + 10,
		30, 30,
		hDlg,
		( HMENU ) IDOK ,
		0, 0 );

	CreateWindow(
		"button",
		"Cancel",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		70, j + 10,
		50, 30,
		hDlg,
		( HMENU ) IDCANCEL,
		0, 0 );

	/*CreateWindow(
		"button",
		"Debug",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		130, j + 10,
		50, 30,
		hDlg,
		( HMENU ) IDB_DEBUG ,
		0, 0 );*/


	return TRUE;
}

char *LikeInSentences( const char *str );
char *DownCase( const char *str );
char *UpperCase ( const char *str );
char *BeginWithUpperCase( const char *str );
char *ReverseRegister( const char *str );

void OnRegCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
	char *( *func[ ] ) ( const char * ) =
	{
		LikeInSentences,
		DownCase,
		UpperCase,
		BeginWithUpperCase,
		ReverseRegister
	};

	static int i = 0;

	HWND par = GetParent( hDlg );

	hEdit = GetWindow( par, GW_CHILD );

	static char *text = GetTextFromEdit( hEdit );

	switch( id )
	{
	case IDRB_LIKE_IN_SENTENCES:
	case IDRB_DOWNCASE:
	case IDRB_UPPERCASE:
	case IDRB_BEGIN_WITH_UPPERCASE:
	case IDRB_REVERSE_REGISTER:
		{
			int index = id;
			i = id - IDRB_LIKE_IN_SENTENCES;
			CheckRadioButton( hDlg, IDRB_LIKE_IN_SENTENCES, IDRB_REVERSE_REGISTER, index );

			break;
		}
	case IDOK:
		{
			text = func[ i ]( text );

			SetWindowText( hEdit, text );
			UpdateWindow( hEdit );

			break;
		}
	case IDCANCEL:
		{
			EndDialog( hDlg, 0 );
			hDlg = 0;			
		}
	}
}

char *LikeInSentences( const char *str )
{
	int len = strlen( str );
	char *result = new char[ len + 1 ] ;

	strcpy( result, str );

	for( int i = 0; i < len - 1 ; i ++ )
	{
		if( result[ i ] == '.' )
		{
			result [ i + 1 ] = toupper( result[ i + 1 ] );
		}
	}

	return result;
}

char *DownCase( const char *str )
{
	int len = strlen( str );
	char *result = new char[ len + 2 ] ;

	int i = 0;

	for( i = 0 ; i < len; i ++ )
	{
		result[ i ] = tolower( str[ i ] ) ;
	}

	result[ i ] = 0;

	return result;
}

char *UpperCase( const char *str )
{
	int len = strlen( str );
	char *result = new char[ len + 2 ] ;

	int i = 0;

	for( i = 0 ; i < len; i ++ )
	{
		result[ i ] = toupper( str[ i ] ) ;
	}

	result[ i ] = 0;

	return result;
}

char *BeginWithUpperCase( const char *str )
{
	int len = strlen( str );
	char *result = new char[ len + 1 ] ;

	strcpy( result, str );
	result[ 0 ] = toupper( result[ 0 ] );

	for( int i = 0; i < len - 1 ; i ++ )
	{
		if( result[ i ] == '.' || result[ i ] == ' ' )
		{
			result [ i + 1 ] = toupper( result[ i + 1 ] );
		}
	}

	return result;
}

char *ReverseRegister( const char *str )
{
	int len = strlen( str );
	char *result = new char[ len + 1 ];

	for( int i = 0; i <= len; i ++ )
	{
		if( isupper( str[ i ] ) )
		{
			result[ i ] = tolower( str[ i ] );
		}
		else
		{
			result[ i ] = toupper( str[ i ] );
		}
	}

	return result;
}
