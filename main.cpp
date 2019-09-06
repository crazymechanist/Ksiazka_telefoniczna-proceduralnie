#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct Kontakt {
    int id=0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
};

int stringToInt(string liczbaWFormacieString);

int zapisanieKontaktu(int idOstatnioDodanegoKontaktu, vector<Kontakt> &ksiazkaKontaktow);

void pokazKsiazkeKontaktow (const vector<Kontakt> &ksiazkaKontaktow);

void wyszukajImiennie(const vector<Kontakt> &ksiazkaKontaktow);

void wyszukajPoNazwisku(const vector<Kontakt> &ksiazkaKontaktow);

int wczytanieTestowychKontaktow (vector<Kontakt> &ksiazkaKontaktow, int idOstatnioDodanegoKontaktu);

void wczytanieKontaktuZPliku(vector<Kontakt> &ksiazkaKontaktow);

void zapiszKontaktyDoPliku(int idOstatnioDodanegoKontaktu, vector<Kontakt> &ksiazkaKontaktow);

void wyswietlKontakt (const vector<Kontakt> &ksiazkaKontaktow, int idKontaktu);

int sprawdzIdOstatniegoKontaktu (const vector <Kontakt> &ksiazkaKontaktow);

void usunKontakt (vector <Kontakt> &ksiazkaKontaktow);

void edytujKontakt (vector <Kontakt> &ksiazkaKontaktow);

//MAIN///POCZATEK//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    vector <Kontakt> ksiazkaKontaktow;
    char opcja=0;
    int idOstatnioDodanegoKontaktu=0;
    wczytanieKontaktuZPliku( ksiazkaKontaktow);

    while(true) {
        cout << "MENU GLOWNE" << endl
             << "______________" << endl
             << "1. Dodaj adresata" << endl
             << "2. Wyszukaj po imieniu" << endl
             << "3. Wyszukaj po nazwisku" << endl
             << "4. Wyswietl wszystkich adresatow" << endl
             << "5. Usun adresata" << endl
             << "6. Edytuj adresata" << endl
             << "9. Koniec" << endl
             << "______________" << endl
             << "Czego potrzebujesz?" << endl;

        opcja = getch();

        switch(opcja) {
        case '1':
            idOstatnioDodanegoKontaktu = sprawdzIdOstatniegoKontaktu (ksiazkaKontaktow);
            zapisanieKontaktu(idOstatnioDodanegoKontaktu, ksiazkaKontaktow);
            zapiszKontaktyDoPliku(idOstatnioDodanegoKontaktu, ksiazkaKontaktow);
            Sleep (1000);
            system ("cls");
            break;
        case '2':
            wyszukajImiennie(ksiazkaKontaktow);
            Sleep (1000);
            system ("cls");
            break;
        case '3':
            wyszukajPoNazwisku(ksiazkaKontaktow);
            Sleep (1000);
            system ("cls");
            break;
        case '4':
            pokazKsiazkeKontaktow (ksiazkaKontaktow);
            Sleep (1000);
            system ("cls");
            break;
        case '5':
            usunKontakt (ksiazkaKontaktow);
            zapiszKontaktyDoPliku(idOstatnioDodanegoKontaktu, ksiazkaKontaktow);
            Sleep (1000);
            system ("cls");
            break;
        case '6':
            edytujKontakt (ksiazkaKontaktow);
            zapiszKontaktyDoPliku(idOstatnioDodanegoKontaktu, ksiazkaKontaktow);
            Sleep (1000);
            system ("cls");
            break;
        case '9':
            cout << "KONIEC... " << endl;
            exit(0);
            break;
        default:
            cout << "Jeszcze raz" << endl;
            Sleep (1000);
            system ("cls");
        }
    }
    return 0;
}
//MAIN///KONIEC//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int stringToInt(string liczbaWFormacieString) {
    int liczbaWFormacieInt = atoi(liczbaWFormacieString.c_str());
    return liczbaWFormacieInt ;
}

void zapiszKontaktyDoPliku(int idOstatnioDodanegoKontaktu, vector<Kontakt> &ksiazkaKontaktow) {
    fstream plik;
    string przerywnik="|";
    plik.open("KsiazkaAdresowa.txt", ios::out);
    for (unsigned int i=0; i<ksiazkaKontaktow.size(); i++) {
        plik<<ksiazkaKontaktow[i].id<<przerywnik<<ksiazkaKontaktow[i].imie<<przerywnik<<ksiazkaKontaktow[i].nazwisko<<przerywnik<<ksiazkaKontaktow[i].numerTelefonu<<przerywnik<<ksiazkaKontaktow[i].email<<przerywnik<<ksiazkaKontaktow[i].adres<<endl;
    }
    plik.close();
}

