#include "stdafx.h"
#include "Morugan.h"
#include "Player.h"
#include "IEnemy.h"
#include "PlayerStatus.h"
Morugan::Morugan()
{
}


Morugan::~Morugan()
{
	delete m_effect;
}

bool Morugan::Start()
{
    m_effect = new GameObj::Suicider::CEffekseer;
	m_effect->Play(L"Asset/effect/Effects/efk/magic_laser.efk", 1.0f, m_position, m_rotation, m_scale);
	//m_effect->Play(L"Asset/effect/morugan/efk/morugan.efk", 1.0f, m_position, m_rotation, m_scale);
	m_player = FindGO<Player>(L"Player");
	//�G�t�F�N�g���v���C���[�̌����ɉ�]
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), atan2f(-m_player->GetFront().x, -m_player->GetFront().z));
	m_effect->SetRot(qRot);
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	return true;
}

void Morugan::Update()
{
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), atan2f(-m_player->GetFront().x, -m_player->GetFront().z));
	m_effect->SetRot(qRot);
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	if (m_timer >= m_time) {
		//A�x�N�g��(�P�ʃx�N�g��)�A�����K���̐��ʂ̃x�N�g��
		CVector3 front = m_player->GetFront();
		QueryGOs<IEnemy>(L"Enemy", [&](IEnemy* enemy)
		{
			//�G�l�~�[������ł����珈�����I�����܂�
			if (enemy->GetDeath()) {
				return true;
			}
			//B�x�N�g���A�G�l�~�[�̍��W���烂���K���̍��W���������x�N�g��
			CVector3 pos = enemy->GetPosition() - m_position;
			//A�x�N�g����B�x�N�g���̓��ς����߂�
			//����ɂ��uB�x�N�g������A�x�N�g���ɐ����x�N�g���v�ƁuA�x�N�g���v�̌������W����A�x�N�g���̎n�_�܂ł̒��������܂�
			float ip = front.Dot(pos);
			//���ς�0�����Ȃ珈�����I������
			if (ip < 0) {
				return true;
			}
			//���ς������K���̒�����蒷���ꍇ�A�������I������
			else if (ip > m_length) {
				return true;
			}
			//A�x�N�g���ɋ��߂����ς������āA�uB�x�N�g������A�x�N�g���ɐ����x�N�g���v�ƁuA�x�N�g���v�̌������W��C�x�N�g�������߂�
			CVector3 c = front * ip;
			//C�x�N�g����B�x�N�g���̋����̋�����2�悪���ȉ�(�G�̃R���W�����̔��a�{�����K���̂��񂿂��̔��a��2��)�Ȃ�G�l�~�[�Ƀ_���[�W��^����
			CVector3 pos2 = pos - c;
			if (pos2.LengthSq() <= std::pow((enemy->GetRadius() + m_r), 2.0f)) {
				enemy->Damage(m_damage);
				//�����G�l�~�[��HP��0�ȉ��ɂȂ�����
				if (enemy->GetDeath()) {
					//�G�l�~�[�̌o���l���v���C���[�̌o���l�ɉ��Z
					PlayerStatus* playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
					playerstatus->PlusExp(enemy->GetExp());
				}
			}
			return true;
		});
	}
	m_timer += m_frame * GetDeltaTimeSec();
	//�v���C���[���r�����łȂ��Ȃ玩�g���폜����
	if (!m_player->GetAria()) {
		delete this;
	}
}


