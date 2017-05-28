#ifndef raytracer_util_hxx_included
#define raytracer_util_hxx_included

namespace raytracer {
	constexpr double pi = 3.14159265359;

	double deg2rad( double const& deg ) {
		return deg * pi / 180;
	}
	double rad2deg( double const& rad ) {
		return rad / pi * 180;
	}

	template< typename T >
	T sq( T const& x ) {
		return x * x;
	}
}

#endif // !raytracer_util_hxx_included
