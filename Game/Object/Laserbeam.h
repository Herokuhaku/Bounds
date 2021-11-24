#pragma once
#include <vector>
#include "../common/Vector3.h"

using HitNormal = std::pair<bool, Float3>;

class Laserbeam
{
public:
	static constexpr int LASER_COUNT_MAX = 8;
	static constexpr float LAZER_POW = 5000;


	Laserbeam(int stageid,float bulletpow);
	~Laserbeam();

	void Init(void);
	void Update(Float3 plpos,Float3 ang);
	void Draw(void);

	void CheckLaser(Float3 pos, Float3 ang, int& count);
	void Laser(Float3& pos, Float3& v);
	void DrawLaser(Float3 start,Float3 end);
	Float3 Ref(Float3 vec, Float3 normal);
private:
	HitNormal HitCheckStage(Float3 start, Float3 vec, Float3& end);

	std::vector<std::pair<Float3, Float3>> line_;
	int stageid_;
	float bulletpow_;
};

