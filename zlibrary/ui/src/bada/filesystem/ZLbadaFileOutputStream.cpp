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

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "ZLbadaFileOutputStream.h"
#include "ZLbadaFSManager.h"
#include <FBase.h>

ZLbadaFileOutputStream::ZLbadaFileOutputStream(const std::string &name) : myName(name), myHasErrors(false), myFile(0) {
	 AppLog("ZLbadaFileOutputStream %s",name.c_str());
}

ZLbadaFileOutputStream::~ZLbadaFileOutputStream() {
	close();
}

bool ZLbadaFileOutputStream::open() {
	 AppLog("ZLbadaFileOutputStream::open");
	close();
//TODO сделать временные файлы
	//myTemporaryName = myName + ".XXXXXX" + '\0';
	myTemporaryName = myName + '\0';// + ".XXXXXX" + '\0';
	// AppLog("myTemporaryName %s",myTemporaryName.c_str());
	//mode_t currentMask = umask(S_IRWXO | S_IRWXG);
	// AppLog("umask");
	//int temporaryFileDescriptor = ::mkstemp(const_cast<char*>(myTemporaryName.data()));
	// AppLog("mkstemp");
	//umask(currentMask);
	//if (temporaryFileDescriptor == -1) {
	//	return false;
	//}

	//myFile = fdopen(temporaryFileDescriptor, "w+");
	 myFile = fopen(const_cast<char*>(myName.data()), "w+");
	// AppLog("fopen");
	return myFile != 0;
}

void ZLbadaFileOutputStream::write(const char *data, size_t len) {
	if (::fwrite(data, 1, len, myFile) != len) {
		myHasErrors = true;
	}
}

void ZLbadaFileOutputStream::write(const std::string &str) {
	if (::fwrite(str.data(), 1, str.length(), myFile) != (size_t)str.length()) {
		myHasErrors = true;
	}
}

void ZLbadaFileOutputStream::close() {
	if (myFile != 0) {
		::fclose(myFile);
		myFile = 0;
		//if (!myHasErrors) {
		//	rename(myTemporaryName.c_str(), myName.c_str());
		//}
	}
}
