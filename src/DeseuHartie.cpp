#include <iostream>
#include <string>
#include "../include/DeseuHartie.h"

DeseuHartie::DeseuHartie(const float cantitate_hartie, const CalitateHartie calit)
    : Deseu(cantitate_hartie), calitate(calit) {}

int DeseuHartie::timp_descompunere_ani() const {
    return (calitate == CalitateHartie::CARTON) ? 2 : 1;
}

float DeseuHartie::calculeaza_amprenta_carbon() const {
    float factor = 0.5f;
    if (calitate == CalitateHartie::CARTON) factor = 0.6f;
    else if (calitate == CalitateHartie::PRINT_ALB) factor = 0.9f;
    else if (calitate == CalitateHartie::MACULATURA) factor = 0.4f;

    return factor * cantitate;
}

std::string DeseuHartie::get_tip() const {
    return "Hartie";
}

void DeseuHartie::afiseaza_impl(std::ostream& os) const {
    os << " -> Tip hartie: " << calitate_hartie_to_string() << "\n";
    os << " -> Copaci salvati (estimare): " << cantitate * 0.015f << "\n";
    os << " -> Timp estimat descompunere: " << timp_descompunere_ani() << " ani.\n";
    os << " -> Amprenta de carbon generata: " << calculeaza_amprenta_carbon() << " kg CO2.";
}

std::string DeseuHartie::genereaza_raport_ecologic() const {
    std::string raport;
    raport += "=== RAPORT ECOLOGIC - DESEU HARTIE ===\n";
    raport += "Cantitate: " + std::to_string(cantitate) + " kg\n";
    raport += "Timp de descompunere: " + std::to_string(timp_descompunere_ani()) + " ani\n";
    raport += "Amprenta carbon totala: " + std::to_string(calculeaza_amprenta_carbon()) + " kg CO2\n";
    raport += "\n[Analiza Impact]\n";

    if (cantitate < 10.0f) {
        raport += "  - Impact redus asupra mediului.\n";
        raport += "  - Usor de reciclat in hartie reciclata de calitate inferioara (cartoane de oua, etc).\n";
        raport += "  - Echivalent CO2: similar cu " + std::to_string(static_cast<int>(calculeaza_amprenta_carbon() / 2.3f)) + " km parcursi cu masina.\n";
    } else if (cantitate < 50.0f) {
        raport += "  - Impact moderat, cantitate optima pentru centrele de colectare.\n";
        raport += "  - Necesita depozitare in mediu uscat pentru a preveni mucegaiul.\n";
        raport += "  - Echivalent CO2: similar cu " + std::to_string(static_cast<int>(calculeaza_amprenta_carbon() / 2.3f)) + " km parcursi cu masina.\n";
        raport += "  - Recomandare: compactare rapida pentru economisirea spatiului.\n";
    } else {
        raport += "  - Impact SEMNIFICATIV pozitiv prin salvarea masei lemnoase!\n";
        raport += "  - Necesita tocator industrial de mare capacitate.\n";
        raport += "  - Echivalent CO2: similar cu " + std::to_string(static_cast<int>(calculeaza_amprenta_carbon() / 2.3f)) + " km parcursi cu masina.\n";
        raport += "  - ATENTIE: Volum mare! Trimiteti direct la fabrica de celuloza.\n";
    }

    raport += "\n[Solutii Recomandate]\n";
    raport += "  1. Transformare in pasta de celuloza pentru ambalaje noi.\n";
    raport += "  2. Folosire ca material ecologic de umplutura pentru colete.\n";
    raport += "  3. Peletizare pentru izolare termica ecologica.\n";
    raport += "=======================================\n";
    return raport;
}

std::string DeseuHartie::calitate_hartie_to_string() const {
    switch (calitate) {
        case CalitateHartie::CARTON: return "Carton gros / Ambalaje";
        case CalitateHartie::PRINT_ALB: return "Hartie alba de birou";
        case CalitateHartie::MACULATURA: return "Maculatura mixta";
        default: return "Hartie standard";
    }
}