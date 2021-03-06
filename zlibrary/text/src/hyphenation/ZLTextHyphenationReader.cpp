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

#include "ZLTextHyphenationReader.h"
#include "ZLTextTeXHyphenator.h"

void ZLTextHyphenationReader::characterDataHandler(const char *text, size_t len) {
	if (myReadPattern) {
		myBuffer.append(text, len);
	}
}

static const std::string PATTERN = "pattern";

void ZLTextHyphenationReader::startElementHandler(const char *tag, const char**) {
	if (PATTERN == tag) {
		myReadPattern = true;
	}
}

void ZLTextHyphenationReader::endElementHandler(const char *tag) {
	if (PATTERN == tag) {
		myReadPattern = false;
		if (!myBuffer.empty()) {
		   myHyphenator->myPatternTable.push_back(new ZLTextTeXHyphenationPattern(myBuffer));
		}
		myBuffer.erase();
	}
}

ZLTextHyphenationReader::ZLTextHyphenationReader(ZLTextTeXHyphenator *hyphenator) {
	myHyphenator = hyphenator;
	myReadPattern = false;
}

ZLTextHyphenationReader::~ZLTextHyphenationReader() {
}
