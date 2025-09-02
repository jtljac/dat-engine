/* -------------------------------------------- */
/*  Statics                                     */
/* -------------------------------------------- */
#ifndef VEC3_INL
#define VEC3_INL
namespace DatEngine::DatMaths {
    template<typename TComponent>
    const Vector<3, TComponent> Vector<3, TComponent>::NORTH = {0, 0, 1};

    template<typename TComponent>
    const Vector<3, TComponent> Vector<3, TComponent>::EAST = {1, 0, 0};

    template<typename TComponent>
    const Vector<3, TComponent> Vector<3, TComponent>::SOUTH = {0, 0, -1};

    template<typename TComponent>
    const Vector<3, TComponent> Vector<3, TComponent>::WEST = {-1, 0, 0};

    template<typename TComponent>
    const Vector<3, TComponent> Vector<3, TComponent>::UP = {0, 1, 0};

    template<typename TComponent>
    const Vector<3, TComponent> Vector<3, TComponent>::DOWN = {0, -1, 0};

    /* -------------------------------------------- */
    /*  Initialisation                              */
    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent>& Vector<3, TComponent>::operator=(const Vector<3, TOther>& otherVec) {
        x = static_cast<TComponent>(otherVec.x);
        y = static_cast<TComponent>(otherVec.y);
        z = static_cast<TComponent>(otherVec.z);
        return *this;
    }

    /* -------------------------------------------- */
    /*  getters                                     */
    /* -------------------------------------------- */

    template<typename TComponent>
    TComponent& Vector<3, TComponent>::operator[](const size_t pos) {
        assert(pos < 3);
        return reinterpret_cast<TComponent*>(&x)[pos];
    }

    template<typename TComponent>
    const TComponent& Vector<3, TComponent>::operator[](const size_t pos) const {
        assert(pos < 3);
        return reinterpret_cast<const TComponent*>(&x)[pos];
    }

