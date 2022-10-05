#include "libs.hpp"

#include "console+vts.hpp"
#include "rubrica.hpp"

CONTATTO rubrica[MAX_SIZE];

// Loop dell'applicazione.
int loop();
// Mostra il titolo dell'applicazione.
void title();
// Mostra il menù.
void menu(string options[], bool optionsState[], int currentOption, int optionsLength);
// Mostra la dashboard.
void dashboard(bool mode, int currentContact, int &contacts);
// TOOL TIP.
void toolTip(int currentOption);

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

/*






dashboard fix separatore contaitti corti poroca9iuds





*/




int loop()
{
	// Variabile di Loop.
	bool doLoop = true;
	// Lunghezza Menù.
	int optionsLength = 18;
	
	string nome = "", cognome = "";
	
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
	dashboard(mode, currentContact, contacts);
	
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
				dashboard(mode, currentContact, contacts);
				break;
				
				/*
					COMANDI RAPIDI
				*/
				
				// Comando "Su".
			case 'A':
			case 'a':
				// In modalità semplice controllo se il prossomo elemento fa parte degli ultimi 8.
				// Why? Evitare che la tabella della dashboard presenti meno di 8 contatti anche
				// se i contatti sono più di 8. Sostanzialemente si anticipa il campo toloidale.
				if (mode)
				{
					// Ci sono pochi contatti scorro nella tabella senza cambiarla.
					if (contacts <= 8)
					{
						currentContact = currentContact - 1 >= 0 ? currentContact - 1 : contacts - 1;	
					}
					else
					{
						//currentContact = currentContact - 1 >= 0 ? currentContact - 1 : contacts - 8;
						currentContact = currentContact - 1 >= 0 ? currentContact - 1 : contacts - 1;
					}
				}
				else
				{
					currentContact = currentContact - 1 >= 0 ? currentContact - 1 : contacts - 1;
				}
				
				dashboard(mode, currentContact, contacts);			

				break;
				
				// Comando "Giù".
			case 'D':
			case 'd':
				// In modalità semplice controllo se il prossomo elemento fa parte degli ultimi 8.
				// Why? Evitare che la tabella della dashboard presenti meno di 8 contatti anche
				// se i contatti sono più di 8. Sostanzialemente si anticipa il campo toloidale.
				if (mode)
				{
					// Ci sono pochi contatti scorro nella tabella senza cambiarla.
					if (contacts <= 8)
					{
						currentContact = currentContact + 1 <= contacts - 1 ? currentContact + 1 : 0;
					}
					else
					{
						//currentContact = currentContact + 1 <= contacts - 8 ? currentContact + 1 : 0;
						currentContact = currentContact + 1 <= contacts - 1 ? currentContact + 1 : 0;
					}
				}
				else
				{
					currentContact = currentContact + 1 <= contacts - 1 ? currentContact + 1 : 0;
				}
				
				dashboard(mode, currentContact, contacts);
				break;
				
				// Comando "In Cima".
			case 'T':
			case 't':
				// Seleziono il primo contatto.
				currentContact = 0;
				dashboard(mode, currentContact, contacts);
				break;
				
				// Comando "In Fondo".
			case 'B':
			case 'b':
				// Selezione l'ultimo contatto.
				currentContact = contacts - 1;
				dashboard(mode, currentContact, contacts);
				break;
				
				// Comando "Dashboard"	
			case 'H':
			case 'h':
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

				dashboard(mode, currentContact, contacts);
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
						dashboard(mode, currentContact, contacts);
						break;
						
						// Comando "Rimuovi Contatto".
					case 2:
						rimuovi(rubrica, currentContact, contacts);
						dashboard(mode, currentContact, contacts);
						break;
						
						// Comando "Modifica Contatto".
					case 3:
						modifica (rubrica, contacts, currentContact);
						dashboard(mode, currentContact, contacts);
						break;
						
						// Comando "Filtra Contatto".
					case 4:
						
						filtra (nome,  cognome);
						break;
						
						/*
							COMANDI DASHBOARD
						*/
					
						// Comando "Su".
					case 6:
						if (currentContact - 1 >= 0)
							currentContact--;
						else
							currentContact = contacts - 1;
						
						dashboard(mode, currentContact, contacts);
						break;
						
						// Comando "Giù".
					case 7:
						if (currentContact + 1 <= contacts - 1)
							currentContact++;
						else
							currentContact = 0;
						
						dashboard(mode, currentContact, contacts);
						break;
						
						// Comando "In Cima".
					case 8:
						currentContact = 0;
						dashboard(mode, currentContact, contacts);
						break;
						
						// Comando "In Fondo".
					case 9:
						currentContact = contacts - 1;
						dashboard(mode, currentContact, contacts);
						break;
						
						// Comando "Dashboard".
					case 11:
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

						dashboard(mode, currentContact, contacts);
						break;
						
						// Comando "Ricarica".
					case 13:
						carica(rubrica, contacts);
						dashboard(mode, currentContact, contacts);
						break;
					
					// Comando "Reset".
					case 14:
						// Reset.
						system("cls");
						// Disegno la dashboard.
						dashboard(mode, currentContact, contacts);
						break;
							
						// Comando "Esci".
					case 16:
						doLoop = false;
						break;
						
					default:
						break;
				}
				
				break;
				
			case 'W':
			case 'w':
				// Oltre il limite. Imposto al minimo.
				if (currentOption - 1 < 0)
					currentOption = optionsLength - 1;
				// Opzione superiore.
				else
					currentOption--;
	
				// Seleziono il prossimo elemento abilitato.
				while (!optionsState[currentOption])
				{
					// Oltre il limite. Imposto al minimo.
					if (currentOption - 1 < 0)
						currentOption = optionsLength - 1;
					// Opzione superiore.
					else
						currentOption--;
				}
				
				break;
				
			case 'S':
			case 's':
				// Oltre il limite. Imposto al massimo.
				if (currentOption + 1 > optionsLength - 1)
					currentOption = 0;
				// Opzione inferiore.
				else
					currentOption++;
	
				// Seleziono il prossimo elemento abilitato.
				while (!optionsState[currentOption])
				{
					// Oltre il limite. Imposto al massimo.
					if (currentOption + 1 > optionsLength - 1)
						currentOption = 0;
					// Opzione inferiore.
					else
						currentOption++;
				}
				
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

