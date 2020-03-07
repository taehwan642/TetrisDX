#pragma once
#include "Sprite.h"
class Tetromino : public Sprite
{
public:
	Tetromino();
};

class TetrominoMNG : public Singleton<TetrominoMNG>
{
public:
	Tetromino* t;
	void CreateTetromino();
};