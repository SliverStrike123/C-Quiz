#include "G21_TP065228_TP065588_TP065888_TP066229_TP072070_Queue.hpp"
#include "G21_TP065228_TP065588_TP065888_TP066229_TP072070_Array.hpp"
#include "G21_TP065228_TP065588_TP065888_TP066229_TP072070_Stack.hpp"
#include "G21_TP065228_TP065588_TP065888_TP066229_TP072070_Tree.hpp"
#include "G21_TP065228_TP065588_TP065888_TP066229_TP072070_LinkedList.hpp"
#include <chrono>

using namespace std::chrono;
using namespace std;

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	int numberOfStudents = 70 + rand() % 31;
	int numberOfrounds = 3;

	
	Question* questions = loadQuestion("G21_TP065228_TP065588_TP065888_TP066229_TP072070_questions.csv");
	

	

	//initialize all necessary data structures
	QuestionQueue* questionQueue = new QuestionQueue(300);
	DiscardedQuestionQueue* discardedQueue = new DiscardedQuestionQueue(300);
	StudentList* studentList = new StudentList(numberOfStudents);
	AnsweredQuestionsStack* answeredStack = new AnsweredQuestionsStack();
	BinaryTree tree;
	SortedStudentLinkedList doublylinkedlist;
	
	auto start = high_resolution_clock::now();
	for (int i = 0; i < questionQueue->getSize(); i++)
	{
		questionQueue->addQuestion(questions[i]);
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Execution time for loadquestions in microseconds = " << duration.count() << endl;
	start = high_resolution_clock::now();
	for (int i = 0; i < numberOfStudents; i++)
	{
		string name;
		int index = i + 1;
		
		name = "Student" + to_string(index);
		
		studentList->addStudent(name, i);
	}
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Execution time for load students in microseconds = " << duration.count() << endl;
	cout << "Class Size: " << numberOfStudents << endl;
	for (int round = 1 ; round <= numberOfrounds; round++)
	{
		if (answeredStack->allQuestionsAnswered())
		{
			break;
		}
		cout << "Round " << round << endl;
		
		
		for (int i = 0; i < numberOfStudents; i++)
		{
			// check if discarded deck is empty or not
			bool isDiscardedEmpty = discardedQueue->isEmpty();
			bool validInput = false;
			bool decline = true;
			int rejectedTimes = 0;
			int choice = 1;
			cout << string(100, '-') << endl;
			cout << studentList->getName(i) << ", it is your turn!" << endl;

			if (!answeredStack->isEmpty())
			{
				cout << string(100, '-') << endl;
				cout << "Last Answered Question = " << answeredStack->peekTopofDeck() << endl;
				cout << string(100, '-') << endl;
			}
			
			if (round != 1)
			{
				if (isDiscardedEmpty)
				{
					cout << "Discarded Deck is currently empty!" << endl;
					cout << string(100, '-') << endl;
				}
				else if (questionQueue->isEmpty())
				{
					cout << string(100, '-') << endl;
					cout << "No more unanswered questions!" << endl;
					cout << string(100, '-') << endl;
					cout << "Drawing from discarded deck!" << endl;
					choice = 2;
				}
				else
				{
					cout << string(100, '-') << endl;
					cout << "Discarded Deck Size: " << discardedQueue->getsize() << endl;
					cout << string(100, '-') << endl;
					cout << "Current Discarded Question: " << discardedQueue->getquestionstring() << endl;
					cout << string(100, '-') << endl;
					cout << "Select deck to pick from (1 - Unanswered, 2 - Discarded): ";
					cin >> choice;
					while (choice != 1 && choice != 2)
					{
						cin.clear();
						cin.ignore();
						cout << "Invalid Input, please choose between 1 and 2 (1 - Unanswered, 2 - Discarded): ";
						cin >> choice;
						
					}
				}
			}
			
			if (choice == 1)
			{
				questionQueue->showQuestion();
				string dummydecision;
				char decision;
				while (decline && rejectedTimes < 2)
				{
					cout << "Accept or decline this question? (a = accept, d = decline): ";
					cin >> dummydecision;
					decision = tolower(dummydecision[0]);
					if (dummydecision.length() > 1 || (decision != 'a' && decision != 'd'))
					{
						cout << "Invalid input received" << endl;
					}
					else
					{
						if (decision == 'a')
						{
							decline = false;
						}
						else if (decision == 'd')
						{
							discardedQueue->addDiscardedQuestion(questionQueue->getQuestion());
							questionQueue->dequeue();
							questionQueue->showQuestion();
							rejectedTimes++;
						}
					}
				}
				char answer;
				string dummyanswer;
				cout << "Your Answer: ";
				cin >> dummyanswer;
				answer = dummyanswer[0];
				while (!validInput)
				{
					answer = toupper(answer);
					if (dummyanswer.length() == 1 && (answer == 'A' || answer == 'B' || answer == 'C' || answer == 'D'))
					{
						validInput = true;
					}
					else
					{
						cout << "Invalid input received, please answer properly by choosing between A,B,C or D!" << endl;
						cout << "Your Answer: ";
						cin >> dummyanswer;
						answer = dummyanswer[0];
					}
				}
				char correctanswer = questionQueue->getAnswer();
				string questionString = questionQueue->getquestionstring();
				int questionScore = questionQueue->getscore();

				if (answer == correctanswer)
				{
					cout << "Answer Correct!" << endl;
					studentList->studentAnswer(questionString, round, i, questionScore);
				}
				else
				{
					cout << "Answer Wrong!" << endl;
					studentList->studentAnswer(questionString, round, i, 0);
				}
				cout << "Student" << i + 1 << "'s current score = " << studentList->getTotalScore(i) << endl;
				answeredStack->push(questionString);
				questionQueue->dequeue();
			}

			else if (choice == 2)
			{
				discardedQueue->showDiscardedQuestion();
				string dummyanswer;
				char answer;
				cout << "Your Answer: ";
				cin >> dummyanswer;
				answer = dummyanswer[0];
				while (!validInput)
				{
					answer = toupper(answer);
					if (answer == 'A' || answer == 'B' || answer == 'C' || answer == 'D')
					{
						validInput = true;
					}
					else
					{
						cout << "Invalid input received, please answer properly by choosing between A,B,C or D!" << endl;
						cout << "Your Answwer: ";
						cin >> answer;
					}
				}
				char correctanswer = discardedQueue->getAnswer();
				string questionString = discardedQueue->getquestionstring();
				int questionScore = discardedQueue->getscore();

				if (answer == correctanswer)
				{
					cout << "Answer Correct!" << endl;
					studentList->studentAnswer(questionString, round, i, questionScore);
				}
				else
				{
					cout << "Answer Wrong!" << endl;
					studentList->studentAnswer(questionString, round, i, 0);
				}
				cout << "Student" << i + 1 << "'s current score = " << studentList->getTotalScore(i) << endl;
				answeredStack->push(questionString);
				discardedQueue->dequeue();
			}
		}
	}

	//free up memory by popping all elements in stack 
	while (!answeredStack->isEmpty())
	{
		answeredStack->pop();
	}
	//free up memory by dequeuing all elements in queue
	while (!questionQueue->isEmpty())
	{
		questionQueue->dequeue();
	}
	while (!discardedQueue->isEmpty())
	{
		discardedQueue->dequeue();
	}
	cout << "Quiz End!" << endl;
	start = high_resolution_clock::now();
	Student* sortedlist = studentList->sortList();
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Execution time for bubblesort in microseconds = " << duration.count() << endl;
	string top30[30];
	for (int i = 0; i < 30; i++)
	{
		top30[i] = sortedlist[i].name;
	}
	for (int i = 0; i < numberOfStudents; i++)
	{
		int rank = i + 1;
		doublylinkedlist.insertIntoList(sortedlist[i],rank);
	}
	start = high_resolution_clock::now();
	tree.buildtree(top30);
	cout << string(100, '-') << endl;
	tree.printTop30Tree();
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Execution time for buildtree in microseconds = " << duration.count() << endl;
	bool proceed = false;

	while (!proceed)
	{
		int settings; 
		cout << "Choose the following settings, 1. Search for student, 2. Proceed: ";
		cin >> settings;
		if (settings != 1 && settings != 2)
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid Input Received" << endl;
			cout << "Choose the following settings, 1. Search for student, 2. Proceed: ";
			cin >> settings;
		}
		if (settings == 1)
		{
			string name;
			cout << "Enter student name: ";
			cin >> name;
			if (tree.searchNode(name))
			{
				cout << name << " exist in the Top 30 list!" << endl;
			}
			else
			{
				cout << name << " does not exist in the Top 30 list!" << endl;
			}
		}
		if (settings == 2)
		{
			proceed = true;
		}

	}
	proceed = false;
	start = high_resolution_clock::now();
	cout << string(100, '-') << endl;
	cout << "Leaderboard" << endl;
	cout << string(100, '-') << endl;
	cout << "| Ranking | Name | Question 1 | Question 2 | Question 3 | Total Score | " << endl;
	cout << string(100, '-') << endl;
	stop = high_resolution_clock::now();
	doublylinkedlist.displayLinkedList();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Execution time for buildtree in microseconds = " << duration.count() << endl;

	while (!proceed)
	{
		int params;
		cout << "Leaderboard parameters settings: 1. Decending, 2. Ascending, 3. Open Search, 4. End Quiz: ";
		cin >> params;
		if (params != 1 && params != 2 && params != 3 && params != 4)
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input received" << endl;
			cout << "Leaderboard parameters settings: 1. Decending, 2. Ascending, 3. Open Search, 4. End Quiz:";
			cin >> params;
		}
		if (params == 1)
		{
			cout << string(100, '-') << endl;
			cout << "Parameters: Decending" << endl;
			cout << string(100, '-') << endl;
			cout << "| Name | Question 1 | Question 2 | Question 3 | Total Score | " << endl;
			cout << string(100, '-') << endl;
			doublylinkedlist.displayLinkedList();
		}
		if (params == 2)
		{
			cout << string(100, '-') << endl;
			cout << "Parameters: Ascending" << endl;
			cout << string(100, '-') << endl;
			cout << "| Name | Question 1 | Question 2 | Question 3 | Total Score | " << endl;
			cout << string(100, '-') << endl;
			doublylinkedlist.displayReversedLinkedList();
		}
		if (params == 3)
		{
			string name;
			cout << "Search: ";
			cin >> name;
			doublylinkedlist.searchList(name);
		}
		if (params == 4)
		{
			proceed = true;
		}
	}
	cout << "Quiz Ended!";
	while (!doublylinkedlist.isEmpty())
	{
		doublylinkedlist.deletefromList();
	}
	return 0;
}