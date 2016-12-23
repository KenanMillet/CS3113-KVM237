
#pragma once

class Matrix {
    public:
    
        Matrix();
    
        union {
            float m[4][4];
            float ml[16];
        };
    
        void identity();
        Matrix operator * (const Matrix &m2) const;
        Matrix inverse() const;
    
        void Translate(float x, float y, float z);
        void Scale(float x, float y, float z);
        void Rotate(float rotation);
        void Roll(float roll);
        void Pitch(float pitch);
        void Yaw(float yaw);
    
        void setPosition(float x, float y, float z);
        void setScale(float x, float y, float z);
        void setRotation(float rotation);
        void setRoll(float roll);
        void setPitch(float pitch);
        void setYaw(float yaw);

        void setOrthoProjection(float left, float right, float bottom, float top, float zNear, float zFar);
        void setPerspectiveProjection(float fov, float aspect, float zNear, float zFar);
};

class Vector
{
public:
	Vector(float = 0.0f, float = 0.0f, float = 0.0f, float = 1.0f);
	Vector(const Vector&);
	Vector& operator=(const Vector&);
	
	float magnitude() const;
	Vector& normalize();

	Vector operator+(const Vector&) const;
	Vector operator-(const Vector&) const;
	Vector operator-() const;
	float operator*(const Vector&) const;
	Vector operator^(const Vector&) const;
	Vector operator*(float) const;
	Vector operator/(float) const;

	Vector& operator+=(const Vector&);
	Vector& operator-=(const Vector&);
	Vector& operator^=(const Vector&);
	Vector& operator*=(float);
	Vector& operator/=(float);

	float& operator[](size_t);
	const float& operator[](size_t) const;

	float dot(const Vector&) const;
	Vector cross(const Vector&) const;

	float& x;
	float& y;
	float& z;
	float& w;
private:
	float v[4];
};

Vector operator*(const Matrix&, const Vector&);
bool operator==(const Vector&, const Vector&);
bool operator!=(const Vector&, const Vector&);