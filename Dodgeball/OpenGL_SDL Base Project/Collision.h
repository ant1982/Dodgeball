#pragma once
// Collision - library of functions and classes for collision detection
#include "Commons.h"


class Sphere {
public:
	Sphere(Vector3D c, float r) { centre = c; radius = r; collided = false; }
	float GetBoundingRadius() const { return radius; }
	Vector3D GetCentre() { return centre; }
	void Update(Vector3D newPos) { centre = newPos; }
	void SetCollided(bool c) { collided = c; }
	bool GetCollided() { return collided; }
private:
	Vector3D centre;
	float radius;
	bool collided;
};

class Box {

public:

	Box(Vector3D position, float h, float w, float d) { Position = position, height = h, width = w, depth = d, collided = false; };
	float GetNearCorner() const { return Corner1; }
	float GetFarCorner() const { return Corner2; }
	void Update(Vector3D newPos) { Position = newPos; }
	void SetCollided(bool c) { collided = c; }
	bool GetCollided() { return collided; }
	Vector3D GetPosition() const { return Position; }
	float GetWidth() const { return width; }
	float GetHeight() const { return height; }
	float GetDepth() const { return depth; }

private:
	float Corner1;
	float Corner2;
	float height;
	float width;
	float depth;

	bool collided;
	Vector3D Position;
	//float x = Position.x;
	//float y = Position.y;
	//float z = Position.z;

};

class Plane {

public:

	Plane(Vector3D position) { Position = position, collided = false; }
	void Update(Vector3D newPos) { Position = newPos; }
	void SetCollided(bool c) { collided = c; }
	bool GetCollided() { return collided; }
	Vector3D GetPosition() const { return Position; }

private:

	Vector3D Position;
	bool collided;
};

class Collision {
public:

	static bool SphereSphereCollision(Sphere *s1, Sphere *s2) {
		Vector3D centre1 = s1->GetCentre();
		Vector3D centre2 = s2->GetCentre();
		float dx = centre2.x - centre1.x;
		float dy = centre2.y - centre1.y;
		float dz = centre2.z - centre1.z;

		float dSquared = dx*dx + dy*dy + dz *dz;

		float sumOfBoundingRadii = s1->GetBoundingRadius() + s2->GetBoundingRadius();

		float hasCollided = false;
		if (dSquared < (sumOfBoundingRadii * sumOfBoundingRadii)) {
			s1->SetCollided(true);
			s2->SetCollided(true);
			return true;
		}
		return false;
	}

	static bool BoxCollision(Box* b1, Box* b2)
	{
		Vector3D box1 = b1->GetPosition();
		float b1width = b1->GetWidth();
		float b1height = b1->GetHeight();
		float b1depth = b1->GetDepth();


		Vector3D box2 = b1->GetPosition();
		float b2width = b2->GetWidth();
		float b2height = b2->GetHeight();
		float b2depth = b2->GetDepth();

		float hasCollided = false;

		if (box1.x /*+ b1width*/ >= box2.x &&
			box2.x /*+ b2width*/ <= box1.x &&
			box1.x /*+ b1height*/ >= box2.y &&
			box2.y /*+ b2height*/ <= box1.y &&
			box1.z /*+ b1depth*/ >= box2.z &&
			box2.z /*+ b2depth*/ <= box1.z
			)
		{
			b1->SetCollided(true);
			b1->SetCollided(true);
			return true;
		}

		return false;
	}

	static bool SpherePlaneCollision(Sphere* s1, Plane* p1) {

		Vector3D centre1 = s1->GetCentre();
		float radius = s1->GetBoundingRadius();

		Vector3D plane1 = p1->GetPosition();
		if (radius < plane1.y - centre1.y)
		{
			p1->SetCollided(true);
			s1->SetCollided(true);
			return true;
		}
		return false;
	}

	static bool BoxCircleCollision(Box *b1, Sphere *s1) {

		Vector3D box1 = b1->GetPosition();
		float b1width = b1->GetWidth();
		float b1height = b1->GetHeight();
		float b1depth = b1->GetDepth();

		Vector3D centre1 = s1->GetCentre();
		float radius = s1->GetBoundingRadius();

		if (box1.x + b1width >= centre1.x - radius &&
			box1.x <= centre1.x + radius &&
			box1.y + b1height >= centre1.y - radius &&
			box1.y <= centre1.y + radius &&
			box1.z + b1depth >= centre1.z - radius &&
			box1.z <= centre1.z + radius
			)
		{
			b1->SetCollided(true);
			s1->SetCollided(true);
			return true;
		}
		return false;
	}
};
