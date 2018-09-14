#include <iostream>
#include<math.h>
#include<conio.h>
#include<stdlib.h>

using namespace std;


//****************************************************************
//*********** Queue

struct myStack
{
   int data;
   int priority;
   struct myStack *next;
}*top = NULL;//constructor

bool myEmptyStack()
{
    if(top==NULL)
        return true;
        else
            return false;
}

void push(int value, int priority)
{
   struct myStack *newStack;//creates new node
   newStack = (struct myStack*)malloc(sizeof(struct myStack));//allocates needed memory
   newStack->data = value;
   newStack->priority= priority;
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


int getLeastPriority()
{
    struct myStack *temp = top;
    int minPriorityValue= temp->priority;
    int minPriorityElement= temp ->data;
    if(top == NULL)
        cout<<endl<<"Stack is Empty"<<endl;
    else
    {
        while(temp->next != NULL)
        {
            if(minPriorityValue>temp->priority)
            {
                minPriorityValue=temp->priority;
                minPriorityElement=temp ->data;
            }
            temp=temp->next;
        }
    }
    return(minPriorityElement);
}
int main()
{
    int value, priority, myCount=0, numberOfElements=0, leastPriority;
    cout<<"Enter how many values you want to enqueue: ";
    cin>>numberOfElements;
    while(myCount<numberOfElements)
    {
        cout<<"Enter a value you want to add into queue with its priority in this format( value \t priority):";
        cin>>value>>priority;
        push(value, priority);
        cout<<endl;
        myCount++;
    }
    leastPriority=getLeastPriority();
    cout<<"The element with the least priority is: "<<leastPriority;

    while (1);
    return 0;
}
