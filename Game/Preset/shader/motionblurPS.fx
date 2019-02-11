struct VSInput {
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> sceneTexture : register(t0);	//シーンテクスチャ
Texture2D<float4> VelocityMap : register(t1);	//ベロシティマップ
sampler Sampler : register(s0);

PSInput VSMain(VSInput In)
{
	PSInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}

static const float samples = 8;
static const float blurscale = -1.0f;// -0.15f;// 0.4f;
static const float BUNBO = 0.002f*(8.0f / samples);//0.001953125f

#include"MotionBlurHeader.h"

float4 PSMain(PSInput In) : SV_Target0
{	
	//ベロシティマップ取得
	float2 velocity = VelocityMap.Sample(Sampler, In.uv);
	velocity.xy *= blurscale;

	//速度低いと出る
	if (abs(velocity.x) < BUNBO*0.5f && abs(velocity.y) < BUNBO*0.5f) {//0.001f
		discard;
	}

	float4 Out = sceneTexture.Sample(Sampler, In.uv);

	float loopmax = min(samples, max(abs(velocity.x), abs(velocity.y)) / BUNBO);

	//　サンプリング
	float samplecnt = 0.0f;
	[unroll]
	for (float i = 0; i < loopmax; i++)
	{
		float t = (i + 1) / loopmax;
		float sampz = VelocityMap.Sample(Sampler, In.uv + t * velocity.xy).w;
		if (sampz > 0.0f) {// && velocity.z < sampz + Z_OFFSET) {//手前のピクセルからはサンプルしない
			Out += sceneTexture.Sample(Sampler, In.uv + t * velocity.xy);
			samplecnt += 1.0f;
		}
	}

	//　平均を求める
	Out /= samplecnt + 1;

	return Out;
}