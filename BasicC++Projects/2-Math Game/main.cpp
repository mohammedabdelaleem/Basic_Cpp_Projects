//#include<bits/stdc++.h>//Consists Of The Most Built In Functions
#include <iostream> //cin ,cout
#include <stdlib.h>//srand
#include <time.h> //time
#include <windows.h> // Sleep
//#include <cstdlib>  // clsusing namespace std;
#include<climits>
using namespace std;

enum enOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };
enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enBkColors { Red = 1, Green = 2, Yellow = 3 };


struct stQuestion
{
    short Number1 = 0;
    short Number2 = 0;
    enOpType OperatoinType;
    enQuestionLevel QuestionLevel;
    short CorrectAnswer = 0;
    short PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionList[15];
    short NumberOfQuestions = 0;
    enQuestionLevel QuestionLevel;
    enOpType QuestionOpType;
    short NumberOfCorrectAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool IsPass = false;
};

void ResetNormalBkColor()
{
    system("cls");
    system("Color 0f");
}

void moveCursor(int row, int col) {/////////////
    cout << "\033[" << row << ";" << col << "H"; //33 Escape character
}

inline void load(int time)
{
    moveCursor(25, 48);
    cout << "\t--->Loading";
    for (int i = 0; i < time; i++)
    {
        if ((i + 1) != time)
        {
            Sleep(250);//250*10^3sec
            cout << ".";
        }
        else
        {
            Sleep(250);
            cout << ":-)";
            Sleep(350);
        }
    }
    system("cls");
}

void ChangeBk(enBkColors BkColor)
{
    switch (BkColor)
    {
    case enBkColors::Green:
        system("Color 2f");//Green Bk Color
        break;

    case enBkColors::Red:
        system("Color 4f");//Red Bk Color
        cout << "\a";
        break;

    case enBkColors::Yellow:
        system("Color 6f");//Red Bk Color
        break;
    }
}

void SetScreenColor(bool Flag)
{
    (Flag) ? ChangeBk(enBkColors::Green) : ChangeBk(enBkColors::Red);
}

/*This code checks if the input stream is in a good state
 before checking if the input is within the valid range.
  If the input is not a valid number or is outside the valid range,
   it clears the input stream and asks the user to input again.*/
//short ReadHowManyQuestion()
//{
//    short NumberOfQuestions = 1;
//    bool validInput = true;
//    do
//    {
//        if (!validInput) {
//            // If input was invalid, clear the error flag and ignore any remaining input in the stream
//            cin.clear();
//            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//I Did This Function For Number Full Validation , But It goes against Windows.h So i Will Archeive It 
//            cout << "Invalid input. Please enter a number between 1 and 15." << endl;
//        }
//        cout << "How many questions do you want to answer [1-15]? ";
//        cin >> NumberOfQuestions;
//        validInput = cin.good() && NumberOfQuestions >= 1 && NumberOfQuestions <= 15;
//    } while (!validInput);
//
//    return NumberOfQuestions;
//}

short ReadHowManyQuestion()
{
    short Number = 1;
    do
    {
        cout << "Enter A Number [" << 1 << "-" << 15 << "] ? ";
        cin >> Number;

    } while (Number<1 || Number>15);

    return Number;
}

short RandomNumber(short From, short To)
{
    //function To Generate Random Number
    return (rand() % (To - From + 1) + From);
}


enQuestionLevel ReadQuestionLevel()
{
    short QuestionLevel = 1;
    do
    {
        cout << "Enter Question Level [1]Easy  [2]Med  [3]Hard  [4]Mix ? ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel>4);

    return (enQuestionLevel)QuestionLevel;
}

enOpType ReadOpType()
{
    short OpType = 1;
    do
    {
        cout << "Enter An Operation Type [1]Add(+)  [2]Sub(-)  [3]Mul(*)  [4]Div(/)  [5]Mix ? ";
        cin >> OpType;
    } while (OpType < 1 || OpType>5);

    return (enOpType)OpType;
}

enOpType GetRandomOperationType()
{
    short Op = RandomNumber(1, 4);
    return (enOpType)Op;
}

short SimpleCalculate(short Num1, short Num2, enOpType OpType)
{
    switch (OpType)
    {
    case enOpType::Add:
        return Num1 + Num2;

    case enOpType::Sub:
        return Num1 - Num2;

    case enOpType::Mul:
        return Num1 * Num2;

    case enOpType::Div:
        return Num1 / Num2;

    }
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOpType OpType)
{
    stQuestion Question;
    if (QuestionLevel == enQuestionLevel::Mix)
    {
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
    }

    if (OpType == enOpType::MixOp)
    {
        OpType = GetRandomOperationType();
    }

    Question.OperatoinType = OpType;
    Question.QuestionLevel = QuestionLevel;

    switch (QuestionLevel)
    {
        //Easy Level
    case enQuestionLevel::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculate(Question.Number1, Question.Number2, Question.OperatoinType);
        return Question;

        //Medium Level
    case enQuestionLevel::Med:
        Question.Number1 = RandomNumber(15, 50);
        Question.Number2 = RandomNumber(15, 50);

        Question.CorrectAnswer = SimpleCalculate(Question.Number1, Question.Number2, Question.OperatoinType);
        return Question;

        //Hard Level
    case enQuestionLevel::Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.CorrectAnswer = SimpleCalculate(Question.Number1, Question.Number2, Question.OperatoinType);
        return Question;
    }
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
    {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.QuestionOpType);
    }

}

