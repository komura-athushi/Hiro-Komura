#pragma once
class GameCamera;
class GameData;
class FontNumber:public IGameObject
{
public:
	FontNumber();
	~FontNumber();
	bool Start();
	void Update();
	void PostRender()override;
	//�\�����鐔�����󂯎��
	void SetNumber(const int& number)
	{
		m_number = number;
	}
	//���W��ݒ�
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}
	//�ԐF�ɐݒ�
	void SetRed()
	{
		m_isred = true;
	}
private:
	std::vector<int> m_numberlist;						//�����Ŏ󂯎�����������L������A154�Ȃ�{1, 5, 4}�݂����Ȋ�����
	std::vector<CSprite*> m_spritelist;					//CSprite�̉ϒ��z��
	CVector3 m_position;								//�󂯎�������W
	CVector3 m_spriteposition;							//�X�N���[�����W
	CVector2 m_scale = { 0.3f,0.3f};
	CVector3 m_plusposition = CVector3::Zero();			//�����_���ɍ��W��ς���
	const float m_addx = -0.016f;						//�\�����鐔����x�����ɏ��������炵�܂�
	const float m_addy = -0.0015f;						//�\�����鐔������������ɓ����悤�ɂ��܂�
	float m_y = 0.0f;
	const float m_frame = 40.0f;
	float m_alpha = 1.0f;
	float m_timer = 0.0f;								//�^�C�}�[
	const int m_time = 40;								//�^�C�}�[�̐���
	GameCamera* m_gamecamera = nullptr;
	GameData* m_gamedata = nullptr;
	int m_number;										//�󂯎�������l���L�����܂�
	bool m_isred = false;
};

