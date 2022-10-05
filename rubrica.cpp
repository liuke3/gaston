#include "console+vts.hpp"
#include "rubrica.hpp"

//verificare se il numero è un numero!!!
//anche la mail
void modifica(CONTATTO r[MAX_SIZE], int &contacts, int currentContact) {
	
	system("cls");

	// Menù.
	string options[] = {
		"---------------",
		"Nome           ",
		"Cognome        ",
		"Data di Nascita",
		"Numero mobile  ",
		"Numero Fisso   ",
		"Residenza      ",
		"Indirizzo      ",
		"E-Mail         ",
		"Note           ",
		"---------------",
		"TORNA ALLA HOME",
		"---------------",
	};
	
	//elenco di modifica
	string modifica[] = { 
		"NOME: ",
		"COGNOME: ",
		"DATA DI NASCITA: ",
		"NUMERO MOBILE: ",
		"NUMERO FISSO: ",
		"RESIDENZA: ",
		"INDIRIZZO: ",
		"E-MAIL: ",
		"NOTE: ",
	};

	// contatto in modifica
	CONTATTO rickyguala = r[currentContact];
	// opzione selezionata
	int campoMod = 1;
	// lunghezza menu
	int optionsLength= 13;
	// loop menu
	bool doLoop = true;
	
	do {
			
		cout << "\x1b[?25l";
		
		setCursorPosition(0, 0);
		cout << endl;
		cout << fC(210, 150, 250) << " Modifica di un Contatto" << endl;
		cout << fC(100) << " -----------------------" << endl;
		cout << endl;
		
		for (int i = 0; i < optionsLength; i++) {
			
			setCursorPosition(WDSX, WDSY + i + 2);

			// Opzione Selezionata.
			if (i == campoMod) {
				
				// Opzione "Esci".
				if (options[i][0] == 'T')
					cout << fC(240) << bC(255, 0, 0);
				// Separatore.
				else if (options[i][0] == '-')
					cout << fC(opzioneDisabilitata);
				// Altre opzioni.
				else
					cout << bC(opzioneCorrente);
			}
			// Altro.
			else {
				
				// Opzione "Esci".
				if (options[i][0] == 'T')
					cout << fC(255, 0, 0);
				// Separatore.
				else if (options[i][0] == '-')
					cout << fC(opzioneDisabilitata);
				// Altre Opzioni.
				else
					cout << fC(opzioneAbilitata);
			}

			cout << options[i] << bC(12) << fC(35, 165, 100) << "   ";
			
			string valore;
			
			//mostra i valori del contatto che si sta modificando
			switch (i) {
				
				case 1: valore = rickyguala.nome; break;
				case 2: valore = rickyguala.cognome; break;
				// data
				case 4: valore = rickyguala.numeroMobile; break;
				case 5: valore = rickyguala.numeroFisso; break;
				case 6: valore = rickyguala.residenza; break;
				case 7: valore = rickyguala.indirizzo; break;
				case 8: valore = rickyguala.email; break;
				case 9: valore = rickyguala.note; break;
			}
			
			//il campo è vuoto
			if (valore=="#IS_$_NULL!") {
				cout << "";	
			}
			else {
				cout << valore;
			}
			
			cout << bC(12)<< fC(240) << endl;
		}
		
		// nascondo il cursore.
		cout<<"\x1b[?25l";
			
		// prendo l'input
		char action = _getch();

		switch (action) {
			
			case 'W':
			case 'w':
				
				// Oltre il limite. Imposto al minimo.
				if (campoMod - 1 < 0)
					campoMod = campoMod - 1;
				// Opzione superiore.
				else
					campoMod--;
	
				// Seleziono il prossimo elemento abilitato.
				while (options[campoMod][0] == '-')
				{
					// Oltre il limite. Imposto al minimo.
					if (campoMod - 1 < 0)
						campoMod = optionsLength - 1;
					// Opzione superiore.
					else
						campoMod--;
				}
				
				break;
				
			case 'S':
			case 's':
				
				// Oltre il limite. Imposto al massimo.
				if (campoMod + 1 > optionsLength - 1)
					campoMod = 0;
				// Opzione inferiore.
				else
					campoMod++;
	
				// Seleziono il prossimo elemento abilitato.
				while (options[campoMod][0] == '-')
				{
					// Oltre il limite. Imposto al massimo.
					if (campoMod + 1 > optionsLength - 1)
						campoMod = 0;
					// Opzione inferiore.
					else
						campoMod++;
				}
				
				break;
			
			case 'X':
			case 'x':
				
				system("cls");
				cout << "\x1b[?25h";
					
				cout << endl;
				cout << fC(210, 150, 250) << " Modifica di un Contatto" << endl;
				cout << fC(100) << " -----------------------" << endl;
				cout << endl;
				
				//scrivo il campo che si sta modifcando
				cout << " " << fC(240) << modifica[campoMod - 1] << fC(35, 165, 100);
				
				switch (campoMod) {
			
					case 1: //nome
						
						do {
						
							getline (cin, rickyguala.nome, '\n');	
						} while (rickyguala.nome.size() == 0);
						//il campo è obbligatorio quindi si deve per forza scrivere qualcosa
						break;
					
					case 2: //cognome
						
						do {
						
							getline (cin, rickyguala.cognome, '\n');	
						} while (rickyguala.cognome.size() == 0);
						break;
						
					case 3: //data
						
						break;
					
					case 4: //numoro mobile
			
						getline (cin, rickyguala.numeroMobile, '\n');	
			
						break;
					
					case 5: //numoro fisso
			
						getline (cin, rickyguala.numeroFisso, '\n');	
			
						break;
					
					case 6: //residenza
					
						getline (cin, rickyguala.residenza, '\n');	
			
						break;
						
					case 7: //indirizzo
						
						getline (cin, rickyguala.indirizzo, '\n');	
			
						break;
						
					case 8: //mail
						
						getline (cin, rickyguala.email, '\n');	
			
						break;
						
					case 9: //note
					
						do {
						
							getline (cin, rickyguala.note, '\n');
						} while (rickyguala.note.size() > 69);
			
						break;
						
					case 11: //esci
					
						doLoop = false;
					
						break; 
				}
				
				//pulisco solo se campomod è 11 (esci)
				if (campoMod != 11) {
					system("cls");
				}

				break;
		}
		
	} while (doLoop);

	//verifica se il ocntatto è stato effettivamente modificato per chiedere la conferma se è ancora uguale non la chiede
	if (!uguali (r[currentContact], rickyguala)) {
	
		setCursorPosition(0, 4);
		cout << fC(200) << " Modificare il Contatto? [" << fC(30, 165, 100) << "Y" << fC(200) << "/" << fC(255, 90, 70) << "N" << fC(200) << "]";
		char bho = _getch();
		
		if (bho == 'Y' || bho == 'y') {
			
			r[currentContact] = rickyguala;
			salva(r, contacts);
			
		}/* .nome */
	}
	
	cout << "\x1b[?25l";
	system("cls");
}

