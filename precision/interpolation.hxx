
#ifndef PRECISION_INTERPOLATION_HXX
#define PRECISION_INTERPOLATION_HXX

#include <cmath>
#include <vector>
#include <cassert>

namespace precision {
  /**
   * Perform a linear interpolation.
   *
   * Operations that must be defined:
   * IMAGE - IMAGE, should return IMAGE
   * IMAGE + IMAGE, should return IMAGE
   * DOMAIN - DOMAIN, should return DOMAIN
   * IMAGE / DOMAIN, should return IMAGE
   * IMAGE * DOMAIN, should return IMAGE
   *
   * @param x0 x-coordinate of the first point
   * @param y0 y-coordinate of the first point
   * @param x1 x-coordinate of the second point
   * @param y1 y-coordinate of the second point
   * @param x x-coordinate of the desired point
   * @return y-coordinate of the desired point
   */
  template<class _PCS_IMAGE, class _PCS_DOMAIN>
  _PCS_IMAGE linear( _PCS_DOMAIN x0, _PCS_IMAGE y0, _PCS_DOMAIN x1,
                     _PCS_IMAGE y1,  _PCS_DOMAIN x )
  {
    assert( x1 != x0 );

    _PCS_IMAGE delta, result, offset;

    delta  = (y1 - y0) / (x1 - x0);
    offset = y0 - (delta * x0);
    result = offset + (delta * x);

    return result;
  }

  /**
   * Perform a bilinear interpolation.
   * This routine uses 4 points to do its job. The points must be passed in
   * the following order in all vectors: lower-left, lower-right, upper-left
   * and upper-right. Only the four initial points in each vector will be used
   * all others will be ignored.
   *
   * Operations that must be defined:
   *  since it uses linear interpolation, the operations need there will be
   *  used here.
   *
   * @param dx x-coordinate input vector
   * @param dy y-coordinate input vector
   * @param f image input vector, aka f(x,y) vector.
   * @param x x-coordinate of the desired point
   * @param y y-coordinate of the desired point
   * @return f(x,y) of the desired point
   */
  template<class _PCS_IMAGE, class _PCS_DOMAIN_X, class _PCS_DOMAIN_Y>
  _PCS_IMAGE bilinear( std::vector<_PCS_DOMAIN_X>& dx,
                       std::vector<_PCS_DOMAIN_Y>& dy,
                       std::vector<_PCS_IMAGE>& f,
                       _PCS_DOMAIN_X x, _PCS_DOMAIN_Y y )
  {
    assert( dx.size() >= 4 );
    assert( dy.size() >= 4 );
    assert( f.size()  >= 4 );
    _PCS_IMAGE z[ 2 ], result;

    z[0]   = linear( dx[ 0 ], f[ 0 ], dx[ 1 ], f[ 1 ], x );
    z[1]   = linear( dx[ 2 ], f[ 2 ], dx[ 3 ], f[ 3 ], x );
    result = linear( dy[ 0 ], z[ 0 ], dy[ 2 ], z[ 1 ], y );

    return result;
  }

  /**
   * Perform a bilinear interpolation.
   *
   * Operations that must be defined:
   *  since it uses linear interpolation, the operations needed there will be
   *  used here.
   *
   * @param x0 x-coordinate of the lower-left corner
   * @param x1 x-coordinate of the lower-right corner
   * @param y0 y-coordinate of both lower-left and lower-right coner
   * @param f0 function value in point (x0,y0)
   * @param f1 function value in point (x1,y0)
   * @param x2 x-coordinate of the upper-left corner
   * @param x3 x-coordinate of the upper-right corner
   * @param y2 y-coordinate of both upper-left and upper-right corner
   * @param f2 function value in point (x2,y2)
   * @param f3 function value in point (x3,y2)
   * @param x x-coordinate of the desired point
   * @param y y-coordinate of the desired point
   * @return Returns f(x,y).
   */
  template<class _PCS_IMAGE, class _PCS_DOMAIN_X, class _PCS_DOMAIN_Y>
  _PCS_IMAGE bilinear( _PCS_DOMAIN_X x0, _PCS_DOMAIN_X x1, _PCS_DOMAIN_Y y0,
                       _PCS_IMAGE    f0, _PCS_IMAGE    f1,
                       _PCS_DOMAIN_X x2, _PCS_DOMAIN_X x3, _PCS_DOMAIN_Y y2,
                       _PCS_IMAGE    f2, _PCS_IMAGE    f3,
                       _PCS_DOMAIN_X x,  _PCS_DOMAIN_Y y )
  {
    _PCS_IMAGE z[ 2 ], result;

    z[0]   = linear( x0, f0, x1, f1, x );
    z[1]   = linear( x2, f2, x3, f3, x );
    result = linear( y0, z[ 0 ], y2, z[ 1 ], y );

    return result;
  }

