#pragma once
#include "Prototypes.h"

const int HASH_LENGHT = 5;
static const char HASH_FILE_NAME[ 255 ] = { "hash.hsh" };

class File
{
private:
	char*				filename;
	char*				content;
	int					len;

	char				hash[ HASH_LENGHT ];

public:

	bool				isNew;
	bool				isOpened;
	bool				isChanged;
	bool				isSaved;
	bool				isCrypted;

public:

	File( );
	
	void				Open( const char *filename );
	void				Show( HWND hwndWindow );
	void				Save( const char *filename );

	void				Crypt( );
	void				Encrypt( );

	char*				GetContent( ){ return content; }
	int					GetLen( ){ return len; }

	~File( );

};