
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <precision/point3d.hxx>
#include <precision/point.hxx>

#include <cmath>
#include <ostream>

namespace precision {

  void point3d::round( void )
  {
    point::round();
    z_ = ::round( z_ );
  }

  std::ostream& operator <<( std::ostream& os, const point3d& pt )
  {
    std::streamsize original_precision = os.precision();
    std::ios_base::fmtflags original_flag = os.flags();
    os << std::fixed;
    os.precision( 0 );
    os << "(" << pt.x_ << "," << pt.y_ << "," << pt.z_ <<")";
    os << std::scientific;
    os.precision( original_precision );
    os.setf( original_flag );
    return os;
  }

  void swap( point3d& lhs, point3d& rhs )
  {
    lhs.swap( rhs );
  }
}
