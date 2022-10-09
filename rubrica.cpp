#include "console+vts.hpp"
#include "rubrica.hpp"

void prossimoElemento(int &opzione, int massimo)
{
	if (opzione + 1 <= massimo - 1)
		opzione++;
	else
		opzione = 0;
}


void precedenteElemento(int &opzione, int massimo)
{
	if (opzione - 1 >= 0)
		opzione--;
	else
		opzione = massimo - 1;
}


void prossimoElementoAvanzato(int &opzione, int massimo, string options[])
{
	// Oltre il limite. Imposto al massimo.
	if (opzione + 1 > massimo - 1)
		opzione = 0;
	// Opzione inferiore.
	else
		opzione++;
	
	// Seleziono il prossimo elemento abilitato.
	while (options[opzione][0] == '-')
	{
		// Oltre il limite. Imposto al massimo.
		if (opzione + 1 > massimo - 1)
			opzione = 0;
		// Opzione inferiore.
		else
			opzione++;
	}				
}


void precedenteElementoAvanzato(int &opzione, int massimo, string options[])
{
	// Oltre il limite. Imposto al minimo.
	if (opzione - 1 < 0)
		opzione = massimo - 1;
	// Opzione superiore.
	else
		opzione--;
	
	// Seleziono il prossimo elemento abilitato.
	while (options[opzione][0] == '-')
	{
		// Oltre il limite. Imposto al minimo.
		if (opzione - 1 < 0)
			opzione = massimo - 1;
		// Opzione superiore.
		else
			opzione--;
	}
}


