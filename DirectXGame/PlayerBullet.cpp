#include "PlayerBullet.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include "Mymath.h"
#include <TextureManager.h>

void PlayerBullet::Initalize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);

	model_ = model;

	// ���[���h�g�����X�t�H�[���̏�����
	// �����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	////�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
}

void PlayerBullet::Update() {
	//���W���ړ�������(1�t���[�����̈ړ��ʂ𑫂�����)
	Move(worldTransform_.translation_.velocity_);

	//���Ԍo�߂Ńf�X
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTransform_.UpdateMatrix();

}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	// ���f���̕`��
	model_->Draw(worldTransform_, viewProjection);
}

void PlayerBullet::OnCollision() { 
	isDead_ = true; 
}

Vector3 PlayerBullet::GetWorldPosition() {
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}


