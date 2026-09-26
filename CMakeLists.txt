cmake_minimum_required(VERSION 3.19)
project(Impaction LANGUAGES C CXX)

# ---- Configurations ---------------------------------------------------------
if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "" FORCE)
elseif(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

foreach(lang C CXX)
    set(CMAKE_${lang}_FLAGS_DIST "${CMAKE_${lang}_FLAGS_RELEASE}" CACHE STRING "")
endforeach()
set(CMAKE_EXE_LINKER_FLAGS_DIST    "${CMAKE_EXE_LINKER_FLAGS_RELEASE}"    CACHE STRING "")
set(CMAKE_SHARED_LINKER_FLAGS_DIST "${CMAKE_SHARED_LINKER_FLAGS_RELEASE}" CACHE STRING "")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-x64")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")

option(IMPCT_BUILD_SHARED "Build Impaction as a shared library" OFF)

# ---- Vendor libs ------------------------------------------------------------
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)

add_subdirectory(Impaction/vendor/GLFW)
add_subdirectory(Impaction/vendor/Glad)
add_subdirectory(Impaction/vendor/imgui)

find_package(OpenGL REQUIRED)

# ---- Impaction (engine) -----------------------------------------------------
file(GLOB_RECURSE IMPCT_SOURCES CONFIGURE_DEPENDS
    Impaction/src/*.cpp
    Impaction/vendor/stb_image/*.cpp
)

if(IMPCT_BUILD_SHARED)
    add_library(Impaction SHARED ${IMPCT_SOURCES})
    target_compile_definitions(Impaction
        PRIVATE IMPCT_BUILD_DLL
        PUBLIC  IMPCT_DYNAMIC_LINK)
else()
    add_library(Impaction STATIC ${IMPCT_SOURCES}
            Impaction/src/Platform/Linux/LinuxWindow.cpp
            Impaction/src/Platform/Linux/LinuxWindow.h
            Impaction/src/Impaction/Core/Window.cpp
            Impaction/src/Platform/Linux/LinuxInput.cpp
            Impaction/src/Platform/Linux/LinuxInput.h
            Impaction/src/Impaction/Core/Input.cpp)
endif()

target_include_directories(Impaction PUBLIC
    Impaction/src
    Impaction/vendor
    Impaction/vendor/spdlog/include
    Impaction/vendor/glm
    Impaction/vendor/stb_image
)

target_precompile_headers(Impaction PRIVATE Impaction/src/impct_pch.h)

target_link_libraries(Impaction PUBLIC Glad glfw ImGui OpenGL::GL)

target_compile_definitions(Impaction PUBLIC
    GLFW_INCLUDE_NONE
    $<$<CONFIG:Debug>:IMPCT_DEBUG>
    $<$<CONFIG:Release>:IMPCT_RELEASE>
    $<$<CONFIG:Dist>:IMPCT_DIST>
)

if(MSVC)
    target_compile_options(Impaction PUBLIC /utf-8)
    target_compile_definitions(Impaction PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

# ---- Sandbox ----------------------------------------------------------------
file(GLOB_RECURSE SANDBOX_SOURCES CONFIGURE_DEPENDS Sandbox/src/*.cpp)

add_executable(Sandbox ${SANDBOX_SOURCES})
target_link_libraries(Sandbox PRIVATE Impaction)   # inherits includes, defines, /utf-8

set_target_properties(Sandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}/Sandbox"
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Sandbox"
)

add_custom_command(TARGET Sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Sandbox/assets"
        "$<TARGET_FILE_DIR:Sandbox>/assets"
)

if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Sandbox)
endif()
