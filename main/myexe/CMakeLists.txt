cmake_minimum_required(VERSION 3.12)

set(SOURCE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)

#Include the whole include directory for this directory
include_directories(${INCLUDE_FOLDER})

#Source files
set(SOURCES ${SOURCE_FOLDER}/main.cpp
			${SOURCE_FOLDER}/Shader.cpp
			${SOURCE_FOLDER}/Camera.cpp)

#Headers files (for IntelliSense)
set(HEADERS ${INCLUDE_FOLDER}/Shader.hpp
			${INCLUDE_FOLDER}/Camera.hpp)

#Main exec
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PUBLIC 
	glfw
	glad
	stb::stb
)

# Adding shader files inside output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy_directory
				   "${INCLUDE_FOLDER}/Shaders"
				   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Adding textures files inside output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy_directory
				   "${INCLUDE_FOLDER}/Textures"
				   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})