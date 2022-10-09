#include "libs.hpp"

#include "console+vts.hpp"
#include "rubrica.hpp"

// Rubrica.
CONTATTO rubrica[MAX_SIZE];
// Stato Rubrica.
bool rubricaFiltrata[MAX_SIZE] = { true };
// Filtri.
string nome = "";
string cognome = "";


// Loop dell'Applicazione.
int loop();
// Mostra il Titolo.
void title();
// Mostra il Menù.
void menu(string options[], bool optionsState[], int currentOption, int optionsLength);
// Mostra la Dashboard.
void dashboard(bool mode, int currentContact, int &contacts, bool fullDraw);
// Mostra il Tool Tip.
void toolTip(int currentOption);
void separatore(int sx, int sy, int length);
void valutaColoreRiga(int i, int contacts, int currentContact);
void completaRiga(string word, int maxLength, RGB color);
void serveUnGap(int campo, int indiceUltimoCampo);
RGB ottieniColoreRiga(int i, int contacts, int currentContact);
void nextContatto(bool mode, int &currentContact, int contacts, bool rF[MAX_SIZE]);
void previousContatto(bool mode, int &currentContact, int contacts, bool rF[MAX_SIZE]);
void changeMode(bool &mode, string options[], bool optionsState[]);


int main()
{
	// Imposto Enconding.
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	
	// Abilito le funzionalità VTS.
	// Ottengo l'Output Handle Standard.
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return -1;

    DWORD dwMode = 0;
    // Ottengo la modalità della console.
    if (!GetConsoleMode(hOut, &dwMode))
        return -1;

    dwMode |= 0x0004 | 0x0008;
    // Imposto la modalità della console.
    if (!SetConsoleMode(hOut, dwMode))
        return -1;
    
	// Imposto il colore di primo piano.
	cout << fC(defaultFC);
	// Imposto il colore di secondo piano.
	cout << bC(defaultBC);
	// Imposto il titolo della console.
	SetConsoleTitle("Gaston");

	// Chiamo il loop.
	return loop();
}


