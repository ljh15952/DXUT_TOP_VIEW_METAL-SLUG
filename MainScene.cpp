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
void MainScene::Init()
{
	P = new Player;
	P->_position = { 10,10 };
	this->AddChild(P, 1);

	E = new Enemy_1(Ride_type::foot);
	E->_position = { 4500,4500 };
	this->AddChild(E, 1);

	S2 = new Sprite;
	S2->Create(L"asd.png");
	S2->_pivot = { 0,0 };
//	S2->_scale = { 0.2f,0.2f };
	this->AddChild(S2, 0);

	Bullet_Manager::GetInstance()->Make_Bullet();

	Minimap = new MiniMap(P,E);

	Camera::GetInstance()->CameraInit();
	Camera::GetInstance()->Follow(P);
}

void MainScene::Update()
{
	Camera::GetInstance()->SetPos({ P->_position.x , P->_position.y });
	Camera::GetInstance()->Update();
	Camera::GetInstance()->SetTransform();


	//벽 충돌처리
	RECT TEMP;
	if (IntersectRect(&TEMP, &P->GetRect(), &S2->GetRect()))
	{
	//	S1->_position -= v * 5.1f;
	}       
	//

	if (Director::GetInstance()->OnMouseDown())
	{

	}
	else if (Director::GetInstance()->OnMouse())
	{
		P->Attack();
	}
}

void MainScene::OnExit()
{
}

