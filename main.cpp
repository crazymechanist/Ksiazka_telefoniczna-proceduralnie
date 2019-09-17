#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};

struct Kontakt {
    int id=0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
};

int zapisanieKontaktu(int idOstatnioDodanegoKontaktu, vector<Kontakt> &ksiazkaKontaktow);

void pokazKsiazkeKontaktow (const vector<Kontakt> &ksiazkaKontaktow);

void wyszukajImiennie(const vector<Kontakt> &ksiazkaKontaktow);

void wyszukajPoNazwisku(const vector<Kontakt> &ksiazkaKontaktow);

int wczytanieTestowychKontaktow (vector<Kontakt> &ksiazkaKontaktow, int idOstatnioDodanegoKontaktu);

void wczytanieKontaktowZPliku(vector<Kontakt> &ksiazkaKontaktow, int idZalogowanegoUzytkownika) ;

void zapiszKontaktyDoPliku(int idOstatnioDodanegoKontaktu, vector<Kontakt> &ksiazkaKontaktow, int idZalogowanegoUzytkownika);

void wyswietlKontakt (const vector<Kontakt> &ksiazkaKontaktow, int idKontaktu);

int sprawdzIdOstatniegoKontaktu ();

int usunKontakt (vector <Kontakt> &ksiazkaKontaktow);

int edytujKontakt (vector <Kontakt> &ksiazkaKontaktow);

int stringToInt(string liczbaWFormacieString);

int rejestracja( vector<Uzytkownik> &users, int usersCout);

int logowanie(const vector<Uzytkownik> uzytkownicy, int idOstatniegoUzytkownika);

void zmianaHasla(vector<Uzytkownik> &uzytkownicy, int idOstatniegoUzytkownika, int idZalogowanegoUzytkownika);

void zapiszUzytkownikowDoPliku(int idOstatniegoUzytkownika, const vector<Uzytkownik> &uzytkownicy);

int wczytanieUzytkownikowZPliku(vector<Uzytkownik> &uzytkownicy);

string intToStringConvert (int Number );

bool moveToStartOfLine(std::ifstream& fs);

string getLastLineInFile(std::ifstream& fs) ;

void zapiszOstatniKontaktDoPliku(int idOstatnioDodanegoKontaktu, const vector<Kontakt> &ksiazkaKontaktow, int idZalogowanegoUzytkownika ) ;

void saveContactsToFile(int currentUserId, int contactId, const vector<Kontakt> &contactsBook );

