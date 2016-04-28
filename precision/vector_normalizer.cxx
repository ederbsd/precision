
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <precision/vector_normalizer.hxx>

#include <cmath>
#include <cstddef>

namespace precision {

  vector_normalizer::vector_normalizer( const std::vector<double>& v )
      :to_normalize_( v ), min_( v[0] ), max_( v[0] )

  {
    for( size_t i = 1; i < v.size(); i++ ) {
      max_ = std::max( max_, v[i] );
      min_ = std::min( min_, v[i] );
    }
  }

  std::vector<double> vector_normalizer::normalize() const
  {
    double offset = get_offset();
    double scale = get_scale();

    std::vector<double> v_normalized;

    for( size_t i=0; i < to_normalize_.size(); i++ ) {
      v_normalized.push_back( ( to_normalize_[i] - offset ) / scale );
    }

    return v_normalized;
  }

  double vector_normalizer::get_offset() const
  {
    return min_;
  }

  double vector_normalizer::get_scale() const
  {
    return ( max_ - min_ ) / 2;
  }
}
