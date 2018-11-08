#pragma once
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
//�X�e�[�W�̏��Ƃ��ǂƂ��𐶐�����N���X�ł�
class Ground : public IGameObject
{
public:
	Ground();
	~Ground();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//�X�e�[�W�̏���ݒ�
	void SetStage(const int& stage)
	{
		m_stage = stage;
	}
private:

	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_position;                                        //���W
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //�傫��
	CQuaternion m_rotation;                                     //�N�I���e�[�V����
	PhysicsStaticObject m_staticobject;                         //�ÓI�I�u�W�F�N�g
	int m_stage = 0;                                            //�X�e�[�W���
};

