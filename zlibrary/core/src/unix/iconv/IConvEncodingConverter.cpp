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

    // includes
    #include <FBase.h>
    #include <FText.h>

    // namespace
    using namespace Tizen::Base;
    using namespace Tizen::Text;


//#include <iconv.h>

#include <ZLUnicodeUtil.h>

#include "IConvEncodingConverter.h"

class IConvEncodingConverter : public ZLEncodingConverter {

private:
	IConvEncodingConverter(const std::string &encoding);
	~IConvEncodingConverter();

	void convert(std::string &dst, const char *srcStart, const char *srcEnd);
	void reset();
	bool fillTable(int *map);

private:
//	iconv_t
	Encoding* myIConverter;
	std::string myBuffer;

friend class IConvEncodingConverterProvider;
};

bool IConvEncodingConverterProvider::providesConverter(const std::string &encoding) {
//	AppLog("IConvEncodingConverterProvider::providesConverter %s",encoding.c_str());
	 Tizen::Base:: String bada_encoding(encoding.c_str());
	//iconv_t converter = iconv_open("utf-8", encoding.c_str());
	 result r = E_SUCCESS;
	 Encoding* pEnc = Encoding::GetEncodingN(bada_encoding);
	 // Encoding* pEnc = Encoding::GetEncodingN(L"ISO-8859-2");
	 // Exceptions:
	 // E_SUCCESS The method is successful.
	 // E_UNSUPPORTED_TYPE The specified encoding type is not supported.
	if (GetLastResult() == E_SUCCESS) {
			delete pEnc;
		//AppLog("true");
		return true;
	}
	//AppLog("false");
/*
	if (converter != (iconv_t)-1) {
		iconv_close(converter);
		return true;
	}*/
	return false;
}

shared_ptr<ZLEncodingConverter> IConvEncodingConverterProvider::createConverter(const std::string &encoding) {
	return new IConvEncodingConverter(encoding);
}

IConvEncodingConverter::IConvEncodingConverter(const std::string &encoding) {
//AppLog("IConvEncodingConverterProvider::IConvEncodingConverter %s",encoding.c_str());

//	myIConverter = iconv_open("utf-8", encoding.c_str());
}

IConvEncodingConverter::~IConvEncodingConverter() {
//	AppLog("IConvEncodingConverterProvider::~IConvEncodingConverter()");
//	if (myIConverter != (iconv_t)-1) {
		//iconv_close(myIConverter);
	//}
}

void IConvEncodingConverter::convert(std::string &dst, const char *srcStart, const char *srcEnd) {
	AppLog("IConvEncodingConverterProvider::convert()");
/*	if ((srcStart == srcEnd) || (myIConverter == (iconv_t)-1)) {
		return;
	}

	size_t inSize;
	char *in;
	if (myBuffer.empty()) {
		inSize = srcEnd - srcStart;
		in = (char*)srcStart;
	} else {
		myBuffer.append(srcStart, srcEnd - srcStart);
		inSize = myBuffer.length();
		in = (char*)myBuffer.data();
	}

	size_t outSize = 3 * inSize;
	const size_t startOutSize = outSize;
	size_t oldLength = dst.length();
	dst.append(outSize, '\0');
	char *out = (char*)dst.data() + oldLength;

iconvlabel:
#ifdef DO_ICONV_CAST
	iconv(myIConverter, (const char**)&in, &inSize, &out, &outSize);
#else // DO_ICONV_CAST
	iconv(myIConverter, &in, &inSize, &out, &outSize);
#endif // DO_ICONV_CAST
	if (inSize != 0) {
		if (myBuffer.empty()) {
			myBuffer.append(in, inSize);
		} else {
			myBuffer.erase(0, myBuffer.length() - inSize);
		}
	} else {
		myBuffer.erase();
	}
	if ((myBuffer.length() > 1) && (outSize == startOutSize)) {
		// looks like myBuffer contains incorrect character at start
		myBuffer.erase(0, 1);
		in = (char*)myBuffer.data();
		inSize = myBuffer.length();
		goto iconvlabel;
	}
	dst.erase(oldLength + startOutSize - outSize);
	*/
}

void IConvEncodingConverter::reset() {
	myBuffer.erase();
}

bool IConvEncodingConverter::fillTable(int *map) {
//	AppLog("IConvEncodingConverterProvider::fillTable()");
/*	if (myIConverter == (iconv_t)-1) {
		return false;
	}

	char inBuffer[1];
	char outBuffer[3];
	char *in, *out;
	size_t inSize, outSize;
	for (int i = 0; i < 256; ++i) {
		in = inBuffer;
		out = outBuffer;
		inSize = 1;
		outSize = 3;
		inBuffer[0] = i;
#ifdef DO_ICONV_CAST
		iconv(myIConverter, (const char**)&in, &inSize, &out, &outSize);
#else // DO_ICONV_CAST
		iconv(myIConverter, &in, &inSize, &out, &outSize);
#endif // DO_ICONV_CAST
		if (inSize == 0) {
			ZLUnicodeUtil::Ucs4Char ch;
			ZLUnicodeUtil::firstChar(ch, outBuffer);
			map[i] = ch;
		} else {
			map[i] = i;
		}

	}
	*/
	return false;
	//return true;

}
