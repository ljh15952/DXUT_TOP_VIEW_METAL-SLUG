#include "DXUT.h"
#include "MainScene.h"
#include "RealMainScene.h"
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
//스패셜스킬
//스크립트추가
//유도탄 애니메이션
//UI더 깔끔하게
//쓰래기 부시면 아이템뜨고 먹기
//1스테이지 코드 정리
//레이어 정리좀

//spawntimer = 1;
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

void MainScene::Init()
{
	stage = new Stage_1;
}

void MainScene::Update()
{
	stage->Collide();

	
	if (DXUTWasKeyPressed('Q'))
	{
		delete stage;
		stage = new Stage_2;
	}
	if (DXUTWasKeyPressed('W'))
	{
		delete stage;
		stage = new Stage_3;
	}
}

void MainScene::OnExit()
{
}

