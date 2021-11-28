find_package(SFML 2 REQUIRED COMPONENTS system graphics window)
set(sfml_libs sfml-system sfml-graphics sfml-window)

file(GLOB source_files CONFIGURE_DEPENDS "*.cpp")
add_executable(roboticarm ${source_files})
target_link_libraries(roboticarm PRIVATE ${sfml_libs} -lGL -lGLEW)

add_custom_command(TARGET roboticarm PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                           ${PROJECT_SOURCE_DIR}/shaders/ $<TARGET_FILE_DIR:roboticarm>)
