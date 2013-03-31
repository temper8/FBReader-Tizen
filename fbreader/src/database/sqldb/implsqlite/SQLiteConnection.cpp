/*
 * Copyright (C) 2009-2010 Geometer Plus <contact@geometerplus.com>
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

#include <iostream>

#include "SQLiteConnection.h"
#include "SQLiteDataBase.h"
#include "SQLiteStatement.h"

SQLiteConnection::SQLiteConnection(const std::string &name)
	: DBConnection() 
	, myName(name) 
	, myDatabase(0) {
}

SQLiteConnection::~SQLiteConnection() {
	if (isOpened()) {
		close();
	}
}


bool SQLiteConnection::open() {
	if (myDatabase != 0) {
		return true;
	}
	myDatabase = new Database();
	if (!myDatabase) return false;
	AppLog("myDatabase name = %s",myName.c_str());
	result r = myDatabase->Construct(myName.c_str(), true);
	//result r = myDatabase->Construct("/Home/books.db", true);
	if (!IsFailed(r)) return true;
	dumpError();
	if (myDatabase != 0) {
		  delete myDatabase;
		myDatabase = 0;
	}
	return false;
}

void SQLiteConnection::finalizeOpenedStatements() {
	size_t size = myStatements.size();
//	AppLog("finalizeOpenedStatements size = %d",size);
	for (size_t i = 0; i < size; ++i) {
		const int res = myStatements[i]->finalize();
		if (res != SQLITE_OK) {
			dumpError();
		}
	}
//	AppLog("myStatements.clear()");
	myStatements.clear();
//	AppLog("myStatements.clear() OK");
}

bool SQLiteConnection::close() {
	if (myDatabase == 0) {
		return true;
	}
	finalizeOpenedStatements();
	delete myDatabase;
	myDatabase = 0;
	return true;

}

void SQLiteConnection::dumpError() const {
	AppLog("dumpError");
	if (myDatabase != 0) {
		AppLog("dumpError 2");
	//	const std::string msg = sqlite3_errmsg(myDatabase); // TODO: error & message handling
	//	const int code = sqlite3_errcode(myDatabase); // TODO: error & message handling
	//	std::cerr << "SQLITE IMPLEMENTATION ERROR: (" << code << ") " << msg << std::endl;
	}
}