bool uguali (CONTATTO r1, CONTATTO r2) {
	
	if (r1.nome != r2.nome) return false;
	if (r1.cognome != r2.cognome) return false;
	//if (r1.data != r2.data) return false;
	if (r1.residenza != r2.residenza) return false;
	if (r1.indirizzo != r2.indirizzo) return false;
	if (r1.numeroFisso != r2.numeroFisso) return false;
	if (r1.note != r2.note) return false;
	if (r1.numeroMobile != r2.numeroMobile) return false;
	if (r1.email != r2.email) return false;
	
	return true;
}


/*
disabilito se c'è mc' 1 o 0 contatti
se c'è solo un contatto corrispondete non faccio fare movimenti (stack overflow)
far vedere iu filtri attivi da qualche parte

fare analisi di mercato per l'inserimento dei filtri dA QUALCHE PARTE

1. SCALARE TUTTO NO
2. (SI) ACCOPPARE LE DESCRIZIONI
*/
void filtra (string &nome, string &cognome) {
	
	string filtro2;
	int filtro;
	cout << "che filro si vuole applicare (nome, cognome, entrambi): " << endl;
	getline (cin, filtro2, '\n');
	
	if (filtro2 == "nome") filtro = 1;
	if (filtro2 == "cognome") filtro = 2;
	if (filtro2 == "entrambi") filtro = 3;
	
	switch (filtro) {
		
		case 1: //filtra per nome
			
			getline (cin, nome, '\n');
			break;
		
		case 2: //filtra per cognome
			
			getline (cin, cognome, '\n');
			break;
			
		case 3: //filtra per enrambi
		
			getline (cin, nome, '\n');
			getline (cin, cognome, '\n');
			break;
	}
}

