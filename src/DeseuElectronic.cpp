//
// Created by lenovo on 21.05.2026.
//
#include <iostream>
#include "DeseuElectronic.h"

DeseuElectronic::DeseuElectronic(float cantitate_electric, bool are_baterie)
    : Deseu(cantitate_electric), contine_baterie(are_baterie) {}

int DeseuElectronic::timp_descompunere_ani() const {
    return 1000;
}

std::string DeseuElectronic::get_tip() const {
    return "Electronice";
}


float DeseuElectronic::calculeaza_amprenta_carbon() const {
    float amprenta_baza = cantitate * 15.5f;
    if (contine_baterie) {
        amprenta_baza += (cantitate * 50.0f); // Bateriile de litiu sunt extrem de poluante
    }
    return amprenta_baza;
}
void DeseuElectronic::afiseaza_impl(std::ostream& os) const {
    os << " -> Timp estimat descompunere: " << timp_descompunere_ani() << " ani.\n";
    os << " -> Amprenta de carbon generata: " << calculeaza_amprenta_carbon() << " kg CO2.";
}

std::string DeseuElectronic::genereaza_raport_ecologic() const {
    std::string raport;
    raport += "=== RAPORT ECOLOGIC - DESEU ELECTRONIC ===\n";
    raport += "Cantitate: " + std::to_string(cantitate) + " kg\n";
    raport += "Timp de descompunere: " + std::to_string(timp_descompunere_ani()) + " ani\n";
    raport += "Amprenta carbon totala: " + std::to_string(calculeaza_amprenta_carbon()) + " kg CO2\n";
    raport += "\n[Analiza Impact]\n";
    raport += "  - Deseurile electronice contin metale grele (plumb, mercur, cadmiu).\n";

    if (cantitate < 5.0f) {
        raport += "  - Cantitate mica, dar PERICULOASA daca nu e gestionata corect.\n";
        raport += "  - Poate contamina " + std::to_string(static_cast<int>(cantitate * 1000)) + " litri de apa subterana.\n";
    } else if (cantitate < 25.0f) {
        raport += "  - Impact semnificativ! Metale pretioase recuperabile: ~" + std::to_string(static_cast<int>(cantitate * 0.02f * 1000)) + " grame aur.\n";
        raport += "  - Poate contamina " + std::to_string(static_cast<int>(cantitate * 1000)) + " litri de apa subterana.\n";
        raport += "  - Recomandare: trimitere urgenta la centrul de dezmembrare autorizat.\n";
    } else {
        raport += "  - Cantitate CRITICA de deseuri electronice!\n";
        raport += "  - Metale pretioase recuperabile: ~" + std::to_string(static_cast<int>(cantitate * 0.02f * 1000)) + " grame aur.\n";
        raport += "  - Risc MAJOR de contaminare: " + std::to_string(static_cast<int>(cantitate * 1000)) + " litri de apa subterana in pericol.\n";
        raport += "  - ATENTIE: Interventie imediata a autoritatilor de mediu necesara!\n";
    }

    raport += "\n[Solutii Recomandate]\n";
    raport += "  1. Dezmembrare autorizata pentru recuperare metale pretioase.\n";
    raport += "  2. Neutralizare substante toxice in instalatii specializate.\n";
    raport += "  3. Reciclare componente reutilizabile (baterii, circuite).\n";
    raport += "  4. Certificat de distrugere date pentru dispozitive cu stocare.\n";
    raport += "===========================================\n";

    if (contine_baterie) {
        raport += "ATENTIE: Risc de scurgeri toxice din baterie!\n";
    } else {
        raport += "Poate fi reciclat pentru metale rare.\n";
    }
    return raport;
}