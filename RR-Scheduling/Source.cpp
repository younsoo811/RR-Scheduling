#include <stdio.h>
#define SIZE 100

static char job[SIZE] { 0 };	//작업이름 입력
static int CPUc[SIZE] = { 0 };	//작업의 CPU 사이클 저장
static int CPUcb[SIZE] = { 0 };	//작업의 CPU 사이클 백업
static int TTime[SIZE] = { 0 };	//작업의 반환시간 저장
static int TimeQ;				//CPU 할당 시간 (단위: ms)
static int ti;					//반복문 i의 최종 개수=전체 작업의 수
static int ini = 0;				//초기화된 CPU 사이클 수 저장
static int totT = 0;			//총 반환시간
static double avgT;				//작업의 평균 반환시간 저장

void RR_Scheduler();			// Round Robin 스케줄러
void Print_RR();				// 결과 출력

void main()
{
	int i = 0;	//작업 도착시간

	printf("CPU 할당 시간을 입력하세요 (정수 입력하기): ");
	scanf("%d", &TimeQ);
	printf("\n");

	//작업 도착 순서대로 입력 받기
	while(1){
		printf("작업의 이름을 입력하세요 (느낌표 입력시 입력 종료): ");
		scanf("%s", &job[i]);
		if (job[i] == '!'){
			break;	//느낌표 입력시 입력(while문) 종료
		}

		printf("작업의 CPU 사이클을 입력하세요: ");
		scanf("%d", &CPUc[i]);
		CPUcb[i] = CPUc[i];	//사이클 백업

		i++;	//작업 도착시간 1 증가
	}
	ti = i;	//i값을 전역변수 ti에 백업

	RR_Scheduler();	//RR 스케줄러 호출
	Print_RR();		//결과 출력
}

void RR_Scheduler() // Round Robin 스케줄러
{
	printf("\n\n- 간트 차트 상 작업의 할당, 회수\n\n");
	while (1){
		if (ini == ti){
			printf("-----마지막 작업 종료-----\n\n");
			//모든 작업이 할당 완료됨
			break;	//더이상 할당할 작업이 없음
		}
		for (int k = 0; k < ti; k++)
		{
			if (CPUc[k] != 0){

				if (CPUc[k] > TimeQ){
					//작업의 CPU 사이클 - 할당시간을 해주고
					//할당시간+총 반환시간만큼 작업의 반환시간에 더해주기
					CPUc[k] -= TimeQ;
					TTime[k] = TimeQ + totT;
					totT += TimeQ;	//총 반환시간 구하기
					printf("작업%c 인터럽트 발생 시간: %d \n", job[k], TTime[k]);
				}
				else{
					//남은 작업의 CPU 사이클+총 반환시간의 값을 작업의 반환시간에 더해주기
					//해당 작업 남은 CPU 사이클 0으로 초기화
					TTime[k] = CPUc[k] + totT;
					totT += CPUc[k];	//총 반환시간 구하기
					printf("작업%c 인터럽트 발생 시간: %d \n", job[k], TTime[k]);
					CPUc[k] = 0;
					ini++;

				}
			}
		}
	}
	
}

void Print_RR() // 결과 출력
{
	printf("\n- 반환시간 결과 출력\n\n");
	for (int i = 0; i < ti; i++){
		printf("작업 이름 : %c \n", job[i]);

		//도착시간 0을 기준으로 했을때의 반환시간 - 작업 도착시간
		printf("반환 시간 : %d \n\n", TTime[i] - i);

		//작업의 반환시간들을 모두 더하고
		avgT += (TTime[i] - i);
	}
	//모든 작업의 반환시간의 평균을 구하기
	avgT = avgT / ti;

	printf("평균 반환 시간: %.2lfms \n\n", avgT);
}