bool carica(CONTATTO r[MAX_SIZE], int &contacts) {
	
	// Resetto il numero di contatti.
	contacts = 0;
	
	fstream f;

	// Apro il csv
	f.open("rubrica.csv", ios_base::in);
	
	if (!f.is_open()) {
		
		// manca il csv provo a crearlo
		f.open("rubrica.csv", ios_base::out);
		
		// Non si è creato
		if (!f.is_open())
			return false;
		
		// chiudo il file
		f.close();	
		// apro di nuovo il csv
		f.open("rubrica.csv", ios_base::in);
	}
	
	// linea del file
	string line;
	// campo csv
	string word;
	// counter
	int current = 0;
	
	while ( getline(f, line, '\n')) {
		
		// creo uno stream da line
		stringstream inLine(line);
		
		// contatto
		CONTATTO t;
		// data di nascita del contatto
		DATA a;
		
		for (int i = 0; i < 9; i++)	{
			
			// prendo il campo
			getline(inLine, word, '§');
			
			switch (i) {
				
				// Nome
				case 0: t.nome = word; break;
				// Cognome
				case 1: t.cognome = word; break;
				// Data di nascita
				case 2:
					a.giorno =99;
					a.mese=12;
					a.anno=29;
		
					
					t.dataNascita =a;
					/*
					
					pietro fai la data
					*/
					
					break;
				// Numero mobile
				case 3: t.numeroMobile = word; break;				
				// Numero Fisso.
				case 4: t.numeroFisso = word; break;				
				// Residenza.
				case 5: t.residenza = word; break;
				// Indirizzo.
				case 6: t.indirizzo = word; break;
				// E-Mail.
				case 7: t.email = word; break;
				// Note.
				case 8: t.note = word; break;
			}
		}
		
		r[contacts++] = t;
	}
	
	f.close();
	
	return true;
}

bool salva(CONTATTO r[MAX_SIZE], int contacts) {
	fstream f;

	f.open("rubrica.csv", ios_base::out);
	
	if (!f.is_open())
		return false;
	
	for (int i = 0; i < contacts; i++) {
	
		stringstream t;	
		t << r[i].nome;
		t << "§" << r[i].cognome;
		t << "§" << r[i].dataNascita.giorno << r[i].dataNascita.mese << r[i].dataNascita.anno;
		t << "§" << r[i].numeroMobile;
		t << "§" << r[i].numeroFisso;
		t << "§" << r[i].residenza;
		t << "§" << r[i].indirizzo;
		t << "§" << r[i].email;
		t << "§" << r[i].note;
		// converto in stringa
		f << t.str() << endl;
	}
	
	// chiudo il file
	f.close();
	
	return true;
}

