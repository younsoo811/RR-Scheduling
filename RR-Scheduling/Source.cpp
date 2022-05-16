#include <stdio.h>
#define SIZE 100

static char job[SIZE] { 0 };	//�۾��̸� �Է�
static int CPUc[SIZE] = { 0 };	//�۾��� CPU ����Ŭ ����
static int CPUcb[SIZE] = { 0 };	//�۾��� CPU ����Ŭ ���
static int TTime[SIZE] = { 0 };	//�۾��� ��ȯ�ð� ����
static int TimeQ;				//CPU �Ҵ� �ð� (����: ms)
static int ti;					//�ݺ��� i�� ���� ����=��ü �۾��� ��
static int ini = 0;				//�ʱ�ȭ�� CPU ����Ŭ �� ����
static int totT = 0;			//�� ��ȯ�ð�
static double avgT;				//�۾��� ��� ��ȯ�ð� ����

void RR_Scheduler();			// Round Robin �����ٷ�
void Print_RR();				// ��� ���

void main()
{
	int i = 0;	//�۾� �����ð�

	printf("CPU �Ҵ� �ð��� �Է��ϼ��� (���� �Է��ϱ�): ");
	scanf("%d", &TimeQ);
	printf("\n");

	//�۾� ���� ������� �Է� �ޱ�
	while(1){
		printf("�۾��� �̸��� �Է��ϼ��� (����ǥ �Է½� �Է� ����): ");
		scanf("%s", &job[i]);
		if (job[i] == '!'){
			break;	//����ǥ �Է½� �Է�(while��) ����
		}

		printf("�۾��� CPU ����Ŭ�� �Է��ϼ���: ");
		scanf("%d", &CPUc[i]);
		CPUcb[i] = CPUc[i];	//����Ŭ ���

		i++;	//�۾� �����ð� 1 ����
	}
	ti = i;	//i���� �������� ti�� ���

	RR_Scheduler();	//RR �����ٷ� ȣ��
	Print_RR();		//��� ���
}

void RR_Scheduler() // Round Robin �����ٷ�
{
	printf("\n\n- ��Ʈ ��Ʈ �� �۾��� �Ҵ�, ȸ��\n\n");
	while (1){
		if (ini == ti){
			printf("-----������ �۾� ����-----\n\n");
			//��� �۾��� �Ҵ� �Ϸ��
			break;	//���̻� �Ҵ��� �۾��� ����
		}
		for (int k = 0; k < ti; k++)
		{
			if (CPUc[k] != 0){

				if (CPUc[k] > TimeQ){
					//�۾��� CPU ����Ŭ - �Ҵ�ð��� ���ְ�
					//�Ҵ�ð�+�� ��ȯ�ð���ŭ �۾��� ��ȯ�ð��� �����ֱ�
					CPUc[k] -= TimeQ;
					TTime[k] = TimeQ + totT;
					totT += TimeQ;	//�� ��ȯ�ð� ���ϱ�
					printf("�۾�%c ���ͷ�Ʈ �߻� �ð�: %d \n", job[k], TTime[k]);
				}
				else{
					//���� �۾��� CPU ����Ŭ+�� ��ȯ�ð��� ���� �۾��� ��ȯ�ð��� �����ֱ�
					//�ش� �۾� ���� CPU ����Ŭ 0���� �ʱ�ȭ
					TTime[k] = CPUc[k] + totT;
					totT += CPUc[k];	//�� ��ȯ�ð� ���ϱ�
					printf("�۾�%c ���ͷ�Ʈ �߻� �ð�: %d \n", job[k], TTime[k]);
					CPUc[k] = 0;
					ini++;

				}
			}
		}
	}
	
}

void Print_RR() // ��� ���
{
	printf("\n- ��ȯ�ð� ��� ���\n\n");
	for (int i = 0; i < ti; i++){
		printf("�۾� �̸� : %c \n", job[i]);

		//�����ð� 0�� �������� �������� ��ȯ�ð� - �۾� �����ð�
		printf("��ȯ �ð� : %d \n\n", TTime[i] - i);

		//�۾��� ��ȯ�ð����� ��� ���ϰ�
		avgT += (TTime[i] - i);
	}
	//��� �۾��� ��ȯ�ð��� ����� ���ϱ�
	avgT = avgT / ti;

	printf("��� ��ȯ �ð�: %.2lfms \n\n", avgT);
}