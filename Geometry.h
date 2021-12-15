#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <iostream>
#include <memory>
#include<vector>

class Point;

class Shape {

public:

	Shape(int d);

	bool setDepth(int d);

	int getDepth() const;

	int dim() const;

	virtual void translate(float x, float y)=0;
	virtual void rotate()=0;
	virtual void scale(float f)=0;
	virtual bool contains(const Point& p) const=0;

	
	static constexpr double PI = 3.1415926;

protected:
	unsigned int depth;
	unsigned int dimention;
private:
	
};

class Point : public Shape {

public:
	Point(float x, float y, int d=0);

	float getX() const;
	float getY() const;

	void translate(float x,float y) override;
	void rotate() override;
	void scale(float f) override;
	bool contains(const Point& p) const override;

private:
	float X, Y;
};

class LineSegment : public Shape {

public:
	
	LineSegment(const Point& p, const Point& q);

	float getXmin() const;
	float getXmax() const;
	float getYmin() const;
	float getYmax() const;

	float length() const;

	void translate(float x, float y) override;
	void rotate() override;
	void scale(float f) override;
	bool contains(const Point& p) const override;

private:
	//x-y coordinates where X1<X2 and Y1<Y2.
	float X1, X2, Y1, Y2;
};

class TwoDShape : public Shape {

public:
	
	TwoDShape(int d);

	virtual float area() const = 0;

protected:
	//x-y coordinates of center.
	float CX, CY;
};

class Rectangle : public TwoDShape {

public:
	
	Rectangle(const Point& p, const Point& q);

	
	float getXmin() const;
	float getYmin() const;
	float getXmax() const;
	float getYmax() const;

	float area() const override;

	void translate(float x, float y) override;
	void rotate() override;
	void scale(float f) override;
	bool contains(const Point& p) const override;

private:
	//x-y coordinates where RX1<RX2 and RY1<RY2.
	float RX1, RX2, RY1, RY2;
};

class Circle : public TwoDShape {

public:

	Circle(const Point& c, float r);

	float getX() const;
	float getY() const;
	float getR() const;

	float area() const override;

	void translate(float x, float y) override;
	void rotate() override;
	void scale(float f) override;
	bool contains(const Point& p) const override;

private:
	//Radius
	float rad;
};


class Scene {

public:
	Scene();

	void addObject(std::shared_ptr<Shape> ptr);

	void setDrawDepth(int d);

	static constexpr int WIDTH = 60;
	static constexpr int HEIGHT = 20;
	
	//Constant to initalize drawdepth to prevent garbage value when setDrawDepth is not called.
	static constexpr int MAX = 99999;

private:
	int drawdepth;
	std::vector<std::shared_ptr<Shape>> SP;

friend std::ostream& operator<<(std::ostream& out, const Scene& s);
};

#endif /* GEOMETRY_H_ */