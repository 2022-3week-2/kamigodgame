cbuffer cbuff0 : register(b0)
{
	float4 color;
}

cbuffer cbuff1 : register(b1)
{
	matrix mat;
}

struct VSOutput
{
	float4 svpos : SV_POSITION;
	float2 uv :TEXCOORD;
};