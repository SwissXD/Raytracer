#include <cmath>

#include "Raytracer.hxx"

int main( int argc, char** argv )
{
	using namespace raytracer;

	Image image{ 1920, 1080 };
	Scene scene;
	scene.camera.Position = vec3d{ 0.0, 4.0, -8.0 };
	scene.camera.At = vec3d{ 0.0, -std::sin( deg2rad( 20 ) ), std::cos( deg2rad( 20 ) ) };
	scene.camera.Up = vec3d{ 0.0, 1.0, 0.0 };
	scene.camera.FOVX = deg2rad( 60.0 );
	scene.Objects.emplace_back( std::make_unique< Sphere >( vec3d{ -2.0, 1.0,  2.0 }, 1.0, color{ 1.0, 0.0, 0.0 } ) );
	scene.Objects.emplace_back( std::make_unique< Sphere >( vec3d{  2.0, 1.0,  2.0 }, 1.0, color{ 1.0, 1.0, 0.0 } ) );
	scene.Objects.emplace_back( std::make_unique< Sphere >( vec3d{  2.0, 1.0, -2.0 }, 1.0, color{ 0.0, 1.0, 0.0 } ) );
	scene.Objects.emplace_back( std::make_unique< Sphere >( vec3d{ -2.0, 1.0, -2.0 }, 1.0, color{ 0.0, 0.0, 1.0 } ) );
	scene.BackgroundColor = color{ 1.0, 1.0, 1.0 };
	scene.Render( image );
	const auto SfImage = image.ToSfImage();
	char const* Filename = "output.png";
	if( argc >= 2 )
		Filename = argv[ 1 ];
	SfImage.saveToFile( Filename );
}