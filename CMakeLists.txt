cmake_minimum_required(VERSION 3.7)

project(Pacman LANGUAGES C)

find_package(SDL2 REQUIRED)
find_library(SDL2_MIXER_LIBRARY SDL2_mixer PATHS ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL_mixer-release-2.6.3)  # Path to SDL_Mixer library

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
		${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
		${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${SDL2_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL_mixer-release-2.6.3/include)  # Add SDL_Mixer include directory
target_compile_definitions(${PROJECT_NAME} PRIVATE "SDL_MAIN_HANDLED")
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARY})  # Link against SDL2 and SDL_Mixer libraries

IF (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
ENDIF()