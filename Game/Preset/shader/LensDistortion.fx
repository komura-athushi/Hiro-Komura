Texture2D<float4> Texture : register(t0);

sampler Sampler : register(s0);

struct VSInput {
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};
struct PSInput {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

PSInput VSMain(VSInput In)
{
	PSInput Out;
	Out.pos = In.pos;
	Out.uv = In.uv;
	return Out;
}

cbuffer PSCb : register(b0) {
	float k4;
	float LENS_DISTORTION_UV_MAGNIFICATION;
	float ASPECT_RATIO;
	float INV_ASPECT_RATIO;
};

//�r�l�b�g(���ӌ���)���n�܂�ʒu
static const float VIGNETTE_POS_MIN = 0.01f;
static const float VIGNETTE_POS_MAX = 1.0f - VIGNETTE_POS_MIN;
//�I���ʒu
static const float VIGNETTE_END_MIN = -0.006f;

/// @brief �����Y�c�݂�K�p����UV���擾
float4 GetLensDistortion(float2 uv)
{
	// Aspect����l��������ԏ�ł�,�������S����̋����x�N�g��
	float2 rVec = (uv - float2(0.5f, 0.5f));
	rVec.x *= ASPECT_RATIO;
	const float r2 = dot(rVec, rVec);
	const float r4 = r2 * r2;
	const float k1 = 0.0f;
	const float k2 = 0.0f;
	const float k3 = 0.0f;

	// ���a�����c�݂��l�����������x�N�g��
	float2 distortionR = (1.0f + k1 * r2 + k2 * r4) / (1.0f + k3 * r2 + k4 * r4) * rVec;
	
	// �~�������c�ݗʂ̉��Z
	/*const float p1 = 0.0f;
	const float p2 = 0.0f;
	const float C = 2.0f * rVec.x * rVec.y;
	const float2 V = 2.0f * rVec * rVec;
	distortionR += float2(p1*C + p2 * (r2 + V.x), p2*C + p1 * (r2 + V.y));*/

	// �A�X�y�N�g��␳
	distortionR.x *= INV_ASPECT_RATIO;

	// ��ʒ��S��̊g��,UV���W�ւ̕ϊ�
	uv = (distortionR*LENS_DISTORTION_UV_MAGNIFICATION) + float2(0.5f, 0.5f);
	
	//���ӌ���
	float4 output = Texture.Sample(Sampler, uv);
	if (uv.x < VIGNETTE_POS_MIN || uv.y < VIGNETTE_POS_MIN || uv.x > VIGNETTE_POS_MAX || uv.y > VIGNETTE_POS_MAX) {
		float2 sub = uv; 
		if (uv.x < VIGNETTE_POS_MIN) { sub.x = VIGNETTE_POS_MIN; }else if (uv.x > VIGNETTE_POS_MAX) { sub.x = VIGNETTE_POS_MAX; }
		if (uv.y < VIGNETTE_POS_MIN) { sub.y = VIGNETTE_POS_MIN; }else if (uv.y > VIGNETTE_POS_MAX) { sub.y = VIGNETTE_POS_MAX; }

		uv  -= float2(0.5f, 0.5f); uv.x *= ASPECT_RATIO;
		sub -= float2(0.5f, 0.5f); sub.x *= ASPECT_RATIO;

		output = float4(lerp(output.xyz, float3(0.0f, 0.0f, 0.0f), distance(uv,sub) / distance(float2((VIGNETTE_END_MIN-0.5f)*ASPECT_RATIO, VIGNETTE_END_MIN-0.5f), float2((VIGNETTE_POS_MIN-0.5f)*ASPECT_RATIO, VIGNETTE_POS_MIN-0.5f))), output.w);
		//return float4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	//else {
		//uv -= float2(0.5f, 0.5f); uv.x *= ASPECT_RATIO;
		//output.xyz *= saturate(1.0f - pow(distance(float2(0.0f,0.0f), uv*0.85f),8.0f)*6.0f);
	//}
	return output;
}

float4 PSMain(PSInput In) : SV_Target0
{
	//����̃R�����g�O���Ɩʔ������ƂɂȂ�
	//In.uv = GetLensDistortion(In.uv);

	return GetLensDistortion(In.uv);
}