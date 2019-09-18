#include "DXUT.h"
#include "MainScene.h"
//���� �����! �ΰ��� ���õȰ͵�  
//õõ�� ����? X
//��üȭ ���ع�,��,Ż��
//�������� ������� X
//�� �����ϰ� �����̱� ü�� ��
//�� ���ڳ���
//�� ���ڹ����� ���� �ױ� ü�� ��
//�Ѻ��ٱ�? X
//�ʸ����(�ݶ��̴� ó��) X

//�ϴ��� �÷��̾� ���� ������
//�÷��̾ �ϴ°͵�
//�����̱�
//�ѽ��(����,�����,����ź)
//�����ϱ�
//��Ÿ��
//����� ��ų����
//�������ĸԱ� 
//�� ������ �ȳ������ϱ�
//����������ϰ��ϱ�


//�Ѿ��� �ϴ���
//�浹ó���ϱ�
//����ź�̸� ���󰡱�
//�ʹ����� �ȳ������ϱ�
//��������ȵǰ��ϱ�

//�����ϴ���
//�������°Ե�������
//�����ð����� ���ڳ���
//��Ÿ���ֱ�
//�Ѿ˿� �ĸ����� ä�±��̱�
//���� ������Ʈ Ǯ�� �����
//���ڳ� �����⸦ �����µ� �̰� �������� ���ֱ� 

//�Ѿ� �ý���
//������
//��������ȹ
//��������
//�̴ϸ�!!�����߿�
//�� ���� �Ÿ����ؼ� ����ߵ�
//�̵����ܰ���Ÿ��
//1�������� 2�������� 3��������
//���� ����� ����ź ����Ƚ�ų(ȭ�����������)
//�����ؼ� �� �̵��������� ����Ÿ�� �������� �������̸� ���ӿ���
//���� �����Ÿ��̻� �־����� ��� ���ӿ���~
//3������������ �̵����� �ı��Ǹ� ���ӿ���~~ (�ٴٶ�)
//���̵������� �����ؼ� Ż�����ֳ�?->����
//�÷��̾�� �׷� ����ũ���̴� �̵����� ������? -> ����
//�÷��̾� ������ �ĸ¾Ƽ� �̵����� �ı��Ǹ�? -> �ɾ�� ��� �������� �Ÿ��־����� ���ӿ�����
//�̵� ���� ���l�����ұ�
//�������� ī�޶�

//1�������� ��ó���� ������ Ÿ�鼭 ���θ��� �Ѿư�
//10�ʸ��� �� 2�� ����? �� 10���� ������ �������� Ŭ����
//2�������� ����� ū~ų���� ��� ���� �� �׿�����
//3�������� �ٴٿ���  ������ ������ ���󰡸� ������ ������ ���ϸ鼭 ���� ��Ʈ������ Ÿ��ٳ����


//�� ��ġ�ϱ�
//�÷��̾� Ż�� �ִϸ��̼��߰�
//�� �̵���� �� ����
//�� �����ʸ����
//�����ǰŸ��߰� 3�ʵ��� �Ÿ��� 100m�̻��� ��� ���ӿ���
//UI �Ѿ˼� �̼Ǹ�ǥ ���.. ü��
//������
//������� �� �̵��������� ����Ÿ��
//�̵����ܺ� ���ǵ� �뷱�� ����
//�������� ī�޶�
//���� vs �Ѿ� , ���� vs �÷��̾� ���ڵ��׳� �Ѿ˷� ������!!
//�������� �ʿ��� �������
void MainScene::Init()
{
	P = new Player;
	P->_position = { 2300,2300 };
	this->AddChild(P, 1);

	for (int i = 0; i < 2; i++)
	{
		Enemy_1 * e = new Enemy_1(Ride_type::foot);
		e->_position = { 4930 ,4880 };
		e->GoPos = e->_position;
		this->AddChild(e, 1);
		E.push_back(e);
	}
	S2 = new Sprite;
	S2->Create(L"asd.png");
	S2->_pivot = { 0,0 };
//	S2->_scale = { 0.2f,0.2f };
	this->AddChild(S2, 0);

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

	Bullet_Manager::GetInstance()->Make_Bullet();
	EnemyWeaponManager::GetInstance()->MakeEnemyWeapons();

	Minimap = new MiniMap(P,E);
    
	Camera::GetInstance()->CameraInit();
	Camera::GetInstance()->Follow(P);
}

void MainScene::Update()
{
	Camera::GetInstance()->SetPos({ P->_position.x , P->_position.y });
	Camera::GetInstance()->Update();
	Camera::GetInstance()->SetTransform();

//	cout << P->_position.x << " " << _position.y << endl;
	//�� �浹ó��
	for (auto it : walls)
	{
		RECT TEMP;
		if (IntersectRect(&TEMP, &P->GetRect(), &it->GetRect()))
		{
			P->_position -= P->v * P->Speed;
			P->iscol = true;
		}
	}

	for (auto it : Bullet_Manager::GetInstance()->_bullets)
	{
		for (auto it2 : E)
		{
			if (it->_visible)
			{
				it->CollideBullet(P);
				//for(auto it : Enemy_Manager::GetInstance()->_enemys)
				//{
				//		it->collideBullet(it);
				//}
				it->CollideBullet(it2);
			}
		}
	}

	if (Director::GetInstance()->OnMouseDown())
	{
		P->isshot = true;
		P->shot_timer = 0;
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

