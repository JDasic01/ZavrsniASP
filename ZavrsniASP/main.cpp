#include<iostream>
#include<iomanip>
#include <list>
#include <vector>
#include <fstream>
#include <string.h>
#include <sstream>
using namespace std;

vector<string> proba;
int n;

struct CvorBinarno
{
    string podatak; // rw - kljuc
    string ID;
    string age;
    string nationality;
    string overall;
    string potential;
    string club;
    string clubLogo;
    string special;
    string prefferedFoot;
    string internationalReputation;
    string weakFoot;
    string skillMove;
    string realFace;
    string position;
    string jerseyNumber;
    string loanedFrom;
    string height;
    string weight;
    string ls;
    string st;
    string rs;
    CvorBinarno* lijevi;
    CvorBinarno* desni;
    CvorBinarno(vector <string> lista, int pos)
    {
        podatak = lista[pos];
        ID = lista[pos - 21];
        age = lista[pos - 20];
        nationality = lista[pos - 19];
        overall = lista[pos - 18];
        potential = lista[pos - 17];
        club = lista[pos - 16];
        clubLogo = lista[pos - 15];
        special = lista[pos - 14];
        prefferedFoot = lista[pos - 13];
        internationalReputation = lista[pos - 12];
        weakFoot = lista[pos - 11];
        skillMove = lista[pos - 10];
        realFace = lista[pos - 9];
        position = lista[pos - 8];
        jerseyNumber = lista[pos - 7];
        loanedFrom = lista[pos - 6];
        height = lista[pos - 5];
        weight = lista[pos - 4];
        ls = lista[pos - 3];
        st = lista[pos - 2];
        rs = lista[pos - 1];
        lijevi = NULL;
        desni = NULL;
    }
};

struct Cvor
{
    string podaci;
    string ID;
    string age;
    string nationality;
    string overall;
    string potential;
    string club;
    string clubLogo;
    string special;
    string prefferedFoot;
    string internationalReputation;
    string weakFoot;
    string skillMove;
    string realFace;
    string position;
    string jerseyNumber;
    string loanedFrom;
    string height;
    string weight;
    string ls;
    string st;
    string rs;
    Cvor* lijevi;
    Cvor* desni;
    Cvor(vector <string> lista, int pos)
    {
        podaci = lista[pos];
        ID = lista[pos - 21];
        age = lista[pos - 20];
        nationality = lista[pos - 19];
        overall = lista[pos - 18];
        potential = lista[pos - 17];
        club = lista[pos - 16];
        clubLogo = lista[pos - 15];
        special = lista[pos - 14];
        prefferedFoot = lista[pos - 13];
        internationalReputation = lista[pos - 12];
        weakFoot = lista[pos - 11];
        skillMove = lista[pos - 10];
        realFace = lista[pos - 9];
        position = lista[pos - 8];
        jerseyNumber = lista[pos - 7];
        loanedFrom = lista[pos - 6];
        height = lista[pos - 5];
        weight = lista[pos - 4];
        ls = lista[pos - 3];
        st = lista[pos - 2];
        rs = lista[pos - 1];
        lijevi = NULL;
        desni = NULL;
    }
};

int UnosDatoteke()
{ 
    fstream fin;

    fin.open("fifa.txt", ios::in);

    string line;

    while (getline(fin, line))
    {
        proba.push_back(line);
    }
    n = proba.size();
    return n;
}

CvorBinarno* unos(CvorBinarno* cvor, vector<string> lista, int position) {
    if (cvor == NULL)
        cvor = new CvorBinarno(lista, position);
    else if (lista[position] < cvor->podatak)
        cvor->lijevi = unos(cvor->lijevi, lista, position);
    else if (lista[position] > cvor->podatak)
        cvor->desni = unos(cvor->desni, lista, position);
    return cvor;
}

CvorBinarno* stvoriStablo(vector<string> lista, int position) {
    CvorBinarno* korijen = new CvorBinarno(lista, position);

    for (int i = 21; i < lista.size(); i += 22) {
        unos(korijen, lista, i);
    }

    return korijen;
}

void printInorderBinarno(CvorBinarno* cvor) {
    if (cvor == NULL)
        return;

    printInorderBinarno(cvor->lijevi);
    cout << cvor->podatak << " ";
    printInorderBinarno(cvor->desni);
}

void LijevaRotacija(Cvor*& cvor)
{
    Cvor* temp = cvor->lijevi;
    cvor->lijevi = temp->desni;
    temp->desni = cvor;
    cvor = temp;
}

