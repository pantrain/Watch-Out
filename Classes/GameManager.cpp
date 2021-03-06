﻿#include "GameManager.h"

using namespace cocos2d;

static GameManager* _instance = nullptr;

GameManager* GameManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new GameManager();
	}
	return _instance;
}

void GameManager::destroy()
{
	if (_instance != nullptr)
	{
		delete _instance;
		_instance = nullptr;
	}
}

void GameManager::pushEnemyImage(const std::string& filename)
{
	_enemyImages.push_back(filename);
}

void GameManager::setDifficulty(const Difficulty difficulty)
{
	_difficulty = difficulty;
}

void GameManager::setSelectCountrys(const int index, Country country)
{
	std::stringstream ss;
	ss << "Friendly_" << index;

	UserDefault::getInstance()->setIntegerForKey(ss.str().c_str(), country);
}

Country GameManager::getSelectCountrys(const int index)
{
	std::stringstream ss;
	ss << "Friendly_" << index;

	return (Country)UserDefault::getInstance()->getIntegerForKey(ss.str().c_str());
}

void GameManager::setTimeScale(float timeScale)
{
	_timeScale = timeScale;
}

void GameManager::setScoreZero()
{
	_score = 0;
}

void GameManager::upScore()
{
	for (int i = 0; i < 3; ++i)
	{
		_score += (!_playerCatche[i] && _playerLife[i]) ? 1 : 0;
	}
}

int GameManager::getBestScore()
{
	if (UserDefault::getInstance()->getIntegerForKey("BestScore") < _score)
	{
		UserDefault::getInstance()->setIntegerForKey("BestScore", _score);
	}
	return UserDefault::getInstance()->getIntegerForKey("BestScore");
}

void GameManager::addMoney(int money)
{
	int myMoney = UserDefault::getInstance()->getIntegerForKey("Money");
	UserDefault::getInstance()->setIntegerForKey("Money", myMoney + money);
}

void GameManager::minusMoney(int money)
{
	int myMoney = UserDefault::getInstance()->getIntegerForKey("Money");
	UserDefault::getInstance()->setIntegerForKey("Money", myMoney - money);
}