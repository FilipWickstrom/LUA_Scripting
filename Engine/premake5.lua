project "Game"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
	linkoptions { "-IGNORE:4098"}
    targetdir("build/bin/" .. outputdir .. "/%{prj.name}")
    objdir("build/bin-int/" .. outputdir .. "/%{prj.name}")

	
	-- Define the location of pre-compiled header.
    --pchheader "EnginePCH.h"
	--pchsource "src/EnginePCH.cpp"

    -- Define the location(s) of files.
    files {
        "src/**.h",
		"src/**.cpp",
		"script/**.*"
    }


    -- Define any includes of folder(s).
    -- Useful to remove any "../folder/file.h" in code.
    includedirs {
        "src",
        "../Engine/src",
        "../ThirdParty/irrlicht/include/",
		"../ThirdParty/lua/include"
    }

    vpaths {
		["Lua Scripts"] = { "**.lua" },
		
		["Camera"] 			= { "**Camera.*" },
		
		["Game"] 			= { "**Game.*" },
		
		["Input"]			= { "**InputHandler.*"},
		
		["Lua Managers"] 	= { "**EnemyManager.*" },
		
		["Managers"]		= { "**Graphics.*", "**LuaHandler.*", "**SceneManager.*" },
		
		["Modules"] 		= {},
			
		["Object"]			= { "**Model.*", "**Object.*" },
		
		["Scene"]			= { "**Scene.*" },
    }

    filter {"system:windows"}
        defines {
            "WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }
		--Windows specific for now
        postbuildcommands {
			{ "copy ..\\ThirdParty\\irrlicht\\lib\\Irrlicht.dll build\\bin\\" .. outputdir ..  "\\Game\\Irrlicht.dll" }
        }

    filter {"configurations:Debug"}
        kind "ConsoleApp"
        staticruntime "on"
        runtime "Debug"
        defines{"_DEBUG", "_UNICODE", "UNICODE"}
        symbols "on"
        libdirs{
			"../ThirdParty/lua/lib/",
			"../ThirdParty/irrlicht/lib/"
		}
		links {
			"LuaLibD.lib",
			"Irrlicht.lib"
		}

    filter {"configurations:Release"}
        kind "ConsoleApp"
        staticruntime "on"
        runtime "Release"
        defines{"NDEBUG", "_UNICODE", "UNICODE"}
        optimize "on"
        libdirs{
			"../ThirdParty/lua/lib/",
			"../ThirdParty/irrlicht/lib/"
		}
		links {
			"LuaLib.lib",
			"Irrlicht.lib"
		}