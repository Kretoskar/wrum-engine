project "AnimBoxRuntime"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
	{
		"Public/**.h",
		"Public/**.cpp",
		"Private/**.h",
		"Private/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/AnimBoxCore/Public",
		"%{wks.location}/AnimBoxRuntime/Public",
		"%{wks.location}/vendor/glfw/include",
		"%{wks.location}/vendor/glad/include",
	}

	links
	{
		"AnimBoxCore"
	}

    filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"GLCORE_PLATFORM_WINDOWS"
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