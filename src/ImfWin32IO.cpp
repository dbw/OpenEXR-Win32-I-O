#include "ImfWin32IO.h"
#include <IexBaseExc.h>

namespace Imf
{

	std::string GetLastErrorMessage(std::string function)
	{
		std::string message;
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

		message = function + " failed with error: " + (LPTSTR)lpMsgBuf;

    LocalFree(lpMsgBuf);
		return message;
	}

	//! Win32 native implementation of Win32IFStream

	Win32IFStream::Win32IFStream(const char filename[])
		: IStream(filename),
			_file(0),
			_deleteStream(true)
	{
		SetLastError(0);
		_file = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL , NULL);
		if (_file == INVALID_HANDLE_VALUE)
		{
			//throw Iex::InputExc ("File does not exist.");
		  if (GetLastError())
		  {
			  throw Iex::InputExc(GetLastErrorMessage("Win32OFStream::Win32OFStream()").c_str());
		  }
		}
		if (GetLastError())
		{
			throw Iex::InputExc(GetLastErrorMessage("Win32OFStream::Win32OFStream()").c_str());
		}
	}

	Win32IFStream::Win32IFStream(HANDLE _ihandle, const char filename[])
		: IStream(filename), _file(0), _deleteStream(false)
	{
		_file = _ihandle;
	}


	Win32IFStream::~Win32IFStream()

	{
		if ((_file != INVALID_HANDLE_VALUE) && _deleteStream) CloseHandle(_file);
	}

	bool Win32IFStream::read(char c[], int n)
	{
		DWORD bytesRead = 0;
		if (!ReadFile(_file, (LPVOID) c, n, &bytesRead, 0))
		{
			throw Iex::InputExc(GetLastErrorMessage("Win32IFStream::read()").c_str());
		}
		return true;
	}

	Int64 Win32IFStream::tellg()
	{
		SetLastError(0);
		LARGE_INTEGER lNewFile;
		LARGE_INTEGER lNewPos;
		lNewPos.QuadPart = 0;
		BOOL ret = SetFilePointerEx(_file, lNewPos, &lNewFile, FILE_CURRENT);
		if (GetLastError())
		{
			throw Iex::InputExc(GetLastErrorMessage("Win32IFStream::tellg()").c_str());
		}
		return lNewFile.QuadPart;
	}

	void Win32IFStream::seekg(Int64 pos)
	{
		SetLastError(0);
		LARGE_INTEGER lNewFile;
		LARGE_INTEGER lNewPos;
		lNewPos.QuadPart = pos;
		BOOL ret = SetFilePointerEx(_file, lNewPos, &lNewFile, FILE_BEGIN);
		if (GetLastError())
		{
			throw Iex::InputExc(GetLastErrorMessage("Win32IFStream::seekg()").c_str());
		}
	}

	void Win32IFStream::clear()
	{
		SetLastError(0);
	}

	//! Win32 native implementation of Win32OFStream

	Win32OFStream::Win32OFStream(const char filename[])
		: OStream(filename), _file(0), _deleteStream(true)
	{
		//_file = CreateFileA(filename, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, NULL, NULL);
    /*
     *  GENERIC_READ | GENERIC_WRITE 
     *
     * When an application creates a file across a network, it is better to use GENERIC_READ | GENERIC_WRITE for dwDesiredAccess than to use GENERIC_WRITE alone.
     * The resulting code is faster, because the redirector can use the cache manager and send fewer SMBs with more data.
     * This combination also avoids an issue where writing to a file across a network can occasionally return ERROR_ACCESS_DENIED.
     */
		_file = CreateFileA(filename,  GENERIC_READ | GENERIC_WRITE , NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (_file == INVALID_HANDLE_VALUE)
		{
			throw Iex::InputExc(GetLastErrorMessage("Win32OFStream::Win32OFStream()").c_str());
		}
	}

	Win32OFStream::Win32OFStream(HANDLE ohandle, const char filename[])
		: OStream(filename), _file(0), _deleteStream(false)
	{
		_file = ohandle;
	}


	Win32OFStream::~Win32OFStream()
	{
		if ((_file != INVALID_HANDLE_VALUE) && _deleteStream) CloseHandle(_file);
	}

	void Win32OFStream::write(const char c[], int n)
	{
		DWORD bytesRead = 0;
		if (!WriteFile(_file, (LPVOID) c, n, &bytesRead, 0))
		{
			throw Iex::InputExc(GetLastErrorMessage("Win32IFStream::write()").c_str());
		}
	}

	Int64 Win32OFStream::tellp()
	{
		SetLastError(0);
		LARGE_INTEGER lNewFile;
		LARGE_INTEGER lNewPos;
		lNewPos.QuadPart = 0;
		BOOL ret = SetFilePointerEx(_file, lNewPos, &lNewFile, FILE_CURRENT);
		if (GetLastError())
		{
			throw Iex::InputExc(GetLastErrorMessage("Win32OFStream::tellp()").c_str());
		}
		return lNewFile.QuadPart;
	}

	void Win32OFStream::seekp(Int64 pos)
	{
		SetLastError(0);
		LARGE_INTEGER lNewFile;
		LARGE_INTEGER lNewPos;
		lNewPos.QuadPart = pos;
		BOOL ret = SetFilePointerEx(_file, lNewPos, &lNewFile, FILE_BEGIN);
		if (GetLastError())
		{
			throw Iex::InputExc(GetLastErrorMessage("Win32OFStream::seekp()").c_str());
		}
	}

}
