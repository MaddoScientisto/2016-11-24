// TicTacToe.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "TicTacToe2.h"
#include <string>
#include <io.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "MaddoLib.h"


using namespace std;
using namespace Maddo;

const int ROWS = 3;
const int COLUMNS = 3;
char board[ROWS][COLUMNS] = { { '_', '_', '_' },
{ '_', '_', '_' },
{ '_', '_', '_' } };

int xScore = 0;
int oScore = 0;

void InitBoard()
{
	for (auto i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			board[i][j] = '_';
		}
	}
}

void OutputBoardHeader()
{

}

void OutputBoard()
{
	MaddoLib::OutputLine("");
	MaddoLib::OutputLine("Stato corrente del campo di gioco:");
	MaddoLib::OutputLine("");
	MaddoLib::OutputLine("  1 2 3");
	for (int i = 0; i < ROWS; ++i)
	{

		MaddoLib::Output(to_string(i + 1) + " ");
		for (int j = 0; j < COLUMNS; ++j)
		{
			MaddoLib::Output(string(1, board[i][j]) + " ");

		}

		MaddoLib::OutputLine("");
	}
}

int GetRowColumnNumber()
{
	int value;
	string input;
	bool ok = false;
	while (!ok)
	{
		input = MaddoLib::Input("Inserire riga (0-2): ");
		if (input.length() == 1)
		{
			if (input[0] >= 0 && input[0] <= 2)
			{
				return input[0];
			}
		}
	}
	return 0;
}

void GetCellInput()
{
	int x;
	int y;
}

char GetPlayerCharacter()
{

	bool isValid = false;
	char playerCharacter = 'X'; // Default giusto in caso

	while (!isValid)
	{
		string input = MaddoLib::Input("Inserire il carattere del giocatore (O o X): ");
		if (input.length() == 1 && (input[0] == 'O' || input[0] == 'X'))
		{
			isValid = true;
			playerCharacter = input[0];

			MaddoLib::OutputLine("Il carattere selezionato è: " + input.substr(0, 1)); // devo fare così perché altrimenti mi manda in output il valore numerico oppure si corrompe il buffer
		}
		else
		{
			MaddoLib::OutputLine("Carattere non valido: " + string(1, input[0]));
		}
	}


	return playerCharacter;
}

bool IsLineFull(int line, char player)
{
	return (board[line][0] == player && board[line][1] == player && board[line][2] == player);

}

bool IsColumnFull(int column, char player)
{
	return (board[0][column] == player && board[1][column] == player && board[2][column] == player);

}

bool AreDiagonalsFull(char player)
{
	return (board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[2][0] == player && board[1][1] == player && board[0][2] == player);
}

char IsStateWinning()
{
	//1. Controllare righe
	//2. Controllare colonne
	//3. Controllare 2 diagonali

	char players[2] = { 'X', 'O' };

	for (int p = 0; p < 2; p++)
	{
		if (AreDiagonalsFull(players[p]))
		{
			return players[p];
		}
		for (int i = 0; i < 3; i++)
		{
			if (IsLineFull(i, players[p]) || IsColumnFull(i, players[p]))
			{
				return players[p];
			}
		}
	}

	return '_';
}

bool IsBoardFull()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == '_') return false;
		}
	}
	return true;
}

void DoPlayerTurn(char playerCharacter)
{
	MaddoLib::OutputLine("Turno del giocatore.");
	bool isCorrect = false;
	int x, y;

	while (!isCorrect) // Pericolosissimo triplo ciclo perché adoro vivere pericolosamente
	{

		while (!isCorrect)
		{
			x = MaddoLib::InputInt("Inserire riga: ", "Il valore inserito non è un numero", 1, 3);
			x--;
			if (x >= 0 && x <= 2)
			{
				isCorrect = true;

			}
		}

		isCorrect = false;

		while (!isCorrect)
		{
			y = MaddoLib::InputInt("Inserire colonna: ", "Il valore inserito non è un numero", 1, 3);
			y--;
			if (y >= 0 && y <= 2)
			{
				isCorrect = true;

			}
		}

		isCorrect = board[x][y] == '_';
		if (!isCorrect) { MaddoLib::OutputLine("La posizione selezionata contiene già: " + string(1, board[x][y])); OutputBoard(); }
	}
	board[x][y] = playerCharacter;

	//int x = MaddoLib::Input("Inserire riga: ");


}

void RandomTurn(char aiCharacter, char playerCharacter)
{
	int i = 0;
	int rX, rY;
	while (i < 90000) // metto un limite massimo nel caso improbabile vengano generati 90000 risultati non idonei
	{
		rX = rand() % 3;
		rY = rand() % 3;

		if (board[rX][rY] == '_')
		{
			board[rX][rY] = aiCharacter;
			return;
		}
		i++;
	}

	MaddoLib::OutputLine("Errore: Non è stato possibile trovare un posto");
}

