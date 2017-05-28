#ifndef raytracer_Camera_hxx_included
#define raytracer_Camera_hxx_included

#include "Vector.hxx"

namespace raytracer
{
	struct Camera
	{
		vec3d Position;
		vec3d At;
		vec3d Up;
		double FOVX;
	};
}

#endif // !raytracer_Camera_hxx_included
