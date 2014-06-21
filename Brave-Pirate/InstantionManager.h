#ifndef InstantionManager_h
#define InstantionManager_h
#pragma once 
#include "Barrel.h" 
#include "Fish.h"
#include "Bonus.h"
#include "Delay.h"
#include "Textures.h"



namespace
{
template <class typ>  class  InstantionManager;
template <class T>
std::ostream & operator<< (std::ostream &w, const InstantionManager<T> &i);

template <>
std::ostream & operator<< (std::ostream &w, const InstantionManager<Barrel> &i);

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
	friend std::istream & operator>> <>(std::istream &, InstantionManager<typ> &);
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
	}
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
			float speed = 0, hp = 0, dmg = 0, scl = 0;
			file>>textureName>>speed>>hp>>scl;

			if(textureName!= "" && speed!=0 && hp!=0 && scl !=0)
				listOfAllObjects.push_back(Fish(startPosition, Vector2(scl,scl), 0, textureName,hp,speed));
		}
		file.close();
	}	
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
		if(range < listOfAllObjects.size())
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

template <class Typ> std::ostream & operator<<(std::ostream &w, const InstantionManager<Fish> &i)
{
	w<<i.dispersion<<" "<<i.instantionDelay<<" "<<i.range<<" "<<i.startPosition
		<<" "<<i.upgradeDelay<<" "<<GameObject::fishesArrayPointer.size()<<std::endl;
	for(std::list<Fish>::const_iterator iter = GameObject::fishesArrayPointer.begin(); iter != GameObject::fishesArrayPointer.end(); iter++)
			w<<*iter<<" ";
	return w;
}

template <class Typ> std::ostream & operator<<(std::ostream &w, const InstantionManager<Barrel> &i)
{
	w<<i.dispersion<<" "<<i.instantionDelay<<" "<<i.range<<" "<<i.startPosition
		<<" "<<i.upgradeDelay<<" "<<GameObject::barrelsArrayPointer.size()<<std::endl;
	for(std::list<Barrel>::const_iterator iter = GameObject::barrelsArrayPointer.begin(); iter != GameObject::barrelsArrayPointer.end(); iter++)
			w<<*iter<<" ";
	return w;
}

template <class Typ> std::istream & operator>> (std::istream &w, const InstantionManager<Fish> &i)
{
	int typ =0;
	int size=0;
	w>>i.dispersion>>i.instantionDelay>>i.range>>i.startPosition>>i.upgradeDelay>>size;
	for(int c=0;c<size;c++)
	{
		w>>typ;
		if(typ == 1)
		{
			Fish f(Vector2(0,0), Vector2(10,10), 0, "cannonball.png", 10, 0.4f);
			w>>f;
			GameObject::fishesArrayPointer.push_back(f);
		}
		if(typ == 2)
		{
			Bonus b(Vector2(0,0), Vector2(10,10), 0, "cannonball.png", 10, 0.4f,10);
			w>>b;
			GameObject::fishesArrayPointer.push_back(b);
		}
	}
}

template <class Typ> std::istream & operator>> (std::istream &w, const InstantionManager<Barrel> &i)
{
	int size=0;
	w>>i.dispersion>>i.instantionDelay>>i.range>>i.startPosition>>i.upgradeDelay>>size;
	for(int c=0;c<size;c++)
	{
			Barrel b(FloatingObject(Vector2(0,0), Vector2(10,10), 0, "barrel.png", 
					Vector2(10,10), Vector2(10,10)),10,10,10,10);
			w>>b;
			GameObject::barrelsArrayPointer.push_back(b);
	}
}

template <>
std::ostream& operator<<  (std::ostream &w, const InstantionManager<Barrel> &i)
{
        w<<i.dispersion<<" "<<i.instantionDelay<<" "<<i.range<<" "<<i.startPosition<<" "<<i.upgradeDelay<<" "<<GameObject::barrelsArrayPointer.size()<<std::endl;
        for(Lista::const_iterator iter = GameObject::barrelsArrayPointer.begin(); iter != GameObject::barrelsArrayPointer.end(); ++iter)
                        w<< *static_cast<Barrel*>((*iter))<<" ";
        return w;
}
}

#endif