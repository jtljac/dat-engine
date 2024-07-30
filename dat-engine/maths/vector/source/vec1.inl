/* -------------------------------------------- */
/*  Initialisation                              */
/* -------------------------------------------- */
#ifndef VEC1_INL
#define VEC1_INL

namespace DatEngine::DatMaths {
    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType>& Vector<1, componentType>::operator=(const Vector<1, otherType>& otherVec) {
        x = static_cast<componentType>(otherVec.x);
        return *this;
    }

    /* -------------------------------------------- */

    template<typename componentType>
    Vector<1, componentType>::operator componentType() { // NOLINT(*-explicit-constructor)
        return x;
    }

    /* -------------------------------------------- */
    /*  getters                                     */
    /* -------------------------------------------- */

    template<typename componentType>
    componentType& Vector<1, componentType>::operator[](const size_t pos) {
        assert(pos < 1);
        return x;
    }

    template<typename componentType>
    const componentType& Vector<1, componentType>::operator[](const size_t pos) const {
        assert(pos < 1);
        return x;
    }

    /* -------------------------------------------- */
    /*  Maths                                       */
    /* -------------------------------------------- */

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType> Vector<1, componentType>::operator+(const Vector<1, otherType>& rhs) const {
        return {x + static_cast<componentType>(rhs.x)};
    }

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType> Vector<1, componentType>::operator+(const otherType rhs) const {
        return {x + static_cast<componentType>(rhs)};
    }

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType>& Vector<1, componentType>::operator+=(const Vector<1, otherType>& rhs) {
        x += static_cast<componentType>(rhs.x);

        return *this;
    }

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType>& Vector<1, componentType>::operator+=(const otherType rhs) {
        x += static_cast<componentType>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType> Vector<1, componentType>::operator-(const Vector<1, otherType>& rhs) const {
        return {x - static_cast<componentType>(rhs.x)};
    }

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType> Vector<1, componentType>::operator-(const otherType rhs) const {
        return {x - static_cast<componentType>(rhs)};
    }

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType>& Vector<1, componentType>::operator-=(const Vector<1, otherType>& rhs) {
        x -= static_cast<componentType>(rhs.x);

        return *this;
    }

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType>& Vector<1, componentType>::operator-=(const otherType rhs) {
        x -= static_cast<componentType>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename componentType>
    Vector<1, componentType> Vector<1, componentType>::operator-() {
        return {-x};
    }

    /* -------------------------------------------- */

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType> Vector<1, componentType>::operator*(const Vector<1, otherType>& rhs) const {
        return {x * static_cast<componentType>(rhs.x)};
    }

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType> Vector<1, componentType>::operator*(const otherType rhs) const {
        return {x * static_cast<componentType>(rhs)};
    }

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType>& Vector<1, componentType>::operator*=(const Vector<1, otherType>& rhs) {
        x *= static_cast<componentType>(rhs.x);

        return *this;
    }

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType>& Vector<1, componentType>::operator*=(const otherType rhs) {
        x *= static_cast<componentType>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType> Vector<1, componentType>::operator/(const Vector<1, otherType>& rhs) const {
        return {x / static_cast<componentType>(rhs.x)};
    }

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType> Vector<1, componentType>::operator/(const otherType rhs) const {
        return {x / static_cast<componentType>(rhs)};
    }

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType>& Vector<1, componentType>::operator/=(const Vector<1, otherType>& rhs) {
        x /= static_cast<componentType>(rhs.x);

        return *this;
    }

    template<typename componentType>
    template<typename otherType>
    Vector<1, componentType>& Vector<1, componentType>::operator/=(const otherType rhs) {
        x /= static_cast<componentType>(rhs);

        return *this;
    }

    /* -------------------------------------------- */

    template<typename componentType>
    template<typename otherType>
    componentType Vector<1, componentType>::dotProduct(Vector<1, otherType> otherVec) const {
        return x * static_cast<componentType>(otherVec.x);
    }

    /* -------------------------------------------- */

    template<typename componentType>
    componentType Vector<1, componentType>::length() const {
        return x;
    }

    template<typename componentType>
    componentType Vector<1, componentType>::lengthSquared() const {
        return x * x;
    }

    /* -------------------------------------------- */

    template<typename componentType>
    void Vector<1, componentType>::normalise() {
        x = 1;
    }

    template<typename componentType>
    Vector<1, componentType> Vector<1, componentType>::normalised() const {
        return {1};
    }

    template<typename componentType>
    bool Vector<1, componentType>::isNormalised(componentType tolerance) const {
        return std::abs(1 - lengthSquared()) < tolerance;
    }

    /* -------------------------------------------- */
    /*  Comparison                                  */
    /* -------------------------------------------- */

    template<typename componentType>
    template<typename otherType>
    bool Vector<1, componentType>::operator==(const Vector<1, otherType>& rhs) const {
        return x == rhs.x;
    }

    template<typename componentType>
    template<typename otherType>
    bool Vector<1, componentType>::equal(const Vector<1, otherType>& rhs, componentType tolerance) const {
        return std::abs(x - static_cast<componentType>(rhs.x)) < tolerance;
    }

    template<typename componentType>
    template<typename otherType>
    bool Vector<1, componentType>::operator!=(const Vector<1, otherType>& rhs) const {
        return !operator==(rhs);
    }

    /* -------------------------------------------- */

    template<typename componentType>
    template<typename otherType>
    bool Vector<1, componentType>::operator<(const Vector<1, otherType>& rhs) const {
        return this->x < static_cast<componentType>(rhs.x);
    }

    template<typename componentType>
    template<typename otherType>
    bool Vector<1, componentType>::operator>(const Vector<1, otherType>& rhs) const {
        return this->x > static_cast<componentType>(rhs.x);
    }

    template<typename componentType>
    template<typename otherType>
    bool Vector<1, componentType>::operator<=(const Vector<1, otherType>& rhs) const {
        return this->x <= static_cast<componentType>(rhs.x);
    }

    template<typename componentType>
    template<typename otherType>
    bool Vector<1, componentType>::operator>=(const Vector<1, otherType>& rhs) const {
        return this->x >= static_cast<componentType>(rhs.x);
    }

    /* -------------------------------------------- */

    template<typename componentType>
    template<typename otherType>
    std::strong_ordering Vector<1, componentType>::operator<=>(const Vector<1, otherType>& rhs) const {
        return this->x <=> static_cast<componentType>(rhs.x);
    }
}
#endif // VEC1_INL