void dashboard(bool mode, int currentContact, int &contacts)
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
	int advancedMaxLength = 28;
	
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
		advancedMaxLength -= 28;	
	}
	
	// Separatore.
	for (int i = 0; i < advancedMaxLength; i++)
	{
		setCursorPosition(WDSX + 24 + i, WDSY + 6);
		
		if (i == 0)
			cout << "\x1b[0K";
			
		cout << fC(opzioneDisabilitata) << "-";
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
	
	// Separatore.
	for (int i = 0; i < advancedMaxLength; i++)
	{
		setCursorPosition(WDSX + 24 + i, WDSY + 8);	
		if (i == 0)
			cout << "\x1b[0K";				
		cout << fC(opzioneDisabilitata) << "-";
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
		// Modalità 'Semplice'.
		if (mode)
		{
			//
			// Titolo.
			//
			
			setCursorPosition(WDSX + 24, WDSY + 9);
			cout << fC(240) << bC(10, 70, 125);
				
			for (int i = 0; i < 5; i++)
			{
				// Scrivo il titolo i-esimo.
				cout << simpled[i];
				
				// Aggiungo Spazi per Completare la Riga.
				for (int j = simpled[i].size(); j < simpledMaxLength[i]; j++)
					cout << " ";
					
				// Altri Campi => Aggiungo il gap.
				if (i != 4)
					cout << "   ";
				// Ultimo Campo.
				else
					cout << fC(12) << bC(12) << "#" << fC(240) << bC(12) << endl;
			}
			
			//
			// Tabella.	
			//
			
			// Massimo contatti da visualizare.
			int max = contacts <= 8 ? 8 : currentContact + 8;
			
			for (int i = contacts <= 8 ? 0 : currentContact; i < max; i++)
			{
				// Imposto la Posizione del Cursore.
				// Pochi contatti.
				if (contacts <= 8)
				{
					setCursorPosition(WDSX + 24, WDSY + 10 + i);
				}
				else
				{
					setCursorPosition(WDSX + 24, WDSY + 10 + i - currentContact);
				}
				
				// Controllo se il contatto corrente è selezionato.
				if (i == currentContact)
				{
					// Colore elemento selezionato.
					cout << bC(opzioneCorrente);
				}
				// Il contatto corrente non è selezionato.
				else
				{
					// Pochi contatti.
					if (contacts <= 8)
					{
						// Colore Riga Chiaro.
						if ((i) % 2 == 0)
							cout << bC(125);
						// Colore Riga Scuro.
						else
							cout << bC(75);
					}
					else
					{
						// Colore Riga Chiaro.
						if ((i - currentContact) % 2 == 0)
							cout << bC(125);
						// Colore Riga Scuro.
						else
							cout << bC(75);
					}
				}
					
				string word = "";
					
				// Esistono Contatti.
				if (i < contacts)
				{
					// Scorro i Campi dell'i-esimo Campo
					for (int y = 0; y < 5; y++)
					{		
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
							
						// Campo non impostato.
						if (word == "#IS_$_NULL!")
						{
							// Essendo il campo vuoto imposto word a una strina "nulla" in modo
							// tale che la compensazione della riga sia corretta.
							// #IS_$_NULL! sono più di 0 caratteri ma io non scrivi quindi il codice
							// di completamento scriverebbe pochi caratteri.
							word = "";
						}
						else
						{
							cout << word;
						}
							
						// Aggiungo Spazi per Completare la Riga.
						for (int j = word.size(); j < simpledMaxLength[y]; j++)
							cout << " ";
							
						// Altri Campi.
						if (y != 4)
							cout << "   ";
						// Ultimo Campo.
						else
							cout << fC(12) << bC(12) << "#" << fC(240) << bC(12) << endl;
					}
				}
				// Non Esistono Contatti.
				else
				{
					for (int y = 0; y < 5; y++)
					{
						// Pochi contatti.
						if (contacts <= 8)
						{
							// Colore Riga Chiaro.
							if ((i) % 2 == 0)
								cout << fC(125);
							// Colore Riga Scuro.
							else
								cout << fC(75);
						}
						else
						{
							// Colore Riga Chiaro.
							if ((i - currentContact) % 2 == 0)
								cout << fC(125);
							// Colore Riga Scuro.
							else
								cout << fC(75);
						}
					
						// Aggiungo Spazi per Completare la Riga.
						for (int j = word.size(); j < simpledMaxLength[y]; j++)
							cout << "#";
							
						// Altri Campi.
						if (y != 4)
							cout << "   ";
						// Ultimo Campo.
						else
							cout << fC(12) << bC(12) << "#" << fC(240) << endl;
					}
				}
			}
		}
		// Modalità 'Avanzata'.
		else
		{
			for (int i = 0; i < 9; i++)
			{
				setCursorPosition(WDSX + 24, WDSY + 9 + i);
				cout << fC(255);
				cout << advanced[i] << " ";
				cout << fC(100, 200, 75);
				
				cout << "\x1b[0K";
				
				string word;
				
				switch (i)
				{
					// Nome.
					case 0: word = rubrica[currentContact].nome; break;
					// Cognome.
					case 1: word = rubrica[currentContact].cognome; break;
					// Data.
					case 2: word = ""; break;
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
				
				// Campo non impostato.
				if (word == "#IS_$_NULL!")
				{
					cout << " ";
				}
				else
				{
					cout << word;
				}
				
				cout << endl;
			}
			
			cout << fC(240);
		}
	}
	
	// Separatore.
	for (int i = 0; i < advancedMaxLength; i++)
	{
		setCursorPosition(WDSX + 24 + i, WDSY + 18);
		// Pulisco la linea.	
		if (i == 0)
			cout << "\x1b[0K";			
		cout << fC(opzioneDisabilitata) << "-";
	}
	
	setCursorPosition(WDSX + 24, WDSY + 19);
	cout << fC(210, 150, 250) << bC(12) << "\x1b[3mPremi 'A' o 'D' per Scorrere. Premi 'H' per Cambiare Visualizzazione.\x1b[0m" << fC(240);
	
	// Separatore.
	for (int i = 0; i < advancedMaxLength; i++)
	{
		setCursorPosition(WDSX + 24 + i, WDSY + 20);
		// Pulisco la linea.
		if (i == 0)
			cout << "\x1b[0K";		
		cout << fC(opzioneDisabilitata) << "-";
	}
		
	// Separatore.
	for (int i = 0; i < advancedMaxLength; i++)
	{
		setCursorPosition(WDSX + 24 + i, WDSY + 22);
		// Pulisco la linea.
		if (i == 0)
			cout << "\x1b[0K";		
		cout << fC(opzioneDisabilitata) << "-";
	}
}

void toolTip(int currentOption)
{
	string tips[] = {
		"",
		"Pemette l'aggiunta di un nuovo contatto alla rubrica",
		"Permette la rimozione di un contatto esistente dalla rubrica",
		"Permette la modifica di un contatto esistente della rubrica",
		"Permette l'applicazione di filtri per la visualizzazione dei contatti dell rubrica",
		"",
		"(A) Seleziona il contatto precedente",
		"(D) Seleziona il contatto successivo",
		"(T) Seleziona il primo contatto",
		"(B) Seleziona il l'ultimo contatto",
		"",
		"Alterna la modalita' visiva della dashboard",
		"",
		"Ricarica la rubrica dal sorgente",
		"(5) Effettua un aggiornamento grafica TOTALE",
		"",
		"Termina l'applicazione ma non lo fare pls >_<",
	};
	
	setCursorPosition(WDSX + 24, WDSY + 21);
	cout << "\x1b[0K\x1b[1m" << fC(255, 190, 20) << tips[currentOption] << fC(249) << "\x1b[0m";
}

