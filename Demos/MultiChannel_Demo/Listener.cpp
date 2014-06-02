#include "Listener.h"

#define ROTATION_SPEED 10
#define MOVEMENT_SPEED 500

DeviceListener::DeviceListener(RenderWindow* win, Camera* cam, SceneManager *sceneMgr)
{
    // Populate the camera and scene manager containers
    mSceneMgr = sceneMgr;
	camera = cam;
	mWindow = win;

	// Get the camera node
	mPitchNode = camera->getParentSceneNode();
    mCamNode = mPitchNode->getParentSceneNode();

    // continue rendering
    mContinue = true;

	// Initialize the direction vector
    mDirection = Vector3::ZERO;
    yaw = 0;
    pitch = 0;

	// Initialize OIS
	OIS::ParamList params;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	params.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem(params);

	if(mInputManager->getNumberOfDevices(OIS::OISMouse) > 0)
	{
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
		mMouse->setEventCallback(this);
	}
	if(mInputManager->getNumberOfDevices(OIS::OISKeyboard) > 0)
	{
		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
		mKeyboard->setEventCallback(this);
	}

	windowResized(mWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
}

DeviceListener::~DeviceListener()
{
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
}

void DeviceListener::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void DeviceListener::windowClosed(Ogre::RenderWindow* rw)
{
	if(rw == mWindow)
	{
		if(mInputManager)
		{
			mInputManager->destroyInputObject(mMouse);
			mInputManager->destroyInputObject(mKeyboard);

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
}

// Most code will go here. This gets called every frame
bool DeviceListener::frameStarted(const FrameEvent& evt)
{
	mMouse->capture();
	mKeyboard->capture();

	// Rotate the camera
    mCamNode->yaw(yaw * evt.timeSinceLastFrame);
    mPitchNode->pitch(pitch * evt.timeSinceLastFrame);
    // Reset the variables
    yaw = pitch = 0;

    // Move the camera
	mCamNode->translate(mPitchNode->_getDerivedOrientation() * mDirection * evt.timeSinceLastFrame);

	const RenderWindow::FrameStats& stats = mWindow->getStatistics();
	OverlayManager::getSingleton().getOverlayElement("TextAreaName")->setCaption(
		StringConverter::toString(mWindow->getAverageFPS()) +
		"\n\n5.1 Audio:\nF1 = Play\nF2 = Pause\nF3 = Stop");

	return  mContinue;
}

// Mouse event callbacks
bool DeviceListener::mouseMoved(const OIS::MouseEvent &arg)
{
	// This populates the camera rotation variables
	yaw = -Degree(arg.state.X.rel * ROTATION_SPEED);
    pitch = -Degree(arg.state.Y.rel * ROTATION_SPEED);
	return true;
}

// KeyListener Callbacks
bool DeviceListener::keyPressed(const OIS::KeyEvent &arg)
{
	static int count = 0;
	switch(arg.key)
    {
		case OIS::KC_ESCAPE:
            mContinue = false;
            break;

		case OIS::KC_SYSRQ:
			mWindow->writeContentsToFile("ScreenShot"+StringConverter::toString(count++)+".png");
			break;
			break;

		case OIS::KC_F1:
			OgreAL::SoundManager::getSingleton().getSound("5.1 Test")->play();
			break;

		case OIS::KC_F2:
			OgreAL::SoundManager::getSingleton().getSound("5.1 Test")->pause();
			break;

		case OIS::KC_F3:
			OgreAL::SoundManager::getSingleton().getSound("5.1 Test")->stop();
			break;

		case OIS::KC_UP:
		case OIS::KC_W:
            mDirection.z -= MOVEMENT_SPEED;
            break;

        case OIS::KC_DOWN:
		case OIS::KC_S:
            mDirection.z += MOVEMENT_SPEED;
            break;

        case OIS::KC_LEFT:
		case OIS::KC_A:
            mDirection.x -= MOVEMENT_SPEED;
            break;

        case OIS::KC_RIGHT:
		case OIS::KC_D:
            mDirection.x += MOVEMENT_SPEED;
            break;

		case OIS::KC_PGUP:
		case OIS::KC_E:
			mDirection.y += MOVEMENT_SPEED;
			break;

		case OIS::KC_PGDOWN:
		case OIS::KC_Q:
			mDirection.y -= MOVEMENT_SPEED;
			break;
    }
	return true;
}

bool DeviceListener::keyReleased(const OIS::KeyEvent &arg)
{
	switch(arg.key)
    {
		case OIS::KC_UP:
		case OIS::KC_W:
            mDirection.z += MOVEMENT_SPEED;
            break;

        case OIS::KC_DOWN:
		case OIS::KC_S:
            mDirection.z -= MOVEMENT_SPEED;
            break;

        case OIS::KC_LEFT:
		case OIS::KC_A:
            mDirection.x += MOVEMENT_SPEED;
            break;

        case OIS::KC_RIGHT:
		case OIS::KC_D:
            mDirection.x -= MOVEMENT_SPEED;
            break;

		case OIS::KC_PGUP:
		case OIS::KC_E:
			mDirection.y -= MOVEMENT_SPEED;
			break;

		case OIS::KC_PGDOWN:
		case OIS::KC_Q:
			mDirection.y += MOVEMENT_SPEED;
			break;
    }
	return true;
}
