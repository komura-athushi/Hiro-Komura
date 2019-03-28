#include "stdafx.h"
#include "Teleport.h"
#include "Player.h"
#include "GameCamera.h"
Teleport::Teleport()
{
}


Teleport::~Teleport()
{
	delete m_effect;
}

bool Teleport::Start()
{
	m_effect = new GameObj::Suicider::CEffekseer;
	m_effect->Play(L"Asset/effect/tornade/tornade.efk", 1.0f, m_position, CQuaternion::Identity(), { 12.0f,10.0f,12.0f });
	m_player = FindGO<Player>(L"Player");
	m_gamecamera = FindGO<GameCamera>();
	m_sprite.Init(L"Resource/sprite/target2.dds");
	m_sprite2.Init(L"Resource/sprite/window.dds");
	return true;
}

void Teleport::Update()
{
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	CVector3 pos = m_player->GetPosition() - m_position;
	if (pos.LengthSq() <= 200.0f * 200.0f) {
		//�Y���̃��[���h���W��2D���W��ϊ����܂�)
		CVector3 pos = m_gamecamera->GetCamera()->CalcScreenPosFromWorldPos(m_position);
		//�G�l�~�[�̍��W����ʊO�ł���Ή摜�͕\�����܂���
		//�Y���̍��W�Ƀ^�[�Q�b�g�̍��W��\�����܂�
		if (0.0f <= pos.x && pos.x <= 1.0f && 0.0f <= pos.y && pos.y <= 1.0f && 0.0f <= pos.z && pos.z <= 1.0f) {
			m_displayposition = pos;
			m_isdisplay = true;
			if (Pad(0).GetDown(enButtonA) && !m_isaccess) {
				m_isaccess = true;
				m_player->SetStop();
				m_isbutton = false;
				SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/kettei.wav");
				se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
				se->SetVolume(2.0f);
				//3D�Đ�
				se->SetPos(m_position);//���̈ʒu
				se->SetDistance(500.0f);//������������͈�
				se->Play(true); //��������true
			}
		}
		else {
			m_isdisplay = false;
		}
	}
	else {
		m_isdisplay = false;
	}
	if (!Pad(0).GetButton(enButtonB) && !Pad(0).GetButton(enButtonA)) {
		m_isbutton = true;
	}
	if (m_isaccess && m_isbutton) {
		if (Pad(0).GetDown(enButtonA)) {
			m_player->SetMove();
			m_player->SetGameClear();
			m_isbutton = false;
			SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/kettei.wav");
			se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
			se->SetVolume(2.0f);
			//3D�Đ�
			se->SetPos(m_position);//���̈ʒu
			se->SetDistance(500.0f);//������������͈�
			se->Play(true); //��������tru
		}
		else if (Pad(0).GetDown(enButtonB)) {
			m_isaccess = false;
			m_isbutton = false;
			m_player->SetMove();
			SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/cansel.wav");
			se->Play(); //�Đ�(�Đ����I���ƍ폜����܂�)
			se->SetVolume(5.0f);
			//3D�Đ�
			se->SetPos(m_position);//���̈ʒu
			se->SetDistance(500.0f);//������������͈�
			se->Play(true); //��������tru
		}
	}
}

void Teleport::PostRender()
{
	if (m_player->GetisClearAnimation()) {
		return;
	}
	if (!m_isdisplay) {
		return;
	}
	m_sprite.Draw(m_displayposition, { 0.2f,0.2f }, { 0.5f,0.5f },
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		DirectX::SpriteEffects_None,
		1.0f);
	if (m_isaccess) {
		wchar_t output[256];
		swprintf_s(output, L"�X�e�[�W���N���A���܂����H\n");
		m_font.DrawScreenPos(output, { 300.0f,450.0f }, CVector4::White(), { 0.6f,0.6f });
		m_sprite2.DrawScreenPos({ 290.0f,440.0f }, CVector3::One(), CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 0.7f },
			DirectX::SpriteEffects_None,
			0.8f);
	}
}