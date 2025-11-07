#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"

template <Arithmetic T>
class Square : public Figure<T> {
public:
    Square() = default;

    // Конструктор через центр и сторону
    Square(T center_x, T center_y, T side) {
        T half = side / 2;
        this->points.push_back(std::make_unique<Point<T>>(center_x - half, center_y - half));
        this->points.push_back(std::make_unique<Point<T>>(center_x + half, center_y - half));
        this->points.push_back(std::make_unique<Point<T>>(center_x + half, center_y + half));
        this->points.push_back(std::make_unique<Point<T>>(center_x - half, center_y + half));
    }

    // Конструктор копирования
    Square(const Square& other) {
        for (const auto& point_ptr : other.points) {
            this->points.push_back(std::make_unique<Point<T>>(*point_ptr));
        }
    }

    // Конструктор перемещения
    Square(Square&& other) noexcept {
        this->points = std::move(other.points);
    }

    // Конструктор из вектора точек
    Square(std::vector<Point<T>> &vector) {
        for (size_t i = 0; i < vector.size(); ++i) {
            this->points.push_back(std::make_unique<Point<T>>(vector[i]));
        }
    }

    // Оператор присваивания копированием
    Square& operator=(const Square& right_operand) {
        if (this != &right_operand) {
            this->points.clear();
            for (const auto &point_ptr : right_operand.points) {
                this->points.push_back(std::make_unique<Point<T>>(*point_ptr));
            }
        }
        return *this;
    }

    // Оператор присваивания перемещением
    Square& operator=(Square&& right_operand) noexcept {
        if (this != &right_operand) {
            this->points = std::move(right_operand.points);
        }
        return *this;
    }

    void read(std::istream& is) override {
        this->points.clear();
        std::cout << "Enter Square (center_x center_y side): ";
        T center_x, center_y, side;
        is >> center_x >> center_y >> side;
        
        T half = side / 2;
        this->points.push_back(std::make_unique<Point<T>>(center_x - half, center_y - half));
        this->points.push_back(std::make_unique<Point<T>>(center_x + half, center_y - half));
        this->points.push_back(std::make_unique<Point<T>>(center_x + half, center_y + half));
        this->points.push_back(std::make_unique<Point<T>>(center_x - half, center_y + half));
    }

    bool equal(const Figure<T>& other) const override {
        if (typeid(*this) != typeid(other)){
            return false;
        }
        const auto& other_square = static_cast<const Square&>(other);
        
        if (this->points.size() != other_square.points.size()){
            return false;
        }
        for (size_t i = 0; i < this->points.size(); ++i) {
            if (!(*this->points[i] == *other_square.points[i])) {
                return false;
            }
        }
        return true;
    }
    double area() const override {
        if (this->points.size() != 4) return 0.0;
        T side = std::abs(this->points[1]->x - this->points[0]->x);
        return side * side;
    }
    std::string define_figure_type() const override {
        return "Square";
    }
    size_t define_count_vertexes() const override {
        return 4;
    }
};

#endif 