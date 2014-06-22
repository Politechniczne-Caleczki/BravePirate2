#include "GameError.h"


GameError::GameError(const std::string communique):communique(communique)
{
}

GameError::GameError(const std::string communique, const std::string sdl_error):communique(communique), sdl_error(sdl_error)
{
}

const char* GameError::what()const throw()
{
	return communique.c_str();
}

GameError::~GameError(void)
{
}

void GameError::generateErrorLog(const std::string filename)
{
	std::ofstream file(filename);
	if(file.is_open())
	{
		while(!file.eof());
		file<<communique;
	}
	else throw GameError("Could not open file :"+filename);
}