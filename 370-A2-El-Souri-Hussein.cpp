// Assignment2.cpp : Defines the entry point for the console application.

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <sstream>

using namespace std;

/// A string array with a size specifier
class File
{
public:
	int numLines;
	string* lineArray;
};

class Stack
{
	int top;
	int sizeOfStack;
	string* stack;
public:
	Stack(); //Creates 20-element array
	Stack(int); //Creates specific size array

	bool Empty(); //Returns true if empty
	bool Push(string); //Returns true if value added
	string Top();
	bool Pop(); //Returns true if value removed
	void Display();
};

/// Create to_string function (this wasn't needed in Visual Studio)
std::string to_string(float i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}

Stack::Stack()
{
	top = -1;
	sizeOfStack = 72;
	stack = new string[sizeOfStack];
}

Stack::Stack(int size)
{
	top = -1;
	sizeOfStack = size;
	stack = new string[sizeOfStack];
}

bool Stack::Empty()
{
	if (top == -1)
		return true;
	else
		return false;
}

bool Stack::Push(string value)
{
	if (top == sizeOfStack - 1)
	{
		return false;
	}
	else
	{
		++top;
		stack[top] = value;
		return true;
	}
}

string Stack::Top()
{
	if (Empty())
    {
        return "";
    }

	else
    {
        return stack[top];
    }

}

bool Stack::Pop()
{
	if (Empty())
	{
		return false;
	}
	else
	{
		top--;
		return true;
	}
}

void Stack::Display()
{
	for (int i = 0; i <= top; i++)
	{
		cout << stack[i];
	}
	cout << endl;
}

class Queue
{
	int front;
	int rear;
	int count;
	int sizeOfQueue;
	string* queue;
public:
	Queue();
	Queue(int);

	bool Dequeue();
	bool Enqueue(string);
	string First();
	bool IsEmpty();
	int Size();
	void Display();
};

Queue::Queue()
{
	front = 0;
	rear = 0;
	count = 0;
	sizeOfQueue = 72;
	queue = new string[sizeOfQueue];
}

Queue::Queue(int size)
{
	front = 0;
	rear = 0;
	count = 0;
	sizeOfQueue = size;
	queue = new string[sizeOfQueue];
}

bool Queue::Dequeue()
{
	if (IsEmpty())
	{
		return false;
	}
	else
	{
		front = (++front) % sizeOfQueue;
		count--;
		return true;
	}
}

bool Queue::Enqueue(string value)
{
	if (count == sizeOfQueue)
	{
		return false;
	}
	else
	{
		queue[rear] = value;
		rear = (++rear) % sizeOfQueue;
		++count;
		return true;
	}
}

string Queue::First()
{
	if (IsEmpty())
	{
		return "";
	}
	else
	{
		return queue[front];
	}
}

bool Queue::IsEmpty()
{
	if (count == 0)
		return true;
	else
		return false;
}

int Queue::Size()
{
	return count;
}

void Queue::Display()
{
	int index = front;
	for (int i = 0; i <= count-1; i++)
	{
	    cout << queue[index];
		index = (++index) % sizeOfQueue;
	}
	cout << endl;
}

/// Reads a file into a File object
/// Each line of the file is an array element within File object
File readFile(string fileName)
{
	ifstream fileIn;
	fileIn.open(fileName.c_str()); // Open file

	if (!fileIn) // Ends program if problem with file
	{
		cout << "Unable to open a2.txt";
	}

	string temp;
	int numLines = 0; // Counter to keep track of lines
	while (getline(fileIn, temp))
	{
		if (temp != "")
		{
			++numLines;
		}
	}

	fileIn.clear();
	fileIn.seekg(0, ios::beg); // Go back to top of file

	string* infixLines = new string[numLines];

	for (int i = 0; i < numLines; i++)
	{
		getline(fileIn, infixLines[i]);
	}

	File result;
	result.lineArray = infixLines;
	result.numLines = numLines;

	fileIn.close();

	return result;
}

/// Checks type of character
/// Returns 0 for "("
/// Returns 1 for ")"
/// Returns 2 for operator
/// Returns 3 for others (including operands)
int checkType(string in)
{
	if (in == "(")
		return 0;
	else if (in == ")")
		return 1;
	else if ((in == "*") || (in == "/") || (in == "+") || (in == "-") || (in == "^"))
		return 2;
	else
		return 3;
}

/// Returns higher value for higher precedence
int getPrecedence(string in)
{
	if ((in == "+") || (in == "-"))
	{
		return 0;
	}
	else if ((in == "*") || (in == "/"))
	{
		return 1;
	}
	else if (in == "^")
	{
		return 2;
	}
	else
	{
		cout << "getPrecedence received an invalid character";
		return 99;
	}
}

/// Moves a single value from the top of the stack to the back of the queue
void stackToQueue(Stack* myStack, Queue* myQueue)
{
	bool result = myQueue->Enqueue(myStack->Top());
	if (!result)
	{
		cout << "Error enqueuing " << myStack->Top() << " to queue" << endl;
	}

	result = myStack->Pop();
	if (!result)
	{
		cout << "Error popping " << myStack->Top() << " from stack" << endl;
	}
}

