#pragma once
class BasicObject
{
public:
	virtual ~BasicObject(void){};
	virtual void update(void) = 0;
	virtual void draw(void)const = 0;
};

