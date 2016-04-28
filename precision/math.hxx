
#ifndef PRECISION_MATH_HXX
#define PRECISION_MATH_HXX

#include <cfloat>

namespace precision {
  /**
   * Class utility to hold math routines.
   *
   * All methods are static.
   * To prevent instantiation, constructor is private.
   */
  class math {
  public:
    /**
     * Used for converting radian to degrees.
     */
    static const double RADIANS_TO_DEGREES;

    /**
     * Absolute difference between two values.
     *
     * @param lhs Left hand side of comparison.
     * @param rhs Right hand side of comparison.
     * @return The absolute diference between the two values.
     */
    static double compute_difference( double lhs, double rhs );

    /**
     * If the two values are equal.
     *
     * @param lhs Left hand side of comparison.
     * @param rhs Right hand side of comparison.
     * @param eps The difference allowed between the two values
     *            for them to still be considered equal.
     * @return True if they are equal, false otherwise.
     */
    static bool is_equal( double lhs, double rhs, double eps = FLT_EPSILON );

    /**
     * Converts a double to the number of decimal digits desired.
     *
     * Ex:
     * - truncate(1.211, 2) == 1.21
     * - truncate(1.211, 1) == 1.2
     * - truncate(1.211, 0) == 1
     * - truncate(-1.211, 2) == -1.21
     * - truncate(-1.211, 1) == -1.2
     * - truncate(-1.211, 0) == -1
     *
     * @param value Value to truncate.
     * @param digits Decimal digits to truncate to.
     * @return Truncated value.
     */
    static double truncate( double value, int digits );

    /**
     * Computes the division modulus, in double format
     *
     * @param a dividend
     * @param b divisor
     */
    static double modulus( double a, double b );

    /**
     * Computes the factorial of a number
     */
    static long double factorial( const int& n );

    /**
     * Computes the binomial number
     */
    static long binomial_number( const int& n, const int& k );

    /**
     * Computes squared distance between two points.
     *
     * @param x1 Coordinate in x axis for the first point.
     * @param y1 Coordinate in y axis for the first point.
     * @param x2 Coordinate in x axis for the second point.
     * @param y2 Coordinate in y axis for the second point.
     *
     * @return The computed squared distance.
     *
     */
    static double compute_squared_distance( const double& x1, const double& y1,
                                            const double& x2, const double& y2 );
    /**
     * Computes distance between two points.
     *
     * @param x1 Coordinate in x axis for the first point.
     * @param y1 Coordinate in y axis for the first point.
     * @param x2 Coordinate in x axis for the second point.
     * @param y2 Coordinate in y axis for the second point.
     *
     * @return The computed distance.
     *
     */
    static double compute_distance( const double& x1, const double& y1,
                                    const double& x2, const double& y2 );

    /**
     * Computes the cartesian angle for a point given its @a x and @a y
     * coordinates and set the proper quadrant.
     *
     * @param x Coordinate in x axis.
     * @param y Coordinate in y axis.
     *
     * @return The cartesian angle in degrees.
     *
     */
    static double compute_cartesian_angle( const double& x, const double& y );

    /**
     * Converts radians to degrees.
     *
     * @param rad Angle in radians.
     *
     * @return Angle in degrees.
     */
    static double transform_radians_in_degrees( const double& rad );

    /**
     * Converts degrees to radians.
     *
     * @param deg Angle in degrees.
     *
     * @return Angle in radians.
     */
    static double transform_degrees_in_radians( const double& deg );

  private:
      /// Undefined constructor.
      math();
  };
}

#endif // PRECISION_MATH_HXX
