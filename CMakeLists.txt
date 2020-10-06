cmake_minimum_required(VERSION 3.13) # Minimum CMake version
project(CubeWorld)                   # Create project 'CubeWorld'
set(CMAKE_CXX_STANDARD 20)           # Set the C++ standard version

set(CMAKE_CXX_FLAGS "-O3")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin) # Set the binary output directory

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

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
src/2D/Sprite.cpp
src/render/SpriteRenderer.cpp
src/render/TextRenderer.cpp
src/render/ChunkRenderer.cpp
src/2D/text/Glyph.cpp
src/2D/text/Font.cpp
src/2D/text/Text.cpp
src/state/InGameState.cpp
src/render/MasterRenderer.cpp

src/util/math/Ray.cpp

src/world/block/Block.cpp

src/resource/ResourceManager.cpp
)

# Set the include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# FreeType
include_directories(${CMAKE_SOURCE_DIR}/include/freetype2)

# Build the executable
add_executable(CubeWorld ${SOURCES})

# Link the necessary libraries - should probably link statically
target_link_libraries(CubeWorld glfw3 
                                GL 
                                X11 
                                pthread 
                                Xrandr 
                                Xi 
                                dl 
                                GLEW 
                                openal 
                                freetype)