/// Takes in a File object and Queue array pointer
/// Goes through each line of the file object and converts it to a postfix expression
/// The postfix expression exists in a local queue
/// The local queue is added to queue array
void infixToPostfix(File fileIn, Queue* queueIn)
{
    cout << "--------------- Assignment 2 -------------- "<< endl;
	for (int i = 0; i < fileIn.numLines; i++)
	{
		Stack myStack;
		Queue myQueue;

		for (int j = 0; j < fileIn.lineArray[i].length(); j++)
		{
			// each character of the string is accessed with fileIn.lineArray[i]
			string currentLine = fileIn.lineArray[i]; // Get each characrter as a string
			string currentChar = currentLine.substr(j, 1);

			switch (checkType(currentChar)) // 0=(  1=)  2=operator  3=alphabet
			{
				case(0): // "("
				{
					bool result = myStack.Push(currentChar);
					if (!result)
					{
						cout << "Error pushing " << currentChar << " to stack" << endl;
					}

					break;
				}
				case(1): // ")"
				{
					while (myStack.Top() != "(")
					{
						stackToQueue(&myStack, &myQueue);
					}

					bool result = myStack.Pop(); // Pop "("
					if (!result)
					{
						cout << "Error popping " << myStack.Top() << " from stack" << endl;
					}

					break;
				}
				case(2): // operator
				{
					while ((!myStack.Empty())&&(myStack.Top() != "(") &&(getPrecedence(myStack.Top()) >= getPrecedence(currentChar)))
					{
						stackToQueue(&myStack, &myQueue);
					}

					bool result = myStack.Push(currentChar);
					if (!result)
					{
						cout << "Error pushing " << currentChar << " to stack" << endl;
					}

					break;
				}
				case(3): // alphabet
				{
					bool result = myQueue.Enqueue(currentChar);
					if (!result)
					{
						cout << "Error enqueuing " << currentChar << " to queue" << endl;
					}
					break;
				}
				default:
				{
					cout << "Switchcase issue" << endl;
				}
			}
		}
		while (!myStack.Empty())
		{
			stackToQueue(&myStack, &myQueue);
		}
		queueIn[i] = myQueue;
	}
}

/// Performs the arithmetic operation on two numbers, and returns the result as a float
float performOperation(float x, float y, string op)
{
	float result;

	if (op == "+")
		result = x + y;
	else if (op == "-")
		result = x - y;
	else if (op == "*")
		result = x * y;
	else if (op == "/")
		result = x / y;
	else if (op == "^")
		result = pow(x, y);

	return result;
}

/// Takes in an array of queues, its size, and an array of stacks
/// Uses a stack to calculate the result of the postfix expression
/// Places the stack into an array of stacks
void evaluatePostfix(Queue* queueIn, int size, Stack* stackOut)
{
	for (int i = 0; i < size; i++)
	{
		Stack myStack;
		Queue myQueue = queueIn[i];

		while (!myQueue.IsEmpty())
		{
			int type = checkType(myQueue.First());

			if (type == 3) // If operand
			{
				bool result = myStack.Push(myQueue.First());
				if (!result)
				{
					cout << "Error pushing " << myQueue.First() << " to stack" << endl;
				}
				result = myQueue.Dequeue();
				if (!result)
				{
					cout << "Error dequeueing " << myQueue.First() << " from queue" << endl;
				}
			}
			else if (type == 2) // If operator
			{
				string yString = myStack.Top();
				bool result = myStack.Pop();
				if (!result)
				{
					cout << "Error popping " << myStack.Top() << " from stack" << endl;
				}
				string xString = myStack.Top();
				result = myStack.Pop();
				if (!result)
				{
					cout << "Error popping " << myStack.Top() << " from stack" << endl;
				}

				float y = atof(yString.c_str());
				float x = atof(xString.c_str());
				float ans = performOperation(x, y, myQueue.First());

				result = myQueue.Dequeue();
				if (!result)
				{
					cout << "Error dequeueing " << myQueue.First() << " from queue" << endl;
				}

				myStack.Push(to_string(ans));
			}
			else
			{
				cout << "Invalid character in queue" << endl;
			}
		}

		stackOut[i] = myStack;
	}
}


int main()
{
	string fileName = "a2.txt";
	File myFile = readFile(fileName); // Read file into File object

	Queue* myQueues = new Queue[myFile.numLines]; // Creates an array of Queues the size of numLines
	infixToPostfix(myFile, myQueues); // Takes in File object and queue array to fill each queue with the postfix expression

	Stack* myStacks = new Stack[myFile.numLines]; // Creates an array of stacks the size of numLines
	evaluatePostfix(myQueues, myFile.numLines, myStacks); // Takes in queue array and stack array to fill the stack array with the calculated result

	float sum = 0;
	for (int i = 0; i < myFile.numLines; i++)
	{
		cout << "Line " << i+1 << endl;
		cout << "  Original Infix Expression: " << myFile.lineArray[i] << endl;
		cout << "  Postfix Expression: ";
		myQueues[i].Display();
		cout << "  Result: ";
		myStacks[i].Display();
		sum += atof(myStacks[i].Top().c_str());
	}

	cout << "\nThe sum is: " << sum << endl;

    return 0;
}
