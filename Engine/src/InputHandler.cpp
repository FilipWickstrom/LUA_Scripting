#include "PCH.h"
#include "InputHandler.h"

Input::Input()
{
}

Input::~Input()
{

}

auto& Input::Get()
{
    static Input instance;
    return instance;
}

bool Input::IsKeyDown(irr::EKEY_CODE keyCode)
{
    return Get().m_inputHandler.IsKeyDown(keyCode);
}

InputHandler& Input::GetInputHandler()
{
    return Get().m_inputHandler;
}