bool aggiungi(CONTATTO r[MAX_SIZE], int &contacts)
{
	system("cls");
	cout << "\x1b[?25h";
	
	string fields[] = {
		"NOME: ",
		"COGNOME: ",
		"DATA DI NASCITA: ",
		"NUMERO MOBILE: ",
		"NUMERO FISSO: ",
		"RESIDENZA: ",
		"INDIRIZZO: ",
		"E-MAIL: ",
		"NOTE: ",
	};
	
	bool requiredField[] = {
		true,
		true,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
	};
	
	CONTATTO t;

	cout << endl;
	cout << fC(210, 150, 250) << " Aggiunta di un Contatto" << endl;
	cout << fC(100) << " -----------------------" << endl;
	cout << endl;
	cout << "\x1b[3m" << fC(255, 0, 0) << " * " << fC(200) << " Indica un Campo Obbligatorio";
	cout << "\x1b[0m" << endl;
	cout << " Digitare " << fC(140, 105, 175) << "!q" << fC(200) << " per Annullare" << endl;
	cout << endl;
	
	for (int i = 0; i < 9; i++)
	{
		bool ok = false;
		
		string data;
		
		while (!ok)
		{
			cout << fC(255, 0, 0);
		
			// Indicatore campo obbligatorio.
			if (requiredField[i])
				cout << " * ";	
			// Indicatore Campo Facoltativo.
			else
				cout << " ";
			
			cout << fC(255);
			cout << fields[i];
			cout << fC(35, 165, 100);
		
			getline(cin, data, '\n');
			
			// Annullo.
			if (data == "!q")
			{
				system("cls");
				cout << "\x1b[?25l";
	
				return false;	
			}
			
			// Campo Obbligatorio.
			if (requiredField[i])
			{
				// Campo Pieno.
				if (data.size() != 0)
				{
					ok = true;
				}
			}
			// Campo Facoltativo.
			else
			{
				// Campo Vuoto.
				if (data.size() == 0)
				{		
					data = "#IS_$_NULL!";
				}
				
				ok = true;
			}
		}
		
		switch (i)
		{
			// Nome.
			case 0: t.nome = data; break;
			// Cognome.
			case 1: t.cognome = data; break;
			// Data di Nascita.
			case 2: break;
			// Numero Mobile.
			case 3: t.numeroMobile = data; break;
			// Numero Fisso.
			case 4: t.numeroFisso = data; break;
			// Residenza.
			case 5: t.residenza = data; break;
			// Indirizzo.
			case 6: t.indirizzo = data; break;
			// E-Mail.
			case 7: t.email = data; break;
			// Note.
			case 8: t.note = data; break;
		}
	}
	
	cout << endl << fC(200);
	cout << " Creare il Contatto? [" << fC(30, 165, 100) << "Y" << fC(200) << "/" << fC(255, 90, 70) << "N" << fC(200) << "]";
	char key = _getch();
	bool wait = true;
		
	// Risposta Affermativa.
	if (key == 'y' || key == 'Y')
	{
		// Aggiungo.
		r[contacts++] = t;		
	}
	// Risposta Negativa.
	else
	{
		system("cls");
		cout << "\x1b[?25l";
	
		return false;
	}

	system("cls");
	cout << "\x1b[?25l";
	
	// Provo a salvare.
	if (!salva(r, contacts))
		return false;
	
	return true;
}

bool rimuovi(CONTATTO r[MAX_SIZE], int currentContact, int &contacts)
{
	system("cls");
	cout << "\x1b[?25l";
	
	cout << endl;
	cout << fC(210, 150, 250) << " Rimozione di un Contatto" << endl;
	cout << fC(100) << " ------------------------" << endl;
	cout << endl;
	
	// Nome.
	cout << fC(35, 165, 100) << " NOME:           " << fC(240) << r[currentContact].nome << endl;
	// Cognome.
	cout << fC(35, 165, 100) << " COGNOME:        " << fC(240) << r[currentContact].cognome << endl;
	// Numero Mobile.
	cout << fC(35, 165, 100) << " NUMERO MOBILE:  " << fC(240) << r[currentContact].numeroMobile << endl;
	// Numero Fisso.
	cout << fC(35, 165, 100) << " NUMERO FISSO:   " << fC(240) << r[currentContact].numeroFisso << endl;
	// E-Mail.
	cout << fC(35, 165, 100) << " E-MAIL:         " << fC(240) << r[currentContact].email << endl << endl;
	
	cout << fC(200);
	cout << " Eliminare il Contatto? [" << fC(30, 165, 100) << "Y" << fC(200) << "/" << fC(255, 90, 70) << "N" << fC(200) << "]";
	char key = _getch();
	
	system("cls");
	cout << "\x1b[?25l";
		
	// Risposta Affermativa.
	if (key == 'y' || key == 'Y')
	{
		// Shifto.
		for (int i = currentContact; i < contacts - 1; i++)
			r[i] = r[i + 1];
		
		// Ultimo contatto.
		if (contacts == 1)
		{
			currentContact = 0;
		}
		else
		{
			// Cambio il Contatto Corrente.
			currentContact--;
		}
		
		// Diminuisco il Numero di Contatti.
		contacts--;
	}
	// Risposta Negativa.
	else
	{
		return false;
	}
	
	// Provo a salvare.
	if (!salva(r, contacts))
		return false;
	
	return true;
}

