#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

template <typename T>
class Point {

public:

    static auto cross(Point a, Point b) {

        return a.x * b.y - a.y * b.x;

    }

    static auto dot(Point a, Point b) {

        return a.x * b.x + a.y * b.y;

    }

    T x = T();
    T y = T();

    explicit Point() = default;

    explicit Point(T x, T y) : x(x), y(y) {}

    auto operator-() const {

        return Point(-x, -y);

    }

    auto operator+=(Point other) {

        x += other.x;
        y += other.y;

    }

    auto operator-=(Point other) {

        x -= other.x;
        y -= other.y;

    }

    auto operator*=(T factor) {

        x *= factor;
        y *= factor;

    }

    auto operator/=(T divisor) {

        x /= divisor;
        y /= divisor;

    }

    auto norm() const {

        return Point::dot(*this, *this);

    }

    auto length() const {

        return std::hypot(x, y);

    }

    auto quadrant() const {

        if (y == 0) {
            if (x == 0) {
                return 0;
            }
            return x > 0 ? 1 : 3;
        }

        if (y > 0) {
            return x > 0 ? 1 : 2;
        }

        return x < 0 ? 3 : 4;

    }

    friend auto operator==(Point lhs, Point rhs) {

        return lhs.x == rhs.x && lhs.y == rhs.y;

    }

    friend auto operator+(Point lhs, Point rhs) {

        lhs += rhs;

        return lhs;

    }

    friend auto operator-(Point lhs, Point rhs) {

        lhs -= rhs;

        return lhs;

    }

    friend auto operator*(Point lhs, T rhs) {

        lhs *= rhs;

        return lhs;

    }

    friend auto operator/(Point lhs, T rhs) {

        lhs /= rhs;

        return lhs;

    }

    friend auto operator*(T lhs, Point rhs) {

        return rhs * lhs;

    }

};

template <typename T>
class Segment {

private:

    using PointT = Point<T>;

public:

    static auto intersects(const Segment& s_1, const Segment& s_2) {

        const auto crossSign = [](PointT v_1, PointT v_2) {
            const auto prod = PointT::cross(v_1, v_2);
            if (prod == 0) {
                return 0;
            }
            return prod > 0 ? 1 : -1;
        };

        const auto sign_1 = crossSign(s_1.b - s_1.a, s_2.a - s_1.a);
        const auto sign_2 = crossSign(s_1.b - s_1.a, s_2.b - s_1.a);

        if (sign_1 == 0 && sign_2 == 0) {
            const auto overlaps = [](T a_1, T a_2, T b_1, T b_2) {
                if (a_1 > a_2) {
                    std::swap(a_1, a_2);
                }
                if (b_1 > b_2) {
                    std::swap(b_1, b_2);
                }
                return std::max(a_1, b_1) <= std::min(a_2, b_2);
            };
            return (
                overlaps(s_1.a.x, s_1.b.x, s_2.a.x, s_2.b.x) &&
                overlaps(s_1.a.y, s_1.b.y, s_2.a.y, s_2.b.y)
            );
        }

        const auto vec = s_2.b - s_2.a;

        return sign_1 != sign_2 && crossSign(vec, s_1.a - s_2.a) != crossSign(vec, s_1.b - s_2.a);

    }

    PointT a = PointT();
    PointT b = PointT();

    explicit Segment() = default;

    explicit Segment(PointT a, PointT b) : a(a), b(b) {}

    auto contains(PointT p) const {

        const auto [min_x, max_x] = std::minmax(a.x, b.x);
        const auto [min_y, max_y] = std::minmax(a.y, b.y);

        return (
            PointT::cross(b - a, p - a) == 0 && p.x >= min_x && p.x <= max_x && p.y >= min_y &&
            p.y <= max_y
        );

    }

    auto length() const {

        return (b - a).length();

    }

    auto norm() const {

        return (b - a).norm();

    }

};

template <typename T>
class Polygon {

private:

    using PointT = Point<T>;
    using SegmentT = Segment<T>;

    std::vector<PointT> vertices = std::vector<PointT>();

public:

    int sz = 0;

    explicit Polygon() = default;

    explicit Polygon(int sz) : sz(sz) {

        vertices.resize(sz);

    }

    template <typename It>
    explicit Polygon(It first, It last) {

        while (first != last) {
            vertices.push_back(*first);
            ++first;
        }

        sz = vertices.size();

    }

    auto& operator[](int pos) {

        return vertices[pos];

    }

    auto operator[](int pos) const {

        return vertices[pos];

    }

    auto begin() {

        return std::begin(vertices);

    }

    auto begin() const {

        return std::begin(vertices);

    }

    auto contains(PointT p) const {

        auto inside = 0;

        for (auto i = 0; i < sz; ++i) {
            const auto a = vertices[i];
            const auto b = vertices[i < sz - 1 ? i + 1 : 0];
            if (SegmentT(a, b).contains(p)) {
                return 2;
            }
            inside ^= (
                (a.x < p.x && p.x <= b.x && PointT::cross(a - b, p - b) > 0) ||
                (b.x < p.x && p.x <= a.x && PointT::cross(b - a, p - a) > 0)
            );
        }

        return inside;

    }

    auto doubleArea() const {

        auto area = T();

        for (auto i = 0; i < sz; ++i) {
            area += PointT::cross(vertices[i], vertices[i < sz - 1 ? i + 1 : 0]);
        }

        area = std::abs(area);

        return area;

    }

    auto end() {

        return std::end(vertices);

    }

    auto end() const {

        return std::end(vertices);

    }

    auto perimeter() const {

        auto perim = 0.0;

        for (auto i = 0; i < sz; ++i) {
            perim += SegmentT(vertices[i], vertices[i < sz - 1 ? i + 1 : 0]).length();
        }

        return perim;

    }

    auto size() const {

        return std::size(vertices);

    }

};
