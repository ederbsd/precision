
#ifndef PRECISION_VECTOR_NORMALIZER_HXX
#define PRECISION_VECTOR_NORMALIZER_HXX

#include <vector>

namespace precision {
  /**
   *  Vector normalizer
   */
  class vector_normalizer {
  public:
    /**
     * Default constructor
     */
    vector_normalizer( const std::vector<double>& v );

    /**
     * Normalize vector with offset and scale values.
     *
     * @return Vector normalized.
     *
     */
    std::vector<double> normalize() const;

    /**
     * Get scale value.
     *
     * @return Scale value.
     *
     */
    double get_scale() const;

    /**
     * Get offset value.
     *
     * @return Offset value.
     *
     */
    double get_offset() const;

  private:
    std::vector<double> to_normalize_; ///< vector to normalize
    double min_; ///< vector minimum element.
    double max_; ///< vector maximum element.
  };
}

#endif // PRECISION_MATRIX_NORMALIZER_HXX
