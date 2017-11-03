#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 FragPos;

uniform mat4 model;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
     gl_Position = vec4(vec2(FragPos),0.0,1.0);
}