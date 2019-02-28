/*!
 * @brief	���f���V�F�[�_�[�B
 */

#include"MotionBlurHeader.h"

/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);	
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t1);
StructuredBuffer<float4x4> boneMatrixOld : register(t2);
//�C���X�^���V���O�p���[���h�s��
StructuredBuffer<float4x4> InstancingWorldMatrix : register(t3);
StructuredBuffer<float4x4> InstancingWorldMatrixOld : register(t4);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// �萔�o�b�t�@�B
/////////////////////////////////////////////////////////////
/*!
 * @brief	���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;

	//�O��̍s��
	float4x4 mWorld_old;
	float4x4 mView_old;
	float4x4 mProj_old;

	//�J�����̈ړ���
	float4 camMoveVec;//w:�������l�������X�P�[��

	float4 depthBias;//x:max=(1.0f) y:max=(far-near) z:�u���[�̋ߋ����������l
};

//�}�e���A���p�����[�^�[
cbuffer MaterialCb : register(b1) {
	float4 albedoScale;	//�A���x�h�ɂ�����X�P�[��
	float4 emissive;	//�G�~�b�V�u(���Ȕ���) w�����C�e�B���O���邩
}

/////////////////////////////////////////////////////////////
//�e��\����
/////////////////////////////////////////////////////////////
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float3 Tangent  : TANGENT;				//�ڃx�N�g���B
    float2 TexCoord : TEXCOORD0;			//UV���W�B
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float2 TexCoord	: TEXCOORD0;			//UV���W�B
    float3 Tangent	: TANGENT;				//�ڃx�N�g���B
    uint4  Indices  : BLENDINDICES0;		//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ��Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
    float4 Weights  : BLENDWEIGHT0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ւ̃X�L���E�F�C�g�Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 Viewpos		: TEXCOORD1;

	float4	curPos		: CUR_POSITION;//���ݍ��W
	float4	lastPos		: LAST_POSITION;//�ߋ����W
	bool isWorldMove	: IS_WORLD_BLUR;//���[���h��Ԃňړ����Ă��邩?
};

//Z�l�������݃s�N�Z���V�F�[�_�[�̓���
struct ZPSInput {
	float4 Position 	: SV_POSITION;
	float2 TexCoord 	: TEXCOORD0;
	float4 posInProj	: TEXCOORD1;
};


/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In
#if defined(INSTANCING)
	, uint instanceID : SV_InstanceID 
#endif 
){
	PSInput psInput = (PSInput)0;

#if defined(INSTANCING)
	float4 pos = mul(InstancingWorldMatrix[instanceID], In.Position);
#else
	float4 pos = mul(mWorld, In.Position);
#endif

	float3 posW = pos.xyz;
	pos = mul(mView, pos); psInput.Viewpos = pos.xyz;
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;

#if defined(INSTANCING)
	psInput.Normal = normalize(mul(InstancingWorldMatrix[instanceID], In.Normal));
	psInput.Tangent = normalize(mul(InstancingWorldMatrix[instanceID], In.Tangent));
#else
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
#endif

	psInput.curPos = pos;

	//�x���V�e�B�}�b�v�p���
#if !defined(NO_MOTIONBLUR)

#if defined(INSTANCING)
		float4 oldpos = mul(InstancingWorldMatrixOld[instanceID], In.Position);
#else
		float4 oldpos = mul(mWorld_old, In.Position);
#endif

		oldpos.xyz = lerp(posW, oldpos.xyz, MotionBlurScale);

#if defined(INSTANCING)
		float3 trans = float3(InstancingWorldMatrix[instanceID]._m03, InstancingWorldMatrix[instanceID]._m13, InstancingWorldMatrix[instanceID]._m23);
		float3 transOld = float3(InstancingWorldMatrixOld[instanceID]._m03, InstancingWorldMatrixOld[instanceID]._m13, InstancingWorldMatrixOld[instanceID]._m23);
#else
		float3 trans = float3(mWorld._m03, mWorld._m13, mWorld._m23);
		float3 transOld = float3(mWorld_old._m03, mWorld_old._m13, mWorld_old._m23);
#endif

		transOld = lerp(trans, transOld, MotionBlurScale);
		trans -= transOld;

		if (length(trans) > camMoveVec.w
			&& distance(camMoveVec.xyz, trans) > camMoveVec.w
#if defined(INSTANCING)
			|| distance(float3(InstancingWorldMatrix[instanceID]._m00, InstancingWorldMatrix[instanceID]._m10, InstancingWorldMatrix[instanceID]._m20), float3(InstancingWorldMatrixOld[instanceID]._m00, InstancingWorldMatrixOld[instanceID]._m10, InstancingWorldMatrixOld[instanceID]._m20)) > 0.0f
			|| distance(float3(InstancingWorldMatrix[instanceID]._m01, InstancingWorldMatrix[instanceID]._m11, InstancingWorldMatrix[instanceID]._m21), float3(InstancingWorldMatrixOld[instanceID]._m01, InstancingWorldMatrixOld[instanceID]._m11, InstancingWorldMatrixOld[instanceID]._m21)) > 0.0f
			|| distance(float3(InstancingWorldMatrix[instanceID]._m02, InstancingWorldMatrix[instanceID]._m12, InstancingWorldMatrix[instanceID]._m22), float3(InstancingWorldMatrixOld[instanceID]._m02, InstancingWorldMatrixOld[instanceID]._m12, InstancingWorldMatrixOld[instanceID]._m22)) > 0.0f
#else
			|| distance(float3(mWorld._m00, mWorld._m10, mWorld._m20), float3(mWorld_old._m00, mWorld_old._m10, mWorld_old._m20)) > 0.0f
			|| distance(float3(mWorld._m01, mWorld._m11, mWorld._m21), float3(mWorld_old._m01, mWorld_old._m11, mWorld_old._m21)) > 0.0f
			|| distance(float3(mWorld._m02, mWorld._m12, mWorld._m22), float3(mWorld_old._m02, mWorld_old._m12, mWorld_old._m22)) > 0.0f
#endif
		){
			psInput.isWorldMove = true;
		}

		float4 oldpos2 = mul(mView_old, oldpos);
		oldpos = mul(mView, oldpos);
		oldpos.xyz = lerp(oldpos.xyz, oldpos2.xyz, MotionBlurScale);

		oldpos = mul(mProj_old, oldpos);
		
		psInput.lastPos = oldpos;
#endif

	return psInput;
}
//Z�l�������ݗp
ZPSInput VSMain_RenderZ(VSInputNmTxVcTangent In
#if defined(INSTANCING)
	, uint instanceID : SV_InstanceID
#endif 
){
	ZPSInput psInput = (ZPSInput)0;

#if defined(INSTANCING)
	float4 pos = mul(InstancingWorldMatrix[instanceID], In.Position);
#else
	float4 pos = mul(mWorld, In.Position);
#endif

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.posInProj = pos;
	psInput.TexCoord = In.TexCoord;

	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
 * �S�Ă̒��_�ɑ΂��Ă��̃V�F�[�_�[���Ă΂��B
 * In��1�̒��_�f�[�^�BVSInputNmTxWeights�����Ă݂悤�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In
#if defined(INSTANCING)
	, uint instanceID : SV_InstanceID
#endif 
){
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{	
		float w = 0.0f;
		[unroll]
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //�Ō�̃{�[�����v�Z����B
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);	  	
	}
#if defined(INSTANCING)
	//�C���X�^���V���O
	skinning = mul(InstancingWorldMatrix[instanceID], skinning);
#endif
	
	//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
	//mul�͏�Z���߁B
	pos = mul(skinning, In.Position);
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );

	float3 posW = pos.xyz;	

	pos = mul(mView, pos);  psInput.Viewpos = pos.xyz;
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;

	psInput.curPos = pos;

	//�x���V�e�B�}�b�v�p���
#if !defined(NO_MOTIONBLUR)
		float4x4 oldskinning = 0;
		float4 oldpos = 0;
		{
			float w = 0.0f;
			[unroll]
			for (int i = 0; i < 3; i++)
			{
				oldskinning += boneMatrixOld[In.Indices[i]] * In.Weights[i];
				w += In.Weights[i];
			}
			oldskinning += boneMatrixOld[In.Indices[3]] * (1.0f - w);
		}
#if defined(INSTANCING)
		//�C���X�^���V���O
		oldskinning = mul(InstancingWorldMatrixOld[instanceID], oldskinning);
#endif
		oldpos = mul(oldskinning, In.Position);
		oldpos.xyz = lerp(posW, oldpos.xyz, MotionBlurScale);

		float3 trans = float3(skinning._m03, skinning._m13, skinning._m23);
		float3 transOld = float3(oldskinning._m03, oldskinning._m13, oldskinning._m23);
		transOld = lerp(trans, transOld, MotionBlurScale);
		trans -= transOld;

		if (length(trans) > camMoveVec.w
			&& distance(camMoveVec.xyz, trans) > camMoveVec.w
			|| distance(float3(skinning._m00, skinning._m10, skinning._m20), float3(oldskinning._m00, oldskinning._m10, oldskinning._m20)) > 0.0f
			|| distance(float3(skinning._m01, skinning._m11, skinning._m21), float3(oldskinning._m01, oldskinning._m11, oldskinning._m21)) > 0.0f
			|| distance(float3(skinning._m02, skinning._m12, skinning._m22), float3(oldskinning._m02, oldskinning._m12, oldskinning._m22)) > 0.0f
		) {
			psInput.isWorldMove = true;
		}

		float4 oldpos2 = mul(mView_old, oldpos);
		oldpos = mul(mView, oldpos);
		oldpos.xyz = lerp(oldpos.xyz, oldpos2.xyz, MotionBlurScale);

		oldpos = mul(mProj_old, oldpos);
			
		psInput.lastPos = oldpos;
#endif

    return psInput;
}
//Z�l�������ݗp
ZPSInput VSMainSkin_RenderZ(VSInputNmTxWeights In
#if defined(INSTANCING)
	, uint instanceID : SV_InstanceID
#endif 
){
	ZPSInput psInput = (ZPSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos = 0;
	{
		float w = 0.0f;
		[unroll]
		for (int i = 0; i < 3; i++)
		{
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//�Ō�̃{�[�����v�Z����B
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);		
	}
#if defined(INSTANCING)
	//�C���X�^���V���O
	skinning = mul(InstancingWorldMatrix[instanceID], skinning);
#endif

	//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
	//mul�͏�Z���߁B
	pos = mul(skinning, In.Position);	
	pos = mul(mView, pos);
	pos = mul(mProj, pos);

	psInput.Position = pos;
	psInput.posInProj = pos;
	psInput.TexCoord = In.TexCoord;

	return psInput;
}

//G-Buffer�o��
struct PSOutput_RenderGBuffer {
	float4 albedo		: SV_Target0;		//�A���x�h
	float3 normal		: SV_Target1;		//�@��
	float4 viewpos		: SV_Target2;		//�r���[���W
	float4 velocity		: SV_Target3;		//���x
	float4 velocityPS	: SV_Target4;		//���x(�s�N�Z���V�F�[�_)
	float4 lightingParam: SV_Target5;		//���C�e�B���O�p�p�����[�^�[
};
PSOutput_RenderGBuffer PSMain_RenderGBuffer(PSInput In)
{
	PSOutput_RenderGBuffer Out = (PSOutput_RenderGBuffer)0;

	//�A���x�h
	Out.albedo = albedoTexture.Sample(Sampler, In.TexCoord);
	Out.albedo.xyz = pow(Out.albedo.xyz, 2.2f);
	Out.albedo *= albedoScale;

	//���e�X�g
	if (Out.albedo.a > 0.5f) { 
		Out.albedo.a = 1.0f;//����������
	}
	else {
		discard;
	}

	//�@��
	Out.normal = In.Normal;

	//�r���[���W
	Out.viewpos = float4(In.Viewpos.x, In.Viewpos.y, In.Viewpos.z + depthBias.y, In.curPos.z / In.curPos.w + depthBias.x);

	//���C�e�B���O�p�p�����[�^�[
	Out.lightingParam = emissive;

	//���x
#if !defined(NO_MOTIONBLUR)
		float2	current = In.curPos.xy / In.curPos.w;
		float2	last = In.lastPos.xy / In.lastPos.w;		

		if (In.lastPos.z < 0.0f) {
		//if (last.z < 0.0f || last.z > 1.0f) {
			Out.velocity.z = min(In.curPos.z, In.lastPos.z) + depthBias.y;
			Out.velocity.w = max(In.curPos.z, In.lastPos.z) + depthBias.y; 
			Out.velocityPS.z = -1.0f;
			Out.velocityPS.w = -1.0f;
			return Out;
			//discard; 
		}

		current.xy *= float2(0.5f, -0.5f); current.xy += 0.5f;
		last.xy *= float2(0.5f, -0.5f); last.xy += 0.5f;

		Out.velocity.z = min(In.curPos.z, In.lastPos.z) + depthBias.y;
		Out.velocity.w = max(In.curPos.z, In.lastPos.z) + depthBias.y;

		if (In.isWorldMove || In.curPos.z + depthBias.y < depthBias.z) {
			Out.velocity.xy = current.xy - last.xy;

			Out.velocityPS.z = max(In.curPos.z, In.lastPos.z) + depthBias.y;
			Out.velocityPS.w = -1.0f;

			//Out.albedo.r = 1.0f; Out.albedo.b = 0.0f; Out.albedo.g = 0.0f;
		}
		else {
			Out.velocityPS.xy = current.xy - last.xy;
			
			Out.velocityPS.z = min(In.curPos.z, In.lastPos.z) + depthBias.y;
			Out.velocityPS.w = max(In.curPos.z, In.lastPos.z) + depthBias.y;

			if (abs(Out.velocityPS.x) < BUNBO*0.5f && abs(Out.velocityPS.y) < BUNBO*0.5f) {
				Out.velocityPS.z = Out.velocityPS.w;
				Out.velocityPS.w = -1.0f;
			}

			//Out.albedo.r *= 0.1f; Out.albedo.b = 1.0f; Out.albedo.g *= 0.1f;
		}
#else
		Out.velocity.z = In.curPos.z + depthBias.y;
		Out.velocity.w = In.curPos.z + depthBias.y;
		Out.velocityPS.z = -1.0f;// In.curPos.z + depthBias.y;
		Out.velocityPS.w = -1.0f;// In.curPos.z + depthBias.y;
#endif

	return Out;
}

//Z�l�o��
float4 PSMain_RenderZ(ZPSInput In) : SV_Target0
{
	//�A���x�h
	float alpha = albedoTexture.Sample(Sampler, In.TexCoord).a * albedoScale.a;

	//���e�X�g
	if (alpha > 0.5f) {
	}
	else {
		discard;
	}

	return In.posInProj.z / In.posInProj.w + depthBias.x ;// +1.0f*max(abs(ddx(In.posInProj.z / In.posInProj.w)), abs(ddy(In.posInProj.z / In.posInProj.w)));
}