int main() {
    vector <Uzytkownik> uzytkownicy;
    vector <Kontakt> ksiazkaKontaktow;
    int idZalogowanegoUzytkownika = 0;
    int idOstatniegoUzytkownika = 0;
    idOstatniegoUzytkownika = wczytanieUzytkownikowZPliku(uzytkownicy);
    int iloscUzytkownikow=uzytkownicy.size();
    char wybor;

    while (1) {
        if (idZalogowanegoUzytkownika == 0) {
            system("cls");
            cout << "MENU GLOWNE" << endl
                 << "______________" << endl
                 << "1. Rejestracja" <<endl
                 << "2. Logowanie" << endl
                 << "9. Zakoncz program" << endl
                 << "______________" << endl
                 << "Czego potrzebujesz?" << endl;
            cin >> wybor;
            cin.ignore();
            //wybor = getch();
            switch(wybor) {
            case '1':
                idOstatniegoUzytkownika = rejestracja(uzytkownicy,idOstatniegoUzytkownika);
                zapiszUzytkownikowDoPliku(idOstatniegoUzytkownika, uzytkownicy);
                break;
            case '2':
                idZalogowanegoUzytkownika = logowanie(uzytkownicy,idOstatniegoUzytkownika);
                break;
            case '9':
                zapiszUzytkownikowDoPliku(idOstatniegoUzytkownika, uzytkownicy);
                exit(0);
                break;
            default:
                cout << "Wprowadz inna liczbe!";
                Sleep (1000);
                system ("cls");
            }
        } else {
            int idOstatniegoKontaktu=0;
            wczytanieKontaktowZPliku( ksiazkaKontaktow, idZalogowanegoUzytkownika);
            while (idZalogowanegoUzytkownika != 0) {
                system("cls");
                cout << "MENU GLOWNE" << endl
                     << "______________" << endl
                     << "1. Dodaj adresata" << endl
                     << "2. Wyszukaj po imieniu" << endl
                     << "3. Wyszukaj po nazwisku" << endl
                     << "4. Wyswietl wszystkich adresatow" << endl
                     << "5. Usun adresata" << endl
                     << "6. Edytuj adresata" << endl
                     << "7. Zmien haslo " << endl
                     << "8. Wyloguj sie" << endl
                     << "9. Koniec" << endl
                     << "______________" << endl
                     << "Czego potrzebujesz?" << endl;
                cin >> wybor;
                cin.ignore();
                switch(wybor) {
                case '1': {
                    idOstatniegoKontaktu = sprawdzIdOstatniegoKontaktu ();
                    zapisanieKontaktu(idOstatniegoKontaktu, ksiazkaKontaktow);
                    zapiszOstatniKontaktDoPliku(idOstatniegoKontaktu, ksiazkaKontaktow, idZalogowanegoUzytkownika);
                    Sleep (1000);
                    system ("cls");
                    break;
                }

                case '2': {
                    wyszukajImiennie(ksiazkaKontaktow);
                    Sleep (1000);
                    system ("cls");
                    break;
                }

                case '3': {
                    wyszukajPoNazwisku(ksiazkaKontaktow);
                    Sleep (1000);
                    system ("cls");
                    break;
                }

                case '4': {
                    pokazKsiazkeKontaktow (ksiazkaKontaktow);
                    Sleep (1000);
                    system ("cls");
                    break;
                }

                case '5': {
                    int idDoUsuniecia = usunKontakt (ksiazkaKontaktow);
                    saveContactsToFile(idZalogowanegoUzytkownika, idDoUsuniecia, ksiazkaKontaktow );
                    Sleep (1000);
                    system ("cls");
                    break;
                }
                case '6': {
                    int idDoEdycji = edytujKontakt (ksiazkaKontaktow);
                    saveContactsToFile(idZalogowanegoUzytkownika, idDoEdycji, ksiazkaKontaktow );
                    Sleep (1000);
                    system ("cls");
                    break;
                }
                case '7': {
                    zmianaHasla(uzytkownicy, idOstatniegoUzytkownika, idZalogowanegoUzytkownika);
                    break;
                }
                case '8': {
                    idZalogowanegoUzytkownika=0;
                    ksiazkaKontaktow.erase(ksiazkaKontaktow.begin(), ksiazkaKontaktow.end());
                    break;
                }
                case '9': {
                    exit(0);
                    break;
                }
                default: {
                    cout << "Wprowadz inna liczbe!";
                    Sleep (1000);
                    system ("cls");
                }

                }
            }
        }
    }
    return 0;
}

