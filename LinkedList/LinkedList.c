#include <stdio.h>

//Node 구조체
typedef struct node {
	int value; // 값을 저장하는 변수
	struct node* next; //다음 노드의 주소를 저장
	//다음 노드는 struct node 타입임으로 다음 노드의 주소는 struct node 타입의 주소임으로 struct node* 로 next를 선언한다.
}node; // 이름 재정의 ( 안하면 struct node 라고 계속 써야한다)


//NULL : 포인터가 가리키는 대상이 없는 경우
node* head= NULL; // 첫 노드의 주소를 저장하는 변수 8byte 포인터

void insertFrontNode(int data) 
{
	node* newNode;  // 생성된 노드의 주소를 저장하는 변수
	newNode=(node*)malloc(sizeof(node));   //노드 생성
	newNode->value = data;
	newNode->next = NULL;

	if (head == NULL){  // 생성된 노드가 없는 경우 ( 첫 노드인 경우)
		head = newNode;
		return;  //호출한 곳으로 돌아간다. (함수 종료)
	}
	
	newNode->next = head;
	head = newNode;
}

void displayNode()
{
	node* curNode;  // 방문한 노드의 주소를 저장하는 변수
	if (head == NULL) //생성된 노드가 없는 경우
		return; // 함수 종료
	curNode = head; // 첫 번째 노드를 방문 노드로 설정

	while (curNode->next != NULL)  //다음 노드가 있다면 계속 진행
	{
		printf("%d => ", curNode->value); // 방문한 노드의 값을 출력
		curNode = curNode->next;  //방문 노드를 다음 노드로 이동
	}

}


int getNodeCount()
{
	int count = 0;  // 카운트 변수
	node* curNode; //방문 노드의 주소를 저장하는 포인터
	if (head == NULL)  // 생성된 노드가 없으면?
		return 0;   // 카운트는 0
	
	//노드의 개수를 구해 리턴
	curNode = head;

	while (curNode != NULL) //방문 노드가 있다면
	{
		++count;
		curNode = curNode->next;
	}

	return count;
}