int loop()
{
	// Variabile di Loop.
	bool doLoop = true;
	// Lunghezza Menù.
	int optionsLength = 18;
		
	// Menù.
	string options[] = {
		"-------------------",
		"Aggiungi Contatto  ",
		"Rimuovi Contatto   ",
		"Modifica Contatto  ",
		"Filtra Conttatto   ",
		"-------------------",
		"Vai Su             ",
		"Vai Giu'           ",
		"Vai in Cima        ",
		"Vai in Fondo       ",
		"-------------------",
		"Dashboard: Semplice",
		"-------------------",
		"Ricarica Rubrica   ",
		"Reset Grafico      ",
		"-------------------",
		"ESCI               ",
		"-------------------",
	};
	
	// Stato Menù.
	bool optionsState[] = {
		false,
		true,
		false,
		false,
		true,
		false,
		true,
		true,
		true,
		true,
		false,
		true,
		false,
		true,
		true,
		false,
		true,
		false,
	};
	
	// Selezione Corrente.
	int currentOption = 1;
	// Numero di Contatti Totali.
	int contacts = 0;
	// Modalità Dashboard.
	// 'true'	=> Semplice.
	// 'false'	=> Avanzata.
	bool mode = true;
	// Contatto Selezionato.
	int currentContact = 0;
	
	// Carico la Rubrica.
	if (!carica(rubrica, contacts))
		return -1;
	
	// Disegno la Dashboard.
	dashboard(mode, currentContact, contacts, true);
	
	// Loop Applicazione.
	while (doLoop)
	{
		toolTip(currentOption);
			
		// Controllo il numero di contatti. Se sono troppo pochi
		// bisogna disabilitare le opzioni di socrrimento.
		for (int i = 2; i < 10; i++)
		{
			// L'opzione non è un Separatore e non è il Filtro.
			if (options[i][0] != '-' && options[i][0] != 'F')
			{
				// Non ci sono contatti quindi disabilito tutto.
				if (contacts == 0)
				{
					// Non server scorrere e non posso modificare, filtrare rimuovere nulla
					for (int o = 2; o < 10; o++)
						// L'elemento non è un separatore
						if (options[o][0] != '-')
							optionsState[o] = false;
				}
				// Un solo contatto.
				else if (contacts == 1)
				{
					// abilito tutto.
					for (int o = 2; o < 10; o++)
						// L'elemento non è un separatore
						if (options[o][0] != '-')
							optionsState[o] = true;
							
					optionsState[4] = false;
							
					// Non server scorrere.
					for (int o = 6; o < 10; o++)
						optionsState[o] = false;
				}
				// Contatti sufficienti per le features dell'applicazione.
				else
				{
					// Non server scorrere.
					for (int o = 2; o < 10; o++)
						// L'elemento non è un separatore
						if (options[o][0] != '-')
							optionsState[o] = true;
				}
			}
		}
						
		// Disegno il Titolo.
		title();
		// Disegno il Menù.
		menu(options, optionsState, currentOption, optionsLength);
		
		// Richiedo l'Input.
		char key = _getch();
		
		// Analizzo l'Input.
		switch (key)
		{
			case '5':
				// Reset.
				system("cls");
				// Disegno la dashboard.
				dashboard(mode, currentContact, contacts, true);
				break;
				
				/*
					COMANDI RAPIDI
				*/
				
				// Comando "Su".
			case 'A':
			case 'a':
				previousContatto(mode, currentContact, contacts, rubricaFiltrata);
				dashboard(mode, currentContact, contacts, false);
				break;
				
				// Comando "Giù".
			case 'D':
			case 'd':
				nextContatto(mode, currentContact, contacts, rubricaFiltrata);
				dashboard(mode, currentContact, contacts, false);
				break;
				
				// Comando "In Cima".
			case 'T':
			case 't':
				// Seleziono il Primo Contatto.
				currentContact = 0;
				dashboard(mode, currentContact, contacts, false);
				break;
				
				// Comando "In Fondo".
			case 'B':
			case 'b':
				// Seleziono l'Ultimo Contatto.
				currentContact = contacts - 1;
				dashboard(mode, currentContact, contacts, false);
				break;
				
				// Comando "Dashboard"	
			case 'H':
			case 'h':
				changeMode(mode, options, optionsState);
				dashboard(mode, currentContact, contacts, false);
				break;

				/*
					COMANDI MENU
				*/
				
				// Comando "Esegui".
			case 'X':
			case 'x':
				switch (currentOption)
				{
						/*
							COMANDI DATABASE
						*/
						
						// Comando "Aggiungi Contatto".
					case 1:
						aggiungi(rubrica, contacts);
						break;
						
						// Comando "Rimuovi Contatto".
					case 2:
						rimuovi(rubrica, currentContact, contacts);
						nome = "";
						cognome = "";
						break;
						
						// Comando "Modifica Contatto".
					case 3:
						modifica(rubrica, contacts, currentContact);
						break;
						
						// Comando "Filtra Contatto".
					case 4:
						filtra(nome, cognome, rubrica, rubricaFiltrata, currentContact,contacts);
						break;
						
						/*
							COMANDI DASHBOARD
						*/
					
						// Comando "Su".
					case 6:
						previousContatto(mode, currentContact, contacts, rubricaFiltrata);
						break;
						
						// Comando "Giù".
					case 7:
						nextContatto(mode, currentContact, contacts, rubricaFiltrata);
						break;
						
						// Comando "In Cima".
					case 8:
						currentContact = 0;
						break;
						
						// Comando "In Fondo".
					case 9:
						currentContact = contacts - 1;
						break;
						
						// Comando "Dashboard".
					case 11:
						changeMode(mode, options, optionsState);
						break;
						
						// Comando "Ricarica".
					case 13:
						carica(rubrica, contacts);
						nome = "";
						cognome = "";
						break;
					
						// Comando "Reset".
					case 14:
						system("cls");						
						break;
							
						// Comando "Esci".
					case 16:
						doLoop = false;
						break;
						
					default:
						break;			
				}
				
				dashboard(mode, currentContact, contacts, (currentOption < 6 || currentOption > 9));
				break;
				
			case 'W':
			case 'w':
				precedenteElementoAvanzato(currentOption, optionsLength, options);		
				break;
				
			case 'S':
			case 's':
				prossimoElementoAvanzato(currentOption, optionsLength, options);
				break;
				
			default:
				break;
		}
	}
	
	return 0;
}

