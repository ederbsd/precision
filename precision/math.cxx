
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <precision/math.hxx>

#include <cmath>
#include <cassert>

namespace precision {
  /*
   * math
   */
  const double pi = std::acos( -1.0 );
  const double math::RADIANS_TO_DEGREES = 180. / pi;

  double math::compute_difference( double lhs, double rhs )
  {
    double res = 0.;

    if( lhs * rhs < 0 ) { // different signs
      res = std::fabs( lhs ) + std::fabs( rhs );
    } else {
      res = std::fabs( std::fabs( lhs ) - std::fabs( rhs ) );
    }

    assert( res >= 0 );

    return res;
  }

  bool math::is_equal( double lhs, double rhs, double eps )
  {
    assert( eps >= 0 );

    return lhs == rhs ? true : compute_difference( lhs, rhs ) <= eps;
  }

  double math::truncate( double value, int digits )
  {
    double p( std::pow( 10, digits ) );
#ifdef HAVE_TRUNC
    return ::trunc( value * p ) / p;
#else
    if( value >= 0 ) {
      return std::floor( value * p ) / p;
    } else {
      return std::ceil( value * p ) / p;
    }
#endif
  }

  double math::modulus( double a, double b )
  {
    assert( a >= 0. );
    assert( b > 0. );

    return a - b * std::floor( a / b );
  }

  long double math::factorial( const int& n )
  {
    assert( n >= 0 );

    long double factorial = 1;

    for ( unsigned i = n; i > 1; i-- ) {
      factorial *= i;
    }

    return factorial;
  }

  long math::binomial_number( const int& n, const int& k )
  {
    assert( n > 0 );
    assert( k > 0 );
    assert( n >= k );

    return long ( factorial( n ) / ( factorial( k ) * factorial( n - k ) ) );
  }

  double math::compute_squared_distance( const double& x1,
                                         const double& y1,
                                         const double& x2,
                                         const double& y2 )
  {
    double dx = x1 - x2;
    double dy = y1 - y2;
    return ( dx * dx + dy * dy );
  }

  double math::compute_distance( const double& x1,
                                 const double& y1,
                                 const double& x2,
                                 const double& y2 )
  {
    return std::sqrt( compute_squared_distance( x1, y1, x2, y2 ) );
  }

  double math::compute_cartesian_angle( const double& x,
                                        const double& y )
  {
    return ( std::atan2( y, x ) * RADIANS_TO_DEGREES );
  }

  double math::transform_radians_in_degrees( const double& rad )
  {
    return rad * RADIANS_TO_DEGREES;
  }

  double math::transform_degrees_in_radians( const double& deg )
  {
    return deg / RADIANS_TO_DEGREES;
  }
}
