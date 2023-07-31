/* -------------------------------------------- */
/*  Initialisation                              */
/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<4, componentType>& Vector<4, componentType>::operator=(const Vector<4, otherType>& otherVec) {
    x = static_cast<componentType>(otherVec.x);
    y = static_cast<componentType>(otherVec.y);
    z = static_cast<componentType>(otherVec.z);
    w = static_cast<componentType>(otherVec.w);
    return *this;
}

/* -------------------------------------------- */
/*  getters                                     */
/* -------------------------------------------- */

template<typename componentType>
componentType& Vector<4, componentType>::operator[](const size_t pos) {
    assert(pos < 4);
    return (reinterpret_cast<componentType*>(&x))[pos];
}

template<typename componentType>
const componentType& Vector<4, componentType>::operator[](const size_t pos) const {
    assert(pos < 4);
    return (reinterpret_cast<const componentType*>(&x))[pos];
}

/* -------------------------------------------- */
/*  Maths                                       */
/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<4, componentType> Vector<4, componentType>::operator+(const Vector<4, otherType>& rhs) const {
    return {
            x + static_cast<componentType>(rhs.x),
            y + static_cast<componentType>(rhs.y),
            z + static_cast<componentType>(rhs.z),
            w + static_cast<componentType>(rhs.w)
    };
}

template<typename componentType>
template<typename otherType>
Vector<4, componentType> Vector<4, componentType>::operator+(const otherType rhs) const {
    return {
            x + static_cast<componentType>(rhs),
            y + static_cast<componentType>(rhs),
            z + static_cast<componentType>(rhs),
            w + static_cast<componentType>(rhs)
    };
}

template<typename componentType>
template<typename otherType>
Vector<4, componentType>& Vector<4, componentType>::operator+=(const Vector<4, otherType>& rhs) {
    x += static_cast<componentType>(rhs.x);
    y += static_cast<componentType>(rhs.y);
    z += static_cast<componentType>(rhs.z);
    w += static_cast<componentType>(rhs.w);

    return *this;
}

