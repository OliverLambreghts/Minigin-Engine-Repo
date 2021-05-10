#pragma once
#include <SDL_render.h>

namespace utils
{
	struct Point2f
	{
		float x;
		float y;
	};

	struct Tile
	{
		virtual void SSInteract() = 0;
		virtual void QBInteract() = 0;
		virtual bool IsActive() = 0;
		virtual ~Tile() = default;
	
		Point2f center;
		std::vector<Point2f> vertices;
		bool isActive = false;
	};

	struct Tile1 : public Tile
	{
		virtual ~Tile1() = default;
		
		virtual bool IsActive() override
		{
			return isActive;
		}

		virtual void QBInteract() override
		{
			isActive = true;
		}

		virtual void SSInteract() override
		{
			isActive = false;
		}
	};

	struct Tile2 : public Tile
	{
		bool isActiveOne = false;
		bool isActiveTwo = false;

		virtual ~Tile2() = default;

		virtual bool IsActive() override
		{
			if (isActiveOne && isActiveTwo)
				return true;
			return false;
		}

		virtual void QBInteract() override
		{
			if (!isActiveOne)
				isActiveOne = true;
			else if (!isActiveTwo)
				isActiveTwo = true;
		}

		virtual void SSInteract() override
		{
			if (isActiveTwo)
				isActiveTwo = false;
			else if (isActiveOne)
				isActiveOne = false;
		}
	};

	void DrawHexagon(SDL_Renderer* renderer, const std::vector<Point2f>& vertices);
	bool IsPointInPolygon(const Point2f& p, const std::vector<Point2f>& vertices);
	bool IsPointInPolygon(const Point2f& p, const Point2f* vertices, size_t nrVertices);
	bool IntersectLineSegments(const Point2f& p1, const Point2f& p2, const Point2f& q1, const Point2f& q2, float& outLambda1, float& outLambda2, float epsilon = 1e-6);
	bool IsPointOnLineSegment(const Point2f& p, const Point2f& a, const Point2f& b);
}