#include <gtest/gtest.h>
#include <memory>
#include "../include/figure.h"
#include "../include/square.h"
#include "../include/rectangle.h"
#include "../include/trapezoid.h"
#include "../include/array.h"


// Тесты для Square
TEST(SquareTest, AreaCalculation) {
    Square<double> square(0.0, 0.0, 4.0);
    EXPECT_DOUBLE_EQ(16.0, static_cast<double>(square));
}

TEST(SquareTest, CenterCalculation) {
    Square<double> square(2.0, 2.0, 4.0);
    Point<double> center = square.center();
    EXPECT_DOUBLE_EQ(2.0, center.x);
    EXPECT_DOUBLE_EQ(2.0, center.y);
}

TEST(SquareTest, EqualityOperator) {
    Square<double> square1(0.0, 0.0, 4.0);
    Square<double> square2(0.0, 0.0, 4.0);
    Square<double> square3(1.0, 1.0, 3.0);
    
    EXPECT_TRUE(square1 == square2);
    EXPECT_FALSE(square1 == square3);
}

// Тесты для Rectangle
TEST(RectangleTest, AreaCalculation) {
    Rectangle<double> rectangle(0.0, 0.0, 6.0, 4.0);
    EXPECT_DOUBLE_EQ(24.0, static_cast<double>(rectangle));
}

TEST(RectangleTest, CenterCalculation) {
    Rectangle<double> rectangle(1.0, 1.0, 4.0, 2.0);
    Point<double> center = rectangle.center();
    EXPECT_DOUBLE_EQ(1.0, center.x);
    EXPECT_DOUBLE_EQ(1.0, center.y);
}

// Тесты для Trapezoid
TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid<double> trapezoid(0.0, 0.0, 8.0, 4.0, 3.0);
    EXPECT_DOUBLE_EQ(18.0, static_cast<double>(trapezoid));
}

// Тесты для Array

TEST(ArrayTest, TotalAreaCalculation) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    auto square = std::make_shared<Square<double>>(0.0, 0.0, 2.0);    // area = 4
    auto rectangle = std::make_shared<Rectangle<double>>(0.0, 0.0, 3.0, 2.0); // area = 6
    
    figures.add(square);
    figures.add(rectangle);
    
    EXPECT_DOUBLE_EQ(10.0, figures.arrayArea());
}

TEST(ArrayTest, SpecificTypeArray) {
    Array<Square<double>> squares;
    
    squares.add(Square<double>(0.0, 0.0, 2.0));
    squares.add(Square<double>(1.0, 1.0, 3.0));
    
    EXPECT_DOUBLE_EQ(13.0, squares.arrayArea()); // 4 + 9
}

// Тест копирования и перемещения
TEST(FigureTest, CopyConstructor) {
    Square<double> original(0.0, 0.0, 5.0);
    Square<double> copy(original);
    
    EXPECT_TRUE(original == copy);
}

TEST(FigureTest, MoveConstructor) {
    Square<double> original(0.0, 0.0, 5.0);
    Square<double> moved(std::move(original));
    
    EXPECT_DOUBLE_EQ(25.0, static_cast<double>(moved));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}