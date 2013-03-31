#ifndef _B2APP_H_
#define _B2APP_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>
#include "ZLApplication.h"

/**
 * [B2App] application must inherit from Application class
 * which provides basic features necessary to define an application.
 */

class ZLbadaLibraryImplementation;

class badaApp :
	public Tizen::App::Application,
	public Tizen::System::IScreenEventListener
{
public:

	/**
	 * [badaApp] application must have a factory method that creates an instance of itself.
	 */

	static Tizen::App::Application* CreateInstance(void);
	static ZLApplication* ZLApp;
public:
	static void SetZLApplication(ZLApplication* a) { ZLApp = a; };
	void TestTest();
	badaApp();
	~badaApp();


public:


	// Called when the application is initializing.
	bool OnAppInitializing(Tizen::App::AppRegistry& appRegistry);

	// Called when the application is terminating.
	bool OnAppTerminating(Tizen::App::AppRegistry& appRegistry, bool forcedTermination = false);


	// Called when the application's frame moves to the top of the screen.
	void OnForeground(void);


	// Called when this application's frame is moved from top of the screen to the background.
	void OnBackground(void);

	// Called when the system memory is not sufficient to run the application any further.
	void OnLowMemory(void);

	// Called when the battery level changes.
	void OnBatteryLevelChanged(Tizen::System::BatteryLevel batteryLevel);

	// Called when the screen turns on.
	void OnScreenOn (void);

	// Called when the screen turns off.
	void OnScreenOff (void);
};

#endif
