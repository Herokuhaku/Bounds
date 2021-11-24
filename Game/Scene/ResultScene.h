#pragma once
#include "SceneBase.h"
#include "../common/Vector2.h"
#include "../Time.h"

class Stage;
class Player;
class Box {
public:
	Float2 pos;
	Float2 size;
	bool flag = false;
};
class ResultScene : public SceneBase
{
public:
	ResultScene();
	ResultScene(Time cleartime,StageID stageid);
	~ResultScene();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void RealDraw(void)override;

	void DrawDebug(void)override;

	bool WriteClearTime();
private:

	std::unique_ptr<Stage> stage_;

	std::shared_ptr<Player>player_;

	Time cleartime_;
	Time besttime_;
	float drawrecordtime_;
	bool newrecord_;
	Box box_;

	//screenÇÃÉTÉCÉY
	Float2 scr_;
};