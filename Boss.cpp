#include "DXUT.h"
#include "Boss.h"
#define PI 3.14159265

Boss::Boss(Player* p)
{
	Create(L"boss/Idle/i1.png");
	_scale = { 3,3 };
	player = p;
	_mytype = T_My_Type::boss;

	shottimer = 0.05f;
	rad = 0;
}

Boss::~Boss()
{
}

void Boss::Attack()
{
	P1();
}

void Boss::Movement()
{
}


void Boss::Update()
{
	_position.x += 7;

	static float t1 = 0.5f;
	t1 -= Time::deltaTime;
	if (t1 < 0)
	{
		Attack();
		t1 = shottimer;
	}
}
void Boss::isHit()
{
}

void Boss::P1()
{
	if (shottimer <= 0.02f)
	{
		//setnextpat;
		return;
	}
	shottimer -= 0.0001f;
	for (int r = 0; r <= 360; r+=10)
	{
		float x = (cos(r * (PI / 180)));
		float y = (sin(r * (PI / 180)));
		Bullet_Manager::GetInstance()->Shot_Bullet(_position, { x,y }, _mytype, P_shot_type::pistol);
	}
}

void Boss::P2()
{
	if (shottimer <= 0.02f)
	{
		//setnextpat;
		return;
	}
	shottimer -= 0.0001f;
	float x = (cos(rad * (PI / 180)));
	float y = (sin(rad * (PI / 180)));
	//4¹æÇâ
	Bullet_Manager::GetInstance()->Shot_Bullet(_position, { x,y }, _mytype, P_shot_type::pistol);
	Bullet_Manager::GetInstance()->Shot_Bullet(_position, { -x,-y }, _mytype, P_shot_type::pistol);
	Bullet_Manager::GetInstance()->Shot_Bullet(_position, { x,-y }, _mytype, P_shot_type::pistol);
	Bullet_Manager::GetInstance()->Shot_Bullet(_position, { -x,y }, _mytype, P_shot_type::pistol);

	rad += 5;
}

void Boss::P3()
{
	if (shottimer <= 0.02f)
	{
		//setnextpat;
		return;
	}
	shottimer -= 0.0001f;
	float x = (cos(rad * (PI / 180)));
	float y = (sin(rad * (PI / 180)));
	Bullet_Manager::GetInstance()->Shot_Bullet(_position, { x,-y }, _mytype, P_shot_type::pistol);
	Bullet_Manager::GetInstance()->Shot_Bullet(_position, { -x,y }, _mytype, P_shot_type::pistol);
	rad += 10;

}
