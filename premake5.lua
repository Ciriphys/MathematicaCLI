workspace "Mathematica"
    architecture "x64"
    configurations { "Debug", "Release" }

    output = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    project "Mathematica"
        location "build"
        language "C++"
        cppdialect "C++17"
        kind "ConsoleApp"

        targetdir   ( "bin/" .. output .. "/%{prj.name}" )
        objdir      ( "bin/obj/" .. output .. "/%{prj.name}" )

        files { "build/src/**.cpp", "build/include/**.h" }
        includedirs { "build/src", "build/include" }

        pchheader "mthpch.h"
        pchsource "build/src/mthpch.cpp"

        filter "system:Windows"
            staticruntime "On"
            systemversion "latest"
            system "windows"

            defines { "MTH_WIN" }

        filter "system:Mac"     
            system "macosx"

        filter { "configurations:Debug" }
            defines { "MTH_DEBUG", "DEBUG" }
            symbols "On"
        
        filter { "configurations:Release" }
            defines { "MTH_RELEASE", "NDEBUG" }
            optimize "On"