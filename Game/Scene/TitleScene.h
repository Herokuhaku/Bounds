#pragma once
#include "SceneBase.h"
class Stage;
class Player;
class TitleScene : public SceneBase
{
public:
	TitleScene();
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void RealDraw(void)override;

	void DrawDebug(void)override;
private:

	std::unique_ptr<Stage> stage_;

	std::shared_ptr<Player>player_;
};