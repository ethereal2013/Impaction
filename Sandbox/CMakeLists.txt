file(GLOB_RECURSE SANDBOX_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(Sandbox ${SANDBOX_SOURCES})
target_link_libraries(Sandbox PRIVATE Impaction)

# Keep shader and texture paths relative to Sandbox's assets/ directory usable
# when CLion launches the executable from its build output directory.
add_custom_command(TARGET Sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:Sandbox>/assets"
        VERBATIM)
