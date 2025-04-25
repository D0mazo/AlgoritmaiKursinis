#include <iostream>

struct Mazgas {
    char duomuo;
    Mazgas* ankstesnis;
    Mazgas* kitas;
    Mazgas(char d) : duomuo(d), ankstesnis(nullptr), kitas(nullptr) {}
};

Mazgas* iterpti(Mazgas* pradzios, char duomuo) {
    Mazgas* naujasMazgas = new Mazgas(duomuo);
    if (!pradzios) return naujasMazgas;
    Mazgas* einamasis = pradzios;
    while (einamasis->kitas) einamasis = einamasis->kitas;
    einamasis->kitas = naujasMazgas;
    naujasMazgas->ankstesnis = einamasis;
    return pradzios;
}

Mazgas* pasalintiZodzius(Mazgas* pradzios) {
    Mazgas* einamasis = pradzios;
    while (einamasis) {
        if ((einamasis->duomuo == 'A' || einamasis->duomuo == 'a') &&
            (einamasis == pradzios || einamasis->ankstesnis->duomuo == ' ' ||
             einamasis->ankstesnis->duomuo == ',' || einamasis->ankstesnis->duomuo == '.')) {
            Mazgas* zodzioPradzia = einamasis;
            while (einamasis && einamasis->duomuo != ' ' && einamasis->duomuo != ',' &&
                   einamasis->duomuo != '.') einamasis = einamasis->kitas;
            Mazgas* poZodzio = einamasis;
            if (zodzioPradzia == pradzios) {
                pradzios = poZodzio;
                if (pradzios) pradzios->ankstesnis = nullptr;
            } else {
                zodzioPradzia->ankstesnis->kitas = poZodzio;
                if (poZodzio) poZodzio->ankstesnis = zodzioPradzia->ankstesnis;
            }
            Mazgas* temp = zodzioPradzia;
            while (temp != poZodzio) {
                Mazgas* kita = temp->kitas;
                delete temp;
                temp = kita;
            }
            einamasis = poZodzio;
        } else {
            einamasis = einamasis->kitas;
        }
    }
    return pradzios;
}

void spausdintiSarasa(Mazgas* pradzios) {
    Mazgas* einamasis = pradzios;
    while (einamasis) {
        std::cout << einamasis->duomuo;
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

void ivestiSarasa(Mazgas*& pradzios) {
    std::cout << "Iveskite simboliu seka (baigti su Enter):\n";
    atlaisvintiSarasa(pradzios);
    pradzios = nullptr;
    char c;
    std::cin.ignore();
    while (std::cin.get(c) && c != '\n') {
        pradzios = iterpti(pradzios, c);
    }
}

int main() {
    Mazgas* pradzios = nullptr;
    int pasirinkimas;

    do {
        std::cout << "\n1. Ivesti simboliu seka\n";
        std::cout << "2. Pasalinti zodzius, prasidedancius raide A\n";
        std::cout << "3. Spausdinti sarasa\n";
        std::cout << "0. Baigti\n";
        std::cout << "Pasirinkite: ";
        std::cin >> pasirinkimas;

        switch (pasirinkimas) {
            case 1:
                ivestiSarasa(pradzios);
                break;
            case 2:
                pradzios = pasalintiZodzius(pradzios);
                break;
            case 3:
                if (pradzios) spausdintiSarasa(pradzios);
                else std::cout << "Sarasas tuscias\n";
                break;
            case 0:
                break;
            default:
                std::cout << "Neteisingas pasirinkimas\n";
        }
    } while (pasirinkimas != 0);

    atlaisvintiSarasa(pradzios);
    return 0;
}