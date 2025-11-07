#ifndef FIGURE_H
#define FIGURE_H

#include <memory>
#include <iostream>
#include <vector>
#include <concepts>
#include <cmath>

template <class T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic T>
struct Point {
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

template <Arithmetic T>
class Figure {
    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& figure) {
        os << "--------------------------------------------------------\n";
        os << figure.define_figure_type() << ":\n";
        for (size_t i = 0; i < figure.points.size(); ++i) {
            os << "  Point " << i + 1 << ": " << *figure.points[i] << "\n";
        }
        os << "  Area: " << static_cast<double>(figure) << "\n";
        auto center = figure.center();
        os << "  Center: " << center << "\n";
        os << "--------------------------------------------------------\n";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure<T>& figure) {
        figure.read(is);
        return is;
    }

    friend bool operator==(const Figure<T>& lhs, const Figure<T>& rhs) {
        if (lhs.define_figure_type() != rhs.define_figure_type()) {
            return false;
        }
        if (lhs.points.size() != rhs.points.size()) {
            return false;
        }
        for (size_t i = 0; i < lhs.points.size(); i++) {
            if (*lhs.points[i] != *rhs.points[i]) {
                return false;
            }
        }
        return true;
    }

public:
    Point<T> center() const {
        if (points.empty()) return Point<T>();
        T sum_x = 0, sum_y = 0;
        for (const auto& point : points) {
            sum_x += point->x;
            sum_y += point->y;
        }
        return Point<T>(sum_x / points.size(), sum_y / points.size());
    }

    virtual double area() const = 0;
    
    explicit operator double() const {
        return area();
    }

    virtual void read(std::istream& is) = 0;
    virtual bool equal(const Figure<T>& other) const = 0;
    virtual std::string define_figure_type() const = 0;
    virtual size_t define_count_vertexes() const = 0;
    virtual ~Figure() = default;

protected:
    std::vector<std::unique_ptr<Point<T>>> points;
};

#endif 