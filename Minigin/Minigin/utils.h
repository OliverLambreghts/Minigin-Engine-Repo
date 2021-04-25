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
		Point2f center;
		std::vector<Point2f> vertices;
		bool isActive = false;
	};

	void DrawHexagon(SDL_Renderer* renderer, const std::vector<Point2f>& vertices);
	bool IsPointInPolygon(const Point2f& p, const std::vector<Point2f>& vertices);
	bool IsPointInPolygon(const Point2f& p, const Point2f* vertices, size_t nrVertices);
	bool IntersectLineSegments(const Point2f& p1, const Point2f& p2, const Point2f& q1, const Point2f& q2, float& outLambda1, float& outLambda2, float epsilon = 1e-6);
	bool IsPointOnLineSegment(const Point2f& p, const Point2f& a, const Point2f& b);
}