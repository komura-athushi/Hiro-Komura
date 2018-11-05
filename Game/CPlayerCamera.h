#pragma once

#include"TpsCamera.h"

class CPlayerCamera : public IGameObject {
public:
	bool Start()override {
		//TPS�J�����̏�����
		m_camera.Init(CVector3::Zero(), CVector3::AxisZ()*200.0f, CVector3::Up());
		m_camera.GetCamera().SetFar(2000.0f);
		//���C���J�����ɐݒ�
		m_camera.SetToMainCamera();

		//�}�E�X�J�[�\���𒆉��ɌŒ�
		GetMouseCursorManager().SetLockMouseCursor(true);
		//�}�E�X�J�[�\�����\��
		GetMouseCursorManager().SetShowMouseCursor(false);

		m_camera.RotationCamera({ 0.0f,CMath::PI*-0.5f });


		return true;
	}
	void Update()override {
		if (!m_lock) {
			//�}�E�X�J�[�\���̓����ɘA�����ăJ������]
			CVector2 mousemove = GetMouseCursorManager().GetMouseMove();
			mousemove.x *= m_sensi.x; mousemove.y *= m_sensi.y;
			m_camera.RotationCamera(mousemove);
		}

		if (GetAsyncKeyState('R')) {
			m_camera.RotationCamera({ 0.31f,0.0f });
		}
		if (GetAsyncKeyState('Q')) {
			m_camera.RotationCamera({ -0.31f,0.0f });
		}

		if (GetAsyncKeyState('O')) {
			//�}�E�X�J�[�\���𒆉��ɌŒ�
			GetMouseCursorManager().SetLockMouseCursor(true);
			//�}�E�X�J�[�\�����\��
			GetMouseCursorManager().SetShowMouseCursor(false);
			m_lock = false;
		}
		if (GetAsyncKeyState('P')) {
			//�}�E�X�J�[�\���𒆉��ɌŒ�
			GetMouseCursorManager().SetLockMouseCursor(false);
			//�}�E�X�J�[�\�����\��
			GetMouseCursorManager().SetShowMouseCursor(true);
			m_lock = true;
		}

		//�J�����X�V
		m_camera.Update();
	};

	void SetPos(const CVector3& v) {
		m_camera.SetTarget(v);
	}

	CVector3 GetFront()const {
		return m_camera.GetFront();
	}
	CVector3 GetUp()const {
		return m_camera.GetUp();
	}
	CVector3 GetLeft()const {
		return CVector3::GetCross(m_camera.GetFront(), m_camera.GetUp());
	}

private:
	TpsCamera m_camera;
	CVector2 m_sensi = { 4.0f*(1.0f/1280.0f),-4.0f*(1.0f / 1280.0f) };
	bool m_lock = false;
};