int zapisanieKontaktu(int idOstatnioDodanegoKontaktu, vector<Kontakt> &ksiazkaKontaktow) {
    idOstatnioDodanegoKontaktu++;
    Kontakt tempKontakt;
    tempKontakt.id = idOstatnioDodanegoKontaktu;
    cout << "ZAPISYWANIE NOWEGO KONTAKTU:" << endl;
    cout << "Imie:";
    getline(cin,tempKontakt.imie);
    cout << "Nazwisko:";
    getline(cin,tempKontakt.nazwisko);
    cout << "Numer telefonu:";
    getline(cin,tempKontakt.numerTelefonu);
    cout << "Adres email:";
    getline(cin,tempKontakt.email);
    cout << "Adres zamieszkania:";
    getline(cin,tempKontakt.adres);
    ksiazkaKontaktow.push_back(tempKontakt);
    cout << "Kontakt zapisany!";
    return idOstatnioDodanegoKontaktu;
}

void wczytanieKontaktuZPliku(vector<Kontakt> &ksiazkaKontaktow) {
    string linia;
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);
    if(!plik.good()) {
        plik.open("KsiazkaAdresowa.txt", ios::out);
        plik.close();
    } else {
        string komorkaZPliku[5];
        Kontakt tempKontakt;
        while (getline(plik, linia)) {
            int ilePozycji=6;
            for (int i = 0 ; i<ilePozycji-1 ; i++) {
                string przerywnik ="|";
                size_t pozycjaPrzerywnika = linia.find(przerywnik);
                komorkaZPliku[i] = linia.substr(0, pozycjaPrzerywnika);
                linia.erase(0,pozycjaPrzerywnika+1);
            }
            tempKontakt.id=stringToInt(komorkaZPliku[0]);
            tempKontakt.imie=komorkaZPliku[1];
            tempKontakt.nazwisko=komorkaZPliku[2];
            tempKontakt.numerTelefonu=komorkaZPliku[3];
            tempKontakt.email=komorkaZPliku[4];
            tempKontakt.adres=linia;
            ksiazkaKontaktow.push_back(tempKontakt);
        }
    }
    plik.close();
}

void pokazKsiazkeKontaktow (const vector<Kontakt> &ksiazkaKontaktow) {
    cout << "TWOJE KONTAKTY:" << endl;
    for (unsigned int i=0; i<ksiazkaKontaktow.size(); i++) {
        wyswietlKontakt (ksiazkaKontaktow, i );
        cout<<endl;
    }
    cout << "Nacisnij dowolny klawisz";
    getch();
    system("cls");
}

void wyszukajImiennie(const vector<Kontakt> &ksiazkaKontaktow) {
    string fraza;
    bool czyZnaleziono=0;
    cout<<"Wpisz fraze do wyszukania: ";
    getline( cin, fraza);
    for (unsigned int i=0; i<ksiazkaKontaktow.size(); i++) {
        size_t pozycja = ksiazkaKontaktow[i].imie.find(fraza);
        if (pozycja!=string::npos) {
            czyZnaleziono=1;
            wyswietlKontakt (ksiazkaKontaktow, i );
        }
        if (i==ksiazkaKontaktow.size()-1) {
            if(czyZnaleziono!=0)
                cout << "To wszystko"<<endl;
            else
                cout << "Nie znaleziono!" <<endl;
        }
    }
    cout << "Nacisnij dowolny klawisz";
    getch();
}

void wyszukajPoNazwisku(const vector<Kontakt> &ksiazkaKontaktow) {
    string fraza;
    bool czyZnaleziono=0;
    cout<<"Wpisz fraze do wyszukania: ";
    getline( cin, fraza);
    for (unsigned int i=0; i<ksiazkaKontaktow.size(); i++) {
        size_t pozycja = ksiazkaKontaktow[i].nazwisko.find(fraza);
        if (pozycja!=string::npos) {
            czyZnaleziono=1;
            wyswietlKontakt (ksiazkaKontaktow, i );
        }
        if (i==ksiazkaKontaktow.size()-1) {
            if(czyZnaleziono!=0)
                cout << "To wszystko"<<endl;
            else
                cout << "Nie znaleziono!" <<endl;
        }

    }
    cout << "Nacisnij dowolny klawisz";
    getch();
}