void title()
{
	setCursorPosition(0, 1);
	
	cout << "\x1b[1m";
	cout << fC(255, 0, 0);
	cout << "     _____            _             " << endl;
	cout << fC(255, 0, 0);
	cout << "    |   __| ___  ___ | |_  ___  ___ " << endl;
	cout << fC(0, 255, 0);
	cout << "    |  |  || .'||_ -||  _|| . ||   |" << endl;
	cout << fC(0, 0, 255);
	cout << "    |_____||__,||___||_|  |___||_|_|" << endl;
	cout << fC(255, 205, 70);
	cout << endl << "    Versione 1.0.4" << endl;
	
	cout << "\x1b[0m";
}

void menu(string options[], bool optionsState[], int currentOption, int optionsLength)
{
	// Nascondo il Cursore.
	cout << "\x1b[?25l";
	
	// Scorro Opzioni Menù.
	for (int i = 0; i < optionsLength; i++)
	{
		setCursorPosition(WDSX, WDSY + 6 + i);

		// Opzione Abilitata nel Menù.
		if (optionsState[i])
		{
			// Opzione Selezionata.
			if (i == currentOption)
			{
				// Opzione "Esci".
				if (options[i][0] == 'E')
					cout << fC(240) << bC(255, 0, 0);
				// Opzione "Dashboard".
				else if (i == 11)
					cout << fC(240) << bC(50, 150, 255);
				// Altre opzioni.
				else
					cout << bC(opzioneCorrente);
			}
			// Altro.
			else
			{
				// Opzione "Esci".
				if (options[i][0] == 'E')
					cout << fC(255, 0, 0);
				// Opzione "Dashboard".
				else if (i == 11)
					cout << fC(50, 150, 255) << bC(12);
				// Altre Opzioni.
				else
					cout << fC(opzioneAbilitata);
			}
		}
		// Opzione Disabilitata nel Menù.
		else
		{
			cout << fC(opzioneDisabilitata);
		}
		
		// Il terminale di windows 10 è speciale. Questa riga oernette di evitare che i
		// colori di sfondo svaniscano.
		cout << options[i] << fC(12) << bC(12) << "#" << fC(defaultFC) << bC(defaultBC);
	}
}

