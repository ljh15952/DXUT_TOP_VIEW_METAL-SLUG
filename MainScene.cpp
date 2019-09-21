#include "DXUT.h"
#include "MainScene.h"
//오늘 만들것! 인게임 관련된것들  
//천천히 돌기? X
//객체화 장해물,적,탈것
//도망가는 적만들기 X
//적 공격하고 적죽이기 체력 깎
//적 지뢰놓기
//적 지뢰밟으면 나도 죽기 체력 깎
//총봐꾸기? X
//맵만들기(콜라이더 처리) X

//일단은 플레이어 부터 만들자
//플레이어가 하는것들
//움직이기
//총쏘기(권총,기관총,유도탄)
//점프하기
//차타기
//스페셜 스킬쓰기
//아이템쳐먹기 
//맵 밖으로 안나가게하기
//지형통과못하게하기


//총알이 하는일
//충돌처리하기
//유도탄이면 따라가기
//맵밖으로 안나가게하기
//지형통과안되게하기

//적이하는일
//지형에맞게도망가기
//일정시간마다 지뢰놓기
//차타고있기
//총알에 쳐맞으면 채력깎이기
//지뢰 오브젝트 풀로 만들기
//지뢰나 쓰래기를 던지는데 이거 랜덤으로 해주기 

//총알 시스템
//아이템
//보스전기획
//보스구현
//미니맵!!제일중요
//각 적의 거리구해서 띄워야됨
//이동수단갈아타기
//1스테이지 2스테이지 3스테이지
//권총 기관총 유도탄 스페셜스킬(화면적모두죽임)
//점프해서 적 이동수단으로 갈아타기 점프도중 적못죽이면 게임오버
//적과 일정거리이상 멀어졌을 경우 게임오버~
//3스테이지에서 이동수단 파괴되면 게임오버~~ (바다라서)
//적이동수단은 점프해서 탈수만있나?->ㅇㅇ
//플레이어는 그럼 리스크없이는 이동수단 못봐꿈? -> ㅇㅇ
//플레이어 죽으면 쳐맞아서 이동수단 파괴되면? -> 걸어서라도 잡아 못잡으면 거리멀어져서 게임오버지
//이동 수단 뭐뭠뭐로할까
//역동적인 카메라

//1스테이지 맨처음엔 퀵보드 타면서 적두명을 쫓아감
//10초마다 적 2명씩 생성? 적 10마리 잡으면 스테이지 클리어
//2스테이지 디귿자 큰~킬에서 모든 적을 다 죽여야함
//3스테이지 바다에서  보스전 보스를 따라가며 보스의 공격을 피하면서 공격 보트같은거 타고다녀야지


//벽 설치하기 OK
//플레이어 탈것 애니메이션추가 OK
//적 이동경로 잘 설정 OK
//적 스포너만들기 OK
//적과의거리뜨게 3초동안 거리가 100m이상일 경우 게임오버 no      
//UI 총알수 미션목표 등등.. 체력        
//아이템
//점프기능 적 이동수단으로 갈아타기
//이동수단별 스피드 밸런스 조절
//역동적인 카메라
//지뢰 vs 총알 , 지뢰 vs 플레이어 지뢰도그냥 총알로 만들자!!
//코드 정리?
//적죽으면 맵에서 사라지게 OK
//적여러종류추가

//아이템 쓰래기 뿌시면나오는거 **
//유도탄,스패셜스킬
//맞으면 깜빡이는거
//맞으면 화면흔들리는거
//죽는 애니메이션 + 폭팔 이펙트

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
void MainScene::Init()
{
	P = new Player;
	P->_position = { 1600,2300 };
	this->AddChild(P, 1);

	S2 = new Sprite;
	S2->Create(L"asd.png");
	S2->_pivot = { 0,0 };
	//	S2->_scale = { 0.2f,0.2f };
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

