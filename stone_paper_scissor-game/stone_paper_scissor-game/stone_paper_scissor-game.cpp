#include <iostream>
#include <string>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };

enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stGameResults 
{
    short GameRound = 0;
    short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;

};


short ReadHowManyRounds()
{
    short Number = 0;
    do
    {
        cout << "How Many Rounds Do Yoy Want To Play: " << endl;
        cin >> Number;
    } while (Number <= 0);

    return Number;
}

short RandomNumber(short From, short To)
{
    short randNum = rand() % (To - From + 1) + From;
    return randNum;  
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);  
}

void ResetScreen()
{
	system("cls"); 
    system("Color 0F");
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player:
        cout << system("Color 0A"); // Green for Player
        break;
    case enWinner::Computer:
        cout << system("Color E4"); // Red for Computer
		cout << "\a"; // Beep sound for Computer win
        break;
    case enWinner::Draw:
        cout << system("Color 16"); // Yellow for Draw
        break;
    }
}

enGameChoice ReadPlayerChoice()
{
    short PlayerChoice = 0;
    do
    {
        cout << "Please Choose Your Option:\n";
        cout << "1. Stone\n";
        cout << "2. Paper\n";
        cout << "3. Scissor\n";
        cout << "Your Choice: ";
        cin >> PlayerChoice;
    } while (PlayerChoice < 1 || PlayerChoice > 3);

	return (enGameChoice) PlayerChoice;
}

enWinner WhoWinRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
        {
            return enWinner::Computer;
        }break;
    case enGameChoice::Scissor:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }break;
    }

    return enWinner::Player;

}
string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player", "Computer", "Draw" };
	return arrWinnerName[Winner - 1];
}

string ChooiseName(enGameChoice Chooise)
{
	string arrChoiceName[3] = { "Stone", "Paper", "Scissor" };
	return arrChoiceName[Chooise - 1];
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
    cout << "\nRound [" << RoundInfo.RoundNumber << "] Result:\n";
    cout << "Player Choice: " << ChooiseName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice: " << ChooiseName(RoundInfo.ComputerChoice) << endl;
    cout << "Winner: " << RoundInfo.WinnerName << endl;

}

enWinner WhoWonGame(short PlayerChoiceTimes, short ComputerChoiceTimes)
{

    if (PlayerChoiceTimes > ComputerChoiceTimes)
        return enWinner::Player;
    else if (ComputerChoiceTimes > PlayerChoiceTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
   
}

stGameResults FillGameResults(int GameRounds, short PlayerChoiceTimes, short ComputerChoiceTimes, short DrawsTimes)
{
    stGameResults GameResults;

	GameResults.GameRound = GameRounds;
	GameResults.PlayerWinTimes = PlayerChoiceTimes;
    GameResults.ComputerWinTimes = ComputerChoiceTimes;
    GameResults.DrawTimes = DrawsTimes;
    GameResults.GameWinner = WhoWonGame(PlayerChoiceTimes, ComputerChoiceTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);
   
    return GameResults;
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short PlayerChoiceTimes = 0, ComputerChoiceTimes = 0, DrawsTimes = 0;

    for (int GameRounds = 1; GameRounds <= HowManyRounds; GameRounds++)
    { 
        cout << "\n Round [" << GameRounds << "] begins:\n";
		RoundInfo.RoundNumber = GameRounds;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWinRound(RoundInfo);
		RoundInfo.WinnerName= WinnerName(RoundInfo.Winner);

	// Irement the game results based on the winner of the round
    if (RoundInfo.Winner == enWinner::Player)
        PlayerChoiceTimes++;
    else if (RoundInfo.Winner == enWinner::Computer)
		ComputerChoiceTimes++;
    else 
		DrawsTimes++;

	PrintRoundResult(RoundInfo);
    }

	return FillGameResults(HowManyRounds, PlayerChoiceTimes, ComputerChoiceTimes, DrawsTimes);

}

string Tabs(int Count)
{
    string TabsStr;
    for (int i = 0; i < Count; i++)
    {
        TabsStr += "\t";
		cout << "\t";
    }
    return TabsStr;
}


void ShowGameOverScreen()
{
	cout << Tabs(2) << "------------------------------------------------------------\n\n" ;
    cout << Tabs(2) << "                     +++G a m e  O v e r +++\n\n";
    cout << Tabs(2) << "------------------------------------------------------------\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{

	cout << Tabs(2) << "Game Rounds: " << GameResults.GameRound << endl;
	cout << Tabs(2) << "Player Win Times: " << GameResults.PlayerWinTimes << endl;
	cout << Tabs(2) << "Computer Win Times: " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw Times: " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Game Winner: " << GameResults.WinnerName << endl;


    SetWinnerScreenColor(GameResults.GameWinner);

}



void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << endl << Tabs(3) << "Do You Want To Play Again? (Y/N): ";
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');
    
}



int main()
{
    srand((unsigned)time(NULL));

	StartGame();

    return 0;
}

