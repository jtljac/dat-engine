/* -------------------------------------------- */
/*  Statics                                     */
/* -------------------------------------------- */

template<typename componentType>
const Vector<3, componentType> Vector<3, componentType>::NORTH = {0, 0, 1};

template<typename componentType>
const Vector<3, componentType> Vector<3, componentType>::EAST = {1, 0, 0};

template<typename componentType>
const Vector<3, componentType> Vector<3, componentType>::SOUTH = {0, 0, -1};

template<typename componentType>
const Vector<3, componentType> Vector<3, componentType>::WEST = {-1, 0, 0};

template<typename componentType>
const Vector<3, componentType> Vector<3, componentType>::UP = {0, -1, 0};

template<typename componentType>
const Vector<3, componentType> Vector<3, componentType>::DOWN = {0, 1, 0};

/* -------------------------------------------- */
/*  Initialisation                              */
/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<3, componentType>& Vector<3, componentType>::operator=(const Vector<3, otherType>& otherVec) {
    x = static_cast<componentType>(otherVec.x);
    y = static_cast<componentType>(otherVec.y);
    z = static_cast<componentType>(otherVec.z);
    return *this;
}

/* -------------------------------------------- */
/*  Maths                                       */
/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<3, componentType> Vector<3, componentType>::operator+(const Vector<3, otherType>& rhs) const {
    return {
            x + static_cast<componentType>(rhs.x),
            y + static_cast<componentType>(rhs.y),
            z + static_cast<componentType>(rhs.z)
    };
}

template<typename componentType>
template<typename otherType>
Vector<3, componentType> Vector<3, componentType>::operator+(const otherType rhs) const {
    return {
            x + static_cast<componentType>(rhs),
            y + static_cast<componentType>(rhs),
            z + static_cast<componentType>(rhs)
    };
}

template<typename componentType>
template<typename otherType>
Vector<3, componentType>& Vector<3, componentType>::operator+=(const Vector<3, otherType>& rhs) const {
    x += static_cast<componentType>(rhs.x);
    y += static_cast<componentType>(rhs.y);
    z += static_cast<componentType>(rhs.z);

    return *this;
}

