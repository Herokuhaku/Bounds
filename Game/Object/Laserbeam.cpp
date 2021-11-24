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
	// 壁に当たった位置
	Float3 end;
	// ベクトルに弾のスピードをかける

	// ステージとの当たり判定をとる
	// 返り値は pair<当たったかどうか,法線ベクトル>
	HitNormal hit = HitCheckStage(pos,v,end);
	// endは参照で渡していて、当たった位置を返す
	if (count > 0) {
		line_.emplace_back(pos, end);
	}
	// 反射ベクトルをRefで作ってベクトルにいれる
	v = Ref(v, hit.second);
	// posを当たった先に入れ替える
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
	// 進行の逆ベクトルと法線ベクトルの内積をとる
	auto dot = Dot(-vec, normal);
	// vec + parallel で壁に平行なベクトル
	auto parallel = (dot * normal);

	// 反射ベクトル 係数を2倍にすることで反射ベクトルになる
	auto ref = vec + (2 * parallel);
	return ref;
}

HitNormal Laserbeam::HitCheckStage(Float3 start,Float3 vec,Float3& end)
{
	HitNormal hit = std::make_pair<bool, Float3>(false, Float3());
	int count = 0;
	// 当たり判定ベクトルの開始地点
	auto StartPos = start + vec;
	auto oldpos = start;
	MV1_COLL_RESULT_POLY_DIM HitPoly;
	//auto HitPoly = MV1CollCheck_Sphere(stageid_,0, StartPos.toVECTOR(), 10);
	while (count++ < 1000) {
		// 当たり判定チェック
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
