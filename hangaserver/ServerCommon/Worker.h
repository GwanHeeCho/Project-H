#pragma once
#include <iostream>
// https://neive.tistory.com/303
// https://neive.tistory.com/22?category=403086

class Command
{
	virtual void execute();
};

class Attack : public Command
{
	virtual void execute()
	{
		std::cout << "Attack" << std::endl;
	}
};