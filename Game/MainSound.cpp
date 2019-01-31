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
	m_bgm = NewGO<SuicideObj::CBGM>(L"Asset/sound/bgm/title.wav");
	m_bgm->Play(false, true); //ループで再生(第二引数)
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
			m_bgm->Play(false, true); //ループで再生(第二引数)
			break;
		case 1:
			m_bgm = NewGO<SuicideObj::CBGM>(L"Asset/sound/bgm/town.wav");
			m_bgm->Play(false, true); //ループで再生(第二引数)
			break;
		case 2:
			m_bgm = NewGO<SuicideObj::CBGM>(L"Asset/sound/bgm/stage1.wav");
			m_bgm->Play(false, true); //ループで再生(第二引数)
			break;
		case 3:
			break;
		}
		m_state1 = m_state2;
	}
}
