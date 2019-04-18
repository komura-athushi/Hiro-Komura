#pragma once
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
//�v���C���[�����̃I�u�W�F�N�g�ɋ߂Â��ƃX�e�[�W1�Ɉړ����܂�
class Stage2_Teleport :public IGameObject
{
public:
	Stage2_Teleport();
	~Stage2_Teleport();
	bool Start() override;
	void Update() override;
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
	GameObj::Suicider::CEffekseer* m_effect = nullptr;			//�G�t�F�N�g
	const float m_frame = 40.0f;
	CVector3 m_position = CVector3::Zero();                     //���W
	CVector3 m_scale = CVector3::One();                         //�傫��
	CQuaternion m_rotation;                                     //�N�I���e�[�V����
	PhysicsStaticObject m_staticobject;                         //�ÓI�I�u�W�F�N�g
};

