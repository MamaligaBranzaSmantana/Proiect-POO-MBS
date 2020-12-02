#include <iostream>

using namespace std;

class Tabel {
	public:
		string nume;
		class coloana {
			public:
				string nume;
				string tip;
				short dimensiune;
				int defaultValue;
		};
		coloana* c; //vector de coloane in tabela
};

class comanda {  //clasa comanda mama -- identifica tipul comenzii, aici ma gandesc ca ar trebui sa contine niste atribute comune pe care toate comenzile sa le mosteneasca? daca nu, folosim doar fct idComanda
	public: 
		string denumire;
		void idComanda(); //functie care identifica tipul comenzii --> Daca este select, insert, create etc. (cu un switch)

};

class createTable {
	public:
		Tabel t; //declarare tabela
		int nrColoane; //nr de coloane ale tabelei
		void citireColoane(); //citim numele, tipul, etc. al fiecarei coloane
		createTable(string nume, Tabel::coloana* c, int nrColoane) //connstructor cu parametrii
		{
			t.nume = nume;
			t.c = new Tabel::coloana[nrColoane];
			for (int i = 0; i < nrColoane; i++)
			{
				t.c[i].nume = c[i].nume;
				//...etc.
			}
		}
};

class dropTable { //ar trebui sa stearga de tot Tabelul t
	public:
		Tabel t;
		void stergereTabel(); // un delete[] t.coloana si ?? cum stergi de tot de pe disk obiectul t :))))
};

int main()
{
	return 0;
}