void dashboard(bool mode, int currentContact, int &contacts, bool fullDraw)
{
	// Campi.
	string advanced[] = {
		"NOME:            ",
		"COGNOME:         ",
		"DATA DI NASCITA: ",
		"NUMERO MOBILE:   ",
		"NUMERO FISSO:    ",
		"RESIDENZA:       ",
		"INDIRIZZO:       ",
		"E-MAIL:          ",
		"NOTE:            ",
	};
	
	// Lunghezza Separatore.
	int advancedMaxLength = 69;
	
	// Campi.
	string simpled[] = {
		"NOME",
		"COGNOME",
		"NUMERO MOBILE",
		"NUMERO FISSO",
		"E-MAIL",
	};
	
	// Lunghezza Colonna.
	int simpledMaxLength[] = {
		4,
		7,
		13,
		12,
		6,
	};
	
	// Scorro Attributi Contatto.
	for (int i = 0; i < 5; i++)
	{
		// Scorro Rubrica.
		for (int j = 0; j < contacts; j++)
		{
			switch (i)
			{
				// Nome.
				case 0:
					if (simpledMaxLength[i] < rubrica[j].nome.size())
						simpledMaxLength[i] = rubrica[j].nome.size();
					break;
						
				// Cognome.
				case 1:
					if (simpledMaxLength[i] < rubrica[j].cognome.size())
						simpledMaxLength[i] = rubrica[j].cognome.size();
					break;
						
				// Numero Mobile.
				case 2:
					if (simpledMaxLength[i] < rubrica[j].numeroMobile.size())
						simpledMaxLength[i] = rubrica[j].numeroMobile.size();
					break;
						
				// Numero Fisso.
				case 3:
					if (simpledMaxLength[i] < rubrica[j].numeroFisso.size())
						simpledMaxLength[i] = rubrica[j].numeroFisso.size();
					break;
						
				// E-Mail.
				case 4:
					if (simpledMaxLength[i] < rubrica[j].email.size())
						simpledMaxLength[i] = rubrica[j].email.size();
					break;
			}
		}
	}
	
	
		
	//
	//	Dimensione Separatore.
	//
		
	// Non ci sono contatti. Il separatore deve avere una dimensione fissa.
	if (contacts == 0)
	{
		// Dimensione fissa.
		advancedMaxLength = 69;
	}
	// Calcolo la dimensione adattiva del separatore.
	else
	{
		// Calcolo Dimensione Separatori.
		for (int i = 0; i < 5; i++)
			// Aggiungo Massima Lunghezza Colonna.
			advancedMaxLength += simpledMaxLength[i];
				
		// Aggiungo Separatori.
		advancedMaxLength += 12;
		// Tolgo Dimensione Iniziale.
		advancedMaxLength -= 69;	
	}
	

	//
	//	Indicatore Contatti.
	//
	
	setCursorPosition(WDSX + 24, WDSY + 7);
	cout << "\x1b[0K";
	
	// Non ci sono contatti.
	if (contacts == 0)
	{
		cout << fC(150, 210, 240) << "0 Contatti";
	}
	// Ci sono contatti.
	else
	{
		// Modalità 'Semplice'.
		if (mode)
		{
			cout << fC(150, 210, 240) << "\x1b[3mContatti " << currentContact + 1 << "..";
				
			if (contacts < 8 || contacts - currentContact < 8)
				cout << contacts << " di " << contacts << "\x1b[0m" << fC(240);
			else
				cout << currentContact + 8 << " di " << contacts << "\x1b[0m" << fC(240);
		}
		// Modalità 'Avanzata'.
		else
		{
			cout << fC(150, 210, 240) << "\x1b[3mContatto " << currentContact + 1 << " di " << contacts << "\x1b[0m"  << fC(240);
		}
	}
	

		
	//
	//	Contenuto
	//
	
	// Non ci sono Contatti.
	if (contacts == 0)
	{
		// Pulisco le righe dove c'è la visualizzazione dei contatti.
		for (int i = 0; i < 10; i++)
		{
			setCursorPosition(WDSX + 24, WDSY + 9 + i);
			cout << "\x1b[0K";
		}
		
		// Messaggio.
		setCursorPosition(WDSX + 24, WDSY + 10);
		cout << fC(255, 230, 70) << "Ops! La rubrica e' vuota!";
		setCursorPosition(WDSX + 24, WDSY + 11);
		cout << "Seleziona 'Aggiungi Contatto' per iniziare subito!" << fC(240);
	}
	// Ci sono Contatti.
	else
	{
		//
		//	Modalità 'Semplice'.
		//
		if (mode)
		{
			//
			//	Titolo Tabella.
			//
			
			setCursorPosition(WDSX + 24, WDSY + 9);
					
			// Scrivo il Titolo I-Esimo.
			for (int i = 0; i < 5; i++)
			{
				cout << fC(240) << bC(10, 70, 125) << simpled[i];
				completaRiga(simpled[i], simpledMaxLength[i], RGB{ 10, 70, 125 });
				serveUnGap(i, 4);
			}
			
			
			
			//
			// Tabella.	
			//
			
			// Massimo Numero di Contatti da Visualizare.
			int max = contacts <= 8 ? 8 : currentContact + 8;
			
			// Scorro i Contatti da Visualizzare.
			for (int i = contacts <= 8 ? 0 : currentContact; i < max; i++)
			{
				// Pochi Contatti.
				if (contacts <= 8)
					setCursorPosition(WDSX + 24, WDSY + 10 + i);
				else
					setCursorPosition(WDSX + 24, WDSY + 10 + i - currentContact);
				
				valutaColoreRiga(i, contacts, currentContact);
				
				// Campo.	
				string word = "";
					
				// Esistono Ancora Contatti.
				if (i < contacts)
				{
					// Scorro i Campi dell'i-esimo Campo
					for (int y = 0; y < 5; y++)
					{		
						// Campo del Contatto.
						switch (y)
						{
							// Nome.
							case 0: word = rubrica[i].nome; break;
							// Cognome.
							case 1: word = rubrica[i].cognome; break;	
							// Numero Mobile.
							case 2: word = rubrica[i].numeroMobile; break;
							// Numero Fisso.
							case 3: word = rubrica[i].numeroFisso; break;
							// E-Mail.
							case 4: word = rubrica[i].email; break;
						}
						
						// Campo non Impostato.
						if (word == "#IS_$_NULL!")
							word = "";
						else
							cout << fC(240) << word;
						
						valutaColoreRiga(i, contacts, currentContact);
						completaRiga(word, simpledMaxLength[y], ottieniColoreRiga(i, contacts, currentContact));
						serveUnGap(y, 4);
					}
				}
				//
				//	Sono Finiti i Contatti.
				//
				else
				{
					// Riempo la Tabella con Righe Vuote.
					for (int y = 0; y < 5; y++)
					{
						valutaColoreRiga(i, contacts, currentContact);
						completaRiga(word, simpledMaxLength[y], ottieniColoreRiga(i, contacts, currentContact));
						serveUnGap(y, 4);
					}
				}
			}
		}
		//
		//	Modalità 'Avanzata'.
		//
		else
		{
			// Scorro Campi del Contatto Corrente.
			for (int i = 0; i < 9; i++)
			{
				// Scrivo la Descrizione del Campo.
				setCursorPosition(WDSX + 24, WDSY + 9 + i);
				cout << fC(255) << advanced[i] << " " << fC(100, 200, 75);		
				// Cancello Linea.
				cout << "\x1b[0K";		
				// Valore I-Esimo Campo.
				string word;
				
				// Selezione I-Esimo Campo.
				switch (i)
				{
					// Nome.
					case 0: word = rubrica[currentContact].nome; break;
					// Cognome.
					case 1: word = rubrica[currentContact].cognome; break;
					// Data.
					case 2: word = rubrica[currentContact].dataNascita; break;
					// Numero Mobile.
					case 3: word = rubrica[currentContact].numeroMobile; break;
					// Numero Fisso.
					case 4: word = rubrica[currentContact].numeroFisso; break;
					// Residenza.
					case 5: word = rubrica[currentContact].residenza; break;
					// Indirizzo.
					case 6: word = rubrica[currentContact].indirizzo; break;
					// E-Mail.
					case 7: word = rubrica[currentContact].email; break;
					// Note.
					case 8: word = rubrica[currentContact].note; break;
				}
				
				// Campo non Impostato.
				if (word == "#IS_$_NULL!")
					cout << " " << endl << fC(240);
				else
					cout << word << endl << fC(240);
			}
		}
	}
		
	// Mostro Filtri Applicati.
	setCursorPosition(WDSX + 24, WDSY + 19);
	cout << fC(200) << "Nome:    " << fC(210, 150, 250) << bC(12) << "\x1b[3m" << nome << "\x1b[0m" << fC(240);
	setCursorPosition(WDSX + 24, WDSY + 20);
	cout << fC(200) << "Cognome: " << fC(210, 150, 250) << bC(12) << "\x1b[3m" << cognome << "\x1b[0m" << fC(240);
	
	// Disegno Separatori.
	if (fullDraw)
	{
		separatore(WDSX + 24, WDSY + 6, advancedMaxLength);
		separatore(WDSX + 24, WDSY + 8, advancedMaxLength);
		separatore(WDSX + 24, WDSY + 18, advancedMaxLength);
		separatore(WDSX + 24, WDSY + 21, advancedMaxLength);
		separatore(WDSX + 24, WDSY + 23, advancedMaxLength);
	}
}

