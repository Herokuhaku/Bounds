#include "Player.h"
#include "Camera.h"
#include "../AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../AllControl/KeyBoardCtl.h"

int Player::id_ = 0;

Player::Player()
{
	Init();
}
Player::Player(int stagemodelid)
{
	stagemodelid_ = stagemodelid;
	Init();
}

Player::~Player()
{
	MV1DeleteModel(modelid_);
}

void Player::Init(void)
{
	jumpflag_ = false;
	fallflag_ = false;
	playerid_ = id_++;
	modelid_ = MV1LoadModel("Model/gun.mv1");
	trans_.pos_ = Float3{0.0f,700.0f,0.0f};
	//trans_.pos_ = Float3();
	camera_ = lpSceneMng.GetCamera();
	eyeoffset_ = Float3(0.0f, 120.0f, 0.0f);
	//eyeoffset_ = Float3(-300,120,0);

	eyepos_ = trans_.pos_ + eyeoffset_;
	camera_->Update(eyepos_);
	movepow_ = 10;

	localangles_ = Float3{ 0.0f,static_cast<float>(AsoUtility::Deg2Rad(180.0)),0.0f };

	// モデルの座標を設定
	MV1SetPosition(modelid_,trans_.pos_.toVECTOR());

	// モデルの角度設定
	Float3 angles = trans_.angles_;
	angles += localangles_;

	MV1SetRotationXYZ(modelid_, angles.toVECTOR());

	// animnumで取れるのはアニメーションの数だから0から数えるため-1
	int animsize = MV1GetAnimNum(modelid_);
	nowanim_ = ANIM::Idle;
	stepanim_ = 0.0f;

	//anim_ = (MV1AttachAnim(modelid_, static_cast<int>(ANIM::Idle)));
	//timeTotalAnim_ = (MV1GetAttachAnimTotalTime(modelid_, anim_));

	jumptime_ = 0.0;

	firecount_ = 0.0f;
	firetime_ = FIRE_INTERVAL;

	laser_ = std::make_unique<Laserbeam>(stagemodelid_, BULLET_SPEED_POW);

	gravity_ = std::make_unique<Gravity>(trans_.pos_,jumpflag_,fallflag_,jumptime_,stagemodelid_);

	lpSceneMng.GetController()->ChangeScenePushed();
}

void Player::Update(void)
{
	float deltatime = lpSceneMng.GetDeltaTime();

	stepanim_ += deltatime * SPEED_ANIM;
	// ジャンプアニメーションは途中で中断しない
	// アニメーションが回り切ったらIdleに戻す
	if (nowanim_ == ANIM::Jump && stepanim_ > timeTotalAnim_) {
		//ChangeAnimation(ANIM::Idle);
	}else if (stepanim_ > timeTotalAnim_) {
		stepanim_ = 0.0f;
	}
	MV1SetAttachAnimTime(modelid_, anim_, stepanim_);

	Float3 dxangle = lpSceneMng.GetCamera()->GetDxlibAngles();
	{
		CntData data = lpSceneMng.GetController()->GetCntData();
		// 移動処理
		Move(data);
		// ジャンプ処理
		Jump(data);
		// 弾を撃つ、ADS処理
		FireFunc(data, deltatime,cfowardvec_);

		if (!data[INPUT_ID::FREE][static_cast<int>(Trg::Now)] && data[INPUT_ID::FREE][static_cast<int>(Trg::Old)]) {
			lpSceneMng.GetCamera()->SetAngles(cangles_);
		}
		else if (!data[INPUT_ID::FREE][static_cast<int>(Trg::Now)]) {
			cangles_ = lpSceneMng.GetCamera()->GetAngles();
			cfowardvec_ = lpSceneMng.GetCamera()->GetDxlibAngles();
		}
	}

	// 落下処理
	if (!HitLine(Float3(0,-15,0)) && !jumpflag_ && !fallflag_) {
		fallflag_ = true;
		jumptime_ = 1.0f;
	}
	// ジャンプ処理
	gravity_->Update(deltatime);

	Float3 angle = trans_.angles_;
	angle += localangles_;

	//MV1SetRotationXYZ(modelid_, VECTOR({ 0.0f,angle.y,angle.z }));
	//MV1SetPosition(modelid_, trans_.pos_.toVECTOR());

	eyepos_ = trans_.pos_ + eyeoffset_;

	// カメラの更新 
	std::pair<bool, double>flag = camera_->Update(eyepos_);

	if (flag.first) {
		// カメラの向きにキャラの向きを合わせる
		AskThreshold(camera_->GetAngles(), flag.second);
	}
	for (auto& bullet : bullets_) {
		bullet->Update(deltatime);
	}
	bullets_.remove_if([&](std::unique_ptr<Bullet>& bullet) {return bullet->isDead();});
	if (CheckHitKey(KEY_INPUT_DELETE)) {
		bullets_.clear();
	}
}

