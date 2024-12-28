struct Input
{
    float4 pos : POSITION;
};

struct Output
{
    float4 svPos : SV_POSITION;
};

cbuffer WorldMat : register(b0)
{
    matrix world;
}

cbuffer ViewProjectionMat : register(b1)
{
    matrix viewProjection;
}

Output main(float4 pos : POSITION)
{
    Output output;
    output.svPos = mul(mul(viewProjection, world), pos);
    
    return output;
}