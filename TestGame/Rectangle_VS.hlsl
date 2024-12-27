struct Input
{
    float4 pos : POSITION;
};

struct Output
{
    float4 svPos : SV_POSITION;
};

cbuffer Transform : register(b0)
{
    matrix world;
}

Output main(float4 pos : POSITION)
{
    Output output;
    output.svPos = mul(world, pos);
    
    return output;
}