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


#include "SQLiteStatement.h"
#include "SQLiteDataBase.h"
#include <FTextAsciiEncoding.h>
#include <FBase.h>




using namespace Tizen::Text;
using namespace std;

SQLiteStatement::SQLiteStatement(Database *db, const char *zSql, const char **pzTail) {
	pDb = db;
	pEnum = 0;
	pStmt = 0;
	int i=0;
	String sql = "";
	String nVal = "";
	static const char *begin = "BEGIN";
	int pos = 0;
	bool isBegin = false;
	static const char *end = "END";
	bool isVal = false;
	while (zSql[i] != 0) {
		if (isVal) {
			if ((zSql[i] == ',') || (zSql[i] == ' ') ||(zSql[i] == ';') ||(zSql[i] == ')') || (zSql[i] == 0x13) || (zSql[i] == 0x10)) {
				sql.Append(zSql[i]);
				isVal = false;
				params.push_back(nVal);
				nVal = "";
			} else {
				nVal.Append(zSql[i]);
			}
		} else {
			if (zSql[i] == '@') {
				sql.Append("?");
				isVal = true;
				nVal = "@";
			} else {
				sql.Append(zSql[i]);
			}
		}
		if(isBegin) {
			if(zSql[i++]==end[pos]) {//можно добавить проверку на ограничительные символы
				pos++;
				if (end[pos]==0) {
					isBegin=false;
					pos=0;
				}
			} else {
				pos=0;
			}
		} else {
			if(zSql[i]==begin[pos]) {
				pos++;
				if (begin[pos]==0) {
					isBegin=true;
					pos=0;
				}
			} else {
				pos=0;
			}
			if (zSql[i++] == ';') {
				break;
			}
		}
	}
	if (nVal != "") {
		params.push_back(nVal);
	}
	*pzTail = &zSql[i];
	sql.Trim();
	if (sql != "") {
		AppLog( "sql !=0");
		 ByteBuffer* bb;
		 bb = Tizen::Base::Utility::StringUtil::StringToUtf8N(sql);
		 AppLog( "Stmt Create %s",(char *)bb->GetPointer());
		 SQLstring = sql;
		 pStmt = pDb->CreateStatementN(sql);
		 AppLog( "Stmt Create r= %d ", GetLastResult());

	} else {AppLog( "sql ==0");
		pStmt = 0;
	}
}

SQLiteStatement::~SQLiteStatement(){
//	AppLog( "~SQLiteStatement");
	const size_t size = myCharBuffer.size();
//	AppLog("myCharBuffer size = %d",size);
	for (size_t i = 0; i < size; ++i) {
		char* chPtrBuf = myCharBuffer[i];
		delete chPtrBuf;
	}
	 myCharBuffer.clear();
}

