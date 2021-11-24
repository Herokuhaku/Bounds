#pragma once
#include <DxLib.h>
#include <memory>
#include <vector>
#include <chrono>
#include "Object/Player.h"
#include "common/Vector3.h"
#include "Object/TargetBall.h"
#include "Time.h"

class Stage
{
public:
	Stage(std::string stagename, std::list<Float3> targetlist);
	//Stage(std::shared_ptr<Player> player);
	~Stage();
	void Init(std::string stagename,std::list<Float3> targetlist);
	bool Update(void);
	void TimeCreate();
	void Draw(void);
	void RealDraw(void);
	void Release(void);
	void AddTargetBall(Float3 pos);
	void DeleteCheckTargetBall(void);
	// �^�[�Q�b�g�̌��ݐ�
	int GetTargetNum(void);
	// �^�[�Q�b�g�̔j�󂵂���
	int GetDestroyTargetCount(void);
	// �����^�[�Q�b�g��
	int GetTargetCount(void);
	// �o�ߎ��Ԃ̎擾
	Time GetElapsedTime(void);
private:
	//Player* pl_;
	std::shared_ptr<Player> player_;

	// ���f���̃n���h��ID
	int modelid_;
	// 
	Float3 pos_;

	std::vector<std::unique_ptr<TargetBall>> targetvector_;
	std::vector<Float3> targetball_;
	int targetcount_;
	int destroytargetcount_;

	// �o�ߎ���
	std::chrono::system_clock::time_point  start_, end_;
	Time time_;
};

