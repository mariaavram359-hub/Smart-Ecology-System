#include "DeseuSticla.h"
#include <iostream>
#include <string>

DeseuSticla::DeseuSticla(float cantitate_sticla, CuloareSticla cul, bool sparta)
    : Deseu(cantitate_sticla), culoare(cul), este_sparta(sparta) {}

int DeseuSticla::timp_descompunere_ani() const {
    return 4000;
}

std::string DeseuSticla::get_tip() const {
    return "Sticla";
}

bool DeseuSticla::get_este_sparta() const {
    return este_sparta;
}

std::string DeseuSticla::culoare_to_string() const {
    switch (culoare) {
        case CuloareSticla::TRANSPARENTA: return "Transparenta";
        case CuloareSticla::VERDE: return "Verde";
        case CuloareSticla::MARO: return "Maro";
        case CuloareSticla::MIXTA: return "Mixta (Sortare dificila)";
        default: return "Necunoscuta";
    }
}

float DeseuSticla::calculeaza_amprenta_carbon() const {
    float baza = cantitate * 1.2f;
    // Daca sticla e mixta, masinariile de sortare optica consuma mai multa energie
    if (culoare == CuloareSticla::MIXTA) {
        baza += (cantitate * 0.5f);
    }
    return baza;
}

void DeseuSticla::afiseaza_impl(std::ostream& os) const {
    os << " -> Culoare sticla: " << culoare_to_string() << "\n";
    os << " -> Stare: " << (get_este_sparta() ? "Sparta (Cioburi)" : "Intreaga") << "\n";
    os << " -> Timp estimat descompunere: " << timp_descompunere_ani() << " ani (practic infinit).\n";
    os << " -> Amprenta de carbon generata: " << calculeaza_amprenta_carbon() << " kg CO2.";
}

std::string DeseuSticla::genereaza_raport_ecologic() const {
    std::string raport;
    raport += "=== RAPORT ECOLOGIC - DESEU STICLA ===\n";
    raport += "Cantitate: " + std::to_string(cantitate) + " kg\n";
    raport += "Timp de descompunere: " + std::to_string(timp_descompunere_ani()) + " ani\n";
    raport += "Amprenta carbon totala: " + std::to_string(calculeaza_amprenta_carbon()) + " kg CO2\n";
    raport += "\n[Analiza Impact]\n";

    if (cantitate < 20.0f) {
        raport += "  - Impact mediu. Deseul este greu, dar poate fi reciclat 100% la infinit fara pierderea calitatii.\n";
        raport += "  - Recomandare: Sortare prealabila pe culori (alba, verde, maro) pentru eficienta maxima.\n";
    } else if (cantitate < 100.0f) {
        raport += "  - Cantitate considerabila. Reciclarea economiseste aprox. " + std::to_string(static_cast<int>(cantitate * 1.2f)) + " kg de materii prime naturale (nisip, soda cenusa, calcar).\n";
        raport += "  - Contribuie la reducerea consumului de energie in cuptoarele de topire cu ~30% fata de productia virgina.\n";
        raport += "  - Atentie la manipulare pentru a evita generarea cioburilor fine care pot contamina alte materiale reciclabile.\n";
    } else {
        raport += "  - Cantitate MASIVA de deseuri din sticla!\n";
        raport += "  - Provocare logistica majora: greutatea foarte mare creste exponential costurile de transport si uzura vehiculelor.\n";
        raport += "  - Risc ridicat de accidente mecanice din cauza fisurilor cauzate de presiunea masei adunate.\n";
        raport += "  - ATENTIE: Necesita colectare cu autoutilitare prevazute cu brate hidraulice grele si cuve ranforsate!\n";
    }

    raport += "\n[Solutii si Valorificare]\n";
    raport += "  1. Topire in cuptoare la 1500 grade si turnare in ambalaje noi.\n";
    raport += "  2. Concasare fina si utilizare ca inlocuitor ecologic de nisip in industria constructiilor (asfalt, beton).\n";
    raport += "  3. Transformare in vata minerala izolatoare pentru cladiri.\n";
    raport += "=========================================\n";
    return raport;
}