#pragma once
#include "unit_fwd.h"

struct Damage {
    Damage( double cut   = 0, 
            double chop  = 0, 
            double pick  = 0, 
            double crush = 0, 
            double mag   = 0) 
        : cutting(cut)
        , chopping(chop)
        , picking(pick)
        , crushing(crush)
        , magic(mag) {}
    double cutting;
    double chopping;
    double picking;
    double crushing;
    double magic;
};

struct Defense {
    Defense(double cut   = 0, 
            double chop  = 0, 
            double pick  = 0, 
            double crush = 0, 
            double mag = 0) 
        : cutting(cut)
        , chopping(chop)
        , picking(pick)
        , crushing(crush)
        , magic(mag) {}
    double cutting  = 0;
    double chopping = 0;
    double picking  = 0;
    double crushing = 0;
    double magic    = 0;
};

enum class BodyPart {
    Head,
    Body,
    Legs
};

struct Impact {
    Impact(BodyPart bp, UnitStats st, Damage dm) : body_part(bp), stats(st), damage(dm) {}
    BodyPart body_part;
    UnitStats stats;
    Damage damage;
};

struct Avoidance {
    Avoidance(UnitStats st, Defense hd, Defense bd, Defense ld) : stats(st), head_def(hd), body_def(bd), legs_def(ld) {}
    UnitStats stats;
    Defense head_def;
    Defense body_def;
    Defense legs_def;
    Defense get_def(BodyPart bp) {
        switch(bp) {
            case BodyPart::Head:
                return head_def;
            case BodyPart::Body:
                return body_def;
            case BodyPart::Legs:
                return legs_def;
            default:
                return body_def;
        }
    }
};

