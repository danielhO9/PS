/**
 * Description: Circle structure with basic operations.
 *  Includes methods to check if a point is inside the circle.
 * Time: $O(1)$ per operation.
 */
const double EPS = 1e-9;

template<typename T>
struct Circle {
	Point<T> c; T r;
	bool inCircle(const Point<T>& p) const { return (p - c).dist() < r * (1 + EPS); }
};