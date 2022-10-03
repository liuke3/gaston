#include "console+vts.hpp"
#include "rubrica.hpp"

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
			
			switch (i)
			{
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

