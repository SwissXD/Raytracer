#ifndef raytracer_Image_hxx_included
#define raytracer_Image_hxx_included

#include <vector>
#include <SFML/Graphics/Image.hpp>
#include "Color.hxx"

namespace raytracer
{
	class Image
	{
		std::size_t mWidth, mHeight;
		std::vector< color > mData;

	public:
		Image( std::size_t Width, std::size_t Height )
			: mWidth{ Width }, mHeight{ Height }, mData( Size() )
		{
		}

		std::size_t Width() const noexcept
		{
			return mWidth;
		}
		std::size_t Height() const noexcept
		{
			return mHeight;
		}
		std::size_t Size() const noexcept
		{
			return Width() * Height();
		}

		auto&& operator()( std::size_t x, std::size_t y ) const noexcept
		{
			return mData[ x + y * Width() ];
		}
		auto&& operator()( std::size_t x, std::size_t y ) noexcept
		{
			return mData[ x + y * Width() ];
		}

		sf::Image ToSfImage() const
		{
			sf::Image Result;
			Result.create( Width(), Height() );
			for( std::size_t y = 0; y < Height(); ++y)
				for( std::size_t x = 0; x < Width(); ++x)
					Result.setPixel( x, y, ( *this )( x, y ).to_sf_color() );
			return Result;
		}
	};
}

#endif // !raytracer_Image_hxx_included
