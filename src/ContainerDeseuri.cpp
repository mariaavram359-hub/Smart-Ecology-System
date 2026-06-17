#include "ContainerDeseuri.h"
#include "Exceptii.h"
#include <iostream>
#include <utility>

ContainerDeseuri::ContainerDeseuri(const int id_container, std::string locatie_container, float capacitate_maxima_container)
    :id(id_container), locatie(std::move(locatie_container)),
    capacitate_maxima(capacitate_maxima_container), grad_umplere(0.0f) {
}

void ContainerDeseuri::afiseaza() const {
    std::cout << "\n";
    std::cout << "SMART CONTAINER\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Locatie: " << locatie << "\n";
    std::cout << "Grad de umplere: " << grad_umplere << " / " << capacitate_maxima << " kg\n";
    istoric_cantitati.afiseaza("Istoric greutati adaugate");

    afiseaza_impl();

    std::cout << "\n";
}

void ContainerDeseuri::adauga_deseuri(const Deseu& deseu_aruncat) {
    float cantitate_primita = deseu_aruncat.get_cantitate();
    std::string tip_primit = deseu_aruncat.get_tip();

    if (in_mentenanta) {
        throw EroareMentenanta("Containerul " + std::to_string(id) + " este in mentenanta si nu accepta deseuri!");
    }

    if (tip_primit != tip_acceptat) {
        throw EroareTipDeseu("Trapa blocata! Nu puteti arunca [" + tip_primit + "] intr-un container pentru [" + tip_acceptat + "].");
    }

    float spatiu_ocupat = calculeaza_spatiu_ocupat(deseu_aruncat);

    if (grad_umplere + spatiu_ocupat > capacitate_maxima) {
        throw EroareSuprasolicitare<int>("Containerul a depasit capacitatea maxima!", this->id);
    }

    grad_umplere += spatiu_ocupat;
    istoric_cantitati.adauga(deseu_aruncat.get_cantitate());
    std::cout << "[Sistem Trapa] Au fost adaugate " << cantitate_primita << " kg de " << tip_primit << ".\n";

    if (necesita_colectare()) {
        std::cout << "\n[ATENTIE] Containerul " << id << " a depasit pragul de " << prag_colectare << "%!\n";
        float colectat = goleste();
        std::cout << "[AUTO] Masina de gunoi a fost trimisa automat! Colectat " << colectat << " kg.\n";
    }
}

float ContainerDeseuri::goleste() {
    float cantitate_colectata = grad_umplere;
    grad_umplere = 0.0f;

    numar_colectari++;
    if (numar_colectari >= prag_mentenanta) {
        in_mentenanta = true;
        std::cout << "[SISTEM] Containerul " << id << " din " << locatie
                  << " a intrat in mentenanta dupa " << numar_colectari << " colectari!\n";
    }

    return cantitate_colectata;
}
float ContainerDeseuri::get_grad_umplere() const {
    return grad_umplere;
}

ContainerDeseuri& ContainerDeseuri::operator+=(const Deseu& deseu_aruncat) {
    this->adauga_deseuri(deseu_aruncat);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const ContainerDeseuri& container) {
    os << "[Rezumat Container] ID: " << container.id
       << " | Tip: " << container.tip_acceptat
       << " | Umplere: " << container.grad_umplere << "/" << container.capacitate_maxima << " kg";
    return os;
}

float ContainerDeseuri::get_capacitate_maxima() const {
    return capacitate_maxima;
}

void ContainerDeseuri::set_prag_colectare(float prag) {
    if (prag > 0.0f && prag <= 100.0f)
        prag_colectare = prag;
}

bool ContainerDeseuri::necesita_colectare() const {
    if (capacitate_maxima <= 0.0f) return false;
    float procent = (grad_umplere / capacitate_maxima) * 100.0f;
    return procent >= prag_colectare;


}

bool ContainerDeseuri::este_in_mentenanta() const {
    return in_mentenanta;
}

void ContainerDeseuri::scoate_din_mentenanta() {
    in_mentenanta = false;
    numar_colectari = 0;
    std::cout << "[Mentenanta] Containerul " << id << " a fost reparat si este din nou operational.\n";
}

int ContainerDeseuri::get_id() const {
    return id;
}

float ContainerDeseuri::calculeaza_spatiu_ocupat(const Deseu& deseu) const {
    return deseu.get_cantitate();
}