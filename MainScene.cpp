#include "DXUT.h"
#include "MainScene.h"


//보스전기획
//보스구현
//1스테이지 2스테이지 3스테이지
//권총 기관총 유도탄 스페셜스킬(화면적모두죽임)
//3스테이지에서 이동수단 파괴되면 게임오버~~ (바다라서)

//UI 총알수 미션목표 등등.. 체력        
//아이템
//코드 정리?

//아이템 쓰래기 뿌시면나오는거 **
//유도탄,스패셜스킬
//맞으면 화면흔들리는거
//더 재밋게할려면?
//적 더 많이?
//킥보드 맵 중간중간에 배치
//레이어 정리좀

//게임목표 1스테이지 클리어 조건
//게임어떠케시작할지 게임어떠떠케끝날지 처음에 2명을 쫓아가면서 스토리뜨면시작
//화면가운데위에 미션이뜸 
//마지막에 하천쪽으로이동하면서 끝    


//미니맵 주인공 파란색 화살표로 적들은 어케할까 
//지뢰크기 up 깜빡이는 애니메이션
//미션 1스프라이트에서 1때서주기
//아래미션들과 여러가지스크립트
//게섯거라~ 나잡아봐라
//이번엔 말이냐  
//이번엔 오토바이냐
//다 죽여주지
//다죽였군 이젠 바다로 가볼까

//미션1 야쿠자들을 죽여라! 남은적 : 2
//미션2 말을 탄 야쿠자들을 빨리 죽여라! 남은적 : 3
//미션3 오토바이 야쿠자들을 빨리 죽여라! 남은적 :4
//미션4 모든 야쿠자들을 빨리 죽여라! 남은적 : 10


//내일할꺼
//스쿠터설치 with 타는거까지 그냥 부딪혀도 타지게
//UI작업더해 스크립트나 남은총알수 남은적
//스패셜스킬
//2스테이지 작업으로 넘어가기
//onexit 데이터 소멸..

void MainScene::Init()
{
	P = new Player;
	P->_position = { 1600,2300 };
	this->AddChild(P, 1);

	S2 = new Sprite;
	S2->Create(L"asd.png");
	S2->_pivot = { 0,0 };
	this->AddChild(S2, 0);


	feulSp = new Sprite;
	feulSp->Create(L"fuel.png");
	feulSp->_position = { 100,200 };
	feulSp->_pivot = { 0,0 };
	feulSp->isUI = true;


	EnemyManager::GetInstance()->Make_Enemy();
	for (int i = 0; i < 2; i++)
	{
		EnemyManager::GetInstance()->SetEnemy({ 2000,2200 + float(200 * i) }, Ride_type::foot);
	}

	//set wall            
	for (int i = 0; i < 13; i++)
	{
		Sprite* w = new Sprite;
		w->Create(L"w.png");
		w->_visible = false;
		walls.push_back(w);
	}
	walls[0]->_position = { 1150,1000 };
	walls[1]->_position = { 6150,1000 };
	walls[2]->_position = { 8650,1000 };
	walls[3]->_position = { 3650,3600 };
	walls[4]->_position = { 6200,3600 };
	walls[5]->_position = { 8550,3600 };
	walls[6]->_position = { 1250,6150 };
	walls[7]->_position = { 3670,6150 };
	walls[8]->_position = { 8650,6150 };
	walls[9]->_position = { 1250,8750 };
	walls[10]->_position = { 3670,8750 };
	walls[11]->_position = { 6200,8750 };
	walls[12]->_position = { 8670,8730 };
	//


	TrasgManager::GetInstance()->Make_Trash();

	Bullet_Manager::GetInstance()->Make_Bullet();

	Minimap = new MiniMap(P);

	Camera::GetInstance()->CameraInit();
	Camera::GetInstance()->Follow(P);


	UI::GetInstance()->UI_Init();
	GM::GetInstance()->GMInit();

	spawntimer = 1;
}

void MainScene::Update()
{
	//카메라 업데이트
	Camera::GetInstance()->SetPos({ P->_position.x , P->_position.y });
	Camera::GetInstance()->Update();
	Camera::GetInstance()->SetTransform();
	//
	GM::GetInstance()->UpdateTimer();

	feulSp->_scale.x = P->feul / 10;

	//적 스포너
	/*spawntimer -= Time::deltaTime;
	if (spawntimer < 0)
	{
		vector2 v = { 2450 * float(rand() % 3 + 1),2450 * float(rand() % 3 + 1) };
		switch (rand() % 3)
		{
		case 0:
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::foot);
			break;
		case 1:
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::motercycle);
			break;
		case 2:
			EnemyManager::GetInstance()->SetEnemy(v, Ride_type::horse);
			break;
		}
		spawntimer = 1;
	}*/
	//

	//벽 충돌처리
	for (auto it : walls)
	{
		RECT TEMP;
		if (IntersectRect(&TEMP, &P->GetRect(), &it->GetRect()))
		{
			P->_position -= P->v * P->Speed;
			P->iscol = true;
		}
	}
	//

	//쓰래기 충돌처리
	P->isoil = false;
	for (auto it : TrasgManager::GetInstance()->Trashs)
	{
		RECT TEMP;
		if (IntersectRect(&TEMP, &P->GetRect(), &it->GetRect()))
		{
			if (it->t == T_Trash_Type::oil)
			{
				P->isoil = true;
			}
			else if (it->t == T_Trash_Type::trash)
			{
				if (it->_visible)
				{
					P->isHit();
					it->_visible = false;
				}
			}
		}
	}
	//플레이어 점프 충돌처리
	if (P->isJump)
	{
		for (auto it : EnemyManager::GetInstance()->_enemys)
		{
			if (it->_visible && it->isDie)
			{
				RECT TEMP;
				if (IntersectRect(&TEMP, &P->GetRect(), &it->GetRect()))
				{
					//it->_visible = false;
					P->RideType = it->RideType;

					if (P->RideType != Ride_type::foot)
						P->feul = 10;
				}
			}
		}
	}
	//

	for (auto it : Bullet_Manager::GetInstance()->_bullets)
	{
		for (auto it2 : EnemyManager::GetInstance()->_enemys)
		{
			if (it->_visible && !it->isHit)
			{
				it->CollideBullet(P);

				if (it2->_visible && !it2->isDie)
				{
					it->CollideBullet(it2);
				}
			}
		}
		for (auto it3 : TrasgManager::GetInstance()->Trashs)
		{
			if (it->_mytype == T_My_Type::player && it3->t == T_Trash_Type::trash && it3->_visible && !it->isHit)
			{
				RECT TEMP;
				if (IntersectRect(&TEMP, &it->GetRect(), &it3->GetRect()))
				{
					it3->_visible = false;
					it->isHit = true;
				}
			}
		}

	}

	if (Director::GetInstance()->OnMouseDown())
	{
		P->isshot = true;
		P->shot_timer = 0;

		if (UI::GetInstance()->isScript)
		{
			UI::GetInstance()->SetNextScriptUI();
		}
	}
	else if (Director::GetInstance()->OnMouse())
	{
		P->Attack();
	}
	else if (Director::GetInstance()->OnMouseUp())
	{
		P->isshot = false;
	}

	

}

void MainScene::OnExit()
{
}