void Player::FireFunc(CntData& data, float deltatime, Float3& dxangle)
{
	if (firetime_ >= FIRE_INTERVAL && data[INPUT_ID::FIRE][static_cast<int>(Trg::Now)] && !data[INPUT_ID::FIRE][static_cast<int>(Trg::Old)]) {
		firetime_ -= deltatime;
		firecount_++;
		Float3 vec = dxangle * BULLET_SPEED_POW;

		//eyepos_ += vec;
		bullets_.emplace_back(std::make_unique<Bullet>(eyepos_, vec, stagemodelid_, modelid_));
	}
	// 弾の撃つインターバルを見る
	if (firetime_ < 0) {
		firetime_ = FIRE_INTERVAL;
	}
	// 弾を撃っていたら規定の値まで数え始める(撃つ間隔調整)
	if (firetime_ != FIRE_INTERVAL) {
		firetime_ -= deltatime;
	}

	if (data[INPUT_ID::ADS][static_cast<int>(Trg::Now)])
	{
		Float3 vec = dxangle * BULLET_SPEED_POW;
		laser_->Update(eyepos_, vec);
		if (!data[INPUT_ID::FREE][static_cast<int>(Trg::Now)]) {
			SetupCamera_Perspective(AsoUtility::Deg2Rad(30));
		}
	}
}

void Player::Jump(CntData& data)
{
	if (data[INPUT_ID::JUMP][static_cast<int>(Trg::Now)] && !jumpflag_) {
		jumpflag_ = true;
		//ChangeAnimation(ANIM::Jump);
	}
}

void Player::SetBeforeDraw(void)
{
}

void Player::Draw(void)
{
	if (playerid_ != 0)
	{
		//MV1DrawModel(modelid_);
	}
	//DrawLine3D(line_[0],line_[1], 0x00ffff);
	//DrawSphere3D(line_[0], 5, 4, 0xffffff, 0xffffff, true);
	
	for (auto& bullet : bullets_) {
		bullet->Draw();
	}
	laser_->Draw();
}

Float3 Player::GetPos(void)
{
	return trans_.pos_;
}

Float3 Player::GetAngles(void)
{
	return trans_.angles_;
}

Float3 Player::GetRotateX(Float3 pos)
{
	// 原点からの距離に移動
	Float3 p = pos;
	Float3 ang;
	ang.x = lpSceneMng.GetCameraAngle().x;
	float x, y, z;
	x = p.x;
	y = (cos(ang.x) * p.y + -sin(ang.x) * p.z);
	z = (sin(ang.x) * p.y + cos(ang.x) * p.z);

	return Float3(x,y,z);
}

Float3 Player::GetRotateY(Float3 pos)
{
	// 原点からの距離に移動
	Float3 p = pos;
	Float3 ang;
	ang.y = lpSceneMng.GetCameraAngle().y;

	float x, y, z;
	x = (cos(ang.y) * p.x + -sin(ang.y) * p.z);
	y = p.y;
	z = (sin(ang.y) * p.x + cos(ang.y) * p.z);

	return Float3(x, y, z);
}

