local DriverType = 
{
   DIRECT3D9	= 4,
   OPENGL		= 5
}

local Window = 
{
	name		= "Budget Binding of Isaac",
	width		= 1920,
	height		= 1080,
	fullscreen	= false,
	vsync		= true,
	driverType	= DriverType.DIRECT3D9
}

return Window