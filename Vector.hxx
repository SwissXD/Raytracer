#ifndef Vector_hxx_included
#define Vector_hxx_included

#include <algorithm>
#include <utility>
#include <cmath>
#include <ostream>
#include <type_traits>

namespace raytracer
{
	template< typename T, std::size_t N >
	class vec
	{
		T m_data[ N ];
		static_assert( N > 0, "invalid dimension" );

	public:
		vec()
			: m_data{}
		{
		}
		vec( vec const& ) = default;
		template< typename... args_t >
		vec( args_t const&... args )
			: m_data{ args... }
		{
			static_assert( sizeof...( args_t ) == N, "invalid number of arguments" );
		}
		template< typename U >
		explicit vec( vec< U, N > const& rhs )
		{
			for( std::size_t i = 0; i < size(); ++i )
				operator[]( i ) = static_cast< T >( rhs[ i ] );
		}

		static constexpr std::size_t static_size = N;
		constexpr std::size_t size() const noexcept
		{
			return static_size;
		}

		auto&& operator[]( std::size_t i ) const noexcept
		{
			return m_data[ i ];
		}
		auto&& operator[]( std::size_t i ) noexcept
		{
			return m_data[ i ];
		}

		vec operator+() const
		{
			return *this;
		}
		vec operator-() const
		{
			vec result;
			for( std::size_t i = 0; i < result.size(); ++i )
				result[ i ] = -result[ i ];
			return result;
		}
		vec& operator+=( vec const& rhs )
		{
			for( std::size_t i = 0; i < size(); ++i )
				operator[]( i ) += rhs[ i ];
			return *this;
		}
		vec& operator-=( vec const& rhs )
		{
			for( std::size_t i = 0; i < size(); ++i )
				operator[]( i ) -= rhs[ i ];
			return *this;
		}
		template< typename U >
		vec& operator*=( U const& rhs )
		{
			for( std::size_t i = 0; i < size(); ++i )
				operator[]( i ) *= rhs;
			return *this;
		}
		template< typename U >
		vec& operator/=( U const& rhs )
		{
			for( std::size_t i = 0; i < size(); ++i )
				operator[]( i ) /= rhs;
			return *this;
		}
	};
	template< typename T >
	using vec2 = vec< T, 2 >;
	using vec2i = vec2< int >;
	using vec2u = vec2< unsigned >;
	using vec2f = vec2< float >;
	using vec2d = vec2< double >;
	template< typename T >
	using vec3 = vec< T, 3 >;
	using vec3i = vec3< int >;
	using vec3u = vec3< unsigned >;
	using vec3f = vec3< float >;
	using vec3d = vec3< double >;
	template< typename T >
	using vec4 = vec< T, 4 >;
	using vec4i = vec4< int >;
	using vec4u = vec4< unsigned >;
	using vec4f = vec4< float >;
	using vec4d = vec4< double >;

	template< typename T, std::size_t N >
	vec< T, N > operator+( vec< T, N > lhs, vec< T, N > const& rhs )
	{
		return lhs += rhs;
	}
	template< typename T, std::size_t N >
	vec< T, N > operator-( vec< T, N > lhs, vec< T, N > const& rhs )
	{
		return lhs -= rhs;
	}
	template< typename T, std::size_t N, typename U >
	vec< T, N > operator*( vec< T, N > object, U const& scalar )
	{
		return object *= scalar;
	}
	template< typename T, std::size_t N, typename U >
	vec< T, N > operator*( U const& scalar, vec< T, N > object )
	{
		return object *= scalar;
	}
	template< typename T, std::size_t N, typename U >
	vec< T, N > operator/( vec< T, N > object, U const& scalar )
	{
		return object /= scalar;
	}

	template< typename T, std::size_t N >
	T dot( vec< T, N > const& lhs, vec< T, N > const& rhs )
	{
		T result{};
		for( std::size_t i = 0; i < N; ++i )
			result += lhs[ i ] * rhs[ i ];
		return result;
	}
	template< typename T, std::size_t N >
	T normsq( vec< T, N > const& object )
	{
		return dot( object, object );
	}
	template< typename T, std::size_t N >
	T norm( vec< T, N > const& object )
	{
		return std::sqrt( normsq( object ) );
	}
	template< typename T, std::size_t N >
	void normalize( vec< T, N >& object )
	{
		object /= norm( object );
	}
	template< typename T, std::size_t N >
	vec< T, N > normalized( vec< T, N > object )
	{
		normalize( object );
		return object;
	}
	template< typename T >
	vec< T, 2 > cross( vec< T, 2 > const& object )
	{
		return
		{
			object[ 1 ],
			-object[ 0 ],
		};
	}
	template< typename T >
	vec< T, 3 > cross( vec< T, 3 > const& lhs, vec< T, 3 > const& rhs )
	{
		return
		{
			lhs[ 1 ] * rhs[ 2 ] - lhs[ 2 ] * rhs[ 1 ],
			lhs[ 2 ] * rhs[ 0 ] - lhs[ 0 ] * rhs[ 2 ],
			lhs[ 0 ] * rhs[ 1 ] - lhs[ 1 ] * rhs[ 0 ],
		};
	}

	template< typename T, std::size_t N >
	std::ostream& operator<<( std::ostream& Stream, vec< T, N > const& object )
	{
		Stream << '(';
		for( std::size_t i = 0; i < object.size(); ++i )
		{
			Stream << object[ i ];
			if( i + 1 != object.size() )
				Stream << ',';
		}
		Stream << ')';
		return Stream;
	}
}

#endif // !Vector_hxx_included
