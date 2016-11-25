// Esercizio4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


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
		MaddoLib::OutputLine();
		MaddoLib::OutputLine("GAME OVER");
		MaddoLib::OutputLine();
		isRunning = MaddoLib::AskYesNo("Nuova partita?");

	}


	return 0;
}

// function declarations
void OutputStats(int fuel, int ammo, int supplies);
void EsplorationMission(int *fuel, int *ammo, int *supplies);
void EarthDefense(int *fuel, int *ammo, int *supplies);
void ResearchersEscort(int *fuel, int *ammo, int *supplies);
int SelectMission();
//
enum TipoMissione { esplorazione = 0, difesa = 1, scorta = 2 };
void Esercizio()
{

	int fuel = 100;
	int ammo = 50;
	int supplies = 100;

	while (true)
	{
		MaddoLib::ClearScreen();
		OutputStats(fuel, ammo, supplies);
		int mission = SelectMission();
		switch (mission)
		{
		case esplorazione:
			EsplorationMission(&fuel, &ammo, &supplies);
			break;
		case difesa:
			EarthDefense(&fuel, &ammo, &supplies);
			break;
		case scorta:
			ResearchersEscort(&fuel, &ammo, &supplies);
			break;
		default:
			// Non dovrebbe accadere
			break;
		}
		MaddoLib::ClearScreen();
		OutputStats(fuel, ammo, supplies);
		if (fuel <= 0)
		{
			MaddoLib::OutputLine("Hai terminato la benzina");
			return;
		}
		if (ammo <= 0)
		{
			MaddoLib::OutputLine("Hai terminato le munizioni");
			return;
		}
		if (supplies <= 0)
		{
			MaddoLib::OutputLine("Hai terminato le scorte");
			return;
		}

		
		MaddoLib::Pause();
	}
}

void OutputStats(int fuel, int ammo, int supplies)
{
	MaddoLib::OutputLine("Benzina: " + to_string(fuel) + "\nMunizioni: " + to_string(ammo) + "\nScorte: " + to_string(supplies));
	MaddoLib::OutputLine();
}

void EsplorationMission(int *fuel, int *ammo, int *supplies)
{
	*fuel -= 20;
	*supplies -= 20;
}
void EarthDefense(int *fuel, int *ammo, int *supplies)
{
	*fuel -= 5;
	*supplies -= 5;
	*ammo -= 20;
}
void ResearchersEscort(int *fuel, int *ammo, int *supplies)
{
	*fuel -= 10;
	*ammo -= 10;
	*supplies -= 10;
}
int SelectMission()
{
	while (true)
	{
		MaddoLib::OutputLine("[0]: Esplorazione");
		MaddoLib::OutputLine("[1]: Difesa");
		MaddoLib::OutputLine("[2]: Ricerca");

		return MaddoLib::InputInt("Selezionare la missione:", "Valore non corretto", 0, 2);
	}
}