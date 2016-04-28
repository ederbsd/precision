
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <precision/tie_point.hxx>

#include <cmath>

namespace precision {

  tie_point::tie_point( const point& x_y, const point& u_v,
                        const tie_point::type& t )
  {
    set( x_y, u_v, t );
  }

  void tie_point::set( const point& x_y, const point& u_v,
                       const tie_point::type& t )
  {
    x_y_ = x_y ;
    u_v_ = u_v ;
    type_ = t;
  }

  void tie_point::set_xy( const point& x_y )
  {
    x_y_ = x_y ;
  }

  void tie_point::set_uv( const point& u_v )
  {
    u_v_ = u_v ;
  }

  void tie_point::get( point& x_y, point& u_v ) const
  {
    x_y = x_y_ ;
    u_v = u_v_ ;
  }

  void tie_point::get( point& x_y, point& u_v, tie_point::type& t ) const
  {
    x_y = x_y_ ;
    u_v = u_v_ ;
    t = type_;
  }

  point tie_point::get_xy() const
  {
    return x_y_ ;
  }

  point tie_point::get_uv() const
  {
    return u_v_ ;
  }

  tie_point::type tie_point::get_type() const
  {
    return type_;
  }

  void tie_point::set_type( const type& t )
  {
    type_ = t;
  }

  void
  tie_point::remove_duplicate_points
  ( std::vector<precision::tie_point>& registered_points, double max_dif )
  {
    precision::point work_point1;
    precision::point ref_point1;
    precision::point work_point2;
    precision::point ref_point2;

    std::vector<precision::tie_point>::iterator rg_i = registered_points.begin();

    for( size_t i = 0; i + 1 < registered_points.size(); ) {
      (*rg_i).get( work_point1, ref_point1 );
      bool work_coord_equal = true;
      
      std::vector<precision::tie_point>::iterator rg_j = rg_i + 1;
      for( size_t j = i+1; j < registered_points.size();  ) {
        (*rg_j).get( work_point2, ref_point2 );
        // Testing if there are equal reference points
        if( ref_point1 == ref_point2 ) {

          // Testing if work points are equal
          if( ( fabs( work_point1.get_x() - work_point2.get_x() ) > max_dif ) ||
              ( fabs( work_point1.get_y() - work_point2.get_y() ) > max_dif ) ){
            work_coord_equal = false;
          }
          // Removing the duplicated tie point
          registered_points.erase( rg_j );
        } else {
          j++;
          rg_j++;
        }
      }
      // If work coordinates of duplicated tie points are differente,
      // both are removed
      if( !work_coord_equal ) {
        registered_points.erase( rg_i );
      } else {
        i++;
        rg_i++;
      }
    }
  }

  void tie_point::compute_origins( const std::list<tie_point>& tie_points,
                                   point& xy0,
                                   point& uv0 )
  {
    double x0 = 0.;
    double y0 = 0.;

    double u0 = 0.;
    double v0 = 0.;

    size_t n = 0;

    std::list<precision::tie_point>::const_iterator it;
    for( it = tie_points.begin(); it != tie_points.end(); it++ ) {

      if( it->get_type() == tie_point::CONTROL ||
              it->get_type() == tie_point::CONTROL_CHECK ) {

        precision::point u_v, x_y;
        it->get( x_y, u_v );

        x0 += x_y.get_x();
        y0 += x_y.get_y();

        u0 += u_v.get_x();
        v0 += u_v.get_y();

        ++n;
      }
    }

    xy0 = precision::point( x0 / n, y0 / n );
    uv0 = precision::point( u0 / n, v0 / n );
  }

  void tie_point::change_origins( std::list<precision::tie_point>& tie_points,
                                  const point& xy0,
                                  const point& uv0 )
  {
    std::list<precision::tie_point>::iterator it;
    for( it = tie_points.begin(); it != tie_points.end(); it++ ) {
      precision::point u_v, x_y;
      it->get( x_y, u_v );

      // changing work-point origin
      x_y -= xy0;

      // changing reference-point origin
      u_v -= uv0;

      it->set_xy( x_y );
      it->set_uv( u_v );
    }
  }

  std::ostream& operator <<( std::ostream& os, const tie_point& tp )
  {
    os << "Work Point:" << tp.x_y_ << " Reference Point:" << tp.u_v_;
    return os;
  }
}
