﻿#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"SuitableBullet.h"
#include"Trackingbullet.h"
#include"Input.h"

class Enemy {
public:
	~Enemy();

	void Initialize(Model* head, Model* body1, Model* body2, Model* body3/*, Model* modelSuitable*/);

	void Update();

	void Draw(ViewProjection& viewProjection);

	//攻撃
	void SecondAttack();
	void ThirdAttack();

	//追尾
	const std::list<Trackingbullet*>& GetSuitableBullet() const { return trackingbulletNums_; } 
	// 複数
	const std::list<SuitableBullet*>& GetTrackingbullet() const { return suitableBulletNums_; }

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
	//Model* modelSuitable_=nullptr;

	//フェーズ
	Phase phase_;
	//Phase phase_ = Phase::Final;

	// 敵複数
	std ::list<Trackingbullet*> trackingbulletNums_;
	std ::list<SuitableBullet*> suitableBulletNums_;

	//敵回転
	float RotateSpeed;
	//弾の出るタイミング
	float TrackingTiming;
	float SuitableTiming;
	//弾のモデル
	Model* TrackingModel;
	Model* SuitableModel;
	Vector3 suitableposition;
};