template<typename componentType>
template<typename otherType>
Vector<4, componentType>& Vector<4, componentType>::operator+=(const otherType rhs) {
    x += static_cast<componentType>(rhs);
    y += static_cast<componentType>(rhs);
    z += static_cast<componentType>(rhs);
    w += static_cast<componentType>(rhs);

    return *this;
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<4, componentType> Vector<4, componentType>::operator-(const Vector<4, otherType>& rhs) const {
    return {
            x - static_cast<componentType>(rhs.x),
            y - static_cast<componentType>(rhs.y),
            z - static_cast<componentType>(rhs.z),
            w - static_cast<componentType>(rhs.w)
    };
}

template<typename componentType>
template<typename otherType>
Vector<4, componentType> Vector<4, componentType>::operator-(const otherType rhs) const {
    return {
            x - static_cast<componentType>(rhs),
            y - static_cast<componentType>(rhs),
            z - static_cast<componentType>(rhs),
            w - static_cast<componentType>(rhs)
    };
}

template<typename componentType>
template<typename otherType>
Vector<4, componentType>& Vector<4, componentType>::operator-=(const Vector<4, otherType>& rhs) {
    x -= static_cast<componentType>(rhs.x);
    y -= static_cast<componentType>(rhs.y);
    z -= static_cast<componentType>(rhs.z);
    w -= static_cast<componentType>(rhs.w);

    return *this;
}

template<typename componentType>
template<typename otherType>
Vector<4, componentType>& Vector<4, componentType>::operator-=(const otherType rhs) {
    x -= static_cast<componentType>(rhs);
    y -= static_cast<componentType>(rhs);
    z -= static_cast<componentType>(rhs);
    w -= static_cast<componentType>(rhs);

    return *this;
}

/* -------------------------------------------- */

template<typename componentType>
Vector<4, componentType> Vector<4, componentType>::operator-() {
    return {
            -x,
            -y,
            -z,
            -w
    };
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<4, componentType> Vector<4, componentType>::operator*(const Vector<4, otherType>& rhs) const {
    return {
            x * static_cast<componentType>(rhs.x),
            y * static_cast<componentType>(rhs.y),
            z * static_cast<componentType>(rhs.z),
            w * static_cast<componentType>(rhs.w)
    };
}

template<typename componentType>
template<typename otherType>
Vector<4, componentType> Vector<4, componentType>::operator*(const otherType rhs) const {
    return {
            x * static_cast<componentType>(rhs),
            y * static_cast<componentType>(rhs),
            z * static_cast<componentType>(rhs),
            w * static_cast<componentType>(rhs)
    };
}

template<typename componentType>
template<typename otherType>
Vector<4, componentType>& Vector<4, componentType>::operator*=(const Vector<4, otherType>& rhs) {
    x *= static_cast<componentType>(rhs.x);
    y *= static_cast<componentType>(rhs.y);
    z *= static_cast<componentType>(rhs.z);
    w *= static_cast<componentType>(rhs.w);

    return *this;
}

template<typename componentType>
template<typename otherType>
Vector<4, componentType>& Vector<4, componentType>::operator*=(const otherType rhs) {
    x *= static_cast<componentType>(rhs);
    y *= static_cast<componentType>(rhs);
    z *= static_cast<componentType>(rhs);
    w *= static_cast<componentType>(rhs);

    return *this;
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<4, componentType> Vector<4, componentType>::operator/(const Vector<4, otherType>& rhs) const {
    return {
            x / static_cast<componentType>(rhs.x),
            y / static_cast<componentType>(rhs.y),
            z / static_cast<componentType>(rhs.z),
            w / static_cast<componentType>(rhs.w)
    };
}

template<typename componentType>
template<typename otherType>
Vector<4, componentType> Vector<4, componentType>::operator/(const otherType rhs) const {
    return {
            x / static_cast<componentType>(rhs),
            y / static_cast<componentType>(rhs),
            z / static_cast<componentType>(rhs),
            w / static_cast<componentType>(rhs)
    };
}

template<typename componentType>
template<typename otherType>
Vector<4, componentType>& Vector<4, componentType>::operator/=(const Vector<4, otherType>& rhs) {
    x /= static_cast<componentType>(rhs.x);
    y /= static_cast<componentType>(rhs.y);
    z /= static_cast<componentType>(rhs.z);
    w /= static_cast<componentType>(rhs.w);

    return *this;
}

template<typename componentType>
template<typename otherType>
Vector<4, componentType>& Vector<4, componentType>::operator/=(const otherType rhs) {
    x /= static_cast<componentType>(rhs);
    y /= static_cast<componentType>(rhs);
    z /= static_cast<componentType>(rhs);
    w /= static_cast<componentType>(rhs);

    return *this;
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
componentType Vector<4, componentType>::dotProduct(Vector<4, otherType> otherVec) const {
    return x * static_cast<componentType>(otherVec.x)
           + y * static_cast<componentType>(otherVec.y)
           + z * static_cast<componentType>(otherVec.z)
           + w * static_cast<componentType>(otherVec.w);
}

/* -------------------------------------------- */

template<typename componentType>
componentType Vector<4, componentType>::length() const {
    return DatMaths::sqrt(lengthSquared());
}

template<typename componentType>
componentType Vector<4, componentType>::lengthSquared() const {
    return x * x
           + y * y
           + z * z
           + w * w;
}

/* -------------------------------------------- */

template<typename componentType>
void Vector<4, componentType>::normalise() {
    componentType invLength = DatMaths::invSqrt(lengthSquared());
    x *= invLength;
    y *= invLength;
    z *= invLength;
    w *= invLength;
}

template<typename componentType>
Vector<4, componentType> Vector<4, componentType>::normalised() const {
    componentType invLength = DatMaths::invSqrt(lengthSquared());

    return {
            x * invLength,
            y * invLength,
            z * invLength,
            w * invLength
    };
}

template<typename componentType>
bool Vector<4, componentType>::isNormalised(componentType tolerance) const {
    return std::abs(1 - lengthSquared()) < tolerance;
}

/* -------------------------------------------- */
/*  Comparison                                  */
/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
bool Vector<4, componentType>::operator==(const Vector<4, otherType>& rhs) const {
    return x == rhs.x
           && y == rhs.y
           && z == rhs.z
           && w == rhs.w;
}

template<typename componentType>
template<typename otherType>
bool Vector<4, componentType>::equal(const Vector<4, otherType>& rhs, componentType tolerance) const {
    return std::abs(x - static_cast<componentType>(rhs.x)) < tolerance
           && std::abs(y - static_cast<componentType>(rhs.y)) < tolerance
           && std::abs(z - static_cast<componentType>(rhs.z)) < tolerance
           && std::abs(w - static_cast<componentType>(rhs.w)) < tolerance;
}

template<typename componentType>
template<typename otherType>
bool Vector<4, componentType>::operator!=(const Vector<4, otherType>& rhs) const {
    return !operator==(rhs);
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
bool Vector<4, componentType>::operator<(const Vector<4, otherType>& rhs) const {
    return this->lengthSquared() < static_cast<componentType>(rhs.lengthSquared());
}

template<typename componentType>
template<typename otherType>
bool Vector<4, componentType>::operator>(const Vector<4, otherType>& rhs) const {
    return this->lengthSquared() > static_cast<componentType>(rhs.lengthSquared());
}

template<typename componentType>
template<typename otherType>
bool Vector<4, componentType>::operator<=(const Vector<4, otherType>& rhs) const {
    return this->lengthSquared() <= static_cast<componentType>(rhs.lengthSquared());
}

template<typename componentType>
template<typename otherType>
bool Vector<4, componentType>::operator>=(const Vector<4, otherType>& rhs) const {
    return this->lengthSquared() >= static_cast<componentType>(rhs.lengthSquared());
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
std::strong_ordering Vector<4, componentType>::operator<=>(const Vector<4, otherType>& rhs) const {
    return this->lengthSquared() <=> static_cast<componentType>(rhs.lengthSquared());
}