#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"

template <Arithmetic T>
class Rectangle : public Figure<T> {
public:
    Rectangle() = default;

    // Конструктор через центр, ширину и высоту
    Rectangle(T center_x, T center_y, T width, T height) {
        T half_w = width / 2, half_h = height / 2;
        this->points.push_back(std::make_unique<Point<T>>(center_x - half_w, center_y - half_h));
        this->points.push_back(std::make_unique<Point<T>>(center_x + half_w, center_y - half_h));
        this->points.push_back(std::make_unique<Point<T>>(center_x + half_w, center_y + half_h));
        this->points.push_back(std::make_unique<Point<T>>(center_x - half_w, center_y + half_h));
    }

    // Конструктор копирования
    Rectangle(const Rectangle& other) {
        for (const auto& point_ptr : other.points) {
            this->points.push_back(std::make_unique<Point<T>>(*point_ptr));
        }
    }

    // Конструктор перемещения
    Rectangle(Rectangle&& other) noexcept {
        this->points = std::move(other.points);
    }

    // Конструктор из вектора точек
    Rectangle(std::vector<Point<T>> &vector) {
        for (size_t i = 0; i < vector.size(); ++i) {
            this->points.push_back(std::make_unique<Point<T>>(vector[i]));
        }
    }

    // Оператор присваивания копированием
    Rectangle& operator=(const Rectangle& right_operand) {
        if (this != &right_operand) {
            this->points.clear();
            for (const auto &point_ptr : right_operand.points) {
                this->points.push_back(std::make_unique<Point<T>>(*point_ptr));
            }
        }
        return *this;
    }

    // Оператор присваивания перемещением
    Rectangle& operator=(Rectangle&& right_operand) noexcept {
        if (this != &right_operand) {
            this->points = std::move(right_operand.points);
        }
        return *this;
    }

    void read(std::istream& is) override {
        this->points.clear();
        std::cout << "Enter Rectangle (center_x center_y width height): ";
        T center_x, center_y, width, height;
        is >> center_x >> center_y >> width >> height;
        
        T half_w = width / 2, half_h = height / 2;
        this->points.push_back(std::make_unique<Point<T>>(center_x - half_w, center_y - half_h));
        this->points.push_back(std::make_unique<Point<T>>(center_x + half_w, center_y - half_h));
        this->points.push_back(std::make_unique<Point<T>>(center_x + half_w, center_y + half_h));
        this->points.push_back(std::make_unique<Point<T>>(center_x - half_w, center_y + half_h));
    }

    bool equal(const Figure<T>& other) const override {
        if (typeid(*this) != typeid(other)){
            return false;
        }
        const auto& other_rect = static_cast<const Rectangle&>(other);
        
        if (this->points.size() != other_rect.points.size()){
            return false;
        }
        for (size_t i = 0; i < this->points.size(); ++i) {
            if (!(*this->points[i] == *other_rect.points[i])){
                return false;
            }
        }
        return true;
    }

    double area() const override {
        if (this->points.size() != 4) return 0.0;
        T width = std::abs(this->points[1]->x - this->points[0]->x);
        T height = std::abs(this->points[2]->y - this->points[1]->y);
        return width * height;
    }

    std::string define_figure_type() const override {
        return "Rectangle";
    }

    size_t define_count_vertexes() const override {
        return 4;
    }
};

#endif 