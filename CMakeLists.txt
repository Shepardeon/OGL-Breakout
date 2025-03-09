cmake_minimum_required(VERSION 3.10.0)
project(Breakout VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(lib/glfw-3.4)
add_subdirectory(lib/glad)
add_subdirectory(lib/glm)
add_subdirectory(lib/stb_image)

# MY_SOURCES is defined to be a list of all the source files for my game 
# DON'T ADD THE SOURCES BY HAND, they are already added with this macro
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable("${CMAKE_PROJECT_NAME}")

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})

target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE -static-libgcc -static-libstdc++)
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glfw glad glm stb_image)