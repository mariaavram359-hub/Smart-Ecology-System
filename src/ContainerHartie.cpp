#include "ContainerHartie.h"
#include <iostream>

ContainerHartie::ContainerHartie(int id, const std::string& locatie, float capacitate_maxima)
    : ContainerDeseuri(id, locatie, capacitate_maxima) {
    this->tip_acceptat = "Hartie";
}

void ContainerHartie::compacteaza_carton() {
    if (grad_umplere > 10.0f) {
        grad_umplere *= 0.90f; 
    }
}


ContainerHartie* ContainerHartie::clone() const {
    return new ContainerHartie(*this);
}

void ContainerHartie::afiseaza_impl() const {
    std::cout << "Container Hartie [ID: " << id
       << " | Locatie: " << locatie
       << " | Umplere: " << grad_umplere << "/" << capacitate_maxima << " kg]";
}