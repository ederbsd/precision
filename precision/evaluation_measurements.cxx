
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <precision/evaluation_measurements.hxx>
#include <precision/math.hxx>
#include <precision/vector.hxx>

#include <cmath>
#include <set>

namespace precision {

  evaluation_measurements::evaluation_measurements()
  {
    /* Iniatilizing evaluation measurements */
    length_variation_ = 0.0;
    anisomorphism_    = 0.0;
    similarity_       = 0.0;
  }

  evaluation_measurements::~evaluation_measurements()
  {
  }

  bool evaluation_measurements::estimate_length_var(
    const std::list<tie_point>& tie_points )
  {
    std::set<tie_point> tp( tie_points.begin(), tie_points.end());
    std::set<tie_point>::const_iterator tpi_iterator, tpj_iterator;

    if( tp.size() < 2 ) {
      return false;
    }

    point x_y_i, u_v_i;
    point x_y_j, u_v_j;

    double den;

    /* Estimates the length variation measurement */
    length_variation_ = 0.0;
    unsigned list_size = tp.size();
    den =  math::binomial_number( list_size, 2 );
    tpi_iterator = tp.begin();
    for( unsigned i = 0; i < list_size - 1; i++ ) {
      ( *tpi_iterator ).get( x_y_i, u_v_i );

      tpj_iterator = tpi_iterator;
      for( unsigned j = ( i + 1 ); j < list_size; j++ ) {

        tpj_iterator++;

        ( *tpj_iterator ).get( x_y_j, u_v_j );

        if( x_y_i == x_y_j || u_v_i == u_v_j ) {
          return false;
        }
        precision::vector v_xy( x_y_i, x_y_j );
        precision::vector v_uv( u_v_i, u_v_j );

        length_variation_ += ( v_xy.length_vector() / v_uv.length_vector() ) /den ;
      }

      tpi_iterator++;
    }

    return true;
  }

  bool evaluation_measurements::estimate_anisomorphism(
    const std::list<tie_point>& tie_points )
  {
    std::list<tie_point> tp;

    tp = tie_points;

    if( tp.size() < 2 ) {
      return false;
    }

    std::list<tie_point>::iterator tpi_iterator, tpj_iterator;

    point x_y_i, u_v_i;
    point x_y_j, u_v_j;

    double num_1, den_1, num_2, den_2, den, sum;

    /* Estimates the anisomorphism measurement */
    unsigned list_size = tp.size();
    den = math::binomial_number( list_size, 2 );

    tpi_iterator = tp.begin();
    sum = 0.0;
    for( unsigned i = 0; i < list_size - 1; i++ ) {

      ( *tpi_iterator ).get( x_y_i, u_v_i );

      tpj_iterator = tpi_iterator;
      for( unsigned j = ( i + 1 ); j < list_size; j++ ) {

        tpj_iterator++;

        ( *tpj_iterator ).get( x_y_j, u_v_j );

        num_1 = std::fabs( x_y_i.get_x() - x_y_j.get_x() );
        den_1 = std::fabs( u_v_i.get_x() - u_v_j.get_x() );

        num_2 = std::fabs( x_y_i.get_y() - x_y_j.get_y() );
        den_2 = std::fabs( u_v_i.get_y() - u_v_j.get_y() );

        if( ( den_1 * num_2 != 0 ) ) {
          sum += ( num_1 * den_2 ) / ( den_1 * num_2 );
        } else { // Impossible to determine anisomorphism from this points.
          den--;
        }
      }

      tpi_iterator++;
    }

    anisomorphism_ = ( den )? ( sum / den ): 1.0;

    return true;
  }

  bool evaluation_measurements::estimate_similarity(
    const std::list<tie_point>& tie_points )
  {
    std::list<tie_point> tp;

    tp = tie_points;

    if( tp.size() < 3 ) {
      return false;
    }

    std::list<tie_point>::iterator tpi_iterator, tpj_iterator, tpk_iterator;

    point x_y_i, u_v_i;
    point x_y_j, u_v_j;
    point x_y_k, u_v_k;

    double den;

    /* Estimates the similarity measurement */
    similarity_ = 0.0;
    unsigned list_size = tp.size();
    den =  math::binomial_number( list_size, 3 );
    tpi_iterator = tp.begin();
    for( unsigned i = 0; i < list_size - 2; i++ ) {
      ( *tpi_iterator ).get( x_y_i, u_v_i );

      tpj_iterator = tpi_iterator;
      for( unsigned j = ( i + 1 ); j < list_size - 1; j++ ) {

        tpj_iterator++;
        ( *tpj_iterator ).get( x_y_j, u_v_j );

        tpk_iterator = tpj_iterator;
        for( unsigned k = ( j + 1 ); k < list_size; k++ ) {

          tpk_iterator++;
          ( *tpk_iterator ).get( x_y_k, u_v_k );

          precision::vector v_xy_ij( x_y_i, x_y_j );
          precision::vector v_xy_ik( x_y_i, x_y_k );

          precision::vector v_uv_ij( u_v_i, u_v_j );
          precision::vector v_uv_ik( u_v_i, u_v_k );

          similarity_ += ( v_xy_ij.angle_b_vectors( v_xy_ik ) /
                           v_uv_ij.angle_b_vectors( v_uv_ik )
                         ) / den;
        }
      }
      tpi_iterator++;
    }

    return true;
  }

  double evaluation_measurements::get_length_variation() const
  {
    return length_variation_;
  }

  double evaluation_measurements::get_anisomorphism() const
  {
    return anisomorphism_;
  }

  double evaluation_measurements::get_similarity() const
  {
    return similarity_;
  }
}
