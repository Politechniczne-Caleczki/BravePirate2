#ifndef ConstantAndDefinitions_h
#define ConstantAndDefinitions_h
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
#define INCREASE_LEVEL_DIFFICULTY 1.05f
#define CHANCE_FOR_A_BONUS 40

static const std::string DEFAULT_WIN_NAME = "Brave-Pirate";
static const std::string windowSettings = "WindowSettings.txt";
static const std::string resourcesPath = "Resources/";
static const std::string texturesPath = "images/";
static const std::string fontName = "arial.ttf";
static const std::string fishesFile = "Fishes.txt";
static const std::string barrelFile = "Obstacles.txt";
static const std::string bonusFile = "Bonus.txt";
static const std::string iconFile = "icon.bmp";
static const std::string errorFile = "ErrorLog.txt";
static const std::string saveFile = "SaveFile.admi";
static const std::string cannonBallTextures = "cannonball.png";

const Vector2 gameOverSize(400,400);
const Vector2 cannonBallSize(10,10);
const float cannonBallSpeed = 0.4f;

enum Fishs_Gifts_Types
{
	energyFish = 0,
	rodSpeedBonus = 1,
	cannonSpeedBonus = 2,
	healthShipBonus = 3,
	cannonPowerBonus = 4,
	scoreBonus = 5
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
		w>>b.textureName>>b.speed>>b.value>>b.depth>>b.size>>type;
		b.type = (Fishs_Gifts_Types)type;
		return w;
	}
};


#endif