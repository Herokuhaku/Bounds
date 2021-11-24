#pragma once
#include <list>

#include "SceneBase.h"

class Stage;
class Player;
class StageSelect;
class StageSelectScene : public SceneBase
{
public:
	StageSelectScene();
	~StageSelectScene();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void RealDraw(void)override;

	void DrawDebug(void)override;
private:
	std::shared_ptr<Player>player_;

	std::list<StageSelect*> stageselect_;
};