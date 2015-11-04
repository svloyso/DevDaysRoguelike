#pragma once
#include <memory>

class Action;
class Move : public Action;
class Atack : public Action;
class Pick : public Action;
class Interact : public Action;
class Destroyed : public Action;

typedef std::shared_ptr<Action> ActionPtr;
typedef std::shared_ptr<Move> MovePtr;
typedef std::shared_ptr<Atack> AtackPtr;
typedef std::shared_ptr<Pick> PickPtr;
typedef std::shared_ptr<Interact> InteractPtr;
typedef std::shared_ptr<Destroyed> DestroyedPtr;

