#include <iostream>
#include "./include/figure.h"
#include "./include/square.h"
#include "./include/rectangle.h"
#include "./include/trapezoid.h"
#include "./include/array.h"

int main() {
    // Создание фигур через ввод с клавиатуры
    Square<double> square;
    std::cin >> square;

    Rectangle<double> rectangle;
    std::cin >> rectangle;

    Trapezoid<double> trapezoid;
    std::cin >> trapezoid;

    // Array с shared_ptr<Figure<double>>
    Array<std::shared_ptr<Figure<double>>> figures;

    std::shared_ptr<Figure<double>> shared_ptr_square = std::make_shared<Square<double>>(square);
    std::shared_ptr<Figure<double>> shared_ptr_rectangle = std::make_shared<Rectangle<double>>(rectangle);
    std::shared_ptr<Figure<double>> shared_ptr_trapezoid = std::make_shared<Trapezoid<double>>(trapezoid);

    figures.add(shared_ptr_square);
    figures.add(shared_ptr_rectangle);
    figures.add(shared_ptr_trapezoid);

    figures.printArray();
    std::cout << "Total area in array figures = " << figures.arrayArea() << '\n';

    // Удаление элемента
    std::cout << "\n\nAfter pop element index 0:\n";
    figures.pop(0);
    figures.printArray();

    // Array с конкретными типами
    std::cout << "\n\nTesting Array<Square<int>>:\n";

    std::vector<Point<double>> square_points_1 = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    std::vector<Point<double>> square_points_2 = {{1, 1}, {3, 1}, {3, 3}, {1, 3}};

    Square<double> square_1(square_points_1);
    Square<double> square_2(square_points_2);

    Array<Square<double>> array_squares;
    array_squares.add(square);
    array_squares.add(square_1);
    array_squares.add(square_2);

    array_squares.printArray();
    std::cout << "Total area in array squares = " << array_squares.arrayArea() << '\n';

    // Тестирование сравнения
    std::cout << "\n\nTesting equals: \n";
    std::cout << "Check square_1 == square ?\n";
    std::cout << "square_1: \n " << square_1 << '\n';
    std::cout << "square: \n " << square << '\n';

    std::cout << (square_1 == square ? "Equal" : "Not equal") << '\n';

    std::cout << '\n';
    std::cout << "Check square == square_2 ?\n";
    std::cout << "square: " << square << '\n';
    std::cout << "square_2: " << square_2 << '\n';

    std::cout << (square == square_2 ? "Equal" : "Not equal") << '\n';

    return 0;
}