void coloreOpzione(int i, int currentOption, string options[])
{
	// Opzione Selezionata.
	if (i == currentOption)
	{			
		// Opzione "Esci".
		if (options[i][0] == 'T')
			cout << fC(240) << bC(255, 0, 0);
		// Separatore.
		else if (options[i][0] == '-')
			cout << fC(opzioneDisabilitata);
		// Altre opzioni.
		else
			cout << fC(240) << bC(opzioneCorrente);
		}
	// Altro.
	else
	{	
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
}


// Controlla se un campo generico è valido
bool isCampoValid(string campo, bool obbligatorio)
{	
	// Inserisco Indicatore Campo non Inizializzato.
	if (campo.size() == 0)
		campo = "#IS_$_NULL!";
			
	// Controllo se il Campo Contiene il Carattere Separatore.
	if (campo.find("§") != std::string::npos)
		return false;

	if (obbligatorio)
		return campo.size() > 0 && campo.size() <= 70;
		
	return campo.size() <= 70;
}


// Controlla se il Formato della Data è Valido.
bool isDataValid(string data)
{
	//campo vuoto.
	if (data.size() == 0 || data == "#IS_$_NULL!" || data == "")
		return true;
	
	// DD/MM/YYYY.	
	if (data.size() != 10)
		return false;
	
	string giorno = "";
	string mese = "";
	string anno = "";
	
	int c = 0;
	
	for (int i = 0; i < 10; i++)
	{
		if (c == 0)
		{
			if (data[i] == '/')
				c++;
			else
				giorno += data[i];
		}
		else if (c == 1)
		{
			if (data[i] == '/')
				c++;
			else
				mese += data[i];		
		}
		else if (c == 2)
			anno += data[i];
	}
		
	if (giorno.size() < 1 || giorno.size() > 2)
		return false;
		
	if (mese.size() < 1 || mese.size() > 2)
		return false;
			
	if (anno.size() != 4)
		return false;
		
	/*
	if (stoi(giorno) < 0 || stoi(giorno) > 31)
		return false;
		
	if (stoi(mese, nullptr) < 0 || stoi(mese, nullptr) > 12)
		return false;
		
	if (stoi(anno, nullptr) < 0 || stoi(anno, nullptr) > 9999)
		return false;
	
	int giorniPerMese[] = {
		31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};
	
	if (stoi(giorno, nullptr) > giorniPerMese[stoi(mese, nullptr) - 1])
		return false;
	*/
	
	return true;
}


void modifica(CONTATTO r[MAX_SIZE], int &contacts, int currentContact) {
	
	system("cls");

	// Menù.
	string options[] = {
		"---------------",
		"Nome           ",
		"Cognome        ",
		"Data di Nascita",
		"Numero Mobile  ",
		"Numero Fisso   ",
		"Residenza      ",
		"Indirizzo      ",
		"E-Mail         ",
		"Note           ",
		"---------------",
		"TORNA ALLA HOME",
		"---------------",
	};
	
	// Elenco di Modifica.
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
	
	// Contatto in Modifica.
	CONTATTO rickyguala = r[currentContact];
	// Opzione Selezionata.
	int campoMod = 1;
	// Lunghezza Menù.
	int optionsLength= 13;
	// Loop Menù.
	bool doLoop = true;
	
	bool ok = false;
	
	do {
			
		setCursorPosition(0, 0);
		cout << "\x1b[?25l" << endl << fC(210, 150, 250) << " Modifica di un Contatto" << endl;
		cout << fC(100) << " -----------------------" << endl << endl;
		cout << "\x1b[3m" << fC(255, 0, 0) << " * " << fC(200) << "Indica un Campo Obbligatorio";
		cout << "\x1b[0m" << endl;
		cout << " Il carattere " << fC(255, 175, 90) << "§" << fC(200) << " non puo' essere usato!" << endl;
		cout << endl;
		
		for (int i = 0; i < optionsLength; i++) {
			
			setCursorPosition(WDSX, WDSY + i + 5);
			coloreOpzione(i, campoMod, options);
			cout << options[i] << bC(12) << fC(35, 165, 100) << "   ";
			
			string valore;
			
			//mostra i valori del contatto che si sta modificando
			switch (i) {
				
				case 1: valore = rickyguala.nome; break;
				case 2: valore = rickyguala.cognome; break;
				case 3: valore = rickyguala.dataNascita; break;
				case 4: valore = rickyguala.numeroMobile; break;
				case 5: valore = rickyguala.numeroFisso; break;
				case 6: valore = rickyguala.residenza; break;
				case 7: valore = rickyguala.indirizzo; break;
				case 8: valore = rickyguala.email; break;
				case 9: valore = rickyguala.note; break;
			}
			
			//il campo è vuoto
			if (valore=="#IS_$_NULL!")
				cout << "" << bC(12)<< fC(240) << endl;
			else
				cout << valore << bC(12)<< fC(240) << endl;
		}
		
		// nascondo il cursore.
		cout<<"\x1b[?25l";		
		// prendo l'input
		char action = _getch();

		// controllo azione
		switch (action) {
			
			case 'W':
			case 'w':		
				precedenteElementoAvanzato(campoMod, optionsLength, options);
				break;
				
			case 'S':
			case 's':
				prossimoElementoAvanzato(campoMod, optionsLength, options);
				break;
			
			case 'X':
			case 'x':		
				system("cls");
				
				cout << "\x1b[?25h" << endl << fC(210, 150, 250) << " Modifica di un Contatto" << endl;
				cout << fC(100) << " -----------------------" << endl << endl;
		
				if (campoMod == 3)
					cout << fC(200) << " La Data va Fornita nel Formato dd/mm/yyyy" << endl;
				
				//indicatore campo obbligatorio
				if (campoMod == 1 || campoMod == 2)
					cout << fC(255, 0, 0) << " * ";
				else
					cout << " ";

				cout  << fC(240) << modifica[campoMod - 1] << fC(35, 165, 100);
			
				switch (campoMod) {
			
					case 1: //nome (campo obbligatorio)
												
						getline (cin, rickyguala.nome, '\n');
						
						if (!isCampoValid(rickyguala.nome, true))
							rickyguala.nome = r[currentContact].nome;

						break;
					
					case 2: //cognome (campo obbligatorio)

						getline (cin, rickyguala.cognome, '\n');	
						
						if (!isCampoValid(rickyguala.cognome, true))
							rickyguala.cognome = r[currentContact].cognome;
						
						break;
						
					case 3: //data
						
						getline (cin, rickyguala.dataNascita, '\n');

						if (!isDataValid(rickyguala.dataNascita));
							rickyguala.dataNascita = r[currentContact].dataNascita;
							
						break;
					
					case 4: //numero mobile
						
						getline (cin, rickyguala.numeroMobile, '\n');
						
						if (!is_num_mob(rickyguala.numeroMobile))
							rickyguala.numeroMobile = r[currentContact].numeroMobile;
						
						break;
					
					case 5: //numoro fisso

						getline (cin, rickyguala.numeroFisso, '\n');
						
						if (!is_num_fiss(rickyguala.numeroFisso))
							rickyguala.numeroFisso = r[currentContact].numeroFisso;
			
						break;
					
					case 6: //residenza

						getline (cin, rickyguala.residenza, '\n');
						
						if (!isCampoValid(rickyguala.residenza, false))
							rickyguala.residenza = r[currentContact].residenza;
			
						break;
						
					case 7: //indirizzo

						getline (cin, rickyguala.indirizzo, '\n');
						
						if (!isCampoValid(rickyguala.indirizzo, false))
							rickyguala.indirizzo = r[currentContact].indirizzo;
			
						break;
						
					case 8: //e-mail
						
				
						getline (cin, rickyguala.email, '\n');
						
					 	if (!is_mail(rickyguala.email))
					 		rickyguala.email = r[currentContact].email;
			
						break;
						
					case 9: //note
					
						getline (cin, rickyguala.note, '\n');
						
						
						if (!isCampoValid(rickyguala.note, false))
							rickyguala.note = r[currentContact].note;
			
						break;
						
					case 11: //esci
					
						doLoop = false;
					
						break; 
				}
				
				//pulisco solo se 'campoMod' è 11 (esci)
				if (campoMod != 11) {
					
					system("cls");
				}

				break;
		}
		
	} while (doLoop);
	
	cout << "\x1b[?25l";
	
	//verifica se il ocntatto è stato effettivamente modificato per chiedere la conferma se è ancora uguale non la chiede
	if (!uguali (r[currentContact], rickyguala)) {
	
		setCursorPosition(0, 4);
		cout << fC(200) << " Modificare il Contatto? [" << fC(30, 165, 100) << "Y" << fC(200) << "/" << fC(255, 90, 70) << "N" << fC(200) << "]";
		
		char bho = _getch();
		
		while (bho != 'Y' && bho != 'y' && bho != 'N' && bho != 'n')
			bho = _getch();
		
		if (bho == 'Y' || bho == 'y') {
			
			r[currentContact] = rickyguala;
			salva(r, contacts);	
		}
	}
	
	cout << "\x1b[?25l";
	system("cls");
}

//verifica se due contatti sono uguali
bool uguali (CONTATTO r1, CONTATTO r2) {
	
	// controllo campo per campo se ci sono differenze
	if (r1.nome != r2.nome) return false;
	if (r1.cognome != r2.cognome) return false;
	if (r1.dataNascita != r2.dataNascita) return false;
	if (r1.residenza != r2.residenza) return false;
	if (r1.indirizzo != r2.indirizzo) return false;
	if (r1.numeroFisso != r2.numeroFisso) return false;
	if (r1.note != r2.note) return false;
	if (r1.numeroMobile != r2.numeroMobile) return false;
	if (r1.email != r2.email) return false;
	
	return true;
}


// Confronta due contatti per nome e cognome e stabilisce quale viene prima.
// True  => Contatto 1 viene prima.
// False => Contatto 1 viene dopo.
bool confronta (CONTATTO r1, CONTATTO r2) {
	
	string fullNameR1 = r1.nome + " " + r1.cognome;
	string fullNameR2 = r2.nome + " " + r2.cognome;
	
	return fullNameR1 < fullNameR2;
}


void filtra (string &nome, string &cognome, CONTATTO r[MAX_SIZE], bool rF[MAX_SIZE], int &currentContact, int contacts)
{			
	// Menù.
	string options[] = {
		"---------------",
		"Nome           ",
		"Cognome        ",
		"Nome e Cognome ",
		"---------------",
		"Reset          ",
		"---------------",
		"TORNA ALLA HOME",
		"---------------",
	};
	
	// Lunghezza Menù.
	int optionsLength = 9;	
	// Opzione Selezionata.
	int campoMod = 1;
	// Variabile di Controllo.
	bool ok = false;

	system("cls");
	cout << endl;
	cout << fC(210, 150, 250) << " Filtri di un Contatto" << endl;
	cout << fC(100) << " ---------------------"<< endl;
	cout << endl;

	while (!ok)
	{
		setCursorPosition(0, WDSY + 2);
		cout << fC(200) << "\x1b[0K Nome:    " << fC(210, 150, 250) << bC(12) << "\x1b[3m" << nome << "\x1b[0m" << fC(240);
		setCursorPosition(0, WDSY + 3);
		cout << fC(200) << "\x1b[0K Cognome: " << fC(210, 150, 250) << bC(12) << "\x1b[3m" << cognome << "\x1b[0m" << fC(240);
	
		for (int i = 0; i < optionsLength; i++)
		{
			setCursorPosition(WDSX, WDSY + i + 5);
			coloreOpzione(i, campoMod, options);
			cout << options[i] << bC(12) << fC(35, 165, 100) << "   ";
		}
				
		// Nascondo il Cursore.
		cout<<"\x1b[?25l";			
		// Prendo l'Input.
		char action = _getch();

		// Controllo Azione.
		switch (action)
		{
			case 'W':
			case 'w':		
				precedenteElementoAvanzato(campoMod, optionsLength, options);
				break;
				
			case 'S':
			case 's':
				prossimoElementoAvanzato(campoMod, optionsLength, options);
				break;
			
			case 'X':
			case 'x':		
				system("cls");					
				cout << "\x1b[?25h" << endl;
				cout << fC(210, 150, 250) << " Filtri di un Contatto" << endl;
				cout << fC(100) << " ---------------------" << endl;
				cout << endl;

				switch (campoMod)
				{			
					case 1: // Filtra per Nome.
						cout << fC(240) << " NOME: " << fC(65, 130, 115);	
						getline (cin, nome, '\n');
						break;
						
					case 2: // Filtra per Cognome.
					cout << fC(240) << " COGNOME: " << fC(65, 130, 115);		
						getline (cin, cognome, '\n');
						break;
							
					case 3: //filtra per Nome e Cognome.
						cout << fC(240) << " NOME: " << fC(65, 130, 115);	
						getline (cin, nome, '\n');
						cout << fC(240) << " COGNOME: " << fC(65, 130, 115);	
						getline (cin, cognome, '\n');
						break;
						
					case 5:
						nome = "";
						cognome = "";
						break;
						
					case 7:
						ok = true;
						break;	
				}
				
				cout << fC(240);
		
				if (campoMod >= 1 && campoMod <= 3)
				{
					if (!applicaFiltri(campoMod, nome, cognome, r, rF, currentContact, contacts))
					{
						MessageBox(NULL, "Nessuno Contatto Corrispondente ai Filtri!", "Gaston", MB_OK | MB_ICONERROR);
						nome = "";
						cognome = "";				
					}				
				}
			
				break;
		}
	}
	
	system("cls");
}


bool applicaFiltri(int campoMod, string &nome, string &cognome, CONTATTO r[MAX_SIZE], bool rF[MAX_SIZE], int &currentContact, int contacts)
{
// Sono stati Impostati dei Filtri.
				if (nome != "" && nome != "")
				{
					// Scorro i Contatti.
					for (int i = 0; i < contacts; i++)
					{
						bool showIt = false;
						
						// Scorro Filtri.
						switch (campoMod)
						{		
								// Filtro Nome.
							case 1:
								if (r[i].nome.find(nome) != string::npos)
							    	showIt = true;				
								break;
								
								// Filtro Cognome.
							case 2:
								if (r[i].cognome.find(cognome) != string::npos)
							    	showIt = true;				
								break;
								
								// Filtro Nome e Cognome.
							case 3:
								if (r[i].nome.find(nome) != string::npos && r[i].cognome.find(cognome) != string::npos)
							    	showIt = true;
								break;
						}
						
						rF[i] = showIt;
					}
					
					// Numero Totale Contatti Corrispondente ai Filtri.
					int conto = 0;
					// Primo Contatto che Rispetta i Filtri.
					int primo = -1;
					
					// controllo se c'è roba che corrisponde ai filtri.
					for (int i = 0; i < contacts; i++)
					{
						// Il Contatto I-Esimo Rispetta i Filtri.
						if (rF[i])
						{
							if (primo < 0)
								primo = i;
								
							// Aumento Contatti con i Filtri.
							conto++;
						}
					}
						
					// Accetto i Filtri.
					if (conto > 0)
					{
						// Imposto il Primo Contatto che ha i Filtri Giusti.
						currentContact = primo;
						//
						return true;
					}
					else
					{

						return false;
					}
				}
				
				
				else
				{
					return true;
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
		
		for (int i = 0; i < 9; i++)	{
			
			// prendo il campo
			getline(inLine, word, '§');
			
			switch (i) {
				
				// Nome
				case 0: t.nome = word; break;
				// Cognome
				case 1: t.cognome = word; break;
				// Data di nascita
				case 2: t.dataNascita = word; break;
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
		
		if (!isCampoValid(t.nome, true) ||
			!isCampoValid(t.cognome, true) ||
			!isDataValid(t.dataNascita) ||
			!is_num_mob(t.numeroMobile) ||
			!is_num_fiss(t.numeroFisso) ||
			!isCampoValid(t.residenza, false) ||
			!isCampoValid(t.indirizzo, false) ||
		//	!is_mail(t.email) ||
			!isCampoValid(t.note, false))
		{
			MessageBox(NULL, "ERRORE GREVISSIMO! UN DATO NON E' CORRETTO!!!", "Gaston", MB_OK | MB_ICONERROR);
			exit(-104);
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
		t << "§" << r[i].dataNascita;
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


void aggiungi(CONTATTO r[MAX_SIZE], int &contacts)
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

	cout << endl << fC(210, 150, 250) << " Aggiunta di un Contatto" << endl;
	cout << fC(100) << " -----------------------" << endl << endl;	
	cout << "\x1b[3m" << fC(255, 0, 0) << " * " << fC(200) << "Indica un Campo Obbligatorio" << "\x1b[0m" << endl;
	cout << " Digitare " << fC(140, 105, 175) << "!q" << fC(200) << " per Annullare" << endl;
	cout << " Il carattere " << fC(255, 175, 90) << "§" << fC(200) << " non puo' essere usato!" << endl << endl;
	
	for (int i = 0; i < 9; i++)
	{
		// Variabile di controllo dell'input
		bool ok = false;	
		//campo di memorizzazione temporaneo
		string data;
		
		while (!ok) {
			
			cout << fC(255, 0, 0);
		
			if (i == 2)
			{
				cout << fC(200) << " La Data va Fornita nel Formato dd/mm/yyyy" << endl;
			}		
			
			//indicatore campo obbligatorio
			if (requiredField[i])
				cout << " * ";
			// Indicatore Campo Facoltativo.
			else
				cout << " ";
		
			cout << fC(255) << fields[i] << fC(35, 165, 100);
		
			// Ottengo l'Input.
			getline(cin, data, '\n');
			
			// Controllo Input.
			switch (i)
			{
				// Data di Nascita.
				case 2:
					if (isDataValid(data))
						ok = true;
					break;
				
				// Numero Mobile.
				case 3:
					if (is_num_mob(data))
						ok = true;
					break;
					
				// Numero Fisso.
				case 4:
					if (is_num_fiss(data))
						ok = true;
					break;
					
				// E-Mail.
				case 7:
					if (is_mail(data))
						ok = true;			
					break;
					
				// Altri Campi.
				default:
					if (isCampoValid(data, requiredField[i]))
						ok = true;
					break;
			}

			// Annullo.
			if (data == "!q")
			{
				system("cls");
				cout << "\x1b[?25l";
				return;
			}
		}
		
		switch (i)	{
			
			// Nome.
			case 0: t.nome = data; break;
			// Cognome.
			case 1: t.cognome = data; break;
			// Data di Nascita.
			case 2: t.dataNascita = data; break;
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
	
	cout << "\x1b[?25l" << endl << fC(200);
	cout << " Creare il Contatto? [" << fC(30, 165, 100) << "Y" << fC(200) << "/" << fC(255, 90, 70) << "N" << fC(200) << "]";
	
	char key = _getch();
	
	//attendo tasto validoo
	while (key != 'Y' && key != 'y' && key != 'N' && key != 'n')
		key = _getch();
		
	system("cls");
	cout << "\x1b[?25l";
	
	// Crea Contatto.
	if (key == 'y' || key == 'Y')
	{		
		// Aggiungo.
		r[contacts++] = t;	
		
		// Provo a Salvare.
		if (!salva(r, contacts))
		{
			// Non Salva >:(.
			MessageBox(NULL, "NON E' STATO POSSIBILE SALVARE LA RUBRICA!!!", "Gaston", MB_OK | MB_ICONERROR);
		}
	}
}


void rimuovi(CONTATTO r[MAX_SIZE], int &currentContact, int &contacts) {
	
	system("cls");
	cout << "\x1b[?25l" << endl << fC(210, 150, 250) << " Rimozione di un Contatto" << endl;
	cout << fC(100) << " ------------------------" << endl << endl;
	cout << fC(35, 165, 100) << " NOME:           " << fC(240) << r[currentContact].nome << endl;
	cout << fC(35, 165, 100) << " COGNOME:        " << fC(240) << r[currentContact].cognome << endl;
	cout << fC(35, 165, 100) << " NUMERO MOBILE:  " << fC(240) << r[currentContact].numeroMobile << endl;
	cout << fC(35, 165, 100) << " NUMERO FISSO:   " << fC(240) << r[currentContact].numeroFisso << endl;
	cout << fC(35, 165, 100) << " E-MAIL:         " << fC(240) << r[currentContact].email << endl << endl;	
	cout << fC(200) << " Eliminare il Contatto? [" << fC(30, 165, 100) << "Y" << fC(200) << "/" << fC(255, 90, 70) << "N" << fC(200) << "]";

	char key = _getch();
	
	// Attendo tasto valido
	while (key != 'Y' && key != 'y' && key != 'N' && key != 'n')
		key = _getch();
		
	system("cls");
	cout << "\x1b[?25l";
	
	// Elimina!!!
	if (key == 'y' || key == 'Y')
	{		
		// Shifto.
		for (int i = currentContact; i < contacts - 1; i++)
			r[i] = r[i + 1];
		
		// Cambio il contatto corrente.
		currentContact--;	
		// Diminuisco il Numero di Contatti.
		contacts--;
		
		// Provo a Salvare.
		if (!salva(r, contacts))
		{
			// Non Salva >:(.
			MessageBox(NULL, "NON E' STATO POSSIBILE SALVARE LA RUBRICA!!!", "Gaston", MB_OK | MB_ICONERROR);
		}
	}
}


bool is_mail (string mail) {
	
	//campo vuoto.
	if (mail.size() == 0 || mail == "#IS_$_NULL!")
		return true;
		
	if (mail.size() > 70)
		return false;
		
	int chiocciola, punto;
	string mail2;
	
	//cerca una @ nella stringa
	if (mail.find("@") != std::string::npos) {
		
	    chiocciola++;
	}
	//divide la stringa in due usando come divisore la @
	splitstr (mail, "@", mail2);
	
	//cesca un . nella seconda parte della stringa
	if (mail2.find(".") != std::string::npos) {
		
	    punto++;
	}
	
	//se ci sono una @ ed un . (nella seconda parte della stringa) allora e` una mail
	if (punto == 1 && chiocciola == 1) {
		
		return true;
	} else {

		return false;
	}
}

//divide la stringa dal delimitatore
void splitstr(string str, string deli, string &string2) {

    int start = 0;
    int end = str.find(deli);
    while (end != -1) {

        start = end + deli.size();
        end = str.find(deli, start);
    }
    string2 = str.substr(start, end - start);
}

bool is_num_mob (string num) {

	//campo vuoto.
	if (num.size() == 0 || num == "#IS_$_NULL!")
		return true;
		
    int si;

    //rimuove gli spazi dalla stringa
    remove(num.begin(), num.end(), ' ');

    if (only_num(num) == 1) {

        //controlla se c'e un +  per verificare se e stato inserito il prefisso
        if (num.find("+") != std::string::npos) {

           si++;
        }

        //no prefisso
        if (num.length() == 10 && si == 0 ) {

            return true;
        }
        //con prefisso
        if (si != 0 && num.length() <= 14 && num.length() >= 12) {

            return true;
        }
    } else {

        return false;
    }
}

//controlla se la stringa e` composta solo da numeri, + o spazi
bool only_num(string &str) {
    //1 = no lettere 0 = lettere
    return str.find_first_not_of("1234567890+ ") == string::npos;
}

bool is_num_fiss (string num) {

	//campo vuoto.
	if (num.size() == 0 || num == "#IS_$_NULL!")
		return true;
		
    int si;

    //rimuove gli spazi dalla stringa
    remove(num.begin(), num.end(), ' ');

    if (only_num(num) == 1) {

        //controlla se c'e un +  per verificare se e stato inserito il prefisso
        if (num.find("+") != std::string::npos) {

           si++;
        }

        //no prefisso
        if (num.length() == 9 && si == 0 ) {

            return true;
        }
        //con prefisso
        if (si != 0 && num.length() <= 13 && num.length() >= 11) {

            return true;
        }
    } else {

        return false;
    }
}

