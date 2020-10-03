#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec4 Color;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * model * vec4(aPos.x, aPos.y, 0.f, 1.f);
    Color = vec4(1, 1, 1, 1);
    TexCoord = aTexCoord;
}