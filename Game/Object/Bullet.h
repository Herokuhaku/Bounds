#pragma once
#include <utility>
#include "../common/Vector3.h"

using HitNormal = std::pair<bool, Float3>;

class Bullet
{
public:
	// ���˂���܂ł̎���
	static constexpr float REF_INTERVAL = 0.0f;
	// ���˂����u�Ԃ̃x�N�g���̌W��
	static constexpr float REF_POW = 3.0f;
	Bullet(Float3 pos,Float3 vec,int stage,int player);
	~Bullet();

	void Init(void);
	void Update(float delta);
	void Draw(void);

	// Hit������true�Ɩ@���x�N�g����Ԃ� Hit���Ȃ�������false��{0,0,0}���Ԃ�
	HitNormal HitCheckStage(Float3& end);
	bool isDead(void) { return dead_;};
	Float3 GetPos(void) { return pos_; };
private:
	Float3 pos_;
	// �i��ł����
	Float3 vec_;
	// �����Ă����
	Float3 angle_;
	// �e�̑傫��
	float size_;
	// ���t���[�����˂��ăx�N�g�����o�O��Ȃ��悤�ɊԊu��������
	float time_;

	// ���f���̃n���h�����
	int stagemodel_;
	int playermodel_;
	// true�ɂȂ�Βe��������
	bool dead_;
	int count;
};

