#pragma once

void InitBoard();
void OutputBoardHeader();
void OutputBoard();
int GetRowColumnNumber();
void GetCellInput();
char GetPlayerCharacter();
bool IsLineFull(int line, char player);
bool IsColumnFull(int column, char player);
bool AreDiagonalsFull(char player);
char IsStateWinning();
bool IsBoardFull();
char GetCell(int x, int y);
void SetCell(char character, int x, int y);
bool IsCellFull(char character, int x, int y);
void DoPlayerTurn(char playerCharacter);
enum Difficulty;
void RandomTurn(char aiCharacter, char playerCharacter);
void MediumTurn(char aiCharacter, char playerCharacter);
void DoAITurn(Difficulty difficulty, char aiCharacter, char playerCharacter);
enum TurnType;
Difficulty ChooseDifficulty();
void Game();
int main();