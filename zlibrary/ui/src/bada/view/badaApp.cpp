/**
 * Name        : B2App
 * Version     : 
 * Vendor      : 
 * Description : 
 */


#include "badaApp.h"
#include "badaForm.h"
#include "../library/ZLBadaLibraryImplementation.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::System;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

badaApp::badaApp()
{
}

badaApp::~badaApp()
{
}
void badaApp::TestTest(){
	AppLog("B2App::TestTest");
}

Application* badaApp::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new badaApp();
}

bool badaApp::OnAppInitializing(AppRegistry& appRegistry)
{
	Frame* pAppFrame = new Frame();
	pAppFrame->Construct();
	AddFrame(*pAppFrame);

	PowerManager::SetScreenEventListener(*this);

	ZLbadaLibraryImplementation::SetBada2App(this);
	AppLog("B2App::OnAppInitializing");
	ZLbadaLibraryImplementation::createApplicationWindow();

 // Create a form
	AppLog("Create a form");
	badaForm *pbadaForm = new badaForm();
	pbadaForm->Initialize();

	// Add the form to the frame

	pAppFrame->AddControl(*pbadaForm);
	pAppFrame->SetBackgroundColor(Tizen::Graphics::Color::GetColor(COLOR_ID_BLUE));
	// Set the current form

	pAppFrame->SetCurrentForm(*pbadaForm);

	// Draw and Show the form
	pbadaForm->Invalidate(true);

	return true;
}

bool
badaApp::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this application for termination.
	// The application's permanent data and context can be saved via appRegistry.
	return true;
}

void
badaApp::OnForeground(void)
{
	// TODO:
	// Start or resume drawing when the application is moved to the foreground.
	AppLog("OnForeground");
}

void
badaApp::OnBackground(void)
{
	// TODO:
	// Stop drawing when the application is moved to the background.
	AppLog("OnBackground");
}

void
badaApp::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the application.
}

void
badaApp::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void
badaApp::OnScreenOn (void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
	AppLog("OnScreenOn");
}

void
badaApp::OnScreenOff (void)
{
	// TODO:
	//  Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
	AppLog("OnScreenOff");
}
