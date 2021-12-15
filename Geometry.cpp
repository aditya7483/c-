#include "Geometry.h"
#include <stdexcept>
#include <cmath>
// ============ Shape class =================

Shape::Shape(int d) {
	if (d < 0)
		throw std::invalid_argument("Depth cannot be negetive");
	else
		depth = d;
}

bool Shape::setDepth(int d) {
	if (d < 0)
		return false;
	else
	{
		depth = d;
		return true;
	}
}

int Shape::getDepth() const {
	return depth;
}

int Shape::dim() const {
	return dimention;
}

// =============== Point class ================

Point::Point(float x, float y, int d):Shape(int (d))
{
	dimention = 0;
	X = x;
	Y = y;
}

float Point::getX() const {
	return X;
}

float Point::getY() const {
	return Y;
}

void Point::translate(float x, float y) 
{
	X += x;
	Y += y;
}

void Point::rotate() { }

void Point::scale(float f)
{
	if (f <= 0)
	{
		throw std::invalid_argument("value of scale should be greater than zero");
	}
}

bool Point::contains(const Point& p)const 
{
	if (X == p.getX() && Y == p.getY())
	{
		return true;
	}
	return false;
}

// =========== LineSegment class ==============

LineSegment::LineSegment(const Point& p, const Point& q):Shape(int (p.getDepth()))
{
	if (p.getDepth() != q.getDepth())
	{
		throw std::invalid_argument("Depth of the points must be equal");
	}

	else if (p.getX() != q.getX() && p.getY() != q.getY())
	{
		throw std::invalid_argument("The line should be aligned to either x or y axis");
	}

	else if (p.getX() == q.getX() && p.getY() == q.getY())
	{
		throw std::invalid_argument("The points should not have same x and y coordinates");
	}

	dimention = 1;
	
	X1 = (p.getX() < q.getX()) ? p.getX() : q.getX();
	X2 = (p.getX() > q.getX()) ? p.getX() : q.getX();
	Y1 = (p.getY() < q.getY()) ? p.getY() : q.getY();
	Y2 = (p.getY() > q.getY()) ? p.getY() : q.getY();
}

float LineSegment::getXmin() const {
	return X1;
}

float LineSegment::getXmax() const {
	return X2;
}

float LineSegment::getYmin() const {
	return Y1;
}

float LineSegment::getYmax() const {
	return Y2;
}

float LineSegment::length() const {
	float a, b;
	a = pow((X1 - X2), 2);
	b = pow((Y1 - Y2), 2);
	return sqrt(a + b);
}

void LineSegment::translate(float x, float y) 
{
	X1 += x;
	X2 += x;
	Y1 += y;
	Y2 += y;
}

void LineSegment::rotate() 
{
	//x and y co-ordinates of the center.
	float cx, cy, dist;
	cx = (X1 + X2) / 2;
	cy = (Y1 + Y2) / 2;
	
	if (Y1 == Y2)
	{
		dist = abs(X2 - cx);
		X1 = cx;
		X2 = cx;

		Y1 = cy - dist;
		Y2 = cy + dist;
	}
	else
	{
		dist = abs(Y2 - cy);
		Y1 = cy;
		Y2 = cy;

		X1 = cx - dist;
		X2 = cx + dist;
	}
}

void LineSegment::scale(float f) 
{
	if (f <= 0)
	{
		throw std::invalid_argument("factor cannot be zero or negative");
	}

	float cx,cy;

	//distance of ends from the center
	//and the value to be added to the coordinates of the center.
	float dist,ad;

	cx = (X1 + X2) / 2;
	cy = (Y1 + Y2) / 2;
	
	if (Y1 == Y2)
	{
		dist = abs(X2 - cx);
		ad = dist * f;

		X1 = cx - ad;
		X2 = cx + ad;
	}
	else
	{
		dist = abs(Y2 - cy);
		ad = dist * f;

		Y2 = cy + ad;
		Y1 = cy - ad;
	}

}

bool LineSegment::contains(const Point& x) const 
{	
	if ((x.getX() >= X1 && x.getX() <= X2) && (x.getY() >= Y1 && x.getY() <= Y2))
	{
		return true;
	}
	return false;
}

// ============ TwoDShape class ================

TwoDShape::TwoDShape(int d) :Shape(int (d))
{
	dimention = 2;
}

// ============== Rectangle class ================

