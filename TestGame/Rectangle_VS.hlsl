struct Input
{
    float4 pos : POSITION;
    float4 color : COLOR;
};

struct Output
{
    float4 svPos : SV_POSITION;
    float4 color : COLOR;
};

cbuffer WorldMat : register(b0)
{
    matrix world;
}

cbuffer ViewProjectionMat : register(b1)
{
    matrix viewProjection;
}

Output main(Input input)
{
    Output output;
    output.svPos = mul(mul(viewProjection, world), input.pos);
    output.color = input.color;
    
    return output;
}