void DesnaRotacija(Cvor*& cvor)
{
    Cvor* temp = cvor->desni;
    cvor->desni = temp->lijevi;
    temp->lijevi = cvor;
    cvor = temp;
}

void LijevaRotacija2x(Cvor*& cvor)
{
    DesnaRotacija(cvor->lijevi);
    LijevaRotacija(cvor);
}

void DesnaRotacija2x(Cvor*& cvor)
{
    LijevaRotacija(cvor->desni);
    DesnaRotacija(cvor);
}

void printInorder(Cvor* cvor)
{
    if (cvor == NULL) return;
    printInorder(cvor->lijevi);
    cout << cvor->podaci << " ";
    printInorder(cvor->desni);
}

int Visina(Cvor* cvor)
{
    if (cvor == NULL) return -1;
    else
    {
        int LVisina = Visina(cvor->lijevi);
        int DVisina = Visina(cvor->desni);
        if (LVisina > DVisina) return LVisina + 1;
        else return DVisina + 1;
    }
}

Cvor* DodajAVL(Cvor*& cvor, vector <string> lista, int position)
{
    if (cvor == NULL)
        cvor = new Cvor(lista, position);
    else if (lista[position] < cvor->podaci)
    {
        DodajAVL(cvor->lijevi, lista, position);
        if (Visina(cvor->lijevi) - Visina(cvor->desni) == 2)
        {
            if (lista[position] < cvor->lijevi->podaci)
                LijevaRotacija(cvor);
            else
                LijevaRotacija2x(cvor);
        }
    }
    else if (lista[position] > cvor->podaci)
    {
        DodajAVL(cvor->desni, lista, position);
        if (Visina(cvor->desni) - Visina(cvor->lijevi) == 2)
        {
            if (lista[position] > cvor->desni->podaci)
                DesnaRotacija(cvor);
            else
                DesnaRotacija2x(cvor);
        }
    }
    return cvor;
}

void IspisStabla(Cvor* korijen, int sirina)
{
    if (korijen == 0)
    {

        cout << setw(sirina) << "*" << endl;
        return;
    }
    IspisStabla(korijen->desni, sirina + 6);
    cout << setw(sirina) << korijen->podaci << "<" << endl;
    IspisStabla(korijen->lijevi, sirina + 6);
}

void ispisElementa(Cvor* korijen, int sirina, string searchFor)
{
    if (korijen->podaci == searchFor)
    {
        cout <<  korijen->podaci << endl;
        cout << korijen->ID << endl;
        cout << korijen->age << endl;
        cout << korijen->nationality << endl;
        cout << korijen->overall << endl;
        cout << korijen->potential << endl;
        cout << korijen->club << endl;
        cout << korijen->clubLogo << endl;
        cout << korijen->special << endl;
        cout << korijen->prefferedFoot << endl;
        cout << korijen->internationalReputation << endl;
        cout << korijen->weakFoot << endl;
        cout << korijen->skillMove << endl;
        cout << korijen->realFace << endl;
        cout << korijen->position << endl;
        cout << korijen->jerseyNumber << endl;
        cout << korijen->loanedFrom << endl;
        cout << korijen->height << endl;
        cout << korijen->weight << endl;
        cout << korijen->ls << endl;
        cout << korijen->st << endl;
        cout << korijen->rs << endl;
    }
    else if(searchFor < korijen->podaci)
    {
        ispisElementa(korijen->lijevi, sirina, searchFor);
    }
    else
    {
        ispisElementa(korijen->desni, sirina, searchFor);
    }

}

int main()
{
    int velicina = UnosDatoteke();

    CvorBinarno* korijen = stvoriStablo(proba, 21);
    cout << "Inorder obilazak binarnog stabla je:\n";
    printInorderBinarno(korijen);
    cout << endl;

    int root_index = 21;
    Cvor* root = new Cvor(proba, 21);
    for (int i = 21; i < velicina; i+=22) {
        DodajAVL(root, proba, i);
    }

    cout << "Inorder obilazak AVL stabla je:\n";
    printInorder(root);

    cout << endl;
    IspisStabla(root, 0);

    string izbor;
    do {
        cout << "Za izlaz iz programa napisite 'x': ";
        cout << "Unesite kljuc elementa stabla kojeg zelite ispisati: ";
        cin >> izbor;
        if(izbor!="x")
            ispisElementa(root, 0, izbor);
    } while (izbor!="x");

    return 0;
}