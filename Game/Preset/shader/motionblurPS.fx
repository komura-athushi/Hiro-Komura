struct VSInput {
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> sceneTexture : register(t0);	//�V�[���e�N�X�`��
Texture2D<float4> VelocityMap : register(t1);	//�x���V�e�B�}�b�v
sampler Sampler : register(s0);

cbuffer PSCb : register(b0) {
	float DistantThreshold;
	float distanceScale;
};

PSInput VSMain(VSInput In)
{
	PSInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}

#include"MotionBlurHeader.h"

//static const float DistantThreshold = 500.0f;

float4 PSMain(PSInput In) : SV_Target0
{	
	//�x���V�e�B�}�b�v�擾
	float3 velocity = VelocityMap.Sample(Sampler, In.uv);
	velocity.xy *= blurscale;

	//���x�Ⴂ�Əo��
	if (abs(velocity.x) < BUNBO*0.5f && abs(velocity.y) < BUNBO*0.5f) {//0.001f
		discard;
	}

	float4 Out = sceneTexture.Sample(Sampler, In.uv);

	float loopmax = min(samples, max(abs(velocity.x), abs(velocity.y)) / BUNBO);

	//�@�T���v�����O
	float samplecnt = 0.0f;
	[unroll]
	for (float i = 0; i < loopmax; i++)
	{
		float t = (i + 1) / loopmax;
		float4 sampz = VelocityMap.Sample(Sampler, In.uv + t * velocity.xy);

		if (sampz.w > 0.0f || sampz.z > DistantThreshold){// && sampz.z  > DistantThreshold || velocity.z < sampz.z + Z_OFFSET * distanceScale) {//��O�̃s�N�Z������̓T���v�����Ȃ�
			Out += sceneTexture.Sample(Sampler, In.uv + t * velocity.xy);
			samplecnt += 1.0f;
		}
	}

	//�@���ς����߂�
	Out /= samplecnt + 1;

	return Out;
}