#pragma once
class MainSound:public IGameObject
{
	//�V���O���g���A���̃N���X�̃C���X�^���X����������݂����Ȃ����Ƃ������f�U�C���p�^�[���̈�ł�
private:
	//�R���X�g���N�^�ƃf�X�g���N�^��private�ɐ錾���邱�ƂŊO�����琶���o���Ȃ����܂�
	MainSound();
	~MainSound();
public:
	//���̊֐����g����GameData�N���X�̃C���X�^���X�𐶐����܂�
	//���̊֐����̃��[�J���ȐÓI�ϐ��͍ŏ��Ɋ֐����Ă΂��Ƃ��ɂ͏���������܂����A�ȍ~�Ă΂�鎞�͏���������܂���
	static MainSound& GetInstance()
	{
		//private�ȃR���X�g���N�^���Ăяo��
		static MainSound inst;
		return inst;
	}
	bool Start();
	void Update();
	//�Đ�����BGM��ݒ肵�܂�
	void SetBGM(const int& state)
	{
		m_state2 = state;
	}
	enum State {
		enBGM_Title,										//�^�C�g��
		enBGM_Town,										    //���_
		enBGM_Stage1,										//�X�e�[�W1
		enBGM_Stage2,										//�X�e�[�W2
		enBGM_Stage3,										//�X�e�[�W3
	};
private:
	SuicideObj::CBGM* m_bgm = nullptr;
	int m_state1 = 0;				//���ݍĐ����Ă����	
	int m_state2 = 0;				//�Đ��\��̋�
};

