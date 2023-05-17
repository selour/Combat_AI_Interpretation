#type vertex
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in mat4 a_Tranform;
layout (location = 6) in vec3 a_Color;
layout (location = 7) in float a_Alpha;
layout (location = 8) in float a_TexCoordZ;

uniform mat4 u_ViewProjection;


out vec3 v_TexCoord;
out vec3 v_Color;
out float v_Alpha;
void main()
{
	v_TexCoord = vec3(a_TexCoord.xy,a_TexCoordZ);
	v_Color = a_Color;
	v_Alpha = a_Alpha;
    gl_Position = u_ViewProjection * a_Tranform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core
layout (location = 0) out vec4 outColor;


in vec3 v_TexCoord;
in vec3 v_Color;
in float v_Alpha;

uniform sampler2DArray u_Texture0;
uniform float u_Hit;

float noise1d(float v){
    return cos(v + cos(v * 90.1415) * 100.1415) * 0.5 + 0.5;
}

void main()
{
		float alpha = texture(u_Texture0, v_TexCoord).a *v_Alpha;
		if( alpha < 0.1)
			discard;
		if(u_Hit == -1.0)
			outColor = texture(u_Texture0, v_TexCoord) * vec4(v_Color.rgb, v_Alpha);
		else
		{
			if(noise1d(u_Hit)>0.5)
			{
				outColor = vec4(vec3(v_Color.rgb),alpha);
			}
			else
			{
				outColor = texture(u_Texture0, v_TexCoord) * vec4(v_Color.rgb, v_Alpha);
			}
		}
		//outColor = vec4(v_Color.rgb, v_Alpha);

}