Float3 Player::GetRotateZ(Float3 pos)
{
	// 原点からの距離に移動
	Float3 p = pos;
	Float3 ang;
	ang.z = lpSceneMng.GetCameraAngle().z;
	float x, y, z;
	x = cos(ang.z) * p.x + -sin(ang.z) * p.y;
	y = sin(ang.z)* p.x + cos(ang.z) * p.y;
	z = p.z;

	return Float3(x, y, z);
}

bool Player::HitCheck(Float3 vec)
{	
	auto CenterPos = trans_.pos_ + vec/2;
	// 地面に埋まらないように
	CenterPos.y += CHECK_POW*2;
	//DrawSphere3D(CenterPos, CHECK_POW, 5, 0x00ffff, 0x00ffff, true);
	// 当たり判定チェック
	for (int i = 0; i < MV1GetFrameNum(stagemodelid_); i++) {
		//auto HitPoly = MV1CollCheck_Line(stagemodelid_,i, StartPos.toVECTOR(), EndPos);
		auto HitPoly = MV1CollCheck_Sphere(stagemodelid_, i,CenterPos.toVECTOR(),CHECK_POW);
		if (HitPoly.Dim != nullptr)
		{
			MV1CollResultPolyDimTerminate(HitPoly);
			return true;
		}
		MV1CollResultPolyDimTerminate(HitPoly);
	}
	// 当たらなかったら移動
	trans_.pos_ += vec;
	return false;
}

void Player::AskThreshold(Float3 cangle, float rotRad)
{
	// プレイヤーのアングルY(rad)
	float radUnitAngleY = AsoUtility::RadIn2PI(trans_.angles_.y);

	// プレイヤーが向こうとしているアングルY
	float radMoveAngleY = cangle.y + rotRad;
	// radに変換
	radMoveAngleY = AsoUtility::RadIn2PI(radMoveAngleY);
	
	// 時計回りに回るか反時計回りかを求める
	float aroundDir = 0.0f;
	// クルクルする
	// → DirNearAroundRad関数の要件を満たしてない(angles_を0~360に収めると治る)
	aroundDir = AsoUtility::DirNearAroundRad(radUnitAngleY, radMoveAngleY);

	// ブルブルする
	// → ゲーム制御においてよくある問題　しきい値、みなし値を設ける
	float diff = abs(radMoveAngleY - radUnitAngleY);

	Threshold(diff,aroundDir,radMoveAngleY);
}

void Player::Threshold(float diff,float aroundDir,float radMoveAngleY)
{
	if (diff > SPEED_ROT_RAD + 0.01) {
		// 回転処理
		trans_.angles_.y += SPEED_ROT_RAD * aroundDir;
		return;
	}
	// 閾値以下だったら回転処理をしない
	trans_.angles_.y = radMoveAngleY;
}

void Player::ChangeAnimation(ANIM anim)
{
	nowanim_ = anim;
	MV1DetachAnim(modelid_, anim_);
	anim_ = MV1AttachAnim(modelid_, static_cast<int>(anim));
	timeTotalAnim_ = (MV1GetAttachAnimTotalTime(modelid_, anim_));
	stepanim_ = 0.0f;
	MV1SetAttachAnimTime(modelid_, anim_, stepanim_);
}

