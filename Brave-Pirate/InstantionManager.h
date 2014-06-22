#ifndef InstantionManager_h
#define InstantionManager_h
#pragma once 
#include "Barrel.h" 
#include "Fish.h"
#include "Bonus.h"
#include "Delay.h"
#include "Textures.h"
#include <typeinfo>
#include "GameError.h"

namespace
{
template <class typ>  class  InstantionManager;

template <class T>
std::ostream & operator<< (std::ostream &w, const InstantionManager<T> &i);
template <class T>
std::istream & operator>> (std::istream &w, InstantionManager<T> &i);

template <>
std::ostream & operator<< (std::ostream &w, const InstantionManager<Barrel> &i);
template <>
std::ostream & operator<< (std::ostream &w, const InstantionManager<Fish> &i);

template <>
std::istream & operator>> (std::istream &w, InstantionManager<Barrel> &i);
template <>
std::istream & operator>> (std::istream &w, InstantionManager<Fish> &i);

template <class typ> class InstantionManager 
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
	explicit InstantionManager(const std::string path,Vector2 startPosition,int dispersion, Delay instantionDelay,Delay upgradeDelay); 
	~InstantionManager();
	void update();	
	void draw();

	friend std::ostream & operator<< <>(std::ostream &w, const InstantionManager<typ> &i);
	friend std::istream & operator>> <>(std::istream &w, InstantionManager<typ> &i);
};

template <class typ>
InstantionManager<typ>::InstantionManager(const std::string path,Vector2 startPosition, int dispersion, Delay instantionDelay,Delay upgradeDelay){}

template <>
InstantionManager<Barrel>::InstantionManager(const std::string path, Vector2 startPosition,int dispersion, Delay instantionDelay,Delay upgradeDelay)
:startPosition(startPosition), dispersion(dispersion), instantionDelay(instantionDelay), upgradeDelay(upgradeDelay), range(1)
{
	std::ifstream file(resourcesPath+barrelFile);
	if(file.is_open())//error
	{
		while(!file.eof())
		{
			std::string textureName = "";
			float speed = 0, hp = 0, dmg = 0, scl = 0;
			int scor =0;
			file>>textureName>>speed>>hp>>dmg>>scl>>scor;
			if(textureName!= "" && speed!=0 && hp!=0 && scl !=0 && scor!=0)
					listOfAllObjects.push_back(Barrel(FloatingObject(startPosition, Vector2(scl,scl), 0, textureName,
						Vector2(startPosition.get_X(),scl), Vector2(startPosition.get_X()+scl,scl)), hp, speed, dmg, scor));

		}
		file.close();
	}else throw GameError("File not found", resourcesPath+barrelFile);
	instantionDelay.Start();
	upgradeDelay.Start();
}

template <>
InstantionManager<Fish>::InstantionManager(const std::string path, Vector2 startPosition, int dispersion, Delay instantionDelay,Delay upgradeDelay)
:startPosition(startPosition),dispersion(dispersion), instantionDelay(instantionDelay), upgradeDelay(upgradeDelay), range(1)
{
	std::ifstream file(resourcesPath+fishesFile);
	if(file.is_open())//error
	{
		while(!file.eof())
		{
			std::string textureName = "";
			float speed = 0, hp = 0, dmg = 0, sclX = 0, sclY = 0;;
			file>>textureName>>speed>>hp>>sclX>>sclY;

			if(textureName!= "" && speed!=0 && hp!=0 && sclX !=0 && sclY != 0)
				listOfAllObjects.push_back(Fish(startPosition, Vector2(sclX,sclY), 0, textureName,hp,speed));
		}
		file.close();
	}else throw	GameError("File not found", resourcesPath+fishesFile);
	instantionDelay.Start();
	upgradeDelay.Start();
}

template <class typ>
InstantionManager<typ>::~InstantionManager(){}

template <>
InstantionManager<Barrel>::~InstantionManager()
{
	for(Lista::iterator iter = GameObject::barrelsArrayPointer.begin(); iter!= GameObject::barrelsArrayPointer.end();iter++)
	{
		delete *iter;
	}
	GameObject::barrelsArrayPointer.clear();
}

