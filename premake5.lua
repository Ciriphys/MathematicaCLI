workspace "Mathematica"
    architecture "x64"
    configurations { "Debug", "Release", "Distribution", "ProfilerDebug", "ProfilerRelease", "ProfilerDistribution" }

    output = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    project "Mathematica"
        location "Build"
        language "C++"
        cppdialect "C++17"
        kind "ConsoleApp"

        targetdir   ( "Binaries/" .. output .. "/%{prj.name}" )
        objdir      ( "Binaries/Objects/" .. output .. "/%{prj.name}" )

        files { "Build/Source/**.cpp", "Build/Include/**.h" }
        includedirs { "Build/Source/CLI", "Build/Source/Core", "Build/Include", "Build/Include/CLI" }

        pchheader "mthpch.h"
        pchsource "Build/Source/mthpch.cpp"

        filter "system:Windows"
            staticruntime "On"
            systemversion "latest"
            system "windows"
            defines { "MTH_WIN", "MTH_PLATFORM=\"Windows\"" }

        filter "system:Macosx"     
            system "macosx"
            defines { "MTH_MACOS", "MTH_PLATFORM=\"Apple\"" }

        filter "system:Linux"
            pic "On"
            system "linux"
            defines { "MTH_LINUX", "MTH_PLATFORM=\"Linux\"" }

        filter { "configurations:Debug" }
            defines { "MTH_DEBUG", "DEBUG", "MTH_CONFIG=\"Debug\"" }
            optimize "Debug"
            symbols "On"

        filter { "configurations:ProfilerDebug" }
            defines { "MTH_DEBUG", "DEBUG", "MTH_CONFIG=\"Debug\"", "MTH_USE_PROFILER" }
            optimize "Debug"
            symbols "On"
        
        filter { "configurations:Release" }
            defines { "MTH_RELEASE", "NDEBUG", "MTH_CONFIG=\"Release\"" }
            optimize "On"
            symbols "Default"

        filter { "configurations:ProfilerRelease" }
            defines { "MTH_RELEASE", "NDEBUG", "MTH_CONFIG=\"Release\"", "MTH_USE_PROFILER" }
            optimize "On"
            symbols "Default"

        filter { "configurations:Distribution" }
            defines { "MTH_DISTRIBUTION", "NDEBUG", "MTH_CONFIG=\"Distribution\"" }
            optimize "Full"
            symbols "Off"

        filter { "configurations:ProfilerDistribution" }
            defines { "MTH_DISTRIBUTION", "NDEBUG", "MTH_CONFIG=\"Distribution\"", "MTH_USE_PROFILER" }
            optimize "Full"
            symbols "Off"