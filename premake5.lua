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
IncludeDir["stb_image"] = "Impaction/vendor/stb_image"

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

		premake.override(vcxproj.elements, "project", function(base, prj)
		local calls = base(prj)
		table.insertafter(calls, vcxproj.userMacros, useBuiltinVcpkgApplocalDeps)
		return calls
	end)

	local ImpctKind = "StaticLib"

project "Impaction"
	location "Impaction"
	kind(ImpctKind)
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	if ImpctKind == "SharedLib" then
		defines {
			"IMPCT_DYNAMIC_LINK",
			"IMPCT_BUILD_DLL"
		}
	end

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "impct_pch.h"
	pchsource "Impaction/src/impct_pch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links {
		"Glad",
		"GLFW",
		"ImGui",

		"OpenGL32.lib"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		systemversion "latest"

		buildoptions {
			"/utf-8"
		}

		defines {
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines "IMPCT_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "IMPCT_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "IMPCT_DIST"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Impaction/vendor/spdlog/include",
		"Impaction/src",
		"Impaction/vendor",
		"%{IncludeDir.glm}"
	}

	filter "system:windows"
		systemversion "latest"

		buildoptions {
			"/utf-8"
		}

		defines {
			"_CRT_SECURE_NO_WARNINGS",
		}


		links {
        "Impaction"
		}

	filter "configurations:Debug"
		defines "IMPCT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "IMPCT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "IMPCT_DIST"
		runtime "Release"
		optimize "on"
