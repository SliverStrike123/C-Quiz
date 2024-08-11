#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Question {
    string text;
    string answers[4];
    char correctAnswer;
    int score;
};

string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

Question* loadQuestion(string filepath)
{
    //Read Questions from File
    ifstream file(filepath);
    if (!file) {
        cerr << "Unable to open file: " << filepath << endl;
        exit(1);
    }

    string line;
    int questionCount = 0;

    while (getline(file, line)) {
        ++questionCount;
    }
    file.clear();
    file.seekg(0);

    Question* questions = new Question[questionCount];
    int index = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        Question q;

        getline(ss, q.text, ',');
        q.text = trim(q.text);

        for (int i = 0; i < 4; ++i) {
            getline(ss, q.answers[i], ',');
            q.answers[i] = trim(q.answers[i]);
        }

        getline(ss, item, ',');
        item = trim(item);
        if (!item.empty()) {
            q.correctAnswer = item[0];
        }
        else {
            cerr << "Error: Missing correct answer for question: " << q.text << endl;
            exit(1);
        }

        getline(ss, item, ',');
        item = trim(item);
        q.score = stoi(item);

        questions[index++] = q;
    }

    file.close();
    //Shuffle the questions
    srand(time(0));
    for (int i = questionCount - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(questions[i], questions[j]);
    }
    return questions;
}
class DiscardedQuestionQueue {
    int frontindex, rearindex;
    int countsize;
    int arraysize;
    Question* discardedquestions = nullptr;

public:
    DiscardedQuestionQueue(int arraysize)
    {
        frontindex = -1;
        rearindex = -1;
        countsize = 0;
        this->arraysize = arraysize;
        discardedquestions = new Question[arraysize];
    }

    ~DiscardedQuestionQueue()
    {
        delete[] discardedquestions;
    }
    int getSize()
    {
        return arraysize;
    }
    bool isFull()
    {
        if (rearindex == arraysize - 1)
        {
            return true;
        }
        return false;
    }
    bool isEmpty()
    {
        if ((frontindex == -1 && rearindex == -1) || (frontindex > rearindex)) {
            return true;
        }
        else
        {
            return false;
        }
    }
    void addDiscardedQuestion(Question question)
    {
        if (isFull())
        {
            cout << "Queue already full (overflow!)" << endl;
            return;
        }
        if (frontindex == -1)
        {
            frontindex++; //frontindex = 0;
        }

        rearindex++;
        discardedquestions[rearindex].text = question.text;
        for (int i = 0; i < 4; i++)
        {
            discardedquestions[rearindex].answers[i] = question.answers[i];
        }
        discardedquestions[rearindex].correctAnswer = question.correctAnswer;
        discardedquestions[rearindex].score = question.score * 0.8;

        countsize++;
    }
    void showDiscardedQuestion()
    {
        cout << string(100, '-') << endl;
        cout << discardedquestions[frontindex].text << endl;
        for (int i = 0; i < 4; i++)
        {
            cout << char(65 + i) << "." << discardedquestions[frontindex].answers[i] << " ";
        }
        cout << endl << "Question is worth " << discardedquestions[frontindex].score << " points" << endl;
        cout << string(100, '-') << endl;
    }
    string getquestionstring()
    {
        return discardedquestions[frontindex].text;
    }
    int getscore()
    {
        return discardedquestions[frontindex].score;
    }
    char getAnswer()
    {
        return discardedquestions[frontindex].correctAnswer;
    }
    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue already empty! (underflow)";
            return;
        }
        discardedquestions[frontindex] = {};
        frontindex++;
        countsize--;

        if (countsize == 0)
        {
            frontindex = -1;
            rearindex = -1;
        }
    }
    Question getQuestion()
    {
        return discardedquestions[frontindex];
    }
    int getsize()
    {
        return countsize;
    }
};

class QuestionQueue {
    int frontindex, rearindex;
    int countsize;
    int arraysize;
    Question* questions = nullptr;
    
public:
    QuestionQueue(int arraysize)
    {
        frontindex = -1;
        rearindex = -1;
        countsize = 0;
        this->arraysize = arraysize;
        questions = new Question[arraysize];
    }

    ~QuestionQueue()
    {
        delete[] questions;
    }
    int getSize()
    {
        return arraysize;
    }
    bool isFull()
    {
        if (rearindex == arraysize - 1)
        {
            return true;
        }
        return false;
    }
    bool isEmpty()
    {
        if ((frontindex == -1 && rearindex == -1) || (frontindex > rearindex) || countsize == 0) {
            return true;
        }
        else
        {
            return false;
        }
    }
    void addQuestion(Question question)
    {
        if (isFull())
        {
            cout << "Queue already full (overflow!)" << endl;
            return;
        }
        if (frontindex == -1)
        {
            frontindex++; //frontindex = 0;
        }

        rearindex++;
        questions[rearindex].text = question.text;
        for (int i = 0; i < 4; i++)
        {
            questions[rearindex].answers[i] = question.answers[i];
        }
        questions[rearindex].correctAnswer = question.correctAnswer;
        questions[rearindex].score = question.score;

        countsize++;

    }

    void showQuestion()
    {
        cout << string(100, '-') << endl;
        cout << questions[frontindex].text << endl;
        for (int i = 0; i < 4; i++)
        {
            cout << char(65+i) << "." << questions[frontindex].answers[i] << " ";
        }
        cout << endl << "Question is worth " << questions[frontindex].score << " points" << endl;
        cout << string(100, '-') << endl;
    }

    string getquestionstring()
    {
        return questions[frontindex].text;
    }
    int getscore()
    {
        return questions[frontindex].score;
    }
    char getAnswer()
    {
        return questions[frontindex].correctAnswer;
    }
    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue already empty! (underflow)";
            return;
        }
        questions[frontindex] = {};
        frontindex++;
        countsize--;
        cout << countsize << endl;
        if (countsize == 0)
        {
            frontindex = -1;
            rearindex = -1;
        }
    }
    Question getQuestion()
    {
        return questions[frontindex];
    }
};



