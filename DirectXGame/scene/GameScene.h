#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "FollowCamera.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DebugCamera.h>
#include <memory>
#include "Skydome.h"
#include "Ground.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void CheckAllCollision();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// 3Dモデルデータ
	std::unique_ptr<Model> model_;

	
	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	// デバッグカメラ
	std::unique_ptr<DebugCamera> debugCamera_;
	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
	// 追従カメラ
	std::unique_ptr<FollowCamera> followCamera_;

	// 自キャラ
	std::unique_ptr<Player> player_;
	// 3Dモデルデータ
	std::unique_ptr<Model> modelPlayerHead_;
	std::unique_ptr<Model> modelPlayerBody1_;
	std::unique_ptr<Model> modelPlayerBody2_;
	std::unique_ptr<Model> modelPlayerBody3_;

	// 敵キャラ
	std::unique_ptr<Enemy> enemy_;
	// 3Dモデル
	std::unique_ptr<Model> modelEnemyHead_;
	std::unique_ptr<Model> modelEnemyBody1_;
	std::unique_ptr<Model> modelEnemyBody2_;
	std::unique_ptr<Model> modelEnemyBody3_;

	//敵の弾
	//複数
	std::unique_ptr<Enemy> suitableBullet_;
	std::unique_ptr<Model> modelSuitableBullet_;

	Skydome* skydome_ = nullptr;

	Model* modelSkydome_ = nullptr;

	Ground* ground_ = nullptr;

	Model* modelGround_ = nullptr;
	
	//ライフ
	uint32_t LifeHandle_;

	int EnemyLife = 5;

	private:
	//シーン切り替え
	enum Scene {
		TITLE,
		OPERATION,
		GAME,
		CLEAR
	};

	Scene scene = TITLE;
	
	/*Sprite* fadeSprite_ = nullptr;
	　Vector4 fadeColor_ = {1.0f, 1.0f, 1.0f, 1.0f};*/

	//テクスチャハンドル
	uint32_t FadeFake_ = 0;
	uint32_t TitleTexture_ = 0;
	uint32_t OperationTexture_ = 0;
	uint32_t ClearTexture_ = 0;

	Sprite* fadeTitleSprite = nullptr;
	Vector4 fadeTitleColor_ = {1.0f, 1.0f, 1.0f, 0.0f};

	Sprite* fadeOperationSprite_ = nullptr;
	Vector4 fadeOperationColor_ = {1.0f, 1.0f, 1.0f, 0.0f};

	//シーン画面のスプライト
	std::unique_ptr<Sprite> FadeFakeSprite = nullptr;
	std::unique_ptr<Sprite> TitleSprite_ = nullptr;
	//std::unique_ptr<Sprite> OperationSprite_ = nullptr;
	std::unique_ptr<Sprite> ClearSprite_ = nullptr;

	//ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;
	XINPUT_STATE prevjoyState;

	std::unique_ptr<Model> modelPlayerBullet_;

	private:
	//サウンドデータハンドル
	uint32_t GameSound_ = 0;
	


	//音声再生ハンドル
	uint32_t Gamevoice_ = 0;
	

	uint32_t voiceHandle_ = 0;


	
	// 速度
	Vector3 velocity_;

	//フェード
	/*Sprite* fadeSprite_ = nullptr;
	Vector4 fadeColor_ = {1.0f, 1.0f, 1.0f, 0.0f};*/

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};