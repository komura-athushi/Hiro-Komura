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
private:
	std::vector<int> m_numberlist;						//�����Ŏ󂯎�����������L������
	std::vector<CSprite*> m_spritelist;					//CSprite�̉ϒ��z��
	CVector3 m_position;								//�󂯎�������W
	CVector3 m_spriteposition;							//�X�N���[�����W
	CVector2 m_scale = { 0.3f,0.3f};
	const float m_addx = -0.015f;
	const float m_addy = -0.0015f;
	float m_y = 0.0f;
	const float m_frame = 40.0f;
	float m_alpha = 1.0f;
	float m_timer = 0.0f;								//�^�C�}�[
	const int m_time = 40;								//�^�C�}�[�̐���
	GameCamera* m_gamecamera = nullptr;
	GameData* m_gamedata = nullptr;
	int m_number;
};

