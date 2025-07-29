workspace "WrumEngine"
    architecture "x86_64"
	startproject "AnimBoxRuntime"

    configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/GLFW"
	include "vendor/glad"
group ""

group "WrumEngine"
    include "WrumCore"
    include "Sandbox"
group ""