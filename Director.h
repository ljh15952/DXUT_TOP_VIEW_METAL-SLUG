#pragma once
#include "Types.h"
#include "Scene.h"
//#include "Renderer.h"
class Director : public Singleton<Director>
{
public:
	void Init();
	void Update();

	void ChangeScene(Scene* scene);

	bool OnMouseDown();
	bool OnMouse();
	bool OnMouseUp();

	LPD3DXSPRITE GetSprite() { return _sprite; };

	vector2 GetMousePos();
	POINT p;
private:
	static LPD3DXSPRITE _sprite;
	Scene* _currentScene;
	int ClickNum;
};

