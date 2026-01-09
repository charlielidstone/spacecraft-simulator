#ifndef VECTOR2_HPP
#define VECTOR2_HPP

struct Vector2 {
	double x = 0.0;
	double y = 0.0;

	Vector2() = default;
	Vector2(double x, double y) : x(x), y(y) {}

	Vector2 operator+(const Vector2& other) const {
		return { x + other.x, y + other.y };
	}

	Vector2 operator-(const Vector2& other) const {
		return { x - other.x, y - other.y };
	}

	Vector2 operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2 operator-=(const Vector2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2 operator*(const double& scalar) const {
		return { x * scalar, y * scalar };
	}

	Vector2 operator/(const double& scalar) const {
		return { x / scalar, y / scalar };
	}
};

#endif