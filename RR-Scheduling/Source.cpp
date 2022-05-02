#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define SIZE 100

static char job[SIZE];			//�۾��̸� �Է�
static int ATime[SIZE] = { 0 };	//�۾��� �����ð� ����
static int CPUc[SIZE] = { 0 };	//�۾��� CPU ����Ŭ ����
static int CPUcb[SIZE] = { 0 };	//�۾��� CPU ����Ŭ ���
static int TTime[SIZE] = { 0 };	//�۾��� ��ȯ�ð� ����
static int TimeQ;				//CPU �Ҵ� �ð� (����: ms)
static double avgT;				//�۾��� ��� ��ȯ�ð� ����
static int ti;					//�ݺ��� i�� ���� ����=�۾��� ��
static int ini = 0;				//�ʱ�ȭ�� CPU ����Ŭ �� ����
static int totT = 0;				//�� ��ȯ�ð�

void RR_Scheduler();

void Result();
void resort();

void main()
{
	int i = 0;

	printf("CPU �Ҵ� �ð��� �Է��ϼ���: ");
	scanf("%d", &TimeQ);

	//�۾� ���� ������� �Է� �ޱ�
	while(1){
		printf("�۾��� �̸��� �Է��ϼ���: ");
		scanf("%s", &job[i]);
		if (job[i] == '!'){
			break;	//����ǥ �Է½� �Է�(while��) ����
		}
		ATime[i] = i;		//�۾� �����ð� ����

		printf("�۾��� CPU ����Ŭ�� �Է��ϼ���: ");
		scanf("%d", &CPUc[i]);
		CPUcb[i] = CPUc[i];	//����Ŭ ���

		i++;
	}
	ti = i;	//i���� �������� ti�� ���

	RR_Scheduler();	//RR �����ٷ� ȣ��
	Result();		//��� ���
	//resort();		//��� ���

}

void RR_Scheduler() // Round Robin �����ٷ�
{
	while (1){
		if (ini == ti){
			printf("\n�۾� �Ҵ� ����\n");
			//��� �۾��� �Ҵ� �Ϸ��
			break;	//���̻� �Ҵ��� �۾��� ����
		}
		for (int k = 0; k < ti; k++)
		{
			if (CPUc[k] != 0){

				if (CPUc[k] > TimeQ){
					//�۾��� CPU ����Ŭ - �Ҵ�ð��� ���ְ�
					//�Ҵ�ð���ŭ �۾��� ��ȯ�ð��� �����ֱ�
					CPUc[k] -= TimeQ;
					
					TTime[k] = TimeQ + totT;
					totT += TimeQ;	//��Ʈ��Ʈ ���κ� �����ϱ�
					printf("%c ��ȯ �ð� : %d \n", job[k], TTime[k]);
				}
				else{
					//���� �۾��� CPU ����Ŭ�� ��ȯ�ð��� �����ֱ�
					//�ش� �۾� ���� CPU ����Ŭ 0���� �ʱ�ȭ
					TTime[k] = CPUc[k] + totT;
					totT += CPUc[k];	//��Ʈ��Ʈ ���κ� �����ϱ�
					CPUc[k] = 0;
					ini++;

				}
			}
		}
	}
	
}

void Result() // ��� ���
{
	for (int i = 0; i < ti; i++){
		printf("�۾� �̸� : %c \n", job[i]);
		printf("��ȯ �ð� : %d \n\n", TTime[i] - i);

		avgT += (TTime[i] - i);
	}
	avgT = avgT / ti;

	printf("��� ��ȯ �ð�: %lf \n", avgT);
}

void resort()	//����
{
	
}