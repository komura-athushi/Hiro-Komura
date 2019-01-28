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
#define SHADOWMAP_NUM 8
static const uint SHADOW_MAX_WIDTH = 4096 / 2;
static const uint SHADOW_MAX_HEIGHT = 4096 / 2;

cbuffer ShadowCb : register(b1) {
	float4x4 ViewProjInv;
	float4x4 mLVP[SHADOWMAP_NUM];
	float4 shadowDir[SHADOWMAP_NUM];//w�̓o�C�A�X
	float4 enableShadowMap[SHADOWMAP_NUM];//x:�V���h�E�}�b�v�L�����H y:PCSS�L�� z:width�T�C�Y w:height�T�C�Y

	int boolAO;//AO��L���ɂ��邩
};
struct HideInShadow {
	float flag[SHADOWMAP_NUM];
};
Texture2DArray<float> shadowMaps  : register(t60);
SamplerComparisonState	shadowSamplerComparisonState	: register(s1);

static const float2 blockerSampleMap[] = {
	float2(-0.00276f,-0.00276f),
	float2(-0.00276f,-0.00138f),
	float2(-0.00276f, 0.0f),
	float2(-0.00276f, 0.00138f),
	float2(-0.00276f, 0.00276f),

	float2(-0.00138f,-0.00276f),
	float2(-0.00138f,-0.00138f),
	float2(-0.00138f, 0.0f),
	float2(-0.00138f, 0.00138f),
	float2(-0.00138f, 0.00276f),

	float2(0.0f,-0.00276f),
	float2(0.0f,-0.00138f),
	float2(0.0f, 0.0f),
	float2(0.0f, 0.00138f),
	float2(0.0f, 0.00276f),

	float2(0.00138f,-0.00276f),
	float2(0.00138f,-0.00138f),
	float2(0.00138f, 0.0f),
	float2(0.00138f, 0.00138f),
	float2(0.00138f, 0.00276f),

	float2(0.00276f,-0.00276f),
	float2(0.00276f,-0.00138f),
	float2(0.00276f, 0.0f),
	float2(0.00276f, 0.00138f),
	float2(0.00276f, 0.00276f),
};
static const float2 PCSSSampleMap[] = {
	float2(-0.00138f,-0.00138f),
	float2(-0.00138f,-0.00092f),
	float2(-0.00138f,-0.00046f),
	float2(-0.00138f, 0.0f),
	float2(-0.00138f, 0.00046f),
	float2(-0.00138f, 0.00092f),
	float2(-0.00138f, 0.00138f),

	float2(-0.00092f,-0.00138f),
	float2(-0.00092f,-0.00092f),
	float2(-0.00092f,-0.00046f),
	float2(-0.00092f, 0.0f),
	float2(-0.00092f, 0.00046f),
	float2(-0.00092f, 0.00092f),
	float2(-0.00092f, 0.00138f),

	float2(-0.00046f,-0.00138f),
	float2(-0.00046f,-0.00092f),
	float2(-0.00046f,-0.00046f),
	float2(-0.00046f, 0.0f),
	float2(-0.00046f, 0.00046f),
	float2(-0.00046f, 0.00092f),
	float2(-0.00046f, 0.00138f),

	float2(0.0f,-0.00138f),
	float2(0.0f,-0.00092f),
	float2(0.0f,-0.00046f),
	float2(0.0f, 0.0f),
	float2(0.0f, 0.00046f),
	float2(0.0f, 0.00092f),
	float2(0.0f, 0.00138f),

	float2(0.00046f,-0.00138f),
	float2(0.00046f,-0.00092f),
	float2(0.00046f,-0.00046f),
	float2(0.00046f, 0.0f),
	float2(0.00046f, 0.00046f),
	float2(0.00046f, 0.00092f),
	float2(0.00046f, 0.00138f),

	float2(0.00092f,-0.00138f),
	float2(0.00092f,-0.00092f),
	float2(0.00092f,-0.00046f),
	float2(0.00092f, 0.0f),
	float2(0.00092f, 0.00046f),
	float2(0.00092f, 0.00092f),
	float2(0.00092f, 0.00138f),

	float2(0.00138f,-0.00138f),
	float2(0.00138f,-0.00092f),
	float2(0.00138f,-0.00046f),
	float2(0.00138f, 0.0f),
	float2(0.00138f, 0.00046f),
	float2(0.00138f, 0.00092f),
	float2(0.00138f, 0.00138f),
};

