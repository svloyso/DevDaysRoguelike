#pragma once
#include <memory>

class Action;
class Move;
class Atack;
class Pick;
class Interact;
class Die;

typedef std::shared_ptr<Action> ActionPtr;
typedef std::shared_ptr<Move> MovePtr;
typedef std::shared_ptr<Atack> AtackPtr;
typedef std::shared_ptr<Pick> PickPtr;
typedef std::shared_ptr<Interact> InteractPtr;
typedef std::shared_ptr<Die> DiePtr;

