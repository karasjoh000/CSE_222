#include<stdio.h>
#include"header.h" 
int main() { 
	struct node list[100]; 
	init(list); 
	list[0].next=1; 
	list[1].data=1; 
	list[1].next=2; 
	list[2].data=5; 
	list[2].next=3; 
	list[3].data=10; 
	list[3].next=MYNULL; 
	printf("%d result",search(list,11));
	return 0; 
} 

	
