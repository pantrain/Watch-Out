#pragma once

#include "PopUp.h"

namespace cocos2d
{
	class MainPopUp
		: public PopUp
	{
	public:
		bool init(Node* parent);
		CREATE_POPUP(MainPopUp);

	};
}