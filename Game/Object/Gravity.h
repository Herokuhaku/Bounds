#pragma once
#include "../common/Vector3.h"
class Gravity
{
public:
	Gravity(Float3& pos, bool& jump,bool& fall,double& time,int stagemodel);
	void Init(void);

	void Update(float delta);
	bool CheckStage(Float3& vec,Float3& pos);
private:
	Float3& pos_;

	// �d��
	float gravity_;
	// �W�����v����
	bool& jump_;
	// �����Ă锻��
	bool& fall_;

	// �d�͂�K�p���邩�ǂ���
	bool gravitybool_;
	// ���݂̃W�����v��
	float jumppow_;
	// �ŏ��̉����x
	float v1;
	// �W�����v���Ăǂ̂��炢�̎��Ԃ�������
	double& time_;

	// �����蔻��p�X�e�[�W���f��
	int stagemodel_;
};

