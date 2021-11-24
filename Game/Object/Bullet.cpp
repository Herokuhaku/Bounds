#include "Bullet.h"
#include <DxLib.h>

Bullet::Bullet(Float3 pos, Float3 vec, int stage,int player)
{
	pos_ = pos;
	vec_ = vec;
	stagemodel_ = stage;
	playermodel_ = player;
	Init();
}

Bullet::~Bullet()
{
}

void Bullet::Init(void)
{
	size_ = 25.0f;
	time_ = 0.0f;
	dead_ = false;
	count = 0;
}

void Bullet::Update(float delta)
{
	HitNormal hit = HitCheckStage(pos_);
	bool flag = false;
	if (!hit.first) {
		pos_ += vec_;
	}
	else if(time_ >= REF_INTERVAL){
		count++;
		// hit.second�ɖ@���x�N�g���������Ă���(���K���ς�)
		// ���˃x�N�g���������vec�ɓ����

		// �i�s�̋t�x�N�g���Ɩ@���x�N�g���̓��ς��Ƃ�
		auto dot = Dot(-vec_, hit.second);
		// vec + parallel �ŕǂɕ��s�ȃx�N�g��
		auto parallel = (dot * hit.second);

		// ���˃x�N�g�� �W����2�{�ɂ��邱�ƂŔ��˃x�N�g���ɂȂ�
		auto ref = vec_ + (2 * parallel);
		vec_ = ref;

		//pos_ += vec_;
		time_ = 0.0f;
		flag = true;
	}

	time_ += delta;

	if (count > 8) {
		dead_ = true;
	}
}

void Bullet::Draw(void)
{
	SetUseLighting(true);
	DrawSphere3D(pos_.toVECTOR(),size_,5,/*size_,*/ 0xff0000, 0xff0000, true);
	SetUseLighting(false);
}

HitNormal Bullet::HitCheckStage(Float3& end)
{
	HitNormal hit = std::make_pair<bool,Float3>(false,Float3());
	// �����蔻��x�N�g���̊J�n�n�_
	auto StartPos = pos_ + vec_;
	// �����蔻��x�N�g���̏I���n�_
	auto EndPos = pos_ + (vec_ *2);
	// �����蔻��`�F�b�N
	for (int i = 0; i < MV1GetFrameNum(stagemodel_); i++) {
		auto HitPoly = MV1CollCheck_Sphere(stagemodel_, i, StartPos.toVECTOR(),10);
	
		if (HitPoly.Dim != nullptr)
		{
			hit.first = true;
			hit.second = HitPoly.Dim->Normal;
			end = StartPos;
			//pos_ = Float3(HitPoly.Dim->HitPosition) - vec_;
			//hit.second.Normalize();
			return hit;
		}
	}
	return hit;
}
