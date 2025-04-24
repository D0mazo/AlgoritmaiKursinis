#include <iostream>
#include <string>
#include <queue>

// Node structure for linked list
struct Mazgas {
    char duomuo;
    Mazgas* kitas;
    Mazgas(char d) : duomuo(d), kitas(nullptr) {}
};

// Node structure for binary tree
struct MedzioMazgas {
    char duomuo;
    MedzioMazgas* kairys;
    MedzioMazgas* desinys;
    MedzioMazgas(char d) : duomuo(d), kairys(nullptr), desinys(nullptr) {}
};

// Linked list functions
Mazgas* iterpti(Mazgas* pradzios, char duomuo) {
    Mazgas* naujasMazgas = new Mazgas(duomuo);
    if (!pradzios) return naujasMazgas;
    Mazgas* einamasis = pradzios;
    while (einamasis->kitas) einamasis = einamasis->kitas;
    einamasis->kitas = naujasMazgas;
    return pradzios;
}

Mazgas* sukurtiNaujaSarasa(Mazgas* pradzios, int n) {
    if (!pradzios) return nullptr;
    Mazgas* einamasis = pradzios;
    int tarpuSkaicius = 0;
    while (einamasis) {
        if (einamasis->duomuo == ' ') tarpuSkaicius++;
        einamasis = einamasis->kitas;
    }
    if (tarpuSkaicius != 1) return nullptr;
    einamasis = pradzios;
    Mazgas* tarpas = nullptr;
    while (einamasis) {
        if (einamasis->duomuo == ' ') tarpas = einamasis;
        einamasis = einamasis->kitas;
    }
    Mazgas* naujaPradzia = tarpas->kitas;
    if (!naujaPradzia) return pradzios;
    einamasis = naujaPradzia;
    while (einamasis->kitas) einamasis = einamasis->kitas;
    einamasis->kitas = pradzios;
    tarpas->kitas = nullptr;
    return naujaPradzia;
}

void spausdintiSarasa(Mazgas* pradzios) {
    Mazgas* einamasis = pradzios;
    while (einamasis) {
        if (einamasis->duomuo == ' ') std::cout << "_ ";
        else std::cout << einamasis->duomuo << " ";
        einamasis = einamasis->kitas;
    }
    std::cout << std::endl;
}

void atlaisvintiSarasa(Mazgas* pradzios) {
    Mazgas* einamasis = pradzios;
    while (einamasis) {
        Mazgas* laikinas = einamasis;
        einamasis = einamasis->kitas;
        delete laikinas;
    }
}

// Binary tree functions
MedzioMazgas* iterptiIMedi(MedzioMazgas* saknis, char duomuo) {
    if (!saknis) return new MedzioMazgas(duomuo);
    
    if (duomuo < saknis->duomuo)
        saknis->kairys = iterptiIMedi(saknis->kairys, duomuo);
    else if (duomuo > saknis->duomuo)
        saknis->desinys = iterptiIMedi(saknis->desinys, duomuo);
    
    return saknis;
}

MedzioMazgas* rastiMin(MedzioMazgas* mazgas) {
    MedzioMazgas* current = mazgas;
    while (current && current->kairys)
        current = current->kairys;
    return current;
}

MedzioMazgas* pasalintiIsMedzio(MedzioMazgas* saknis, char duomuo) {
    if (!saknis) return saknis;
    
    if (duomuo < saknis->duomuo)
        saknis->kairys = pasalintiIsMedzio(saknis->kairys, duomuo);
    else if (duomuo > saknis->duomuo)
        saknis->desinys = pasalintiIsMedzio(saknis->desinys, duomuo);
    else {
        if (!saknis->kairys) {
            MedzioMazgas* temp = saknis->desinys;
            delete saknis;
            return temp;
        } else if (!saknis->desinys) {
            MedzioMazgas* temp = saknis->kairys;
            delete saknis;
            return temp;
        }
        
        MedzioMazgas* temp = rastiMin(saknis->desinys);
        saknis->duomuo = temp->duomuo;
        saknis->desinys = pasalintiIsMedzio(saknis->desinys, temp->duomuo);
    }
    return saknis;
}

