#pragma once

namespace Wrum
{
	struct Vec3
	{
		union
		{
			struct 
			{
				float x;
				float y;
				float z;
			};

			struct
			{
				float r;
				float g;
				float b;
			};

			float v[3];
		};

		Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

		static float Dot(const Vec3& lhs, const Vec3& rhs);
		// Right handed cross product
		static Vec3 Cross(const Vec3& lhs, const Vec3& rhs);
		static float Angle(const Vec3& lhs, const Vec3& rhs);
	
		static Vec3 Project(const Vec3& a, const Vec3& b);
		static Vec3 Reject(const Vec3& a, const Vec3& b);
		static Vec3 Reflect(const Vec3& a, const Vec3& b);
		static float Distance(const Vec3& a, const Vec3& b);
		static float DistanceSq(const Vec3& a, const Vec3& b);
		static Vec3 Lerp(const Vec3& a, const Vec3& b, float alpha);

		Vec3 GetRight() const { return {x, 0.0f, 0.0f}; }
		Vec3 GetUp() const { return {0.0f, y, 0.0f}; }
		Vec3 GetForward() const { return {0.0f, 0.0f, -z}; }
		
		float LenSq() const;
		float Len() const;
		void Normalize();
		Vec3 Normalized() const;
		std::string ToString() const;

		static Vec3 Zero;
		
		static Vec3 GlobalRight;
		static Vec3 GlobalForward;
		static Vec3 GlobalUp;
	};
	
	Vec3& operator+=(Vec3& lhs, Vec3 rhs);
	Vec3& operator-=(Vec3& lhs, Vec3 rhs);

	Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
	Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
	Vec3 operator*(const Vec3& vec, float num);

	bool operator==(const Vec3& lhs, const Vec3& rhs);
	bool operator!=(const Vec3& lhs, const Vec3& rhs);
}