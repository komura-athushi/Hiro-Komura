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
			if (Pad(0).GetDown(enButtonB) && !m_isaccess) {
				m_isaccess = true;
				m_player->SetStop();
				m_isbutton = false;
			}
		}
		else {
			m_isdisplay = false;
		}
	}
	else {
		m_isdisplay = false;
	}
	if (!Pad(0).GetButton(enButtonA) && !Pad(0).GetButton(enButtonB)) {
		m_isbutton = true;
	}
	if (m_isaccess && m_isbutton) {
		if (Pad(0).GetDown(enButtonB)) {
			m_player->SetMove();
			m_player->SetGameClear();
			m_isbutton = false;
		}
		else if (Pad(0).GetDown(enButtonA)) {
			m_isaccess = false;
			m_isbutton = false;
			m_player->SetMove();
		}
	}
}

void Teleport::PostRender()
{
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
		m_font.DrawScreenPos(output, { 00.0f,00.0f }, CVector4::White());
	}
}