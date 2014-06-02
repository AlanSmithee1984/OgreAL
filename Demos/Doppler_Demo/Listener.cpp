#include "Listener.h"

#define ROTATION_SPEED 10
#define MOVEMENT_SPEED 500

void DeviceListener::onButtonPress(BetaGUI::Button *ref, Ogre::uchar type)
{
	String textValue;
	Real floatValue;
	if(type == 1) // button down
	{
		if(ref == dfUp01)
		{
			textValue = doppler->getValue();
			floatValue = Ogre::StringConverter::parseReal(textValue);
			floatValue += 0.01;
			textValue = Ogre::StringConverter::toString(floatValue);
			doppler->setValue(textValue);
			OgreAL::SoundManager::getSingleton().setDopplerFactor(floatValue);
		}
		else if(ref == dfUp10)
		{
			textValue = doppler->getValue();
			floatValue = Ogre::StringConverter::parseReal(textValue);
			floatValue += 0.1;
			textValue = Ogre::StringConverter::toString(floatValue);
			doppler->setValue(textValue);
			OgreAL::SoundManager::getSingleton().setDopplerFactor(floatValue);
		}
		else if(ref == dfDn01)
		{
			textValue = doppler->getValue();
			floatValue = Ogre::StringConverter::parseReal(textValue);
			floatValue -= 0.01;
			if(floatValue < 0) floatValue = 0;
			textValue = Ogre::StringConverter::toString(floatValue);
			doppler->setValue(textValue);
			OgreAL::SoundManager::getSingleton().setDopplerFactor(floatValue);
		}
		else if(ref == dfDn10)
		{
			textValue = doppler->getValue();
			floatValue = Ogre::StringConverter::parseReal(textValue);
			floatValue -= 0.1;
			if(floatValue < 0) floatValue = 0;
			textValue = Ogre::StringConverter::toString(floatValue);
			doppler->setValue(textValue);
			OgreAL::SoundManager::getSingleton().setDopplerFactor(floatValue);
		}
		else if(ref == ssUp01)
		{
			textValue = speed->getValue();
			floatValue = Ogre::StringConverter::parseReal(textValue);
			floatValue += 1;
			textValue = Ogre::StringConverter::toString(floatValue);
			speed->setValue(textValue);
			OgreAL::SoundManager::getSingleton().setSpeedOfSound(floatValue);
		}
		else if(ref == ssUp10)
		{
			textValue = speed->getValue();
			floatValue = Ogre::StringConverter::parseReal(textValue);
			floatValue += 10;
			textValue = Ogre::StringConverter::toString(floatValue);
			speed->setValue(textValue);
			OgreAL::SoundManager::getSingleton().setSpeedOfSound(floatValue);
		}
		else if(ref == ssDn01)
		{
			textValue = speed->getValue();
			floatValue = Ogre::StringConverter::parseReal(textValue);
			floatValue -= 1;
			if(floatValue < 0) floatValue = 0;
			textValue = Ogre::StringConverter::toString(floatValue);
			speed->setValue(textValue);
			OgreAL::SoundManager::getSingleton().setSpeedOfSound(floatValue);
		}
		else if(ref == ssDn10)
		{
			textValue = speed->getValue();
			floatValue = Ogre::StringConverter::parseReal(textValue);
			floatValue -= 10;
			if(floatValue < 0) floatValue = 0;
			textValue = Ogre::StringConverter::toString(floatValue);
			speed->setValue(textValue);
			OgreAL::SoundManager::getSingleton().setSpeedOfSound(floatValue);
		}
	}
}

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
	params.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
	params.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));

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

	carNode = mSceneMgr->getSceneNode("CarNode");

	soundManager = OgreAL::SoundManager::getSingletonPtr();

	/******************* CREATE GUI ***************************/
	mGui = new BetaGUI::GUI("DopplerGui", "Arial", 14);
	BetaGUI::Window *mainWindow = mGui->createWindow(Vector4(mWindow->getWidth()-235, 10, 225, 95),
		"bgui.window", BetaGUI::MOVE, "Doppler Settings");
	mainWindow->createStaticText(Vector4(5, 25, 100, 15), "Doppler Factor:");
	doppler = mainWindow->createTextInput(Vector4(5, 40, 100, 20), "bgui.textinput", "1.0", 3);
	dfDn10 = mainWindow->createButton(Vector4(5, 65, 21, 24), "bgui.button", "<<", BetaGUI::Callback(this));
	dfDn01 = mainWindow->createButton(Vector4(31, 65, 21, 24), "bgui.button", "<", BetaGUI::Callback(this));
	dfUp01 = mainWindow->createButton(Vector4(57, 65, 21, 24), "bgui.button", " >", BetaGUI::Callback(this));
	dfUp10 = mainWindow->createButton(Vector4(83, 65, 21, 24), "bgui.button", ">>", BetaGUI::Callback(this));
	mainWindow->createStaticText(Vector4(115, 25, 100, 15), "Speed of Sound:");
	speed = mainWindow->createTextInput(Vector4(115, 40, 100, 20), "bgui.textinput", "343.3", 5);
	ssDn10 = mainWindow->createButton(Vector4(116, 65, 21, 24), "bgui.button", "<<", BetaGUI::Callback(this));
	ssDn01 = mainWindow->createButton(Vector4(142, 65, 21, 24), "bgui.button", "<", BetaGUI::Callback(this));
	ssUp01 = mainWindow->createButton(Vector4(168, 65, 21, 24), "bgui.button", " >", BetaGUI::Callback(this));
	ssUp10 = mainWindow->createButton(Vector4(194, 65, 21, 24), "bgui.button", ">>", BetaGUI::Callback(this));
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

		Ogre::Root::getSingleton().removeFrameListener(this);
		Ogre::Root::getSingleton().queueEndRendering();
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

	carNode->yaw(Degree(-100 * evt.timeSinceLastFrame));
	soundManager->getSound("BusSound")->setVelocity(carNode->getOrientation().zAxis() * 100);
	
	const RenderWindow::FrameStats& stats = mWindow->getStatistics();
	OverlayManager::getSingleton().getOverlayElement("TextAreaName")->setCaption(
		StringConverter::toString(mWindow->getAverageFPS()) +
		"\n\nDoppler:    Speed of Sound:\nF1 = Up    F3 = Up\nF2 = Down F6 = Down");

	return  mContinue;
}