void MediumTurn(char aiCharacter, char playerCharacter)
{
	for (int i = 0; i < 3; i++)
	{
		//Orizzontali
		if (IsCellFull(playerCharacter, i, 0) && IsCellFull(playerCharacter, i, 1) && IsCellFull('_', i, 2))
		{
			SetCell(aiCharacter, i, 2);
			return;
		}
		else if (IsCellFull('_', i, 0) && IsCellFull(playerCharacter, i, 1) && IsCellFull(playerCharacter, i, 2))
		{
			SetCell(aiCharacter, i, 0);
			return;
		}
		else
			if (IsCellFull(playerCharacter, i, 0) && IsCellFull('_', i, 1) && IsCellFull(playerCharacter, i, 2))
			{
				SetCell(aiCharacter, i, 1);
				return;
			}
			else
				//Verticali
				if (IsCellFull(playerCharacter, 0, i) && IsCellFull(playerCharacter, 1, i) && IsCellFull('_', 2, i))
				{
					SetCell(aiCharacter, 2, i);
					return;
				}
				else
					if (IsCellFull(playerCharacter, 0, i) && IsCellFull('_', 1, i) && IsCellFull(playerCharacter, 2, i))
					{
						SetCell(aiCharacter, 1, i);
						return;
					}
					else
						if (IsCellFull('_', 0, i) && IsCellFull(playerCharacter, 1, i) && IsCellFull(playerCharacter, 2, i))
						{
							SetCell(aiCharacter, 0, i);
							return;
						}
	}

	//Diagonali

	if (IsCellFull(playerCharacter, 0, 0) && IsCellFull(playerCharacter, 1, 1) && IsCellFull('_', 2, 2))
	{
		SetCell(aiCharacter, 2, 2);
		return;
	}
	else if (IsCellFull(playerCharacter, 0, 0) && IsCellFull('_', 1, 1) && IsCellFull(playerCharacter, 2, 2))
	{
		SetCell(aiCharacter, 1, 1);
		return;
	}
	else
		if (IsCellFull('_', 0, 0) && IsCellFull(playerCharacter, 1, 1) && IsCellFull(playerCharacter, 2, 2))
		{
			SetCell(aiCharacter, 0, 0);
			return;
		}

		else if (IsCellFull(playerCharacter, 2, 0) && IsCellFull(playerCharacter, 1, 1) && IsCellFull('_', 0, 2))
		{
			SetCell(aiCharacter, 0, 2);
			return;
		}
		else if (IsCellFull(playerCharacter, 2, 0) && IsCellFull('_', 1, 1) && IsCellFull(playerCharacter, 0, 2))
		{
			SetCell(aiCharacter, 1, 1);
			return;
		}
		else if (IsCellFull('_', 2, 0) && IsCellFull(playerCharacter, 1, 1) && IsCellFull(playerCharacter, 0, 2))
		{
			SetCell(aiCharacter, 2, 0);
			return;
		}
		else
		{
			// Nessuna di queste condizioni, effettuare una mossa random
			RandomTurn(aiCharacter, playerCharacter);
		}
}

enum Difficulty { RANDOM, MEDIUM };
void DoAITurn(Difficulty difficulty, char aiCharacter, char playerCharacter)
{
	MaddoLib::OutputLine("Turno AI");

	if (difficulty == RANDOM)
	{
		RandomTurn(aiCharacter, playerCharacter);
	}
	else if (difficulty == MEDIUM)
	{

		MediumTurn(aiCharacter, playerCharacter);
	}

}

char GetCell(int x, int y)
{
	return board[x][y];
}

void SetCell(char character, int x, int y)
{
	board[x][y] = character;
}

bool IsCellFull(char character, int x, int y)
{
	return board[x][y] == character;
}

enum TurnType { PLAYER, AI };


Difficulty ChooseDifficulty()
{
	int diff;
	while (true)
	{
		MaddoLib::OutputLine("[0]: Facile\n[1]: Medio");
		diff = MaddoLib::InputInt("Inserire il livello di difficoltà desiderato: ", "Non è stato inserito un numero", 0, 1);
		if (diff == RANDOM)
		{

			MaddoLib::OutputLine("Livello di difficoltà selezionato: Facile");
			return RANDOM;
		}
		else if (diff == MEDIUM)
		{
			MaddoLib::OutputLine("Livello di difficoltà selezionato: Medio");
			return MEDIUM;
		}
	}


}

void Game()
{
	InitBoard();
	TurnType turn;
	Difficulty difficulty = ChooseDifficulty();

	char playerCharacter = GetPlayerCharacter();
	char aiCharacter;
	if (playerCharacter == 'X') { aiCharacter = 'O'; }
	else { aiCharacter = 'X'; }

	if (MaddoLib::AskYesNo("Vuoi iniziare per primo?"))
	{
		turn = PLAYER;
	}
	else
	{
		turn = AI;
	}

	bool isPlaying = true;

	while (isPlaying)
	{
		MaddoLib::ClearScreen();
		OutputBoard();

		if (turn == PLAYER)
		{
			DoPlayerTurn(playerCharacter);
			turn = AI;
		}
		else
		{
			DoAITurn(difficulty, aiCharacter, playerCharacter);
			turn = PLAYER;
		}

		char c = IsStateWinning();
		if (c == 'X')
		{
			// Vittoria di X
			isPlaying = false;
			OutputBoard();
			MaddoLib::OutputLine("Vittoria di X");
			xScore += 10;
			oScore -= 10;
			break;

		}
		else if (c == 'O')
		{
			// Vittoria di O
			isPlaying = false;
			OutputBoard();
			MaddoLib::OutputLine("Vittoria di O");
			oScore += 10;
			xScore -= 10;
			break;
		}


		if (IsBoardFull())
		{
			// pareggio
			MaddoLib::OutputLine("Pareggio");
			OutputBoard();
			isPlaying = false;
		}

		// Nessuna di queste condizioni: nuovo turno
		MaddoLib::Pause();
	}


	MaddoLib::OutputLine("Punteggi:\nX: " + to_string(xScore) + "\nO: " + to_string(oScore));
}

int main()
{
	srand(static_cast<unsigned int>(time(0))); // Inizializzare il generatore di numeri casuali
	bool exit = false;
	while (!exit) {
		Game();

		exit = MaddoLib::AskYesNo("\nUscire dal programma?");
	}
	return 0;
}