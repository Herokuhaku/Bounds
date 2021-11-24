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
	// マウスも管理する
	Int2 mpos;
	GetMousePoint(&mpos.x, &mpos.y);

	// 感度調整
	float movePow = 20;

	// キーボード操作でカメラを移動
	// 前後移動
	char key[256];
	GetHitKeyStateAll(key);
	float rad = 0.0f;

	// キーボード操作でカメラ角度を変更(コントローラーはこの方式)
	//if (key[KEY_INPUT_RIGHT]) {
	//	// 右回転
	//	angles_.y += AsoUtility::Deg2Rad(movePow);
	//}
	//if (key[KEY_INPUT_LEFT]) {
	//	// 右回転
	//	angles_.y -= AsoUtility::Deg2Rad(movePow);
	//}

	Float2 vec;
	vec = (Float2(mpos.x,mpos.y) - scrsize);
	Int2 plus;
	// 符号を保存する
	plus = vec.GetSign();
	// 絶対値を取る
	vec.Abs();

	// マウス操作でカメラ角度を変更
 	if (plus.x > 0) {
		// 右回転
		angles_.y += AsoUtility::Deg2Rad(vec.x / movePow);
	}
	if (plus.x < 0) {
		// 左回転
		angles_.y -= AsoUtility::Deg2Rad(vec.x / movePow);
	}
	if (plus.y > 0) {
		// 見下ろす
		angles_.x += AsoUtility::Deg2Rad(vec.y / movePow);
	}
	if (plus.y < 0) {
		// 見上げる
		angles_.x -= AsoUtility::Deg2Rad(vec.y / movePow);
	}


	//// キーボード操作でカメラ角度を変更
	//if (key[KEY_INPUT_DOWN]) {
	//	// 見下ろす
	//	angles_.x += AsoUtility::Deg2Rad(movePow);
	//}
	//if (key[KEY_INPUT_UP]) {
	//	// 見上げる
	//	angles_.x -= AsoUtility::Deg2Rad(movePow);
	//}
}

std::pair<bool, double> Camera::Update(Float3 pos)
{
	bool flag = false;
	double rotrad = 0.0f;
	pos_ = pos;
	float movePow = 1;
	// キーボード操作でカメラを移動
	// 前後移動
	char key[256];
	GetHitKeyStateAll(key);
	float rad = 0.0f;
	//// 垂直移動	
	if (key[KEY_INPUT_N]) {
		pos_.y -= movePow;
	}
	if (key[KEY_INPUT_M]) {
		pos_.y += movePow;
	}

	// キーボード操作でカメラ角度を変更
	if (key[KEY_INPUT_RIGHT]) {
		// 右回転
		rotrad = AsoUtility::Deg2Rad(movePow);
		angles_.y += rotrad;
		flag = true;
	}
	if (key[KEY_INPUT_LEFT]) {
		// 右回転
		rotrad = AsoUtility::Deg2Rad(movePow);
		angles_.y -= rotrad;
		flag = true;
	}

	// キーボード操作でカメラ角度を変更
	if (key[KEY_INPUT_DOWN]) {
		// 見下ろす
		angles_.x += AsoUtility::Deg2Rad(movePow);
		//flag = true;
	}
	if (key[KEY_INPUT_UP]) {
		// 見上げる
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
