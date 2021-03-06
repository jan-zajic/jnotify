/*******************************************************************************
 * JNotify - Allow java applications to register to File system events.
 * 
 * Copyright (C) 2005 - Content Objects
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 ******************************************************************************
 *
 * Content Objects, Inc., hereby disclaims all copyright interest in the
 * library `JNotify' (a Java library for file system events). 
 * 
 * Yahali Sherman, 21 November 2005
 *    Content Objects, VP R&D.
 *    
 ******************************************************************************
 * Author : Omry Yadan
 ******************************************************************************/

#ifndef WATCHDATA_H_
#define WATCHDATA_H_

#include <windows.h>
#include <winbase.h>
#include <winnt.h>
#include <string>

using namespace std;

typedef void(*ChangeCallback)(int watchID, int action, const WCHAR* filePath, int len);

class WatchData
{
private:
    static int _counter;

    bool _watchSubtree;
    int _watchId;
    int _mask;
    DWORD _byteReturned;
    WCHAR* _path;
    HANDLE _hDir;
    HANDLE _completionPort;
    OVERLAPPED _overLapped;
    char _buffer[8196];
public:
    WatchData();
    WatchData(const WCHAR* path, int mask, bool watchSubtree, HANDLE completionPort);
    virtual ~WatchData();
    
    const char* getBuffer(){ return _buffer;}
    const int getBufferSize() {return sizeof(_buffer);}
    const WCHAR* getPath() {return _path;}
    const int getId() {return _watchId;}
    int watchDirectory();
    
    // cancel pending watch on the hDir, returns 0 if okay or errorCode otherwise.
    int unwatchDirectory();
};

#endif /*WATCHDATA_H_*/
