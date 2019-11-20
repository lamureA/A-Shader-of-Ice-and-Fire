#version 450

#define ID gl_InvocationID

layout (vertices = 3) out;

in VS_OUT
{
    vec4 pos;
    vec3 normal;
    vec2 tex_coords;
    vec3 tangent;
    vec3 bitangent;
} tcs_in[];

out TCS_OUT
{
    vec4 pos;
    vec3 normal;
    vec2 tex_coords;
    vec3 tangent;
    vec3 bitangent;
} tcs_out[];


void main(void)
{
    if (ID == 0)
    {
        gl_TessLevelInner[0] = 32;// horizontal

        gl_TessLevelOuter[0] = 32;// edge 0-3
        gl_TessLevelOuter[1] = 32;// edge 2-3
        gl_TessLevelOuter[2] = 32;// edge 1-2
    }

    gl_out[ID].gl_Position = gl_in[ID].gl_Position;

    tcs_out[ID].pos = tcs_in[ID].pos;
    tcs_out[ID].normal = tcs_in[ID].normal;
    tcs_out[ID].tex_coords = tcs_in[ID].tex_coords;
    tcs_out[ID].tangent = tcs_in[ID].tangent;
    tcs_out[ID].bitangent = tcs_in[ID].bitangent;
}