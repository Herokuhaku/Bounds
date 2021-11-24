#pragma once
#include <string>
#include <vector>
#include "DxLib.h"
#include "common/Vector3.h"
static class AsoUtility
{

public:

	static std::vector <std::string> Split(std::string& line, char delimiter);

	// ���W�A��(rad)����x(deg)
	static double Rad2Deg(double rad);

	// �x(deg)���烉�W�A��(rad)
	static double Deg2Rad(double deg);

	// 0�`360�x�͈̔͂Ɏ��߂�
	static double DegIn360(double deg);

	// 0(0)�`2��(360�x)�͈̔͂Ɏ��߂�
	static double RadIn2PI(double rad);

	// ��]�����Ȃ����̉�]�������擾����(���v���:1�A�����v���:-1)
	static int DirNearAroundRad(float from, float to);
	
	// ��]�����Ȃ����̉�]�������擾����(���v���:1�A�����v���:-1)
	static int DirNearAroundDeg(float from, float to);
	
	// ���`���
	static double Lerp(double start, double end, double t);

	// �p�x�̐��`���
	static double LerpDeg(double start, double end, double t);

	// �p�x�̐��`���
	static Float3 RotXZPos(Float3 centerPos, Float3 radiusPos, double rad);

	static double Magnitude(Float3 v);
	static double Distance(Float3 v1, Float3 v2);

};

