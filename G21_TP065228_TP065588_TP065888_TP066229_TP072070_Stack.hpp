#pragma once
#include<iostream>

using namespace std;

struct AnsweredQuestion
{
    string question;
    AnsweredQuestion* nextadddress;
};

class AnsweredQuestionsStack
{
    AnsweredQuestion* top, *bottom;
    int size;

public: 
    AnsweredQuestionsStack()
    {
        top = bottom = nullptr;
        size = 0;
    }

    ~AnsweredQuestionsStack()
    {
        AnsweredQuestion* current = top;
        while (current != nullptr) {
            AnsweredQuestion* next = current->nextadddress;
            delete current;
            current = next;
        }
    }

    bool isEmpty()
    {
        if (top == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void push(string answeredquestion)
    {
        AnsweredQuestion* newQuestion = new AnsweredQuestion;
        newQuestion->question = answeredquestion;
        newQuestion->nextadddress = nullptr;

        if (top == nullptr)
        {
            top = bottom = newQuestion;
        }
        else
        {
            newQuestion->nextadddress = top;
            top = newQuestion;
        }

        cout << "Question added to answered deck" << endl;
        size++;
    }

    bool allQuestionsAnswered()
    {
        if (size == 300)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow!" << endl;
            return;
        }

        AnsweredQuestion* current = top;
        top = top->nextadddress;
        if (top == nullptr)
        {
            bottom = nullptr;
        }
        delete current;
        size--;
    }


    string peekTopofDeck()
    {
        return top->question;
    }

};


