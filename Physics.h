#pragma once
#include <array>

using pos_t = std::array<double, 2>;

inline pos_t operator +(const pos_t &a, const pos_t &b) {
	return { a[0] + b[0], a[1] + b[1] };
}
inline pos_t operator -(const pos_t &a, const pos_t &b) {
	return { a[0] - b[0], a[1] - b[1] };
}
/*pos_t operator -(const pos_t &a) {
return { -a[0], -a[1] };
}*/
inline pos_t operator *(const pos_t &a, const pos_t &b) {
	return { a[0] * b[0], a[1] * b[1] };
}
inline pos_t operator /(const pos_t &a, const pos_t &b) {
	return { a[0] / b[0], a[1] / b[1] };
}
inline pos_t operator *(const pos_t &a, const double &b) {
	return { a[0] * b, a[1] * b };
}
inline bool operator ==(const pos_t &a, const double &b) {
	return a[0] == b && a[1] == b;
}


class Physics
{
private:
	//friend class pos_t;
	//using pos_t = std::array<double, 2>;
	/*friend class pos_t;
	friend pos_t operator +(const pos_t &a, const pos_t &b) {
	return { a[0] + b[0], a[1] + b[1] };
	}
	friend pos_t operator -(const pos_t &a, const pos_t &b) {
	return { a[0] - b[0], a[1] - b[1] };
	}
	friend pos_t operator *(const pos_t &a, const pos_t &b) {
	return { a[0] * b[0], a[1] * b[1] };
	}
	friend pos_t operator *(const pos_t &a, const double &b) {
	return { a[0] * b, a[1] * b };
	}*/
public:

	pos_t position;
	pos_t velocity;
	pos_t acceleration;

	Physics(pos_t pos = { 0, 0 }, pos_t vel = { 0, 0 }, pos_t acc = { 0, 0 });
	void move(int dt, bool resistance = false);
	void bounce(int axis, float direction);
	~Physics();
};