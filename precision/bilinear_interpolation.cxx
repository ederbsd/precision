
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <precision/bilinear_interpolation.hxx>

namespace precision {

  bilinear_interpolation::
  bilinear_interpolation( double x1, double y1,
                          double x2, double y2,
                          double q11, double q12,
                          double q21, double q22 ) :
      x1_( x1 ), y1_( y1 ),
      x2_( x2 ), y2_( y2 ),
      q11_( q11 ), q12_ ( q12 ), q21_( q21 ), q22_( q22 )
  {
    double quoc( ( x2_ - x1_ ) * ( y2_ - y1_ ) );

    a_ = q11_ / quoc;
    b_ = q21_ / quoc;
    c_ = q12_ / quoc;
    d_ = q22_ / quoc;
  }

  bilinear_interpolation::~bilinear_interpolation()
  {
  }

  double
  bilinear_interpolation::interpolate_at( double x, double y ) const
  {
    double ret = 0.;

    ret += a_ * ( x2_ - x ) * ( y2_ - y );
    ret += b_ * ( x - x1_ ) * ( y2_ - y );
    ret += c_ * ( x2_ - x ) * ( y - y1_ );
    ret += d_ * ( x - x1_ ) * ( y - y1_ );

    return ret;
  }
}
