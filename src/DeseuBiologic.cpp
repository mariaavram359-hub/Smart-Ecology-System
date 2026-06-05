//
// Created by lenovo on 21.05.2026.
//
#include <iostream>
#include "../include/DeseuBiologic.h"

DeseuBiologic::DeseuBiologic(float cantitate_bio, bool compostabil)
    : Deseu(cantitate_bio), este_compostabil(compostabil) {}

int DeseuBiologic::timp_descompunere_ani() const {
    return este_compostabil ? 1 : 3;
}

float DeseuBiologic::calculeaza_amprenta_carbon() const {
    return cantitate * 0.5f;
}

std::string DeseuBiologic::get_tip() const {
    return "Biologic";
}

void DeseuBiologic::afiseaza_impl(std::ostream& os) const {
    os << " -> Timp estimat descompunere: " << timp_descompunere_ani() << " ani.\n";
    os << " -> Amprenta de carbon generata: " << calculeaza_amprenta_carbon() << " kg CO2.";
}

std::string DeseuBiologic::genereaza_raport_ecologic() const {
    std::string raport;
    raport += "=== RAPORT ECOLOGIC - DESEU BIOLOGIC ===\n";
    raport += "Cantitate: " + std::to_string(cantitate) + " kg\n";
    raport += "Timp de descompunere: " + std::to_string(timp_descompunere_ani()) + " an\n";
    raport += "Amprenta carbon totala: " + std::to_string(calculeaza_amprenta_carbon()) + " kg CO2\n";
    raport += "\n[Analiza Impact]\n";

    if (cantitate < 20.0f) {
        raport += "  - Impact minim, deseu biodegradabil rapid.\n";
        raport += "  - Poate fi compostat direct in gospodarie.\n";
    } else if (cantitate < 100.0f) {
        raport += "  - Cantitate semnificativa, necesita compostare industriala.\n";
        raport += "  - Potential de generare biogaz: " + std::to_string(static_cast<int>(cantitate * 0.3f)) + " litri.\n";
        raport += "  - Recomandare: procesare in maxim 48 ore pentru a evita mirosurile.\n";
    } else {
        raport += "  - Cantitate CRITICA de deseuri biologice!\n";
        raport += "  - Risc de fermentare si generare gaze toxice.\n";
        raport += "  - Potential de generare biogaz: " + std::to_string(static_cast<int>(cantitate * 0.3f)) + " litri.\n";
        raport += "  - ATENTIE: Colectare de urgenta necesara in maxim 24 ore!\n";
    }

    raport += "\n[Solutii Recomandate]\n";
    raport += "  1. Compostare industriala pentru obtinere ingrasamant natural.\n";
    raport += "  2. Digestie anaeroba pentru producere biogaz.\n";
    raport += "  3. Valorificare energetica prin ardere controlata.\n";
    raport += "=========================================\n";

    if (este_compostabil) {
        raport += "Impact pozitiv. Poate fi transformat in ingrasamant natural.\n";
    }
    else {
        raport += "Impact neutru. Necesita procesare in instalatii de biogaz.\n";
    }
    return raport;
}


