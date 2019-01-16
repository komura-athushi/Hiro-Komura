sampler Sampler : register(s0);
sampler NoFillteringSampler : register(s2);

//ライト
cbuffer lightCb : register(b2)
{
	float3 eyePos; 	//		: packoffset(c0);		//カメラの位置。
	int numDirectionLight;//	: packoffset(c0.w);		//ディレクションライトの数。
	int numPointLight;	//	: packoffset(c0.x);		//ポイントライトの数。
	float3 ambientLight;//		: packoffset(c1.yzw);	//アンビエントライト。
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

//シャドウマップ系
#define SHADOWMAP_NUM 12
#define SHADOWMAP_ARRAY(a) shadowMap##a
cbuffer ShadowCb : register(b1) {
	float4x4 ViewProjInv;
	float4x4 mLVP[SHADOWMAP_NUM];
	float4 shadowDir[SHADOWMAP_NUM];//wはオフセット
	float4 enableShadowMap[SHADOWMAP_NUM];//シャドウマップ有効か？

	int boolAO;//AOを有効にするか
};
struct HideInShadow {
	bool flag[SHADOWMAP_NUM];
};
Texture2D<float> shadowMap0  : register(t60);
Texture2D<float> shadowMap1  : register(t61);
Texture2D<float> shadowMap2  : register(t62);
Texture2D<float> shadowMap3  : register(t63);
Texture2D<float> shadowMap4  : register(t64);
Texture2D<float> shadowMap5  : register(t65);
Texture2D<float> shadowMap6  : register(t66);
Texture2D<float> shadowMap7  : register(t67);
Texture2D<float> shadowMap8  : register(t68);
Texture2D<float> shadowMap9  : register(t69);
Texture2D<float> shadowMap10 : register(t70);
Texture2D<float> shadowMap11 : register(t71);
SamplerComparisonState	shadowSamplerComparisonState	: register(s1);

//シャドウマップの判定
inline bool ShadowMapFunc(uint usemapnum, float4 worldpos) {

	//Zからワールド座標を出す
	//float4 worldpos = float4(CalcWorldPosFromUVZ(In.uv, viewpos.w, ViewProjInv), 1.0f);

	//座標算出
	float4 lLViewPosition = mul(mLVP[usemapnum], worldpos);
	lLViewPosition.xyz /= lLViewPosition.w;

	// -1.0f 〜 1.0f の値なので、これを 0.0f 〜 1.0f の値にする
	lLViewPosition.x = lLViewPosition.x *0.5f + 0.5f;
	// yは更に上下反転
	lLViewPosition.y = -lLViewPosition.y *0.5f + 0.5f;

	//オフセット
	lLViewPosition.z -= shadowDir[usemapnum].w;//0.00025f*4.0f;// +0.00025f*(1.0f - lLViewPosition.z);//Z値に応じたバイアス値

	int kekka = 1;
	switch (usemapnum) {
	case 0:
		kekka = SHADOWMAP_ARRAY(0).SampleCmpLevelZero(shadowSamplerComparisonState, lLViewPosition.xy, lLViewPosition.z);
		break;
	case 1:
		kekka = SHADOWMAP_ARRAY(1).SampleCmpLevelZero(shadowSamplerComparisonState, lLViewPosition.xy, lLViewPosition.z);
		break;
	case 2:
		kekka = SHADOWMAP_ARRAY(2).SampleCmpLevelZero(shadowSamplerComparisonState, lLViewPosition.xy, lLViewPosition.z);
		break;
	case 3:
		kekka = SHADOWMAP_ARRAY(3).SampleCmpLevelZero(shadowSamplerComparisonState, lLViewPosition.xy, lLViewPosition.z);
		break;
	case 4:
		kekka = SHADOWMAP_ARRAY(4).SampleCmpLevelZero(shadowSamplerComparisonState, lLViewPosition.xy, lLViewPosition.z);
		break;
	case 5:
		kekka = SHADOWMAP_ARRAY(5).SampleCmpLevelZero(shadowSamplerComparisonState, lLViewPosition.xy, lLViewPosition.z);
		break;
	case 6:
		kekka = SHADOWMAP_ARRAY(6).SampleCmpLevelZero(shadowSamplerComparisonState, lLViewPosition.xy, lLViewPosition.z);
		break;
	case 7:
		kekka = SHADOWMAP_ARRAY(7).SampleCmpLevelZero(shadowSamplerComparisonState, lLViewPosition.xy, lLViewPosition.z);
		break;
	case 8:
		kekka = SHADOWMAP_ARRAY(8).SampleCmpLevelZero(shadowSamplerComparisonState, lLViewPosition.xy, lLViewPosition.z);
		break;
	case 9:
		kekka = SHADOWMAP_ARRAY(9).SampleCmpLevelZero(shadowSamplerComparisonState, lLViewPosition.xy, lLViewPosition.z);
		break;
	case 10:
		kekka = SHADOWMAP_ARRAY(10).SampleCmpLevelZero(shadowSamplerComparisonState, lLViewPosition.xy, lLViewPosition.z);
		break;
	case 11:
		kekka = SHADOWMAP_ARRAY(11).SampleCmpLevelZero(shadowSamplerComparisonState, lLViewPosition.xy, lLViewPosition.z);
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

//Z値からワールド座標を復元
float3 CalcWorldPosFromUVZ(float2 uv, float zInScreen, float4x4 mViewProjInv)
{
	float3 screenPos;
	screenPos.xy = (uv * float2(2.0f, -2.0f)) + float2(-1.0f, 1.0f);
	screenPos.z = zInScreen;

	float4 worldPos = mul(mViewProjInv, float4(screenPos, 1.0f));
	worldPos.xyz /= worldPos.w;
	return worldPos.xyz;
}

//スペキュラ
float3 NormalizedPhong(float3 specular, float power, float3 viewDir, float3 normal, float3 lightDir)
{
	float3 R = -viewDir + (2.0f * dot(normal, viewDir) * normal);
	return specular * pow(max(dot(lightDir, R), 0.0f), power) * ((power + 1.0f) / (2.0 * 3.14));
}
//ディフューズ
float3 Lambert(float3 diffuse, float3 lightDir, float3 normal)
{
	return max(diffuse * dot(normal, lightDir), 0.0f);
}

float4 PSMain(PSDefferdInput In) : SV_Target0
{
	//float a = SHADOWMAP_ARRAY(0).Sample(Sampler, In.uv);
	//return float4(a,a,a,1.0f);

	float4 albedo = albedoTexture.Sample(Sampler, In.uv);

	//αテスト
	if (albedo.w > 0.0f) {
	}else{
		discard;
	}

	float3 normal = normalMap.Sample(Sampler, In.uv).xyz;
	float4 viewpos = PosMap.Sample(Sampler, In.uv);
	float3 worldpos = CalcWorldPosFromUVZ(In.uv, viewpos.w, ViewProjInv);
	float4 lightParam = lightParamTex.Sample(Sampler, In.uv);

	//ライティング無効
	if (lightParam.a < 0.5f) {
		return float4(saturate(albedo.rgb + lightParam.rgb), albedo.w);//エミッシブ加算
	}

	//シャドウマップの範囲に入っているか判定
	HideInShadow hideInShadow = (HideInShadow)0;
	for (int i = 0; i < SHADOWMAP_NUM; i++) {
		if (enableShadowMap[i].x){
		if (ShadowMapFunc(i, float4(worldpos, 1.0f)) == true) {			
			hideInShadow.flag[i] = true;
			//break;
		}
		}
	}

	//ライティング
	float3 Out = 0; 
	//エミッシブ
	//ディレクションライト
	for (int i = 0; i < numDirectionLight; i++) {

		//シャドウマップの遮蔽適応
		float nothide = 1.0f;
		for (int swi = 0; swi < SHADOWMAP_NUM; swi++) {
			if (hideInShadow.flag[swi]) {
				nothide = min(nothide, saturate(1.0f - dot(shadowDir[swi].xyz, directionLight[i].direction)*-1.0f));
				if (nothide == 0.0f) { break; }
			}
		}

		if (nothide == 0.0f) { continue; }
		Out += Lambert(albedo.xyz, directionLight[i].direction, normal) * directionLight[i].color * nothide;
	}
	//ポイントライト
	for (int i = 0; i < numPointLight; i++) {
		float3 dir = pointLightList[i].position - worldpos;
		float len = length(dir);
		if (len > 0.0f && len < pointLightList[i].range) {
			
			dir = normalize(dir);

			//減衰を計算する。
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

	//アンビエント
	Out += albedo.xyz * ambientLight * ambientOcclusion;

	//エミッシブを加算
	Out += lightParam.rgb;

	//0.0~1.0で出力
	Out = saturate(Out);
	return float4(Out, albedo.w);
	
}