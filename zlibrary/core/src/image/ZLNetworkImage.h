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

#ifndef __ZLNETWORKIMAGE_H__
#define __ZLNETWORKIMAGE_H__

#include <ZLImage.h>
#include <ZLMimeType.h>

class ZLFileImage;

class ZLNetworkImage : public ZLSingleImage {

public:
	ZLNetworkImage(shared_ptr<ZLMimeType> mimeType, const std::string &url);
	const shared_ptr<std::string> stringData() const;

private:
	shared_ptr<ZLExecutionData> synchronizationData() const;

private:
	const std::string myURL;
	std::string myFileName;
	mutable bool myIsSynchronized;
	mutable shared_ptr<ZLFileImage> myCachedImage;
};

#endif /* __ZLNETWORKIMAGE_H__ */
