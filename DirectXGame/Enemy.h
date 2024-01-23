#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"SuitableBullet.h"
#include"Trackingbullet.h"

class Enemy {
public:
	~Enemy();

	void Initialize(Model* head, Model* body1, Model* body2, Model* body3);

	void Update();

	void Draw(ViewProjection& viewProjection);

	//当たり判定
	void OnCollision();

	Vector3 GetWorldPosition();

	//攻撃
	void SecondAttack();
	void ThirdAttack();

	//
	//const std::list<LotEnemy*>& GetLotEnemys() const { return enemyNums_; }

	const WorldTransform& GetWorldTransform() { return worldTransformHead_; }

	// 親となるワールドトランスフォーム
	void SetParent(const WorldTransform* parent);

private:
	//行動フェーズ
	enum class Phase {
		First,//1
		Second,//2
		Third,//3
		Final,//頭
	};

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformBody1_;
	WorldTransform worldTransformBody2_;
	WorldTransform worldTransformBody3_;
	// モデル
	Model* headModel_ = nullptr;
	Model* bodyModel1_ = nullptr;
	Model* bodyModel2_ = nullptr;
	Model* bodyModel3_ = nullptr;

	// デスフラグ
	bool isDead_ = false;

	//フェーズ
	Phase phase_ = Phase::First;
	//Phase phase_ = Phase::Final;
};