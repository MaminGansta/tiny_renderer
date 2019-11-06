#pragma once
#include <Windows.h>
#include <string> 
#include <tchar.h>

static std::string Log;

inline void add_log(std::string note)
{
	Log += note;
	Log += '\n';
}

// write log to file
inline void dump_log(void)
{
	HANDLE hFile;

	hFile = CreateFile("Log/log.txt",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("hFile is NULL\n"));
		_tprintf(TEXT("Target file is %s\n"),
			"log.txt");
	}

	DWORD dwWriteBytes;
	WriteFile(hFile, Log.c_str(), Log.size(), &dwWriteBytes, 0);

	CloseHandle(hFile);
}

