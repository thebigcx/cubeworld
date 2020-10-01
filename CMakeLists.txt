cmake_minimum_required(VERSION 3.13) # Minimum CMake version
project(CubeWorld)                   # Create project 'CubeWorld'
set(CMAKE_CXX_STANDARD 20)           # Set the C++ standard VERSION

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin) # Set the binrary output directory

# Compile all files
file(GLOB SOURCES CONFIGURE_DEPENDS
src/util/stb_image/stb_image.cpp

src/Main.cpp
src/Game.cpp
src/Window.cpp
src/util/Color.cpp
src/Mesh.cpp
src/shader/Shader.cpp
src/player/Camera.cpp
src/player/Player.cpp
src/texture/Texture.cpp
src/Image.cpp
src/world/chunk/Chunk.cpp
src/world/chunk/ChunkMeshBuilder.cpp
src/world/chunk/ChunkManager.cpp
src/world/World.cpp
src/world/terrain/TerrainGenerator.cpp
src/texture/Skybox.cpp
src/player/MousePicker.cpp

src/util/math/Ray.cpp

src/world/block/Block.cpp

src/resource/ResourceManager.cpp
)

# Set the include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Build the executable
add_executable(CubeWorld ${SOURCES})

# Link the OpenGL libraries
target_link_libraries(CubeWorld glfw GL X11 pthread Xrandr Xi dl GLEW openal)
