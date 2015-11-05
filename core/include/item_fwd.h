#pragma once

class Item;
class Weapon;
class Clothes;
class Usable;
class Misc;
class Potion;
class Key;

typedef std::shared_ptr<Item>       ItemPtr;
typedef std::shared_ptr<Weapon>     WeaponPtr;
typedef std::shared_ptr<Clothes>    ClothesPtr;
typedef std::shared_ptr<Usable>     UsablePtr;
typedef std::shared_ptr<Misc>       MiscPtr;
typedef std::shared_ptr<Potion>     PotionPtr;
typedef std::shared_ptr<Key>        KeyPtr;
