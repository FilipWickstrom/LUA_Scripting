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
			return true;
		}

		return false;
	}

	virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
	{
		return keyIsDown[keyCode];
	}

	void CheckKeyboard()
	{
		int x = 0, y = 0;

		if (IsKeyDown(irr::KEY_KEY_W))
		{
			y = 1;
		}
		else if (IsKeyDown(irr::KEY_KEY_S))
		{
			y = -1;
		}

		if (IsKeyDown(irr::KEY_KEY_A))
		{
			x = 1;
		}
		else if (IsKeyDown(irr::KEY_KEY_D))
		{
			x = -1;
		}

		lua_getglobal(LUA, "OnInput");
		lua_pushnumber(LUA, x);
		lua_pushnumber(LUA, y);
		lua_pcall(LUA, 2, 0, 0);
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


	// Get the Axis mapped from -1 to 1.
	static void CheckKeyboard();

	static bool IsKeyDown(irr::EKEY_CODE keyCode);

	static InputHandler& GetInputHandler();
};