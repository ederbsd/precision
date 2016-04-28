
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <precision/vector.hxx>

#include <cmath>
#include <cassert>

namespace precision {

  vector::vector( const point& p1, const point& p2 )
  {
    assert( p1 != p2 );

    if( p1 == p2 ) {
      throw "";
    }

    p1_ = p1;
    p2_ = p2;
  }

  vector::~vector()
  {
  }

  void vector::set( const point& p1, const point& p2 )
  {
    assert( p1 != p2 );

    p1_ = p1;
    p2_ = p2;
  }

  void vector::set_p1( const point& p1 )
  {
    assert( p1 != p2_ );

    p1_ = p1;
  }

  void vector::set_p2( const point& p2 )
  {
    assert( p1_ != p2 );

    p2_ = p2;
  }

  void vector::get( point& p1, point& p2 ) const
  {
    p1 = p1_;
    p2 = p2_;
  }

  point vector::get_p1() const
  {
    return p1_;
  }

  point vector::get_p2() const
  {
    return p2_;
  }

  double vector::length_vector()
  {
    return std::sqrt( std::pow( p1_.get_x() - p2_.get_x(), 2 ) +
                      std::pow( p1_.get_y() - p2_.get_y(), 2 ) );
  }

  double vector::angle_b_vectors( const vector& v )
  {
    point p1_v, p2_v;

    v.get( p1_v, p2_v );

    double x1, y1, x2, y2;

    x1 = p2_.get_x() - p1_.get_x();
    y1 = p2_.get_y() - p1_.get_y();

    x2 = p2_v.get_x() - p1_v.get_x();
    y2 = p2_v.get_y() - p1_v.get_y();

    return std::acos( ( ( x1 * x2 ) + ( y1 * y2 ) ) /
                 ( std::sqrt( std::pow( x1, 2 ) + std::pow( y1, 2 ) ) *
                   std::sqrt( std::pow( x2, 2 ) + std::pow( y2, 2 ) )
                 )
               );
  }
}
