#ifndef OOP_STATIESORTARE_H
#define OOP_STATIESORTARE_H

#pragma once
#include <vector>
#include <string>
#include "ContainerDeseuri.h"
#include "Istoric.h"
#include "StrategieSortare.h"

class StatieSortare {
private:
    std::vector<ContainerDeseuri*> flota_containere;
    static float total_reciclat;

    static float goleste_container(ContainerDeseuri* container) ;
    Istoric<std::string> jurnal_evenimente;

public:
    StatieSortare() = default;
    ~StatieSortare();
    StatieSortare(const StatieSortare& alta_statie);
    StatieSortare& operator=(StatieSortare alta_statie);

    void swap(StatieSortare& alta_statie) noexcept;

    ContainerDeseuri* operator[](size_t index) const;

    void adaugaContainer(ContainerDeseuri* container);
    void mentenanta_rutina() const;
    void afiseaza_rezumat() const;
    void colecteaza_tot_gunoiul();
    void colectare_automata() const;
    void afiseaza_raport_complet() const;
    void executa_sortare(const StrategieSortare& strategie);

    [[nodiscard]] ContainerDeseuri* cauta_dupa_id(int id) const;
    [[nodiscard]] int numar_containere_critice() const;
    [[nodiscard]] float total_kg_in_flota() const;
    [[nodiscard]] bool exista_containere_in_mentenanta() const;
    [[nodiscard]] float calculeaza_scor_sustenabilitate() const;

    static void afiseaza_statistici();
    static std::string interpreteaza_scor(float scor);
};

#endif //OOP_STATIESORTARE_H