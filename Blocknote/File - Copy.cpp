#include "File.h"

#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

vector< string >GetLinesFromFile( const char *filename )
{
	ifstream file( filename, ios::binary );

	vector< string > result;
	string currStr;
	int i = 0;

	while( !file.eof( ) )
	{
		getline( file, currStr );

		result.push_back( currStr );

		if( currStr.length( ) == 0 )
		{ break; }
	}

	file.close ( );

	return result ;
}

File::File( )
{
	srand( time( 0 ) );

	passchar	= 128 + rand( ) % 255;

	filename	= 0;
	content		= 0;
	isNew		= 0;
	isOpened	= 0;
	isSaved		= 0;
	isCrypted	= 0;
}

void File::OpenDialog( HWND owner, char *filter, char *defext )
{
	FillOpenSave( ofn, owner, filter, defext );

	if( GetOpenFileName( &ofn ) )
	{
		Load( ofn.lpstrFile );

		char *wintext = new char[ strlen( ofn.lpstrFile ) + strlen( " - CryptNote" ) + 1 ];
		strcpy( wintext, ofn.lpstrFile );
		strcat( wintext, " - CryptNote" );
		SetWindowText( owner, wintext );
	}
	else
	{
		MessageBox( 0, "Cant open file" , "Sorry", MB_OK );
	}
}

void File::Open( const char *filename )
{
	this ->filename = new char[ strlen( filename ) + 1 ];
	strcpy( this ->filename, filename );

	passchar		= 128 + rand( ) % 255;

	this ->content	= GetInfFromFile( filename );
}

void File::Show( HWND hwndWindow )
{
	SetWindowText( hwndWindow, this ->content );
}

void File::Show( HWND hwndEdit, HWND hWnd )
{
	Show( hwndEdit );

	int last = GetLastCharPos( filename, '\\' );
	char *onlyName = filename + last + 1;

	char *title = new char[ strlen( onlyName ) + strlen( " - CryptNote" ) + 1 ];
	strcpy( title, onlyName );
	strcat( title, " - CryptNote" );

	SetWindowText( hWnd, title );	
}

void File::SaveDialog( HWND owner, char *filter, char *defext )
{
	FillOpenSave( ofn, owner, filter, defext );

	if( GetSaveFileName( &ofn ) == TRUE )
	{
		if( filename )
			delete filename;

		filename = new char [ strlen( ofn.lpstrFile ) + 1 ];

		strcpy( filename, ofn.lpstrFile );

		Save( filename );
	}	
}

void File::Save( const char* filename )
{
	ofstream file( filename );

	file << content;

	file.close( );

	isSaved = true;
	isChanged = false;
}

void File::Crypt( )
{
	int len = strlen( content );

	for( int i = 0; i < len; i ++ )
	{
		content[ i ] = content[ i ] ^ passchar;
	}

	vector< string > history = GetLinesFromFile( HISTORY_FILE );

	if(  history[ 0 ].length( ) > 1 )
	{
		for( int i = 0; i < history.size( ); i ++ )
		{
			if( !strcmp( history[ i ].c_str( ), filename ) ) 
			{
				return ;
			}
		}
	}

	if( filename )
	{
		AddUniqueStrToFile( HISTORY_FILE, filename );
		
		char *pas = new char( this ->passchar );
		AddUniqueStrToFile( PASSWD_FILE, pas );
	}

	isCrypted = true;
	isChanged = true;
}

void File::Encrypt( )
{
	int len = strlen( content );

	for( int i = 0; i < len; i ++ )
	{
		content[ i ] = content[ i ] ^ passchar;
	}

	isCrypted = false;
	isChanged = true;
}

void File::LoadFromEdit( HWND hEdit )
{
	if( content )
		delete content;

	content = GetTextFromEdit( hEdit );
}

void File::Clear( )
{
	if( content )
		delete content;
	content = 0;
	isChanged = true;
}

void File::Reload( )
{
	if( this ->filename )
	{
		Load( this ->filename ); 
	}
}

void File::Close( )
{
	if( filename )
		delete filename;
	if( this ->content )
		delete content;

	isOpened = false;
}

File::~File( )
{
	if( filename )
		delete filename ;
	if( content )
		delete content;
}