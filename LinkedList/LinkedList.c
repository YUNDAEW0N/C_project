#include <stdio.h>

//Node 구조체
typedef struct node {
	int value; // 값을 저장하는 변수
	struct node* next; //다음 노드의 주소를 저장
	//다음 노드는 struct node 타입임으로 다음 노드의 주소는 struct node 타입의 주소임으로 struct node* 로 next를 선언한다.
}node; // 이름 재정의 ( 안하면 struct node 라고 계속 써야한다)


//NULL : 포인터가 가리키는 대상이 없는 경우
node* head = NULL; // 첫 노드의 주소를 저장하는 변수 8byte 포인터

void insertFrontNode(int data)
{
	node* newNode;  // 생성된 노드의 주소를 저장하는 변수
	newNode = (node*)malloc(sizeof(node));   //노드 생성
	newNode->value = data;
	newNode->next = NULL;

	if (head == NULL) {  // 생성된 노드가 없는 경우 ( 첫 노드인 경우)
		head = newNode;
		return;  //호출한 곳으로 돌아간다. (함수 종료)
	}

	newNode->next = head;
	head = newNode;
}

void insertTailNode(int data)
{
	node* newNode; //생성된 노드의 주소를 저장하는 포인터 변수
	node* curNode; // 방문 노드의 주소를 저장하는 포인터 변수
	newNode = (node*)malloc(sizeof(node)); // 노드 생성
	newNode->value = data;
	newNode->next = NULL;

	if (head == NULL) {  // 연결 리스트가 구성되지 않았으면
		head = newNode;
		return;
	}

	//연결리스트 순회 -> 마지막 노드에 위치
	curNode = head;

	while (curNode->next != NULL)
		curNode = curNode->next;

	curNode->next = newNode; // 마지막 노드와 새노드를 연결
}

void displayNode()
{
	node* curNode;  // 방문한 노드의 주소를 저장하는 변수
	if (head == NULL) //생성된 노드가 없는 경우
		return; // 함수 종료
	curNode = head; // 첫 번째 노드를 방문 노드로 설정

	while (curNode->next != NULL)  //다음 노드가 있다면 계속 진행 (마지막 노드 포함x)
	{
		printf("%d => ", curNode->value); // 방문한 노드의 값을 출력
		curNode = curNode->next;  //방문 노드를 다음 노드로 이동
	}

	printf("%d\n", curNode->value); // 마지막 노드 출력

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
		++count; //노드의 개수를 1씩 증가
		curNode = curNode->next; // 방문노드를 다음노드로 이동
	}

	return count;

}

void removeNodeFront()
{
	node* delNode; // 삭제할 노드의 주소를 저장하는 포인터 변수
	if (head == NULL) //연결 리스트가 구성 되기 전
		return; //함수 종료

	//1. 첫번째 노드를 삭제할 노드로 설정
	delNode = head;
	//2. head를 다음 노드로 이동
	head = head->next;
	//3. 첫 번째 노드 제거
	free(delNode);
}

void removeNodeValue(int target)
{
	node* delNode; // 삭제할 노드의 주소를 저장하는 포인터 변수
	node* prevNode; // 이전 노드의 주소를 저장하는 포인터 변수
	if (head == NULL)
		return;

	//삭제할 노드가 첫 노드인 경우
	if (head->value == target)
	{
		delNode = head;
		head = head->next;
		free(delNode);
		return;
	}
	//중간에 있는 경우
	//순회하면서 삭제할 노드 검색
	prevNode = head;
	delNode = head;

	while (prevNode->next != NULL)
	{
		delNode = prevNode->next;
		if (delNode->value == target)
		{
			prevNode->next = delNode->next;
			free(delNode);
			return;
		}
		prevNode = delNode;
	}
}

void memoryFree()
{
	node* delNode;  // 삭제할 노드의 주소를 저장하는 포인터 변수
	if (head == NULL) // 연결 리스트가 비어있으면
		return; // 함수 종료

	//모든 노드 제거 : 첫번째 노드를 제거 => 반복
	while (head != NULL) // 삭제할 노드가 없을때까지
	{
		delNode = head;
		head = head->next;
		free(delNode);
	}
}


int main()
{
	int choice;
	int data;
	int count;
	while (1)
	{
		system("cls");
		printf("\n\n  *** 단일 연결 리스트(Singly Linked List) ***\n\n");
		printf("=====================================\n");
		printf(" 1. 맨 앞 삽입\n");
		printf(" 2. 맨 뒤 삽입\n");
		printf(" 3. 앞에서부터 N번째 삽입\n");
		printf(" 4. 오름차순 정렬 삽입\n");
		printf("=====================================\n");
		printf(" 5. 맨 앞 삭제\n");
		printf(" 6. 맨 뒤 삭제\n");
		printf(" 7. 전체 노드 삭제\n");
		printf(" 8. 특정 값 삭제\n");
		printf(" 9. 앞에서부터 N번째 삭제\n");
		printf("=====================================\n");
		printf("10. 단일 연결 리스트 출력(노드 순회)\n");
		printf("11. 노드의 개수 구하기\n");
		printf("12. 노드 검색\n");
		printf(" 0. 프로그램 종료\n");
		printf("=====================================\n");
		printf("\n메뉴 선택 : ");
		scanf("%d", &choice);
		while (getchar() != '\n');

		switch (choice)
		{
		case 1:
			printf("\n\n정수 입력 : ");
			scanf("%d", &data);
			insertFrontNode(data);
			break;
		case 2:
			printf("\n\n정수 입력 : ");
			scanf("%d", &data);
			insertTailNode(data);
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			removeNodeFront();
			break;
		case 6:
			break;
		case 7:
			memoryFree();
			break;
		case 8:
			printf("\n\n삭제할 값 입력 : ");
			scanf("%d", &data);
			removeNodeValue(data);
			break;
		case 9:
			break;
		case 10:
			displayNode();
			break;
		case 11:
			count = getNodeCount(); //노드의 개수를 구해 리턴하는 함수
			printf("\n\n\t\t생성 된 노드의 개수는 %d개 입니다.\n", count);
			break;
		case 12:
			break;
		case 0:
			memoryFree();
			exit(0); //프로그램 강제 종료
		}//end switch

		//switch문을 빠져 나오면 일시 대기 시킨다.
		printf("\n\n\t\t");
		system("pause"); //일시 대기

	}//end while
	return 0;
}
