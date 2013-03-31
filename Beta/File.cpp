#include "File.h"

#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

vector< string >GetLinesFromFile( const char *filename )
{
	ifstream file( filename, ios::binary );

	vector< string > result;
	string currStr = 0;
	int i = 0;

	while( !file.eof( ) )
	{
		getline( file, currStr );

		result.push_back( currStr );
	}

	file.close ( );

	return result ;
}



File::File( )
{
	int i = 0;
	char ch = 0;
		
	bool isHashSelected = false;

	vector< string > hashs = GetLinesFromFile( HASH_FILE_NAME );

	while( !isHashSelected )
	{
		while( i < HASH_LENGHT )
		{
			hash[ i ++ ] = 128 + rand( ) % 255;
		}

		for( int i = 0; i < hashs.size( ); i ++ )
		{
			if( strcmp( hash, hashs[ i ].c_str( ) ) )
			{
				isHashSelected = true;
			}
		}
	}
}

void File::Open( const char *filename )
{
	this ->filename = new char[ strlen( filename ) + 1 ];
	strcpy( this ->filename, filename );

	len = GetCountOfCharacters( filename );

	this ->content = GetInfFromFile( filename );
}

