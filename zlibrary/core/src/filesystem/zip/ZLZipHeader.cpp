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
#include <ZLLogger.h>

#include "ZLZipHeader.h"
#include "ZLZDecompressor.h"
#include "../ZLInputStream.h"

const int ZLZipHeader::SignatureLocalFile = 0x04034B50;
const int ZLZipHeader::SignatureData = 0x08074B50;

bool ZLZipHeader::readFrom(ZLInputStream &stream) {
	AppLog("ZLZipHeader::readFrom 1");
	size_t startOffset = stream.offset();
	Signature = readLong(stream);
	switch (Signature) {
		default:
			return false;
		case SignatureLocalFile:
			//AppLog("ZLZipHeader::readFrom SignatureLocalFile");
			Version = readShort(stream);
			Flags = readShort(stream);
			CompressionMethod = readShort(stream);
			ModificationTime = readShort(stream);
			ModificationDate = readShort(stream);
			CRC32 = readLong(stream);
			CompressedSize = readLong(stream);
			UncompressedSize = readLong(stream);
			if (CompressionMethod == 0 && CompressedSize != UncompressedSize) {
				ZLLogger::Instance().println("zip", "Different compressed & uncompressed size for stored entry; the uncompressed one will be used.");
				CompressedSize = UncompressedSize;
			}
			NameLength = readShort(stream);
			ExtraLength = readShort(stream);
			return stream.offset() == startOffset + 30 && NameLength != 0;
		case SignatureData:
		//	AppLog("ZLZipHeader::readFrom SignatureData");
			CRC32 = readLong(stream);
			CompressedSize = readLong(stream);
			UncompressedSize = readLong(stream);
			NameLength = 0;
			ExtraLength = 0;
			return stream.offset() == startOffset + 16;
	}
}
const size_t BUFFER_SIZE = 2048;//*16;

void ZLZipHeader::skipEntry(ZLInputStream &stream, ZLZipHeader &header) {
	switch (header.Signature) {
		default:
			break;
		case SignatureLocalFile:
			if (header.Flags & 0x08) {
				stream.seek(header.ExtraLength, false);
				AppLog("ZLZDecompressor decompressor %d", (size_t)-1);
				ZLZDecompressor decompressor((size_t)-1);
				size_t size;
				do {
					//AppLog("ZLZipHeader::skipEntry 1");
					size = decompressor.decompress(stream, 0, BUFFER_SIZE);
					//AppLog("decompress size=%d",size);
					header.UncompressedSize += size;
				} while (size == BUFFER_SIZE);
				AppLog("header.UncompressedSize %d",header.UncompressedSize);
				//stream.seek(16, false);
			} else {
				stream.seek(header.ExtraLength + header.CompressedSize, false);
			}
			break;
	}
}

unsigned short ZLZipHeader::readShort(ZLInputStream &stream) {
	char buffer[2];
	stream.read(buffer, 2);
	return ((((unsigned short)buffer[1]) & 0xFF) << 8) + ((unsigned short)buffer[0] & 0xFF);
}

unsigned long ZLZipHeader::readLong(ZLInputStream &stream) {
	char buffer[4];
	stream.read(buffer, 4);

	return
		((((unsigned long)buffer[3]) & 0xFF) << 24) +
		((((unsigned long)buffer[2]) & 0xFF) << 16) +
		((((unsigned long)buffer[1]) & 0xFF) << 8) +
		((unsigned long)buffer[0] & 0xFF);
}
