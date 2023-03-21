/*
X1.	Toate clasele vor con?ine obligatoriu constructori de ini?ializare (0.25p), parametriza?i (0.25p) ?i de copiere (0.25p); destructor (0.25p);
operatorii „=” (0.25p), „>>” (0.25p), „<<” (0.25p) supraînc?rca?i corespunz?tor, mo?teniri & encapsulare (0.5p)
X2.	Clasele derivate trebuie sa contina constructori parametrizati (prin care sa se evidentieze transmiterea parametrilor catre constructorul din
clasa de baza) si destructori. (0.75p)
X3.	În fiecare proiect vor fi ilustrate conceptele de upcasting, downcasting, func?ii virtuale (pure – unde se consider? mai natural) – 1.5p
(0.5p / cerin??)
X4.	Utilizarea de variabile ?i de func?ii statice – 0.5p
X5.	Tratarea exceptiilor (try – catch) – 1p
X6.	Citirea informa?iilor complete a n obiecte (de diferite tipuri), memorarea ?i afi?area acestora – 0.5p
X7.	Meniu interactiv – 0.5p
8.	Rezolvarea corect? a cerin?elor suplimentare corespunzatoare fiecarei teme – 2p.
Se acord? punctaje par?iale corespunz?tor ?i 1p oficiu.
- Dac? sursa nu compileaz?, se acorda nota 1 (punctul din oficiu).
- Dup? expirarea termenului limit? se mai pot trimite teme pe mail pentru o perioad? de gra?ie de 2 zile (48 de ore). Pentru fiecare zi par?ial? de
întârziere se vor sc?dea 2 puncte. Dup? expirarea termenului de gra?ie, proiectele nu vor fi acceptate ?i vor fi notate cu 0. Punctul din oficiu este
primit doar dac? a fost trimis proiectul în perioada limit? + perioada de gra?ie.

Tema 14. Se dau clasele :
-Proces(int nrProces, string reclamant, string reclamat)
- Proces_civil(double dauneMorale, double dauneMateriale, int nrMartori, bool stadiu)
- Proces_penal(int dovezi, bool stadiu).
Sa se faca verificarile in constructori si la citire astfel : daca nrMartori > 5 automat stadiul este 1, altfel este 0. Daca la un proces penal
numarul dovezilor > 25 atunci stadiul este 1.
Sa se poata modifica stadiul unui proces si sa se creeze o metoda de calculare a taxei de timbru pentru fiecare proces civil.
Taxa de timbru = 10 / 100 * dauneMorale + 10 % *dauneMateriale.
Sa se afle procesul care are taxa de timbru cea mai mare.
*/

#include <iostream>

using namespace std;

class Proces {
protected:
	int nrProces;
	string reclamant, reclamat;

public:
//constructori:
	Proces() {
		nrProces = -1;
		reclamant = "\0";
		reclamat = "\0";
	}
	Proces(int nr, string numeReclamant, string numeReclamat) : nrProces(nr), reclamant(numeReclamant), reclamat(numeReclamat) {};
//destructor:
	~Proces() {};
//constructor de copiere:
	Proces(const Proces& proces) : nrProces(proces.nrProces), reclamant(proces.reclamant), reclamat(proces.reclamat) {};
//operatori:
	Proces& operator=(const Proces& proces) {
		if (this != &proces) {
			this->nrProces = proces.nrProces;
			this->reclamant = proces.reclamant;
			this->reclamat = proces.reclamat;
		}
		else return *this;
	}
	friend ostream& operator<<(ostream&, const Proces&);
	friend istream& operator>> (istream&, Proces&);
//functii virtuale:
	virtual void afisareInfo() = 0;
	virtual double calculTimbru() = 0;
	virtual void modifica() = 0;
	virtual bool getStadiu() = 0;
	virtual void setStadiu(bool b) = 0;

	int getnrProces() {
		return this->nrProces;
	}

	friend class GrupProcese;
};

istream& operator>> (istream& in, Proces& proces) {
	cout << "Introduceti datele procesului:\n\n";
	cout << "Nr. proces: ";
	in >> proces.nrProces;
	cout << "Nume reclamant: ";
	in >> proces.reclamant;
	cout << "Nume reclamat: ";
	in >> proces.reclamat;
	return in;
}

ostream& operator<<(ostream& out, const Proces& proces) {
	out << "Datele procesului sunt:\n\n";
	out << "Nr. proces: " << proces.nrProces<<"\n";
	out << "Nume reclamant: " << proces.reclamant << "\n";
	out << "Nume reclamat: " << proces.reclamant << "\n";
	return out;
}

