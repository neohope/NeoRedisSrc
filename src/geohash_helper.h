/*
 * 经纬度Geo
 */

#ifndef GEOHASH_HELPER_HPP_
#define GEOHASH_HELPER_HPP_

#include "geohash.h"

#define GZERO(s) s.bits = s.step = 0;
#define GISZERO(s) (!s.bits && !s.step)
#define GISNOTZERO(s) (s.bits || s.step)

typedef uint64_t GeoHashFix52Bits;
typedef uint64_t GeoHashVarBits;

typedef struct {
    GeoHashBits hash;
    GeoHashArea area;
    GeoHashNeighbors neighbors;
} GeoHashRadius;

int GeoHashBitsComparator(const GeoHashBits *a, const GeoHashBits *b);
uint8_t geohashEstimateStepsByRadius(double range_meters, double lat);
int geohashBoundingBox(GeoShape *shape, double *bounds);
GeoHashRadius geohashCalculateAreasByShapeWGS84(GeoShape *shape);
GeoHashFix52Bits geohashAlign52Bits(const GeoHashBits hash);
double geohashGetDistance(double lon1d, double lat1d,
                          double lon2d, double lat2d);
int geohashGetDistanceIfInRadius(double x1, double y1,
                                 double x2, double y2, double radius,
                                 double *distance);
int geohashGetDistanceIfInRadiusWGS84(double x1, double y1, double x2,
                                      double y2, double radius,
                                      double *distance);
int geohashGetDistanceIfInRectangle(double width_m, double height_m, double x1, double y1,
                                    double x2, double y2, double *distance);

#endif /* GEOHASH_HELPER_HPP_ */
