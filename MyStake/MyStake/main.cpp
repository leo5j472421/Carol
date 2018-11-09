//
//  main.cpp
//  MyStake
//
//  Created by Leo Chu Ming on 2018/11/8.
//  Copyright © 2018 Carol. All rights reserved.
//

#include <iostream>
#include <string>
#define MAX 80
using namespace std;

struct MyStack
{
    int top;
    char s[MAX];
    bool IsEmpty();
    bool IsFull();
    void Push(char);
    char Pop();
    
    MyStack()
    {
        top=-1;
    }
};


bool MyStack::IsEmpty()
{
    if(top==-1)
        return true;
    else
        return false;
}

bool MyStack::IsFull()
{
    if(top==MAX-1)
        return true;
    else
        return false;
}

void MyStack::Push(char ch)
{
    if(IsFull()==true)
        printf("Stack is full. Cannot Push any element.\n");
    else
    {
        top++;
        s[top]=ch;
    }
}

char MyStack::Pop()
{
    char ch;
    if(IsEmpty()==true)
    {
        printf("Stack is Empty. Cannot pop any element.\n");
        return 0;
    }
    
    else
    {
        ch=s[top];
        top--;
        return ch;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "請輸入選項" << endl ;
    return 0;
}
