#include<iostream>
using namespace std;
class GuessGame
{
 private:
 int secretNumber;
 int MinimumNumber;
 int MaximumNumber;
 int attempts;
  
 public:
 GuessGame(int min, int max)
 {
  MinimumNumber=min;
  MaximumNumber=max;
  getSecretNumber();
 }
 
 void  getSecretNumber()
 {
  srand(static_cast<unsigned int>(time(0)));
  secretNumber = rand() % (MaximumNumber - MinimumNumber+1) + MinimumNumber;
 }
 
 bool operator()(int guess) 
 {
  attempts++;

   if (guess == secretNumber) 
   {
    cout << " You guessed the number in " << attempts << " attempts"<<endl;
     return true; 
   }
   else if (guess < secretNumber)
   {
    cout << "Too low ";
   } 
   else
  {
   cout << "Too high ";
   }
    cout << "Attempts: " << attempts << endl;
   return false; 
  }
 void resetGame()
  {
  getSecretNumber();
  attempts=0;
  }
 char playAgain()
 {
  char choice;
  cout<<"Do you want to play again (y/n) :" ;
  cin>>choice;
  return choice;
  
 }
 void playGame()
 {
  cout << "Welcome to the Number Guessing Game "<<endl;
  cout << "Try to guess the number between " << MinimumNumber << " and " << MaximumNumber << endl;

 while (true) 
 {
  int guess;
  cout << "Enter your guess: ";
  cin >> guess;

  if ((*this)(guess)) 
   {
     break;
   }
  }
 }
};

int main()
{
 const int MinimumNumber = 1;
 const int MaximumNumber= 100;
 char playAgain;
  do 
  {
    GuessGame game(MinimumNumber, MaximumNumber);
    game.playGame();

    playAgain = game.playAgain();
    if (playAgain == 'y' || playAgain == 'Y') 
    {
     game.resetGame();
    }

  }
  while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing"<<endl;
 return 0;
}

