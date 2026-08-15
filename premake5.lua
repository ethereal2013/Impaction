workspace "Impaction"
architecture "x64"

configurations {
	"Debug",
	"Release",
	"Dist"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


IncludeDir = {}
IncludeDir["GLFW"] = "Impaction/vendor/GLFW/include"
IncludeDir["Glad"] = "Impaction/vendor/GLAD/include"
IncludeDir["ImGui"] = "Impaction/vendor/imgui"
IncludeDir["glm"] = "Impaction/vendor/glm"

include "Impaction/vendor/GLFW"
include "Impaction/vendor/Glad"
include "Impaction/vendor/imgui"

require "vstudio"

	local vcxproj = premake.vstudio.vc2010

	local function useBuiltinVcpkgApplocalDeps()
		premake.w('  <PropertyGroup>')
		premake.w('    <VcpkgXUseBuiltInApplocalDeps>true</VcpkgXUseBuiltInApplocalDeps>')
		premake.w('  </PropertyGroup>')
	end

	local function copyImpactionRuntimeToSandbox(prj)
		if prj.name ~= "Impaction" then
			return
		end

		premake.w('  <Target Name="CopyImpactionRuntimeToSandbox" AfterTargets="Build">')
		premake.w('    <MakeDir Directories="$(OutDir)..\\Sandbox\\" />')
		premake.w('    <Copy SourceFiles="$(TargetPath)" DestinationFolder="$(OutDir)..\\Sandbox\\" SkipUnchangedFiles="true" />')
		premake.w('  </Target>')
	end

	premake.override(vcxproj.elements, "project", function(base, prj)
		local calls = base(prj)
		table.insertafter(calls, vcxproj.userMacros, useBuiltinVcpkgApplocalDeps)
		table.insert(calls, copyImpactionRuntimeToSandbox)
		return calls
	end)

project "Impaction"
	location "Impaction"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "impct_pch.h"
	pchsource "Impaction/src/impct_pch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links {
		"Glad",
		"GLFW",
		"ImGui",

		"OpenGL32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		buildoptions {
			"/utf-8"
		}

		defines {
			"IMPCT_PLATFORM_WINDOWS",
			"IMPCT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "IMPCT_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "IMPCT_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "IMPCT_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Impaction/vendor/spdlog/include",
		"Impaction/src",
		"%{IncludeDir.glm}"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		buildoptions {
			"/utf-8"
		}

		defines {
			"IMPCT_PLATFORM_WINDOWS",
		}

		links {
			"Impaction"
		}

	filter "configurations:Debug"
		defines "IMPCT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "IMPCT_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "IMPCT_DIST"
		runtime "Release"
		optimize "On"
