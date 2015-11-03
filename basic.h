#pragma once

class Object{
    public:
        Object() : id(next_id++) {}
        int get_id() { return id; }

    private:
        int id;
        static int next_id;
};
int Object::next_id = 0;

class VisibleObject : public Object {
    //EMPTY NOW
};