class ProcesCivil : public Proces {
	static double procent;
	double dauneMorale, dauneMateriale;
	int nrMartori;
	bool stadiu;

public:
//constructor:
	ProcesCivil(int NrProces, string Reclamant, string Reclamat, double DauneMorale, double DauneMateriale, int NrMartori, bool Stadiu): Proces(NrProces, Reclamant, Reclamat) {
		this->dauneMorale = DauneMorale;
		this->dauneMateriale = DauneMateriale;
		this->nrMartori = NrMartori;
		this->stadiu = Stadiu;
	}
	ProcesCivil() : Proces() {
		this->dauneMorale = -1;
		this->dauneMateriale = -1;
		this->nrMartori = 0;
		this->stadiu = 0;
	};
//destructor:
	~ProcesCivil() {};
//operatori:
	ProcesCivil& operator=(const ProcesCivil& proces) {
		if (this != &proces) {
		this->nrProces = proces.nrProces;
		this->reclamant = proces.reclamant;
		this->reclamat = proces.reclamat;
		this->dauneMorale = proces.dauneMorale;
		this->dauneMateriale = proces.dauneMateriale;
		this->nrMartori = proces.nrMartori;
		this->stadiu = proces.stadiu;
		}
	}
	friend ostream& operator<<(ostream&, const ProcesCivil&);
	friend istream& operator>> (istream&, ProcesCivil&);
//functii virtuale:
	void afisareInfo() {
		cout << *this;
	}
	double calculTimbru() {
		return  dauneMorale * procent + dauneMateriale * procent;
	}
	void modifica();
	bool getStadiu() {
		return this->stadiu;
	}
	void setStadiu(bool b) {
		this->stadiu = b;
	}

	static void formulaTimbru();

	friend class GrupProcese;
};

istream& operator>> (istream& in, ProcesCivil& proces) {
	bool ok = false;
	cout << "Introduceti datele procesului:\n\n";
	cout << "Nr. proces: ";
	in >> proces.nrProces;
	cout << "Nume reclamant: ";
	in >> proces.reclamant;
	cout << "Nume reclamat: ";
	in >> proces.reclamat;
	cout << "Daune morale: ";
	in >> proces.dauneMorale;
	cout << "Daune materiale: ";
	in >> proces.dauneMateriale;
	cout << "Numar martori: ";
	in >> proces.nrMartori;
	while (!ok) {
		cout << "Stadiu proces: ";
		try {
			in >> proces.stadiu;
			if (proces.nrMartori > 5 && !proces.stadiu || proces.nrMartori <= 5 && proces.stadiu) {
				throw invalid_argument("STADIU INCORECT\n");
			}
			else ok = true;
		}
		catch (invalid_argument& e) {
			cout << e.what();
			continue;
		}
	}
	return in;
}

ostream& operator<<(ostream& out, const ProcesCivil& proces) {
	out << "Datele procesului sunt:\n\n";
	out << "Nr. proces: " << proces.nrProces << "\n";
	out << "Nume reclamant: " << proces.reclamant << "\n";
	out << "Nume reclamat: " << proces.reclamant << "\n";
	out << "Daune morale: " << proces.dauneMorale << "\n";
	out << "Daune materiale: " << proces.dauneMateriale << "\n";
	out << "Stadiu proces: " << proces.stadiu << "\n";
	out << "Numar martori: " << proces.nrMartori << "\n";
	return out;
}

void ProcesCivil::modifica() {
	cout << "Numar actual de martori: " << this->nrMartori << "\n";
	cout << "Numar nou de martori: ";
	cin >> this->nrMartori;
	if (this->nrMartori > 5) {
		this->stadiu = true;
		cout << "Stadiul procesului a devenit 1.\n";
	}
}

double ProcesCivil::procent = 0.1;

void ProcesCivil::formulaTimbru() {
	cout << "Pentru calculul taxei de timbru se foloseste formula:\n";
	cout << ProcesCivil::procent << " * daune_morale + " << ProcesCivil::procent << " *daune_materiale\n";
}

