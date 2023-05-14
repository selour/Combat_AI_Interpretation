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
uniform float u_Proportion;

float RoundRectEdge(vec2 position, vec2 size, float radius)
{
    float d = length(max(abs(position) - size + radius, 0.0)) - radius;
    float col = (1.-smoothstep(-.01, 0., d))*smoothstep(-.02, -0.01, d);
    return col;
}
float RoundRectTile(vec2 position, vec2 size, float radius)
{
    float d = length(max(abs(position) - size + radius, 0.0)) - radius;
    float col = (1.-smoothstep(-.05, 0., d))*0.5;
    return col;
}
void main()
{
	vec2 uv = v_TexCoord.xy;
	uv -= 0.5;
    //outColor = vec4(v_TexCoord.xy, 0.0, v_Alpha);
    float outAlpha = 0.0;
    switch (int (v_TexCoord.z))
    {
    case -2: 
        outAlpha = RoundRectEdge(uv,vec2(0.5),0.05); 
        outColor = vec4(v_Color,outAlpha * v_Alpha);
        break;
    case -1:
        outAlpha= max(RoundRectTile(uv,vec2(0.5),0.05),RoundRectEdge(uv,vec2(0.5),0.05)); 
        outColor = vec4(v_Color,outAlpha * v_Alpha);
        break;
    default:
        outColor = texture(u_Texture0, v_TexCoord)* vec4(v_Color.rgb,v_Alpha);
        break;
    }
   
	

}