template<typename componentType>
template<typename otherType>
Vector<3, componentType>& Vector<3, componentType>::operator+=(const otherType rhs) const {
    x += static_cast<componentType>(rhs);
    y += static_cast<componentType>(rhs);
    z += static_cast<componentType>(rhs);

    return *this;
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<3, componentType> Vector<3, componentType>::operator-(const Vector<3, otherType>& rhs) const {
    return {
            x - static_cast<componentType>(rhs.x),
            y - static_cast<componentType>(rhs.y),
            z - static_cast<componentType>(rhs.z)
    };
}

template<typename componentType>
template<typename otherType>
Vector<3, componentType> Vector<3, componentType>::operator-(const otherType rhs) const {
    return {
            x - static_cast<componentType>(rhs),
            y - static_cast<componentType>(rhs),
            z - static_cast<componentType>(rhs)
    };
}

template<typename componentType>
template<typename otherType>
Vector<3, componentType>& Vector<3, componentType>::operator-=(const Vector<3, otherType>& rhs) const {
    x -= static_cast<componentType>(rhs.x);
    y -= static_cast<componentType>(rhs.y);
    z -= static_cast<componentType>(rhs.z);

    return *this;
}

template<typename componentType>
template<typename otherType>
Vector<3, componentType>& Vector<3, componentType>::operator-=(const otherType rhs) const {
    x -= static_cast<componentType>(rhs);
    y -= static_cast<componentType>(rhs);
    z -= static_cast<componentType>(rhs);

    return *this;
}

/* -------------------------------------------- */

template<typename componentType>
Vector<3, componentType> Vector<3, componentType>::operator-() {
    return {
            -x,
            -y,
            -z
    };
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<3, componentType> Vector<3, componentType>::operator*(const Vector<3, otherType>& rhs) const {
    return {
            x * static_cast<componentType>(rhs.x),
            y * static_cast<componentType>(rhs.y),
            z * static_cast<componentType>(rhs.z)
    };
}

template<typename componentType>
template<typename otherType>
Vector<3, componentType> Vector<3, componentType>::operator*(const otherType rhs) const {
    return {
            x * static_cast<componentType>(rhs),
            y * static_cast<componentType>(rhs),
            z * static_cast<componentType>(rhs)
    };
}

template<typename componentType>
template<typename otherType>
Vector<3, componentType>& Vector<3, componentType>::operator*=(const Vector<3, otherType>& rhs) const {
    x *= static_cast<componentType>(rhs.x);
    y *= static_cast<componentType>(rhs.y);
    z *= static_cast<componentType>(rhs.z);

    return *this;
}

template<typename componentType>
template<typename otherType>
Vector<3, componentType>& Vector<3, componentType>::operator*=(const otherType rhs) const {
    x *= static_cast<componentType>(rhs);
    y *= static_cast<componentType>(rhs);
    z *= static_cast<componentType>(rhs);

    return *this;
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<3, componentType> Vector<3, componentType>::operator/(const Vector<3, otherType>& rhs) const {
    return {
            x / static_cast<componentType>(rhs.x),
            y / static_cast<componentType>(rhs.y),
            z / static_cast<componentType>(rhs.z)
    };
}

template<typename componentType>
template<typename otherType>
Vector<3, componentType> Vector<3, componentType>::operator/(const otherType rhs) const {
    return {
            x / static_cast<componentType>(rhs),
            y / static_cast<componentType>(rhs),
            z / static_cast<componentType>(rhs)
    };
}

template<typename componentType>
template<typename otherType>
Vector<3, componentType>& Vector<3, componentType>::operator/=(const Vector<3, otherType>& rhs) const {
    x /= static_cast<componentType>(rhs.x);
    y /= static_cast<componentType>(rhs.y);
    z /= static_cast<componentType>(rhs.z);

    return *this;
}

template<typename componentType>
template<typename otherType>
Vector<3, componentType>& Vector<3, componentType>::operator/=(const otherType rhs) const {
    x /= static_cast<componentType>(rhs);
    y /= static_cast<componentType>(rhs);
    z /= static_cast<componentType>(rhs);

    return *this;
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
componentType Vector<3, componentType>::dotProduct(Vector<3, otherType> otherVec) const {
    return x * static_cast<componentType>(otherVec.x)
           + y * static_cast<componentType>(otherVec.y)
           + z * static_cast<componentType>(otherVec.z);
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<3, componentType> Vector<3, componentType>::crossProduct(Vector<3, otherType> otherVec) const {
    return {
            y * static_cast<componentType>(otherVec.z) - z * static_cast<componentType>(otherVec.y),
            z * static_cast<componentType>(otherVec.x) - x * static_cast<componentType>(otherVec.z),
            x * static_cast<componentType>(otherVec.y) - y * static_cast<componentType>(otherVec.x)
    };
}

/* -------------------------------------------- */

template<typename componentType>
componentType Vector<3, componentType>::length() const {
    return DatMaths::sqrt(lengthSquared());
}

template<typename componentType>
componentType Vector<3, componentType>::lengthSquared() const {
    return x * x
           + y * y
           + z * z;
}

/* -------------------------------------------- */

template<typename componentType>
void Vector<3, componentType>::normalise() {
    componentType invLength = DatMaths::invSqrt(lengthSquared());
    x *= invLength;
    y *= invLength;
    z *= invLength;
}

template<typename componentType>
Vector<3, componentType> Vector<3, componentType>::normalised() const {
    componentType invLength = DatMaths::invSqrt(lengthSquared());

    return {
            x * invLength,
            y * invLength,
            z * invLength
    };
}

/* -------------------------------------------- */

template<typename componentType>
Vector<3, componentType> Vector<3, componentType>::perpendicular(Vector<3, componentType> axis) const {
    return crossProduct(axis);
}

/* -------------------------------------------- */
/*  Comparison                                  */
/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
bool Vector<3, componentType>::operator==(const Vector<3, otherType>& rhs) const {
    return x == rhs.x
           && y == rhs.y
           && z == rhs.z;
}

template<typename componentType>
template<typename otherType>
bool Vector<3, componentType>::equal(const Vector<3, otherType>& rhs, componentType tolerance) const {
    return std::abs(x - static_cast<componentType>(rhs.x)) < tolerance
           && std::abs(y - static_cast<componentType>(rhs.y)) < tolerance
           && std::abs(z - static_cast<componentType>(rhs.z)) < tolerance;
}

template<typename componentType>
template<typename otherType>
bool Vector<3, componentType>::operator!=(const Vector<3, otherType>& rhs) const {
    return !operator==(rhs);
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
bool Vector<3, componentType>::operator<(const Vector<3, otherType>& rhs) const {
    return this->lengthSquared() < static_cast<componentType>(rhs.lengthSquared());
}

template<typename componentType>
template<typename otherType>
bool Vector<3, componentType>::operator>(const Vector<3, otherType>& rhs) const {
    return this->lengthSquared() > static_cast<componentType>(rhs.lengthSquared());
}

template<typename componentType>
template<typename otherType>
bool Vector<3, componentType>::operator<=(const Vector<3, otherType>& rhs) const {
    return this->lengthSquared() <= static_cast<componentType>(rhs.lengthSquared());
}

template<typename componentType>
template<typename otherType>
bool Vector<3, componentType>::operator>=(const Vector<3, otherType>& rhs) const {
    return this->lengthSquared() >= static_cast<componentType>(rhs.lengthSquared());
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
std::strong_ordering Vector<3, componentType>::operator<=>(const Vector<3, otherType>& rhs) const {
    return this->lengthSquared() <=> static_cast<componentType>(rhs.lengthSquared());
}