char GetOpTypeSympol(enOpType OpType)//For Each Question
{
    char OpTypes[4] = { '+','-','*','/' };
    return OpTypes[OpType - 1];
}

string GetOpTypeName(enOpType OpType)//for Final Result
{
    string arrOpType[5] = { "Add(+)" , "Sub(-)" , "Mul(*)" , "Div(/)" , "Mix" };
    return arrOpType[(int)OpType - 1];
}

void PtintTheQuestion(stQuizz Quizz, short QuestionNumber)
{
    cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSympol(Quizz.QuestionList[QuestionNumber].OperatoinType) << endl;
    cout << "------\n";
}

short ReadQuestionAnswer()
{
    short Answer = 0;
    cin >> Answer;
    return Answer;
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;

        cout << "\n\nWrong Answer :-( \n";
        cout << "The Right answer is: ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfCorrectAnswers++;

        cout << "\nRight Answer :-) \n\n";
    }
    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);

}

void AskAndCorrectQuestionList(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PtintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quizz, QuestionNumber);

        if (QuestionNumber != Quizz.NumberOfQuestions - 1) load(5);
    }
    (Quizz.IsPass) = (Quizz.NumberOfCorrectAnswers >= Quizz.NumberOfWrongAnswers);
}

string Tab(short NumberOfTabs)
{
    string t = "";
    for (short i = 1; i <= NumberOfTabs; i++)
        t += "\t";

    return t;
}

string GetFinalResult(bool IsPass)
{
    return (IsPass) ? "Pass" : "Fail";
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
    string arrQuestionLevels[4] = { "Easy" , "Med", "Hard" , "Mix" };
    return arrQuestionLevels[QuestionLevel - 1];
}


void PrintQuizzResults(stQuizz Quizz)
{
    load(8);
    moveCursor(10, 80);
    cout << endl;
    cout << Tab(4) << "-----------------------------\n";
    cout << Tab(4) << "------Final Result " << GetFinalResult(Quizz.IsPass) << "-----\n";
    cout << Tab(4) << "-----------------------------\n\n";

    cout << Tab(4) << "Number Of Questions    : " << Quizz.NumberOfQuestions << endl;
    cout << Tab(4) << "Questions Level        : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
    cout << Tab(4) << "OpType                 : " << GetOpTypeName(Quizz.QuestionOpType) << endl;
    cout << Tab(4) << "Number Of Right Answers: " << Quizz.NumberOfCorrectAnswers << endl;
    cout << Tab(4) << "Number Of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
    cout << Tab(4) << "-----------------------------\n\n";
    SetScreenColor(Quizz.IsPass);
}

void PlayMathGame()
{
    stQuizz Quizz;

    Quizz.NumberOfQuestions = ReadHowManyQuestion();
    Quizz.QuestionLevel = ReadQuestionLevel();
    Quizz.QuestionOpType = ReadOpType();

    //loading 5 seconds
    load(5);

    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionList(Quizz);
    PrintQuizzResults(Quizz);
}

void StartGame()
{
    char PlayAgain = 'Y';

    do {
        ResetNormalBkColor();
        PlayMathGame();


        cout << endl << "Do You Want To Play Again[Y/N]?: ";
        cin >> PlayAgain;

        if (PlayAgain == 'Y' || PlayAgain == 'y')load(7);
        else
        {
            load(7);
            ResetNormalBkColor();
        }
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}