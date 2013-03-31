/**
 * This file contains the bada application entry point.
 */

#include <ZLibrary.h>
#include "FBReader.h"
#include "ZLApplication.h"


using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

_EXPORT_ int OspMain(int argc, char *pArgv[]);

#ifdef _PROFILE
extern void start_profile (void);
extern void end_profile (void);
#else
#define start_profile()
#define end_profile()
#endif


/**
 * The entry function of bada application called by the operating system.
  */

int OspMain(int argc, char **argv)
{
	result r = E_SUCCESS;

	AppLog("Application started.");

	if (!ZLibrary::init(argc, argv)) {
		AppLog("ZLibrary::init failed");
		return 1;
		}


	//ZLibrary::run(new ZLApplication("FBReader"));
	ZLibrary::run(new FBReader(argc == 1 ? std::string() : argv[1]));
	ZLibrary::shutdown();



	AppLog("Application finished.");

	return static_cast<int>(r);
}
#ifdef __cplusplus
}
#endif // __cplusplus
