# Set the project name
project(sub_glad)

# Add a library with the above sources
add_library(${PROJECT_NAME} 
    src/glad.c
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)