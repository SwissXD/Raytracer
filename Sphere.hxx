#ifndef raytracer_Sphere_hxx_included
#define raytracer_Sphere_hxx_included

#include "Intersection.hxx"
#include "Vector.hxx"
#include "Object.hxx"
#include "Util.hxx"

#include <cmath>

namespace raytracer
{
	struct Sphere : public Object
	{	
		double Radius;
		color Color;

		Sphere( vec3d Position, double Radius, color Color )
			: Object{ Position }, Radius{ Radius }, Color{ Color }
		{
		}

		virtual Intersection Intersect( Ray const& ray ) const override
		{
			Intersection Result;

			const vec3d v = ray.Position - Position;
			const double vSq = dot( v, v );
			const double a = dot( ray.Direction, v );
			double Discriminant = sq( a ) - vSq + sq( Radius );
			if( bool Hit = Discriminant >= 0 )
			{
				Discriminant = std::sqrt( Discriminant );
				const double x1 = -a + Discriminant;
				const double x2 = -a - Discriminant;
				const bool x1n = x1 < 0;
				const bool x2n = x2 < 0;
				if( x1n )
					if( x2n )
						Hit = false;
					else
						Result.Distance = x2;
				else
					if( x2n )
						Result.Distance = x1;
					else
						Result.Distance = std::min( x1, x2 );
				if( Hit )
				{
					Result.Hit = this;
					Result.Position = ray.Position + ray.Direction * Result.Distance;
				}
			}
			return Result;
		}

		virtual color GetColor( vec3d const& Point ) const override
		{
			return Color;
		}
	};
}

#endif // !raytracer_Sphere_hxx_included
