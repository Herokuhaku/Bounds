#include "Laserbeam.h"
#include <DxLib.h>

Laserbeam::Laserbeam(int stageid,float bulletpow)
{
	stageid_ = stageid;
	bulletpow_ = bulletpow;
	Init();
}

Laserbeam::~Laserbeam()
{
}

void Laserbeam::Init(void)
{
	line_.reserve(LASER_COUNT_MAX);
}

void Laserbeam::Update(Float3 pos, Float3 ang)
{
	int count = 0;
	//ang = ang;
	CheckLaser(pos,ang,count);
}

void Laserbeam::Draw(void)
{
	for (auto& line : line_) {
		DrawLaser(line.first,line.second);
	}
	line_.clear();
}

void Laserbeam::CheckLaser(Float3 pos, Float3 v,int& count)
{
	count++;
	// �ǂɓ��������ʒu
	Float3 end;
	// �x�N�g���ɒe�̃X�s�[�h��������

	// �X�e�[�W�Ƃ̓����蔻����Ƃ�
	// �Ԃ�l�� pair<�����������ǂ���,�@���x�N�g��>
	HitNormal hit = HitCheckStage(pos,v,end);
	// end�͎Q�Ƃœn���Ă��āA���������ʒu��Ԃ�
	if (count > 0) {
		line_.emplace_back(pos, end);
	}
	// ���˃x�N�g����Ref�ō���ăx�N�g���ɂ����
	v = Ref(v, hit.second);
	// pos�𓖂�������ɓ���ւ���
	pos = end;
	if (count < 7) {
		CheckLaser(pos, v, count);
	}

}

void Laserbeam::Laser(Float3& pos, Float3& v)
{
	//hit = HitCheckStage(pos, v, end);
	//line_.emplace_back(pos, end);

	//v = Ref(v, hit.second);
	//pos = end + v*2;
}

void Laserbeam::DrawLaser(Float3 start, Float3 end)
{
	DrawCapsule3D(start.toVECTOR(), end.toVECTOR(), 5, 16, 0xffff00, 0xffff00, true);
}

Float3 Laserbeam::Ref(Float3 vec, Float3 normal)
{
	//vec.Normalize();
	// �i�s�̋t�x�N�g���Ɩ@���x�N�g���̓��ς��Ƃ�
	auto dot = Dot(-vec, normal);
	// vec + parallel �ŕǂɕ��s�ȃx�N�g��
	auto parallel = (dot * normal);

	// ���˃x�N�g�� �W����2�{�ɂ��邱�ƂŔ��˃x�N�g���ɂȂ�
	auto ref = vec + (2 * parallel);
	return ref;
}

HitNormal Laserbeam::HitCheckStage(Float3 start,Float3 vec,Float3& end)
{
	HitNormal hit = std::make_pair<bool, Float3>(false, Float3());
	int count = 0;
	// �����蔻��x�N�g���̊J�n�n�_
	auto StartPos = start + vec;
	auto oldpos = start;
	MV1_COLL_RESULT_POLY_DIM HitPoly;
	//auto HitPoly = MV1CollCheck_Sphere(stageid_,0, StartPos.toVECTOR(), 10);
	while (count++ < 1000) {
		// �����蔻��`�F�b�N
		for (int i = 0; i < MV1GetFrameNum(stageid_); i++) {
			HitPoly = MV1CollCheck_Sphere(stageid_, i, StartPos.toVECTOR(), 10);

			if (HitPoly.Dim != nullptr)
			{
				hit.first = true;
				hit.second = HitPoly.Dim->Normal;
				//end = HitPoly.Dim->HitPosition;
				end = StartPos;
				MV1CollResultPolyDimTerminate(HitPoly);
				return hit;
			}
			MV1CollResultPolyDimTerminate(HitPoly);
		}
		oldpos = StartPos;
		StartPos += vec;
	}	
	return hit;
}
