/*
 * Gview.h
 *
 *  Created on: 13.10.2011
 *      Author: Alex
 */

#ifndef GVIEW_H_
#define GVIEW_H_

#include <FGraphics.h>

//#include "ZLView.h"
#include <ZLFile.h>
#include "ZLFileImage.h"

using namespace Tizen::Graphics;
using namespace Tizen::Base::Utility;
//class ZLViewWidget;
class ZLPaintContext;
class ZLView;


 class GView : public ZLView {
public:
	void ReadImage();
	shared_ptr<ZLImage> testImage;
	shared_ptr<ZLImageData> testImageData;
	Point CircleXY;
	virtual bool onStylusRelease(int x, int y);
	virtual void paint();
	GView(ZLPaintContext &context);
	virtual ~GView();
private:

};

#endif /* GVIEW_H_ */
