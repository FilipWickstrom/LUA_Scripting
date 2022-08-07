#pragma once

/*
	Internal input handler of keyboard or mouse events.
*/
class InputHandler : public irr::IEventReceiver
{
private:
	bool m_keyIsDown[irr::KEY_KEY_CODES_COUNT]		= { false };
	bool m_keyPressed[irr::KEY_KEY_CODES_COUNT]		= { false };
	bool m_keyReleased[irr::KEY_KEY_CODES_COUNT]	= { false };

public:
	InputHandler() = default;
	~InputHandler() = default;

	virtual bool OnEvent(const irr::SEvent& e)
	{
		if (e.EventType == irr::EET_KEY_INPUT_EVENT)
		{
			irr::EKEY_CODE key = e.KeyInput.Key;

			// Key is pressed now
			if (m_keyIsDown[key])
			{
				// Key has been released at this moment
				if (!e.KeyInput.PressedDown)
					m_keyReleased[key] = true;
			}
			// Key is not pressed now
			else
			{	
				// Key is changing state at this moment
				if (e.KeyInput.PressedDown)
					m_keyPressed[key] = true;
			}

			m_keyIsDown[key] = e.KeyInput.PressedDown;

			// Return true as we do not want to click 
			// gui buttons with space or return.
			if (key == irr::EKEY_CODE::KEY_SPACE ||
				key == irr::EKEY_CODE::KEY_RETURN)
				return true;
		}
		if (e.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			switch (e.MouseInput.Event)
			{
			case irr::EMIE_LMOUSE_PRESSED_DOWN:
			{
				irr::EKEY_CODE key = irr::EKEY_CODE::KEY_LBUTTON;

				// Check if key is changing state
				if (!m_keyIsDown[key])
					m_keyPressed[key] = true;

				m_keyIsDown[key] = true;
				break;
			}
			case irr::EMIE_LMOUSE_LEFT_UP:
			{
				irr::EKEY_CODE key = irr::EKEY_CODE::KEY_LBUTTON;

				// Check if key is changing state
				if (m_keyIsDown[key])
					m_keyReleased[key] = true;

				m_keyIsDown[key] = false;
				break;
			}
			case irr::EMIE_RMOUSE_PRESSED_DOWN:
			{
				irr::EKEY_CODE key = irr::EKEY_CODE::KEY_RBUTTON;

				// Check if key is changing state
				if (!m_keyIsDown[key])
					m_keyPressed[key] = true;

				m_keyIsDown[key] = true;
				break;
			}
			case irr::EMIE_RMOUSE_LEFT_UP:
			{
				irr::EKEY_CODE key = irr::EKEY_CODE::KEY_RBUTTON;

				// Check if key is changing state
				if (!m_keyIsDown[key])
					m_keyReleased[key] = true;

				m_keyIsDown[key] = false;

				break;
			}
			}
		}

		return false;
	}

	virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
	{
		return m_keyIsDown[keyCode];
	}

	virtual bool IsKeyReleasedOnce(irr::EKEY_CODE keyCode)
	{
		bool up = m_keyReleased[keyCode];
		if (up)
			m_keyReleased[keyCode] = false;
		return up;
	}

	virtual bool IsKeyPressedOnce(irr::EKEY_CODE keyCode)
	{
		bool down = m_keyPressed[keyCode];
		if (down)
			m_keyPressed[keyCode] = false;
		return down;
	}
};

/*
	User-friendly input controller.
*/
class Input
{
private:

	InputHandler m_inputHandler;
	Input();
	~Input();
	static auto& Get();

public:
	static bool IsKeyDown(irr::EKEY_CODE keyCode);
	static bool IsKeyPressedOnce(irr::EKEY_CODE keyCode);
	static bool IsKeyReleasedOnce(irr::EKEY_CODE keyCode);

	static InputHandler& GetInputHandler();
};