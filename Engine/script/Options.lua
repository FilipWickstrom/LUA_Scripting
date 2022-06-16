local DriverType = 
{
   EDT_SOFTWARE		= 1, --maybe remove, does not work that good
   EDT_DIRECT3D9	= 4,
   EDT_OPENGL		= 5
}

local Window = 
{
	name		= "Budget Binding of Isaac",
	width		= 1920,
	height		= 1080,
	fullscreen	= false,
	vsync		= true,
	driverType	= DriverType.EDT_DIRECT3D9
}

return Window