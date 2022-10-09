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
bool uguali (CONTATTO r1, CONTATTO r2);
bool salva(CONTATTO r[MAX_SIZE], int contacts);
bool aggiungi(CONTATTO r[MAX_SIZE], int &contacts);
bool rimuovi(CONTATTO r[MAX_SIZE], int currentContact, int &contacts);
void modifica(CONTATTO r[MAX_SIZE], int &contacts, int currentContacts);
bool visualizza(CONTATTO r[MAX_SIZE], int &contacts);
void filtra (string &nome, string &cognome);
bool is_mail (string mail);
void splitstr(string str, string deli, string &string2);
bool is_num_mob (string num);

