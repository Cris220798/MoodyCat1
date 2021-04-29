#include "raylib.h"
#include <iostream>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "Scores.h"

void Scores::Init() {
	appdataPath = getenv("appdata");
	moodyCatDirectory = appdataPath + "/MoodyCat1";
	file = moodyCatDirectory + "/scores.txt";
	if (!std::filesystem::is_directory(moodyCatDirectory) || !std::filesystem::exists(moodyCatDirectory)) {
		std::filesystem::create_directory(moodyCatDirectory);
	}
}

void Scores::AddScore(int score) {
	if (!ScoreExists(score)) {
		this->scores.push_back(score);
		if (scores.size() > 1)
			std::sort(this->scores.begin(), this->scores.end(), std::greater<int>());
	}
}

int Scores::GetPlace(int score) {
	int i = 0;
	int size = scores.size();
	bool found = false;
	
	while (i < size && !found) {
		if (score == scores.at(i))
			found = true;
		i++;
	}
	return i;
}

bool Scores::ScoreExists(int score) {
	bool res = false;
	if (!scores.empty()) {
		for (int s : scores) {
			if (s == score)
				res = true;
		}
	}
	return res;
}

bool Scores::FileExists() {
	return std::filesystem::exists(file);
}

void Scores::WriteFile() {
	std::ofstream outFile (file);
	for (int s : scores) {
		outFile << s << std::endl;
	}
	outFile.close();
}

void Scores::ReadFile() {
	if (FileExists()) {
		std::ifstream inFile(file);
		std::string line;
		this->scores.clear();

		while (inFile >> line) {
			this->scores.push_back(std::move(stoi(line)));
		}
		if(this->scores.size() > 1) std::sort(this->scores.begin(), this->scores.end(), std::greater<int>());
	}
}