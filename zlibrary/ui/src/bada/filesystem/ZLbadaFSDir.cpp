/*
 * Copyright (C) 2004-2010 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */
#include <FBase.h>
#include <FIo.h>
#include <FText.h>

using namespace Tizen::Text;
using namespace Tizen::Base;
using namespace Tizen::Base::Utility;
using namespace Tizen::Io;


#include <sys/stat.h>
//#include <dirent.h>
#include <stdio.h>

#include "ZLbadaFSDir.h"
#include "ZLbadaFSManager.h"

void ZLbadaFSDir::collectSubDirs(std::vector<std::string> &names, bool includeSymlinks) {
	 AppLog("ZLbadaFSDir::collectSubDirs");
    Directory dir;
    DirEnumerator *pDirEnum = null;
    result r = E_SUCCESS;
    // Opens the directory
    r = dir.Construct(path().c_str());
    AppLog(" dir.Construct %s",path().c_str()) ;
    if(IsFailed(r))  AppLog("IsFailed"); //goto CATCH;
    // Reads all the directory entries
    pDirEnum = dir.ReadN();
    //  if(!pDirEnum)    goto CATCH;
    while(pDirEnum->MoveNext() == E_SUCCESS)
    {
        DirEntry dirEntry = pDirEnum->GetCurrentDirEntry();
        if (dirEntry.IsDirectory())  {
        	Tizen::Base::String str = dirEntry.GetName();
        	AppLog("dirEntry name Length = %d",str.GetLength()) ;
        	Utf8Encoding utf8;
        	ByteBuffer* pBB = utf8.GetBytesN(str);
        	std::string  shortName((const char*)pBB->GetPointer());//,str.GetLength());
        	AppLog("dirEntry name = %s",shortName.c_str()) ;
        	if ((shortName ==".")||(shortName == ".."))
        		    AppLog("dirEntry name dots");
        	else
        			names.push_back(shortName);
        	delete pBB;
        }

    }

    // Deletes the enumerator
    delete pDirEnum;

    AppLog("Succeeded");


/*	DIR *dir = opendir(path().c_str());
	if (dir != 0) {
		const std::string namePrefix = path() + delimiter();
		const dirent *file;
		struct stat fileInfo;
		std::string shortName;
		while ((file = readdir(dir)) != 0) {
			shortName = file->d_name;
			if ((shortName == ".") || (shortName == "..")) {
				continue;
			}
			const std::string path = namePrefix + shortName;
			if (includeSymlinks) {
				stat(path.c_str(), &fileInfo);
			} else {
				lstat(path.c_str(), &fileInfo);
			}
			if (S_ISDIR(fileInfo.st_mode)) {
				names.push_back(shortName);
			}
		}
		closedir(dir);
	}
	*/
}

void ZLbadaFSDir::collectFiles(std::vector<std::string> &names, bool includeSymlinks) {
   //TODO collectFiles
	 AppLog("ZLbadaFSDir::collectFiles") ;
    Directory dir;
    DirEnumerator *pDirEnum = null;
    result r = E_SUCCESS;

    // Opens the directory
    r = dir.Construct(path().c_str());
	 AppLog(" dir.Construct %s",path().c_str()) ;
    if(IsFailed(r))  AppLog("IsFailed");

       //goto CATCH;

    // Reads all the directory entries
    pDirEnum = dir.ReadN();
  //  if(!pDirEnum)    goto CATCH;
    while(pDirEnum->MoveNext() == E_SUCCESS)
    {
        DirEntry dirEntry = pDirEnum->GetCurrentDirEntry();
        if (!dirEntry.IsDirectory())
        {
        	Tizen::Base::String str = dirEntry.GetName();
        //	AppLog("fileEntry name Length = %d",str.GetLength()) ;
        	Utf8Encoding utf8;
        	ByteBuffer* pBB = utf8.GetBytesN(str);
        	std::string  shortName((const char*)pBB->GetPointer(),str.GetLength());
        //	AppLog("fileEntry name = %s",shortName.c_str()) ;
        	names.push_back(shortName);
        	delete pBB;
        }

    }

    // Deletes the enumerator
    delete pDirEnum;

    AppLog("Succeeded");

    // The opened directory is closed automatically when the destructor of the Directory class is invoked.
    //return 0;
/*
CATCH:
    if(pDirEnum)
        delete pDirEnum;
    AppLog("Failed...");
   // return -1;

/*	DIR *dir = opendir(path().c_str());
	if (dir != 0) {
		const std::string namePrefix = path() + delimiter();
		const dirent *file;
		struct stat fileInfo;
		std::string shortName;
		while ((file = readdir(dir)) != 0) {
			shortName = file->d_name;
			if ((shortName == ".") || (shortName == "..")) {
				continue;
			}
			const std::string path = namePrefix + shortName;
			if (includeSymlinks) {
				stat(path.c_str(), &fileInfo);
			} else {
				lstat(path.c_str(), &fileInfo);
			}
			if (S_ISREG(fileInfo.st_mode)) {
				names.push_back(shortName);
			}
		}
		closedir(dir);
	}
	*/
}
