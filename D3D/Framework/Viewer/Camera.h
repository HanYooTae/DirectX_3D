#pragma once

class Camera
{
public:
	Camera();
	virtual ~Camera();

	virtual void Update() = 0;

public:
	void Position(float x, float y, float z);
	void Position(Vector3& vec);
	void Position(Vector3* vec);

	// Radian
	void Rotation(float x, float y, float z);
	void Rotation(Vector3& vec);
	void Rotation(Vector3* vec);

	void RotationDegrees(float x, float y, float z);
	void RotationDegrees(Vector3& vec);
	void RotationDegrees(Vector3* vec);

	void GetMatrix(Matrix* matrix);

	Vector3 Right() { return right; }
	Vector3 Up() { return up; }
	Vector3 Forward() { return forward; }

protected:
	virtual void Rotation();
	virtual void Move();

protected:
	// View ��Ʈ������ ������ִ� �Լ�
	void View();

private:
	Vector3 position = Vector3(0, 0, 0);
	Vector3 rotation = Vector3(0, 0, 0);

	Vector3 right = Vector3(0, 1, 0);
	Vector3 up = Vector3(0, 1, 0);
	Vector3 forward = Vector3(0, 0, 1);

	Matrix matRotation;
	Matrix matView;
};