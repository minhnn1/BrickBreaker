#include "pch.h"
#include "physics.h"
using namespace sf;
using namespace std;

float linear_interpolation(float x, float y, float z)
{
	//current speed, max speed, acceleration
	return ((1.0f - z) * x) + (z * y);
}

float signnum(float x) {
	if (x > 0.0) return 1.0;
	if (x < 0.0) return -1.0;
	return x;
}

Vector2f normalize(Vector2f v)
{
	float length = sqrt(v.x * v.x + v.y * v.y);
	return Vector2f(v.x / length, v.y / length);
}

float dot(Vector2f v1, Vector2f v2)
{
	return sqrt(abs(v1.x * v2.x + v1.y * v2.x));
}

Vector2f multiply(Vector2f v, float f)
{
	return Vector2f(v.x * f, v.y * f);
}

bool ctcCollision(CircleShape obj1, CircleShape obj2)
{
	Vector2f cir1 = obj1.getPosition();
	double rad1 = obj1.getRadius();

	Vector2f cir2 = obj2.getPosition();
	double rad2 = obj2.getRadius();

	double dist = (cir2.x - cir1.x) * (cir2.x - cir1.x) + (cir2.y - cir1.y) * (cir2.y - cir1.y);

	return dist < (rad1 + rad2)* (rad1 + rad2);
}

Vector2f ctcCollisionHandle(CircleShape obj1, Vector2f vel1, CircleShape obj2, Vector2f vel2)
{
	Vector2f cen1 = obj1.getPosition();
	Vector2f cen2 = obj2.getPosition();
	cout << "cen " << cen1.x << " " << cen1.y << " " << cen2.x << " " << cen2.y << endl;
	cout << "vel " << vel1.x << " " << vel1.y << " " << vel2.x << " " << vel2.y << endl;

	Vector2f tangentVector = normalize(Vector2f(cen2.y - cen1.y, cen2.x - cen1.x));
	cout << "tangentVector " << tangentVector.x << " " << tangentVector.y << endl;

	Vector2f relativeVel = Vector2f(vel2.x - vel1.x, vel2.y - vel1.y);
	cout << "relativeVel " << relativeVel.x << " " << relativeVel.y << endl;

	float length = dot(relativeVel, tangentVector);
	cout << "length " << length << endl;

	Vector2f tangentVel = tangentVector * length;
	cout << "tangentVel " << tangentVel.x << " " << tangentVel.y << endl;

	Vector2f perpendicularVel = relativeVel - tangentVel;
	cout << "perpendicularVel " << perpendicularVel.x << " " << perpendicularVel.y << endl;

	cout << endl << endl << endl;
	return perpendicularVel;
}