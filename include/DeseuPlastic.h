//
// Created by lenovo on 21.05.2026.
//

#ifndef OOP_DESEUPLASTIC_H
#define OOP_DESEUPLASTIC_H

#include "Deseu.h"

enum class TipPlastic {
    PET = 1,
    HDPE = 2,
    PVC = 3,
    LDPE = 4,
    PP = 5,
    PS = 6,
    ALTELE = 7
};

class DeseuPlastic : public Deseu {
private:
    TipPlastic tip_plastic;
public:
    explicit DeseuPlastic(float cantitate_plastic, TipPlastic tip);

    [[nodiscard]] bool este_reciclabil() const;

    [[nodiscard]] int timp_descompunere_ani() const override;
    [[nodiscard]] float calculeaza_amprenta_carbon() const override;

    [[nodiscard]] std::string get_tip() const override;
    [[nodiscard]] std::string genereaza_raport_ecologic() const override;

protected:
    void afiseaza_impl(std::ostream& os) const override;
    std::string tip_plastic_to_string() const;
};
#endif //OOP_DESEUPLASTIC_H