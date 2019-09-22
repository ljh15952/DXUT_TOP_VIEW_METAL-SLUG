#pragma once
#include "Node.h"
#include "Sprite.h"
#include "Camera.h"
class Label :
	public Node
{
public:
	vector<Sprite*> sp;
	void Create_Label(int num);
	void Delete_Label();
	int Addpos;
};

