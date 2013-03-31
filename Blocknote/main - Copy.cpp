#include "Prototypes.h"
#include <WindowsX.h>
PIXELFORMATDESCRIPTOR df;
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR command, int nCmdShow )
{
	static LPCSTR szClassName = {"CryptNote" };

	WNDCLASSEX wc;
	HWND window;
	MSG message;

	wc.cbSize = sizeof( WNDCLASSEX );
	wc.style = CS_HREDRAW | CS_VREDRAW;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	wc.lpfnWndProc = WndProc;
	wc.hbrBackground = ( HBRUSH )GetStockObject( WHITE_BRUSH );
	wc.hCursor = LoadCursor( 0, IDC_ARROW );
	wc.hIcon = LoadIcon( hInstance, MAKEINTRESOURCE( IDI_TITLE_ICON ) );
	wc.hIconSm = LoadIcon( hInstance, MAKEINTRESOURCE( IDI_TITLE_ICON ) );
	wc.hInstance = hInstance;
	wc.lpszClassName = szClassName;
	wc.lpszMenuName = MAKEINTRESOURCE( IDR_MENU );

	RegisterClassEx( &wc );

	window = CreateWindow(
		szClassName,
		"CryptNote",
		WS_OVERLAPPEDWINDOW,
		0, 0,
		500, 500,
		0, 0,
		hInstance,
		0
		);

	ShowWindow( window, nCmdShow );

	HACCEL accelerators = LoadAccelerators( hInstance, MAKEINTRESOURCE( IDR_ACCEL ) );

	while( GetMessage( &message, 0, 0, 0 ) )
	{
		if( !IsWindow( hRegDlg ) || !IsDialogMessage( hRegDlg, &message ) )
		{
			if( !TranslateAccelerator( window, accelerators, &message ) ) 
			{
				TranslateMessage( &message );
				DispatchMessage( &message );
			}
		}
	}

	return message.wParam;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
		HANDLE_MSG( hWnd, WM_CREATE, OnCreate );
		HANDLE_MSG( hWnd, WM_SIZE, OnSize );
		HANDLE_MSG( hWnd, WM_COMMAND, OnCommand );	
		HANDLE_MSG( hWnd, WM_DESTROY, OnDestroy );
	case WM_SETFOCUS:
		{
			SetFocus( hEdit );

			break;
		}
	default:
		{
			return DefWindowProc( hWnd, message, wParam, lParam ) ;
		}
	}

	return 0;
}

LRESULT CALLBACK RegisterDlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
			HANDLE_MSG( hDlg, WM_INITDIALOG, OnRegInitDialog );
			HANDLE_MSG( hDlg, WM_COMMAND, OnRegCommand );
	}

	return 0;
}

LRESULT CALLBACK FindReplaceDlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
		HANDLE_MSG( hDlg, WM_INITDIALOG, OnFRInitDialog );
		HANDLE_MSG( hDlg, WM_COMMAND, OnFRCommand );
	}

	return 0;
}

LRESULT CALLBACK HistoryDlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
		HANDLE_MSG( hDlg, WM_INITDIALOG, OnHistoryInitDialog );
		HANDLE_MSG( hDlg, WM_COMMAND, OnHistoryCommand );
	}

	return 0;
}