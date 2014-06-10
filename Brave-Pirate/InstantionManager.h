#pragma once 
#include <list> 
#include <SDL.h>
#include <cstddef> 
#include "Barrel.h" 
#include "Fish.h"
#include "Delay.h"
#include "Textures.h"

template <class typ> class InstantionManager 
{ 
private: 
	list<typ> listOfAllObjects; 
	Delay instantionDelay, upgradeDelay;
	Vector2 startPosition; 
	int range;
	int dispersion;
	void add(unsigned int index);
	void listUpdate();
public: 
	InstantionManager(const string path,Vector2 startPosition,int dispersion, Delay instantionDelay,Delay upgradeDelay); 
	~InstantionManager(){};
	void update();	
	void draw();
};

template <class typ>
InstantionManager<typ>::InstantionManager(const string path,Vector2 startPosition, int dispersion, Delay instantionDelay,Delay upgradeDelay){}

template <>
InstantionManager<Barrel>::InstantionManager(string path, Vector2 startPosition,int dispersion, Delay instantionDelay,Delay upgradeDelay)
:startPosition(startPosition), dispersion(dispersion), instantionDelay(instantionDelay), upgradeDelay(upgradeDelay), range(1)
{
	FILE * myFile = fopen(path.data(),"r");
		if (myFile!=NULL)//error
		{				
			while(!feof(myFile))
			{
				char textureName[32];
				float speed, hp, dmg, scl;
				fscanf(myFile,"%s %f %f %f %f",textureName, &speed, &hp, &dmg, &scl);	
				listOfAllObjects.push_back(Barrel(FloatingObject(startPosition, Vector2(scl,scl), 0, Textures::getTexture(textureName), 
					Vector2(startPosition.get_X(),scl), Vector2(startPosition.get_X()+scl,scl)), hp, speed, dmg));
			}	
		}
	fclose(myFile);
	instantionDelay.Start();
	upgradeDelay.Start();
}

template <>
InstantionManager<Fish>::InstantionManager(string path, Vector2 startPosition, int dispersion, Delay instantionDelay,Delay upgradeDelay)
:startPosition(startPosition),dispersion(dispersion), instantionDelay(instantionDelay), upgradeDelay(upgradeDelay), range(1)
{
	
	FILE * myFile = fopen(path.data(),"r");
		if (myFile!=NULL)//error
		{				
			while(!feof(myFile))
			{
				char textureName[32];
				float speed, hp, dmg, scl;
				fscanf(myFile,"%s %f %f %f",textureName, &speed, &hp, &scl);	
				listOfAllObjects.push_back(Fish(startPosition, Vector2(scl,scl), 0, Textures::getTexture("fish.png"),hp,speed));
			}
		}
	fclose(myFile);
	instantionDelay.Start();
	upgradeDelay.Start();
}

template<>
void InstantionManager<Barrel>::listUpdate()
{
	for(Lista::iterator iter = GameObject::barrelsArrayPointer.begin(); iter!= GameObject::barrelsArrayPointer.end();)
	{		
		(*iter)->update();
		if((*iter)->isDestroyed())
		{		
			delete *iter;			
			iter = GameObject::barrelsArrayPointer.erase(iter);				
		}
		else
			iter++;		
	}
}

template<>
void InstantionManager<Fish>::listUpdate()
{
	for(Lista::iterator iter = GameObject::fishesArrayPointer.begin(); iter!= GameObject::fishesArrayPointer.end();)
	{
		(*iter)->update();

		if((*iter)->getPosition().get_X()- (*iter)->getSize().get_X()<0)
			(*iter)->onCollision();

		
		if((*iter)->isDestroyed())
		{		
			delete *iter;
			iter = GameObject::fishesArrayPointer.erase(iter);			
		}
		else
			iter++;		
	}

}

template<class typ>
void InstantionManager<typ>::update()
{
	listUpdate();

	instantionDelay.update();
	upgradeDelay.update();

	if(upgradeDelay.idRedy())
	{
		if(range<listOfAllObjects.size())
		{
			upgradeDelay.Start();
			range++;
		}
	}

	if(instantionDelay.idRedy())
	{
		instantionDelay.Start();
		unsigned int index = rand()%(range);
		add(index);
	}
}

template<>
void InstantionManager<Barrel>::draw()
{
	for(Lista::iterator iter = GameObject::barrelsArrayPointer.begin(); iter!= GameObject::barrelsArrayPointer.end(); iter++)
	{
		(*iter)->draw();
	}
}

template<>
void InstantionManager<Fish>::draw()
{
	for(Lista::iterator iter = GameObject::fishesArrayPointer.begin(); iter!= GameObject::fishesArrayPointer.end(); iter++)
	{
		(*iter)->draw();
	}
}

template<>
void InstantionManager<Barrel>::add(unsigned int index)
{
	list<Barrel>::iterator iter = listOfAllObjects.begin();
	for(;index >0;index--)iter++;
	GameObject::barrelsArrayPointer.push_back(new Barrel(*iter));	
}

template<>
void InstantionManager<Fish>::add(unsigned int index)
{
	list<Fish>::iterator iter = listOfAllObjects.begin();
	for(;index >0;index--)iter++;
	iter->setPosition(Vector2(startPosition.get_X(), (rand()%dispersion) + startPosition.get_Y()));
	GameObject::fishesArrayPointer.push_back(new Fish(*iter));
}


