#pragma once
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Stage3_Teleport:IGameObject
{
public:
	Stage3_Teleport();
	~Stage3_Teleport();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//���W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	GameObj::Suicider::CEffekseer* m_effect;		//�G�t�F�N�g
	const float m_frame = 40.0f;
	CVector3 m_position;                                        //���W
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //�傫��
	CQuaternion m_rotation;                                     //�N�I���e�[�V����
	PhysicsStaticObject m_staticobject;                         //�ÓI�I�u�W�F�N�g
};

