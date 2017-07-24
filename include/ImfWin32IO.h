///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004, Industrial Light & Magic, a division of Lucas
// Digital Ltd. LLC
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// *       Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// *       Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// *       Neither the name of Industrial Light & Magic nor the names of
// its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////


#ifndef INCLUDED_IMF_WIN32_IO_H
#define INCLUDED_IMF_WIN32_IO_H

//-----------------------------------------------------------------------------
//
//	Low-level file input and output for OpenEXR
//	based on C++ standard iostreams.
//
//-----------------------------------------------------------------------------

#include <ImfIO.h>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace Imf {

//-------------------------------------------
// class Win32IFStream -- an implementation of
// class IStream based on class std::ifstream
//-------------------------------------------

class Win32IFStream: public IStream
{
  public:

    //-------------------------------------------------------
    // A constructor that opens the file with the given name.
    // The destructor will close the file.
    //-------------------------------------------------------

    Win32IFStream (const char fileName[]);


    //---------------------------------------------------------
    // A constructor that uses a std::ifstream that has already
    // been opened by the caller.  The Win32IFStream's destructor
    // will not close the std::ifstream.
    //---------------------------------------------------------

	Win32IFStream (HANDLE _ihandle, const char fileName[]);


    virtual ~Win32IFStream ();

    virtual bool	read (char c[/*n*/], int n);
    virtual Int64	tellg ();
    virtual void	seekg (Int64 pos);
    virtual void	clear ();

  private:

    HANDLE _file;
    bool		_deleteStream;
};


//-------------------------------------------
// class Win32OFStream -- an implementation of
// class OStream based on class std::ofstream
//-------------------------------------------

class Win32OFStream: public OStream
{
  public:

    //-------------------------------------------------------
    // A constructor that opens the file with the given name.
    // The destructor will close the file.
    //-------------------------------------------------------

    Win32OFStream (const char fileName[]);


    //---------------------------------------------------------
    // A constructor that uses a std::ofstream that has already
    // been opened by the caller.  The Win32OFStream's destructor
    // will not close the std::ofstream.
    //---------------------------------------------------------



		Win32OFStream (HANDLE _ohandle, const char fileName[]);


    virtual ~Win32OFStream ();

    virtual void	write (const char c[/*n*/], int n);
    virtual Int64	tellp ();
    virtual void	seekp (Int64 pos);

  private:

		HANDLE _file;
    bool		_deleteStream;
};


} // namespace Imf

#endif