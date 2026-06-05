#ifndef OOP_DESEUSTICLA_H
#define OOP_DESEUSTICLA_H

#pragma once
#include "Deseu.h"
#include <string>

enum class CuloareSticla {
    TRANSPARENTA = 1,
    VERDE = 2,
    MARO = 3,
    MIXTA = 4
};

class DeseuSticla : public Deseu {
private:
    CuloareSticla culoare;
    bool este_sparta;
public:
    explicit DeseuSticla(float cantitate_sticla, CuloareSticla cul, bool sparta);

    [[nodiscard]] int timp_descompunere_ani() const override;
    [[nodiscard]] std::string get_tip() const override;
    [[nodiscard]] float calculeaza_amprenta_carbon() const override;

    [[nodiscard]] std::string genereaza_raport_ecologic() const override;
    void afiseaza_impl(std::ostream &os) const override;

    [[nodiscard]] bool get_este_sparta() const;
    [[nodiscard]] std::string culoare_to_string() const;
};

#endif //OOP_DESEUSTICLA_H