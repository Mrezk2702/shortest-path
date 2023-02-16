#include <stdio.h>
#include "STD_TYPES.h"
#include <stdlib.h>
#include<conio.h>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define ZERO 5
typedef struct node{
	/*x,y are coordinates
	  stats-> indicates whether the node are parent or a child */
	u8 x,y,state,count,path;
	struct node *nx;
	struct node *prv;
	struct
	{
		/*bits that represents directions*/
		u8 d_up : 1;
		u8 d_down : 1;
		u8 d_left : 1;
		u8 d_right : 1;
	}directions;
	struct 
	{
		u8 z:2;
	}no_back;


}node; 
node *head = NULL;
node *tail = NULL;
u8 opp;
u8 i,j;


u8 arr[4][4]={{1,ZERO,1,1},
			  {ZERO,ZERO,1,1},
			  {1,ZERO,ZERO,ZERO},
			  {1,1,1,ZERO}};


void insert_last(node *); /*inserts a node to the stack*/
void check_Fwd (void);
void move_Fwd(void);
void traverse_back(void);
void print_stack(void);
u8 no_Back(u8 value);


void main (void)
{   
	i=0,j=1;
        do{
			check_Fwd();
		}while(i!=3);
    print_stack();

}




void check_Fwd (void)
{
	node *temp =(node *)malloc(sizeof(node));
	temp->directions.d_down=0;
	temp->directions.d_up=0;
	temp->directions.d_right=0;
	temp->directions.d_left=0;
	
	if (arr[i][j+1]==ZERO && RIGHT != opp) /*Checking if there's a path available in right side*/
	{
		temp->count=temp->count+1; /*incrementing the value of available paths*/
		temp->directions.d_right=1;
	}
	if(arr[i][j-1]==ZERO && LEFT!=opp)/*Checking if there's a path available in left side*/
	{
		temp->count=temp->count+1; /*incrementing the value of available paths*/
		temp->directions.d_left=1;
	}
	if(arr[i+1][j]==ZERO && DOWN!=opp)temp->count=temp->count+1;/*incrementing the value of available paths*/
		temp->directions.d_down=1;
	{
		temp->count=temp->count+1;/*incrementing the value of available paths*/
		temp->directions.d_down=1;
		
	}
	if(i>0) /*First row doesn't have up movement*/
	{
		if(arr[i-1][j]==ZERO&& UP !=opp) /*Checking if there's a path available in Up side*/
		{
		temp->count=temp->count+1;/*incrementing the value of available paths*/
		temp->directions.d_up=1;
		}
	}

	if (temp->count==1) /*Normal node*/
	{
		temp->state=0;
	}
	if (temp->count>1) /*Parent node*/
	{
		temp->state=1;
	}
	temp->x=j; /*Assigning coordinates to the node*/
	temp->y=i;
	insert_last(temp);
	move_Fwd();
}


void insert_last(node * elem) /*Attaching the passed node to the end of the list*/
{

	if(head==NULL&&tail==NULL) /*check the list of it's empty*/
	{
		head=elem;
		tail=elem;
		head->nx=NULL;
		head ->prv=NULL;
	
	}
	else
	{
		tail->nx=elem;
		elem->prv=tail;
		tail=elem;
		tail->nx=NULL;

	}
}


void move_Fwd(void)
{
	if(tail->directions.d_right) /*Go to right if true*/
	{
		printf("Going right!\n");
		opp=no_Back(RIGHT);
		tail->path=RIGHT;
		tail->directions.d_right=0;
		j++;
	}
	else if(tail->directions.d_left)/*Go  left if true*/
	{
		printf("Going left!\n");
		tail->path=LEFT;
		opp=no_Back(LEFT);
		tail->directions.d_left=0;
		j--;
	}
	else if(tail->directions.d_down) /*Go down*/
	{
		printf("Going down!\n");
		opp=no_Back(DOWN);
		tail->path=DOWN;
		tail->directions.d_down=0;
		i++;
	}
	else if(tail->directions.d_up) /*Go up*/
	{
		printf("Going up !\n");
		opp=no_Back(UP);
		tail->path=DOWN;
		tail->directions.d_up=0;
		i--;
	}
	else
	{
		if (i==3&j==2) /*destination reached*/
		{
			printf("Destination reached !!\n");
		}
		printf("Surrounded by ones\n");
		printf("Going back to parent..\n");
		print_stack();
		traverse_back();
	}
}
void traverse_back(void) /*this function let's you go to the parent node*/
{
	node * curr=tail;
	do
	{
		curr=curr->prv;
		free(curr->nx);
	}
	while(curr->state!=1);/*Checking the parent node*/
	tail=curr;
	i=tail->y;
	j=tail->x;
	move_Fwd();
}
void print_stack(void)
{
	node* temp=head;
	while(temp->nx!=NULL)
	{
		printf(" x = %d y = %d available paths: %d\n",temp->x,temp->y,temp->path);
		temp=temp->nx;
	}
	printf(" x = %d y = %d available paths: %d\n",temp->x,temp->y,temp->path);

}

u8 no_Back(u8 value)
{
	  node * temp= (node *) malloc(sizeof(node));
	  temp->no_back.z=value;
	  temp->no_back.z+=2;
	  return temp->no_back.z;
}