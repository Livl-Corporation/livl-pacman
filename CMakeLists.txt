# Set the minimum required version of CMake for this project
cmake_minimum_required(VERSION 3.7)

# Set the project name and specify that it uses the C language
project(Pacman LANGUAGES C)

# Add the "modules" directory to the CMake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

# Find the SDL2 and SDL2_mixer libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Add warning flags
if (MSVC)
	# Use warning level 4 for MSVC
	add_compile_options(/W4)
else()
	# Use additional warnings for other compilers
	add_compile_options(-Wall -Wextra)
endif()

# Recursively find all source and header files in the "src" directory
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
		${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
		${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

# Add an executable target for the project using the found source files
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${SDL2_INCLUDE_DIRS})

# Add the "src" directory to the include path for the project
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add the SDL2 include directories to the include path for the project
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})

# Define "SDL_MAIN_HANDLED" for the project
target_compile_definitions(${PROJECT_NAME} PRIVATE "SDL_MAIN_HANDLED")

# Link the project with the SDL2 and SDL2_mixer libraries and the math library ('m')
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES} m)

# Set this project as the startup project in Visual Studio
IF (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
ENDIF()
