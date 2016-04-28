
#ifndef PRECISION_EVALUATION_MEASUREMENTS_HXX
#define PRECISION_EVALUATION_MEASUREMENTS_HXX

#include <precision/tie_point.hxx>

#include <list>

namespace precision {
  /**
   * Evaluation Measurements Class
   */
  class evaluation_measurements {
  public:
    /**
     * Default constructor.
     */
    evaluation_measurements();

    /**
     * Default destructor.
     */
    ~evaluation_measurements();

    /**
     * Estimates the length variation of image from the given tie points
     *
     * @param tie_points User Tie Points List
     * @return true if sucess, false on error
     */
    bool estimate_length_var( const std::list<tie_point>& tie_points );

    /**
     * Estimates the anisomorphism measurement of image from the given tie points
     *
     * @param tie_points User Tie Points List
     * @return true if sucess, false on error
     */
    bool estimate_anisomorphism( const std::list<tie_point>& tie_points );

    /**
     * Estimates the similarity measurement of image from the given tie points
     *
     * @param tie_points User Tie Points List
     * @return true if sucess, false on error
     */
    bool estimate_similarity( const std::list<tie_point>& tie_points );

    /**
     * Returns the length variation measurement.
     *
     * @return length_variation_
     */
    double get_length_variation() const;

    /**
     * Returns the anisomorphism measurement.
     *
     * @return anisomorphism_
     */
    double get_anisomorphism() const;

    /**
     * Returns similarity measurement.
     *
     * @return similarity_
     */
    double get_similarity() const;

  private:
    /**
     * Length variation measurement of image
     */
    double length_variation_;

    /**
     * Anisomorphism measurement of image
     */
    double anisomorphism_;

    /**
     * Similarity measurement of image
     */
    double similarity_;
  };
}

#endif // PRECISION_EVALUATION_MEASUREMENTS_HXX
