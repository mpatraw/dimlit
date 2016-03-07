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
    buildoptions {"-Wall", "-Wextra", "-Wpedantic"}

filter "configurations:Release"
    defines {"NDEBUG"}
    optimize "On"

project "dimlit-lib"
    kind "StaticLib"
    files {"../src/**.cpp"}
    removefiles "../src/main.cpp"
    includedirs {"/usr/local/include"}

project "entityx"
    prebuildcommands { "if [ ! -f ../vendor/entityx/entityx/config.h ]; then cp config.h ../vendor/entityx/entityx/config.h; fi" }
    kind "StaticLib"
    files {
        "../vendor/entityx/entityx/*.cc",
        "../vendor/entityx/entityx/deps/*.cc",
        "../vendor/entityx/entityx/help/*.cc",
        "../vendor/entityx/entityx/tags/*.cc",
    }
    removefiles "../vendor/entityx/entityx/*_test.cc"
    includedirs {"../vendor/entityx"}
    buildoptions {"-Wno-unused-parameter", "-Wno-error=unused-variable", "-Wno-error=sign-compare"}

project "dimlit"
    kind "ConsoleApp"
    files "../src/main.cpp"
    includedirs {"/usr/local/include"}
    libdirs {"/usr/local/lib"}
    links {"dimlit-lib", "termbox", "entityx"}
    targetdir "../bin"


if _OPTIONS["test"] then
    project "dimlit-test"
        kind "ConsoleApp"
        files "../test/main.cpp"
        links {"dimlit-lib"}
end
