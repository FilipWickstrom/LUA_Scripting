#pragma once

/*
	Internal input handler of keyboard or mouse events.
*/
class InputHandler : public irr::IEventReceiver
{
public:
	struct SMouseState
	{
		irr::core::position2di pos;
		bool leftButtonDown;
		SMouseState()
		{
			leftButtonDown = false;
		}
	}MouseState;

private:
	bool keyIsDown[irr::KEY_KEY_CODES_COUNT] = { false };

public:
	InputHandler()
	{
		for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
			keyIsDown[i] = false;
	};
	~InputHandler() = default;

	virtual bool OnEvent(const irr::SEvent& e)
	{
		if (e.EventType == irr::EET_KEY_INPUT_EVENT)
		{
			keyIsDown[e.KeyInput.Key] = e.KeyInput.PressedDown;
		}
		if (e.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			switch (e.MouseInput.Event)
			{
			case irr::EMIE_LMOUSE_PRESSED_DOWN:
			{
				MouseState.leftButtonDown = true;
				keyIsDown[irr::EKEY_CODE::KEY_LBUTTON] = true;

				break;
			}
			case irr::EMIE_LMOUSE_LEFT_UP:
			{
				MouseState.leftButtonDown = false;
				keyIsDown[irr::EKEY_CODE::KEY_LBUTTON] = false;
				break;
			}
			case irr::EMIE_MOUSE_MOVED:
			{
				MouseState.pos.X = e.MouseInput.X;
				MouseState.pos.Y = e.MouseInput.Y;
				break;
			}
			}
		}

		return false;
	}

	virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
	{
		return keyIsDown[keyCode];
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

	static InputHandler& GetInputHandler();
};