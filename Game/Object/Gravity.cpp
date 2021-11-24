#include "Gravity.h"
#include <math.h>

Gravity::Gravity(Float3& pos,bool& jump,bool& fall,double& time, int stagemodel):pos_(pos),jump_(jump),fall_(fall),time_(time)
{
	stagemodel_ = stagemodel;
	Init();
}

void Gravity::Init(void)
{
	v1 = 25;
	gravity_ = 10;
	gravitybool_ = true;
	jumppow_ = 0;
}

void Gravity::Update(float delta)
{
	if (fall_) {
		time_ += delta;
		// ����͂������
		jumppow_ = static_cast<float>((time_ * log(time_)) * gravity_);
		Float3 vec = Float3(0, jumppow_, 0);
		if (!CheckStage(vec, pos_)) {
			pos_.y += -jumppow_;
		}
		else {
			jump_ = false;
			fall_ = false;
			jumppow_ = 0;
			time_ = 0.5;
		}
	}
	if (jump_ && !fall_) {
		time_ += delta;
		// �W�����v���͑���(-�͏�����@( < 0))
		if (jumppow_ <= 0) {
			jumppow_ = static_cast<float>((time_ * log(time_)) * v1);
		}
		else {
			fall_ = true;
			jump_ = false;
		}
		// �������ē�����Ȃ���������W��+

		pos_.y += -jumppow_;
	}
}

bool Gravity::CheckStage(Float3& vec, Float3& pos)
{
	// �����蔻��x�N�g���̊J�n�n�_
	auto StartPos = pos_;
	// �����蔻��x�N�g���̏I���n�_
	auto EndPos = pos_ + vec;

	auto CenterPos = pos_ + (vec / 2);
	// �����蔻��`�F�b�N
	//auto HitPoly = MV1CollCheck_Line(stagemodelid_,4, StartPos.toVECTOR(), EndPos.toVECTOR());
	//fallline_[0] = StartPos.toVECTOR();
	//fallline_[1] = EndPos.toVECTOR();
	//DrawSphere3D(CenterPos.toVECTOR(), movepow_, movepow_, 0xffff00, 0xffff00, true);
	// �����蔻��`�F�b�N
	for (int i = 0; i < MV1GetFrameNum(stagemodel_); i++) {
		//auto HitPoly = MV1CollCheck_Sphere(stagemodel_, i, CenterPos.toVECTOR(),abs(static_cast<int>(vec.y))/2);
		//if (HitPoly.Dim != nullptr)
		//{
		//	//pos_ = pos_ - jumppow_;
		//	MV1CollResultPolyDimTerminate(HitPoly);
		//	return true;
		//}
		//MV1CollResultPolyDimTerminate(HitPoly);
		auto HitPoly = MV1CollCheck_Line(stagemodel_, i, pos.toVECTOR(), (pos + vec).toVECTOR());
		if (HitPoly.HitFlag) {
			pos = HitPoly.HitPosition;
			return true;
		}
	}
	return false;
}
