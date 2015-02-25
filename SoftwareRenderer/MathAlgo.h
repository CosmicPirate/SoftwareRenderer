#ifndef _MATHALGO_H_
#define _MATHALGO_H_

#include <cmath>

namespace math_algo
{
	template<class T>
	inline
		typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
		almost_equal(T x, T y, int ulp)
	{
			// the machine epsilon has to be scaled to the magnitude of the values used
			// and multiplied by the desired precision in ULPs (units in the last place)
			bool eq = std::abs(x - y) < std::numeric_limits<T>::epsilon() * std::abs(x + y) * ulp
				// unless the result is subnormal
				|| std::abs(x - y) < std::numeric_limits<T>::min();
			return eq;
	}


	template <typename T>
	inline int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}


	inline double frac(double val)
	{
		return val - (long long)val;
	}


	inline double clamp(double val, double min = 0, double max = 1)
	{
		return std::fmax(min, std::fmin(val, max));
	}


	inline double interpolate(double min, double max, double grad)
	{
		return min + (max - min) * clamp(grad);
	}
}

#endif // _MATHALGO_H_