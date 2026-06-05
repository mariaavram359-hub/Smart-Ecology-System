//
// Created by lenovo on 21.05.2026.
//

#ifndef OOP_DESEUBIOLOGIC_H
#define OOP_DESEUBIOLOGIC_H

#pragma once
#include "Deseu.h"

class DeseuBiologic : public Deseu {
private:
    bool este_compostabil;
public:

    explicit DeseuBiologic(float cantitate_bio, bool compostabil);

    [[nodiscard]] int timp_descompunere_ani() const override;
    [[nodiscard]] float calculeaza_amprenta_carbon() const override;

    [[nodiscard]] std::string get_tip() const override;

    [[nodiscard]] std::string genereaza_raport_ecologic() const override;

protected:
    void afiseaza_impl(std::ostream& os) const override;
};
#endif //OOP_DESEUBIOLOGIC_H