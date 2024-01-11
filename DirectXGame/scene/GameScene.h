#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
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

	Skydome* skydome_ = nullptr;

	Model* modelSkydome_ = nullptr;

	Ground* ground_ = nullptr;

	Model* modelGround_ = nullptr;


	private:
	//シーン切り替え
	enum Scene {
		TITLE,
		OPERATION,
		GAME,
		CLEAR
	};

	Scene scene = TITLE;

	//テクスチャハンドル
	uint32_t TitleTexture_ = 0;
	uint32_t OperationTexture_ = 0;
	uint32_t ClearTexture_ = 0;

	//シーン画面のスプライト
	std::unique_ptr<Sprite> TitleSprite_ = nullptr;
	std::unique_ptr<Sprite> OperationSprite_ = nullptr;
	std::unique_ptr<Sprite> ClearSprite_ = nullptr;

	//ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;
	XINPUT_STATE prevjoyState;


	private:
	//サウンドデータハンドル
	uint32_t TitleSound_ = 0;
	uint32_t OperationSound_ = 0;
	//uint32_t ClearSound_ = 0;


	//音声再生ハンドル
	uint32_t Titlevoice_ = 0;
	uint32_t Operationvoice_ = 0;


	/*std::unique_ptr<Audio> TitleAudio_ = nullptr;
	std::unique_ptr<Audio> OperationSound_ = nullptr;
	std::unique_ptr<Audio> ClearSound_ = nullptr;*/

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};