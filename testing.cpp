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

void push(int value)
{
   struct myStack *newStack;//creates new stack
   newStack = (struct myStack*)malloc(sizeof(struct myStack));//allocates needed memory
   newStack->data = value;
   if(top == NULL)
      newStack->next = NULL;
   else
      newStack->next = top;
   top = newStack;
   cout<<endl<<"insertion is successful"<<endl;
}

void pop()
{
    if(top==NULL)
      cout<<endl<<"Stack is empty"<<endl;
    else
    {
      struct myStack *temp = top;
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
      cout<<endl<<temp->data<<" ---> NULL ";
   }
}

//****************************************************************
//*********** Queue

struct myQueue
{
   int data;
   struct myQueue *next;
}*myFront = NULL,*myRear=NULL;//constructor

void enQueue(int value)
{
    struct myQueue *newQueue;
    newQueue=(struct myQueue*)malloc(sizeof(struct myQueue));
    newQueue->data=value;
    newQueue->next=NULL;
    if(myFront==NULL)
    {
        myFront= myRear= newQueue;
    }
    else
    {
        myRear->next=newQueue;
        myRear= newQueue;
    }
    cout<<endl<<"Insertion successful"<<endl;
}

void deQueue()
{
    if(myFront==NULL)
    {
        cout<<endl<<"Que is Empty! Deletion not possible"<<endl;
    }
    else
    {
        struct myQueue *temp=myFront;
        myFront=myFront->next;
        cout<<temp->data<<" was deleted"<<endl;
        free(temp);
    }
}

void displayQueue()
{
   if(myFront == NULL)
        cout<<endl<<"Queue is empty"<<endl;
   else{
      struct myQueue *temp = myFront;
      while(temp->next != NULL){
        cout<<temp->data<< " ----->";
        temp = temp -> next;
      }
      cout<<temp->data<< "-----> NULL";
   }
}

int main()
{
    int choice1,choice2, value,answer;
    cout<<"Do you want to work with stacks or queues?(1 for stack 2 for queues 0 to exit): ";
    cin>>answer;
        switch(answer)
        {
        case 1:
            {
                cout<<endl<<":: Stack using Linked List ::"<<endl;
                cout<<endl<<"****** MENU ******"<<endl;
                cout<<endl<<"1. Push"<<endl<<"2. Pop"<<endl<<"3. Display"<<endl<<"4. Exit"<<endl;
                cout<<"Enter your choice: "<<endl;
                cin>>choice1;
      switch(choice1){
        case 1: cout<<"Enter the value to be inserted: ";
		 cin>>value;
		 push(value);
		 break;
        case 2: pop(); break;
        case 3: displayStack(); break;
        case 4: exit(0);
        default: cout<<endl<<"Wrong selection!!! Please try again!!!"<<endl;
        break;
            }

      }
        case 2:
           cout<<endl<<":: Queue using Linked List ::"<<endl;
            cout<<endl<<"****** MENU ******"<<endl;
            cout<<endl<<"1. EnQueue"<<endl<<"2. Dequeue"<<endl<<"3. Display"<<endl<<"4. Exit"<<endl;
            cout<<"Enter your choice: "<<endl;
            cin>>choice2;
            switch(choice1){
                case 1: cout<<"Enter the value to enqueue: ";
                            cin>>value;
                            enQueue(value);
                            break;
                case 2: deQueue(); break;
                case 3: displayQueue(); break;
                case 4: exit(0);
                default: cout<<endl<<"Wrong selection!!! Please try again!!!"<<endl;
                break;
            }
        case 3: cout<<endl<<"Wrong selection!!! Please try again!!!"<<endl;break;
        case 4: exit(0);
    }

}