bool Player::Hit(Float3 vec)
{	
	// 当たり判定ベクトルの開始地点
	auto StartPos = trans_.pos_;
	// 当たり判定ベクトルの終了地点
	auto EndPos = trans_.pos_ + vec;

	auto CenterPos = trans_.pos_ + (vec / 2);
	// 当たり判定チェック
	//auto HitPoly = MV1CollCheck_Line(stagemodelid_,4, StartPos.toVECTOR(), EndPos.toVECTOR());
	//fallline_[0] = StartPos.toVECTOR();
	//fallline_[1] = EndPos.toVECTOR();
	DrawSphere3D(CenterPos.toVECTOR(), movepow_, movepow_, 0xffff00, 0xffff00, true);
	// 当たり判定チェック
	for (int i = 0; i < MV1GetFrameNum(stagemodelid_); i++) {
		//auto HitPoly = MV1CollCheck_Line(stagemodelid_, i, StartPos.toVECTOR(), EndPos.toVECTOR());
		auto HitPoly = MV1CollCheck_Sphere(stagemodelid_, i,CenterPos.toVECTOR(),movepow_);
		if (HitPoly.Dim != nullptr)
		{
			MV1CollResultPolyDimTerminate(HitPoly);
			return true;
		}
		MV1CollResultPolyDimTerminate(HitPoly);
	}
	return false;

	//if (HitPoly.HitFlag == 1)
	//{
	//	return true;
	//}
	//return false;
}

bool Player::HitLine(Float3 vec)
{	
	// 当たり判定チェック
	for (int i = 0; i < MV1GetFrameNum(stagemodelid_); i++) {
		//auto HitPoly = MV1CollCheck_Line(stagemodelid_, i, StartPos.toVECTOR(), EndPos.toVECTOR());
		auto HitPoly = MV1CollCheck_Line(stagemodelid_, i,(trans_.pos_).toVECTOR(),(trans_.pos_ + vec).toVECTOR());
		if (HitPoly.HitFlag)
		{
			return true;
		}
	}
	return false;
}

void Player::Move(CntData data)
{

	// 操作キー判定
	bool isHitMove = false;
	// 回転したい角度
	float rotRad = 0.0f;

	// カメラ情報
	auto cam = lpSceneMng.GetCamera();
	//auto cangle = cam->GetAngles();
	auto cangle = cangles_;
	int movepow = movepow_;
	if (data[INPUT_ID::RUN][static_cast<int>(Trg::Now)]) {
		movepow_ = movepow * 2;
	}
	Float3 vec;
	if (data[INPUT_ID::UP][static_cast<int>(Trg::Now)]) {
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(0.0f);
		// カメラが見てる方向に移動
		vec.x += sinf(cangle.y + rotRad) * movepow_;
		vec.z += cosf(cangle.y + rotRad) * movepow_;
	}
	if (data[INPUT_ID::DOWN][static_cast<int>(Trg::Now)]) {
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(180.0f);
		// カメラが見てる方向に移動
		vec.x += sinf(cangle.y + rotRad) * movepow_;
		vec.z += cosf(cangle.y + rotRad) * movepow_;
	}
	// 横移動
	if (data[INPUT_ID::LEFT][static_cast<int>(Trg::Now)]) {
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(-90.0f);
		// カメラが見てる方向に移動
		vec.x += sinf(cangle.y + rotRad) * movepow_;
		vec.z += cosf(cangle.y + rotRad) * movepow_;
	}
	if (data[INPUT_ID::RIGHT][static_cast<int>(Trg::Now)]) {
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(90.0f);
		// カメラが見てる方向に移動
		vec.x += sinf(cangle.y + rotRad) * movepow_;
		vec.z += cosf(cangle.y + rotRad) * movepow_;
	}
	if (isHitMove) {
		if (!HitCheck(vec) && nowanim_ != ANIM::Run && nowanim_ != ANIM::Jump) {
			//ChangeAnimation(ANIM::Run);
		}
	}
	else if (nowanim_ != ANIM::Idle && nowanim_ != ANIM::Jump) {
		//ChangeAnimation(ANIM::Idle);
	}	
	movepow_ = movepow;
}

std::vector<Float3> Player::GetBulletsPos(void)
{
	std::vector<Float3> posvec;
	posvec.reserve(bullets_.size());
	for (auto& bullet : bullets_) {
		posvec.emplace_back(bullet->GetPos());
	}
	return posvec;
}