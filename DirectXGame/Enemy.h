#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"

// 前方宣言
class Player;

class Enemy {
public:
	~Enemy();

	void Initialize(Model* head, Model* body1, Model* body2, Model* body3);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void Fire();

	const WorldTransform& GetWorldTransform() { return worldTransformHead_; }

	// 親となるワールドトランスフォーム
	void SetParent(const WorldTransform* parent);

	// 当たり判定
	void OnCollision();

	Vector3 GetWorldPosition();

	// 発射間隔
	static const int kFireInterval = 60;

	void SetPlayer(Player* player) { player_ = player; }

	// 弾リストを取得
	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

private:
	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;
	
	// ワールド変換データ
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformBody1_;
	WorldTransform worldTransformBody2_;
	WorldTransform worldTransformBody3_;
	// モデル
	Model* headModel_ = nullptr;
	Model* bodyModel1_ = nullptr;
	Model* bodyModel2_ = nullptr;
	Model* bodyModel3_ = nullptr;
	Model* bulletModel_ = nullptr;

	// 敵の弾
	std::list<EnemyBullet*> bullets_;

	// デスフラグ
	bool isDead_ = false;

	// 発射タイマー
	int32_t fireTimer_ = 0;

	// 自キャラ
	Player* player_;
};