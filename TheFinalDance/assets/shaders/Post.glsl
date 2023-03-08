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
uniform vec2 u_Resolution;
uniform float u_Time;
uniform sampler2D u_Texture0;
uniform int u_State;
float random (vec2 st, float seed)
{
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * (43758.5453123 * seed));
}
vec4 RGBAnoise(vec2 uv)
{
    float seed = fract(u_Time);
    return vec4(random(uv,seed + 0.1),random(uv,seed + 0.2),random(uv,seed + 0.3),random(uv,seed + 0.4));
}
vec4 MpegGlitch(vec2 uv)
{
	vec2 fragCoord = uv.xy * u_Resolution.xy;
	vec2 block = floor(fragCoord.xy / vec2(16.));
	vec2 uv_noise = block / vec2(64.);
	uv_noise += floor(vec2(fract(u_Time)*1.0) * vec2(1234.0, 3543.0)) / vec2(64.);
	
	float block_thresh = pow(fract(u_Time * 1236.0453), 2.0) * 0.005;
	float line_thresh = pow(fract(u_Time * 2236.0453), 3.0) * 0.005;
	
	vec2 uv_r = uv, uv_g = uv, uv_b = uv;

	// glitch some blocks and lines
	if (RGBAnoise(uv_noise).r < block_thresh || RGBAnoise(vec2(uv_noise.y, 0.0)).g < line_thresh) 
	{

		vec2 dist = (fract(uv_noise) - 0.5) * 0.3;
		uv_r += dist * 0.1;
		uv_g += dist * 0.2;
		uv_b += dist * 0.125;
	}
	vec4 fragColor = vec4(1.0);
	fragColor.r = texture(u_Texture0, uv_r).r;
	fragColor.g = texture(u_Texture0, uv_g).g;
	fragColor.b = texture(u_Texture0, uv_b).b;
	// loose luma for some blocks
	if (RGBAnoise(uv_noise).g < block_thresh)
		fragColor.rgb = fragColor.ggg;

	// discolor block lines
	if (RGBAnoise(vec2(uv_noise.y, 0.0)).b * 3.5 < line_thresh)
		fragColor.rgb = vec3(0.0, dot(fragColor.rgb, vec3(1.0)), 0.0);

	// interleave lines in some blocks
	if (RGBAnoise(uv_noise).g * 1.5 < block_thresh || RGBAnoise(vec2(uv_noise.y, 0.0)).g * 2.5 < line_thresh) 
	{
		float line = fract(fragCoord.y / 3.0);
		vec3 mask = vec3(3.0, 0.0, 0.0);
		if (line > 0.333)
			mask = vec3(0.0, 3.0, 0.0);
		if (line > 0.666)
			mask = vec3(0.0, 0.0, 3.0);
		
		fragColor.xyz *= mask;
	}
	return fragColor;
}
void main()
{ 
    switch(u_State)
    {
    case 0:FragColor = texture(u_Texture0,v_TexCoords);break;
    case 1:FragColor = RGBAnoise(v_TexCoords);break;
	case 2:FragColor = mix(MpegGlitch(v_TexCoords), RGBAnoise(v_TexCoords),0.2);break;
    }
    
}