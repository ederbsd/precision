
#ifndef PRECISION_POINT3D_HXX
#define PRECISION_POINT3D_HXX

#include <precision/point.hxx>

#include <algorithm>
#include <ostream>

namespace precision {
  /**
   * Three Dimension Point
   */
  class point3d: public precision::point {
  public:
    /**
     * Default Constructor.
     *
     * @param x X Axis value.
     * @param y Y Axis value.
     * @param z Z Axis value.
     * @param sigma_x X precision.
     * @param sigma_y Y precision.
     * @param sigma_z Z precision.
     */
    explicit point3d( double x = 0, double y = 0, double z = 0,
                      double sigma_x = 1.0, double sigma_y = 1.0, 
                      double sigma_z = 1.0 )
      :point( x, y, sigma_x, sigma_y ), z_( z ), sigma_z_( sigma_z ) {
    }

    /**
     * Swap this point with another.
     *
     * @param other Other point.
     */
    void swap( point3d& other ) {
      point::swap( other );

      std::swap( z_, other.z_ );
      std::swap( sigma_z_, other.sigma_z_ );
    }

    /**
     * Point value setting.
     *
     * @param x X Axis value.
     * @param y Y Axis value.
     * @param z Z Axis value.
     * @param sigma_x X precision.
     * @param sigma_y Y precision.
     * @param sigma_z Z precision.
     */
    void set( double x = 0, double y = 0, double z = 0,
              double sigma_x = 1.0, double sigma_y = 1.0,
              double sigma_z = 1.0 ) {
      point3d tmp( x, y, z, sigma_x, sigma_y, sigma_z );
      swap( tmp );
    }

    /**
     * Z Axis value setting.
     * @param z Z Axis value
     */
    void set_z( double z ) {
      z_ = z ;
    }

    /**
     * Returns the Z Axis value.
     * @return Z Axis value.
     */
    double get_z() const {
      return z_;
    }

    /**
     * Z precision setting
     * @param sigma_z Z precision
     */
    void set_sigma_z( double sigma_z ) {
      sigma_z_ = sigma_z;
    }

    /**
     * Returns the Z precision
     * @return sigma_z Z precision
     */
    double get_sigma_z() const {
      return sigma_z_;
    }

    /**
     * Return the Point values pair and the X precision and the Y precision.
     *
     * @param x X Axis value.
     * @param y Y Axis value.
     * @param z Z Axis value.
     * @param sigma_x X precision.
     * @param sigma_y Y precision.
     * @param sigma_z Z precision.
     */
    void get( double& x, double& y, double& z,
              double& sigma_x, double& sigma_y, double & sigma_z ) const {
      point::get( x, y, sigma_x, sigma_y );

      z = z_;
      sigma_z = sigma_z_;
    }

    /**
     * Return the Point values axis.
     *
     * @param x X Axis value.
     * @param y Y Axis value.
     * @param z Z Axis value.
     */
    void get_xyz( double& x, double& y, double& z ) const {
      point::get_xy( x, y );
      z = z_;
    }

    /**
     * Return precision of the X, Y and Z axis.
     *
     * @param sigma_x X precision.
     * @param sigma_y Y precision.
     * @param sigma_z Z precision.
     */
    void get_sigma_xyz( double& sigma_x, double& sigma_y,
                        double& sigma_z ) const {
      get_sigma_xy( sigma_x, sigma_y );
      sigma_z = sigma_z_;
    }

    /**
     * Rounds both x, y and z components of point
     */
    void round( void );

    bool operator == ( const point3d& p ) const {
      return( point::operator==( p ) && ( z_ == p.z_ ) );
    }

    bool operator != ( const point3d& p ) const {
      return !( *this == p );
    }

    /**
     * Check if this point is less than another.
     *
     * A point is considered less than another by comparing first
     * x and than y or comparing z axis.
     *
     * @param p Another point.
     * @return True if this point is less than @a p, false otherwise.
     */
    bool operator < ( const point3d& p ) const {
      return( ( point::operator<( p ) )
             || ( point::operator==( p ) && z_ < p.z_ ) );
      }

    /**
     * Ostream operator to help debugging, so we can use
     * precision::to_string<point3d>()
     *
     * @param os output stream to print
     * @param pt point to print
     * @return output stream with data inside
     */
    friend std::ostream& operator <<( std::ostream& os, const point3d& pt );

  private:
    double z_; ///< Z Axis value
    double sigma_z_; ///< Z precision
  };

  /**
   * Swap two points with each other.
   *
   * @param lhs Left-hand side point.
   * @param rhs Right-hand side point.
   */
  void swap( point3d& lhs, point3d& rhs );

}

#endif // PCS_POINT3D_HXX
