#pragma once

/*
	Internal input handler of keyboard or mouse events.
*/
class InputHandler : public irr::IEventReceiver
{
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
			// Here you can put in the communication with Lua is wanted.
			keyIsDown[e.KeyInput.Key] = e.KeyInput.PressedDown;
		}

		return false;
	}

	// Gets the Axis (Horizontal or Vertical) and returns a mapped value between -1 to 1
	float CheckKeyboard(const std::string& axis)
	{
		float value = 0.f;

		if (axis == "Vertical")
		{
			if (keyIsDown[irr::KEY_KEY_W])
			{
				value = 1.f;
			}
			else if (keyIsDown[irr::KEY_KEY_S])
			{
				value = -1.f;
			}
		}
		else if (axis == "Horizontal")
		{
			if (keyIsDown[irr::KEY_KEY_A])
			{
				value = 1.f;
			}
			else if (keyIsDown[irr::KEY_KEY_D])
			{
				value = -1.f;
			}
		}

		return value;
	}

	// This is used to check whether a key is being held down
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

public:

	static auto& Get();

	// Get the Axis mapped from -1 to 1.
	static float GetAxis(const std::string& axis);

	static bool IsKeyDown(irr::EKEY_CODE keyCode);

	static InputHandler& GetInputHandler();
};