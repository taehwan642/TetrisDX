#include "DXUT.h"
#include "Tetromino.h"

Block::Block()
{
	SetTexture(L"Block.png");
	_color = { 0,0,0,0 };
}

void Block::SetBPos(Vec2 v)
{
	_position = v * 50;
}

Tetromino::Tetromino()
{
	
}

void Tetromino::Rotate()
{
}

void Tetromino::MoveDown()
{
}

void Tetromino::MoveLeft()
{
}

void Tetromino::MoveRight()
{
}

void TetrominoMNG::CreateTetromino()
{
	t = new Tetromino();
}