template <>
InstantionManager<Fish>::~InstantionManager()
{
	for(Lista::iterator iter = GameObject::fishesArrayPointer.begin(); iter!= GameObject::fishesArrayPointer.end();iter++)
	{
		delete *iter;
	}
	GameObject::fishesArrayPointer.clear();
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

		if((*iter)->getPosition().get_X()+ (*iter)->getSize().get_X()<0)
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
void InstantionManager<typ>::listUpdate(){}

template<class typ>
void InstantionManager<typ>::draw(){}

template<class typ>
void InstantionManager<typ>::add(unsigned int index){}

template<class typ>
void InstantionManager<typ>::update()
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
	std::list<Barrel>::iterator iter = listOfAllObjects.begin();
	for(;index >0;index--)iter++;
	GameObject::barrelsArrayPointer.push_back(new Barrel(*iter));	
}

template<>
void InstantionManager<Fish>::add(unsigned int index)
{
	std::list<Fish>::iterator iter = listOfAllObjects.begin();
	for(;index >0;index--)iter++;
	iter->setPosition(Vector2(startPosition.get_X(), (rand()%dispersion) + startPosition.get_Y()));
	GameObject::fishesArrayPointer.push_back(new Fish(*iter));
}

//FISH
template <> 
std::istream & operator>> (std::istream &w, InstantionManager<Fish> &i)
{
	int typ =0;
	int size=0;
	GameObject::fishesArrayPointer.clear();
	w>>i.dispersion>>i.instantionDelay>>i.range>>i.startPosition>>i.upgradeDelay>>size;
	for(int c=0;c<size;c++)
	{
		w>>typ;
		if(typ == 1)
		{
			Fish f(Vector2(0,0), Vector2(10,10), 0, "cannonball.png", 10, 0.4f);
			w>>f;
			GameObject::fishesArrayPointer.push_back(new Fish(f));
		}
		if(typ == 2)
		{
			Bonus b(Vector2(0,0), Vector2(10,10), 0, "cannonball.png", 10, 0.4f, 10, energyFish);
			w>>b;
			GameObject::fishesArrayPointer.push_back(new Bonus(b));
		}
	}
	return w;
}

template <> 
std::ostream & operator<<(std::ostream &w, const InstantionManager<Fish> &i)
{
	 w<<i.dispersion<<" "<<i.instantionDelay<<" "<<i.range<<" "<<i.startPosition<<" "<<i.upgradeDelay
		 <<" "<<GameObject::fishesArrayPointer.size()<<std::endl;
	for(Lista::const_iterator iter = GameObject::fishesArrayPointer.begin(); iter != GameObject::fishesArrayPointer.end(); ++iter){
		if(typeid(**iter) == typeid(Fish))	 
			w<< *static_cast<Fish*>((*iter));
		if(typeid(**iter) == typeid(Bonus))	 
			w<< *static_cast<Bonus*>((*iter));
	}
	w<<std::endl;
	return w;
}

//BARREL
template <>
std::istream& operator>> (std::istream &w, InstantionManager<Barrel> &i)
{
	GameObject::barrelsArrayPointer.clear();
	int size=0;
	w>>i.dispersion>>i.instantionDelay>>i.range>>i.startPosition>>i.upgradeDelay>>size;
	for(int c=0;c<size;c++)
	{
			Barrel b(FloatingObject(Vector2(400,400), Vector2(10,10), 0, "barrel.png", 
					Vector2(100,100), Vector2(100,100)),1,1,1,1);
			w>>b;
			GameObject::barrelsArrayPointer.push_back(new Barrel(b));
	}
	return w;
}

template <>
std::ostream& operator<<  (std::ostream &w, const InstantionManager<Barrel> &i)
{
        w<<i.dispersion<<" "<<i.instantionDelay<<" "<<i.range<<" "<<i.startPosition<<" "<<i.upgradeDelay
			<<" "<<GameObject::barrelsArrayPointer.size()<<std::endl;
        for(Lista::const_iterator iter = GameObject::barrelsArrayPointer.begin(); iter != GameObject::barrelsArrayPointer.end(); ++iter)
               w<< *static_cast<Barrel*>((*iter));
		w<<std::endl;
        return w;

}


}

#endif