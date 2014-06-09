#pragma once
class BasicObject
{
public:
	virtual ~BasicObject(void);
	virtual void update() = 0;
	virtual void draw()const = 0;
};

