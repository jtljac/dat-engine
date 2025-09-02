/* -------------------------------------------- */
/*  Initialisation                              */
/* -------------------------------------------- */
#ifndef VEC1_INL
#define VEC1_INL

namespace DatEngine::DatMaths {
    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent>& Vector<1, TComponent>::operator=(const Vector<1, TOther>& otherVec) {
        x = static_cast<TComponent>(otherVec.x);
        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    Vector<1, TComponent>::operator TComponent() { // NOLINT(*-explicit-constructor)
        return x;
    }

    /* -------------------------------------------- */
    /*  getters                                     */
    /* -------------------------------------------- */

    template<typename TComponent>
    TComponent& Vector<1, TComponent>::operator[](const size_t pos) {
        assert(pos < 1);
        return x;
    }

    template<typename TComponent>
    const TComponent& Vector<1, TComponent>::operator[](const size_t pos) const {
        assert(pos < 1);
        return x;
    }

    /* -------------------------------------------- */
    /*  Maths                                       */
    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent> Vector<1, TComponent>::operator+(const Vector<1, TOther>& rhs) const {
        return {x + static_cast<TComponent>(rhs.x)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent> Vector<1, TComponent>::operator+(const TOther rhs) const {
        return {x + static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent>& Vector<1, TComponent>::operator+=(const Vector<1, TOther>& rhs) {
        x += static_cast<TComponent>(rhs.x);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent>& Vector<1, TComponent>::operator+=(const TOther rhs) {
        x += static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent> Vector<1, TComponent>::operator-(const Vector<1, TOther>& rhs) const {
        return {x - static_cast<TComponent>(rhs.x)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent> Vector<1, TComponent>::operator-(const TOther rhs) const {
        return {x - static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent>& Vector<1, TComponent>::operator-=(const Vector<1, TOther>& rhs) {
        x -= static_cast<TComponent>(rhs.x);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent>& Vector<1, TComponent>::operator-=(const TOther rhs) {
        x -= static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    Vector<1, TComponent> Vector<1, TComponent>::operator-() {
        return {-x};
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent> Vector<1, TComponent>::operator*(const Vector<1, TOther>& rhs) const {
        return {x * static_cast<TComponent>(rhs.x)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent> Vector<1, TComponent>::operator*(const TOther rhs) const {
        return {x * static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent>& Vector<1, TComponent>::operator*=(const Vector<1, TOther>& rhs) {
        x *= static_cast<TComponent>(rhs.x);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent>& Vector<1, TComponent>::operator*=(const TOther rhs) {
        x *= static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent> Vector<1, TComponent>::operator/(const Vector<1, TOther>& rhs) const {
        return {x / static_cast<TComponent>(rhs.x)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent> Vector<1, TComponent>::operator/(const TOther rhs) const {
        return {x / static_cast<TComponent>(rhs)};
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent>& Vector<1, TComponent>::operator/=(const Vector<1, TOther>& rhs) {
        x /= static_cast<TComponent>(rhs.x);

        return *this;
    }

    template<typename TComponent>
    template<typename TOther>
    Vector<1, TComponent>& Vector<1, TComponent>::operator/=(const TOther rhs) {
        x /= static_cast<TComponent>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    TComponent Vector<1, TComponent>::dotProduct(Vector<1, TOther> otherVec) const {
        return x * static_cast<TComponent>(otherVec.x);
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    TComponent Vector<1, TComponent>::length() const {
        return x;
    }

    template<typename TComponent>
    TComponent Vector<1, TComponent>::lengthSquared() const {
        return x * x;
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    void Vector<1, TComponent>::normalise() {
        x = 1;
    }

    template<typename TComponent>
    Vector<1, TComponent> Vector<1, TComponent>::normalised() const {
        return {1};
    }

    template<typename TComponent>
    bool Vector<1, TComponent>::isNormalised(TComponent tolerance) const {
        return std::abs(1 - lengthSquared()) < tolerance;
    }

    /* -------------------------------------------- */
    /*  Comparison                                  */
    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    bool Vector<1, TComponent>::operator==(const Vector<1, TOther>& rhs) const {
        return x == rhs.x;
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<1, TComponent>::equal(const Vector<1, TOther>& rhs, TComponent tolerance) const {
        return std::abs(x - static_cast<TComponent>(rhs.x)) < tolerance;
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<1, TComponent>::operator!=(const Vector<1, TOther>& rhs) const {
        return !operator==(rhs);
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    bool Vector<1, TComponent>::operator<(const Vector<1, TOther>& rhs) const {
        return this->x < static_cast<TComponent>(rhs.x);
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<1, TComponent>::operator>(const Vector<1, TOther>& rhs) const {
        return this->x > static_cast<TComponent>(rhs.x);
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<1, TComponent>::operator<=(const Vector<1, TOther>& rhs) const {
        return this->x <= static_cast<TComponent>(rhs.x);
    }

    template<typename TComponent>
    template<typename TOther>
    bool Vector<1, TComponent>::operator>=(const Vector<1, TOther>& rhs) const {
        return this->x >= static_cast<TComponent>(rhs.x);
    }

    /* -------------------------------------------- */

    template<typename TComponent>
    template<typename TOther>
    std::strong_ordering Vector<1, TComponent>::operator<=>(const Vector<1, TOther>& rhs) const {
        return this->x <=> static_cast<TComponent>(rhs.x);
    }
} // namespace DatEngine::DatMaths
#endif // VEC1_INL
