
#ifndef PRECISION_POINT_HXX
#define PRECISION_POINT_HXX

#include <algorithm>
#include <ostream>

namespace precision {
  /**
   * Generic Point for Transformations Classes
   */
  class point {
  public:
    /**
     * Default Constructor.
     *
     * @param x X Axis value.
     * @param y Y Axis value.
     * @param sigma_x X precision.
     * @param sigma_y Y precision.
     */
    explicit point( double x = 0, double y = 0,
                    double sigma_x = 1.0, double sigma_y = 1.0 )
        :x_( x ), y_( y ), sigma_x_( sigma_x ), sigma_y_( sigma_y ) {
    }

    /**
     * Destructor.
     */
    ~point() {
    }

    /**
     * Swap this point with another.
     *
     * @param other Other point.
     */
    void swap( point& other ) {
         std::swap( x_, other.x_ );
         std::swap( y_, other.y_ );
         std::swap( sigma_x_, other.sigma_x_ );
         std::swap( sigma_y_, other.sigma_y_ );
    }

    /**
     * Point value setting.
     *
     * @param x X Axis value.
     * @param y Y Axis value.
     * @param sigma_x X precision.
     * @param sigma_y Y precision.
     */
    void set( double x = 0, double y = 0,
              double sigma_x = 1.0, double sigma_y = 1.0 ) {
      point tmp( x, y, sigma_x, sigma_y );
      swap( tmp );
    }

    /**
     * X Axis value setting.
     * @param x X Axis value
     */
    void set_x( double x ) {
      x_ = x ;
    }

    /**
     * Returns the X Axis value.
     * @return X Axis value.
     */
    inline double get_x() const {
      return x_;
    }

    /**
     * X precision setting
     * @param sigma_x X precision
     */
    void set_sigma_x( double sigma_x ) {
      sigma_x_ = sigma_x;
    }

    /**
     * Returns the X precision
     * @return sigma_x X precision
     */
    inline double get_sigma_x() const {
      return sigma_x_;
    }

    /**
     * Y Axis value setting.
     * @param y Y Axix value.
     */
    void set_y( double y ) {
      y_ = y ;
    }

    /**
     * Returns the Y Axis value.
     * @return Y Axis value.
     */
    inline double get_y() const {
      return y_;
    }

    /**
     * Y precision setting
     * @param sigma_y Y precision
     */
    void set_sigma_y( double sigma_y ) {
        sigma_y_ = sigma_y;
    }

    /**
     * Returns the Y precision
     * @return sigma_y Y precision
     */
    inline double get_sigma_y() const {
      return sigma_y_;
    }

    /**
     * Return the Point values pair and the X precision and the Y precision.
     *
     * @param x X Axis value.
     * @param y Y Axis value.
     * @param sigma_x X precision.
     * @param sigma_y Y precision.
     */
    void get( double& x, double& y,
              double& sigma_x, double& sigma_y ) const {
      x = x_;
      y = y_;

      sigma_x = sigma_x_;
      sigma_y = sigma_y_;
    }

    /**
     * Return the Point values pair.
     *
     * @param x X Axis value.
     * @param y Y Axis value.
     */
    inline void get_xy( double& x, double& y ) const {
      x = x_;
      y = y_;
    }

    /**
     * Return the X precision and Y precision.
     *
     * @param sigma_x X precision.
     * @param sigma_y Y precision.
     */
    inline void get_sigma_xy( double& sigma_x, double& sigma_y ) const {
      sigma_x = sigma_x_;
      sigma_y = sigma_y_;
    }

    /**
     * Rounds both x and y components of point.
     */
    void round();

    bool operator == ( const point& p ) const {
      return( ( x_ == p.x_ ) && ( y_ == p.y_ ) );
    }

    bool operator != ( const point& p ) const {
      return !( *this == p );
    }

    /**
     * Check if this point is less than another.
     *
     * A point is considered less than another by comparing first
     * x and than y.
     *
     * @param p Another point.
     * @return True if this point is less than @a p, false otherwise.
     */
    bool operator < ( const point& p ) const {
      return x_ < p.x_ || ( x_ == p.x_ && y_ < p.y_ );
    }

    /**
     * Ostream operator to help debugging, so we can use
     * precision::to_string<point>()
     *
     * @param os output stream to print
     * @param pt point to print
     * @return output stream with data inside
     */
    friend std::ostream& operator <<( std::ostream& os, const point& pt );

    /**
     * Subtract another point to itself.
     *
     * @param rhs Right hand side.
     * @return Itself.
     */
    point& operator -= ( const point& rhs );

    /**
     * Sum another point to itself.
     *
     * @param rhs Right hand side.
     * @return Itself.
     */
    point& operator += ( const point& rhs );

  protected :
    double x_; ///< X Axis value
    double y_; ///< Y Axis value
    double sigma_x_; ///< X precision
    double sigma_y_; ///< Y precision
  };

  /**
   * Swap two points with each other.
   *
   * @param lhs Left-hand side point.
   * @param rhs Right-hand side point.
   */
  void swap( point& lhs, point& rhs );

  /**
   * Subtract two points.
   *
   * @param rhs Right hand side.
   * @param lhs Left hand side.
   * @return A point that is the subtraction of lhs by rhs.
   */
  point operator - ( const point& lhs, const point& rhs );

  /**
   * Sum two points.
   *
   * @param rhs Right hand side.
   * @param lhs Left hand side.
   * @return A point that is the sum of lhs and rhs.
   */
  point operator + ( const point& lhs, const point& rhs );

}

#endif // PRECISION_POINT_HXX
