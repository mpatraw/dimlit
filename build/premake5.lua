newoption {
    trigger     = "test",
    description = "build tests"
}


workspace "dimlit"
    configurations {"Debug", "Release"}
    language "C++"
    buildoptions {"-std=c++14"}
    toolset "clang"

filter "configurations:Debug"
    defines {"DEBUG"}
    flags {"Symbols", "FatalWarnings"}
    buildoptions {"-Wall", "-Wextra", "-Wpedantic", "-Wno-unused-parameter"}

filter "configurations:Release"
    defines {"NDEBUG"}
    optimize "On"

project "dimlit-lib"
    kind "StaticLib"
    files {"../src/**.cpp"}
    removefiles "../src/main.cpp"
    includedirs {"/usr/local/include", "../vendor/anax/include"}

project "anax"
    prebuildcommands { "if [ ! -f ../vendor/anax/include/anax/Config.hpp ]; then cp AnaxConfig.hpp ../vendor/anax/include/anax/Config.hpp; fi" }
    kind "StaticLib"
    files {"../vendor/anax/src/anax/**.cpp"}
    includedirs {"../vendor/anax/include"}
    buildoptions {"-Wno-error=unused-variable", "-Wno-error=sign-compare"}


project "dimlit"
    kind "ConsoleApp"
    files "../src/main.cpp"
    includedirs {"/usr/local/include", "../vendor/anax/include"}
    libdirs {"/usr/local/lib"}
    links {"dimlit-lib", "termbox", "anax"}
    targetdir "../bin"


if _OPTIONS["test"] then
    project "dimlit-test"
        kind "ConsoleApp"
        files "../test/main.cpp"
        links {"dimlit-lib"}
end
