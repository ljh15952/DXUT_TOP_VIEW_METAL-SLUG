#include "DXUT.h"
#include "MainScene.h"
#include "RealMainScene.h"
//�̴ϸ� ���ΰ� �Ķ��� ȭ��ǥ�� ������ �����ұ� 
//����ũ�� up �����̴� �ִϸ��̼�
//�̼� 1��������Ʈ���� 1�����ֱ�
//�Ʒ��̼ǵ�� ����������ũ��Ʈ
//�Լ��Ŷ�~ ����ƺ���
//�̹��� ���̳�  
//�̹��� ������̳�
//�� �׿�����
//���׿��� ���� �ٴٷ� ������
//�̼�1 �����ڵ��� �׿���! ������ : 2
//�̼�2 ���� ź �����ڵ��� ���� �׿���! ������ : 3
//�̼�3 ������� �����ڵ��� ���� �׿���! ������ :4
//�̼�4 ��� �����ڵ��� ���� �׿���! ������ : 10


//�����Ҳ�
//���мȽ�ų
//��ũ��Ʈ�߰�
//����ź �ִϸ��̼�
//UI�� ����ϰ�
//������ �νø� �����۶߰� �Ա�
//1�������� �ڵ� ����
//���̾� ������

//spawntimer = 1;
//�� ������
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

