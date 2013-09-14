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


#ifndef __SQLITESTATEMENT_H__
#define __SQLITESTATEMENT_H__

#include <FIo.h>
#include <vector>
#include <string>
using namespace Tizen::Io;
using namespace Tizen::Base;

class SQLiteStatement {
private:
	std::vector<String> params;
	Database *pDb;
	DbEnumerator* pEnum;
	SQLiteStatement(Database *db, const char *zSql, const char **pzTail);
	//~SQLiteStatement();
	std::vector<char*> myCharBuffer;
	String SQLstring;
public:
	~SQLiteStatement();
	DbStatement* pStmt;
	char* GetCString(const String& sBadaStr);
	int bind_parameter_index(const char *zName);
	const char *bind_parameter_name(int num);
	int column_count();
	int column_type(int iCol);
	int column_int(int iCol);
	double column_double(int iCol);
	const unsigned char *column_text(int iCol);
	int bind_parameter_count();
	int bind_null(int num);
	int bind_int(int num, int val);
	int bind_double(int num, double val);
	int bind_text(int num, const char* val);
	int step();
	int reset();
	int finalize();
	static int prepare(Database *db, const char *zSql, SQLiteStatement** ppStmt, const char **pzTail);
};


#endif /* __SQLITESTATEMENT_H__ */
