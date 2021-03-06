#include "OgreApp.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
	try
	{
		OgreApp directionalDemo;
        directionalDemo.start();
    }
    catch(Exception& e)
    {
        #if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!",
            MB_OK | MB_ICONERROR | MB_TASKMODAL);
        #else
        fprintf(stderr, "An exception has occured: %s\n", e.getFullDescription().c_str());
        #endif

		LogManager::getSingleton().logMessage(e.getFullDescription().c_str());
    }
	return 0;
}
