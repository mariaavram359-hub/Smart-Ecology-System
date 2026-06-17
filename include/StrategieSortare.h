#ifndef OOP_STRATEGIESORTARE_H
#define OOP_STRATEGIESORTARE_H

#pragma once
#include <vector>
#include <algorithm>
#include "ContainerDeseuri.h"

class StrategieSortare {
public:
    virtual void sorteaza(std::vector<ContainerDeseuri*>& containere) const = 0;
    virtual ~StrategieSortare() = default;
};

class SortareDupaUmplere : public StrategieSortare {
public:
    void sorteaza(std::vector<ContainerDeseuri*>& containere) const override {
        std::sort(containere.begin(), containere.end(), [](ContainerDeseuri* a, ContainerDeseuri* b) {
            return a->get_grad_umplere() > b->get_grad_umplere();
        });
    }
};

class SortareDupaID : public StrategieSortare {
public:
    void sorteaza(std::vector<ContainerDeseuri*>& containere) const override {
        std::sort(containere.begin(), containere.end(), [](ContainerDeseuri* a, ContainerDeseuri* b) {
            return a->get_id() < b->get_id();
        });
    }
};

#endif //OOP_STRATEGIESORTARE_H