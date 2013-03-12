#pragma once
class GameSettings
{
public:
	GameSettings(void);
	~GameSettings(void);

	static bool vsAI;

	static int MAP_CELL_SIZE;
	static int const MAP_WIDTH_MAX = 25; // 800 / 32
	static const int MAP_HEIGHT_MAX = 18; // 600 / 32	
};

