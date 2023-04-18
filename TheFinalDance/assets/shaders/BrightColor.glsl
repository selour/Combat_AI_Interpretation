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
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;


in vec3 v_TexCoord;
in vec3 v_Color;
in float v_Alpha;

uniform sampler2DArray u_Texture0;

void main()
{
		float alpha = texture(u_Texture0, v_TexCoord).a *v_Alpha;
		if( alpha < 0.01)
			discard;
		vec3 outColor = vec3(0.0);
		outColor += texture(u_Texture0, v_TexCoord).rgb * v_Color.rgb;
		FragColor = vec4(outColor, alpha);



		vec3 vector1 = outColor;
		vec3 vector2 = vec3(0.2126, 0.7152, 0.0722);
		
		float brightness = dot(vector1, vector2);
		//brightness = max(brightness, 5.0);
		
		// so this should never execute since dot is 1.0
		if(brightness > 1.0) 
		{
		   BrightColor = vec4(outColor, alpha);
		}
		else
		{
			BrightColor = vec4(0.0);
			
		}
		
		
		

}
