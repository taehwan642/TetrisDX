#pragma once
#include "Sprite.h"
class Block : public Sprite
{
public:
	Block();
	void SetBPos(Vec2 v);
};

class Tetromino : public Sprite // 얘가 기본 베이스
{
public:
	Tetromino();
	void Rotate();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
};

class TetrominoMNG : public Singleton<TetrominoMNG>
{
public:
	Tetromino* t;
	void CreateTetromino();
};