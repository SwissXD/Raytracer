#ifndef raytracer_Scene_hxx_included
#define raytracer_Scene_hxx_included

#include <cstddef>
#include <vector>
#include <memory>
#include <limits>
#include <cmath>
#include <cassert>

#include "Camera.hxx"
#include "Image.hxx"
#include "Object.hxx"
#include "Color.hxx"

namespace raytracer
{
	class Scene
	{
	public:
		Camera camera;
		std::vector< std::unique_ptr< Object > > Objects;
		color BackgroundColor;

		Intersection GetIntersection( Ray const& ray ) const
		{
			Intersection Result;
			Result.Distance = std::numeric_limits< double >::max();
			for( auto&& i : Objects )
			{
				auto const Current = i->Intersect( ray );
				if( Current.Hit )
					if( Current.Distance < Result.Distance )
						Result = Current;
			}
			return Result;
		}

		void Render( Image& output ) const
		{
			assert( output.Width() != 0 );
			assert( output.Height() != 0 );

			const double Width = 2 * std::tan( camera.FOVX / 2 );
			const double Height = 2 * std::tan( camera.FOVX / output.Width() * output.Height() / 2 );
			const vec3d At = normalized( camera.At );
			const vec3d Left = normalized( cross( At, camera.Up ) ) * Width;
			const vec3d Up = normalized( cross( At, Left ) ) * Height;

			for( std::size_t y = 0; y < output.Height(); ++y )
				for( std::size_t x = 0; x < output.Width(); ++x )
				{
					Ray ray;
					ray.Position = camera.Position;
					ray.Direction = At
						- Left * ( x / static_cast< double >( output.Width() - 1 ) - 0.5 )
						+ Up * ( y / static_cast< double >( output.Height() - 1 ) - 0.5 );
					normalize( ray.Direction );
					const auto I = GetIntersection( ray );
					if( I.Hit )
						output( x, y ) = I.Hit->GetColor( I.Position );
					else 
						output( x, y ) = BackgroundColor;

				}
		}
	};
}

#endif // !raytracer_Scene_hxx_included
