#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct User {
    int id;
    string login, password;
};

struct Contact {
    int id=0;
    string name="", surname="", tel="", email="", address="";
};

int saveContact(int idLastContact, vector<Contact> &addressBook);

void showAddressBook (const vector<Contact> &addressBook);

void searchByName(const vector<Contact> &addressBook);

void searchBySurname(const vector<Contact> &addressBook);

void contactsLoadFromFile(vector<Contact> &addressBook, int idLoggedUser) ;

void displayContact (const vector<Contact> &addressBook, int idContact);

int checkLastContactId ();

int deleteContact (vector <Contact> &addressBook);

int editContact (vector <Contact> &addressBook);

int stringToInt(string strNumber);

int createNewUser( vector<User> &users, int usersCout);

int logIn(const vector<User> users, int idLastUser);

void changePassword(vector<User> &users, int idLastUser, int idLoggedUser);

void exportUsersToFile(int idLastUser, const vector<User> &users);

int importUsersFromFile(vector<User> &users);

string intToStringConvert (int Number );

bool moveToStartOfLine(ifstream& fs);

string getLastLineInFile(ifstream& fs) ;

void exportLastContactToFile(int idLastContact, const vector<Contact> &addressBook, int idLoggedUser ) ;

void saveContactsToFile(int currentUserId, int contactId, const vector<Contact> &contactsBook );

