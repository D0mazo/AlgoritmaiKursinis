#include <iostream>
#include <string>

struct Mazgas {
    char duomuo;
    Mazgas* kitas;
    Mazgas(char d) : duomuo(d), kitas(nullptr) {}
};

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
        if (einamasis->duomuo == ' ') std::cout << "_";
        else std::cout << einamasis->duomuo;
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
    int n = 0;
    int pasirinkimas;

    do {
        std::cout << "\n1. Ivesti sarasa\n";
        std::cout << "2. Sukurti ir spausdinti nauja sarasa\n";
        std::cout << "0. Baigti\n";
        std::cout << "Pasirinkite: ";
        std::cin >> pasirinkimas;

        switch (pasirinkimas) {
            case 1:
                atlaisvintiSarasa(pradzios);
                atlaisvintiSarasa(naujaPradzia);
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
            case 0:
                break;
            default:
                std::cout << "Neteisingas pasirinkimas\n";
        }
    } while (pasirinkimas != 0);

    atlaisvintiSarasa(pradzios);
    atlaisvintiSarasa(naujaPradzia);
    return 0;
}