Rectangle::Rectangle(const Point& p, const Point& q):TwoDShape(int(p.getDepth()))
{
	if (p.getX() == q.getX() || p.getY() == q.getY())
	{
	throw std::invalid_argument("The points should not have same x or y coordinates");
	}

	if (p.getDepth() != q.getDepth())
	{
		throw std::invalid_argument("Depth of the points must be equal");
	}

	depth = p.getDepth();
	
	RX1 = (p.getX() < q.getX()) ? p.getX() : q.getX();
	RX2 = (p.getX() > q.getX()) ? p.getX() : q.getX();
	RY1 = (p.getY() < q.getY()) ? p.getY() : q.getY();
	RY2 = (p.getY() > q.getY()) ? p.getY() : q.getY();

	CX = (RX1 + RX2) / 2;
	CY = (RY1 + RY2) / 2;
}

float Rectangle::getXmin() const {
	return RX1;
}

float Rectangle::getYmin() const {
	return RY1;
}

float Rectangle::getXmax() const {
	return RX2; 
}

float Rectangle::getYmax() const {
	return RY2;
}

float Rectangle::area()const {
	float a,b;
	a = RX1 - RX2;
	b = RY1 - RY2;
	return a * b;
}

void Rectangle::translate(float x, float y) 
{
	RX1 += x;
	RX2 += x;
	RY1 += y;
	RY2 += y;
}

void Rectangle::rotate() 
{
	//x-y coordinates of center and distance of the sides from center.
	float distx, disty;
	
	distx = abs(RX2 - CX);
	disty = abs(RY2 - CY);

	RY2 = CY + distx;
	RX2 = CX + disty;
	RY1 = CY - distx;
	RX1 = CX - disty;
}

void Rectangle::scale(float f) 
{
	if (f <= 0)
	{
		throw std::invalid_argument("factor cannot be zero or negative");
	}

	float distx, disty;

	distx = abs(RX2 - CX);
	disty = abs(RY2 - CY);

	float adx,ady;//term to be added or subtracted from the coordinates of center.
	adx = f * distx;
	ady = f * disty;

	RX2 = CX + adx;
	RX1 = CX - adx;
	RY2 = CY + ady;
	RY1 = CY - ady;
}

bool Rectangle::contains(const Point& x) const 
{
	if ((x.getX() >= RX1 && x.getX() <= RX2) && (x.getY() >= RY1 && x.getY() <= RY2))
	{
		return true;
	}
	return false;
}

// ================== Circle class ===================

Circle::Circle(const Point& c, float r):TwoDShape(int(c.getDepth()))
{
	if (r <= 0)
	{
		throw std::invalid_argument("Radius must be greater than zero");
	}

	CX = c.getX();
	CY = c.getY();
	rad = r;
	depth = c.getDepth();
}

float Circle::getX() const {
	return CX;
}

float Circle::getY() const {
	return CY;
}

float Circle::getR() const {
	return rad;
}

float Circle::area() const {
	return PI * rad * rad;
}

void Circle::translate(float x, float y) 
{
	CX += x;
	CY += y;
}

void Circle::rotate() {}

void Circle::scale(float f) 
{
	if (f <= 0)
	{
		throw std::invalid_argument("factor cannot be zero or negative");
	}

	rad *= f;
}

bool Circle::contains(const Point& x) const 
{
	float a, b, dist;
	a = pow((CX - x.getX()), 2);
	b = pow((CY - x.getY()), 2);
	dist = sqrt(a + b);

	if (dist <= rad)
	{
		return true;
	}
	return false;
}

// ================= Scene class ===================

constexpr int Scene::WIDTH;
constexpr int Scene::HEIGHT;
constexpr int Scene::MAX;

Scene::Scene() {
	//preventing garbage value if setDrawDepth is not called.
	drawdepth = MAX;
}

void Scene::addObject(std::shared_ptr<Shape> ptr) {
	SP.push_back(ptr);
}

void Scene::setDrawDepth(int d) {
	if (d < 0)
		throw std::invalid_argument("Depth cannot be negetive");
	else
		drawdepth = d;
}

std::ostream& operator<<(std::ostream& out, const Scene& s) {
	bool check = false;

	for (int i = s.HEIGHT-1; i >= 0; i--)
	{
		for (int j = 0; j < s.WIDTH; j++)
		{
			Point p(j, i);

			//check if any of the objects contain the point (j,i).
			for (int k = 0; k < s.SP.size(); k++)
			{
				if ((s.SP[k]->contains(p)) && (s.SP[k]->getDepth() <= s.drawdepth))
				{
					check = true;
					break;
				}
				else check = false;
			}

			if (check)
			{
				out << "*";
			}
			else
			{
				out << " ";
			}
		}
		out << "\n";
	}
	return out;
}
