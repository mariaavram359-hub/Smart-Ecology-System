#include "StatieSortare.h"
#include "ContainerPlastic.h"
#include "ContainerBiodegradabile.h"
#include "ContainerElectronice.h"
#include <iostream>
#include <utility>
#include <numeric>
#include <algorithm>
#include "Logger.h"

float StatieSortare::total_reciclat = 0.0f;

StatieSortare::StatieSortare(const StatieSortare& alta_statie) {
    for (const ContainerDeseuri* container : alta_statie.flota_containere)
        this->flota_containere.push_back(container->clone());
    std::cout << "[Sistem] S-a creat o copie la indigo (Deep Copy) a flotei.\n";
}

void StatieSortare::swap(StatieSortare& alta_statie) noexcept {
    using std::swap;
    swap(this->flota_containere, alta_statie.flota_containere);
}

StatieSortare& StatieSortare::operator=(StatieSortare alta_statie) {
    this->swap(alta_statie);
    return *this;
}

StatieSortare::~StatieSortare() {
    for (ContainerDeseuri* container : flota_containere)
        delete container;
    flota_containere.clear();
}

float StatieSortare::goleste_container(ContainerDeseuri* container) {
    float colectat = container->goleste();
    total_reciclat += colectat;
    return colectat;
}

void StatieSortare::adaugaContainer(ContainerDeseuri* container) {
    flota_containere.push_back(container);
}

void StatieSortare::mentenanta_rutina() const {
    std::cout << "\n--- INCEPERE RUTINA MENTENANTA ---\n";
    for (ContainerDeseuri* container : flota_containere) {
        if (container->este_in_mentenanta()) {
            std::cout << "[Mentenanta] Se repara containerul...\n";
            container->scoate_din_mentenanta();
        } else {
            container->afiseaza();
            if (dynamic_cast<ContainerBiodegradabile*>(container) != nullptr)
                std::cout << "  -> [Actiune]: Se igienizeaza containerul biodegradabil!\n";
            else if (dynamic_cast<ContainerElectronice*>(container) != nullptr)
                std::cout << "  -> [Actiune]: Se calibreaza senzorul de scurgeri toxice!\n";
        }
    }
    std::cout << "--- RUTINA FINALIZATA ---\n";
}

void StatieSortare::executa_sortare(const StrategieSortare& strategie) {
    // Delegăm algoritmul de sortare către obiectul strategie!
    strategie.sorteaza(this->flota_containere);
}

void StatieSortare::colecteaza_tot_gunoiul() {
    std::cout << "\n--- TRIMITERE MASINA DE GUNOI ---\n";
    float cantitate_tura_curenta = 0.0f;
    for (ContainerDeseuri* container : flota_containere)
        cantitate_tura_curenta += goleste_container(container);
    std::cout << "[Sistem] Masina a colectat " << cantitate_tura_curenta << " kg in aceasta tura.\n";
    std::cout << "--- COLECTARE FINALIZATA ---\n\n";
    jurnal_evenimente.adauga("Colectare totala initiata pentru toata flota.");
}

void StatieSortare::colectare_automata() const {
    bool s_a_colectat_ceva = false;

    for (auto* container : flota_containere) {

        if (container->get_grad_umplere() >= container->get_prag_colectare() && container->get_grad_umplere() > 0) {

            Logger::get_instance().info("[AUTO-COLECTARE] Masina de gunoi a golit containerul ID: " +
                                        std::to_string(container->get_id()) +
                                        " (Avea " + std::to_string(container->get_grad_umplere()) + " kg).");


            container->goleste();

            s_a_colectat_ceva = true;
        }
    }

    if (s_a_colectat_ceva) {
        Logger::get_instance().success("Traseul de colectare automata a fost finalizat cu succes!\n");
    }
}

ContainerDeseuri* StatieSortare::operator[](size_t index) const {
    if (index >= flota_containere.size())
        throw std::out_of_range("Eroare de indexare: Nu exista niciun container la pozitia " + std::to_string(index));
    return flota_containere[index];
}

void StatieSortare::afiseaza_rezumat() const {
    std::cout << "\n--- REZUMAT FLOTA ---\n";
    for (const ContainerDeseuri* container : flota_containere)
        std::cout << *container << "\n";
    std::cout << "---------------------\n";
}

