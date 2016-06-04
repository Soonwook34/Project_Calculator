﻿/******************************************
 *** 1학년 1학기 프로젝트 : 큰수계산기	***
 *** 시작 날짜 : 2016년5월 29일			***
 *** 팀원 :	박순욱(20160290)			***
 ***		임규형(20160318)			***
 ***		전혜윤(20160326)			***
 ***		배서현(20160294)			***
 ******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

void starter(char input[]);										//수식 입력 함수
void calculate(char value[], char answer[]);					//수식 계산 함수
int plus(char a[], int n, char b[], int m, char answer[]);		//덧셈 함수
int minus(char a[], int n, char b[], int m, char answer[]);		//뺄셈 함수
int multiply(char a[], int n, char b[], int m, char answer[]);	//곱셈 함수
int divide(char a[], int n, char b[], int m, char answer[]);	//나눗셈 함수
int mod(char a[], int n, char b[], int m, char answer[]);		//나머지 함수
void integer(char inte[], int n);								//받은 배열(상수)을 char형에서 int형으로 바꾸는 함수
void reverse(char rev[], int n);								//받은 배열(상수)을 뒤집어 주는 함수 
void printAnswer(char answer[], int length, int sigDigit);		//정답 출력 함수

int main()
{
	while(1){
		//처음 수식을 받을 배열
		char input[10000] = {0};

		//수식 입력 함수 호출
		starter(input);

		//end 처리
		if(input[0]=='e' && input[1]=='n' && input[2]=='d' && input[3]=='\0'){
			break;
		}

		//clear 처리
		if(input[0]=='c' && input[1]=='l' && input[2]=='e' && input[3]=='a' && input[4]=='r' && input[5]=='\0'){
			system("clear");
		}

		//save 처리
		if(input[0]=='s' && input[1]=='a' && input[2]=='v' && input[3]=='e' && input[4]=='\0'){
			printf("save 함수 만들어야지..\n\n");
		}

		//load 처리
		if(input[0]=='l' && input[1]=='o' && input[2]=='a' && input[3]=='d' && input[4]=='\0'){
			printf("load 함수 만들어야지..\n\n");
		}

		//VAR 처리
		if(input[0]=='V' && input[1]=='A' && input[2]=='R' && input[3]=='\0'){
			printf("VAR 함수 만들어야지..\n\n");
		}
	}
	return 0;
}

//수식 계산 함수
void starter(char input[])
{
	int c, i=0;
	//답 저장 배열
	char answer[59] = {0};

	printf("입력 : ");

	//처음 입력 받기
	while(1){
		c = getchar();

		//수식 입력의 마지막 처리
		if(c=='\n'){
			input[i] = '\0';
			break;
		}

		//띄어쓰기 무시
		else if((c==' ') || (c=='	')){
			continue;
		}

		//받을 수 있는 것(숫자, 알파벳, 수식 기호, 소수점)은 input배열에 저장
		else if(((c>='0') && (c<='9')) || ((c>='a') && (c<='z')) || ((c>='A') && (c<='Z')) || (c=='+') || (c=='-') || (c=='*') || (c=='/') || (c=='%') || (c=='=') || (c=='.')){
			input[i] = c;
			i++;
		}

		//기타 문자 오류 처리
		else{
			printf("error : '%c'는 인식할 수 없습니다\n\n",c);
			while(1){
				c = getchar();
				if(c=='\n'){
					break;
				}
			}
			return;
		}
	}

	//end이면 함수 종료
	if(input[0]=='e' && input[1]=='n' && input[2]=='d' && input[3]=='\0'){
		return;
	}

	//clear이면 함수 종료
	else if(input[0]=='c' && input[1]=='l' && input[2]=='e' && input[3]=='a' && input[4]=='r' && input[5]=='\0'){
		return;
	}

	//save이면 함수 종료
	else if(input[0]=='s' && input[1]=='a' && input[2]=='v' && input[3]=='e' && input[4]=='\0'){
		return;
	}

	//load이면 함수 종료
	else if(input[0]=='l' && input[1]=='o' && input[2]=='a' && input[3]=='d' && input[4]=='\0'){
		return;
	}

	//VAR이면 함수 종료
	else if(input[0]=='V' && input[1]=='A' && input[2]=='R' && input[3]=='\0'){
		return;
	}

	//수식 계산 함수 호출
	calculate(input, answer);

	return;
}

//수식 계산 함수
void calculate(char input[], char answer[])
{
	int c, i, j, k, l;
	int v1, v2;
	int length, sigDigit=0;
	//수와 문자와 기호를 저장할 배열
	char value[N][59] = {0};
	//소수
	char deciCount[N][2] = {0};

	//수식 구분하기
	for(i=0, j=0, k=0; i<strlen(input); i++){
		c = input[i];

		//숫자
		if((c>='0') && (c<='9')){
			if(k>=1){
				if(((value[j][k-1]>='a') && (value[j][k-1]<='z')) || ((value[j][k-1]>='A') && (value[j][k-1]<='Z'))){
					printf("error : 수식을 잘못 입력하셨습니다\n\n");
					return;
				}
			}
			//소수 카운트
			if(deciCount[j][0]){
				deciCount[j][1]+=1;
			}
			value[j][k] = c;
			k++;
		}

		//알파벳
		else if(((c>='a') && (c<='z')) || ((c>='A') && (c<='Z'))){
			if(k>=1){
				if((((value[j][k-1]>='0') && (value[j][k-1]<='9')) || deciCount[j][0]) || (((value[j][k-1]>='a') && (value[j][k-1]<='z')) || ((value[j][k-1]>='A') || (value[j][k-1]<='Z')))){
					printf("error : 수식을 잘못 입력하셨습니다\n\n");
					return;
				}
			}
			value[j][k] = c;
			k++;
		}

		//수식기호
		else if((c=='+') || (c=='-') || (c=='*') || (c=='/') || (c=='%') || (c=='=')){
			//전에 배열이 상수라면 소수자리 채우기
			if(value[j][0]>='0' && value[j][0]<='9'){
				for(l=deciCount[j][1];l<9;l++){
					value[j][k]='0';
					k++;
				}
			}
			value[j][k]='\0';
			value[j+1][0] = c;
			j+=2;
			k=0;
		}

		//소수점
		else if (c=='.'){
			if(deciCount[j][0]){
				printf("error : 소수를 잘못 입력하셨습니다\n\n");
				return;
			}
			deciCount[j][0]=1;
		}

		//배열의 끝
		else if(c=='\0'){
			value[j][k]='\0';
			break;
		}

		//소수 최대 자리를 초과했는지 검사
		if(deciCount[j][0]){
			if(deciCount[j][1]==10){
				printf("error : 소수부분은 9자리까지만 입력해주세요\n\n");
				return;
			}
		}

		//정수 최대 자리를 초과했는지 검사
		else{
			if(k==51){
				printf("error : 정수부분은 50자리까지만 입력해주세요\n\n");
				return;
			}
		}
	}

	//마지막 배열의 소수자리 처리
	if(value[j][0]>='0' && value[j][0]<='9'){
		for(l=deciCount[j][1];l<9;l++){
			value[j][k]='0';
			k++;
		}
	}

	v1=strlen(value[0]);
	v2=strlen(value[2]);
	
	//'+'일 경우
	if(value[1][0]=='+'){
		length = plus(value[0],v1,value[2],v2,answer);

		reverse(answer,length);

		if(deciCount[0][1]>=deciCount[2][1]){
			sigDigit = deciCount[0][1];
		}
		else{
			sigDigit = deciCount[2][1];
		}
	}

	//'-'일 경우
	if(value[1][0]=='-'){
		length = minus(value[0],v1,value[2],v2,answer);
	}

	//'*'일 경우
	if(value[1][0]=='*'){
		length = multiply(value[0],v1,value[2],v2,answer);
	}

	//'/'일 경우
	if(value[1][0]=='/'){
		length = divide(value[0],v1,value[2],v2,answer);
	}

	//'%'일 경우
	if(value[1][0]=='%'){
		length = mod(value[0],v1,value[2],v2,answer);
	}

	//정답 출력 함수 호출
	printAnswer(answer,length,sigDigit);

	printf("\n\n");
	return;
}

//덧셈 함수
int plus(char a[], int n, char b[], int m, char answer[])
{
	int i, j;

	//받은 배열(상수)를 char형에서 int형으로 바꾼다
	integer(a,n);
	integer(b,m);

	//받은 배열(상수)을 뒤집는다
	reverse(a,n);
	reverse(b,m);

	//소수자리를 위한 수
	if(n>=m){
		j=n;
	}
	else{
		j=m;
	}

	//두 수를 한자리씩 더해준다
	for(i=0;i<j;i++){
		answer[i] = a[i] + b[i];
	}

	//10이 넘어가면 올려준다
	for(i=0;i<=j;i++){
		if(answer[i] >= 10){
			answer[i] -= 10;
			answer[i+1] += 1;
		}
	}
	return j;
}

//뺄셈 함수
int minus(char a[], int n, char b[], int m, char answer[])
{
	printf("뺄셈 함수 입력해야지...\n");
	return 0;
}

//곱셈 함수
int multiply(char a[], int n, char b[], int m, char answer[])
{
	printf("곱셈 함수 입력해야지...\n");
	return 0;
}

//나눗셈 함수
int divide(char a[], int n, char b[], int m, char answer[])
{
	printf("나눗셈 함수 입력해야지...\n");
	return 0;
}

//나머지 함수
int mod(char a[], int n, char b[], int m, char answer[])
{
	printf("나머지 함수 입력해야지...\n");
	return 0;
}

//받은 배열(상수)을 char형에서 int형으로 바꾸는 함수
void integer(char inte[], int n)
{
	int i;
	for(i=0;i<n;i++){
		if(inte[i]!=0){
			inte[i] -= '0';
		}
	}
	return;
}

//받은 배열(상수)을 뒤집어 주는 함수
void reverse(char rev[], int n)
{
	int tmp;
	int i;
	for(i=0;i<n/2;i++){
		tmp = rev[i];
		rev[i] = rev[n-1-i];
		rev[n-1-i] = tmp;
	}
	return;
}

//정답 출력 함수
void printAnswer(char answer[], int length, int sigDigit)
{
	int i, j;
	printf("답 : ");
	for(i=0, j=0; i<length; i++){
		//소수자리 출력
		if(i==length-9){
			if(sigDigit!=0){
				printf(".");
				for(j=0; i<length+sigDigit-9; i++){
					printf("%d", answer[i]);
					j++;
					if((j%3==0) && j!=sigDigit){
						printf(",");
					}
				}
				return;
			}
			else{
				return;
			}
		}
		//콤마 출력
		else if((j%3==length%3) && (j!=0 && length!=1)){
			printf(",");
		}
		//정답 출력
		printf("%d", answer[i]);
		j++;
	}
	return;
}