// Mouse event callbacks
bool DeviceListener::mouseMoved(const OIS::MouseEvent &arg)
{
	if(arg.state.buttonDown(OIS::MB_Right))
	{
		// This populates the camera rotation variables
		yaw = -Degree(arg.state.X.rel * ROTATION_SPEED);
		pitch = -Degree(arg.state.Y.rel * ROTATION_SPEED);
	}
	else if(arg.state.buttonDown(OIS::MB_Left))
	{
		mGui->injectMouse(arg.state.X.abs, arg.state.Y.abs, true);
	}
	else
	{
		mGui->injectMouse(arg.state.X.abs, arg.state.Y.abs, false);
	}

	return true;
}

// MouseListener Callbacks
bool DeviceListener::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	mGui->injectMouse(arg.state.X.abs, arg.state.Y.abs, true);
	return true;
}

// KeyListener Callbacks
bool DeviceListener::keyPressed(const OIS::KeyEvent &arg)
{
	static int count = 0;
	float factor;
    switch(arg.key)
    {
		case OIS::KC_ESCAPE:
            mContinue = false;
            break;

		case OIS::KC_SYSRQ:
			mWindow->writeContentsToFile("ScreenShot"+StringConverter::toString(count++)+".png");
			break;

		case OIS::KC_F1:
			soundManager->setDopplerFactor(soundManager->getDopplerFactor() + 1.0);
			break;

		case OIS::KC_F2:
			factor = soundManager->getDopplerFactor();
			if(factor - 1.0 >= 0)
				soundManager->setDopplerFactor(factor - 1.0);
			break;

		case OIS::KC_F3:
			soundManager->setSpeedOfSound(soundManager->getSpeedOfSound() + 50.0);
			break;

		case OIS::KC_F4:
			factor = soundManager->getSpeedOfSound();
			if(factor - 50.0 >= 0)
				soundManager->setSpeedOfSound(factor - 50.0);
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
