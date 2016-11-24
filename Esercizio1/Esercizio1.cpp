// Esercizio1.cpp : definisce il punto di ingresso dell'applicazione console.
//

//Scrivere il programma che gestisce un tabellone di punteggi (leaderboard) che permetta di inserire il punteggio di 10 giocatori (Giocatore 0, Giocatore 1, … Giocatore 9). Una volta che i dati sono stati immessi, stampare a video la lista dei giocatori e dei punteggi inseriti in ordine inverso a cui sono stati inseriti e la media dei punteggi.
#include "MaddoLib.h"
#include <string>
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

const int NumeroGiocatori = 10;

int Punteggi[NumeroGiocatori];

void Esercizio()
{
	for (int i = 0; i < NumeroGiocatori; i++)
	{
		Punteggi[i] = MaddoLib::InputInt("Inserire il punteggio per il giocatore N. " + to_string(i + 1) + ": ", "Il testo inserito non è un numero");
	}

	MaddoLib::ClearScreen();

	for (int i = NumeroGiocatori-1; i >=0; i--)
	{
		MaddoLib::OutputLine("Punteggio giocatore " + to_string(i + 1) + ": " + to_string(Punteggi[i]));
	}

}

