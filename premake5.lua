workspace "AnimBox"
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
group ""

group "AnimBox"
    include "AnimBoxCore"
    include "AnimBoxRuntime"
group ""