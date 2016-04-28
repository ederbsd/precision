
#ifndef PRECISION_VECTOR_HXX
#define PRECISION_VECTOR_HXX

#include <precision/point.hxx>

namespace precision {
  /**
   * Vectors Class
   */
  class vector {
  public:
    /**
     * Default constructor.
     *
     * @param p1 Vector point
     * @param p2 Vector point
     */
    vector( const point& p1, const point& p2 );

    /**
     * Default destructor.
     */
    ~vector();

    /**
     * Set vector.
     *
     * @param p1 Vector point
     * @param p2 Vector point
     */
    void set( const point& p1, const point& p2 );

    /**
     * Set vector point (p1).
     *
     * @param p1 Vector point
     */
    void set_p1( const point& p1 );

    /**
     * Set vector point (p2)
     *
     * @param p2 Vector point
     */
    void set_p2( const point& p2 );

    /**
     * Get points vector.
     *
     * @param p1 Vector point
     * @param p2 Vector point
     */
    void get( point& p1, point& p2 ) const;

    /**
     * Get vector point (p1)
     *
     * @return Vector point
     */
    point get_p1() const;

    /**
     * Get vector point (p2)
     *
     * @return Vector point
     */
    point get_p2() const;

    /**
     * Estimates the vector length.
     *
     * @return vector_length
     */
    double length_vector();

    /**
     * Estimates the angle between two vectors.
     *
     * @return angle_b_vectors
     */
    double angle_b_vectors( const vector& v );

  private:
    /**
     * Vector point
     */
    precision::point p1_;

    /**
     * Vector point
     */
    precision::point p2_;
  };
}

#endif // PRECISION_VECTOR_HXX
