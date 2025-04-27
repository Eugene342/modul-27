#include <iostream>
#include <cmath>
#include <string>
enum class Color
{
	NONE = 0,
	RED = 1,
	BLUE = 2,
	GREEN = 3,
	YELLOW = 4
};
class Shape
{
protected:
	double centerX;
	double centerY;
	Color color;
public:
	Shape(double x, double y, Color c) : centerX(x), centerY(y), color(c)
	{
	}
	virtual double area() const = 0;
	virtual void boundingRectangle(double& width, double& height) const = 0;
	virtual ~Shape()
	{
	}
};
class Circle : public Shape
{
private:
	double radius;
public:
	Circle(double x, double y, Color c, double r) : Shape(x, y, c), radius(r)
	{
	}
	double area() const override
	{
		return atan(1) * 4 * radius * radius;
	}
	void boundingRectangle(double& width, double& height) const override
	{
		width = height = 2 * radius;
	}
};
class Square : public Shape
{
private:
	double length;
public:
	Square(double x, double y, Color c, double l) : Shape(x, y, c), length(l)
	{
	}
	double area() const override
	{
		return length * length;
	}
	void boundingRectangle(double& width, double& height) const override
	{
		width = height = length;
	}
};
class Triangle : public Shape
{
private:
	double length;
public:
	Triangle(double x, double y, Color c, double l) : Shape(x, y, c), length(l)
	{
	}
	double area() const override
	{
		return (std::sqrt(3) / 4) * length * length;
	}
	void boundingRectangle(double& width, double& height) const override
	{
		width = length;
		height = (std::sqrt(3) / 2) * length;
	}
};
class Rectangle : public Shape
{
private:
	double width;
	double height;
public:
	Rectangle(double x, double y, Color c, double w, double h) : Shape(x, y, c), width(w), height(h)
	{
	}
	double area() const override
	{
		return width * height;
	}
	void boundingRectangle(double& w, double& h) const override
	{
		w = width;
		h = height;
	}
};
int main()
{
	std::string command;
	while (true)
	{
		std::cout << "Enter the command (circle, square, triangle, rectangle or exit): ";
		std::cin >> command;
		if (command == "exit")
		{
			break;
		}
		double x, y, parameter1, parameter2;
		Color color;
		std::cout << "Enter the coordinates of the center: ";
		std::cin >> x >> y;
		std::cout << "Enter the color (0 - None, 1 - Red, 2 - Blue, 3 - Green, 4 - Yellow): ";
		int colorInput;
		std::cin >> colorInput;
		color = static_cast <Color>(colorInput);
		Shape* shape = nullptr;
		if (command == "circle")
		{
			std::cout << "Enter the radius: ";
			std::cin >> parameter1;
			shape = new Circle(x, y, color, parameter1);
		}
		else if (command == "square")
		{
			std::cout << "Enter the length: ";
			std::cin >> parameter1;
			shape = new Square(x, y, color, parameter1);
		}
		else if (command == "triangle")
		{
			std::cout << "Enter the length: ";
			std::cin >> parameter1;
			shape = new Triangle(x, y, color, parameter1);
		}
		else if (command == "rectangle")
		{
			std::cout << "Enter the width and the height: ";
			std::cin >> parameter1 >> parameter2;
			shape = new Rectangle(x, y, color, parameter1, parameter2);
		}
		double area = shape->area();
		double boundingWidth, boundingHeight;
		shape->boundingRectangle(boundingWidth, boundingHeight);
		std::cout << "Area: " << area << std::endl;
		std::cout << "Bounding rectangle width = " << boundingWidth << ", height = " << boundingHeight << std::endl;
		std::cout << std::endl;
	}
	return 0;
}

