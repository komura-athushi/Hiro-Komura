sampler Sampler : register(s0);
sampler NoFillteringSampler : register(s2);

//���C�g
cbuffer lightCb : register(b2)
{
	float3 eyePos; 	//		: packoffset(c0);		//�J�����̈ʒu�B
	int numDirectionLight;//	: packoffset(c0.w);		//�f�B���N�V�������C�g�̐��B
	int numPointLight;	//	: packoffset(c0.x);		//�|�C���g���C�g�̐��B
	float3 ambientLight;//		: packoffset(c1.yzw);	//�A���r�G���g���C�g�B
};
struct SDirectionLight {
	float3 color;
	float3 direction;
};
struct SPointLight {
	float3	position;	
	float3	color;	
	float range;
	float attenuation;
};
StructuredBuffer<SDirectionLight> directionLight : register(t100);
StructuredBuffer<SPointLight> pointLightList : register(t101);

//�V���h�E�}�b�v�n
#define NUM_SHADOW_MAP 1
#define SHADOWMAP_ARRAY(a) shadowMap##a
cbuffer ShadowCb : register(b1) {
	float4x4 ViewProjInv;
	float4x4 mLVP[NUM_SHADOW_MAP];
	float3 shadowDir[NUM_SHADOW_MAP];
	int boolAO;
};
Texture2D<float> shadowMap0 : register(t60);
SamplerComparisonState	shadowSamplerComparisonState	: register(s1);

//�V���h�E�}�b�v�̔���
inline bool ShadowMapFunc(uint usemapnum, float4 worldpos) {

	//Z���烏�[���h���W���o��
	//float4 worldpos = float4(CalcWorldPosFromUVZ(In.uv, viewpos.w, ViewProjInv), 1.0f);

	//���W�Z�o
	float4 lLViewPosition = mul(mLVP[usemapnum], worldpos);
	lLViewPosition.xyz /= lLViewPosition.w;

	// -1.0f �` 1.0f �̒l�Ȃ̂ŁA����� 0.0f �` 1.0f �̒l�ɂ���
	lLViewPosition.x = lLViewPosition.x *0.5f + 0.5f;
	// y�͍X�ɏ㉺���]
	lLViewPosition.y = -lLViewPosition.y *0.5f + 0.5f;

	//�I�t�Z�b�g
	lLViewPosition.z -= 0.00025f*4.0f;// +0.00025f*(1.0f - lLViewPosition.z);//Z�l�ɉ������o�C�A�X�l

	int kekka = 1;
	switch (usemapnum) {
	case 0:
		kekka = SHADOWMAP_ARRAY(0).SampleCmpLevelZero(shadowSamplerComparisonState, lLViewPosition.xy, lLViewPosition.z);
		break;
	default:
		break;
	}

	if (kekka == 0)
	{
		return true;
	}

	/*float shadow_z = shadowMap0.Sample(NoFillteringSampler, lLViewPosition.xy);
	if (shadow_z < lLViewPosition.z) {
		Out.rgb *= min(1.0f, (lLViewPosition.z - shadow_z)*10.0f);
	}*/

	return false;
}

//G-Buffer
Texture2D<float4> albedoTexture : register(t0);
Texture2D<float4> normalMap		: register(t1);
Texture2D<float > depthMap		: register(t2);
Texture2D<float4> PosMap		: register(t3);
Texture2D<float > AoMap			: register(t4);
Texture2D<float4> lightParamTex	: register(t5);

struct VSDefferdInput {
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};
struct PSDefferdInput {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

PSDefferdInput VSMain(VSDefferdInput In)
{
	PSDefferdInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}

//Z�l���烏�[���h���W�𕜌�
float3 CalcWorldPosFromUVZ(float2 uv, float zInScreen, float4x4 mViewProjInv)
{
	float3 screenPos;
	screenPos.xy = (uv * float2(2.0f, -2.0f)) + float2(-1.0f, 1.0f);
	screenPos.z = zInScreen;

	float4 worldPos = mul(mViewProjInv, float4(screenPos, 1.0f));
	worldPos.xyz /= worldPos.w;
	return worldPos.xyz;
}

//�X�y�L����
float3 NormalizedPhong(float3 specular, float power, float3 viewDir, float3 normal, float3 lightDir)
{
	float3 R = -viewDir + (2.0f * dot(normal, viewDir) * normal);
	return specular * pow(max(dot(lightDir, R), 0.0f), power) * ((power + 1.0f) / (2.0 * 3.14));
}
//�f�B�t���[�Y
float3 Lambert(float3 diffuse, float3 lightDir, float3 normal)
{
	return max(diffuse * dot(normal, lightDir), 0.0f);
}

float4 PSMain(PSDefferdInput In) : SV_Target0
{
	//float a = SHADOWMAP_ARRAY(0).Sample(Sampler, In.uv);
	//return float4(a,a,a,1.0f);

	float4 albedo = albedoTexture.Sample(Sampler, In.uv);
	float3 normal = normalMap.Sample(Sampler, In.uv).xyz;
	float4 viewpos = PosMap.Sample(Sampler, In.uv);
	float3 worldpos = CalcWorldPosFromUVZ(In.uv, viewpos.w, ViewProjInv);
	float4 lightParam = lightParamTex.Sample(Sampler, In.uv);

	//���C�e�B���O����
	if (lightParam.a < 0.5f) {
		return float4(saturate(albedo.rgb + lightParam.rgb), albedo.w);//�G�~�b�V�u���Z
	}

	//�V���h�E�}�b�v
	bool hideInShadow[NUM_SHADOW_MAP] = { 0 };
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		if (ShadowMapFunc(i, float4(worldpos, 1.0f)) == true) {			
			hideInShadow[i] = true;
			break;
		}
	}

	//���C�e�B���O
	float3 Out = 0; 
	//�G�~�b�V�u
	//�f�B���N�V�������C�g
	for (int i = 0; i < numDirectionLight; i++) {

		//�V���h�E�}�b�v�̎Օ�
		float nothide = 1.0f;
		for (int swi = 0; swi < NUM_SHADOW_MAP; swi++) {
			if (hideInShadow[swi]) {
				nothide = saturate(1.0f - dot(shadowDir[swi], directionLight[i].direction)*-1.0f);
			}
		}

		Out += Lambert(albedo.xyz, directionLight[i].direction, normal) * directionLight[i].color * nothide;
	}
	//�|�C���g���C�g
	for (int i = 0; i < numPointLight; i++) {
		float3 dir = pointLightList[i].position - worldpos;
		float len = length(dir);
		if (len > 0.0f && len < pointLightList[i].range) {
			
			dir = normalize(dir);

			//�������v�Z����B
			float	litRate = len / pointLightList[i].range;
			float	attn = max(1.0 - litRate * litRate, 0.0);

			Out += Lambert(albedo.xyz, dir, normal) * pointLightList[i].color * pow(attn, pointLightList[i].attenuation);
		}
	}	

	//AO
	float ambientOcclusion = 1.0f;
	if (boolAO) {
		ambientOcclusion = AoMap.Sample(Sampler, In.uv);
	}

	//�A���r�G���g
	Out += albedo.xyz * ambientLight * ambientOcclusion;

	//�G�~�b�V�u�����Z
	Out += lightParam.rgb;

	//0.0~1.0�ŏo��
	Out = saturate(Out);
	return float4(Out, albedo.w);
	
}