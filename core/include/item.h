#pragma once
#include <memory>

#include "basic.h"
#include "impact.h"
#include "item_fwd.h"
#include "unit_fwd.h"


enum class ItemType {
    Weapon,
    Clothes,
    Usable,
    Misc,
    Key,
    Potion
};

class Item : public Object {
public:
    Item(double _weight, std::string _descr = "Малопримечательная безделушка") : weight(_weight), description(_descr) {}
    virtual ItemType get_type()=0;
    double get_weight() { return weight; }
    std::string get_name() { return description; }
    DECLARE_COMMON_METHODS(Item)
protected:
    double weight;
    std::string description;
};

class Weapon : public Item {
public:
    Weapon(double _weight, Damage _damage, std::string _descr = "Оружие. Осторожно, можно пораниться.") : Item(_weight, _descr), damage(_damage) {}
    Damage get_damage() { return damage; }
    ItemType get_type() { return ItemType::Weapon; }



    DECLARE_VISIT(Weapon)
    DECLARE_COMMON_METHODS(Weapon)
protected:
    Damage damage;
};

class Clothes : public Item {
public:
    Clothes(double _weight, Defense def, std::string _descr = "Какая-то вещица. Можно нацепить на себя"): Item(_weight, _descr), defense(def) {}
    ItemType get_type() { return ItemType::Clothes; }
    Defense get_defense() { return defense; }
    DECLARE_VISIT(Clothes)
    DECLARE_COMMON_METHODS(Clothes)
protected:
    Defense defense;
};

class Usable : public Item {
public:
    Usable(double _weight, std::string descr = "Это наверняка можно как-то использовать") : Item(_weight, descr) {}
    virtual void use(UnitPtr unit)=0;
    ItemType get_type() { return ItemType::Usable; }
    DECLARE_COMMON_METHODS(Usable)
};

class Misc : public Item {
public:
    Misc(double _weight, std::string _descr = "Что-то непонятное. Возможно, пригодится.") : Item(_weight, _descr) {}
    ItemType get_type() { return ItemType::Misc; }
    DECLARE_COMMON_METHODS(Misc)
};

class Potion : public Usable {
public:
    Potion(double _weight, int _hp, std::string _descr = "странный бутылек с неизвестной жидкостью внутри") : Usable(_weight, _descr), hp(_hp) {}
    void use(UnitPtr unit); 
    ItemType get_type() { return ItemType::Potion; }
    DECLARE_COMMON_METHODS(Potion)
    DECLARE_VISIT(Potion)
private:
    int hp;
};

class Key : public Misc {
public:
    Key(double _weight, std::string descr = "тяжелый металический ключ. Навеняка им можно открыть какую-то дверь") : Misc(_weight, descr) {}
    ItemType get_type() { return ItemType::Key; }
    DECLARE_COMMON_METHODS(Key)
    DECLARE_VISIT(Key)
};

