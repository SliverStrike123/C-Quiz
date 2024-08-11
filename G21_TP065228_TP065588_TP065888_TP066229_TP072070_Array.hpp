#pragma once
#include <iostream>

using namespace std;

struct Student
{
	string name;
	string question1;
	string question2;
	string question3;
	int score1;
	int score2;
	int score3;
	int totalscore;
};

class StudentList 
{
	int numberOfstudents;
	Student* studentList;
	
public:
	StudentList(int numberOfstudents)
	{
		this->numberOfstudents = numberOfstudents;
		studentList = new Student[numberOfstudents];
	}

	~StudentList() {
		delete[] studentList;
	}
	void displaystudentList()
	{
		for (int i = 0; i < numberOfstudents; i++)
		{
			cout << studentList[i].name;
		}
	}
	void addStudent(string name, int index)
	{
		studentList[index].name = name;
		studentList[index].question1 = "";
		studentList[index].question2 = "";
		studentList[index].question3 = "";
		studentList[index].score1 = 0;
		studentList[index].score2 = 0;
		studentList[index].score3 = 0;
		studentList[index].totalscore = 0;
	}

	void studentAnswer(string question,int round, int index, int score)
	{
		if (round == 1)
		{
			studentList[index].question1 = question;
			studentList[index].score1 = score;
			
		}
		else if (round == 2)
		{
			studentList[index].question2 = question;
			studentList[index].score2 = score;
		}
		else if (round == 3)
		{
			studentList[index].question3 = question;
			studentList[index].score3 = score;
		}
		studentList[index].totalscore += score;
	}

	Student* sortList()
	{
		Student* sortedList = studentList;
		//if top == true, descending based on totalscore, else, ascending based on totalscore
		// O(n^2)
		for (int i = 0; i < numberOfstudents; i++) {
			for (int j = 0; j < numberOfstudents - i - 1; j++)
			{
				if (sortedList[j].totalscore < sortedList[j+1].totalscore) 
				{
					Student x = sortedList[j];
					sortedList[j] = sortedList[j+1];
					sortedList[j + 1] = x;
				}
			}
		}
		return sortedList;
	}
	int getTotalScore(int index)
	{
		return studentList[index].totalscore;
	}
	string getName(int index)
	{
		return studentList[index].name;
	}
};