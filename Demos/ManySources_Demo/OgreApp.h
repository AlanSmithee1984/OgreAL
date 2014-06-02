#ifndef _OGRE_APP_H_
#define _OGRE_APP_H_

#include <OgreCamera.h>
#include <OgreConfigFile.h>
#include <OgreEntity.h>
#include <OgreException.h>
#include <OgreLight.h>
#include <OgreLogManager.h>
#include <OgreMeshManager.h>
#include <OgreOverlayContainer.h>
#include <OgreRoot.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>

#include "Listener.h"
#include "OgreAL.h"

using namespace Ogre;

class OgreApp
{
	public:
		OgreApp();
		~OgreApp();
		void start();

	protected:
		void createScene();	
	
	private:
		DeviceListener *listener;		// Listener
		Root *root;						// Root SceneNode
		SceneManager *sceneMgr;			// Current SceneManager
		Camera *camera;					// Cameras attached to each viewport
		Viewport *viewPort;				// Viewports to render into
		RenderWindow *win;				// Ogre Window
		Entity *ent;					// The entity of the object we are animating
		SceneNode *node;				// The SceneNode of the Entity
		Light *light;					// A spotlight on the scene
		OgreAL::Sound *sound;
		OgreAL::SoundManager *soundManager;
};
#endif
