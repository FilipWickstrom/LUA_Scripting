-- Solution configuration file.
workspace "ScriptingProject"
    system "Windows"
    architecture "x86_64"
    flags { 
        "MultiProcessorCompile" 
    }
    
    configurations {
        "Debug",
        "Release"
    }
	-- Set the startup project.
    startproject "Engine"
		targetname "Scripting"
	
	
	filter "platforms:*Static"
		kind "StaticLib"
	
	filter "platforms:*DLL"
		kind "SharedLib"



outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Subprojects.
include "Engine"
include "ThirdParty/lua"


-- Clean.
newaction {
    trigger = "clean",
    description = "Remove all binaries and intermediate binaries, and vs files.",
    execute = function()
        print("Removing binaries")
        os.rmdir("Engine/build/bin")

        print("Removing intermediate binaries")
        os.rmdir("Engine/build/bin-int")
		os.rmdir("ThirdParty/lua/obj")

        print("Removing project files")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
}