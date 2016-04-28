
#ifndef PRECISION_TIE_POINT_HXX
#define PRECISION_TIE_POINT_HXX

#include <precision/point.hxx>

#include <list>
#include <ostream>
#include <string>
#include <vector>

namespace precision {
  /**
   * Generic Tie Point for Geometric Transformations Class support
   *
   * "Original" is the work point
   * "Transformed" is the reference point
   */
  class tie_point {
  public :
    /**
     * Point type
     */
    enum type {
      CONTROL_CHECK = 0,
      CONTROL,
      CHECK,
      NONE
    };

    /**
     * Constructor.
     *
     * @param x_y Work image point coords
     * @param u_v Reference image point coords
     * @param t Point type
     */
    tie_point( const point& x_y = precision::point(),
               const point& u_v = precision::point(),
               const type& t = CONTROL_CHECK );

    /**
     * Check if one this tie-point is smaller than another.
     *
     * This is a method needed for sorting tie-points, maybe to use a
     * tie_point as a key in map for example.
     *
     * @param rhs Righ-Hand Side of the comparison.
     * @return True if this tie-point is less.
     */
    bool operator <( const tie_point& rhs ) const {
      return x_y_ < rhs.x_y_ ||
             ( x_y_ == rhs.x_y_ && u_v_ < rhs.u_v_ );
    }

    /**
     * Check if one this tie-point is eual to another.
     *
     * @param rhs Righ-Hand Side of the comparison.
     * @return True if the tie-points are equal.
     */
    bool operator == ( const tie_point& rhs ) const {
      return x_y_ == rhs.x_y_ && u_v_ == rhs.u_v_;
    }

    /**
     * Tie Point Values setting.
     *
     * @param x_y Work  image point coords
     * @param u_v Reference image point coords
     * @param t Point type
     */
    void set( const point& x_y, const point& u_v,
              const type& t = CONTROL_CHECK );

    /**
     * Tie XY Point Values setting.
     *
     * @param x_y Original image point coords
     */
    void set_xy( const point& x_y );

    /**
     * Tie UV Point Values setting.
     *
     * @param u_v Original image point coords
     */
    void set_uv( const point& u_v );

    /**
     * Type setting.
     *
     * @param t Point type
     */
    void set_type( const type& t );

    /**
     * Return Tie Point Values.
     *
     * @param x_y Original image point coords
     * @param u_v Transformed image point coords
     */
    void get( point& x_y, point& u_v ) const;

    /**
     * Return Tie Point Values.
     *
     * @param x_y Original image point coords
     * @param u_v Transformed image point coords
     * @param t Point type
     */
    void get( point& x_y, point& u_v, type& t ) const;

    /**
     * Return XY Tie Point Values.
     *
     * @return XY Tie Point Values.
     */
    point get_xy() const;

    /**
     * Return UV Tie Point Values.
     *
     * @return UV Tie Point Values.
     */
    point get_uv() const;

    /**
     * Returns point type
     *
     * @return Point type
     */
    type get_type() const;

    /**
     * Removes duplicated tie-points in a list.
     * If work coordinates are equal, only the duplicated point is remove.
     * If work coordinates difference is greater than @p max_dif,
     * both points are removed.
     *
     * @param registered_points List of tie-points.
     * @param max_dif Maximum difference between work coordinates to maintain
     *                duplicated point.
     */
    static void remove_duplicate_points
      ( std::vector<precision::tie_point>& registered_points, double max_dif );

    /**
     * Compute origin for work and reference-points.
     *
     * @param tie_points Tie-point list.
     * @param xy0 Work-points origin.
     * @param uv0 Reference-points origin.
     */
    static void compute_origins( const std::list<tie_point>& tie_points,
                                 point& xy0,
                                 point& uv0 );

    /**
     * Change work and reference-points origin.
     *
     * @param tie_points Tie-point list to change origin.
     * @param xy0 New work-points origin.
     * @param uv0 New reference-points origin.
     */
    static void change_origins( std::list<precision::tie_point>& tie_points,
                                const point& xy0,
                                const point& uv0 );

    /**
     * Ostream operator to help debugging, so we can use
     * precision::to_string<point>().
     *
     * @param os output stream to print.
     * @param tp Tie-point to print.
     * @return output stream with data inside.
     */
    friend std::ostream& operator <<( std::ostream& os, const tie_point& tp );

  private :
    /// Original image point coords
    precision::point x_y_ ;

    /// Transformed image point coords
    precision::point u_v_ ;

    /// Point type
    type type_;
  };
}

#endif // PRECISION_TIE_POINT_HXX
