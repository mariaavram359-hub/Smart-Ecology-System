//
// Created by lenovo on 21.05.2026.
//
#include <iostream>
#include <string>
#include "DeseuPlastic.h"

DeseuPlastic::DeseuPlastic(const float cantitate_plastic, const TipPlastic tip)
    : Deseu(cantitate_plastic), tip_plastic(tip) {}

int DeseuPlastic::timp_descompunere_ani() const {
    return 500;
}

float DeseuPlastic::calculeaza_amprenta_carbon() const {
    return 6.0f * cantitate;
}

std::string DeseuPlastic::get_tip() const {
    return "Plastic";
}

void DeseuPlastic::afiseaza_impl(std::ostream& os) const {
    os << " -> Tip plastic: " << tip_plastic_to_string() << "\n";
    os << " -> Poate fi reciclat direct: " << (este_reciclabil() ? "DA" : "NU") << "\n";
    os << " -> Timp estimat descompunere: " << timp_descompunere_ani() << " ani.\n";
    os << " -> Amprenta de carbon generata: " << calculeaza_amprenta_carbon() << " kg CO2.";
}
std::string DeseuPlastic::genereaza_raport_ecologic() const {
    std::string raport;
    raport += "=== RAPORT ECOLOGIC - DESEU PLASTIC ===\n";
    raport += "Cantitate: " + std::to_string(cantitate) + " kg\n";
    raport += "Timp de descompunere: " + std::to_string(timp_descompunere_ani()) + " ani\n";
    raport += "Amprenta carbon totala: " + std::to_string(calculeaza_amprenta_carbon()) + " kg CO2\n";
    raport += "\n[Analiza Impact]\n";

    if (cantitate < 10.0f) {
        raport += "  - Impact redus asupra mediului.\n";
        raport += "  - Poate fi reciclat intr-un singur ciclu industrial.\n";
        raport += "  - Echivalent CO2: similar cu " + std::to_string(static_cast<int>(calculeaza_amprenta_carbon() / 2.3f)) + " km parcursi cu masina.\n";
    } else if (cantitate < 50.0f) {
        raport += "  - Impact moderat asupra mediului.\n";
        raport += "  - Necesita sortare prealabila inainte de reciclare.\n";
        raport += "  - Echivalent CO2: similar cu " + std::to_string(static_cast<int>(calculeaza_amprenta_carbon() / 2.3f)) + " km parcursi cu masina.\n";
        raport += "  - Recomandare: transport prioritar catre centrul de reciclare.\n";
    } else {
        raport += "  - Impact RIDICAT asupra mediului!\n";
        raport += "  - Necesita procesare industriala speciala.\n";
        raport += "  - Echivalent CO2: similar cu " + std::to_string(static_cast<int>(calculeaza_amprenta_carbon() / 2.3f)) + " km parcursi cu masina.\n";
        raport += "  - ATENTIE: Cantitate critica! Se recomanda colectare de urgenta.\n";
    }

    raport += "\n[Solutii Recomandate]\n";
    raport += "  1. Trimitere la fabrica de reciclare PET/HDPE.\n";
    raport += "  2. Transformare in granule plastice reutilizabile.\n";
    raport += "  3. Reducere volum prin compactare (economie 60% spatiu transport).\n";
    raport += "=======================================\n";
    return raport;
}

bool DeseuPlastic::este_reciclabil() const {
    return (tip_plastic == TipPlastic::PET ||
            tip_plastic == TipPlastic::HDPE ||
            tip_plastic == TipPlastic::LDPE ||
            tip_plastic == TipPlastic::PP);
}

std::string DeseuPlastic::tip_plastic_to_string() const {
    switch (tip_plastic) {
        case TipPlastic::PET: return "PET";
        case TipPlastic::HDPE: return "HDPE";
        case TipPlastic::PVC: return "PVC";
        case TipPlastic::LDPE: return "LDPE";
        case TipPlastic::PP: return "PP";
        case TipPlastic::PS: return "PS";
        default: return "Altele";
    }
}