  /**
   * Perform a third-order lagrange interpolation. There is no
   * restriction regarding the order of the points being passed.
   *
   * Operations that must be defined:
   * DOMAIN - DOMAIN, should return DOMAIN
   * DOMAIN / DOMAIN, should return type 'y', where 'y' can be DOMAIN
   * IMAGE * y, should return IMAGE
   * IMAGE + IMAGE, should return IMAGE
   *
   * ref:
   *   http://mathworld.wolfram.com/LagrangeInterpolatingPolynomial.html
   *
   * @param dx Domain
   * @param im Image, i. e., f(x)
   * @param x  x-coordinate of the point to be interpolated
   * @return Returns the interpolation of the 'x' point
   */
  template<class _PCS_IMAGE, class _PCS_DOMAIN>
  _PCS_IMAGE lagrange( std::vector<_PCS_DOMAIN> dx, std::vector<_PCS_IMAGE> im,
                       _PCS_DOMAIN x )
  {
    _PCS_IMAGE p0, p1, p2, p3;

    assert( dx.size() > 3 );
    assert( dx.size() == im.size() );

    p0 = im[ 0 ] * (x - dx[ 1 ]) / (dx[ 0 ] - dx[ 1 ]);
    p1 = im[ 1 ] * (x - dx[ 0 ]) / (dx[ 1 ] - dx[ 0 ]);
    p2 = im[ 2 ] * (x - dx[ 0 ]) / (dx[ 2 ] - dx[ 0 ]);
    p3 = im[ 3 ] * (x - dx[ 0 ]) / (dx[ 3 ] - dx[ 0 ]);
    for( size_t i = 1; i < dx.size(); i++ ) {
      if( i > 1 ) {
        p0 = p0 * ((x - dx[ i ]) / (dx[ 0 ] - dx[ i ]));
      }
      if( i != 1 ) {
        p1 = p1 * ((x - dx[ i ]) / (dx[ 1 ] - dx[ i ]));
      }
      if( i != 2 ) {
        p2 = p2 * ((x - dx[ i ]) / (dx[ 2 ] - dx[ i ]));
      }
      if( i != 3 ) {
        p3 = p3 * ((x - dx[ i ]) / (dx[ 3 ] - dx[ i ]));
      }
    }

    return p0 + p1 + p2 + p3;
  }

  /**
   * Perform a third-order lagrange interpolation on 4 points. There is no
   * restriction regarding the order of the points being passed.
   *
   * Operations that must be defined:
   * DOMAIN - DOMAIN, should return DOMAIN
   * DOMAIN / DOMAIN, should return type 'y', where 'y' can be DOMAIN
   * IMAGE * y, should return IMAGE
   * IMAGE + IMAGE, should return IMAGE
   *
   * ref:
   *   http://mathworld.wolfram.com/LagrangeInterpolatingPolynomial.html
   *
   * @param x0 Domain coordinate of the first point.
   * @param y0 Image coordinate of the first point.
   * @param x1 Domain coordinate of the second point.
   * @param y1 Image coordinate of the second point.
   * @param x2 Domain coordinate of the third point.
   * @param y2 Image coordinate of the third point.
   * @param x3 Domain coordinate of the fourth point.
   * @param y3 Image coordinate of the fourth point.
   * @param x  x-coordinate of the point to be interpolated
   * @return Returns the interpolation of the 'x' point
   */
  template<class _PCS_IMAGE, class _PCS_DOMAIN>
  _PCS_IMAGE lagrange(
    _PCS_DOMAIN x0, _PCS_IMAGE y0, _PCS_DOMAIN x1, _PCS_IMAGE y1,
    _PCS_DOMAIN x2, _PCS_IMAGE y2, _PCS_DOMAIN x3, _PCS_IMAGE y3,
    _PCS_DOMAIN x )
  {
    _PCS_IMAGE p0, p1, p2, p3;

    p0 = y0* ((x - x1)/(x0 - x1)) * ((x - x2)/(x0 - x2)) * ((x - x3)/(x0 - x3));
    p1 = y1* ((x - x0)/(x1 - x0)) * ((x - x2)/(x1 - x2)) * ((x - x3)/(x1 - x3));
    p2 = y2* ((x - x0)/(x2 - x0)) * ((x - x1)/(x2 - x1)) * ((x - x3)/(x2 - x3));
    p3 = y3* ((x - x0)/(x3 - x0)) * ((x - x1)/(x3 - x1)) * ((x - x2)/(x3 - x2));

    return p0 + p1 + p2 + p3;
  }

