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

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <set>

#include <ZLStringUtil.h>

#include "ZLbadaFSManager.h"
#include "ZLbadaFSDir.h"
#include "ZLbadaFileInputStream.h"
#include "ZLbadaFileOutputStream.h"

#include <FBase.h>
#include <FIo.h>

using namespace Tizen::Base;
using namespace Tizen::Io;


//--------------
ZLbadaFSManager::ZLbadaFSManager():ZLFSManager() {
	AppLog("ZLbadaFSManager::ZLbadaFSManager");
	//connect(&myWatcher, SIGNAL(directoryChanged(QString)), SLOT(onPathChanged(QString)));
	//connect(&myWatcher, SIGNAL(fileChanged(QString)), SLOT(onPathChanged(QString)));
}




std::string ZLbadaFSManager::convertFilenameToUtf8(const std::string &name) const {
	if (name.empty()) {
		return name;
	}
	// AppLog("ZLbadaFSManager::convertFilenameToUtf8");
	// AppLog("name = %s",name.c_str());

	 return name;
	//QString qString = QString::fromLocal8Bit(name.c_str());
	//return (qString == QString::null) ? "" : (const char*)qString.toUtf8();
}
/*
std::string ZLbadaFSManager::mimeType(const std::string &path) const {
	// TODO: implement
	 AppLog("ZLbadaFSManager::mimeType");
	return std::string();
}

*/

shared_ptr<ZLMimeType> ZLbadaFSManager::mimeType(const std::string &path) const {
	// TODO: implement
	 AppLog("ZLbadaFSManager::mimeType");
	return ZLMimeType::EMPTY;
}

//---------------


static std::string getPwdDir() {
	char *pwd = getenv("PWD");
	return "/Home";//(pwd != 0) ? pwd : "";
}

static std::string getHomeDir() {
	char *home = getenv("HOME");
	return "/Home";//(home != 0) ? home : "";
}

ZLFileInfo ZLbadaFSManager::fileInfo(const std::string &path) const {
	AppLog("ZLbadaFSManager::fileInfo %s",path.c_str());
	ZLFileInfo info;
	//struct stat fileStat;
    result r = E_SUCCESS;
    FileAttributes attr;
    Tizen::Base::String badaPath(path.c_str());
    r = File::GetAttributes(badaPath, attr);
   //TODO if(IsFailed(r)) goto CATCH;

	//info.Exists = stat(path.c_str(), &fileStat) == 0; stat - не работает
    info.Exists = (r==E_SUCCESS);

	AppLog("ZLbadaFSManager::fileInfo r = %d", r);
	if (info.Exists) {
		info.Size = attr.GetFileSize();//fileStat.st_size;
		//AppLog("ZLbadaFSManager::fileInfo.Size %d",fileStat.st_size);
		AppLog("ZLbadaFSManager::fileInfo.Size %d",info.Size);
		//AppLog("ZLbadaFSManager::fileInfo.st_mode %x",fileStat.st_mode);
		info.IsDirectory = attr.IsDirectory();//S_ISDIR(fileStat.st_mode);
		if (info.IsDirectory) AppLog("ZLbadaFSManager::fileInfo.IsDirectory");
	}
	return info;
}

