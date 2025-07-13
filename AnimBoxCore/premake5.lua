project "AnimBoxCore"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "PCH.h"
    pchsource "src/PCH.cpp"

    files
	{
		"src/**.h",
		"src/**.cpp",
	}

    defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}


    includedirs
	{
		"src",
		"%{wks.location}/vendor/glfw/include"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

    filter "system:windows"
		systemversion "latest"

		defines
		{
			"GLCORE_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

    filter "configurations:Debug"
		defines "AB_DEBUG"
		runtime "Debug"
		symbols "on"

    filter "configurations:Release"
		defines "AB_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AB_DIST"
		runtime "Release"
		optimize "on"