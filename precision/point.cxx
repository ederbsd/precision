
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <precision/point.hxx>

#include <cmath>
#include <ostream>

namespace precision {

  void point::round()
  {
    x_ = ::round( x_ );
    y_ = ::round( y_ );
  }

  std::ostream& operator <<( std::ostream& os, const point& pt )
  {
    std::streamsize original_precision = os.precision();
    os << std::fixed;
    os.precision( 0 );
    os << "(" << pt.x_ << "," << pt.y_ << ")";
    os << std::scientific;
    os.precision( original_precision );
    return os;
  }

  void swap( point& lhs, point& rhs )
  {
    lhs.swap( rhs );
  }

  point& point::operator -= ( const point& rhs )
  {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    return *this;
  }

  point& point::operator += ( const point& rhs )
  {
    x_ += rhs.x_;
    y_ += rhs.y_;
    return *this;
  }

  point operator - ( const point& lhs, const point& rhs )
  {
    point tmp( lhs );
    tmp -= rhs;
    return tmp;
  }

  point operator + ( const point& lhs, const point& rhs )
  {
    point tmp( lhs );
    tmp += rhs;
    return tmp;
  }  
}