std::string ZLbadaFSManager::resolveSymlink(const std::string &path) const {
//	AppLog("ZLbadaFSManager::resolveSymlink %s",path.c_str());
	return path;
}
	/*
	std::set<std::string> names;
	std::string current = path;
	for (int i = 0; i < 256; ++i) {
		names.insert(current);

		std::string buffer(2048, '\0');
		int len = readlink(current.c_str(), (char*)buffer.data(), 2048);
		if ((len == 2048) || (len <= 0)) {
			return current;
		}
		buffer.erase(len);
		if (buffer[0] != '/') {
			buffer = parentPath(current) + '/' + buffer;
		}
		normalizeRealPath(buffer);
		if (names.find(buffer) != names.end()) {
			return buffer;
		}
		current = buffer;
	}
	return "";

}
*/
void ZLbadaFSManager::normalizeRealPath(std::string &path) const {
//	AppLog("normalizeRealPath %s",path.c_str());

	static std::string HomeDir = getHomeDir();
	static std::string PwdDir = getPwdDir();
//	AppLog("HomeDir %s",HomeDir.c_str());
//	AppLog("PwdDir %s",PwdDir.c_str());

	if (path.empty()) {
		path = PwdDir;
	} else if (path[0] == '~') {
		if ((path.length() == 1) || (path[1] == '/')) {
			//AppLog("HomeDir +");
			path = HomeDir + path.substr(1);
		}
	} else if (path[0] != '/') {
		path = PwdDir + '/' + path;
	}
//	AppLog("normalizeRealPath2 %s",path.c_str());
	int last = path.length() - 1;
	while ((last > 0) && (path[last] == '/')) {
		--last;
	}
	if (last < (int)path.length() - 1) {
		path = path.substr(0, last + 1);
	}

	int index;
	while ((index = path.find("/../")) != -1) {
		int prevIndex = std::max((int)path.rfind('/', index - 1), 0);
		path.erase(prevIndex, index + 3 - prevIndex);
	}
	int len = path.length();
	if ((len >= 3) && (path.substr(len - 3) == "/..")) {
		int prevIndex = std::max((int)path.rfind('/', len - 4), 0);
		path.erase(prevIndex);
	}
	while ((index = path.find("/./")) != -1) {
		path.erase(index, 2);
	}
	while (path.length() >= 2 &&
				 path.substr(path.length() - 2) == "/.") {
		path.erase(path.length() - 2);
	}
	while ((index = path.find("//")) != -1) {
		path.erase(index, 1);
	}
}

ZLFSDir *ZLbadaFSManager::createNewDirectory(const std::string &path) const {
	AppLog("createNewDirectory %s",path.c_str());

	result r = Tizen::Io::Directory::Create(Tizen::Base::String(path.c_str()), true);
	if (r == E_SUCCESS) {
		return createPlainDirectory(path);
	}
	return 0;
}

ZLFSDir *ZLbadaFSManager::createPlainDirectory(const std::string &path) const {
	return new ZLbadaFSDir(path);
}

ZLInputStream *ZLbadaFSManager::createPlainInputStream(const std::string &path) const {
	return new ZLbadaFileInputStream(path);
}

ZLOutputStream *ZLbadaFSManager::createOutputStream(const std::string &path) const {
	return new ZLbadaFileOutputStream(path);
}

bool ZLbadaFSManager::removeFile(const std::string &path) const {
	AppLog("ZLbadaFSManager:removeFile %s",path.c_str());
	return unlink(path.c_str()) == 0;
}

int ZLbadaFSManager::findArchiveFileNameDelimiter(const std::string &path) const {
	return path.rfind(':');
}

static const std::string RootPath = "/";

shared_ptr<ZLDir> ZLbadaFSManager::rootDirectory() const {
	return createPlainDirectory(RootPath);
}

const std::string &ZLbadaFSManager::rootDirectoryPath() const {
	return RootPath;
}

std::string ZLbadaFSManager::parentPath(const std::string &path) const {
	if (path == RootPath) {
		return path;
	}
	int index = findLastFileNameDelimiter(path);
	return (index <= 0) ? RootPath : path.substr(0, index);
}

bool ZLbadaFSManager::canRemoveFile(const std::string &path) const {
	AppLog("ZLbadaFSManager::canRemoveFile %s",path.c_str());
	result r = E_SUCCESS;
	FileAttributes attr;
    r = File::GetAttributes(path.c_str(), attr);
	//TODO   if(IsFailed(r)) goto CATCH;
    if (!attr.IsReadOnly())	AppLog("true"); else AppLog("false");
   return !attr.IsReadOnly();
//	return access(parentPath(path).c_str(), W_OK) == 0;
}

