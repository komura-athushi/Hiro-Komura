
//�萔
cbuffer CSCb : register(b0) {
	//�t���[���o�b�t�@�𑜓x
	uint win_x;
	uint win_y;
	//�����X�P�[��
	float distanceScale;
};

// ���̓e�N�X�`��
Texture2D<float4> albedoTexture : register(t2);

// �o�̓e�N�X�`��
RWTexture2D<float4> rwOutputTex		: register(u0);
RWTexture2D<float4> rwVelocityTex	: register(u1);

static const float samples = 8.0f;
static const float blurscale = -0.15f;
static const float Z_OFFSET = 15.0f;
static const float BUNBO = 0.002f*(8.0f / samples);

[numthreads(32, 32, 1)]
void CSmain(uint3 run_xy : SV_DispatchThreadID)//uint3 run_xy : SV_GroupID , uint3 threadid : SV_GroupThreadID)
{
	//uint x = run_xy.x * 32 + threadid.x, y = run_xy.y * 32 + threadid.y;
	//uint x = run_xy.x, y = run_xy.y;

	uint2 uv = run_xy.xy;

	if (uv.x % 2 == 0) {
		uv.x = win_x - uv.x;
	}
	if (uv.y % 2 == 0) {
		uv.y = win_y - uv.y;
	}

	//�e�N�X�`���T�C�Y�����Ă���o��
	if (uv.x > win_x || uv.y > win_y) {
		return;
	}			

	//���x�擾
	float3 velocity = rwVelocityTex[uv].xyz;
	velocity.xy *= blurscale;	

	//���x�������Ɖ������Ȃ�
	if (abs(velocity.x) < BUNBO*0.5f && abs(velocity.y) < BUNBO*0.5f) {//0.001f
		return;
	}
			
	//�F�擾
	float4 color = albedoTexture[uv];

	float loopmax = min(samples,max(abs(velocity.x), abs(velocity.y))/BUNBO);

	//���W�ϊ�
	velocity.x *= (float)win_x;
	velocity.y *= (float)win_y;

	[unroll]
	for (float i = 0.0f; i < loopmax; i++)
	{
		uint2 sampuv = round((float2)uv + ((i + 1.0f) / loopmax) * velocity.xy);

		if (sampuv.x < 0 || sampuv.y < 0 || sampuv.x > win_x || sampuv.y > win_y) { break; }
		
		float4 samp = rwVelocityTex[sampuv];

		if (velocity.z < samp.w+Z_OFFSET*distanceScale) {//��O�̃s�N�Z������̓T���v�����Ȃ�
			rwOutputTex[sampuv] = lerp(rwOutputTex[sampuv], color, 1.0f / (i + 2.0f));//�T���v�����œ����x
			//rwVelocityTex[sampuv] = float4(samp.xyz, velocity.z);
			//rwOutputTex[sampuv] = color;

			//rwOutputTex[sampuv] += color;			
			//samp.w += 1.0f; rwVelocityTex[sampuv] = samp;
		}
	}
}

//
[numthreads(32, 32, 1)]
void CSresolve(uint3 run_xy : SV_DispatchThreadID)
{
	uint2 uv = run_xy.xy;

	//�e�N�X�`���T�C�Y�����Ă���o��
	if (uv.x > win_x || uv.y > win_y) {
		return;
	}

	float sampcnt = rwVelocityTex[uv].w;
	if (sampcnt > 0.0f) {
		rwOutputTex[uv] /= (sampcnt + 1.0f);
	}
}