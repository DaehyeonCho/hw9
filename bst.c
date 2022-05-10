/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node { 
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)    // 중위순회 (LVR)
{
	if(ptr) {
		inorderTraversal(ptr->left);    // leftchild 탐색
		printf(" [%d] ", ptr->key);     // 부모노드 값 출력
		inorderTraversal(ptr->right);   // rightchild 탐색
	}
}

void preorderTraversal(Node* ptr)   // 전위순회 (VLR)
{
	if(ptr) {
		printf(" [%d] ", ptr->key);     // 부모노드 값 출력
		preorderTraversal(ptr->left);   // leftchild 탐색
		preorderTraversal(ptr->right);  // rightchild 탐색
	}
}

void postorderTraversal(Node* ptr)      // 후위순회 (LRV)
{
	if(ptr) {
		postorderTraversal(ptr->left);  // leftchild 탐색
		postorderTraversal(ptr->right); // rightchild 탐색
		printf(" [%d] ", ptr->key);     // 부모노드 값 출력
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));	// 삽입할 노드 생성
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {	// 이진트리가 공백일 때
		head->left = newNode;
		return 1;
	}

	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		if(ptr->key == key) return 1;	// 삽입하려는 key가 이미 있으면 안됨

		parentNode = ptr;

		if(ptr->key < key)		// ptr과 삽입하려는 key 비교
			ptr = ptr->right;	// key가 더 크면 오른쪽 서브트리로 이동
		else					// key가 더 작으면 왼쪽 서브트리로 이동
			ptr = ptr->left;
	}

	if(parentNode->key > key)	// 부모 노드의 key와 삽입하려는 key 비교
		parentNode->left = newNode;		// 부모 노드의 key가 더 크면 왼쪽에 삽입
	else
		parentNode->right = newNode;	// 부모 노드의 key가 더 작으면 오른쪽에 삽입
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {		// 이진트리에 메모리 할당이 되지 않았을 때 오류 메시지 출력
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {	// 이진트리가 공백일 때 오류 메시지 출력
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* ptr = head->left;
	Node* parentNode = head;

	while(ptr != NULL) {

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {	// 삭제하려는 노드의 자식 노드가 없을 때

				if(parentNode == head)	// 삭제하려는 노드가 루트 노드일 때
					head->left = NULL;	// 루트 노드 삭제

				if(parentNode->left == ptr)		// 삭제하려는 노드가 왼쪽 자식일 때
					parentNode->left = NULL;
				else
					parentNode->right = NULL;	// 삭제하려는 노드가 오른쪽 노드일 때

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);	// 삭제하려는 노드가 자식 노드가 있을 때 오류 메시지 출력
			}
			return 1;
		}

		parentNode = ptr;

		if(ptr->key < key)		// 이진트리의 노드와 key 비교
			ptr = ptr->right;	// key가 더 크면 포인터를 오른쪽 자식 노드로 이동
		else
			ptr = ptr->left;	// key가 더 작으면 포인터를 왼쪽 자식 노드로 이동
	}

	printf("Cannot find the node for key [%d]\n ", key);	// 삭제하려는 키가 존재하지 않을 때 오류 메시지 출력

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)
		return NULL;

	if(ptr->key < key)		// 찾으려는 key가 노드의 key보다 클 때
		ptr = searchRecursive(ptr->right, key);	// 오른쪽 자식 노드로 이동해 계속 탐색
	else if(ptr->key > key)	// 찾으려는 key가 노드의 key보다 작을 때
		ptr = searchRecursive(ptr->left, key);	// 왼쪽 자식 노드로 이동해 계속 탐색

	return ptr;

}
Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left;

	while(ptr != NULL)	
	{
		if(ptr->key == key)		// 해당 key를 찾았을 경우 포인터 값 반환
			return ptr;

		if(ptr->key < key) 		// 찾으려는 key가 노드의 key보다 클 때
			ptr = ptr->right;	// 오른쪽 자식 노드로 이동
		else					// 찾으려는 key가 노드의 key보다 작을 때
			ptr = ptr->left;	// 왼쪽 자식 노드로 이동
	}

	return NULL;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;	// 루트 노드 삭제

	freeNode(p);

	free(head);
	return 1;
}





