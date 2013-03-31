/*
 * Copyright (C) 2010 Geometer Plus <contact@geometerplus.com>
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

#include "ZLTypeId.h"

const ZLTypeId ZLObjectWithRTTI::TYPE_ID;

ZLTypeId::ZLTypeId() {
	AppLog("ZLTypeId::ZLTypeId()");
}

ZLTypeId::ZLTypeId(const ZLTypeId &base) {
	AppLog("ZLTypeId::ZLTypeId(const ZLTypeId &base)");
	myBase = &base;

}

bool ZLTypeId::isSubtypeOf(const ZLTypeId &type) const {
	for (const ZLTypeId *t = this; t != 0; t = t->myBase) {
		if (t == &type) {
			return true;
		}
	}
	return false;
}

bool ZLObjectWithRTTI::isInstanceOf(const ZLTypeId &type, bool exact) const {
	return exact ? typeId() == type : typeId().isSubtypeOf(type);
}
