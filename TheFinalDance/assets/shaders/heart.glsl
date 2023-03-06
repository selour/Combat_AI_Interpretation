#type vertex
#version 330 core
layout (location = 0) in vec2 a_Pos;
layout (location = 1) in vec2 a_TexCoords;

out vec2 v_TexCoords;

void main()
{
    gl_Position = vec4(a_Pos.x, a_Pos.y, 0.0, 1.0); 
    v_TexCoords = a_TexCoords;
}


#type fragment
#version 330 core
out vec4 FragColor;

in vec2 v_TexCoords;
uniform float v_Color;
uniform float v_Shadow;
uniform sampler2D u_Texture0;

void main()
{ 
    vec4 heart = texture(u_Texture0, v_TexCoords);
    vec4 shadow = texture(u_Texture0, ((v_TexCoords - 0.5) * (1. - 0.5 * v_Shadow)) + 0.5);
    shadow.a *= 0.8 * (1. - v_Shadow);
    float coord = max(heart.a,shadow.a);
    FragColor = vec4(v_Color, v_Color, v_Color, coord);
}