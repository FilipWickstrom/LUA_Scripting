
GUI	= {}

Scene = 
{
   NONE		= 0,
   MENU		= 1,
   GAME		= 2,
   EDITOR	= 3
}


function Start()
	local winWidth	= WinWidth()
	local winHeight	= WinHeight()
	
	-- TODO: Tweak layout depending on resolution

	btnSize			= { X = 250, Y = 100 }
	verticalSpace	= btnSize.Y * 1.5 

	GUI["Title"]= AddText("Scripting project", "roboto_48.xml", winWidth/2, 200, 800, 200)

	yDistance	= (-verticalSpace * 0.5)
	GUI["Play"] = AddButton("Play", "roboto_28.xml", winWidth/2, winHeight/2 + yDistance, btnSize.X, btnSize.Y)
	
	yDistance	= yDistance + verticalSpace
	GUI["Edit"] = AddButton("Edit", "roboto_28.xml", winWidth/2, winHeight/2 + yDistance, btnSize.X, btnSize.Y)
	
	yDistance	= yDistance + verticalSpace
	GUI["Quit"] = AddButton("Quit", "roboto_28.xml", winWidth/2, winHeight/2 + yDistance, btnSize.X, btnSize.Y)

end

function Clean()
	-- Go through all the GUI and remove it
	for key, value in next, GUI do
		RemoveGUI(value)
	end
end

function Update()
	-- Check if any of the buttons is clicked
	if (IsButtonPressed(GUI["Play"])) then
		ChangeScene(Scene.GAME)

	elseif(IsButtonPressed(GUI["Edit"])) then
		ChangeScene(Scene.EDITOR)

	elseif(IsButtonPressed(GUI["Quit"])) then
		ChangeScene(Scene.NONE)
	end

end

