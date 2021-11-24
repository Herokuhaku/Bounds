#pragma once
#include <DxLib.h>
#include <memory>
#include <list>
#include <vector>
#include "../common/Vector3.h"
#include "Camera.h"
#include "Bullet.h"
#include "../AllControl/Control.h"
#include "Laserbeam.h"
#include "Gravity.h"

class Transform {
public:
	// ���W
	Float3 pos_;
	// �p�x(rad)
	Float3 angles_;
};

// mv1�̏���
enum class ANIM {
	Idle = 0,
	Jump = 1,
	Run = 2,

};

enum class JUMP {
	STAY,
	JUMP,
	FALL
};

class Player
{
public:
	Player();
	Player(int stagemodelid);
	~Player();
	// �A�j���[�V�������x
	static constexpr float SPEED_ANIM = 20.0f;
	// ���X�ɉ�]�����
	static constexpr float SPEED_ROT = 5.0f;
	// ���X�ɉ�]�����(RAD)
	static constexpr float SPEED_ROT_RAD = SPEED_ROT * (DX_PI_F / 180.0f);
	// 
	//static constexpr float FOWARD_VEC = 5.0f;
	// ���ړ��̎��̃`�F�b�N�����
	static constexpr float CHECK_POW = 20.0f;
	// ���ړ����鎞�ɔ��肪�n�ʂɖ��܂�Ȃ��悤�ɍ���������
	static constexpr float CHECK_HEIGHT = 20.0f;
	// �e�̍ő吔
	static constexpr int FIRE_MAX = 30;

	// �e�����Ԋu(�b)
	static constexpr float FIRE_INTERVAL = 1.0f;
	void Init(void);
	void Update(void);
	// �ړ�����
	void Move(CntData data);
	// �e�����AADS����
	void FireFunc(CntData& data, float deltatime, Float3& dxangle);
	// �W�����v
	void Jump(CntData& data);
	void SetBeforeDraw(void);
	void Draw(void);

	Float3 GetPos(void);
	Float3 GetAngles(void);
	// X����]
	Float3 GetRotateX(Float3 pos);
	// Y����]
	Float3 GetRotateY(Float3 pos);
	// Z����]
	Float3 GetRotateZ(Float3 pos);

	// �����蔻��`�F�b�N(�����̓����x�N�g��)�ړ����܂�
	bool HitCheck(Float3 vec);
	// �����蔻��`�F�b�N(����̂�)
	bool Hit(Float3 vec);
	// �����蔻�菈��(LINE)
	bool HitLine(Float3 vec);
	// 臒l�̐ݒ�
	void AskThreshold(Float3 cangle, float rotRad);
	// 臒l���g���ĉ�]����
	void Threshold(float diff, float aroundDir, float radMoveAngleY);

	void ChangeAnimation(ANIM anim);

	std::vector<Float3> GetBulletsPos(void);
private:
	// �e�̃X�s�[�h�W��
	static constexpr float BULLET_SPEED_POW = 20.0f;
	//float time_;
	// �v���C���[���f���̃n���h��ID
	int modelid_;
	// �X�e�[�W���f���̃n���h��ID
	int stagemodelid_;
	// ���W�Ɗp�x
	Transform trans_;
	Float3 eyeoffset_;
	//�n���܂��邩��shared
	std::shared_ptr<Camera> camera_;
	// �����ԍ�
	int playerid_;
	// �����ԍ������߂�
	static int id_;
	// �A�j���[�V�����̑��Đ�����
	float timeTotalAnim_;

	// �A�j���[�V�����p�̍X�V�X�e�b�v
	float stepanim_;

	float anim_;
	// ���̃A�j���[�V����
	ANIM nowanim_;
	// �L�����̃A���O��
	Float3 localangles_;
	// �ړ����̃X�s�[�h
	float movepow_;
	std::list<std::unique_ptr<Bullet>> bullets_;
	Float3 eyepos_;
	//�R���g���[���[
	//std::unique_ptr<Control>controller_;

	double jumptime_;
	bool jumpflag_;
	bool fallflag_;
	
	// ����������
	int firecount_;
	// 1����������ɂ�����x���Ă�悤�ɂȂ�܂ł̊Ԋu
	float firetime_;
	// �\����
	std::unique_ptr<Laserbeam> laser_;

	// �W�����v
	std::unique_ptr<Gravity> gravity_;

	// �J�����A���O���ۑ�
	Float3 cangles_;
	Float3 cfowardvec_;
	// �f�o�b�O�p
	VECTOR line_[2];
	VECTOR fallline_[2];
};