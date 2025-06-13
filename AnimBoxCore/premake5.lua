project "AnimBoxCore"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    -- will make MD for release and dist and MDd for debug
    staticruntime "off"

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
		"GLFW_INCLUDE_NONE"
	}


    includedirs
	{
		"src",
	}

	links
	{
	}

    filter "system:windows"
		systemversion "latest"

		defines
		{
		}

		links
		{
		}

    filter "configurations:Debug"
		defines "AB_DEBUG"
		runtime "Debug"
		symbols "on"

		links
		{
		}

    filter "configurations:Release"
		defines "AB_RELEASE"
		runtime "Release"
		optimize "on"

		links
		{
		}

	filter "configurations:Dist"
		defines "AB_DIST"
		runtime "Release"
		optimize "on"

		links
		{
		}