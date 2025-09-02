/* -------------------------------------------- */
/*  Initialisation                              */
/* -------------------------------------------- */
#ifndef VEC4_INL
#define VEC4_INL

namespace DatEngine::DatMaths {
    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent>& Vector<4, TComponent>::operator=(const Vector<4, TOther>& otherVec) {
        x = static_cast<TComponent>(otherVec.x);
        y = static_cast<TComponent>(otherVec.y);
        z = static_cast<TComponent>(otherVec.z);
        w = static_cast<TComponent>(otherVec.w);
        return *this;
    }

    /* -------------------------------------------- */
    /*  getters                                     */
    /* -------------------------------------------- */

    template<typename TComponent>
    TComponent& Vector<4, TComponent>::operator[](const size_t pos) {
        assert(pos < 4);
        return reinterpret_cast<TComponent*>(&x)[pos];
    }

    template<typename TComponent>
    const TComponent& Vector<4, TComponent>::operator[](const size_t pos) const {
        assert(pos < 4);
        return reinterpret_cast<const TComponent*>(&x)[pos];
    }

    /* -------------------------------------------- */
    /*  Maths                                       */
    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent> Vector<4, TComponent>::operator+(const Vector<4, TOther>& rhs) const {
        return {x + static_cast<TComponent>(rhs.x),
                y + static_cast<TComponent>(rhs.y),
                z + static_cast<TComponent>(rhs.z),
                w + static_cast<TComponent>(rhs.w)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent> Vector<4, TComponent>::operator+(const TOther rhs) const {
        return {x + static_cast<TComponent>(rhs),
                y + static_cast<TComponent>(rhs),
                z + static_cast<TComponent>(rhs),
                w + static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent>& Vector<4, TComponent>::operator+=(const Vector<4, TOther>& rhs) {
        x += static_cast<TComponent>(rhs.x);
        y += static_cast<TComponent>(rhs.y);
        z += static_cast<TComponent>(rhs.z);
        w += static_cast<TComponent>(rhs.w);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent>& Vector<4, TComponent>::operator+=(const TOther rhs) {
        x += static_cast<TComponent>(rhs);
        y += static_cast<TComponent>(rhs);
        z += static_cast<TComponent>(rhs);
        w += static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent> Vector<4, TComponent>::operator-(const Vector<4, TOther>& rhs) const {
        return {x - static_cast<TComponent>(rhs.x),
                y - static_cast<TComponent>(rhs.y),
                z - static_cast<TComponent>(rhs.z),
                w - static_cast<TComponent>(rhs.w)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent> Vector<4, TComponent>::operator-(const TOther rhs) const {
        return {x - static_cast<TComponent>(rhs),
                y - static_cast<TComponent>(rhs),
                z - static_cast<TComponent>(rhs),
                w - static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent>& Vector<4, TComponent>::operator-=(const Vector<4, TOther>& rhs) {
        x -= static_cast<TComponent>(rhs.x);
        y -= static_cast<TComponent>(rhs.y);
        z -= static_cast<TComponent>(rhs.z);
        w -= static_cast<TComponent>(rhs.w);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent>& Vector<4, TComponent>::operator-=(const TOther rhs) {
        x -= static_cast<TComponent>(rhs);
        y -= static_cast<TComponent>(rhs);
        z -= static_cast<TComponent>(rhs);
        w -= static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    Vector<4, TComponent> Vector<4, TComponent>::operator-() {
        return {-x, -y, -z, -w};
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent> Vector<4, TComponent>::operator*(const Vector<4, TOther>& rhs) const {
        return {x * static_cast<TComponent>(rhs.x),
                y * static_cast<TComponent>(rhs.y),
                z * static_cast<TComponent>(rhs.z),
                w * static_cast<TComponent>(rhs.w)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent> Vector<4, TComponent>::operator*(const TOther rhs) const {
        return {x * static_cast<TComponent>(rhs),
                y * static_cast<TComponent>(rhs),
                z * static_cast<TComponent>(rhs),
                w * static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent>& Vector<4, TComponent>::operator*=(const Vector<4, TOther>& rhs) {
        x *= static_cast<TComponent>(rhs.x);
        y *= static_cast<TComponent>(rhs.y);
        z *= static_cast<TComponent>(rhs.z);
        w *= static_cast<TComponent>(rhs.w);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent>& Vector<4, TComponent>::operator*=(const TOther rhs) {
        x *= static_cast<TComponent>(rhs);
        y *= static_cast<TComponent>(rhs);
        z *= static_cast<TComponent>(rhs);
        w *= static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent> Vector<4, TComponent>::operator/(const Vector<4, TOther>& rhs) const {
        return {x / static_cast<TComponent>(rhs.x),
                y / static_cast<TComponent>(rhs.y),
                z / static_cast<TComponent>(rhs.z),
                w / static_cast<TComponent>(rhs.w)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent> Vector<4, TComponent>::operator/(const TOther rhs) const {
        return {x / static_cast<TComponent>(rhs),
                y / static_cast<TComponent>(rhs),
                z / static_cast<TComponent>(rhs),
                w / static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent>& Vector<4, TComponent>::operator/=(const Vector<4, TOther>& rhs) {
        x /= static_cast<TComponent>(rhs.x);
        y /= static_cast<TComponent>(rhs.y);
        z /= static_cast<TComponent>(rhs.z);
        w /= static_cast<TComponent>(rhs.w);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<4, TComponent>& Vector<4, TComponent>::operator/=(const TOther rhs) {
        x /= static_cast<TComponent>(rhs);
        y /= static_cast<TComponent>(rhs);
        z /= static_cast<TComponent>(rhs);
        w /= static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    TComponent Vector<4, TComponent>::dotProduct(Vector<4, TOther> otherVec) const {
        return x * static_cast<TComponent>(otherVec.x) + y * static_cast<TComponent>(otherVec.y)
               + z * static_cast<TComponent>(otherVec.z) + w * static_cast<TComponent>(otherVec.w);
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    TComponent Vector<4, TComponent>::length() const {
        return DatMaths::sqrt(lengthSquared());
    }

    template<typename TComponent>
    TComponent Vector<4, TComponent>::lengthSquared() const {
        return x * x + y * y + z * z + w * w;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    void Vector<4, TComponent>::normalise() {
        TComponent invLength = DatMaths::invSqrt(lengthSquared());
        x *= invLength;
        y *= invLength;
        z *= invLength;
        w *= invLength;
    }

    template<typename TComponent>
    Vector<4, TComponent> Vector<4, TComponent>::normalised() const {
        TComponent invLength = DatMaths::invSqrt(lengthSquared());

        return {x * invLength, y * invLength, z * invLength, w * invLength};
    }

    template<typename TComponent>
    bool Vector<4, TComponent>::isNormalised(TComponent tolerance) const {
        return std::abs(1 - lengthSquared()) < tolerance;
    }

    /* -------------------------------------------- */
    /*  Comparison                                  */
    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    bool Vector<4, TComponent>::operator==(const Vector<4, TOther>& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<4, TComponent>::equal(const Vector<4, TOther>& rhs, TComponent tolerance) const {
        return std::abs(x - static_cast<TComponent>(rhs.x)) < tolerance
               && std::abs(y - static_cast<TComponent>(rhs.y)) < tolerance
               && std::abs(z - static_cast<TComponent>(rhs.z)) < tolerance
               && std::abs(w - static_cast<TComponent>(rhs.w)) < tolerance;
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<4, TComponent>::operator!=(const Vector<4, TOther>& rhs) const {
        return !operator==(rhs);
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    bool Vector<4, TComponent>::operator<(const Vector<4, TOther>& rhs) const {
        return this->lengthSquared() < static_cast<TComponent>(rhs.lengthSquared());
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<4, TComponent>::operator>(const Vector<4, TOther>& rhs) const {
        return this->lengthSquared() > static_cast<TComponent>(rhs.lengthSquared());
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<4, TComponent>::operator<=(const Vector<4, TOther>& rhs) const {
        return this->lengthSquared() <= static_cast<TComponent>(rhs.lengthSquared());
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<4, TComponent>::operator>=(const Vector<4, TOther>& rhs) const {
        return this->lengthSquared() >= static_cast<TComponent>(rhs.lengthSquared());
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    std::strong_ordering Vector<4, TComponent>::operator<=>(const Vector<4, TOther>& rhs) const {
        return this->lengthSquared() <=> static_cast<TComponent>(rhs.lengthSquared());
    }
} // namespace DatEngine::DatMaths
#endif // VEC4_INL