bool ieskotiMedyje(MedzioMazgas* saknis, char duomuo) {
    if (!saknis) return false;
    if (saknis->duomuo == duomuo) return true;
    if (duomuo < saknis->duomuo)
        return ieskotiMedyje(saknis->kairys, duomuo);
    else
        return ieskotiMedyje(saknis->desinys, duomuo);
}

void spausdintiMedi(MedzioMazgas* saknis) {
    if (!saknis) return;
    spausdintiMedi(saknis->kairys);
    if (saknis->duomuo == ' ') std::cout << "_ ";
    else std::cout << saknis->duomuo << " ";
    spausdintiMedi(saknis->desinys);
}

void spausdintiMediLygiu(MedzioMazgas* saknis) {
    if (!saknis) return;
    
    std::queue<MedzioMazgas*> q;
    q.push(saknis);
    
    while (!q.empty()) {
        int count = q.size();
        while (count > 0) {
            MedzioMazgas* mazgas = q.front();
            q.pop();
            if (mazgas->duomuo == ' ') std::cout << "_ ";
            else std::cout << mazgas->duomuo << " ";
            
            if (mazgas->kairys) q.push(mazgas->kairys);
            if (mazgas->desinys) q.push(mazgas->desinys);
            count--;
        }
        std::cout << std::endl;
    }
}

void atlaisvintiMedi(MedzioMazgas* saknis) {
    if (!saknis) return;
    atlaisvintiMedi(saknis->kairys);
    atlaisvintiMedi(saknis->desinys);
    delete saknis;
}

// Transfer binary tree to linked list
Mazgas* medisISarasa(MedzioMazgas* saknis, Mazgas* sarasas = nullptr) {
    if (!saknis) return sarasas;
    sarasas = medisISarasa(saknis->kairys, sarasas);
    sarasas = iterpti(sarasas, saknis->duomuo);
    sarasas = medisISarasa(saknis->desinys, sarasas);
    return sarasas;
}

void ivestiSarasa(Mazgas*& pradzios, int& n) {
    std::cout << "Iveskite simboliu skaiciu n: ";
    std::cin >> n;
    std::cin.ignore(); // Clear the newline from buffer
    if (n <= 0) {
        n = 0;
        return;
    }
    pradzios = nullptr;
    std::cout << "Iveskite " << n << " simbolius is eiles (tarpui naudokite tarpo klavisa): ";
    std::string input;
    std::getline(std::cin, input);
    
    // Take only first n characters
    for (int i = 0; i < n && i < input.size(); i++) {
        pradzios = iterpti(pradzios, input[i]);
    }
    
    // If not enough characters were entered, fill with spaces
    while (input.size() < n) {
        pradzios = iterpti(pradzios, ' ');
        input += ' ';
    }
    
    Mazgas* einamasis = pradzios;
    int tarpuSkaicius = 0;
    while (einamasis) {
        if (einamasis->duomuo == ' ') tarpuSkaicius++;
        einamasis = einamasis->kitas;
    }
    if (tarpuSkaicius != 1) {
        std::cout << "Klaida: sarase turi buti tiksliai vienas tarpas. Bandykite is naujo.\n";
        atlaisvintiSarasa(pradzios);
        pradzios = nullptr;
        n = 0;
    }
}

