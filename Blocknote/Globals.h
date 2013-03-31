#pragma once
#include <Windows.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const char HISTORY_FILE[]	= "history.his\0";
const char PASSWD_FILE[]	= "pass.pas\0";

static OPENFILENAME ofn;
static char openFileName[ 256 ];

static HWND hFRDialog = 0;//handle find replace 
static MSG dlgMessage;

static HWND hRegDlg = 0;// handle of register dialog

static HWND hEdit = 0;// edit field hangle

static bool isSaved ;
static bool isChanged ;
static bool g_isNew ;

static char *g_text;//loaded text

static HWND hHistoryDlg;