void wyswietlKontakt (const vector<Kontakt> &ksiazkaKontaktow, int idKontaktu) {
    cout <<ksiazkaKontaktow[idKontaktu].id << endl;
    cout << "Imie: " <<ksiazkaKontaktow[idKontaktu].imie << endl;
    cout << "Nazwisko: "<<ksiazkaKontaktow[idKontaktu].nazwisko<< endl;
    cout << "Numer telefonu: " <<ksiazkaKontaktow[idKontaktu].numerTelefonu << endl;
    cout << "Adres email: "<<ksiazkaKontaktow[idKontaktu].email<<endl;
    cout << "Adres zamieszkania: "<<ksiazkaKontaktow[idKontaktu].adres<<endl;
}

int sprawdzIdOstatniegoKontaktu (const vector <Kontakt> &ksiazkaKontaktow) {
    if(ksiazkaKontaktow.size() == 0) {
        return 0;
    } else {
        vector<Kontakt>::const_iterator itr = ksiazkaKontaktow.end()-1;
        Kontakt ostatniKontakt = *itr;
        return ostatniKontakt.id ;
    }
}

void usunKontakt (vector <Kontakt> &ksiazkaKontaktow) {
    int idDoUsuniecia = -1, i=0;
    cout << "Podaj numer id adresata, ktorego chcesz usunac" <<endl;
    cin >> idDoUsuniecia;
    cin.ignore();
    while ( (i<ksiazkaKontaktow.size()) && (idDoUsuniecia != ksiazkaKontaktow[i].id) ) {
        i++;
    }
    if (i == ksiazkaKontaktow.size()) {
        cout << "Nie znaleziono id"<<endl;
    } else {
        cout << "Czy chcesz usunac kontakt:";
        wyswietlKontakt(ksiazkaKontaktow, i);
        cout << "t - TAK" << endl << "n - NIE"<< endl;
        char decyzja = getch();
        if(decyzja == 't') {
            ksiazkaKontaktow.erase(ksiazkaKontaktow.begin()+i);
            cout << "Usunieto kontakt"<<endl;
        } else {
            cout << "Nie usunieto"<<endl;
        }
    }
}

void edytujKontakt (vector <Kontakt> &ksiazkaKontaktow) {
    int idDoEdycji = -1, i=0;
    cout << "Podaj numer id adresata, ktorego chcesz edytowac" <<endl;
    cin >> idDoEdycji;
    cin.ignore();
    while ( (i<ksiazkaKontaktow.size()) && (idDoEdycji != ksiazkaKontaktow[i].id) ) {
        i++;
    }
    if (i == ksiazkaKontaktow.size()) {
        cout << "Nie znaleziono id"<<endl;
    } else {
        cout << "Czy chcesz edytowac kontakt:";
        wyswietlKontakt(ksiazkaKontaktow, i);
        cout << "Ktore pole edytowac: " << endl
             << "1. imie" << endl
             << "2. nazwisko" << endl
             << "3. numer telefonu" << endl
             << "4. email" << endl
             << "5. adres" << endl
             << "6. powrot do menu" << endl;
        char wybor = getch();
        //cin.ignore();
        switch(wybor) {
        case '1':
            cout << "Imie: ";
            cin >> ksiazkaKontaktow[i].imie;
            cin.ignore();
            break;
        case '2':
            cout << "Nazwisko: ";
            cin >> ksiazkaKontaktow[i].nazwisko;
            cin.ignore();
            break;
        case '3':
            cout << "Numer telefonu: ";
            getline(cin, ksiazkaKontaktow[i].numerTelefonu);
            cin.ignore();
            break;
        case '4':
            cout << "Email: ";
            cin >> ksiazkaKontaktow[i].email;
            cin.ignore();
            break;
        case '5':
            cout << "Adres: ";
            getline(cin,ksiazkaKontaktow[i].adres);
            break;
        default:
            ;
        }
        if ( (wybor == '1') || (wybor == '2') || (wybor == '3') || (wybor == '4') || (wybor == '5') ) {
            cout<<"Zmieniono";
        } else {
            cout << "Powrot do menu";
        }
    }

}
