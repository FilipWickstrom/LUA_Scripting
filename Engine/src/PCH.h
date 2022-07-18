#pragma once

// Standard
#include <string>
#include <string_view>
#include <exception>
#include <chrono>
#include <iostream>
#include <sstream>
#include <fstream>
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include <memory>
#include <cassert> 
#include <unordered_map>
#include <vector>
#include <array>
#include <set>
#include <queue>
#include <condition_variable>
#include <bitset>
#include <algorithm>
#include <thread>

// Lua
#ifdef _DEBUG
#pragma comment(lib, "LuaLibD.lib")
#else
#pragma comment(lib, "Lualib.lib")
#endif
#include <lua.hpp>

// Irrlicht
#pragma comment(lib, "Irrlicht.lib")
#include <irrlicht.h>

// Singletons
#include "Graphics.h"
#include "Graphics2D.h"
#include "LuaState.h"
#include "InputHandler.h"
#include "SceneHandler.h"

// Paths
const std::string SPRITEPATH	= "../Assets/Sprites/";
const std::string FONTPATH		= "../Assets/Fonts/";
const std::string SCRIPTSPATH	= "script/";

//Sprite modifier - larger value means smaller sprites
const float SPRITE_SIZE_MODIFIER = 4.f;

/*
	DEBUG 
*/
// Option to show UI area
#define DEBUG_UI 0
#define DEBUG_AABB_HITBOXES 0
#define DEBUG_CIRCULAR_HITBOXES 0

#define DEBUG_LUA_GLOBALS 1

/*
	Code comments
*/
// [TODO]		- Need to be done 
// [OPTIMIZE]	- Code can be optimized for better performance
