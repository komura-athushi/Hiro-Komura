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
	//マスターボリュームを設定
	SetMasterVolume(0.0f);
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
	    case enBGM_Title:
			m_bgm = NewGO<SuicideObj::CBGM>(L"Asset/sound/bgm/title.wav");
			m_bgm->Play(false, true); //ループで再生(第二引数)
			break;
		case enBGM_Town:
			m_bgm = NewGO<SuicideObj::CBGM>(L"Asset/sound/bgm/town.wav");
			m_bgm->Play(false, true); //ループで再生(第二引数)
			break;
		case enBGM_Stage1:
			m_bgm = NewGO<SuicideObj::CBGM>(L"Asset/sound/bgm/stage1.wav");
			m_bgm->Play(false, true); //ループで再生(第二引数)
			break;
		case enBGM_Stage2:
			m_bgm = NewGO<SuicideObj::CBGM>(L"Asset/sound/bgm/stage2.wav");
			m_bgm->Play(false, true); //ループで再生(第二引数)
			break;
		case enBGM_Stage3:
			m_bgm = NewGO<SuicideObj::CBGM>(L"Asset/sound/bgm/stage3.wav");
			m_bgm->Play(false, true); //ループで再生(第二引数)
			break;
		case enBGM_End:
			m_bgm = NewGO<SuicideObj::CBGM>(L"Asset/sound/bgm/end_.wav");
			m_bgm->Play(false, true); //ループで再生(第二引数)
			break;
		}
		m_state1 = m_state2;
	}
}
