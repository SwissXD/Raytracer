#ifndef raytracer_Object_hxx_included
#define raytracer_Object_hxx_included

#include "Vector.hxx"
#include "Intersection.hxx"

namespace raytracer
{
	struct Object : public Intersectable
	{	
		vec3d Position;

		Object() = default;
		explicit Object( vec3d const& Position )
			: Position{ Position }
		{
		}

		virtual color GetColor( vec3d const& Point ) const = 0;
	};
}

#endif // !raytracer_Object_hxx_included
