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

float beatCircle(vec2 uv, float radius)
{
    float d = length(uv);
    float R =.5 - (1. - radius) *(1./3.);
    return smoothstep(R , R - .04, d)*(1.-smoothstep(R - .04 , R - .05 , d)) * 0.4;
}
float determineCircle(vec2 uv)
{
    float col = 1.0;
    float d = length(uv);
    col = smoothstep(.5/3., .5/3. -.01, d) * smoothstep(.5/3. -.05, .5/3. -.01, d) * 0.4;
    return col;
}
float roundrectTile(vec2 position, vec2 size, float radius)
{
    float d = length(max(abs(position) - size + radius, 0.0)) - radius;
    float col = (1.-smoothstep(-.01, 0., d))*smoothstep(-.02, -0.01, d);
    return col;
}
void main()
{
	vec2 uv = v_TexCoord.xy;
	uv -= 0.5;
    //outColor = vec4(v_TexCoord.xy, 0.0, v_Alpha);
    float outAlpha = 0.0;
    switch(int(v_TexCoord.z))
    {
    case 0:outAlpha = max(determineCircle(uv)*(1. + u_Proportion) , beatCircle(uv, u_Proportion)+ beatCircle(uv, 1));break;
    case 1:outAlpha= roundrectTile(uv,vec2(0.5),0.05);break;
    }
    outColor = vec4(v_Color.rgb,outAlpha * v_Alpha);
	

}
