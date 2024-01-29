#include <iostream>
#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
    int *field;
    int sx, sy;
    Matrix(int sx, int sy) {
        this->sx = sx;
        this->sy = sy;
        field = static_cast<int*>(malloc(sizeof(int) * sx * sy));
        if (!field) return;;
        for (int y = 0; y < sy; ++y) {
            for (int x = 0; x < sx; ++x) {
                field[y * sx + x] = 0;
            }
        }
    }
    ~Matrix() {
        free(field);
    }
    Matrix() {
        field = NULL;
    }
    Matrix(const Matrix &other) {
        this->sx = other.sx;
        this->sy = other.sy;
        field = static_cast<int*>(malloc(sizeof(int) * other.sx * other.sy));
        for (int y = 0; y < sy; ++y) {
            for (int x = 0; x < sx; ++x) {
                field[y * sx + x] = other.field[y * sx + x];
            }
        }
    }
    Matrix& operator = (const Matrix &other) {
        this->sx = other.sx;
        this->sy = other.sy;
        free(field);
        field = static_cast<int*>(malloc(sizeof(int) * other.sx * other.sy));
        for (int y = 0; y < sy; ++y) {
            for (int x = 0; x < sx; ++x) {
                field[y * sx + x] = other.field[y * sx + x];
            }
        }
        return *this;
    }
    int get(int x, int y) {
        if (!field) throw std::exception();
        if (y < 0 || y > sy || x < 0 || x > sx) {
            return  -1;
        }
        return field[y * sx + x];
    }
    void set(int x, int y, int value) {
        if (!field) throw std::exception();
        field[y * sx + x] = value;
    }
    int neighbor(int x, int y, int ox, int oy) {
        if (!field) throw std::exception();

        return get(x+ox,y+oy);
    }
    int sumNeighbors(int x, int y) {
        if (!field) throw std::exception();
        int num = 0;
        for (int v = -1; v < 2; ++v) {
            for (int u = -1; u < 2; ++u) {
                if (x + u >= sx || x + u < 0 || y + v >= sy || y + v < 0 || (u == 0 && v == 0)) {
                    continue;
                }
                num += get(x+u,y+v);
            }
        }
        return num;
    }
    std::string toString() {
        std::string str = "[";
        for (int y = 0; y < sy; ++y) {
            str += "[";
            for (int x = 0; x < sx; ++x) {
                str += std::to_string(get(x,y));
                str += (x < sx - 1 ? "," : "");
            } if (y < sy - 1) {
                str += "],\n";
            } else {
                str += "]";
            }
        } str += "]\n";
        return str;
    }
};



#endif //MATRIX_H