// Fornisce una Spiegazione Semplice dell'Opzione Selezionata.
void toolTip(int currentOption)
{
	string tips[] = {
		"",
		"Permette l'Aggiunta di un Nuovo Contatto alla Rubrica",
		"Permette la Rimozione di un Contatto Esistente dalla Rubrica",
		"Permette la Modifica di un Contatto Esistente della Rubrica",
		"Permette il Filtraggio dei Contatti Esistenti della Rubrica",
		"",
		"(A) Seleziona il Contatto Precedente",
		"(D) Seleziona il Contatto Successivo",
		"(T) Seleziona il Primo Contatto",
		"(B) Seleziona il l'Ultimo Contatto",
		"",
		"(H) Cambia la Modalita' della Dashboard'",
		"",
		"Ricarica la Rubrica dal Database",
		"(5) Effettua il Reset Grafico",
		"",
		"Termina l'Applicazione",
	};
	
	setCursorPosition(WDSX + 24, WDSY + 22);
	cout << "\x1b[0K\x1b[1m" << fC(255, 190, 20) << tips[currentOption] << fC(249) << "\x1b[0m";
}

// Disegna un Separatore alle Coordinate 'x' e 'y' di Lunghezza 'lenght'.
void separatore(int sx, int sy, int length)
{
	for (int i = 0; i < length; i++)
	{
		setCursorPosition(sx + i, sy);

		// Pulisco la linea.
		if (i == 0)
			cout << "\x1b[0K";
		
		cout << fC(opzioneDisabilitata) << "-";
	}
}


