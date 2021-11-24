#include "Camera.h"

#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../AsoUtility.h"


Camera::Camera()
{
	Init();
}

Camera::~Camera()
{
}

void Camera::Init(void)
{
	pos_ = Float3{ 0.0f,200.0f,-500.0f };
	angles_ = Float3{ static_cast<float>(AsoUtility::Deg2Rad(30)),0.0f,0.0f};
}

void Camera::Update(void)
{

	Float2 scrsize = lpSceneMng.GetScreenSize() / 2;
	// �}�E�X���Ǘ�����
	Int2 mpos;
	GetMousePoint(&mpos.x, &mpos.y);

	// ���x����
	float movePow = 20;

	// �L�[�{�[�h����ŃJ�������ړ�
	// �O��ړ�
	char key[256];
	GetHitKeyStateAll(key);
	float rad = 0.0f;

	// �L�[�{�[�h����ŃJ�����p�x��ύX(�R���g���[���[�͂��̕���)
	//if (key[KEY_INPUT_RIGHT]) {
	//	// �E��]
	//	angles_.y += AsoUtility::Deg2Rad(movePow);
	//}
	//if (key[KEY_INPUT_LEFT]) {
	//	// �E��]
	//	angles_.y -= AsoUtility::Deg2Rad(movePow);
	//}

	Float2 vec;
	vec = (Float2(mpos.x,mpos.y) - scrsize);
	Int2 plus;
	// ������ۑ�����
	plus = vec.GetSign();
	// ��Βl�����
	vec.Abs();

	// �}�E�X����ŃJ�����p�x��ύX
 	if (plus.x > 0) {
		// �E��]
		angles_.y += AsoUtility::Deg2Rad(vec.x / movePow);
	}
	if (plus.x < 0) {
		// ����]
		angles_.y -= AsoUtility::Deg2Rad(vec.x / movePow);
	}
	if (plus.y > 0) {
		// �����낷
		angles_.x += AsoUtility::Deg2Rad(vec.y / movePow);
	}
	if (plus.y < 0) {
		// ���グ��
		angles_.x -= AsoUtility::Deg2Rad(vec.y / movePow);
	}


	//// �L�[�{�[�h����ŃJ�����p�x��ύX
	//if (key[KEY_INPUT_DOWN]) {
	//	// �����낷
	//	angles_.x += AsoUtility::Deg2Rad(movePow);
	//}
	//if (key[KEY_INPUT_UP]) {
	//	// ���グ��
	//	angles_.x -= AsoUtility::Deg2Rad(movePow);
	//}
}

std::pair<bool, double> Camera::Update(Float3 pos)
{
	bool flag = false;
	double rotrad = 0.0f;
	pos_ = pos;
	float movePow = 1;
	// �L�[�{�[�h����ŃJ�������ړ�
	// �O��ړ�
	char key[256];
	GetHitKeyStateAll(key);
	float rad = 0.0f;
	//// �����ړ�	
	if (key[KEY_INPUT_N]) {
		pos_.y -= movePow;
	}
	if (key[KEY_INPUT_M]) {
		pos_.y += movePow;
	}

	// �L�[�{�[�h����ŃJ�����p�x��ύX
	if (key[KEY_INPUT_RIGHT]) {
		// �E��]
		rotrad = AsoUtility::Deg2Rad(movePow);
		angles_.y += rotrad;
		flag = true;
	}
	if (key[KEY_INPUT_LEFT]) {
		// �E��]
		rotrad = AsoUtility::Deg2Rad(movePow);
		angles_.y -= rotrad;
		flag = true;
	}

	// �L�[�{�[�h����ŃJ�����p�x��ύX
	if (key[KEY_INPUT_DOWN]) {
		// �����낷
		angles_.x += AsoUtility::Deg2Rad(movePow);
		//flag = true;
	}
	if (key[KEY_INPUT_UP]) {
		// ���グ��
		angles_.x -= AsoUtility::Deg2Rad(movePow);
		//flag = true;
	}

	return std::pair<bool,double>(flag,rotrad);
}

void Camera::SetBeforeDraw(void)
{
	SetCameraPositionAndAngle(pos_.toVECTOR(), angles_.x, angles_.y, angles_.z);
	VECTOR vec = GetCameraFrontVector();
	vec = vec;
}

void Camera::Draw(void)
{
}

void Camera::Release(void)
{
}

Float3 Camera::GetPos(void)
{
	return pos_;
}

Float3 Camera::GetAngles(void)
{
	return angles_;
}

void Camera::SetPos(Float3 pos)
{
	pos_ = pos;
}

void Camera::SetAngles(Float3 angle)
{
	angles_ = angle;
}

VECTOR Camera::GetDxlibAngles(void)
{
	return GetCameraFrontVector();
}
