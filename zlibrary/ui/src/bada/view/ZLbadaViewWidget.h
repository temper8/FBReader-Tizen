/*
 * ZLbadaViewWidget.h
 *
 *  Created on: 12.10.2011
 *      Author: Alex
 */

#ifndef ZLBADAVIEWWIDGET_H_
#define ZLBADAVIEWWIDGET_H_

#include "ZLViewWidget.h"
#include "ZLApplication.h"
#include "../application/ZLbadaApplicationWindow.h"
#include "badaForm.h"

class ZLbadaViewWidget: public ZLViewWidget {

public:
	ZLbadaApplicationWindow *myWindows;
    badaForm *mybadaForm;
    Tizen::Graphics::Canvas* myCanvas;
	virtual void setScrollbarEnabled(ZLView::Direction direction, bool enabled);
	virtual void setScrollbarPlacement(ZLView::Direction direction, bool standard);
	virtual void setScrollbarParameters(ZLView::Direction direction, size_t full, size_t from, size_t to);

//	virtual setOrientation(ZLView::Angle angle);

	//void setView(shared_ptr<ZLView> view);
    void doAction(std::string &actionId);
    void repaint();
	ZLbadaViewWidget(ZLView::Angle initialAngle);
	virtual ~ZLbadaViewWidget();
};

#endif /* ZLBADAVIEWWIDGET_H_ */
