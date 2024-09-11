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

    Vector_3<T> operator+(Vector_3<T> v) { return Vector_3<T>(_x + v._x, _y + v._y, _z + v._z) }
    Vector_3<T> operator-(Vector_3<T> v) { return Vector_3<T>(_x - v._x, _y - v._y, _z - v._z) }
    Vector_3<T> operator*(Vector_3<T> v) { return Vector_3<T>(_x * v._x, _y * v._y, _z * v._z) }
    Vector_3<T> operator/(Vector_3<T> v) { return Vector_3<T>(_x / v._x, _y / v._y, _z / v._z) }

    void operator+=(Vector_3<T> v) { _x = _x + v._x; _y = _y + v._y; _z = _z + v._z }
    void operator-=(Vector_3<T> v) { _x = _x - v._x; _y = _y - v._y; _z = _z - v._z }
    void operator*=(Vector_3<T> v) { _x = _x * v._x; _y = _y * v._y; _z = _z * v._z }
    void operator-=(Vector_3<T> v) { _x = _x / v._x; _y = _y / v._y; _z = _z / v._z }

};

class Point_3 {
private:

    GLfloat _cordinats[9];

    Vector_3<float> _point[3];

    void _Update() {

        for (int i{ 0 }; i < 3; i++) {

            _cordinats[i * 3] = _point[i]._x;
            _cordinats[1 + i * 3] = _point[i]._y;
            _cordinats[2 + i * 3] = _point[i]._z;

        }

    }

public:

    Point_3() = default;

    Point_3(Vector_3<float> v0, Vector_3<float> v1, Vector_3<float> v2) {

        _point[0] = v0; _point[1] = v1; _point[2] = v2;

        _Update();

    };

    Vector_3<float> get_Point(int index) const { return _point[index]; }
    void set_Point(int index, Vector_3<float> v) { _point[index] = v; _Update(); }
    void set_Points(Vector_3<float> v0, Vector_3<float> v1, Vector_3<float> v2) {

        _point[0] = v0; _point[1] = v1; _point[2] = v2;

        _Update();

    }

    void operator=(Point_3 p) {

        _point[0] = p.get_Point(0); _point[1] = p.get_Point(1); _point[2] = p.get_Point(2);

        _Update();

    }

    bool operator==(Point_3 p) { if (_point[0] == p.get_Point(0) && _point[1] == p.get_Point(1) && _point[2] == p.get_Point(2)) return true; else return false; }

    Point_3 operator+(Point_3 p) { return Point_3(_point[0] + p.get_Point(0), _point[1] + p.get_Point(1), _point[2] + p.get_Point(2)); }
    Point_3 operator-(Point_3 p) { return Point_3(_point[0] - p.get_Point(0), _point[1] - p.get_Point(1), _point[2] - p.get_Point(2)); }
    Point_3 operator*(Point_3 p) { return Point_3(_point[0] * p.get_Point(0), _point[1] * p.get_Point(1), _point[2] * p.get_Point(2)); }
    Point_3 operator/(Point_3 p) { return Point_3(_point[0] / p.get_Point(0), _point[1] / p.get_Point(1), _point[2] / p.get_Point(2)); }

    void operator+=(Point_3 p) {

        _point[0] = _point[0] + p.get_Point(0); _point[1] = _point[1] + p.get_Point(1); _point[2] = _point[2] + p.get_Point(2);

        _Update();

    }
    void operator-=(Point_3 p) {

        _point[0] = _point[0] - p.get_Point(0); _point[1] = _point[1] - p.get_Point(1); _point[2] = _point[2] - p.get_Point(2);

        _Update();

    }
    void operator+=(Point_3 p) {

        _point[0] = _point[0] * p.get_Point(0); _point[1] = _point[1] * p.get_Point(1); _point[2] = _point[2] * p.get_Point(2);

        _Update();

    }
    void operator+=(Point_3 p) {

        _point[0] = _point[0] / p.get_Point(0); _point[1] = _point[1] / p.get_Point(1); _point[2] = _point[2] / p.get_Point(2);

        _Update();

    }

};