  /**
   * Perform a cubic interpolation.
   * The points must follow an ascending order, i. e., pt1 < pt2 < pt3 < pt4.
   *
   * Operations that must be defined:
   * DOMAIN * scalar, should return DOMAIN
   * DOMAIN + DOMAIN, should return DOMAIN
   *
   * @param distance relative distance where the points are spread of.
   * @param pt1 Value of the first point.
   * @param pt2 Value of the second point.
   * @param pt3 Value of the third point.
   * @param pt4 Value of the fourth point.
   * @return Returns the result of the cubic interpolation
   */
  template<class _PCS_DOMAIN>
  _PCS_DOMAIN cubic( double distance, _PCS_DOMAIN pt1, _PCS_DOMAIN pt2,
                     _PCS_DOMAIN pt3, _PCS_DOMAIN pt4)
  {
    static bool initialized = false;
    static double weights_[101][4]; /// caches weights in .01 intervals
    _PCS_DOMAIN result( 0 );

    if( !initialized ) {
      for( size_t i = 0 ; i < 101; ++i ) {
        double u( 0.01 * i );

        weights_[i][0] = -u * (1.0 - u) * (1.0 - u);
        weights_[i][1] = (1.0 - u) * (1.0 + u - u * u);
        weights_[i][2] = u * (1.0 + u - u * u);
        weights_[i][3] = - u * u * (1.0 - u);
      }
      initialized = true;
    }

    size_t m ( static_cast<size_t>( std::floor( ( distance - std::floor( distance ) ) *
                                           100.0 + 0.5 ) ) );

    result += static_cast<_PCS_DOMAIN>( pt1 * weights_[m][0] );
    result += static_cast<_PCS_DOMAIN>( pt2 * weights_[m][1] );
    result += static_cast<_PCS_DOMAIN>( pt3 * weights_[m][2] );
    result += static_cast<_PCS_DOMAIN>( pt4 * weights_[m][3] );

    return result;
  }

  /**
   * Perform a bicubic interpolation.
   * The desired point (x,y) must be in the region defined by the points 6, 7
   * 10 and 11.
   * The figure below shows how the points must be distributed in order to use
   * this interpolation algorithm.
   *
   *   ^
   *   |
   * yf| 13  14  15  16
   *   |
   *   |  9  10  11  12
   *   |
   *   |  5   6   7   8
   *   |
   * yo|  1   2   3   4
   *   |
   *   +----------------->
   *      xo          xf
   *
   * Operations that must be defined:
   * DOMAIN - DOMAIN, should return DOMAIN;
   * DOMAIN / DOMAIN, should return scalar
   * DOMAIN * scalar, should return DOMAIN
   * DOMAIN < DOMAIN, should return bool
   * DOMAIN > DOMAIN, should return bool
   * IMAGE - IMAGE, should return IMAGE
   * IMAGE / IMAGE, should return scalar
   * IMAGE < IMAGE, should return bool
   * IMAGE > IMAGE, should return bool
   *
   * @param dx Vector that contains x-coordinate of all 16 points.
   * @param dy Vector that contains y-coordinate of all 16 points.
   * @param f Vector that contains the value, i. e., f(x,y) of all 16 points.
   * @param x x-coordinate of the desired point
   * @param y y-coordinate of the desired point
   * @return Returns the bicubic interpolation result of point x,y.
   */
  template<class _PCS_IMAGE, class _PCS_DOMAIN>
  _PCS_IMAGE bicubic( std::vector<_PCS_DOMAIN>dx, std::vector<_PCS_DOMAIN>dy,
                      std::vector<_PCS_IMAGE>f, _PCS_DOMAIN x, _PCS_DOMAIN y )
  {
    assert( dx.size() == 16 );
    assert( dy.size() == 16 );
    assert( f.size()  == 16 );

    _PCS_DOMAIN distancex, distancey, horizontal[ 4 ];

    for( int i = 0; i < 4; i++ ) {
      assert( x >= dx[ 4 * i + 1 ] );
      assert( x <= dx[ 4 * i + 2 ] );

      distancex = (x - dx[4 * i + 2]) / (dx[4 * i + 3] - dx[4 * i + 2]);
      horizontal[ i ] = cubic( distancex, f[ 4 * i ], f[ 4 * i + 1 ],
                               f[ 4 * i + 2 ], f[ 4 * i + 3 ] );

      assert( y >= dy[ i + 4 ] );
      assert( y <= dy[ i + 8 ] );
    }

    distancey = (y - dy[ 5 ]) / (dy[ 9 ] - dy[ 5 ]);
    return( cubic( distancey, horizontal[ 0 ], horizontal[ 1 ],
                   horizontal[ 2 ], horizontal[ 3 ] ) );
  }

