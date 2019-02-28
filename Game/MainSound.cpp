#include "stdafx.h"
#include "MainSound.h"


MainSound::MainSound()
{
}


MainSound::~MainSound()
{
}

bool MainSound::Start()
{
	//�}�X�^�[�{�����[����ݒ�
	//SetMasterVolume(0.0f);
	m_bgm = NewGO<SuicideObj::CBGM>(L"Asset/sound/bgm/title.wav");
	m_bgm->Play(false, true); //���[�v�ōĐ�(������)
	return true;
}

void MainSound::Update()
{
	if (m_state1 != m_state2) {
		DeleteGO(m_bgm);
		m_bgm = nullptr;
		switch (m_state2) {
		case 0:
			m_bgm = NewGO<SuicideObj::CBGM>(L"Asset/sound/bgm/title.wav");
			m_bgm->Play(false, true); //���[�v�ōĐ�(������)
			break;
		case 1:
			m_bgm = NewGO<SuicideObj::CBGM>(L"Asset/sound/bgm/town.wav");
			m_bgm->Play(false, true); //���[�v�ōĐ�(������)
			break;
		case 2:
			m_bgm = NewGO<SuicideObj::CBGM>(L"Asset/sound/bgm/stage1.wav");
			m_bgm->Play(false, true); //���[�v�ōĐ�(������)
			break;
		case 3:
			m_bgm = NewGO<SuicideObj::CBGM>(L"Asset/sound/bgm/stage2.wav");
			m_bgm->Play(false, true); //���[�v�ōĐ�(������)
			break;
		case 4:
			m_bgm = NewGO<SuicideObj::CBGM>(L"Asset/sound/bgm/stage3.wav");
			m_bgm->Play(false, true); //���[�v�ōĐ�(������)
			break;
		}
		m_state1 = m_state2;
	}
}