int main() {
    vector <User> users;
    vector <Contact> addressBook;
    int idLoggedUser = 0;
    int idLastUser = 0;
    idLastUser = importUsersFromFile(users);
    char option;

    while (1) {
        if (idLoggedUser == 0) {
            system("cls");
            cout << "MENU GLOWNE" << endl
                 << "______________" << endl
                 << "1. Rejestracja" <<endl
                 << "2. Logowanie" << endl
                 << "9. Zakoncz program" << endl
                 << "______________" << endl
                 << "Czego potrzebujesz?" << endl;
            cin >> option;
            cin.ignore();
            switch(option) {
            case '1':
                idLastUser = createNewUser(users,idLastUser);
                exportUsersToFile(idLastUser, users);
                break;
            case '2':
                idLoggedUser = logIn(users,idLastUser);
                break;
            case '9':
                exportUsersToFile(idLastUser, users);
                exit(0);
                break;
            default:
                cout << "Wprowadz inna liczbe!";
                Sleep (1000);
                system ("cls");
            }
        } else {
            int idLastContact=0;
            contactsLoadFromFile( addressBook, idLoggedUser);
            while (idLoggedUser != 0) {
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
                cin >> option;
                cin.ignore();
                switch(option) {
                case '1': {
                    idLastContact = checkLastContactId ();
                    saveContact(idLastContact, addressBook);
                    exportLastContactToFile(idLastContact, addressBook, idLoggedUser);
                    Sleep (1000);
                    system ("cls");
                    break;
                }

                case '2': {
                    searchByName(addressBook);
                    Sleep (1000);
                    system ("cls");
                    break;
                }

                case '3': {
                    searchBySurname(addressBook);
                    Sleep (1000);
                    system ("cls");
                    break;
                }

                case '4': {
                    showAddressBook (addressBook);
                    Sleep (1000);
                    system ("cls");
                    break;
                }

                case '5': {
                    int idContactToDelete = deleteContact (addressBook);
                    saveContactsToFile(idLoggedUser, idContactToDelete, addressBook );
                    Sleep (1000);
                    system ("cls");
                    break;
                }
                case '6': {
                    int idContactToEdit = editContact (addressBook);
                    saveContactsToFile(idLoggedUser, idContactToEdit, addressBook );
                    Sleep (1000);
                    system ("cls");
                    break;
                }
                case '7': {
                    changePassword(users, idLastUser, idLoggedUser);
                    exportUsersToFile(idLastUser, users);
                    break;
                }
                case '8': {
                    idLoggedUser=0;
                    addressBook.erase(addressBook.begin(), addressBook.end());
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

int createNewUser( vector<User> &users, int usersCout) {

    string login, password;
    cout << "Podaj nazwe uzytkownika: ";
    cin >>login;
    cin.ignore();
    int i = 0;
    while (i < usersCout) {
        if(users[i].login == login) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> login;
            cin.ignore();
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> password;
    cin.ignore();
    User tempUser;
    tempUser.login = login;
    tempUser.password = password;
    tempUser.id = usersCout + 1;
    users.push_back(tempUser);
    cout << "Konto zalozone" << endl;
    Sleep(1000);
    return usersCout+1;
}

int logIn(const vector<User> users, int idLastUser) {
    string login, password;
    cout << "Podaj login: ";
    cin >> login;
    cin.ignore();
    int i = 0;
    while (i < idLastUser) {
        if(users[i].login == login) {
            for (int attempt = 0; attempt < 3; attempt++) {
                if (attempt==0) {
                    cout << "Podaj haslo:";
                } else {
                    cout << "Podaj haslo. Pozostalo prob " << 3-attempt<< ": ";
                }

                cin >> password;
                cin.ignore();
                if (users[i].password == password) {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return users[i].id;
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

void changePassword(vector<User> &users, int idLastUser, int idLoggedUser) {
    string password;
    cout << "Podaj nowe haslo: ";
    cin >> password;
    cin.ignore();
    for (int i=0; i<idLastUser; i++) {
        if(users[i].id == idLoggedUser) {
            users[i].password = password;
            cout << "Haslo zostalo zmnienione" << endl;
            Sleep(1500);
        }
    }
}

void exportUsersToFile(int idLastUser, const vector<User> &users) {
    fstream file;
    string separator="|";
    file.open("Uzytkownicy.txt", ios::out);
    for (unsigned int i=0; i<users.size(); i++) {
        file<<users[i].id<<separator<<users[i].login<<separator<<users[i].password<<endl;
    }
    file.close();
}

int stringToInt(string strNumber) {
    int intNumber = atoi(strNumber.c_str());
    return intNumber ;
}

int importUsersFromFile(vector<User> &users) {
    string line;
    fstream file;
    int lastId=0;
    file.open("Uzytkownicy.txt", ios::in);
    if(!file.good()) {
        file.open("Uzytkownicy.txt", ios::out);
        file.close();
    } else {
        string cellFile[3];
        User tempUser;
        while (getline(file, line)) {
            int howManyCells=4;
            for (int i = 0 ; i<howManyCells-1 ; i++) {
                string separator ="|";
                size_t separatorPosition = line.find(separator);
                cellFile[i] = line.substr(0, separatorPosition);
                line.erase(0,separatorPosition+1);
            }
            tempUser.id=stringToInt(cellFile[0]);
            tempUser.login=cellFile[1];
            tempUser.password=cellFile[2];
            lastId=stringToInt(cellFile[0]);
            users.push_back(tempUser);
        }
    }
    file.close();
    return lastId;
}

int saveContact(int idLastContact, vector<Contact> &addressBook) {
    idLastContact++;
    Contact tempContact;
    tempContact.id = idLastContact;
    cout << "ZAPISYWANIE NOWEGO KONTAKTU:" << endl;
    cout << "Imie:";
    getline(cin,tempContact.name);
    cout << "Nazwisko:";
    getline(cin,tempContact.surname);
    cout << "Numer telefonu:";
    getline(cin,tempContact.tel);
    cout << "Adres email:";
    getline(cin,tempContact.email);
    cout << "Adres zamieszkania:";
    getline(cin,tempContact.address);
    addressBook.push_back(tempContact);
    cout << "Kontakt zapisany!";
    return idLastContact;
}

void contactsLoadFromFile(vector<Contact> &addressBook, int idLoggedUser) {
    string line;
    fstream file;
    file.open("KsiazkaAdresowa.txt", ios::in);
    if(!file.good()) {
        file.open("KsiazkaAdresowa.txt", ios::out);
        file.close();
    } else {
        string cellFile[6];
        Contact tempContact;
        while (getline(file, line)) {

            int howManyCells=7;
            for (int i = 0 ; i<howManyCells-1 ; i++) {
                string separator ="|";
                size_t separatorPosition = line.find(separator);
                cellFile[i] = line.substr(0, separatorPosition);
                line.erase(0,separatorPosition+1);
            }
            if (stringToInt(cellFile[1]) == idLoggedUser) {
                tempContact.id=stringToInt(cellFile[0]);
                tempContact.name=cellFile[2];
                tempContact.surname=cellFile[3];
                tempContact.tel=cellFile[4];
                tempContact.email=cellFile[5];
                tempContact.address=line;
                addressBook.push_back(tempContact);
            }
        }
    }
    file.close();
}

void showAddressBook (const vector<Contact> &addressBook) {
    cout << "TWOJE KONTAKTY:" << endl;
    for (unsigned int i=0; i<addressBook.size(); i++) {
        displayContact (addressBook, i );
        cout<<endl;
    }
    cout << "Nacisnij dowolny klawisz";
    getch();
    system("cls");
}

void searchByName(const vector<Contact> &addressBook) {
    string phrase;
    bool found=0;
    cout<<"Wpisz fraze do wyszukania: ";
    getline( cin, phrase);
    for (unsigned int i=0; i<addressBook.size(); i++) {
        size_t position = addressBook[i].name.find(phrase);
        if (position!=string::npos) {
            found=1;
            displayContact (addressBook, i );
        }
        if (i==addressBook.size()-1) {
            if(found!=0)
                cout << "To wszystko"<<endl;
            else
                cout << "Nie znaleziono!" <<endl;
        }
    }
    cout << "Nacisnij dowolny klawisz";
    getch();
}

void searchBySurname(const vector<Contact> &addressBook) {
    string phrase;
    bool found=0;
    cout<<"Wpisz fraze do wyszukania: ";
    getline( cin, phrase);
    for (unsigned int i=0; i<addressBook.size(); i++) {
        size_t position = addressBook[i].surname.find(phrase);
        if (position!=string::npos) {
            found=1;
            displayContact (addressBook, i );
        }
        if (i==addressBook.size()-1) {
            if(found!=0)
                cout << "To wszystko"<<endl;
            else
                cout << "Nie znaleziono!" <<endl;
        }

    }
    cout << "Nacisnij dowolny klawisz";
    getch();
}

void displayContact (const vector<Contact> &addressBook, int idContact) {
    cout <<addressBook[idContact].id << endl;
    cout << "Imie: " <<addressBook[idContact].name << endl;
    cout << "Nazwisko: "<<addressBook[idContact].surname<< endl;
    cout << "Numer telefonu: " <<addressBook[idContact].tel << endl;
    cout << "Adres email: "<<addressBook[idContact].email<<endl;
    cout << "Adres zamieszkania: "<<addressBook[idContact].address<<endl;
}

int checkLastContactId () {
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

int deleteContact (vector <Contact> &addressBook) {
    int idContactToDelete = -1, i=0;
    cout << "Podaj numer id adresata, ktorego chcesz usunac" <<endl;
    cin >> idContactToDelete;
    cin.ignore();
    while ( (i<addressBook.size()) && (idContactToDelete != addressBook[i].id) ) {
        i++;
    }
    if (i == addressBook.size()) {
        cout << "Nie znaleziono id"<<endl;
    } else {
        cout << "Czy chcesz usunac kontakt:";
        displayContact(addressBook, i);
        cout << "t - TAK" << endl << "n - NIE"<< endl;
        char option = getch();
        if(option == 't') {
            addressBook.erase(addressBook.begin()+i);
            cout << "Usunieto kontakt"<<endl;
        } else {
            cout << "Nie usunieto"<<endl;
        }
    }
    return idContactToDelete;
}

int editContact (vector <Contact> &addressBook) {
    int idContactToEdit = -1, i=0;
    cout << "Podaj numer id adresata, ktorego chcesz edytowac" <<endl;
    cin >> idContactToEdit;
    cin.ignore();
    while ( (i<addressBook.size()) && (idContactToEdit != addressBook[i].id) ) {
        i++;
    }
    if (i == addressBook.size()) {
        cout << "Nie znaleziono id"<<endl;
    } else {
        cout << "Czy chcesz edytowac kontakt:";
        displayContact(addressBook, i);
        cout << "Ktore pole edytowac: " << endl
             << "1. imie" << endl
             << "2. nazwisko" << endl
             << "3. numer telefonu" << endl
             << "4. email" << endl
             << "5. adres" << endl
             << "6. powrot do menu" << endl;
        char option = getch();
        switch(option) {
        case '1':
            cout << "Imie: ";
            cin >> addressBook[i].name;
            cin.ignore();
            break;
        case '2':
            cout << "Nazwisko: ";
            cin >> addressBook[i].surname;
            cin.ignore();
            break;
        case '3':
            cout << "Numer telefonu: ";
            getline(cin, addressBook[i].tel);
            cin.ignore();
            break;
        case '4':
            cout << "Email: ";
            cin >> addressBook[i].email;
            cin.ignore();
            break;
        case '5':
            cout << "Adres: ";
            getline(cin,addressBook[i].address);
            break;
        default:
            ;
            if ( (option == '1') || (option == '2') || (option == '3') || (option == '4') || (option == '5') ) {
                cout<<"Zmieniono";
            } else {
                cout << "Powrot do menu";
            }
        }
    }

    return idContactToEdit;
}

string intToStringConvert (int Number ) {
    ostringstream ss;
    ss << Number;
    return ss.str();
}

bool moveToStartOfLine(ifstream& fs) {
    fs.seekg(-2, ios_base::cur);
    for(long i = fs.tellg(); i > 0; i--) {
        if(fs.peek() == '\n') {
            fs.get();
            return true;
        }
        fs.seekg(i, ios_base::beg);
    }
    return false;
}

string getLastLineInFile(ifstream& fs) {
    // Go to the last character before EOF
    fs.seekg(-1, ios_base::end);
    if (!moveToStartOfLine(fs)) {
        fs.seekg(0, ios_base::beg);
    }


    string lastline = "";
    getline(fs, lastline);
    return lastline;
}

void exportLastContactToFile(int idLastContact, const vector<Contact> &addressBook, int idLoggedUser ) {
    fstream file;
    string separator="|";
    file.open("KsiazkaAdresowa.txt", ios::app);
    int i=addressBook.size()-1;
    file<<addressBook[i].id<<separator
        <<idLoggedUser<<separator
        <<addressBook[i].name<<separator
        <<addressBook[i].surname<<separator
        <<addressBook[i].tel<<separator
        <<addressBook[i].email<<separator
        <<addressBook[i].address<<endl;
    file.close();
}

void saveContactsToFile(int currentUserId, int contactId, const vector<Contact> &contactsBook ) {
    string line,
           StrFirstNumber = intToStringConvert(contactId),
           StrSecondNumber = intToStringConvert(currentUserId) ;
    string newFileName = "tempKsiazkaKontaktow.txt",
           oldFileName = "KsiazkaAdresowa.txt",
           separator="|";
    fstream oldFile,
            newFile;
    oldFile.open(oldFileName.c_str(), ios::in);
    newFile.open(newFileName.c_str(), ios::out);
    int i=0;
    while ( (i<contactsBook.size()) && (contactId != contactsBook[i].id) ) {
        i++;
    }

    while (getline(oldFile, line)) {
        string phrase=StrFirstNumber+separator+StrSecondNumber+separator;
        size_t position = line.find(phrase);
        if (position!=string::npos) {
            if (i==contactsBook.size()) {
            } else {
                newFile<<contactsBook[i].id<<separator
                       <<currentUserId<<separator
                       <<contactsBook[i].name<<separator
                       <<contactsBook[i].surname<<separator
                       <<contactsBook[i].tel<<separator
                       <<contactsBook[i].email<<separator
                       <<contactsBook[i].address<<separator<<endl;
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

