#include <iostream>

struct MedzioMazgas {
    int duomuo;
    MedzioMazgas* kairysis;
    MedzioMazgas* desinysis;
    MedzioMazgas(int d) : duomuo(d), kairysis(nullptr), desinysis(nullptr) {}
};

struct SarasasMazgas {
    int duomuo;
    SarasasMazgas* kitas;
    SarasasMazgas(int d) : duomuo(d), kitas(nullptr) {}
};

MedzioMazgas* iterptiMedzioMazga(MedzioMazgas* pradzios, int duomuo) {
    if (!pradzios) return new MedzioMazgas(duomuo);
    if (duomuo < pradzios->duomuo) pradzios->kairysis = iterptiMedzioMazga(pradzios->kairysis, duomuo);
    else pradzios->desinysis = iterptiMedzioMazga(pradzios->desinysis, duomuo);
    return pradzios;
}

MedzioMazgas* rastiMinimuma(MedzioMazgas* pradzios) {
    while (pradzios && pradzios->kairysis) pradzios = pradzios->kairysis;
    return pradzios;
}

MedzioMazgas* pasalintiMedzioMazga(MedzioMazgas* pradzios, int duomuo) {
    if (!pradzios) return nullptr;
    if (duomuo < pradzios->duomuo) pradzios->kairysis = pasalintiMedzioMazga(pradzios->kairysis, duomuo);
    else if (duomuo > pradzios->duomuo) pradzios->desinysis = pasalintiMedzioMazga(pradzios->desinysis, duomuo);
    else {
        if (!pradzios->kairysis) {
            MedzioMazgas* temp = pradzios->desinysis;
            delete pradzios;
            return temp;
        }
        if (!pradzios->desinysis) {
            MedzioMazgas* temp = pradzios->kairysis;
            delete pradzios;
            return temp;
        }
        MedzioMazgas* min = rastiMinimuma(pradzios->desinysis);
        pradzios->duomuo = min->duomuo;
        pradzios->desinysis = pasalintiMedzioMazga(pradzios->desinysis, min->duomuo);
    }
    return pradzios;
}

MedzioMazgas* ieskotiMedzioMazga(MedzioMazgas* pradzios, int duomuo) {
    if (!pradzios || pradzios->duomuo == duomuo) return pradzios;
    if (duomuo < pradzios->duomuo) return ieskotiMedzioMazga(pradzios->kairysis, duomuo);
    return ieskotiMedzioMazga(pradzios->desinysis, duomuo);
}

void spausdintiMedi(MedzioMazgas* pradzios) {
    if (pradzios) {
        spausdintiMedi(pradzios->kairysis);
        std::cout << pradzios->duomuo << " ";
        spausdintiMedi(pradzios->desinysis);
    }
}

SarasasMazgas* iterptiSarasoMazga(SarasasMazgas* pradzios, int duomuo) {
    SarasasMazgas* naujasMazgas = new SarasasMazgas(duomuo);
    if (!pradzios) return naujasMazgas;
    SarasasMazgas* einamasis = pradzios;
    while (einamasis->kitas) einamasis = einamasis->kitas;
    einamasis->kitas = naujasMazgas;
    return pradzios;
}

SarasasMazgas* perkeltiISarasa(MedzioMazgas* medzioPradzios, SarasasMazgas* sarasoPradzios) {
    if (medzioPradzios) {
        sarasoPradzios = perkeltiISarasa(medzioPradzios->kairysis, sarasoPradzios);
        sarasoPradzios = iterptiSarasoMazga(sarasoPradzios, medzioPradzios->duomuo);
        sarasoPradzios = perkeltiISarasa(medzioPradzios->desinysis, sarasoPradzios);
    }
    return sarasoPradzios;
}

void spausdintiSarasa(SarasasMazgas* pradzios) {
    SarasasMazgas* einamasis = pradzios;
    while (einamasis) {
        std::cout << einamasis->duomuo << " ";
        einamasis = einamasis->kitas;
    }
    std::cout << std::endl;
}

void atlaisvintiMedi(MedzioMazgas* pradzios) {
    if (pradzios) {
        atlaisvintiMedi(pradzios->kairysis);
        atlaisvintiMedi(pradzios->desinysis);
        delete pradzios;
    }
}

void atlaisvintiSarasa(SarasasMazgas* pradzios) {
    SarasasMazgas* einamasis = pradzios;
    while (einamasis) {
        SarasasMazgas* laikinas = einamasis;
        einamasis = einamasis->kitas;
        delete laikinas;
    }
}

int main() {
    MedzioMazgas* medzioPradzios = nullptr;
    SarasasMazgas* sarasoPradzios = nullptr;
    int pasirinkimas, duomuo;

    do {
        std::cout << "\n1. Iterpti elementa i medi\n";
        std::cout << "2. Pasalinti elementa is medzio\n";
        std::cout << "3. Ieskoti elemento medyje\n";
        std::cout << "4. Spausdinti medi\n";
        std::cout << "5. Perkelti medzio elementus i sarasa\n";
        std::cout << "6. Spausdinti sarasa\n";
        std::cout << "0. Baigti\n";
        std::cout << "Pasirinkite: ";
        std::cin >> pasirinkimas;

        switch (pasirinkimas) {
            case 1:
                std::cout << "Iveskite elementa: ";
                std::cin >> duomuo;
                medzioPradzios = iterptiMedzioMazga(medzioPradzios, duomuo);
                break;
            case 2:
                std::cout << "Iveskite pasalinama elementa: ";
                std::cin >> duomuo;
                medzioPradzios = pasalintiMedzioMazga(medzioPradzios, duomuo);
                break;
            case 3:
                std::cout << "Iveskite ieskoma elementa: ";
                std::cin >> duomuo;
                if (ieskotiMedzioMazga(medzioPradzios, duomuo)) std::cout << "Elementas rastas\n";
                else std::cout << "Elementas nerastas\n";
                break;
            case 4:
                if (medzioPradzios) spausdintiMedi(medzioPradzios);
                else std::cout << "Medis tuscias\n";
                std::cout << std::endl;
                break;
            case 5:
                atlaisvintiSarasa(sarasoPradzios);
                sarasoPradzios = nullptr;
                sarasoPradzios = perkeltiISarasa(medzioPradzios, sarasoPradzios);
                break;
            case 6:
                if (sarasoPradzios) spausdintiSarasa(sarasoPradzios);
                else std::cout << "Sarasas tuscias\n";
                break;
            case 0:
                break;
            default:
                std::cout << "Neteisingas pasirinkimas\n";
        }
    } while (pasirinkimas != 0);

    atlaisvintiMedi(medzioPradzios);
    atlaisvintiSarasa(sarasoPradzios);
    return 0;
}