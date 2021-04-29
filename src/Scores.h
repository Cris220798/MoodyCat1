#pragma once

#include "raylib.h"
#include <iostream>

struct Scores {
	std::vector<int> scores;
	std::string file;
	std::string appdataPath;
	std::string moodyCatDirectory;

	void Init();

	void AddScore(int score);

	int GetPlace(int score);

	bool ScoreExists(int score);

	bool FileExists();

	void WriteFile();

	void ReadFile();

};
