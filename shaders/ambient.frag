#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform vec3 ambient;
uniform sampler2D tex;

void main() {
    color = texture2D(tex, TexCoord.xy) * vec4(ambient, 1.0);
}