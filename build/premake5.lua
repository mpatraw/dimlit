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

project "dimlit"
    kind "ConsoleApp"
    files "../src/main.cpp"
    includedirs {"/usr/local/include"}
    libdirs {"/usr/local/lib"}
    links {"dimlit-lib", "termbox"}
    targetdir "../bin"


if _OPTIONS["test"] then
    project "dimlit-test"
        kind "ConsoleApp"
        files "../test/main.cpp"
        links {"dimlit-lib"}
end
