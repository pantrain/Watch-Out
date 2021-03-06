﻿#include "Friendly.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

Friendly::Friendly()
{	}

Friendly::~Friendly()
{	}

Friendly* Friendly::create(Country county)
{
	Friendly* result = new (std::nothrow) Friendly();
	if (result != nullptr && result->init(county) && result->initWithFile("TouchArea.png"))
	{
		result->autorelease();
		return result;
	}
	CC_SAFE_DELETE(result);

	return nullptr;
}

bool Friendly::init(Country country)
{
	_country = country;
	_move = false;
	_die = false;
	this->setContentSize(Size(95, 155));
	countryImage(country);

	return true;
}

void Friendly::countryImage(Country country)
{
	switch (country)
	{
	case Country::Korea:
		_object = SkeletonObject::create("friendly/char-kr-pack.plist", "friendly/char-kr.csb");
		break;

	case Country::China:
		_object = SkeletonObject::create("friendly/char-cn-pack.plist", "friendly/char-cn.csb");
		break;

	case Country::Japan:
		_object = SkeletonObject::create("friendly/char-jp-pack.plist", "friendly/char-jp.csb");
		break;

	case Country::Peru:
		_object = SkeletonObject::create("friendly/char-pu-pack.plist", "friendly/char-pu.csb");
		break;

	case Country::Philippines:
		_object = SkeletonObject::create("friendly/char-pp-pack.plist", "friendly/char-pp.csb");
		break;

	case Country::Vietnam:
		_object = SkeletonObject::create("friendly/char-vt-pack.plist", "friendly/char-vt.csb");
		break;
	}

	Size size = this->getContentSize();
	_object->getRoot()->setPosition(size.width / 2, size.height / 2 - 20);
	_object->playAnimation("normal", true);
	this->addChild(_object);
}

void Friendly::playDieAnimation()
{
	_object->playAnimation("deathToRight");
	_object->runAction(FadeOut::create(1.0f));
}

void Friendly::setBackPosition(const Vec2& position)
{
	_backPosition = position;
}

void Friendly::setTouchID(const int id)
{
	_touchID = id;
}

void Friendly::setMove(const bool move)
{
	if (_die)
	{
		_move = false;
		return;
	}

	_move = move;
	GameManager::getInstance()->_playerCatche[_friendlyID] = _move;
}

void Friendly::setFriendlyID(const int id)
{
	_friendlyID = id;
}

void Friendly::die(bool left)
{
	if (_die)
	{
		return;
	}

	_particle = ParticleSystemQuad::create("effect/boom.plist");
	_particle->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
	_particle->setScale(0.5f);
	this->addChild(_particle);

	SimpleAudioEngine::getInstance()->playEffect("sound/carCrash.mp3");
	switch (GameManager::getInstance()->getSelectCountrys(_friendlyID))
	{
	case Korea:
	case China:
	case Peru:
		SimpleAudioEngine::getInstance()->playEffect("sound/menDie.mp3");
		break;
	case Japan:
	case Philippines:
	case Vietnam:
		SimpleAudioEngine::getInstance()->playEffect("sound/womenDie.mp3");
		break;
	}

	if (left)
	{
		_alpha = 255.0f;
		schedule(schedule_selector(Friendly::fadeOut));
		_object->playAnimation("deathToRight");
	}
	else
	{
		_alpha = 255.0f;
		schedule(schedule_selector(Friendly::fadeOut));
		_object->playAnimation("deathToLeft");
	}
	_die = true;

	GameManager::getInstance()->_playerLife[_friendlyID] = false;
	bool gameEnd = false;
	for (int i = 0; i < 3; ++i)
	{
		if (GameManager::getInstance()->_playerLife[i])
		{
			gameEnd = true;
		}
	}

	if (!gameEnd)
	{
		GameManager::getInstance()->endGame();
	}
}

void Friendly::setInLine(const bool inLine)
{
	_inLine = inLine;
}

void Friendly::fadeOut(float dt)
{
	if (_alpha <= 0.0f)
	{
		unschedule(schedule_selector(Friendly::fadeOut));
		this->setPosition(9999, 9999);
		_particle->setVisible(false);
		this->setVisible(false);
	}

	std::vector<Node*> bones = _object->getBones();
	_alpha = clampf(_alpha - 250.0f * dt, 0.0f, 255.0f);
	for (int i = 0; i < bones.size(); ++i)
	{
		bones[i]->setOpacity(_alpha);
	}
}