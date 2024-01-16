#pragma once
#include "Model.h"
#include "WorldTransform.h"


class PlayerBullet {
public: 
	void Initalize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);



	void OnCollision();

	// ����<frm>
	static const int32_t kLifeTime = 60 * 5;

	bool IsDead() const { return isDead_; }

	Vector3 GetWorldPosition();

private:
	//���[���h���W�f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//���x
	Vector3 velocity_;
	// �f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	// �f�X�t���O
	bool isDead_ = false;

};
