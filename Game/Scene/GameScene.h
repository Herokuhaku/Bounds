#pragma once
#include "SceneBase.h"
#include "../Object/Player.h"
using NameAndTarget = std::pair<std::string, std::list<Float3>>;

class Stage;

class GameScene : public SceneBase
{
public:
	GameScene(StageID stageid);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void RealDraw(void)override;

	void DrawDebug(void)override;
private:
	void Stage2(void);
	std::unique_ptr<Stage> stage_;
	std::shared_ptr<Player>player_;
	std::map<StageID, NameAndTarget> stageinfo_;

};
