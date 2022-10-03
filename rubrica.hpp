#pragma once

#include "libs.hpp"

#define MAX_SIZE 100

struct DATA
{
	short giorno;
	short mese;
	short anno;
};

struct CONTATTO
{
	string nome;
	string cognome;
	DATA dataNascita;
	string numeroMobile;
	string numeroFisso;
	string residenza;
	string indirizzo;
	string email;
	string note;
};

bool carica(CONTATTO r[MAX_SIZE], int &contacts);
bool salva(CONTATTO r[MAX_SIZE], int contacts);
bool aggiungi(CONTATTO r[MAX_SIZE], int &contacts);
bool rimuovi(CONTATTO r[MAX_SIZE], int currentContact, int &contacts);
bool modifica(CONTATTO r[MAX_SIZE], int &contacts);
bool visualizza(CONTATTO r[MAX_SIZE], int &contacts);

