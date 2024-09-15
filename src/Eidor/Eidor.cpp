#include <glad/glad.h>
#include <GLFW/glfw3.h>


template <class T>
class Vector_3 {
public:

    T _x = 0;
    T _y = 0;
    T _z = 0;

    Vector_3() = default;

    Vector_3(T x, T y, T z) : _x(x), _y(y), _z(z) {}

    void operator=(Vector_3<T> v) { _x = v._x; _y = v._y; _z = v._z; }

    bool operator==(Vector_3<T> v) { if (_x == v._x && _y == v._y && _z == v._z) return true; else return false; }

    Vector_3<T> operator+(Vector_3<T> v) { return Vector_3<T>(_x + v._x, _y + v._y, _z + v._z); }
    Vector_3<T> operator-(Vector_3<T> v) { return Vector_3<T>(_x - v._x, _y - v._y, _z - v._z); }
    Vector_3<T> operator*(Vector_3<T> v) { return Vector_3<T>(_x * v._x, _y * v._y, _z * v._z); }
    Vector_3<T> operator/(Vector_3<T> v) { return Vector_3<T>(_x / v._x, _y / v._y, _z / v._z); }

    void operator+=(Vector_3<T> v) { _x = _x + v._x; _y = _y + v._y; _z = _z + v._z; }
    void operator-=(Vector_3<T> v) { _x = _x - v._x; _y = _y - v._y; _z = _z - v._z; }
    void operator*=(Vector_3<T> v) { _x = _x * v._x; _y = _y * v._y; _z = _z * v._z; }
    void operator/=(Vector_3<T> v) { _x = _x / v._x; _y = _y / v._y; _z = _z / v._z; }

};

class Primitive {
private:

    Vector_3<float> _point[3];

public:

    Primitive() = default;

    Primitive(Vector_3<float> v0, Vector_3<float> v1, Vector_3<float> v2) {

        _point[0] = v0; _point[1] = v1; _point[2] = v2;

    };

    Vector_3<float>& get_Point(int index) { return _point[index]; }
    void set_Point(int index, Vector_3<float> v) { _point[index] = v; }

    void operator=(Primitive p) {

        _point[0] = p.get_Point(0); _point[1] = p.get_Point(1); _point[2] = p.get_Point(2);

    }

    bool operator==(Primitive p) { if (_point[0] == p.get_Point(0) && _point[1] == p.get_Point(1) && _point[2] == p.get_Point(2)) return true; else return false; }

    Primitive operator+(Primitive p) { return Primitive(_point[0] + p.get_Point(0), _point[1] + p.get_Point(1), _point[2] + p.get_Point(2)); }
    Primitive operator-(Primitive p) { return Primitive(_point[0] - p.get_Point(0), _point[1] - p.get_Point(1), _point[2] - p.get_Point(2)); }
    Primitive operator*(Primitive p) { return Primitive(_point[0] * p.get_Point(0), _point[1] * p.get_Point(1), _point[2] * p.get_Point(2)); }
    Primitive operator/(Primitive p) { return Primitive(_point[0] / p.get_Point(0), _point[1] / p.get_Point(1), _point[2] / p.get_Point(2)); }

    void operator+=(Primitive p) {

        _point[0] = _point[0] + p.get_Point(0); _point[1] = _point[1] + p.get_Point(1); _point[2] = _point[2] + p.get_Point(2);

    }
    void operator-=(Primitive p) {

        _point[0] = _point[0] - p.get_Point(0); _point[1] = _point[1] - p.get_Point(1); _point[2] = _point[2] - p.get_Point(2);

    }
    void operator*=(Primitive p) {

        _point[0] = _point[0] * p.get_Point(0); _point[1] = _point[1] * p.get_Point(1); _point[2] = _point[2] * p.get_Point(2);

    }
    void operator/=(Primitive p) {

        _point[0] = _point[0] / p.get_Point(0); _point[1] = _point[1] / p.get_Point(1); _point[2] = _point[2] / p.get_Point(2);

    }

};