  /**
   * Perform a bicubic interpolation.
   * The desired point must lie in the area delimited by the points 6, 7, 10
   * and 11.
   * The sixteen points must lie in a 4x4 matrix with (xo,yo) being the lower-
   * left point, (xf,yo) the lower-right point, (xo,yf) the upper-left point
   * and (xf,yf) the upper-right point. The figure below shows this arrangement:
   *
   *   ^
   *   |
   * yf| 13  14  15  16
   *   |
   *   |  9  10  11  12
   *   |
   *   |  5   6   7   8
   *   |
   * yo|  1   2   3   4
   *   |
   *   +----------------->
   *      xo          xf
   *
   * Operations that must be defined:
   *  same previous bicubic.
   *
   * @param xo first coordinate on x-axis.
   * @param xf last coordinate on x-axis.
   * @param yo first coordinate on y-axis.
   * @param yf last coordinate on y-axis.
   * @param f1 image of the first point.
   * @param f2 image of the second point.
   * @param f3 image of the third point.
   * @param f4 image of the forth point.
   * @param f5 image of the fifth point.
   * @param f6 image of the sixth point.
   * @param f7 image of the seventh point.
   * @param f8 image of the eighth point.
   * @param f9 image of the nineth point.
   * @param f10 image of the tenth point.
   * @param f11 image of the eleventh point.
   * @param f12 image of the twelfth point.
   * @param f13 image of the thirteenth point.
   * @param f14 image of the fourteenth point.
   * @param f15 image of the fifteenth point.
   * @param f16 image of the sixteenth point.
   * @param x x-coordinate of the desired point
   * @param y y-coordinate of the desired point
   * @return the image on point (x,y)
   */
  template<class _PCS_IMAGE, class _PCS_DOMAIN>
  _PCS_IMAGE bicubic( _PCS_DOMAIN xo, _PCS_DOMAIN xf,
                      _PCS_DOMAIN yo, _PCS_DOMAIN yf,
                      _PCS_IMAGE f1,  _PCS_IMAGE f2,  _PCS_IMAGE f3,  _PCS_IMAGE f4,
                      _PCS_IMAGE f5,  _PCS_IMAGE f6,  _PCS_IMAGE f7,  _PCS_IMAGE f8,
                      _PCS_IMAGE f9,  _PCS_IMAGE f10, _PCS_IMAGE f11, _PCS_IMAGE f12,
                      _PCS_IMAGE f13, _PCS_IMAGE f14, _PCS_IMAGE f15, _PCS_IMAGE f16,
                      _PCS_DOMAIN x, _PCS_DOMAIN y )
  {
    assert( x > xo );
    assert( x < xf );

    _PCS_DOMAIN distancex, distancey, horizontal[ 4 ], delta;

    delta = (xf - xo) / 3.;
    assert( x >= xo + delta );
    assert( x <= xo + delta + delta );

    distancex = (x - (xo + delta)) / delta;
    horizontal[ 0 ] = cubic( distancex, f1,  f2,  f3,  f4  );
    horizontal[ 1 ] = cubic( distancex, f5,  f6,  f7,  f8  );
    horizontal[ 2 ] = cubic( distancex, f9,  f10, f11, f12 );
    horizontal[ 3 ] = cubic( distancex, f13, f14, f15, f16 );

    delta = (yf - yo) / 3.;
    assert( y >= yo + delta );
    assert( y <= yo + delta + delta );

    distancey = (y - (yo + delta)) / delta;
    return( cubic( distancey, horizontal[ 0 ], horizontal[ 1 ],
                   horizontal[ 2 ], horizontal[ 3 ] ) );
  }
}

#endif // PRECISION_INTERPOLATION_HXX