// Decide il Colore da Assegnare alla Riga I-Esima della Tabella.
void valutaColoreRiga(int i, int contacts, int currentContact)
{
	// Ottengo Colore Riga.
	RGB t = ottieniColoreRiga(i, contacts, currentContact);
	// Imposto Colore Riga.
	cout << fC(t) << bC(t);	
}


// Ottiene il Colore della Riga I-Esima.
RGB ottieniColoreRiga(int i, int contacts, int currentContact)
{
	// Contatto Corrente.
	if (i == currentContact)
		return opzioneCorrente;
	
	// Pochi contatti.
	if (contacts <= 8)
	{
		// Colore Riga Chiaro.
		if ((i) % 2 == 0)
			return RGB{ 125, 125, 125 };
		// Colore Riga Scuro.
		else
			return RGB{ 75, 75, 75 };
		}
	// Molti Contatti.
	else
	{
		// Colore Riga Chiaro.
		if ((i - currentContact) % 2 == 0)
			return RGB{ 125, 125, 125 };
		// Colore Riga Scuro.
		else
			return RGB{ 75, 75, 75 };
	}
}


// Aggiungi N Spazi Vuoti per Completare la Riga.
void completaRiga(string word, int maxLength, RGB color)
{
	cout << bC(color) << fC(color);
	
	// Aggiungo Spazi per Completare la Riga.
	for (int j = word.size(); j < maxLength; j++)
		cout << "#";
}


// Agggiune un Gap alla Fine della Riga Corrente oppure il Reset Linea.
void serveUnGap(int campo, int indiceUltimoCampo)
{
	// Altri Campi.
	if (campo != indiceUltimoCampo)
		cout << "   ";
	// Ultimo Campo.
	else
		cout << fC(12) << bC(12) << "#" << fC(240) << endl;
}


// Seleziona il Prossimo Contatto della Rubrica.
void nextContatto(bool mode, int &currentContact, int contacts, bool rF[MAX_SIZE])
{
	// No Filtri.
	if (nome == "" && cognome == "")
		currentContact = currentContact + 1 <= contacts - 1 ? currentContact + 1 : 0;
	// Ci sono i Filtri.
	else
	{
		// Salvo il currentContact Iniziale per Evitare Loop.		
		int iniziale = currentContact;
		
		// Cerco il Prossimo Coso.
		do
		{
			currentContact = currentContact + 1 <= contacts - 1 ? currentContact + 1 : 0;
			
			// Un solo Contatto Corrisponde ai Filtri.
			if (iniziale == currentContact)
				break;	
		}
		while (!rF[currentContact]);
	}
}


// Seleziona il Precedente Contatto Della Rubrica.
void previousContatto(bool mode, int &currentContact, int contacts, bool rF[MAX_SIZE])
{
	// No Filtri.
	if (nome == "" && cognome == "")
		currentContact = currentContact - 1 >= 0 ? currentContact - 1 : contacts - 1;
	// Ci sono i Filtri.
	else
	{
		// Salvo il currentContact Iniziale per Evitare Loop.		
		int iniziale = currentContact;
		
		// Cerco il Prossimo Coso.
		do
		{
			currentContact = currentContact - 1 >= 0 ? currentContact - 1 : contacts - 1;
			
			// Un solo Contatto Corrisponde ai Filtri.
			if (iniziale == currentContact)
				break;
			
		}
		while (!rF[currentContact]);
	}
}


// Cambia la Modalità della Dashboard.
void changeMode(bool &mode, string options[], bool optionsState[])
{
	// Inverto la Modalità.
	mode = !mode;
				
	// Dashboard "Semplice".
	if (mode)
		options[11] = "Dashboard: Semplice";
	// Dashboard "Avanzata".
	else
		options[11] = "Dashboard: Avanzata";
				
	// Richiedono la modalità avanzata.
	optionsState[2] = !mode;
	optionsState[3] = !mode;
}