//�V���h�E�}�b�v�̔���
inline float ShadowMapFunc(uint usemapnum, float4 worldpos) {

	//Z���烏�[���h���W���o��
	//float4 worldpos = float4(CalcWorldPosFromUVZ(In.uv, viewpos.w, ViewProjInv), 1.0f);

	//���W�Z�o
	float4 lLViewPosition = mul(mLVP[usemapnum], worldpos);
	lLViewPosition.xyz /= lLViewPosition.w;

	// -1.0f �` 1.0f �̒l�Ȃ̂ŁA����� 0.0f �` 1.0f �̒l�ɂ���
	lLViewPosition.x = lLViewPosition.x *0.5f + 0.5f;
	// y�͍X�ɏ㉺���]
	lLViewPosition.y = -lLViewPosition.y *0.5f + 0.5f;

	//���炵
	float2 scale = float2( enableShadowMap[usemapnum].z / SHADOW_MAX_WIDTH, enableShadowMap[usemapnum].w / SHADOW_MAX_HEIGHT);
	lLViewPosition.xy *= scale;
	
	// �ő�[�x�X�΂����߂�.
	//float  maxDepthSlope = max(abs(ddx(lLViewPosition.z)), abs(ddy(lLViewPosition.z)));
	
	//float  shadowBias = shadowDir[usemapnum].w*0.1f + shadowDir[usemapnum].w*4.0f * maxDepthSlope;
	//shadowBias = min(shadowBias, shadowDir[usemapnum].w*4.0f);
	
	//�o�C�A�X
	lLViewPosition.z -= shadowDir[usemapnum].w;// shadowBias;

	//PCSS����
	if (!enableShadowMap[usemapnum].y) {
		return 1.0f - shadowMaps.SampleCmpLevelZero(shadowSamplerComparisonState, float3(lLViewPosition.xy, usemapnum), lLViewPosition.z);
	}

	float kekka = 0.0f;
	uint cnt = 0;
	
	//�u���b�J�[�̐[�x�l�擾(����)
	float blocker_z = 0.0f;
	float avg_blocker_z = 0.0f;
	[unroll]
	for (uint i = 0; i < 25; i++) {
	//for (float y = -0.00276f; y <= 0.00276f; y += 0.00138f) {
	//[unroll]
	//for (float x = -0.00276f; x <= 0.00276f; x += 0.00138f) {

		blocker_z = shadowMaps.Sample(NoFillteringSampler, float3(lLViewPosition.xy + blockerSampleMap[i] * scale, usemapnum));

		if (blocker_z < lLViewPosition.z) {
			avg_blocker_z += blocker_z;
			cnt++;
		}
	//}
	}
	if (cnt == 0) {
		return 0.0f;
	}
	else {
		avg_blocker_z /= cnt;
	}

	//���e�̃T�C�Y�v�Z
	float maxCnt = 9.0f*(lLViewPosition.z - avg_blocker_z) / avg_blocker_z;// saturate();
	if (maxCnt <= 0.0f) {
		return 0.0f;
	}

	//�e�ɓ����Ă邩����(PCF)
	cnt = 0;
	[unroll]
	for (uint i = 0; i < 49; i++) {
	//for (float y = -0.00138f; y <= 0.00138f; y += 0.00046f){//1.0/720.0
	//[unroll]
	//for (float x = -0.00138f; x <= 0.00138f; x += 0.00046f){

		kekka += 1.0f - shadowMaps.SampleCmpLevelZero(shadowSamplerComparisonState, float3(PCSSSampleMap[i] * maxCnt * scale + lLViewPosition.xy, usemapnum), lLViewPosition.z);

		cnt++;
	//}
	}

	kekka /= cnt;
	return kekka;
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
	float4 albedo = albedoTexture.Sample(Sampler, In.uv);

	//���e�X�g
	if (albedo.w == 0.0f) {
		discard;
	}

	float3 normal = normalMap.Sample(Sampler, In.uv).xyz;
	float4 viewpos = PosMap.Sample(Sampler, In.uv);
	float3 worldpos = CalcWorldPosFromUVZ(In.uv, viewpos.w, ViewProjInv);
	float4 lightParam = lightParamTex.Sample(Sampler, In.uv);

	//���C�e�B���O����
	if (!lightParam.a) {
		return float4(saturate(albedo.rgb + lightParam.rgb), albedo.w);//�G�~�b�V�u���Z
	}

	//�V���h�E�}�b�v�͈̔͂ɓ����Ă��邩����
	HideInShadow hideInShadow = (HideInShadow)0;
	[unroll]
	for (int i = 0; i < SHADOWMAP_NUM; i++) {
		if (enableShadowMap[i].x){
			hideInShadow.flag[i] = ShadowMapFunc(i, float4(worldpos, 1.0f));
		}
	}

	//���C�e�B���O
	float3 Out = 0; 
	
	//�f�B���N�V�������C�g
	[unroll]
	for (int i = 0; i < 4; i++) {

		if (numDirectionLight == i) { break; }

		//�V���h�E�}�b�v�̎Օ��K��
		float nothide = 1.0f;
		[unroll]
		for (int swi = 0; swi < SHADOWMAP_NUM; swi++) {
			nothide = min(nothide, saturate(1.0f - dot(shadowDir[swi].xyz, directionLight[i].direction)*-hideInShadow.flag[swi]));
		}

		Out += Lambert(albedo.xyz, directionLight[i].direction, normal) * directionLight[i].color * nothide;
	}
	//�|�C���g���C�g
	[unroll]
	for (int i = 0; i < 12; i++) {

		if (numPointLight == i) { break; }

		float3 dir = pointLightList[i].position - worldpos;
		float len = length(dir);
		//if (len < pointLightList[i].range) {
			
			dir = normalize(dir);

			//�������v�Z����B
			float	litRate = len / pointLightList[i].range;
			float	attn = max(1.0 - litRate * litRate, 0.0);

			Out += Lambert(albedo.xyz, dir, normal) * pointLightList[i].color * pow(attn, pointLightList[i].attenuation);
		//}
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