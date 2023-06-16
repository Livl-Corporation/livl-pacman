cmake_minimum_required(VERSION 3.7)

project(Pacman LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Add warning flags
if (CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
elseif (CMAKE_C_COMPILER_ID MATCHES "MSVC")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
endif()

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
		${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
		${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE "SDL_MAIN_HANDLED")
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES} m ) # 'm' for the math library

IF (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
ENDIF()
