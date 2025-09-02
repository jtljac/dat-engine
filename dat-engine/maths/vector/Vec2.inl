/* -------------------------------------------- */
/*  Statics                                     */
/* -------------------------------------------- */
#ifndef VEC2_INL
#define VEC2_INL

namespace DatEngine::DatMaths {
    template<typename TComponent>
    const Vector<2, TComponent> Vector<2, TComponent>::UP = {0, -1};

    template<typename TComponent>
    const Vector<2, TComponent> Vector<2, TComponent>::RIGHT = {1, 0};

    template<typename TComponent>
    const Vector<2, TComponent> Vector<2, TComponent>::DOWN = {0, 1};

    template<typename TComponent>
    const Vector<2, TComponent> Vector<2, TComponent>::LEFT = {-1, 0};

    /* -------------------------------------------- */
    /*  Initialisation                              */
    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent>& Vector<2, TComponent>::operator=(const Vector<2, TOther>& otherVec) {
        x = static_cast<TComponent>(otherVec.x);
        y = static_cast<TComponent>(otherVec.y);
        return *this;
    }

    /* -------------------------------------------- */
    /*  getters                                     */
    /* -------------------------------------------- */

    template<typename TComponent>
    TComponent& Vector<2, TComponent>::operator[](const size_t pos) {
        assert(pos < 2);
        return reinterpret_cast<TComponent*>(&x)[pos];
    }

    template<typename TComponent>
    const TComponent& Vector<2, TComponent>::operator[](const size_t pos) const {
        assert(pos < 2);
        return (reinterpret_cast<const TComponent*>(&x))[pos];
    }

    /* -------------------------------------------- */
    /*  Maths                                       */
    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent> Vector<2, TComponent>::operator+(const Vector<2, TOther>& rhs) const {
        return {x + static_cast<TComponent>(rhs.x), y + static_cast<TComponent>(rhs.y)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent> Vector<2, TComponent>::operator+(const TOther rhs) const {
        return {x + static_cast<TComponent>(rhs), y + static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent>& Vector<2, TComponent>::operator+=(const Vector<2, TOther>& rhs) {
        x += static_cast<TComponent>(rhs.x);
        y += static_cast<TComponent>(rhs.y);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent>& Vector<2, TComponent>::operator+=(const TOther rhs) {
        x += static_cast<TComponent>(rhs);
        y += static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent> Vector<2, TComponent>::operator-(const Vector<2, TOther>& rhs) const {
        return {x - static_cast<TComponent>(rhs.x), y - static_cast<TComponent>(rhs.y)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent> Vector<2, TComponent>::operator-(const TOther rhs) const {
        return {x - static_cast<TComponent>(rhs), y - static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent>& Vector<2, TComponent>::operator-=(const Vector<2, TOther>& rhs) {
        x -= static_cast<TComponent>(rhs.x);
        y -= static_cast<TComponent>(rhs.y);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent>& Vector<2, TComponent>::operator-=(const TOther rhs) {
        x -= static_cast<TComponent>(rhs);
        y -= static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    Vector<2, TComponent> Vector<2, TComponent>::operator-() {
        return {-x, -y};
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent> Vector<2, TComponent>::operator*(const Vector<2, TOther>& rhs) const {
        return {x * static_cast<TComponent>(rhs.x), y * static_cast<TComponent>(rhs.y)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent> Vector<2, TComponent>::operator*(const TOther rhs) const {
        return {x * static_cast<TComponent>(rhs), y * static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent>& Vector<2, TComponent>::operator*=(const Vector<2, TOther>& rhs) {
        x *= static_cast<TComponent>(rhs.x);
        y *= static_cast<TComponent>(rhs.y);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent>& Vector<2, TComponent>::operator*=(const TOther rhs) {
        x *= static_cast<TComponent>(rhs);
        y *= static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent> Vector<2, TComponent>::operator/(const Vector<2, TOther>& rhs) const {
        return {x / static_cast<TComponent>(rhs.x), y / static_cast<TComponent>(rhs.y)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent> Vector<2, TComponent>::operator/(const TOther rhs) const {
        return {x / static_cast<TComponent>(rhs), y / static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent>& Vector<2, TComponent>::operator/=(const Vector<2, TOther>& rhs) {
        x /= static_cast<TComponent>(rhs.x);
        y /= static_cast<TComponent>(rhs.y);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<2, TComponent>& Vector<2, TComponent>::operator/=(const TOther rhs) {
        x /= static_cast<TComponent>(rhs);
        y /= static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    TComponent Vector<2, TComponent>::dotProduct(Vector<2, TOther> otherVec) const {
        return x * static_cast<TComponent>(otherVec.x) + y * static_cast<TComponent>(otherVec.y);
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    TComponent Vector<2, TComponent>::length() const {
        return DatMaths::sqrt(lengthSquared());
    }

    template<typename TComponent>
    TComponent Vector<2, TComponent>::lengthSquared() const {
        return x * x + y * y;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    void Vector<2, TComponent>::normalise() {
        TComponent invLength = DatMaths::invSqrt(lengthSquared());
        x *= invLength;
        y *= invLength;
    }

    template<typename TComponent>
    Vector<2, TComponent> Vector<2, TComponent>::normalised() const {
        TComponent invLength = DatMaths::invSqrt(lengthSquared());

        return {x * invLength, y * invLength};
    }

    template<typename TComponent>
    bool Vector<2, TComponent>::isNormalised(TComponent tolerance) const {
        return std::abs(1 - lengthSquared()) < tolerance;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    Vector<2, TComponent> Vector<2, TComponent>::perpendicular(bool clockwise) const {
        if (clockwise) {
            return {-y, x};
        } else {
            return {y, -x};
        }
    }

    /* -------------------------------------------- */
    /*  Comparison                                  */
    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    bool Vector<2, TComponent>::operator==(const Vector<2, TOther>& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<2, TComponent>::equal(const Vector<2, TOther>& rhs, TComponent tolerance) const {
        return std::abs(x - static_cast<TComponent>(rhs.x)) < tolerance
               && std::abs(y - static_cast<TComponent>(rhs.y)) < tolerance;
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<2, TComponent>::operator!=(const Vector<2, TOther>& rhs) const {
        return !operator==(rhs);
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    bool Vector<2, TComponent>::operator<(const Vector<2, TOther>& rhs) const {
        return this->lengthSquared() < static_cast<TComponent>(rhs.lengthSquared());
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<2, TComponent>::operator>(const Vector<2, TOther>& rhs) const {
        return this->lengthSquared() > static_cast<TComponent>(rhs.lengthSquared());
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<2, TComponent>::operator<=(const Vector<2, TOther>& rhs) const {
        return this->lengthSquared() <= static_cast<TComponent>(rhs.lengthSquared());
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<2, TComponent>::operator>=(const Vector<2, TOther>& rhs) const {
        return this->lengthSquared() >= static_cast<TComponent>(rhs.lengthSquared());
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    std::strong_ordering Vector<2, TComponent>::operator<=>(const Vector<2, TOther>& rhs) const {
        return this->lengthSquared() <=> static_cast<TComponent>(rhs.lengthSquared());
    }
} // namespace DatEngine::DatMaths

#endif // VEC2_INL
