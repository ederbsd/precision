
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <precision/vector_utils.hxx>

#include <cmath>
#include <cassert>
#include <cstddef> 

namespace precision {

  void vector_utils::
  cross_product( const std::vector<double>& a,
                 const std::vector<double>& b,
                 std::vector<double>& c )
  {
    assert( a.size() == 3 );
    assert( b.size() == 3 );

    c.resize( 3 );
    c[0] = a[1]*b[2] - b[1]*a[2];
    c[1] = b[0]*a[2] - a[0]*b[2];
    c[2] = a[0]*b[1] - b[0]*a[1];
  }

  double vector_utils::length( const std::vector<double>& a )
  {
    assert( a.size() == 3 );

    return std::sqrt( a[0]*a[0] + a[1]*a[1] + a[2]*a[2] );
  }

  void vector_utils::normalize( std::vector<double>& a )
  {
    assert( a.size() == 3 );

    std::vector<double> antes( a );

    double b = length( a );

    a[0] /= b;
    a[1] /= b;
    a[2] /= b;
  }

  bool vector_utils::is_null( const std::vector<double>& a )
  {
    return length( a ) == 0;
  }

  void
  vector_utils::multiply_vector_by_scalar( const double k,
      const std::vector<double>& A,
      std::vector<double>& B )
  {
    B.resize( A.size() );

    for( size_t i = 0; i < B.size(); i++ ) {
      B[i] = A[i] * k;
    }
  }

  double
  vector_utils::multiply_vector_by_itself( const std::vector<double>& v )
  {
    double result = 0;
    for( size_t i = 0 ; i < v.size(); i++ ) {
      result += v[i] * v[i];
    }
    return result;
  }

  bool
  vector_utils::sum_vectors( const std::vector<double>& A,
                             const std::vector<double>& X,
                             std::vector<double>& B )
  {
    if( A.size() != X.size() ) {
      return false;
    }

    B.resize( A.size() );
    for( size_t i=0; i < B.size(); i++ ) {
      B[i] = A[i] + X[i];
    }

    return true;
  }
}