class ProcesPenal : public Proces {
	int dovezi;
	bool stadiu;

public:
//constructori:
	ProcesPenal(int NrProces, string Reclamant, string Reclamat, int Dovezi, bool Stadiu) : Proces(NrProces, Reclamant, Reclamat) {
		this->dovezi = Dovezi;
		this->stadiu = Stadiu;
	}
	ProcesPenal() : Proces() {
		this->dovezi = 0;
		this->stadiu = 0;
	};
//destructor:
	~ProcesPenal() {};
//operatori:
	ProcesPenal& operator=(const ProcesPenal& proces) {
		if (this != &proces) {
			this->nrProces = proces.nrProces;
			this->reclamant = proces.reclamant;
			this->reclamat = proces.reclamat;
			this->dovezi = proces.dovezi;
			this->stadiu = proces.stadiu;
		}
	}
	friend ostream& operator<<(ostream&, const ProcesPenal&);
	friend istream& operator>> (istream&, ProcesPenal&);
//functii virtuale:
	void afisareInfo() {
		cout << *this;
	}
	double calculTimbru() {
		throw invalid_argument("PROCESTUL NU ESTE CIVIL\n");
	}
	void modifica();
	bool getStadiu() {
		return this->stadiu;
	}
	void setStadiu(bool b) {
		this->stadiu = b;
	}

	friend class GrupProcese;
};

istream& operator>> (istream& in, ProcesPenal &proces) {
	bool ok = false;
	cout << "Introduceti datele procesului:\n\n";
	cout << "Nr. proces: ";
	in >> proces.nrProces;
	cout << "Nume reclamant: ";
	in >> proces.reclamant;
	cout << "Nume reclamat: ";
	in >> proces.reclamat;
	cout << "Dovezi: ";
	in >> proces.dovezi;
	while (!ok) {
		cout << "Stadiu proces: ";
		try {
			in >> proces.stadiu;
			if (proces.dovezi > 25 && !proces.stadiu || proces.dovezi <= 25 && proces.stadiu) {
				throw invalid_argument("STADIU INCORECT\n");
			}
			else ok = true;
		}
		catch (invalid_argument& e) {
			cout << e.what();
		}
	}
	return in;
}

ostream& operator<<(ostream& out, const ProcesPenal& proces) {
	out << "Datele procesului sunt:\n\n";
	out << "Nr. proces: " << proces.nrProces << "\n";
	out << "Nume reclamant: " << proces.reclamant << "\n";
	out << "Nume reclamat: " << proces.reclamant << "\n";
	out << "Dovezi: " << proces.dovezi << "\n";
	out << "Stadiu proces: " << proces.stadiu << "\n";
	return out;
}

void ProcesPenal::modifica() {
	cout << "Numar actual de dovezi: " << this->dovezi << "\n";
	cout << "Numar nou de dovezi: ";
	cin >> this->dovezi;
	if (this->dovezi > 25) {
		this->stadiu = true;
		cout << "Stadiul procesului a devenit 1.\n";
	}
}

class GrupProcese {
	Proces** p;
	int n;
public:
	GrupProcese() {
		p = nullptr;
		n = 0;
	}
	GrupProcese(int n) {
		this->n = n;
		p = new Proces * [n];
	}
	GrupProcese& operator=(const GrupProcese& grup) {
		if (this != &grup) {
			delete[] this->p;
			this->n = grup.n;
			this->p = new Proces * [n];
			for (int i = 0; i < n; i++) {
				this->p[i] = grup.p[i];
			}
		}
		return *this;
	}
	~GrupProcese() {
		delete[] p;
	}
	void meniu();
	void maxim(ProcesCivil*& max);
	void introducereDate();
	void afisareDate();
	void aflaStadiu();
	void modificaDate();
	void timbru();
	void nrValid(int nr, int i);
};

void GrupProcese::nrValid(int nr, int i) {
	for (int j = 0; j < i; i++) {
		if ((*(this->p[j])).getnrProces() == nr) {
			throw invalid_argument("\nPROCESUL CU ACEST NUMAR DEJA EXISTA!\n");
		}
	}
}

void GrupProcese::maxim(ProcesCivil*& max) {
	for (int i = 0; i < this->n; i++) {
		try {
			int curent;
			curent = (*(this->p[i])).calculTimbru();
			if (curent > (*max).calculTimbru()) max = (ProcesCivil*)(this->p[i]);
		}
		catch (invalid_argument& e) {
			continue;
		}
	}
}

void GrupProcese::introducereDate() {
	int n;
	cout << "Cate procese doriti sa centralizati? ";
	cin >> n;
	GrupProcese temp(n);
	*this = temp;
	cout << "    1 -> Proces civil\n" << "    2 -> Proces penal\n";
	for (int i = 0; i < n; i++) {
		int tip;
		bool ok = false;
		while (!ok) {
			cout << "\nCe fel de proces doriti sa introduceti? ";
			try {
				cin >> tip;
				if (tip == 1) {
					while (!ok) {
						try {
							ProcesCivil temp;
							cin >> temp;
							this->nrValid(temp.nrProces, i);
							p[i] = new ProcesCivil(temp);
							ok = true;
						}
						catch (invalid_argument& e) {
							cout << e.what();
							cout << "Reincercati:\n";
						}
					}
				}
				else if (tip == 2) {
					while (!ok) {
						try {
							ProcesPenal temp;
							cin >> temp;
							this->nrValid(temp.nrProces, i);
							p[i] = new ProcesPenal(temp);
							ok = true;
						}
						catch (invalid_argument& e) {
							cout << e.what();
							cout << "Reincercati:\n";
						}
					}
				}
				else throw invalid_argument("OPTIUNEA NU EXISTA(optiunile sunt 1/2)\n");
			}
			catch (invalid_argument& e) {
				cout << e.what();
				continue;
			}
		}
	}
}

