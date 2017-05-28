#ifndef Color_hxx_included
#define Color_hxx_included

#include <SFML/Graphics/Color.hpp>
#include <ostream>

namespace raytracer
{
	template< typename T >
	T const& clamp( T const& value, T const& min, T const& max )
	{
		return value < min ? min : value > max ? max : value;
	}

	struct color
	{
		double r = 0.0, g = 0.0, b = 0.0, a = 1.0;

		color() noexcept = default;
		color( double fill ) noexcept
			: color{ fill, fill, fill }
		{
		}
		color( double r, double g, double b ) noexcept
			: r{ r }, g{ g }, b{ b }
		{
		}
		color( double r, double g, double b, double a ) noexcept
			: r{ r }, g{ g }, b{ b }, a{ a }
		{
		}
		explicit color( sf::Color const& rhs ) noexcept
			: color{ static_cast< double >( rhs.r ) / 255, static_cast< double >( rhs.g ) / 255, static_cast< double >( rhs.b ) / 255, static_cast< double >( rhs.a ) / 255 }
		{
		}

		sf::Color to_sf_color() const noexcept
		{
			return
			{
				static_cast< sf::Uint8 >( clamp( static_cast< int >( r * 255 ), 0, 255 ) ),
				static_cast< sf::Uint8 >( clamp( static_cast< int >( g * 255 ), 0, 255 ) ),
				static_cast< sf::Uint8 >( clamp( static_cast< int >( b * 255 ), 0, 255 ) ),
				static_cast< sf::Uint8 >( clamp( static_cast< int >( a * 255 ), 0, 255 ) ),
			};
		}

		color& operator+=( color const& rhs )
		{
			r += rhs.r;
			g += rhs.g;
			b += rhs.b;
			a += rhs.a;
			return *this;
		}
		color& operator-=( color const& rhs )
		{
			r -= rhs.r;
			g -= rhs.g;
			b -= rhs.b;
			a -= rhs.a;
			return *this;
		}
		color& operator*=( color const& rhs )
		{
			r *= rhs.r;
			g *= rhs.g;
			b *= rhs.b;
			a *= rhs.a;
			return *this;
		}
		template< typename T >
		color& operator*=( T const& scalar )
		{
			r *= scalar;
			g *= scalar;
			b *= scalar;
			a *= scalar;
			return *this;
		}
		color& operator/=( color const& rhs )
		{
			r /= rhs.r;
			g /= rhs.g;
			b /= rhs.b;
			a /= rhs.a;
			return *this;
		}
		template< typename T >
		color& operator/=( T const& scalar )
		{
			r /= scalar;
			g /= scalar;
			b /= scalar;
			a /= scalar;
			return *this;
		}
	};

	color operator+( color lhs, color const& rhs )
	{
		return lhs += rhs;
	}
	color operator-( color lhs, color const& rhs )
	{
		return lhs -= rhs;
	}
	color operator*( color lhs, color const& rhs )
	{
		return lhs *= rhs;
	}
	template< typename T >
	color operator*( color lhs, T const& scalar )
	{
		return lhs *= scalar;
	}
	color operator/( color lhs, color const& rhs )
	{
		return lhs /= rhs;
	}
	template< typename T >
	color operator/( color lhs, T const& scalar )
	{
		return lhs /= scalar;
	}

	std::ostream& operator<<( std::ostream& Stream, color const& object )
	{
		return Stream << '(' << object.r << ',' << object.g << ',' << object.b << ',' << object.a << ')';
	}
}

#endif // !Color_hxx_included
