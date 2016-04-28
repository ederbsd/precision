
#ifndef PRECISION_VECTOR_UTILS_HXX
#define PRECISION_VECTOR_UTILS_HXX

#include <vector>

namespace precision {
  /**
   *  Vector utils class
   */
  class vector_utils {
  public:
    /**
     * Computes the vector cross product of two 3-dimensional vectors
     * a and b.
     *
     * @param a 3-dimensional vector.
     * @param b 3-dimensional vector.
     * @param c Vector cross product computed.
     */
    static void cross_product( const std::vector<double>& a,
                               const std::vector<double>& b,
                               std::vector<double>& c );

    /**
     * Normalize a 3-dimensional vector.
     *
     * @param a 3-dimensional vector to be normalized.
     */
    static void normalize( std::vector<double>& a );

    /**
     * Compute the vector length.
     *
     * @param a 3-dimensional vector.
     * @return Vector length.
     */
    static double length( const std::vector<double>& a );

    /**
     * Check if vector is null.
     *
     * @param a 3-dimensional vector.
     * @return True if vector is null.
     */
    static bool is_null( const std::vector<double>& a );

    /**
     * Multiply vector by itself
     *
     * @param v Vector to multiply
     * @return Multiplication result.
     *
     */
    static double
    multiply_vector_by_itself( const std::vector<double>& v );

    /**
     * Multiply vector by scalar
     *
     * @param k Scalar to multiply
     * @param A Vector to muliply
     * @param B Result vector
     *
     */
    static void
    multiply_vector_by_scalar( const double k,
                               const std::vector<double>& A,
                               std::vector<double>& B );

    /**
     * Sum vectors A+X = B
     *
     * @param A Vector to sum
     * @param X vector to sum
     * @param B result vector
     * @return True if success, false on error
     *
     */
    static bool sum_vectors( const std::vector<double>& A,
                             const std::vector<double>& X,
                             std::vector<double>& B );

  };
}

#endif // PRECISION_VECTOR_UTILS_HXX