int main() {
    Mazgas* pradzios = nullptr;
    Mazgas* naujaPradzia = nullptr;
    MedzioMazgas* medis = nullptr;
    Mazgas* medzioSarasas = nullptr;
    int n = 0;
    int pasirinkimas;

    do {
        std::cout << "\n1. Ivesti sarasa\n";
        std::cout << "2. Sukurti ir spausdinti nauja sarasa\n";
        std::cout << "3. Sukurti dvejetaini medi is sio saraso\n";
        std::cout << "4. Spausdinti medi (in-order)\n";
        std::cout << "5. Spausdinti medi (lygiais)\n";
        std::cout << "6. Ieskoti elemento medyje\n";
        std::cout << "7. Panaikinti elementa is medzio\n";
        std::cout << "8. Perkelti medzio elementus i vienkrypti sarasa\n";
        std::cout << "9. Spausdinti vienkrypcio saraso elementus\n";
        std::cout << "0. Baigti\n";
        std::cout << "Pasirinkite: ";
        std::cin >> pasirinkimas;

        switch (pasirinkimas) {
            case 1:
                atlaisvintiSarasa(pradzios);
                atlaisvintiSarasa(naujaPradzia);
                atlaisvintiMedi(medis);
                atlaisvintiSarasa(medzioSarasas);
                ivestiSarasa(pradzios, n);
                break;
            case 2:
                atlaisvintiSarasa(naujaPradzia);
                naujaPradzia = sukurtiNaujaSarasa(pradzios, n);
                if (naujaPradzia) {
                    std::cout << "Naujas sarasas: ";
                    spausdintiSarasa(naujaPradzia);
                }
                else std::cout << "Klaida: sarasas tuscias arba neteisingas\n";
                break;
            case 3:
                atlaisvintiMedi(medis);
                medis = nullptr;
                if (pradzios) {
                    Mazgas* current = pradzios;
                    while (current) {
                        medis = iterptiIMedi(medis, current->duomuo);
                        current = current->kitas;
                    }
                    std::cout << "Dvejetainis medis sukurtas is sio saraso.\n";
                } else {
                    std::cout << "Klaida: sarasas tuscias\n";
                }
                break;
            case 4:
                if (medis) {
                    std::cout << "Medis (in-order): ";
                    spausdintiMedi(medis);
                    std::cout << std::endl;
                } else {
                    std::cout << "Medis tuscias\n";
                }
                break;
            case 5:
                if (medis) {
                    std::cout << "Medis (lygiais):\n";
                    spausdintiMediLygiu(medis);
                } else {
                    std::cout << "Medis tuscias\n";
                }
                break;
            case 6: {
                if (!medis) {
                    std::cout << "Medis tuscias\n";
                    break;
                }
                std::cout << "Iveskite ieskoma simboli: ";
                char c;
                std::cin >> c;
                if (ieskotiMedyje(medis, c))
                    std::cout << "Elementas '" << c << "' rastas medyje\n";
                else
                    std::cout << "Elementas '" << c << "' nerastas medyje\n";
                break;
            }
            case 7: {
                if (!medis) {
                    std::cout << "Medis tuscias\n";
                    break;
                }
                std::cout << "Iveskite trinama simboli: ";
                char c;
                std::cin >> c;
                if (ieskotiMedyje(medis, c)) {
                    medis = pasalintiIsMedzio(medis, c);
                    std::cout << "Elementas '" << c << "' pasalintas is medzio\n";
                } else {
                    std::cout << "Elementas '" << c << "' nerastas medyje\n";
                }
                break;
            }
            case 8:
                atlaisvintiSarasa(medzioSarasas);
                medzioSarasas = medisISarasa(medis);
                std::cout << "Medzio elementai perkelti i vienkrypti sarasa\n";
                break;
            case 9:
                if (medzioSarasas) {
                    std::cout << "Vienkrypcio saraso elementai: ";
                    spausdintiSarasa(medzioSarasas);
                } else {
                    std::cout << "Sarasas tuscias\n";
                }
                break;
            case 0:
                break;
            default:
                std::cout << "Neteisingas pasirinkimas\n";
        }
    } while (pasirinkimas != 0);

    atlaisvintiSarasa(pradzios);
    atlaisvintiSarasa(naujaPradzia);
    atlaisvintiMedi(medis);
    atlaisvintiSarasa(medzioSarasas);
    return 0;
}