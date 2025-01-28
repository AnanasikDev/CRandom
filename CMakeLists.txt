cmake_minimum_required(VERSION 3.0)
project(SFMLProject)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

# Set SFML directory
set(SFML_DIR "C:/SFML-2.5.1-mingw32/lib/cmake/SFML")

# Find SFML package
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

# Add executable
add_executable(SFMLProject src/shadervis.cpp)

# Link SFML libraries
target_link_libraries(SFMLProject sfml-graphics sfml-window sfml-system)

# Path to SFML bin folder containing DLLs
set(SFML_DLL_PATH "C:/SFML-2.5.1-mingw32/bin")

# Target where the executable is generated (this assumes your target is called 'SFMLProject')
set(TARGET_NAME "SFMLProject")

# Define the list of SFML DLL files to copy
set(SFML_DLL_FILES
    "${SFML_DLL_PATH}/sfml-graphics-2.dll"
    "${SFML_DLL_PATH}/sfml-window-2.dll"
    "${SFML_DLL_PATH}/sfml-system-2.dll"
    "${SFML_DLL_PATH}/sfml-graphics-d-2.dll"
    "${SFML_DLL_PATH}/sfml-window-d-2.dll"
    "${SFML_DLL_PATH}/sfml-system-d-2.dll"
)

# Add custom command to copy DLLs after the build
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SFML_DLL_FILES} $<TARGET_FILE_DIR:${TARGET_NAME}>
    COMMENT "Copying SFML DLLs to output directory"
)