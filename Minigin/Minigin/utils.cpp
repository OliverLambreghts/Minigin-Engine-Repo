#include "MiniginPCH.h"
#include "utils.h"
#include <SDL_render.h>

#include "Vector2f.h"

void utils::DrawHexagon(SDL_Renderer* renderer, const std::vector<Point2f>& vertices)
{
	for (unsigned int i{}; i < vertices.size(); ++i)
	{
		if (i + 1 >= vertices.size())
			break;
		SDL_RenderDrawLine(renderer, static_cast<int>(vertices[i].x), static_cast<int>(vertices[i].y), static_cast<int>(vertices[i + 1].x)
			, static_cast<int>(vertices[i + 1].y));
	}
	SDL_RenderDrawLine(renderer, (int)vertices[0].x, (int)vertices[0].y, (int)vertices[5].x, (int)vertices[5].y);
}

bool utils::IsPointInPolygon(const Point2f& p, const std::vector<Point2f>& vertices)
{
	return IsPointInPolygon(p, vertices.data(), vertices.size());
}

bool utils::IsPointInPolygon(const Point2f& p, const Point2f* vertices, size_t nrVertices)
{
	if (nrVertices < 2)
	{
		return false;
	}
	// 1. First do a simple test with axis aligned bounding box around the polygon
	float xMin{ vertices[0].x };
	float xMax{ vertices[0].x };
	float yMin{ vertices[0].y };
	float yMax{ vertices[0].y };
	for (size_t idx{ 1 }; idx < nrVertices; ++idx)
	{
		if (xMin > vertices[idx].x)
		{
			xMin = vertices[idx].x;
		}
		if (xMax < vertices[idx].x)
		{
			xMax = vertices[idx].x;
		}
		if (yMin > vertices[idx].y)
		{
			yMin = vertices[idx].y;
		}
		if (yMax < vertices[idx].y)
		{
			yMax = vertices[idx].y;
		}
	}
	if (p.x < xMin || p.x > xMax || p.y < yMin || p.y > yMax)
	{
		return false;
	}

	// 2. Draw a virtual ray from anywhere outside the polygon to the point 
	//    and count how often it hits any side of the polygon. 
	//    If the number of hits is even, it's outside of the polygon, if it's odd, it's inside.
	int numberOfIntersectionPoints{ 0 };
	Point2f p2{ xMax + 10.0f, p.y }; // Horizontal line from point to point outside polygon (p2)

	// Count the number of intersection points
	float lambda1{}, lambda2{};
	for (size_t i{ 0 }; i < nrVertices; ++i)
	{
		if (IntersectLineSegments(vertices[i], vertices[(i + 1) % nrVertices], p, p2, lambda1, lambda2))
		{
			if (lambda1 > 0 && lambda1 <= 1 && lambda2 > 0 && lambda2 <= 1)
			{
				++numberOfIntersectionPoints;
			}
		}
	}
	if (numberOfIntersectionPoints % 2 == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool utils::IntersectLineSegments(const Point2f& p1, const Point2f& p2, const Point2f& q1, const Point2f& q2, float& outLambda1, float& outLambda2, float epsilon)
{
	bool intersecting{ false };

	const Vector2f p1p2{ p1, p2 };
	const Vector2f q1q2{ q1, q2 };

	// Cross product to determine if parallel
	const float denom = p1p2.CrossProduct(q1q2);

	// Don't divide by zero
	if (std::abs(denom) > epsilon)
	{
		intersecting = true;

		const Vector2f p1q1{ p1, q1 };

		const float num1 = p1q1.CrossProduct(q1q2);
		const float num2 = p1q1.CrossProduct(p1p2);
		outLambda1 = num1 / denom;
		outLambda2 = num2 / denom;
	}
	else // are parallel
	{
		// Connect start points
		const Vector2f p1q1{ p1, q1 };

		// Cross product to determine if segments and the line connecting their start points are parallel, 
		// if so, than they are on a line
		// if not, then there is no intersection
		if (std::abs(p1q1.CrossProduct(q1q2)) > epsilon)
		{
			return false;
		}

		// Check the 4 conditions
		outLambda1 = 0;
		outLambda2 = 0;
		if (utils::IsPointOnLineSegment(p1, q1, q2) ||
			utils::IsPointOnLineSegment(p2, q1, q2) ||
			utils::IsPointOnLineSegment(q1, p1, p2) ||
			utils::IsPointOnLineSegment(q2, p1, p2))
		{
			intersecting = true;
		}
	}
	return intersecting;
}

bool  utils::IsPointOnLineSegment(const Point2f& p, const Point2f& a, const Point2f& b)
{
	const Vector2f ap{ a, p }, bp{ b, p };
	// If not on same line, return false
	if (abs(ap.CrossProduct(bp)) > 0.001f)
	{
		return false;
	}

	// Both vectors must point in opposite directions if p is between a and b
	if (ap.DotProduct(bp) > 0)
	{
		return false;
	}

	return true;
}