#include <iostream>
#include<math.h>
#include<conio.h>
#include<stdlib.h>

using namespace std;

//****************************************************************
//*********** Stack
struct myStack
{
   int data;
   struct myStack *next;
}*top = NULL;//constructor

bool myEmptyStack()
{
    if(top==NULL)
        return true;
        else
            return false;
}

void push(int value)
{
   struct myStack *newStack;//creates new node
   newStack = (struct myStack*)malloc(sizeof(struct myStack));//allocates needed memory
   newStack->data = value;
   if(top == NULL)
      newStack->next = NULL;
   else
      newStack->next = top;
   top = newStack;
}

void pop()
{
    bool isEmpty;
    isEmpty=myEmptyStack();
    if(isEmpty==true)
      cout<<endl<<"Stack is empty"<<endl;
    else
    {
      struct myStack *temp = top;
      //printf("\nDeleted element: %d", temp->data);
      cout<<endl<<"Deleted element "<<temp->data;
      top = temp->next;
      free(temp);
    }
}

void displayStack()
{
   if(top == NULL)
      cout<<endl<<"Stack is Empty"<<endl;
   else{
      struct myStack *temp = top;
      while(temp->next != NULL)
        {
            cout<<"---> "<<temp->data;
            temp = temp -> next;
        }
      cout<<endl<<"---> "<<temp->data;
   }
}

//****************************************************************
//*********** Queue
//Still incomplete trying different implementations
struct myQueue
{
   int data;
   struct myQueue *next;
}*myFront = NULL,*myRear=NULL;//constructor

bool myEmptyQueue()
{
    if(myRear==NULL)
    {
        return true;
    }
    else
        return false;
}

void enQueue(int value)
{
    struct myQueue *newQueue;
    bool isEmpty;
    isEmpty=myEmptyQueue();
    newQueue->next=NULL;
    if(isEmpty==true)
    {
        myFront= newQueue;
        myRear= newQueue;
    }
    else
    {
        myRear->next=newQueue;
        myRear= newQueue;
    }
}
int main()
{
   int choice, value;
   cout<<endl<<"::Stack using Linked List ::"<<endl;
   while(1){
      cout<<endl<<"****** MENU ******"<<endl;
      cout<<"1. Push"<<endl<<"2. Pop"<<endl<<"3. Display"<<endl<<"4. Exit"<<endl;
      cout<<"Enter your choice: ";
      cin>>choice;
      switch(choice){
	 case 1: cout<<"Enter the value to be inserted: ";
        cin>>value;
        push(value);
        break;
	 case 2: pop(); break;
	 case 3: display(); break;
	 case 4: exit(0);
	 default: cout<<endl<<"Wrong selection!!! Please try again!!!"<<endl;
      }
   }

    return 0;
}
