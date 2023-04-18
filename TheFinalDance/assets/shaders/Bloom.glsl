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

uniform sampler2D u_Scene;
uniform sampler2D u_BloomBlur0;
uniform sampler2D u_BloomBlur1;
uniform sampler2D u_BloomBlur2;

uniform float u_Exposure;

void main()
{             
    //const float gamma = 2.2;
    vec3 hdrColor = texture(u_Scene, v_TexCoords).rgb;      
    vec3 bloomColor = texture(u_BloomBlur0, v_TexCoords).rgb + texture(u_BloomBlur1, v_TexCoords).rgb + texture(u_BloomBlur2, v_TexCoords).rgb;
    //vec3 result = vec3(1.0) - exp(-bloomColor * u_Exposure);
    //hdrColor += result; // additive 
    //hdrColor += bloomColor; // additive blending
    // tone mapping
   // vec3 result = vec3(1.0) - exp(-hdrColor * u_Exposure
    vec3 result = hdrColor * u_Exposure + vec3(1.0) - exp(-bloomColor * u_Exposure);
    // also gamma correct while we're at it       
   //result = pow(result, vec3(1.0 / gamma));
   FragColor = vec4(result, 1.0f);
   //FragColor = vec4(hdrColor, 1.0f);
}