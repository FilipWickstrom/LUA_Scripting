# Scripting project
This is a project where we made a small game with a level editor using C++ and LUA.

Main functionality is done in C++ and most of the game logic is within LUA. 

All of the C++ functions that can be used in LUA is starting with "C_"... in the function name.

# How to build and run
Build the visual studio project with "build.bat". 
It is building for VS2019, but can be easily changed to other versions of VS as well if needed by editing the file. 
Run the program in visual studio in "release" for best performance.

# Game
Movement is with "WASD" and "mouse1" is for shooting projectiles.
"Escape" can be used to go back to menu.
The goal of the game is to reach the finishline while avoiding all the dangerous monsters and escape the dungeon.

# Level editor
It is possible to move the camera with "WASD" and zoom in with "+" and out with "-" on the keyboard.

Place a tile with "mouse1" on an empty tile. 
Remove a tile with "mouse2". 
Tiles can be moved while holding "space".

There are 3 different layers that be choosed when placing, moving and removing tiles. 
These layers can be choosen in the right side of the screen by pressing the different buttons.

Exiting the editor can be done with "Escape" which sends the user back to the main menu.

With the buttons in the top left corner it is possible to:
1. Create a new level.
2. Load the saved level.
3. Save the current level to a file.

# Libraries and third parties
* [Irrlicht Engine (1.8.5)](https://irrlicht.sourceforge.io/)
* [LUA (5.4)](https://www.lua.org/home.html)
* [Premake (5)](https://premake.github.io/)
* [16x16 Dungeon Tileset](https://0x72.itch.io/16x16-dungeon-tileset)
* [16x16 Dungeon Tileset II](https://0x72.itch.io/dungeontileset-ii)
