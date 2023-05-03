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

uniform float v_Time;

void main()
{ 
    // Time varying pixel color
    vec3 col = 0.5 + 0.5*cos(v_Time + v_TexCoords.xyx + vec3(0,2,4));

    // Output to screen
    FragColor = vec4(col,1.0);
}