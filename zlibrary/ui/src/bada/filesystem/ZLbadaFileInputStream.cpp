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

#include "ZLbadaFileInputStream.h"

ZLbadaFileInputStream::ZLbadaFileInputStream(const std::string &name) : myName(name), myNeedRepositionToStart(false) {
	myFile = 0;
}

ZLbadaFileInputStream::~ZLbadaFileInputStream() {
	close();
	if (myFile != 0) {
		fclose(myFile);
	}
}

bool ZLbadaFileInputStream::open() {
	close();
	if (myFile == 0) {
		myFile = fopen(myName.c_str(), "rb");
		AppLog("fopen %s", myName.c_str() );
		AppLog("myFile %d", myFile );
	} else {
		//fseek(myFile, 0, SEEK_SET);
		myNeedRepositionToStart = true;
	}
	return myFile != 0;
}

size_t ZLbadaFileInputStream::read(char *buffer, size_t maxSize) {
//	AppLog(" ZLbadaFileInputStream::read %d",maxSize);
//	AppLog(" myFile %d",myFile);
	if (buffer != 0) {
		if (myNeedRepositionToStart) {
			fseek(myFile, 0, SEEK_SET);
			myNeedRepositionToStart = false;
		}
		return fread(buffer, 1, maxSize, myFile);
	} else {
		if (myNeedRepositionToStart) {
			fseek(myFile, maxSize, SEEK_SET);
			myNeedRepositionToStart = false;
			return ftell(myFile);
		} else {
			int pos = ftell(myFile);
			fseek(myFile, maxSize, SEEK_CUR);
			return ftell(myFile) - pos;
		}
	}
}

void ZLbadaFileInputStream::close() {
//	AppLog(" ZLbadaFileInputStream::close myFile %d",myFile);
	if (myFile != 0) {
		fclose(myFile);
    	myFile = 0;
}
}

size_t ZLbadaFileInputStream::sizeOfOpened() {
	if (myFile == 0) {
		return 0;
	}
	long pos = ftell(myFile);
	fseek(myFile, 0, SEEK_END);
	long size = ftell(myFile);
	fseek(myFile, pos, SEEK_SET);
	return size;
}

void ZLbadaFileInputStream::seek(int offset, bool absoluteOffset) {
//	AppLog(" ZLbadaFileInputStream::seek %d",offset);
	if (myNeedRepositionToStart) {
		absoluteOffset = true;
		myNeedRepositionToStart = false;
	}
//	AppLog(" myFile %d",myFile);
	fseek(myFile, offset, absoluteOffset ? SEEK_SET : SEEK_CUR);
}

size_t ZLbadaFileInputStream::offset() const {
//	AppLog(" ZLbadaFileInputStream::offset ");
	return myNeedRepositionToStart ? 0 : ftell(myFile);
}
