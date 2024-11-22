#version 330 core
layout(location = 0) in vec3 position;
layout(location = 2) in vec3 color;

uniform mat4 modelView;
uniform mat4 projection;

out vec3 fragPosition;
out vec4 fragColor;

void main() {
    fragPosition = vec3(modelView * vec4(position, 1.0));
    gl_Position = projection * vec4(fragPosition, 1.0);
    fragColor = vec4(color,1.0);
}