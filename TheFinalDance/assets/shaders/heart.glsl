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
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec2 v_TexCoords;
uniform float v_Color;
uniform float v_Shadow;
uniform sampler2D u_Texture0;

void main()
{ 
    float heart = texture(u_Texture0, v_TexCoords).a;
    float shadow = texture(u_Texture0, ((v_TexCoords - 0.5) * (1. - 0.5 * v_Shadow)) + 0.5).a;
	
	shadow *= 0.8 * (1. - v_Shadow);
	float outAlpha = max(heart,shadow);
    vec4 outColor = vec4(vec3(v_Color * outAlpha),1.0);
	FragColor = outColor;

	vec3 vector1 = vec3(outColor);
	vec3 vector2 = vec3(0.2126, 0.7152, 0.0722);
		
	float brightness = dot(vector1, vector2);
		
	if(brightness > 1.0) 
	{
		BrightColor = FragColor;
	}
	else
	{
		BrightColor = vec4(0.0);
	}
}