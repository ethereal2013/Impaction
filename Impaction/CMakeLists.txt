set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/GLFW)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE IMPCT_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB IMGUI_SOURCES CONFIGURE_DEPENDS vendor/imgui/*.cpp)
file(GLOB STB_SOURCES CONFIGURE_DEPENDS vendor/stb_image/*.cpp)

set(IMGUI_BACKENDS "")
foreach(f
        vendor/imgui/backends/imgui_impl_glfw.cpp
        vendor/imgui/backends/imgui_impl_opengl3.cpp)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${f})
        list(APPEND IMGUI_BACKENDS ${f})
    endif()
endforeach()

add_library(Glad STATIC vendor/Glad/src/glad.c)
target_include_directories(Glad PUBLIC vendor/Glad/include)

add_library(Impaction STATIC
        ${IMPCT_SOURCES}
        ${IMGUI_SOURCES}
        ${IMGUI_BACKENDS}
        ${STB_SOURCES}
)

target_include_directories(Impaction PUBLIC
        src
        vendor/spdlog/include
        vendor/GLFW/include
        vendor/Glad/include
        vendor/imgui
        vendor/imgui/backends
        vendor/glm
        vendor/stb_image
)

target_compile_definitions(Impaction PUBLIC
        _CRT_SECURE_NO_WARNINGS
        GLFW_INCLUDE_NONE
        $<$<CONFIG:Debug>:IMPCT_DEBUG>
        $<$<CONFIG:Release>:IMPCT_RELEASE>
        $<$<CONFIG:Dist>:IMPCT_DIST>
)

target_include_directories(Impaction PUBLIC
        src
        vendor
        vendor/spdlog/include
        vendor/GLFW/include
        vendor/Glad/include
        vendor/imgui
        vendor/imgui/backends
        vendor/glm
        vendor/stb_image
)

target_precompile_headers(Impaction PRIVATE src/impct_pch.h)

target_link_libraries(Impaction PUBLIC
        glfw
        Glad
        OpenGL::GL
        ${CMAKE_DL_LIBS}
)

if(UNIX)
    target_link_libraries(Impaction PUBLIC pthread)
endif()