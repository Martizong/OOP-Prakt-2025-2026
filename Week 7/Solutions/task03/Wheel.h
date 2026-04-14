#pragma once

enum class Material { Steel, Aluminium, Carbon, Magnesium };

class Wheel {
private:
    int radius;
    Material material;

public:
    Wheel();
    Wheel(int r, Material m);

    void setRadius(int r);
    void setMaterial(Material m);

    int getRadius() const;
    Material getMaterial() const;

    void print() const;
};
