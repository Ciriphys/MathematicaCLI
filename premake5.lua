workspace "Mathematica"
    architecture "x64"
    configurations { "Debug", "Release" }

    output = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    project "Mathematica"
        location "build"
        language "C++"
        cppdialect "C++17"
        kind "ConsoleApp"

        targetdir   ( "Binaries/" .. output .. "/%{prj.name}" )
        objdir      ( "Binaries/Objects/" .. output .. "/%{prj.name}" )

        files { "Build/Source/**.cpp", "Build/Include/**.h" }
        includedirs { "Build/Source", "Build/Include" }

        pchheader "mthpch.h"
        pchsource "Build/Source/mthpch.cpp"

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