void GrupProcese::afisareDate() {
	for (int i = 0; i < this->n; i++) {
		(*p[i]).afisareInfo();
		cout << "\n";
	}
}

void GrupProcese::aflaStadiu() {
	int nr;
	bool ok = false;
	try {
		cout << "Numarul procestului pentru care vreti sa stiti stadiul: ";
		cin >> nr;
		for (int i = 0; i < this->n; i++) {
			if ((*(this->p[i])).nrProces == nr) {
				cout << "Stadiu: " << (*(this->p[i])).getStadiu() << "\n";
				ok = true;
				int mod;
				cout << "Doriti sa modificati stadiul procesului?\n";
				cout << "    0 -> NU\n" << "    1 -> DA\n";
				cin >> mod;
				if (mod == 1) {
					bool nou;
					cout << "Pentru a seta stadiul ca 0 introduceti 0, pentru a seta stadiul ca 1 introduceti orice valoare: ";
					cin >> nou;
					(*(this->p[i])).setStadiu(nou);
				}
				
			}
		}
		if (!ok) throw invalid_argument("ACEST PROCES NU EXISTA\n");
	}
	catch (invalid_argument& e) {
		cout << e.what();
	}
}

void GrupProcese::modificaDate() {
	int nr;
	bool ok = false;
	try {
		cout << "Numarul procesului pentru care doriti sa modificati numarul de dovezi/martori: ";
		cin >> nr;
		for (int i = 0; i < n; i++) {
			if ((*(this->p[i])).nrProces == nr) {
				(*(this->p[i])).modifica();
				ok = true;
			}
		}
		if (!ok) throw invalid_argument("ACEST PROCES NU EXISTA\n");
	}
	catch (invalid_argument& e) {
		cout << e.what();
	}
}

void GrupProcese::timbru() {
	int nr;
	bool ok = false;
	try {
		cout << "Numarul procesului pentru care doriti sa se calculeze taxa de timbru: ";
		cin >> nr;
		for (int i = 0; i < n; i++) {
			if ((*(this->p[i])).nrProces == nr) {
				try {
					cout << "Valoarea taxei de timbru: " << (*(this->p[i])).calculTimbru() << "\n";
					ok = true;
				}
				catch (invalid_argument& e) {
					cout << e.what();
					return;
				}
			}
		}
		if (!ok) throw invalid_argument("ACEST PROCES NU EXISTA\n");
	}
	catch (invalid_argument& e) {
		cout << e.what();
	}
}


void GrupProcese::meniu() {
	int optiune;
	cout << "\n";
	cout << "--------CENTRALIZAREA PROCESELOR PENALE SI CIVILE-------------------------------------------------\n\n";
	while (1)
	{
		cout << "Optiunile sunt:\n" << "    0 -> Introducere date\n" << "    1 -> Afisare date\n" << "    2 -> Afla stadiul unui proces\n" << "    3 -> Modifica numar dovezi/martori\n" << "    4 -> Calculeaza taxa de timbru\n" << "    5 -> Am terminat centralizarea\n";
		cout << "--------------------------------------------------------------------------------------------------\nIntroduceti optiunea: ";
		cin >> optiune;
		switch (optiune)
		{
		case 0: introducereDate();
			break;
		case 1: afisareDate();
			break;
		case 2: aflaStadiu();
			break;
		case 3: modificaDate();
			break;
		case 4: timbru();
			break;
		case 5: return;
			break;
		default: cout << "Optiunea " << optiune << " nu exista!\n";
		}
		cout << "--------------------------------------------------------------------------------------------------\n";
	}
}

int main() {
	GrupProcese procese;
	procese.meniu();
	cout << "\n";
	ProcesCivil::formulaTimbru();
	ProcesCivil *max= new ProcesCivil();
	procese.maxim(max);
	cout << "\nCea mai mare taxa de timbru: ";
	if (max->calculTimbru() < 0) cout << "NU EXISTA PROCESE CIVILE\n";
	else {
		cout << max->calculTimbru();
		cout << "\n";
		max->afisareInfo();
	} 
	return 0;
}