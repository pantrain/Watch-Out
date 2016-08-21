﻿#pragma once

#include "cocos2d.h"
#include "Friendly.h"

namespace cocos2d
{
	enum class Difficulty
	{
		Easy,
		Normal,
		Hard,
	};

	class GameManager
	{
	private:
		Country			_country[3];
		Difficulty		_difficulty;
		int				_lifeCount = 3;
		int				_catchCount = 0;
		int				_score = 0;
		float			_timeScale = 1.0f;
		std::vector<std::string> _enemyImages;

	public:
		static GameManager* getInstance();
		static void destroy();

		void pushEnemyImage(const std::string& filename);
		size_t getEnemyImageCount() { return _enemyImages.size(); }
		const std::string& getEnemyImage(int index) { return _enemyImages[index]; }

		void setDifficulty(const Difficulty difficulty);
		Difficulty getDifficulty() { return _difficulty; }

		void setSelectCountrys(const int index, Country country);
		Country getSelectCountrys(const int index) { return _country[index]; }

		void setTimeScale(float timeScale);
		float getTimeScale() { return _timeScale; }

		void setLifeCount(int count);
		int getLifeCount() { return _lifeCount; }

		void setCatchCount(int count);
		int getCatchCount() { return _catchCount; }

		void setScoreZero();
		void upScore();
		int getScore() { return _score; }
		int getBestScore();

		std::function<void()> endGame = [=]() {};
	};
}