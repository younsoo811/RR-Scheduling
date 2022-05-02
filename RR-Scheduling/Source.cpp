#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define SIZE 100

static char job[SIZE];			//작업이름 입력
static int ATime[SIZE] = { 0 };	//작업의 도착시간 저장
static int CPUc[SIZE] = { 0 };	//작업의 CPU 사이클 저장
static int CPUcb[SIZE] = { 0 };	//작업의 CPU 사이클 백업
static int TTime[SIZE] = { 0 };	//작업의 반환시간 저장
static int TimeQ;				//CPU 할당 시간 (단위: ms)
static double avgT;				//작업의 평균 반환시간 저장
static int ti;					//반복문 i의 최종 개수=작업의 수
static int ini = 0;				//초기화된 CPU 사이클 수 저장
static int totT = 0;				//총 반환시간

void RR_Scheduler();

void Result();
void resort();

void main()
{
	int i = 0;

	printf("CPU 할당 시간을 입력하세요: ");
	scanf("%d", &TimeQ);

	//작업 도착 순서대로 입력 받기
	while(1){
		printf("작업의 이름을 입력하세요: ");
		scanf("%s", &job[i]);
		if (job[i] == '!'){
			break;	//느낌표 입력시 입력(while문) 종료
		}
		ATime[i] = i;		//작업 도착시간 저장

		printf("작업의 CPU 사이클을 입력하세요: ");
		scanf("%d", &CPUc[i]);
		CPUcb[i] = CPUc[i];	//사이클 백업

		i++;
	}
	ti = i;	//i값을 전역변수 ti에 백업

	RR_Scheduler();	//RR 스케줄러 호출
	Result();		//결과 출력
	//resort();		//결과 출력

}

void RR_Scheduler() // Round Robin 스케줄러
{
	while (1){
		if (ini == ti){
			printf("\n작업 할당 종료\n");
			//모든 작업이 할당 완료됨
			break;	//더이상 할당할 작업이 없음
		}
		for (int k = 0; k < ti; k++)
		{
			if (CPUc[k] != 0){

				if (CPUc[k] > TimeQ){
					//작업의 CPU 사이클 - 할당시간을 해주고
					//할당시간만큼 작업의 반환시간에 더해주기
					CPUc[k] -= TimeQ;
					
					TTime[k] = TimeQ + totT;
					totT += TimeQ;	//간트차트 끝부분 측정하기
					printf("%c 반환 시간 : %d \n", job[k], TTime[k]);
				}
				else{
					//남은 작업의 CPU 사이클을 반환시간에 더해주기
					//해당 작업 남은 CPU 사이클 0으로 초기화
					TTime[k] = CPUc[k] + totT;
					totT += CPUc[k];	//간트차트 끝부분 측정하기
					CPUc[k] = 0;
					ini++;

				}
			}
		}
	}
	
}

void Result() // 결과 출력
{
	for (int i = 0; i < ti; i++){
		printf("작업 이름 : %c \n", job[i]);
		printf("반환 시간 : %d \n\n", TTime[i] - i);

		avgT += (TTime[i] - i);
	}
	avgT = avgT / ti;

	printf("평균 반환 시간: %lf \n", avgT);
}

void resort()	//정렬
{
	
}