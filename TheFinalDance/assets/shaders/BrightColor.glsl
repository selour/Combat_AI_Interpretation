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

uniform sampler2D u_Texture0;


void main()
{
		
		FragColor = texture(u_Texture0,v_TexCoords);


		float R = FragColor.r;
		float G = FragColor.g;
		float B = FragColor.b;
		
		float brightness = sqrt(0.299 * R * R + 0.587 * G * G + 0.114 * B * B);
		//brightness = max(brightness, 5.0);
		
		// so this should never execute since dot is 1.0
		if(brightness > 1.0) 
		{
		   BrightColor = FragColor;
		}
		else
		{
			BrightColor = vec4(0.0);
		}


}
