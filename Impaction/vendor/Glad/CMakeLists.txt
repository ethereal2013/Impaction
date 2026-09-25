add_library(Glad STATIC src/glad.c)

target_include_directories(Glad PUBLIC include)

# glad loads GL through dlopen on Linux (CMAKE_DL_LIBS is empty on Windows)
target_link_libraries(Glad PUBLIC ${CMAKE_DL_LIBS})

# warnings "off"
if(MSVC)
    target_compile_options(Glad PRIVATE /w)
else()
    target_compile_options(Glad PRIVATE -w)
endif()
