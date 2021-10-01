#include <iostream>
#include <cstdint>
#include <tgmath.h>
#include <vector>
#include <string>
#include <memory>
#include <istream>
#include <sstream>
#include <iomanip>

using namespace std;

class Figure {
public:
	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;
private:
};

class Triangle : public Figure{
public:
	Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {};
	string Name() const override {
		return "TRIANGLE";
	}
	double Perimeter() const override {
		return a_ + b_ + c_;
	}
	double Area() const override {
		double p_ = Perimeter() / 2;
		return sqrt(p_ * (p_ - a_) * (p_ - b_) * (p_ - c_));
	}
private:
	double a_, b_, c_;
};

class Rect : public Figure {
public:
	Rect(double width, double height) : width_(width), height_(height) {};
	string Name() const override {
		return "RECT";
	}
	double Perimeter() const override {
		return 2 * (width_ + height_);
	}
	double Area() const override {
		return width_ * height_;
	}
private:
	double width_, height_;
};

class Circle : public Figure {
public:
	Circle(double r) : r_(r){};
	string Name() const override {
		return "CIRCLE";
	}
	double Perimeter() const override {
		return r_ * PI * 2;
	}
	double Area() const override {
		return r_ * r_ * PI;
	}
private:
	double r_;
	const double PI = 3.14;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
	shared_ptr <Figure > f;

	string type;
	is >> type;

	if (type == "RECT") {
		double width, height;
		is >> width >> height;
		f = make_shared <Rect >(width, height);
	}
	else if (type == "TRIANGLE") {
		double a, b, c;
		is >> a >> b >> c;
		f = make_shared <Triangle >(a, b, c);
	}
	else {
		double r;
		is >> r;
		f = make_shared <Circle >(r);
	}

	return f;
}

int main() {
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			is >> ws;
			figures.push_back(CreateFigure(is));
		}
		else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
					<< current_figure->Name() << " "
					<< current_figure->Perimeter() << " "
					<< current_figure->Area() << endl;
			}
		}
	}
	return 0;
}