int rejestracja( vector<Uzytkownik> &users, int usersCout) {

    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >>nazwa;
    cin.ignore();
    int i = 0;
    while (i < usersCout) {
        if(users[i].nazwa == nazwa) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            cin.ignore();
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    cin.ignore();
    Uzytkownik tempUser;
    tempUser.nazwa = nazwa;
    tempUser.haslo = haslo;
    tempUser.id = usersCout + 1;
    users.push_back(tempUser);
    cout << "Konto zalozone" << endl;
    Sleep(1000);
    return usersCout+1;
}

int logowanie(const vector<Uzytkownik> uzytkownicy, int idOstatniegoUzytkownika) {
    string nazwa, haslo;
    cout << "Podaj login: ";
    cin >> nazwa;
    cin.ignore();
    int i = 0;
    while (i < idOstatniegoUzytkownika) {
        if(uzytkownicy[i].nazwa == nazwa) {
            for (int proby = 0; proby < 3; proby++) {
                if (proby==0) {
                    cout << "Podaj haslo:";
                } else {
                    cout << "Podaj haslo. Pozostalo prob " << 3-proby<< ": ";
                }

                cin >> haslo;
                cin.ignore();
                if (uzytkownicy[i].haslo == haslo) {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}

void zmianaHasla(vector<Uzytkownik> &uzytkownicy, int idOstatniegoUzytkownika, int idZalogowanegoUzytkownika) {
    string haslo;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;
    cin.ignore();
    for (int i=0; i<idOstatniegoUzytkownika; i++) {
        if(uzytkownicy[i].id == idZalogowanegoUzytkownika) {
            uzytkownicy[i].haslo = haslo;
            cout << "Haslo zostalo zmnienione" << endl;
            Sleep(1500);
        }
    }
}

void zapiszUzytkownikowDoPliku(int idOstatniegoUzytkownika, const vector<Uzytkownik> &uzytkownicy) {
    fstream plik;
    string przerywnik="|";
    plik.open("Uzytkownicy.txt", ios::out);
    for (unsigned int i=0; i<uzytkownicy.size(); i++) {
        plik<<uzytkownicy[i].id<<przerywnik<<uzytkownicy[i].nazwa<<przerywnik<<uzytkownicy[i].haslo<<endl;
    }
    plik.close();
}

int stringToInt(string liczbaWFormacieString) {
    int liczbaWFormacieInt = atoi(liczbaWFormacieString.c_str());
    return liczbaWFormacieInt ;
}

int wczytanieUzytkownikowZPliku(vector<Uzytkownik> &uzytkownicy) {
    string linia;
    fstream plik;
    int ostatnieId=0;
    plik.open("Uzytkownicy.txt", ios::in);
    if(!plik.good()) {
        plik.open("Uzytkownicy.txt", ios::out);
        plik.close();
    } else {
        string komorkaZPliku[3];
        Uzytkownik uzytkownikTymczasowy;
        while (getline(plik, linia)) {
            int ilePozycji=4;
            for (int i = 0 ; i<ilePozycji-1 ; i++) {
                string przerywnik ="|";
                size_t pozycjaPrzerywnika = linia.find(przerywnik);
                komorkaZPliku[i] = linia.substr(0, pozycjaPrzerywnika);
                linia.erase(0,pozycjaPrzerywnika+1);
            }
            uzytkownikTymczasowy.id=stringToInt(komorkaZPliku[0]);
            uzytkownikTymczasowy.nazwa=komorkaZPliku[1];
            uzytkownikTymczasowy.haslo=komorkaZPliku[2];
            ostatnieId=stringToInt(komorkaZPliku[0]);
            uzytkownicy.push_back(uzytkownikTymczasowy);
        }
    }
    plik.close();
    return ostatnieId;
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

void wczytanieKontaktowZPliku(vector<Kontakt> &ksiazkaKontaktow, int idZalogowanegoUzytkownika) {
    string linia;
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);
    if(!plik.good()) {
        plik.open("KsiazkaAdresowa.txt", ios::out);
        plik.close();
    } else {
        string komorkaZPliku[6];
        Kontakt tempKontakt;
        while (getline(plik, linia)) {

            int ilePozycji=7;
            for (int i = 0 ; i<ilePozycji-1 ; i++) {
                string przerywnik ="|";
                size_t pozycjaPrzerywnika = linia.find(przerywnik);
                komorkaZPliku[i] = linia.substr(0, pozycjaPrzerywnika);
                linia.erase(0,pozycjaPrzerywnika+1);
            }
            if (stringToInt(komorkaZPliku[1]) == idZalogowanegoUzytkownika) {
                tempKontakt.id=stringToInt(komorkaZPliku[0]);
                tempKontakt.imie=komorkaZPliku[2];
                tempKontakt.nazwisko=komorkaZPliku[3];
                tempKontakt.numerTelefonu=komorkaZPliku[4];
                tempKontakt.email=komorkaZPliku[5];
                tempKontakt.adres=linia;
                ksiazkaKontaktow.push_back(tempKontakt);
            }
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

int sprawdzIdOstatniegoKontaktu () {
    string line;
    const string filename = "KsiazkaAdresowa.txt";
    ifstream fs;
    int id = 0;
    fs.open(filename.c_str(), std::fstream::in);
    if(!fs.is_open()) {
        std::cout << "Could not open file" << std::endl;
        return -1;
    } else {
        line = getLastLineInFile(fs);
        int howManyCells = 6;
        string cellFromFile [howManyCells];
        for (int i = 0 ; i<howManyCells ; i++) {
            string separator ="|";
            size_t positionOfSeparator = line.find(separator);
            cellFromFile[i] = line.substr(0, positionOfSeparator);
            line.erase(0,positionOfSeparator+1);

        }
        id=stringToInt(cellFromFile[0]);
    }
    return id;
}

int usunKontakt (vector <Kontakt> &ksiazkaKontaktow) {
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
    return idDoUsuniecia;
}

int edytujKontakt (vector <Kontakt> &ksiazkaKontaktow) {
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
            if ( (wybor == '1') || (wybor == '2') || (wybor == '3') || (wybor == '4') || (wybor == '5') ) {
                cout<<"Zmieniono";
            } else {
                cout << "Powrot do menu";
            }
        }
    }

    return idDoEdycji;
}

string intToStringConvert (int Number ) {
    ostringstream ss;
    ss << Number;
    return ss.str();
}

bool moveToStartOfLine(std::ifstream& fs) {
    fs.seekg(-2, std::ios_base::cur);
    for(long i = fs.tellg(); i > 0; i--) {
        if(fs.peek() == '\n') {
            fs.get();
            return true;
        }
        fs.seekg(i, std::ios_base::beg);
    }
    return false;
}

string getLastLineInFile(std::ifstream& fs) {
    // Go to the last character before EOF
    fs.seekg(-1, std::ios_base::end);
    if (!moveToStartOfLine(fs)) {
        fs.seekg(0, ios_base::beg);
    }


    std::string lastline = "";
    getline(fs, lastline);
    return lastline;
}

void zapiszOstatniKontaktDoPliku(int idOstatnioDodanegoKontaktu, const vector<Kontakt> &ksiazkaKontaktow, int idZalogowanegoUzytkownika ) {
    fstream plik;
    string przerywnik="|";
    plik.open("KsiazkaAdresowa.txt", ios::app);
    int i=ksiazkaKontaktow.size()-1;
    plik<<ksiazkaKontaktow[i].id<<przerywnik
        <<idZalogowanegoUzytkownika<<przerywnik
        <<ksiazkaKontaktow[i].imie<<przerywnik
        <<ksiazkaKontaktow[i].nazwisko<<przerywnik
        <<ksiazkaKontaktow[i].numerTelefonu<<przerywnik
        <<ksiazkaKontaktow[i].email<<przerywnik
        <<ksiazkaKontaktow[i].adres<<endl;
    plik.close();
}

void saveContactsToFile(int currentUserId, int contactId, const vector<Kontakt> &contactsBook ) {
    string line,
           StrFirstNumber = intToStringConvert(contactId),
           StrSecondNumber = intToStringConvert(currentUserId) ;
    string newFileName = "tempKsiazkaKontaktow.txt",
           oldFileName = "KsiazkaAdresowa.txt",
           przerywnik="|";
    fstream oldFile,
            newFile;
    oldFile.open(oldFileName.c_str(), ios::in);
    newFile.open(newFileName.c_str(), ios::out);
    int i=0;
    while ( (i<contactsBook.size()) && (contactId != contactsBook[i].id) ) {
        i++;
    }

    while (getline(oldFile, line)) {
        string phrase=StrFirstNumber+przerywnik+StrSecondNumber+przerywnik;
        size_t position = line.find(phrase);
        if (position!=string::npos) {
            if (i==contactsBook.size()) {
            } else {
                newFile<<contactsBook[i].id<<przerywnik
                       <<currentUserId<<przerywnik
                       <<contactsBook[i].imie<<przerywnik
                       <<contactsBook[i].nazwisko<<przerywnik
                       <<contactsBook[i].numerTelefonu<<przerywnik
                       <<contactsBook[i].email<<przerywnik
                       <<contactsBook[i].adres<<przerywnik<<endl;
            }

        } else {
            newFile<<line<<endl;
        }
    }
    oldFile.close();
    newFile.close();
    if (remove(oldFileName.c_str()) !=0)
        cout<<"Remove operation failed"<<endl;
    else
        rename(newFileName.c_str(),oldFileName.c_str());
}

