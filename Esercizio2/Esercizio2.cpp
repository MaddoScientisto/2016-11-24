// Esercizio2.cpp : definisce il punto di ingresso dell'applicazione console.
//

// Scrivere il programma di un gioco simile a “Battaglia navale” : -In una griglia 10 X 10, il programma deve posizionare casualmente una piccola nave nemica(1 X 1). - Ad ogni turno, il giocatore dichiara la casella da colpire, inserendo X e Y della cella bersaglio(se il valore non è valido, segnalare e richiedere); -Se il giocatore ha colpito il bersaglio, segnalare la vittoria e chiedere se si vuole ricominciare o meno.Altrimenti dichiarare quanto si è andati vicini al bersaglio stampando “Fuoco” se il colpo è arrivato entro un quadrato 3 X 3 intorno al bersaglio, “Fuochino” entro un quadrato 5 X 5, “Acqua” altrimenti.

#include <string>
#include "MaddoLib.h"
#include <time.h>
#include <math.h>

using namespace std;
using namespace Maddo;

void Esercizio();

int main()
{
	bool isRunning = true;
	while (isRunning)
	{
		MaddoLib::ClearScreen();
		Esercizio();

		isRunning = MaddoLib::AskYesNo("Ripetere il programma?");

	}


	return 0;
}

const int GRID_ROWS = 10;
const int GRID_COLUMNS = 10;
bool Grid[GRID_ROWS][GRID_COLUMNS];

// Dichiarazione funzioni
void FillGrid(bool grid[][GRID_COLUMNS]);
void EmptyGrid(bool grid[][GRID_COLUMNS]);
void PrintGrid(bool grid[][GRID_COLUMNS], bool reveal);
bool IsSquareHit(int x, int y);
bool CheckNear(int x, int y, int ray);

// Funzioni

void Esercizio()
{
	int x, y;
	int turn = 1;
	srand(static_cast<unsigned int>(time(0))); // Inizializzare il generatore di numeri casuali
	EmptyGrid(Grid);
	FillGrid(Grid);
	
	while (true)
	{
		MaddoLib::ClearScreen();
		MaddoLib::OutputLine("Turno: " + to_string(turn));
		
		PrintGrid(Grid, false);

		x = MaddoLib::InputInt("Inserire linea: ", "Valore non corretto", 0, 9);
		y = MaddoLib::InputInt("Inserire colonna: ", "Valore non corretto", 0, 9);
		if (Grid[x][y])
		{
			MaddoLib::OutputLine("Centro");
			MaddoLib::ClearScreen();
			MaddoLib::OutputLine("Completato in: " + to_string(turn) + " turni.");
			PrintGrid(Grid, true);
			MaddoLib::OutputLine("GAME OVER MAN... GAME OVER");
			return;
		}
		//Todo: controllo di prossimità

		
		if (CheckNear(x, y, 1))
		{
			MaddoLib::OutputLine("Fuoco");
		}
		else
		{			
			if (CheckNear(x, y, 3))
			{
				MaddoLib::OutputLine("Fuochino");
			}
			else
			{
				MaddoLib::OutputLine("Acqua");
			}
		}

		
		MaddoLib::Pause();
		turn++;
	}



}

void FillGrid(bool grid[][GRID_COLUMNS])
{
	int x = rand() % GRID_COLUMNS;
	int y = rand() % GRID_ROWS;
	grid[x][y] = true;
}

void EmptyGrid(bool grid[][GRID_COLUMNS])
{
	for (int i = 0; i < GRID_ROWS; i++)
	{
		for (int j = 0; j < GRID_COLUMNS; j++)
		{
			grid[i][j] = false;
		}
	}
}

void PrintGrid(bool grid[][GRID_COLUMNS], bool reveal)
{
	
	MaddoLib::OutputLine("  0 1 2 3 4 5 6 7 8 9");
	for (int i = 0; i < GRID_ROWS; i++)
	{
		MaddoLib::Output(to_string(i) + " ");
		for (int j = 0; j < GRID_COLUMNS; j++)
		{

			if (reveal && grid[i][j])
			{
				MaddoLib::Output("X ");
			}
			else
			{
				MaddoLib::Output("~ ");
			}


		}
		MaddoLib::OutputLine();
	}
}

bool IsSquareHit(int x, int y)
{
	return (Grid[x][y] == true);
}

bool CheckNear(int x, int y, int ray) 
{

	int cx, cy;
	bool isHit = false;
	for (int dx = -abs(ray); dx <= abs(ray); dx++) {
		for (int dy = -abs(ray); dy <= abs(ray); dy++)
		{
			cx = x + dx;
			cy = y + dy;

			if (cy < 0) cy = 0;
			if (cx < 0) cx = 0;
			if (cx > GRID_COLUMNS) cx = GRID_COLUMNS - 1;
			if (cy > GRID_ROWS) cy = GRID_COLUMNS - 1;

			if (!isHit) isHit = IsSquareHit(cx, cy);

		}
	}
	return isHit;
}


