#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"SuitableBullet.h"
#include"Input.h"
#include "EnemyBullet.h"

// 前方宣言
class Player;

class Enemy {
public:
	~Enemy();

	void Initialize(Model* head, Model* body1, Model* body2, Model* body3/*, Model* modelSuitable*/);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void Fire();

	const WorldTransform& GetWorldTransform() { return worldTransformHead_; }

	// 当たり判定
	void OnCollision();

	Vector3 GetWorldPosition();

	float GetworldRotY();

	//攻撃
	void SecondAttack();

	// 複数
	const std::list<SuitableBullet*>& GetSuitableBullet() const { return suitableBulletNums_; }
	// 発射間隔
	static const int kFireInterval = 60;

	void SetPlayer(Player* player) { player_ = player; }

	// 親となるワールドトランスフォーム
	void SetParent(const WorldTransform* parent);

	// 弾の出るタイミング
	static const int SuitableInterval = 25;

private:
	//行動フェーズ
	enum class Phase {
		First,//1
		Second,//2
		Third,//3
		Final,//頭
	};

	Input* input_ = nullptr;

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;
	
	// ワールド変換データ
	WorldTransform worldTransform_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformBody1_;
	WorldTransform worldTransformBody2_;
	WorldTransform worldTransformBody3_;
	// 弾ワールド変換データ
	WorldTransform worldTransformSuitable_;
	// モデル
	Model* headModel_ = nullptr;
	Model* bodyModel1_ = nullptr;
	Model* bodyModel2_ = nullptr;
	Model* bodyModel3_ = nullptr;
	Model* bulletModel_ = nullptr;

	// 敵の弾
	std::list<EnemyBullet*> bullets_;
	Model* suitableModel_ = nullptr;

	// デスフラグ
	bool isDead_ = false;

	//フェーズ
	Phase phase_;
	//Phase phase_ = Phase::Final;

	// 敵複数
	std ::list<SuitableBullet*> suitableBulletNums_;

	//敵回転
	float RotateSpeed;
	//弾の出るタイミング
	int32_t SuitableTiming;
	//弾のモデル
	Model* SuitableModel;
	Vector3 suitableposition;

	//SuitableBullet suitableBullet_;
	// 発射タイマー
	int32_t fireTimer_ = 0;

	// 自キャラ
	Player* player_;
};