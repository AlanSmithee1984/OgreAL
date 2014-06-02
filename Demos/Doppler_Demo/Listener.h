#ifndef _LISTENER_H_
#define _LISTENER_H_

#include "OgreCamera.h"
#include "OgreFrameListener.h"
#include "OgreOverlayManager.h"
#include "OgreRenderWindow.h"
#include "OgreStringConverter.h"
#include "Overlay/OgreTextAreaOverlayElement.h"
#include "OgreWindowEventUtilities.h"

#include "OIS/OISInputManager.h"
#include "OIS/OISKeyboard.h"
#include "OIS/OISMouse.h"

#include "OgreALListener.h"
#include "OgreALSoundManager.h"
#include "BetaGUI.h"

using namespace Ogre;

class DeviceListener : public FrameListener, public Ogre::WindowEventListener,
		public OIS::MouseListener, public OIS::KeyListener, public BetaGUI::BetaGUIListener
{
	public:
		DeviceListener(RenderWindow* win, Camera* cam, SceneManager *sceneMgr);
		~DeviceListener();

		// Frame event callbacks
		bool frameStarted(const FrameEvent& evt);
		//bool frameEnded(const FrameEvent& evt);

		// Window event callbacks
		virtual void windowResized(Ogre::RenderWindow* rw);
		virtual void windowClosed(Ogre::RenderWindow* rw);

		// Mouse event callbacks
		virtual bool mouseMoved(const OIS::MouseEvent &arg);
		virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){return false;}

		// Keyboard event callbacks
		virtual bool keyPressed(const OIS::KeyEvent &arg);
		virtual bool keyReleased(const OIS::KeyEvent &arg);

		void onButtonPress(BetaGUI::Button *ref, Ogre::uchar type);

	protected:
		OIS::Mouse *mMouse;
		OIS::Keyboard *mKeyboard;
		OIS::InputManager *mInputManager;
		Ogre::SceneManager *mSceneMgr;
		Ogre::SceneNode *mCamNode, *mPitchNode;
		Ogre::Camera *camera;
		Ogre::RenderWindow *mWindow;
		bool mContinue;
		Ogre::Degree pitch, yaw;
		Ogre::Vector3 mDirection;
		OgreAL::SoundManager *soundManager;
		SceneNode *carNode;
		Vector3 target;
		BetaGUI::GUI *mGui;
		BetaGUI::TextInput *doppler, *speed;
		BetaGUI::Button *dfUp01, *dfUp10, *dfDn01, *dfDn10;
		BetaGUI::Button *ssUp01, *ssUp10, *ssDn01, *ssDn10;
};
#endif
