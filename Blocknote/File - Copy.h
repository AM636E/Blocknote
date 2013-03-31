#pragma once
#include "Prototypes.h"

class File
{
private:
	char*				filename;
	char*				content;

	char				passchar;	

public:	

	bool				isNew;
	bool				isOpened;
	bool				isChanged;
	bool				isSaved;
	bool				isCrypted;

public:

	File( );
	
	void				OpenDialog( HWND owner, char *filter, char *defext );
	void				Open( const char *filename );
	void				Load( const char *filename ){ Open( filename ); };
	void				Reload( );
	void				LoadFromEdit( HWND hEdit );

	void				Show( HWND hwndWindow );
	void				Show( HWND hwndEdit, HWND hWnd );
	
	void				SaveDialog( HWND owner, char *filter, char *defext );
	void				Save( const char *filename );
	void				Save( ){ Save( this ->filename ); }
	void				Clear( );
	void				Close( );
	void				LoadChanges( HWND hEdit ){ LoadFromEdit( hEdit ); }

	void				Crypt( );
	void				Encrypt( );

	const char*			GetContent( )const{ return content; }
	const char*			GetFileName( )const{ return filename; }
	
	void				SetPasschar( const char ch ){ passchar = ch; }
	
	~File( );
};