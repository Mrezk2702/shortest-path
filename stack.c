#include "STD_TYPES.h"

typedef struct node
{
    u8 dir;
    struct node *nx;
}node;

node *head=NULL;

void push (u8 val)
{
    if (head==NULL)
    {
        head=(node*)malloc(sizeof(node));
        head->dir=val;
        head>nx=NULL;
        
    }
    else
    {
        node *temp=(node*) malloc(sizeof(node));
        temp->dir=val;
        temp->nx=head;
        head=temp
    }
}

void pop(void)
{
    head=head->nx;   
}