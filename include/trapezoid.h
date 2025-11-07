#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "figure.h"

template <Arithmetic T>
class Trapezoid : public Figure<T> {
public:
    Trapezoid() = default;

    // Конструктор через центр, основания и высоту 
    Trapezoid(T center_x, T center_y, T bottom, T top, T height) {
        T half_bottom = bottom / 2;
        T half_top = top / 2;
        T half_height = height / 2;
        
        this->points.push_back(std::make_unique<Point<T>>(center_x - half_bottom, center_y - half_height));
        this->points.push_back(std::make_unique<Point<T>>(center_x + half_bottom, center_y - half_height));
        this->points.push_back(std::make_unique<Point<T>>(center_x + half_top, center_y + half_height));
        this->points.push_back(std::make_unique<Point<T>>(center_x - half_top, center_y + half_height));
    }

    // Конструктор копирования
    Trapezoid(const Trapezoid& other) {
        for (const auto& point_ptr : other.points) {
            this->points.push_back(std::make_unique<Point<T>>(*point_ptr));
        }
    }

    // Конструктор перемещения
    Trapezoid(Trapezoid&& other) noexcept {
        this->points = std::move(other.points);
    }

    // Конструктор из вектора точек
    Trapezoid(std::vector<Point<T>> &vector) {
        for (size_t i = 0; i < vector.size(); ++i) {
            this->points.push_back(std::make_unique<Point<T>>(vector[i]));
        }
    }

    // Оператор присваивания копированием
    Trapezoid& operator=(const Trapezoid& right_operand) {
        if (this != &right_operand) {
            this->points.clear();
            for (const auto &point_ptr : right_operand.points) {
                this->points.push_back(std::make_unique<Point<T>>(*point_ptr));
            }
        }
        return *this;
    }

    // Оператор присваивания перемещением
    Trapezoid& operator=(Trapezoid&& right_operand) noexcept {
        if (this != &right_operand) {
            this->points = std::move(right_operand.points);
        }
        return *this;
    }

    void read(std::istream& is) override {
        this->points.clear();
        std::cout << "Enter Trapezoid (center_x center_y bottom top height): ";
        T center_x, center_y, bottom, top, height;
        is >> center_x >> center_y >> bottom >> top >> height;
        
        T half_bottom = bottom / 2;
        T half_top = top / 2;
        T half_height = height / 2;
        
        this->points.push_back(std::make_unique<Point<T>>(center_x - half_bottom, center_y - half_height));
        this->points.push_back(std::make_unique<Point<T>>(center_x + half_bottom, center_y - half_height));
        this->points.push_back(std::make_unique<Point<T>>(center_x + half_top, center_y + half_height));
        this->points.push_back(std::make_unique<Point<T>>(center_x - half_top, center_y + half_height));
    }

    bool equal(const Figure<T>& other) const override {
        if (typeid(*this) != typeid(other)) return false;
        const auto& other_trap = static_cast<const Trapezoid&>(other);
        
        if (this->points.size() != other_trap.points.size()) return false;
        for (size_t i = 0; i < this->points.size(); ++i) {
            if (!(*this->points[i] == *other_trap.points[i])) return false;
        }
        return true;
    }

    double area() const override {
        if (this->points.size() != 4) return 0.0;
        T bottom = std::abs(this->points[1]->x - this->points[0]->x);
        T top = std::abs(this->points[2]->x - this->points[3]->x);
        T height = std::abs(this->points[2]->y - this->points[1]->y);
        return (bottom + top) * height / 2.0;
    }

    std::string define_figure_type() const override {
        return "Trapezoid";
    }

    size_t define_count_vertexes() const override {
        return 4;
    }
};

#endif 