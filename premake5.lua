workspace "Mathematica"
    architecture "x64"
    configurations { "Debug", "Release", "ProfilerDebug", "ProfilerRelease" }

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

        filter "system:Windows"
            staticruntime "On"
            systemversion "latest"
            system "windows"
            defines { "MTH_WIN", "MTH_PLATFORM=\"Windows\"" }

            pchheader "mthpch.h"
            pchsource "Build/Source/mthpch.cpp"

        filter "system:Macosx"     
            system "macosx"
            defines { "MTH_MACOS", "MTH_PLATFORM=\"Apple\"" }

            pchheader "Include/mthpch.h"
            pchsource "Build/Source/mthpch.cpp"

        filter "system:Linux"
            pic "On"
            system "linux"
            defines { "MTH_LINUX", "MTH_PLATFORM=\"Linux\"" }

            pchheader "mthpch.h"
            pchsource "Build/Source/mthpch.cpp"

        filter { "configurations:Debug" }
            defines { "MTH_DEBUG", "DEBUG", "MTH_CONFIG=\"Debug\"" }
            optimize "Off"
            symbols "On"

        filter { "configurations:ProfilerDebug" }
            defines { "MTH_DEBUG", "DEBUG", "MTH_CONFIG=\"Debug\"", "MTH_USE_PROFILER" }
            optimize "Off"
            symbols "On"
        
        filter { "configurations:Release" }
            defines { "MTH_RELEASE", "NDEBUG", "MTH_CONFIG=\"Release\"" }
            optimize "On"
            symbols "Default"

        filter { "configurations:ProfilerRelease" }
            defines { "MTH_RELEASE", "NDEBUG", "MTH_CONFIG=\"Release\"", "MTH_USE_PROFILER" }
            optimize "On"
            symbols "Default"