    /* -------------------------------------------- */
    /*  Maths                                       */
    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent> Vector<3, TComponent>::operator+(const Vector<3, TOther>& rhs) const {
        return {x + static_cast<TComponent>(rhs.x),
                y + static_cast<TComponent>(rhs.y),
                z + static_cast<TComponent>(rhs.z)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent> Vector<3, TComponent>::operator+(const TOther rhs) const {
        return {x + static_cast<TComponent>(rhs), y + static_cast<TComponent>(rhs), z + static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent>& Vector<3, TComponent>::operator+=(const Vector<3, TOther>& rhs) {
        x += static_cast<TComponent>(rhs.x);
        y += static_cast<TComponent>(rhs.y);
        z += static_cast<TComponent>(rhs.z);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent>& Vector<3, TComponent>::operator+=(const TOther rhs) {
        x += static_cast<TComponent>(rhs);
        y += static_cast<TComponent>(rhs);
        z += static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent> Vector<3, TComponent>::operator-(const Vector<3, TOther>& rhs) const {
        return {x - static_cast<TComponent>(rhs.x),
                y - static_cast<TComponent>(rhs.y),
                z - static_cast<TComponent>(rhs.z)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent> Vector<3, TComponent>::operator-(const TOther rhs) const {
        return {x - static_cast<TComponent>(rhs), y - static_cast<TComponent>(rhs), z - static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent>& Vector<3, TComponent>::operator-=(const Vector<3, TOther>& rhs) {
        x -= static_cast<TComponent>(rhs.x);
        y -= static_cast<TComponent>(rhs.y);
        z -= static_cast<TComponent>(rhs.z);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent>& Vector<3, TComponent>::operator-=(const TOther rhs) {
        x -= static_cast<TComponent>(rhs);
        y -= static_cast<TComponent>(rhs);
        z -= static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    Vector<3, TComponent> Vector<3, TComponent>::operator-() {
        return {-x, -y, -z};
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent> Vector<3, TComponent>::operator*(const Vector<3, TOther>& rhs) const {
        return {x * static_cast<TComponent>(rhs.x),
                y * static_cast<TComponent>(rhs.y),
                z * static_cast<TComponent>(rhs.z)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent> Vector<3, TComponent>::operator*(const TOther rhs) const {
        return {x * static_cast<TComponent>(rhs), y * static_cast<TComponent>(rhs), z * static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent>& Vector<3, TComponent>::operator*=(const Vector<3, TOther>& rhs) {
        x *= static_cast<TComponent>(rhs.x);
        y *= static_cast<TComponent>(rhs.y);
        z *= static_cast<TComponent>(rhs.z);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent>& Vector<3, TComponent>::operator*=(const TOther rhs) {
        x *= static_cast<TComponent>(rhs);
        y *= static_cast<TComponent>(rhs);
        z *= static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent> Vector<3, TComponent>::operator/(const Vector<3, TOther>& rhs) const {
        return {x / static_cast<TComponent>(rhs.x),
                y / static_cast<TComponent>(rhs.y),
                z / static_cast<TComponent>(rhs.z)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent> Vector<3, TComponent>::operator/(const TOther rhs) const {
        return {x / static_cast<TComponent>(rhs), y / static_cast<TComponent>(rhs), z / static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent>& Vector<3, TComponent>::operator/=(const Vector<3, TOther>& rhs) {
        x /= static_cast<TComponent>(rhs.x);
        y /= static_cast<TComponent>(rhs.y);
        z /= static_cast<TComponent>(rhs.z);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent>& Vector<3, TComponent>::operator/=(const TOther rhs) {
        x /= static_cast<TComponent>(rhs);
        y /= static_cast<TComponent>(rhs);
        z /= static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    TComponent Vector<3, TComponent>::dotProduct(Vector<3, TOther> otherVec) const {
        return x * static_cast<TComponent>(otherVec.x) + y * static_cast<TComponent>(otherVec.y)
               + z * static_cast<TComponent>(otherVec.z);
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<3, TComponent> Vector<3, TComponent>::crossProduct(Vector<3, TOther> otherVec) const {
        return {y * static_cast<TComponent>(otherVec.z) - z * static_cast<TComponent>(otherVec.y),
                z * static_cast<TComponent>(otherVec.x) - x * static_cast<TComponent>(otherVec.z),
                x * static_cast<TComponent>(otherVec.y) - y * static_cast<TComponent>(otherVec.x)};
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    TComponent Vector<3, TComponent>::length() const {
        return DatMaths::sqrt(lengthSquared());
    }

    template<typename TComponent>
    TComponent Vector<3, TComponent>::lengthSquared() const {
        return x * x + y * y + z * z;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    void Vector<3, TComponent>::normalise() {
        TComponent invLength = DatMaths::invSqrt(lengthSquared());
        x *= invLength;
        y *= invLength;
        z *= invLength;
    }

    template<typename TComponent>
    Vector<3, TComponent> Vector<3, TComponent>::normalised() const {
        TComponent invLength = DatMaths::invSqrt(lengthSquared());

        return {x * invLength, y * invLength, z * invLength};
    }

    template<typename TComponent>
    bool Vector<3, TComponent>::isNormalised(TComponent tolerance) const {
        return std::abs(1 - lengthSquared()) < tolerance;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    Vector<3, TComponent> Vector<3, TComponent>::perpendicular(Vector<3, TComponent> axis) const {
        return crossProduct(axis);
    }

    /* -------------------------------------------- */
    /*  Comparison                                  */
    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    bool Vector<3, TComponent>::operator==(const Vector<3, TOther>& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<3, TComponent>::equal(const Vector<3, TOther>& rhs, TComponent tolerance) const {
        return std::abs(x - static_cast<TComponent>(rhs.x)) < tolerance
               && std::abs(y - static_cast<TComponent>(rhs.y)) < tolerance
               && std::abs(z - static_cast<TComponent>(rhs.z)) < tolerance;
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<3, TComponent>::operator!=(const Vector<3, TOther>& rhs) const {
        return !operator==(rhs);
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    bool Vector<3, TComponent>::operator<(const Vector<3, TOther>& rhs) const {
        return this->lengthSquared() < static_cast<TComponent>(rhs.lengthSquared());
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<3, TComponent>::operator>(const Vector<3, TOther>& rhs) const {
        return this->lengthSquared() > static_cast<TComponent>(rhs.lengthSquared());
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<3, TComponent>::operator<=(const Vector<3, TOther>& rhs) const {
        return this->lengthSquared() <= static_cast<TComponent>(rhs.lengthSquared());
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<3, TComponent>::operator>=(const Vector<3, TOther>& rhs) const {
        return this->lengthSquared() >= static_cast<TComponent>(rhs.lengthSquared());
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    std::strong_ordering Vector<3, TComponent>::operator<=>(const Vector<3, TOther>& rhs) const {
        return this->lengthSquared() <=> static_cast<TComponent>(rhs.lengthSquared());
    }
} // namespace DatEngine::DatMaths
#endif // VEC3_INL
