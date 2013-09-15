/*
 * ZLBadaViewWidget.cpp
 *
 *  Created on: 12.10.2011
 *      Author: Alex
 */

#include "ZLbadaViewWidget.h"
#include "badaForm.h"
#include "ZLbadaPaintContext.h"

void ZLbadaViewWidget::doAction(std::string &actionId){
	myWindows->application().doAction(actionId);
}

ZLbadaViewWidget::ZLbadaViewWidget(ZLView::Angle initialAngle): ZLViewWidget(initialAngle), myCanvas(null) {
}

ZLbadaViewWidget::~ZLbadaViewWidget() {

}

//void ZLbadaViewWidget::setView(shared_ptr<ZLView> view){
//	badaForm->myView = view;
//}


void ZLbadaViewWidget::repaint() {
	int angle = myWindows->application().AngleStateOption.value();
	AppLog("AngleStateOption2 %d", angle);
	mybadaForm->setOrientation(angle);
	// Draw and Show the form
	//mybadaForm->Draw();
	//mybadaForm->Show();
    if (mybadaForm == null ) return;
	Rectangle formRect = mybadaForm->GetClientAreaBounds();

	if (myCanvas) delete myCanvas;

	myCanvas = new Canvas();
	myCanvas->Construct(formRect);


	ZLbadaPaintContext &context = (ZLbadaPaintContext&)view()->context();
	context.pCanvas = myCanvas;
	context.myHeight = formRect.height;
	context.myWidth = formRect.width;
	//context.restoreFont();
	view()->paint();
	//mybadaForm->RequestRedraw(true);
	mybadaForm->Invalidate(false);
	AppLog("ZLbadaViewWidget::repaint()");

}

void ZLbadaViewWidget::setScrollbarEnabled(ZLView::Direction direction, bool enabled){
	AppLog("ZLbadaViewWidget::setScrollbarEnabled");
}

void ZLbadaViewWidget::setScrollbarPlacement(ZLView::Direction direction, bool standard){
	AppLog("ZLbadaViewWidget::setScrollbarPlacement");
}
void ZLbadaViewWidget::setScrollbarParameters(ZLView::Direction direction, size_t full, size_t from, size_t to){
	AppLog("ZLbadaViewWidget::setScrollbarParameters");
}

