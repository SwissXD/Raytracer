#ifndef raytracer_Intersection_hxx_included
#define raytracer_Intersection_hxx_included

#include "Vector.hxx"
#include "Ray.hxx"

namespace raytracer
{
	struct Object;

	struct Intersection
	{	
		vec3d Position;
		double Distance;
		Object const* Hit = nullptr;
	};

	struct Intersectable
	{
		virtual ~Intersectable() = default;

		virtual Intersection Intersect( Ray const& ray ) const = 0;
	};
}

#endif // !raytracer_Intersection_hxx_included
