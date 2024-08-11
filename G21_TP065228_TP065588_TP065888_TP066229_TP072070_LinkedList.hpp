#pragma once
#include <iostream>


using namespace std;

struct DoublyLinkedListNode
{
	Student student;
	int ranking;
	DoublyLinkedListNode* next;
	DoublyLinkedListNode* prev;
};

class SortedStudentLinkedList
{
	DoublyLinkedListNode* head, * tail;
	int size;
	
public: 
	SortedStudentLinkedList()
	{
		size = 0;
		head = tail = nullptr;
	}

	~SortedStudentLinkedList()
	{
		while (head != nullptr)
		{
			DoublyLinkedListNode* temp = head;
			head = head->next;
			delete temp;
		}
	}

	DoublyLinkedListNode* createNewNode(Student student,int ranking)
	{
		DoublyLinkedListNode* newNode = new DoublyLinkedListNode();
		newNode->ranking = ranking;
		newNode->student = student;
		newNode->next = nullptr;
		newNode->prev = nullptr;

		return newNode;
	}

	bool isEmpty()
	{
		if (size == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void insertIntoList(Student student, int ranking)
	{
		DoublyLinkedListNode* newNode = createNewNode(student,ranking);

		if (head == nullptr)
		{
			head = tail = newNode;
		}
		else
		{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		size++;
	}

	void displayLinkedList()
	{
		DoublyLinkedListNode* current = head;
		while (current != nullptr)
		{
			cout << "| " << current->ranking << " | " << current->student.name << " | " << current->student.question1 << " | " << current->student.question2 << " | " << current->student.question3 << " |   |" << endl;
			cout << "|   | " << string(current->student.name.length(), ' ') << " | " << current->student.score1 << " | " << current->student.score2 << " | " << current->student.score3 << " | " << current->student.totalscore << " |" << endl;
			current = current->next;
		}
	}

	void displayReversedLinkedList()
	{
		DoublyLinkedListNode* current = tail;
		while (current != nullptr)
		{
			cout << "| " << current->ranking << " | " << current->student.name << " | " << current->student.question1 << " | " << current->student.question2 << " | " << current->student.question3 << " |   |" << endl;
			cout << "|   | " << string(current->student.name.length(), ' ') << " | " << current->student.score1 << " | " << current->student.score2 << " | " << current->student.score3 << " | " << current->student.totalscore << " |" << endl;
			current = current->prev;
		}
	}
	void searchList(string searchkey)
	{
		DoublyLinkedListNode* current = head;
		while (current != nullptr)
		{
			if (current->student.name == searchkey)
			{
				cout << "| " << current->ranking << " | " << current->student.name << " | " << current->student.question1 << " | " << current->student.question2 << " | " << current->student.question3 << " |   |" << endl;
				cout << "|   | " << string(current->student.name.length(), ' ') << " | " << current->student.score1 << " | " << current->student.score2 << " | " << current->student.score3 << " | " << current->student.totalscore << " |" << endl;
				break;
			}
			current = current->next;
		}
		if (current == nullptr)
		{
			cout << searchkey << " does not exist";
		}
	}
	void deletefromList()
	{
		if (!isEmpty())
		{
			DoublyLinkedListNode* temp = head;
			head = head->next;
			delete temp;
			size--;
		}
		else
		{
			cout << "List already empty!";
		}
	}
};