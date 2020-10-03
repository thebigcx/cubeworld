#version 460 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoord).r);
    FragColor = vec4(textColor, 1.0) * sampled;
}