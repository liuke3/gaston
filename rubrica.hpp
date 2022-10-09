#pragma once

#include "libs.hpp"

#define MAX_SIZE 100

struct CONTATTO
{
	string nome;
	string cognome;
	string dataNascita;
	string numeroMobile;
	string numeroFisso;
	string residenza;
	string indirizzo;
	string email;
	string note;
};

bool isDataValid(string data);
void prossimoElemento(int &opzione, int massimo, bool rF[MAX_SIZE]);
void precedenteElemento(int &opzione, int massimo, bool rF[MAX_SIZE]);
void prossimoElementoAvanzato(int &opzione, int massimo, string options[]);
void precedenteElementoAvanzato(int &opzione, int massimo, string options[]);
void coloreOpzione(int i, int currentOption, string options[]);
bool confronta (CONTATTO r1, CONTATTO r2);
bool isCampoValid(string campo, bool obbligatorio);
bool carica(CONTATTO r[MAX_SIZE], int &contacts);
bool uguali (CONTATTO r1, CONTATTO r2);
bool salva(CONTATTO r[MAX_SIZE], int contacts);
void aggiungi(CONTATTO r[MAX_SIZE], int &contacts);
void rimuovi(CONTATTO r[MAX_SIZE], int &currentContact, int &contacts);
void modifica(CONTATTO r[MAX_SIZE], int &contacts, int currentContacts);
bool visualizza(CONTATTO r[MAX_SIZE], int &contacts);
void filtra (string &nome, string &cognome, CONTATTO r[MAX_SIZE], bool rF[MAX_SIZE], int &currentContact, int contacts);
bool applicaFiltri(int campoMod, string &nome, string &cognome, CONTATTO r[MAX_SIZE], bool rF[MAX_SIZE], int &currentContact, int contacts);
bool is_mail (string mail);
void splitstr(string str, string deli, string &string2);
bool is_num_mob (string num);
bool is_num_fiss (string num);
bool only_num(string &str);

