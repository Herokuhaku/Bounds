#pragma once
#include "../common/Vector2.h"
#include "../Scene/SceneBase.h"
class StageSelect
{
public:
	StageSelect(Int2 pos,Int2 size,StageID stageno);
	~StageSelect();
	bool Update(void);
	void Draw(void);
	StageID GetNo(void);
private:
	void Init();
	int screen_;
	Int2 pos_;
	Int2 windowSize_;
	StageID stageno_;
	bool selectflag_;
};

