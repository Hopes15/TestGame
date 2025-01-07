SamplerState smp : register(s0);

struct Output
{
    float4 svPos : SV_POSITION;
    float4 color : COLOR;
};

float4 main(Output output) : SV_TARGET
{
    return output.color;
}