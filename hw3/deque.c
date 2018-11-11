#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int compare(const char *p1,const char (*p2)[20]);
void push_front(int,int*);
void push_back(int,int*);
void pop_front(int*);
void pop_back(int*);
void show(int*);

int len;
int main(void){
	
	char command[20];
	char command_line[5][20]={"push_front","push_back","pop_front","pop_back","show"};
	int number;
	int deq[51];
	memset(deq,-10000,sizeof(deq));
	memset(command,'\0',sizeof(command));
	len =0;
	while(1){	
		memset(command,'\0',sizeof(command));
		scanf("%s",command);
		switch(compare(command,command_line)){
			case 1:
				scanf("%d",&number);
				push_front(number,&deq[0]);
				break;
			case 2:
				scanf("%d",&number);
				push_back(number,&deq[0]);
				break;
			case 3:
				pop_front(&deq[0]);
				break;
			case 4:
				pop_back(&deq[0]);
				break;
			case 5:
				show(&deq[0]);
				break;					
		}
		
	}


}


int compare(const char *p1, const char (*p2)[20]){
	int i;
	for(i=0;i<5;i++){
		if(strcmp(p1,*(p2+i)) == 0){
			return i+1;
		}
	}
}


void push_front(int number,int* arr){
	
	int i;
	for(i=len;i>0;i--){
		arr[i] = arr[i-1];
	}
	arr[0] = number;
	len++;
}
void push_back(int number,int* arr){
	arr[len] = number;
	len++;
}
void pop_back(int* arr){
	arr[len] = -10000;
	len--;
}
void pop_front(int* arr){
	int i;
	for(i=0;i<len;i++){
		arr[i] = arr[i+1];
	}
	len--;
}
void show(int* arr){
	int i;
	for(i=0;i<len;i++)
		printf("%3d",arr[i]);
}