ContainerDeseuri* StatieSortare::cauta_dupa_id(int id) const {
    auto rezultat = std::ranges::find_if(flota_containere,
        [id](const ContainerDeseuri* container) {
            return container->get_id() == id;
        });
    if (rezultat == flota_containere.end())
        throw std::out_of_range("Nu exista niciun container cu ID-ul " + std::to_string(id));
    return *rezultat;
}

int StatieSortare::numar_containere_critice() const {
    return static_cast<int>(std::ranges::count_if(flota_containere,
        [](const ContainerDeseuri* container) {
            if (container->get_capacitate_maxima() <= 0.0f) return false;
            float procent = (container->get_grad_umplere() / container->get_capacitate_maxima()) * 100.0f;
            return procent > 80.0f;
        }));
}

float StatieSortare::total_kg_in_flota() const {
    return std::accumulate(flota_containere.begin(), flota_containere.end(), 0.0f,
        [](float suma, const ContainerDeseuri* container) {
            return suma + container->get_grad_umplere();
        });
}

bool StatieSortare::exista_containere_in_mentenanta() const {
    return std::ranges::any_of(flota_containere,
        [](const ContainerDeseuri* container) {
            return container->este_in_mentenanta();
        });
}

float StatieSortare::calculeaza_scor_sustenabilitate() const {
    if (flota_containere.empty()) return 100.0f;

    float scor = 100.0f;

    scor -= numar_containere_critice() * 15.0f;

    float penalizare_carbon = total_reciclat / 10.0f;
    if (penalizare_carbon > 30.0f)
        penalizare_carbon = 30.0f;
    scor -= penalizare_carbon;

    float capacitate_totala = std::accumulate(flota_containere.begin(), flota_containere.end(), 0.0f,
        [](float suma, const ContainerDeseuri* c) {
            return suma + c->get_capacitate_maxima();
        });

    if (capacitate_totala > 0) {
        float rata_utilizare = (total_kg_in_flota() / capacitate_totala) * 100.0f;
        if (rata_utilizare < 50.0f)
            scor += 10.0f;
    }

    if (scor < 0.0f) scor = 0.0f;
    if (scor > 100.0f) scor = 100.0f;

    return scor;
}

std::string StatieSortare::interpreteaza_scor(float scor) {
    if (scor >= 90.0f) return "EXCELENT  - Orasul este un model de sustenabilitate!";
    if (scor >= 75.0f) return "BUN       - Sistemul functioneaza eficient, mici imbunatatiri posibile.";
    if (scor >= 55.0f) return "MEDIU     - Orasul poate face mai mult. Verificati containerele critice!";
    if (scor >= 35.0f) return "SLAB      - Situatie ingrijoratoare. Colectare urgenta necesara!";
    return                    "CRITIC    - Orasul este in criza ecologica! Interventie imediata!";
}

// void StatieSortare::afiseaza_statistici() {
//     std::cout << "====================================\n";
//     std::cout << "STATISTICI GLOBALE CARTIER:\n";
//     std::cout << "Total deseuri procesate: " << total_reciclat << " kg\n";
//     std::cout << "====================================\n";
// }

void StatieSortare::afiseaza_raport_complet() const {
    std::cout << "\n========================================\n";
    std::cout << "         RAPORT COMPLET STATIE          \n";
    std::cout << "========================================\n";
    std::cout << "Numar total containere: " << flota_containere.size() << "\n";
    std::cout << "Total kg in flota acum: " << total_kg_in_flota() << " kg\n";
    std::cout << "Total kg procesate istoric: " << total_reciclat << " kg\n";
    std::cout << "Containere critice (>80%): " << numar_containere_critice() << "\n";

    if (exista_containere_in_mentenanta())
        std::cout << "ATENTIE: Exista containere in mentenanta!\n";
    else
        std::cout << "Toate containerele sunt operationale.\n";

    float scor = calculeaza_scor_sustenabilitate();
    std::cout << "Scor sustenabilitate: " << scor << " / 100\n";
    std::cout << "Status: " << StatieSortare::interpreteaza_scor(scor) << "\n";

    std::cout << "\n--- Detalii containere ---\n";
    for (const ContainerDeseuri* container : flota_containere)
        std::cout << *container << "\n";
    jurnal_evenimente.afiseaza("Jurnal Statie Sortare");
    std::cout << "========================================\n";
}