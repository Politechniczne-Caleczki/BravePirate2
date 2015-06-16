#ifndef InstanceManager_h
#define InstanceManager_h
#pragma once 
#include "Obstacle.h" 
#include "Metal.h"
#include "Bonus.h"
#include "Delay.h"
#include "Textures.h"
#include <typeinfo>
#include "GameError.h"

namespace
{
template <class typ>  class  InstanceManager;

template <class T>
std::ostream & operator<< (std::ostream &w, const InstanceManager<T> &i);
template <class T>
std::istream & operator>> (std::istream &w, InstanceManager<T> &i);

template <>
std::ostream & operator<< (std::ostream &w, const InstanceManager<Obstacle> &i);
template <>
std::ostream & operator<< (std::ostream &w, const InstanceManager<Metal> &i);

template <>
std::istream & operator>> (std::istream &w, InstanceManager<Obstacle> &i);
template <>
std::istream & operator>> (std::istream &w, InstanceManager<Metal> &i);

template <class typ> class InstanceManager 
{ 
private: 
	std::list<typ> listOfAllObjects; 
	Delay instantionDelay, upgradeDelay;
	Vector2 startPosition; 
	int range;
	int dispersion;
	void add(unsigned int index);
	void listUpdate();
public: 
	explicit InstanceManager(const std::string path,Vector2 startPosition,int dispersion, Delay instantionDelay,Delay upgradeDelay); 
	~InstanceManager();
	void update();	
	void draw();

	friend std::ostream & operator<< <>(std::ostream &w, const InstanceManager<typ> &i);
	friend std::istream & operator>> <>(std::istream &w, InstanceManager<typ> &i);
};

template <class typ>
InstanceManager<typ>::InstanceManager(const std::string path,Vector2 startPosition, int dispersion, Delay instantionDelay,Delay upgradeDelay){}

template <>
InstanceManager<Obstacle>::InstanceManager(const std::string path, Vector2 startPosition,int dispersion, Delay instantionDelay,Delay upgradeDelay)
:startPosition(startPosition), dispersion(dispersion), instantionDelay(instantionDelay), upgradeDelay(upgradeDelay), range(1)
{
	std::ifstream file(resourcesPath+cactosFile);
	if(file.is_open())//error
	{
		while (!file.eof())
		{
			std::string textureName = "";
			float hp = 0, dmg = 0;
			int scor = 0;
			Vector2 scale(0, 0);

			file >> textureName >> hp >> dmg >> scale >> scor;
			if (textureName != "" && hp != 0 && scor != 0)
				listOfAllObjects.push_back(Obstacle(FloatingObject(startPosition, scale, 0, textureName, Vector2(startPosition.get_X(), scale.get_Y()), Vector2(startPosition.get_X() + scale.get_X(), scale.get_Y())), hp, dmg, scor));
		}
		file.close();
	}else throw GameError("File not found", resourcesPath+cactosFile);
	instantionDelay.Start();
	upgradeDelay.Start();
}

template <>
InstanceManager<Metal>::InstanceManager(const std::string path, Vector2 startPosition, int dispersion, Delay instantionDelay,Delay upgradeDelay)
:startPosition(startPosition),dispersion(dispersion), instantionDelay(instantionDelay), upgradeDelay(upgradeDelay), range(1)
{
	std::ifstream file(resourcesPath+metalFile);
	if(file.is_open())//error
	{
		while(!file.eof())
		{
			std::string textureName = "";
			float hp = 0;
			Vector2 size(0, 0);
			file >> textureName >> hp >> size;

			if (textureName != "" && hp != 0);
				listOfAllObjects.push_back(Metal(startPosition,size, 0, textureName,hp));
		}
		file.close();
	}else throw	GameError("File not found", resourcesPath+metalFile);
	instantionDelay.Start();
	upgradeDelay.Start();
}

template <class typ>
InstanceManager<typ>::~InstanceManager(){}

template <>
InstanceManager<Obstacle>::~InstanceManager()
{
	for(Lista::iterator iter = GameObject::cactosArrayPointer.begin(); iter!= GameObject::cactosArrayPointer.end();iter++)
	{
		delete *iter;
	}
	GameObject::cactosArrayPointer.clear();
}

template <>
InstanceManager<Metal>::~InstanceManager()
{
	for(Lista::iterator iter = GameObject::metalArrayPointer.begin(); iter!= GameObject::metalArrayPointer.end();iter++)
	{
		delete *iter;
	}
	GameObject::metalArrayPointer.clear();
}

template<>
void InstanceManager<Obstacle>::listUpdate()
{
	for(Lista::iterator iter = GameObject::cactosArrayPointer.begin(); iter!= GameObject::cactosArrayPointer.end();)
	{		
		(*iter)->update();
		if((*iter)->isDestroyed())
		{		
			delete *iter;			
			iter = GameObject::cactosArrayPointer.erase(iter);				
		}
		else
			iter++;		
	}
}

template<>
void InstanceManager<Metal>::listUpdate()
{
	for(Lista::iterator iter = GameObject::metalArrayPointer.begin(); iter!= GameObject::metalArrayPointer.end();)
	{
		(*iter)->update();

		if((*iter)->getPosition().get_X()+ (*iter)->getSize().get_X()<0)
			(*iter)->onCollision();

		
		if((*iter)->isDestroyed())
		{		
			delete *iter;
			iter = GameObject::metalArrayPointer.erase(iter);			
		}
		else
			iter++;		
	}

}

template<class typ>
void InstanceManager<typ>::listUpdate(){}

template<class typ>
void InstanceManager<typ>::draw(){}

template<class typ>
void InstanceManager<typ>::add(unsigned int index){}

template<class typ>
void InstanceManager<typ>::update()
{
	listUpdate();
	instantionDelay.update();
	upgradeDelay.update();

	if(upgradeDelay.idRedy())
	{		
		if(range < (int)listOfAllObjects.size())
		{
			instantionDelay.setDelay(instantionDelay.getDelay()/INCREASE_LEVEL_DIFFICULTY);
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
void InstanceManager<Obstacle>::draw()
{
	for(Lista::iterator iter = GameObject::cactosArrayPointer.begin(); iter!= GameObject::cactosArrayPointer.end(); iter++)
	{
		(*iter)->draw();
	}
}

template<>
void InstanceManager<Metal>::draw()
{
	for(Lista::iterator iter = GameObject::metalArrayPointer.begin(); iter!= GameObject::metalArrayPointer.end(); iter++)
	{
		(*iter)->draw();
	}
}

template<>
void InstanceManager<Obstacle>::add(unsigned int index)
{
	std::list<Obstacle>::iterator iter = listOfAllObjects.begin();
	for(;index >0;index--)iter++;
	GameObject::cactosArrayPointer.push_back(new Obstacle(*iter));	
}

template<>
void InstanceManager<Metal>::add(unsigned int index)
{
	std::list<Metal>::iterator iter = listOfAllObjects.begin();
	for(;index >0;index--)iter++;
	iter->setPosition(Vector2(startPosition.get_X(), (rand()%dispersion) + startPosition.get_Y()));
	GameObject::metalArrayPointer.push_back(new Metal(*iter));
}

//FISH
template <> 
std::istream & operator>> (std::istream &w, InstanceManager<Metal> &i)
{
	int typ =0;
	int size=0;
	GameObject::metalArrayPointer.clear();
	w>>i.dispersion>>i.instantionDelay>>i.range>>i.startPosition>>i.upgradeDelay>>size;
	for(int c=0;c<size;c++)
	{
		w>>typ;
		if(typ == 1)
		{
			Metal f(Vector2(0,0), Vector2(10,10), 0, "cannonball.png", 10);
			w>>f;
			GameObject::metalArrayPointer.push_back(new Metal(f));
		}
		if(typ == 2)
		{
			Bonus b(Vector2(0,0), Vector2(10,10), 0, "cannonball.png", 10, 0.4f, 10, energyBonus);
			w>>b;
			GameObject::metalArrayPointer.push_back(new Bonus(b));
		}
	}
	return w;
}

template <> 
std::ostream & operator<<(std::ostream &w, const InstanceManager<Metal> &i)
{
	 w<<i.dispersion<<" "<<i.instantionDelay<<" "<<i.range<<" "<<i.startPosition<<" "<<i.upgradeDelay
		 <<" "<<GameObject::metalArrayPointer.size()<<std::endl;
	for(Lista::const_iterator iter = GameObject::metalArrayPointer.begin(); iter != GameObject::metalArrayPointer.end(); ++iter){
		if(typeid(**iter) == typeid(Metal))	 
			w<< *static_cast<Metal*>((*iter));
		if(typeid(**iter) == typeid(Bonus))	 
			w<< *static_cast<Bonus*>((*iter));
	}
	w<<std::endl;
	return w;
}

//BARREL
template <>
std::istream& operator>> (std::istream &w, InstanceManager<Obstacle> &i)
{
	GameObject::cactosArrayPointer.clear();
	int size=0;
	w>>i.dispersion>>i.instantionDelay>>i.range>>i.startPosition>>i.upgradeDelay>>size;
	for(int c=0;c<size;c++)
	{
			Obstacle b(FloatingObject(Vector2(400,400), Vector2(10,10), 0, "cactos.png", 
					Vector2(100,100), Vector2(100,100)),1,1,1);
			w>>b;
			GameObject::cactosArrayPointer.push_back(new Obstacle(b));
	}
	return w;
}

template <>
std::ostream& operator<<  (std::ostream &w, const InstanceManager<Obstacle> &i)
{
        w<<i.dispersion<<" "<<i.instantionDelay<<" "<<i.range<<" "<<i.startPosition<<" "<<i.upgradeDelay
			<<" "<<GameObject::cactosArrayPointer.size()<<std::endl;
        for(Lista::const_iterator iter = GameObject::cactosArrayPointer.begin(); iter != GameObject::cactosArrayPointer.end(); ++iter)
               w<< *static_cast<Obstacle*>((*iter));
		w<<std::endl;
        return w;

}


}

#endif