char* SQLiteStatement::GetCString(const String& sBadaStr) {
    if (sBadaStr.GetLength() == 0) return null;
    ByteBuffer* pBuffer = Tizen::Base::Utility::StringUtil::StringToUtf8N(sBadaStr);
 //   AppLog( "SQLiteStatement::GetCString %s",(char *)pBuffer->GetPointer());
    int byteCount = 0;
    if (pBuffer != null){
        byteCount = pBuffer->GetLimit();
        char* chPtrBuf = new char[byteCount + 1];
        if (chPtrBuf != null){
            	pBuffer->GetArray((byte*)chPtrBuf, 0, byteCount);
            	delete pBuffer;
            	myCharBuffer.push_back(chPtrBuf);
            	return chPtrBuf;
        		}
        delete pBuffer;
    	}

    return null;
}
int SQLiteStatement::bind_parameter_index(const char *zName){
	String parName = zName;
	int res = 0;
	int i=1;
	for (std::vector<String>::iterator it = params.begin(); it != params.end(); it++) {
		if (parName.Equals(*it, false)) {
			res = i;
			break;
		}
		i++;
	}
	return res;
}
const char *SQLiteStatement::bind_parameter_name(int num){
	std::vector<String>::iterator it = params.begin();
	it != params.end();
	it=it+(num-1);
	return GetCString(*it);
}
int SQLiteStatement::column_count(){
	if (pEnum) {
		return pEnum->GetColumnCount();
	} else {
		return 0;
	}
}
int SQLiteStatement::column_type(int iCol){
	if (pEnum) {
		switch (pEnum->GetColumnType(iCol)) {
			case DB_COLUMNTYPE_INT: return SQLITE_INTEGER;
			case DB_COLUMNTYPE_INT64: AppLog("COLUMNTYPE_INT64");return 0;
			case DB_COLUMNTYPE_DOUBLE: return SQLITE_FLOAT;
			case DB_COLUMNTYPE_TEXT: return SQLITE_TEXT;
			case DB_COLUMNTYPE_NULL: return SQLITE_NULL;
			default: return 0;
		}
	} else {
		return 0;
	}
}
int SQLiteStatement::column_int(int iCol){
	int res;
	pEnum->GetIntAt(iCol, res);
	return res;
}
double SQLiteStatement::column_double(int iCol){
	double res;
	pEnum->GetDoubleAt(iCol, res);
	return res;
}
const unsigned char *SQLiteStatement::column_text(int iCol){
	String res;
	pEnum->GetStringAt(iCol, res);
	return (unsigned char*)GetCString(res);
}
int SQLiteStatement::bind_parameter_count(){
	return params.size();
}
int SQLiteStatement::bind_null(int num){
	switch (pStmt->BindNull(num)) {
		case E_SUCCESS: return SQLITE_OK;
		default: return SQLITE_ERROR;
	}
}
int SQLiteStatement::bind_int(int num, int val){
	AppLog("Stmt bind_int %d", val);
	switch (pStmt->BindInt(num - 1, val)) {
		case E_SUCCESS: AppLog("Stmt OK"); return SQLITE_OK;
		default: AppLog("Stmt ERROR"); return SQLITE_ERROR;
	}
}
int SQLiteStatement::bind_double(int num, double val){
	switch (pStmt->BindDouble(num - 1, val)) {
		case E_SUCCESS: return SQLITE_OK;
		default: return SQLITE_ERROR;
	}
}
int SQLiteStatement::bind_text(int num, const char* val){
	AppLog("Stmt bind_text %s", val);
	switch (pStmt->BindString(num - 1, val)) {
		case E_SUCCESS: AppLog("Stmt OK");  return SQLITE_OK;
		default: AppLog("Stmt ERROR"); return SQLITE_ERROR;
	}
}
int SQLiteStatement::step(){
	AppLog("step");
	int res = E_INVALID_STATE ;
	if (!pEnum) {
		AppLog("Stmt sql %s", GetCString(SQLstring));
		pEnum = pDb->ExecuteStatementN(*pStmt);
		AppLog("Stmt Exe res %d", GetLastResult());
		if (pEnum) {
			res = pEnum->MoveNext();
			AppLog("Stmt MoveNext %d", res);
		} else {
			res = GetLastResult();
			AppLog("Stmt Exe res2 %d", res);
			if (res == E_SUCCESS) return SQLITE_DONE;
			if (res == E_OUT_OF_RANGE) return SQLITE_DONE;

		}
	} else {
		res = pEnum->MoveNext();
		AppLog("step res MoveNext  %d", res);
	}
	AppLog("Stmt switch res %d", res);
	switch (res) {
		case E_SUCCESS: return SQLITE_ROW;
		case E_OUT_OF_RANGE: AppLog("Stmt E_OUT_OF_RANGE"); return SQLITE_DONE;

		case E_INVALID_STATE: 	AppLog("E_INVALID_STATE"); 	return SQLITE_DONE;
		//case -1610610827: AppLog("1610610927"); return SQLITE_ROW;
		case E_OBJECT_LOCKED: 	AppLog("E_OBJECT_LOCKED"); 	return SQLITE_DONE;
		case E_INVALID_FORMAT: 	AppLog("E_INVALID_FORMAT"); return SQLITE_DONE;
		case E_IO: 				AppLog("E_IO"); 			return SQLITE_DONE;
		case E_SYSTEM: 			AppLog("E_SYSTEM"); 		return SQLITE_DONE;

		default: return SQLITE_ERROR;
	}
}
int SQLiteStatement::reset(){
	int res = E_SUCCESS;
	if (pEnum) {
		res = pEnum->Reset();
	}
	if (res == E_SUCCESS) {
		return SQLITE_OK;
	} else {
		return SQLITE_ERROR;
	}
}
int SQLiteStatement::finalize(){
	if (pStmt) delete pStmt;
	if (pEnum) delete pEnum;
	return SQLITE_OK;
}
int SQLiteStatement::prepare(Database *db, const char *zSql, SQLiteStatement** ppStmt, const char **pzTail) {
	AppLog("SQLiteStatement::prepare");
	if (zSql[0]==0) {
		*ppStmt = 0;
	} else {AppLog("new SQLiteStatement");
		*ppStmt = new SQLiteStatement(db, zSql, pzTail);
		if (*ppStmt == 0) AppLog("ppStmt == 0");
		AppLog("new SQLiteStatement 2");
		if ((*ppStmt)->pStmt==0) {
			AppLog("delete ppStmt");
			delete *ppStmt;
			*ppStmt = 0;
		}
		AppLog("new SQLiteStatement 3");
	}
	return SQLITE_OK;
}
