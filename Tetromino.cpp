#include "DXUT.h"
#include "Tetromino.h"

Tetromino::Tetromino()
{
	_position = { 0,0 };
	_scale = { 0.005,0.005 };
	_isUI = false;
	SetTexture(L"sibal.png");
}

void TetrominoMNG::CreateTetromino()
{
	t = new Tetromino();
}
