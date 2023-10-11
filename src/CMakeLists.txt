# Set the source files
set(SOURCE_FILES main.cpp Color.cpp Particle.cpp glad.c)
# Add the executable with the source files
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Tell the compiler where to find the header files
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

# Link the GLFW library
target_link_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/lib/libglfw3dll.a")

# Set the output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")