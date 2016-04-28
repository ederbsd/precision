
#ifndef PRECISION_BILINEAR_INTERPOLATION_HXX
#define PRECISION_BILINEAR_INTERPOLATION_HXX

#include <cmath>

namespace precision {
  /**
   * Translation Transformation Class
   */
  class bilinear_interpolation {
  public:
    /**
     * Default constructor.
     *
     * We need the function (f) value at four points. We assume
     * that x is the horizontal axis, and y is the vertical axis.
     * (x1,y1) is the upper left point
     *
     * @param x1 x coordinate for upper left coordinate
     * @param y1 y coordinate for upper left coordinate
     * @param x2 x coordinate for lower right coordinate
     * @param y2 y coordinate for lower right coordinate
     * @param q11 function value at (x1,y1)
     * @param q12 function value at (x1,y2)
     * @param q21 function value at (x2,y1)
     * @param q22 function value at (x2,y2)
     */
    bilinear_interpolation( double x1, double y1,
                            double x2, double y2,
                            double q11,
                            double q12,
                            double q21,
                            double q22 );

    /**
     * Default destructor.
     */
    ~bilinear_interpolation();

    /**
     * Computes the interpolated value
     *
     * @param x x coordinate for the interpolated value
     * @param y y coordinate for the interpolated value
     */
    double interpolate_at( double x, double y ) const;

  protected:
    /// x coordinate for upper left coordinate
    double x1_;

    /// y coordinate for upper left coordinate
    double y1_;

    /// x coordinate for lower right coordinate
    double x2_;

    /// y coordinate for lower right coordinate
    double y2_;

    /// function value at (x1,y1)
    double q11_;

    /// function value at (x1,y2)
    double q12_;

    /// function value at (x2,y1)
    double q21_;

    /// function value at (x2,y2)
    double q22_;

    /// Bilinear coefficient
    double a_;

    /// Bilinear coefficient
    double b_;

    /// Bilinear coefficient
    double c_;

    /// Bilinear coefficient
    double d_;
  };
}

#endif // PRECISION_BILINEAR_INTERPOLATION_HXX
