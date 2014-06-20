#pragma once 
#include <iostream>
#include <string>
#include "Vector2.h"

#define DEFAULT_POS_X 100
#define DEFAULT_POS_Y 100
#define DEFAULT_SIZE_W 1000
#define DEFAULT_SIZE_H 600
#define TIME_TO_NEXT_LEVEL 40000
#define INSTANTIATE_TIME 6000
#define INCREASE_LEVEL_DIFFICULTY 1.05
#define CHANCE_FOR_A_BONUS 7



const std::string DEFAULT_WIN_NAME = "Brave-Pirate";
const std::string windowSettings = "WindowSettings.txt";
const std::string resourcesPath  = "Resources/";
const std::string texturesPath = "images/";
const std::string fontName = "arial.ttf";
const std::string fishesFile = "Fishes.txt";
const std::string barrelFile = "burrels.txt";
const std::string bonusFile = "bonus.txt";

enum Fishs_Gifts_Types
{
	energyFish = 0,
	rodSpeedBonus = 1,
	cannonSpeedBonus = 2,
	healthShipBonus = 3
};


struct SampleBonus
{
	std::string textureName;
	float speed, depth, value;
	Vector2 size;
	Fishs_Gifts_Types type;

	friend std::ostream & operator<< (std::ostream &w, const SampleBonus &b)
	{
		return w<<b.textureName<<" "<<b.speed<<" "<<b.value<<" "<<b.depth<<" "<<b.size<<" "<<(int)b.type<<std::endl; 
	}

	friend std::istream & operator>> (std::istream &w, SampleBonus &b)
	{
		int type;
		return w>>b.textureName>>b.speed>>b.value>>b.depth>>b.size>>type;
		b.type = (Fishs_Gifts_Types)type;
		return w;
	}
};

