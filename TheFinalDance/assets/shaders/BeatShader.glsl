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
uniform float u_Beat;
uniform float u_Hit;

float noise1d(float v){
    return cos(v + cos(v * 90.1415) * 100.1415) * 0.5 + 0.5;
}
vec2 hash( vec2 x )
{
    const vec2 k = vec2( 0.3183099, 0.3678794 );
    x = x*k + k.yx;
    return -1.0 + 2.0*fract( 16.0 * k*fract( x.x*x.y*(x.x+x.y)) );
}

float noise( in vec2 p )
{
    vec2 i = floor( p );
    vec2 f = fract( p );
	
	vec2 u = f*f*(3.0-2.0*f);

    return mix( mix( dot( hash( i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ), 
                     dot( hash( i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),
                mix( dot( hash( i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ), 
                     dot( hash( i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y);
}

float FinalBeat(vec2 uv, float proportion)
{
    float noiseboi = 0.0;
	noiseboi = noise( 32.0 * uv );
    
    float r = proportion * 0.5;
    float dissolve = r;
    noiseboi *= dissolve;
    
    float ir = clamp(-1.* proportion * 0.5+0.55, 0.04, 1.0); 
    

    float c = 0.;
    float d = length(uv-vec2(0));
	c =  smoothstep(r, r - 0.04, d) - smoothstep(r, r - ir, d);
    noiseboi *= c; 
    c += noiseboi;
    return c;
}
float beatCircle(vec2 uv, float radius)
{
    float d = length(uv);
    float R =.5 - (1. - radius) *(1./3.);
    return smoothstep(R , R - .04, d)*(1.-smoothstep(R - .04 , R - .05 , d)) * 0.5;
}
float determineCircle(vec2 uv)
{
    float col = 1.0;
    float d = length(uv);
    col = smoothstep(.5/3., .5/3. -.01, d) * smoothstep(.5/3. -.05, .5/3. -.01, d) * 0.5;
    return col;
}

void main()
{
	vec2 uv = v_TexCoord.xy;
	uv -= 0.5;
    float outAlpha = 0.0;
    switch(int(v_TexCoord.z))
    {
    case 0:
        float alpha = texture(u_Texture0, v_TexCoord).a *v_Alpha;
		if( alpha < 0.1)
			discard;
        if(u_Hit == -1.0)
        {
            outColor = texture(u_Texture0, v_TexCoord) * vec4(v_Color.rgb, v_Alpha);
        }
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
        break;
    case 1:
        outColor = texture(u_Texture0, v_TexCoord) * vec4(v_Color, v_Alpha);
        break;
    case 2:
        outColor = vec4(texture(u_Texture0, v_TexCoord).rgb,texture(u_Texture0, v_TexCoord).a*0.8);
        break;
    case 3:
        outAlpha = max(determineCircle(uv)*(1. + u_Proportion) , beatCircle(uv, u_Proportion)+ beatCircle(uv, 1));
        outColor = vec4(v_Color.rgb,outAlpha * v_Alpha);
        break;
    case 4:
        outAlpha = FinalBeat(uv, u_Beat);
        outColor = vec4(v_Color.rgb,outAlpha * v_Alpha);
        break;
        
    }

	

}
