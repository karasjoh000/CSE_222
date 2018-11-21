/* John Karasev CSE 224 Intro To Data Structures January 11, 2017

   PROGRAM DESCRIPTION:
   This program accepts numbers and inserts
   them into a linked list that sorts them from least to
   greatest automatically. The user can also delete a node insert
   a node and search for a node(number).  By defualt the program accepts 100
   numbers. You can change this by changinging the defined
   number for LIST_SIZE found in header.h.

   HOW TO USE:
   let number be some number
   to insert a number use:
   > i number
   to search for a number use:
   > s number
   to delete a number use:
   > d number
   to exit program use:
   > x                                    */
#include <stdio.h>
#include <string.h>
#include "header.h"//where all defs are.
int main(void) {
	struct node list[LIST_SIZE];
	char buffer[20];
	int num;
	char cmd;
	int result;
	char space;
	init(list);
	usage();
	while(1) {
		printf(">");
		fgets(buffer, 19, stdin); //read input
		result = sscanf(buffer,"%c%c%d",&cmd,&space,&num);//parse input
//		printf("cmd = %c      num = %d   result = %d  space|%c| \n", cmd, num, result,space);
		if(((cmd!='i')&&(cmd!='s')&&(cmd!='d')&&(cmd!='p')&&(cmd!='x'))||
		(((cmd=='i')||(cmd=='d')||(cmd=='s'))&&(result!=3))||
		((space!=' ')&&((cmd=='i')||(cmd=='s')||(cmd=='d')))||
		(((cmd=='p')||(cmd=='x'))&&(result!=2)&&(space!=' '))){//if wrong input display synopsis
			usage();
		}
		//check what command was issued and do the correct operations for each case
		else if(cmd == 'x')
			break;
		else if(cmd == 'i') {
			result = add(list, num);
			if(result==1) printf("SUCCESS\n");
			else printf("NODE ALREADY IN LIST\n");
		}
		else if(cmd == 'p')
			print(list);
		else if(cmd == 'd') {
			result = delete(list,num);
			if (result==1) printf("SUCCESS\n");
			else printf("NODE NOT FOUND\n");
		}
		else {
			result = search(list, num);
			if(result==1) printf("FOUND\n");
			else printf("NOT FOUND\n");
		}

	}
	return 0;
}

/* void usage(void); - this function prints the synopsis of the program*/
void usage(void) {
	printf("                 SYNOPSIS OF LEGAL COMMANDS:\n");
        printf("i number | insert a number where number is any legal integer\n");
        printf("p        | print the numbers in the list in order\n");
        printf("s number | search a number where number is any real integer\n");
        printf("d number | delete a number where number is any real integer\n");
        printf("x        | exit the program\n");
}
/* void init(NODE*)  This function initiailizes the list by setting the array index to 0,
with next set to MYNULL. All valid flags in all other nodes are set to zero. */
void init(struct node *x) {
        int index = 0;
        x[index].valid = 1;
        x[index].next = MYNULL; //sentinol
        index++;
        for(index=1;index<LIST_SIZE;index++) { //sets all valids to zero except the first element
        x[index].valid = 0;
        }
}
/* void init(NODE*)  This function initiailizes the list by setting the array index to 0,
with next set to MYNULL. All valid flags in all other nodes are cleared. */
int get_node(struct node *ptr) {
	int index=1;
	while(index != LIST_SIZE){
		if(ptr[index].valid == 0) return index;//if valid is 0 return index
		index++;
	}
	return MYNULL; //returns 0 if no valid = 0 were found before MYNULL (list full)
}
/*void release_node(struct node *, int); - changes a flag to zero
of a deleted node given the node index*/
void release_node(struct node *ptr, int index) {
	ptr[index].valid=0;//set flag of index to zero
	return;
}
/*int delete(struct node*, int); - deletes a node from the list given a
number and swaps next fields in the nodes around. Returns 1 if success and
0 if number is not found.*/
int delete(struct node *ptr, int num) {
	int this_node = 0;
	int next_node = ptr[0].next;
	while(next_node != MYNULL) {
		if(num == ptr[next_node].data) { //if num is found
			ptr[this_node].next= ptr[next_node].next;
			release_node(ptr, next_node);
			return 1;
		}
		this_node = next_node;//shifts along the list to find num
		next_node = ptr[this_node].next;
	}
	return 0;
}
/*void print(struct node*); - prints the numbers in the list
in order from least to greatest. */
void print(struct node* ptr) {
	int this_node=0;
	int next_node = ptr[this_node].next;
	while(next_node != MYNULL) { //loop until MYNULL to print nums
		printf("%d ", ptr[next_node].data);
		this_node=next_node;
 		next_node = ptr[this_node].next;
	}
	printf("\n");
	return;
}

/* int search(struct node*,int) - searches for number given. return 1 if found
and 0 if number not found. */
int search(struct node* ptr, int num){
	int this_node = 0;
	int next_node;
	next_node = ptr[0].next;
	while(next_node != MYNULL) {
		if(ptr[next_node].data == num) return 1;//return 1 if found
		this_node=next_node; //shift along the list to next num
		next_node = ptr[this_node].next;
	}
	return 0; //otherwise if not found until MYNULL return 0;
}

/* int add(NODE* , int); This function adds a number into a list automatically
putting it in the right order (least to greatest). Returns 1 if success and 0 if no success(no more space or number already exists).  */
int add(struct node* ptr, int num) {
	int this_node = 0;
	int next_node =  ptr[this_node].next;
	int new_node;
	if(search(ptr, num) == 1) {
		 return 0; //if number already exists return 0
	}
	while(next_node!=MYNULL) {
		if(num > ptr[next_node].data){
			this_node = next_node; //if num is bigger than next_node shift
			next_node = ptr[this_node].next;//down the list
		}
		else
			return swap(ptr,this_node,new_node,next_node,num); //sub routine that swaps the next fields and sets num to node and valid to 1

	}
	return swap(ptr,this_node,new_node,next_node,num);//this is the case where num is the biggest in the list
}

/*int swap(struct node*, int,int,int,int); - swaps takes the nodes
  to be reranged also gets new node and adds new num to it*/
int swap(struct node *ptr, int prev, int new, int next, int num) {
	new = get_node(ptr);
	ptr[prev].next=new;
	ptr[new].next = next; //swap, valid=0 , and data=num
	ptr[new].data = num;
	ptr[new].valid = 1;
	return 1;
}
