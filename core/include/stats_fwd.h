#pragma once

class Stats;
class ItemStats;
class WeaponStats;
class ClothesStats;
class UsableStats;
class MiscStats;
class ActableStats;
class UnitStats;
class MonsterStats;
class HeroStats;

typedef std::shared_ptr<Stats>          StatsPtr;
typedef std::shared_ptr<ItemStats>      ItemStatsPtr;
typedef std::shared_ptr<WeaponStats>    WeaponStatsPtr;
typedef std::shared_ptr<ClothesStats>   ClothesStatsPtr;
typedef std::shared_ptr<UsableStats>    UsableStatsPtr;
typedef std::shared_ptr<MiscStats>      MiscStatsPtr;
typedef std::shared_ptr<ActableStats>   ActableStatsPtr;
typedef std::shared_ptr<UnitStats>      UnitStatsPtr;
typedef std::shared_ptr<MonsterStats>   MonsterStatsPtr;
typedef std::shared_ptr<HeroStats>      HeroStatsPtr;

