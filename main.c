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

		
		     
