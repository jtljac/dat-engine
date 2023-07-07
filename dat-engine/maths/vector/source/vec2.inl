/* -------------------------------------------- */
/*  Statics                                     */
/* -------------------------------------------- */

template<typename componentType>
const Vector<2, componentType> Vector<2, componentType>::UP = {0, -1};

template<typename componentType>
const Vector<2, componentType> Vector<2, componentType>::RIGHT = {1, 0};

template<typename componentType>
const Vector<2, componentType> Vector<2, componentType>::DOWN = {0, 1};

template<typename componentType>
const Vector<2, componentType> Vector<2, componentType>::LEFT = {-1, 0};

/* -------------------------------------------- */
/*  Initialisation                              */
/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<2, componentType>& Vector<2, componentType>::operator=(const Vector<2, otherType>& otherVec) {
    x = static_cast<componentType>(otherVec.x);
    y = static_cast<componentType>(otherVec.y);
    return *this;
}

/* -------------------------------------------- */
/*  Maths                                       */
/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<2, componentType> Vector<2, componentType>::operator+(const Vector<2, otherType>& rhs) const {
    return {
            x + static_cast<componentType>(rhs.x),
            y + static_cast<componentType>(rhs.y)
    };
}

template<typename componentType>
template<typename otherType>
Vector<2, componentType> Vector<2, componentType>::operator+(const otherType rhs) const {
    return {
            x + static_cast<componentType>(rhs),
            y + static_cast<componentType>(rhs)
    };
}

template<typename componentType>
template<typename otherType>
Vector<2, componentType>& Vector<2, componentType>::operator+=(const Vector<2, otherType>& rhs) const {
    x += static_cast<componentType>(rhs.x);
    y += static_cast<componentType>(rhs.y);

    return *this;
}

template<typename componentType>
template<typename otherType>
Vector<2, componentType>& Vector<2, componentType>::operator+=(const otherType rhs) const {
    x += static_cast<componentType>(rhs);
    y += static_cast<componentType>(rhs);

    return *this;
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<2, componentType> Vector<2, componentType>::operator-(const Vector<2, otherType>& rhs) const {
    return {
            x - static_cast<componentType>(rhs.x),
            y - static_cast<componentType>(rhs.y)
    };
}

template<typename componentType>
template<typename otherType>
Vector<2, componentType> Vector<2, componentType>::operator-(const otherType rhs) const {
    return {
            x - static_cast<componentType>(rhs),
            y - static_cast<componentType>(rhs)
    };
}

template<typename componentType>
template<typename otherType>
Vector<2, componentType>& Vector<2, componentType>::operator-=(const Vector<2, otherType>& rhs) const {
    x -= static_cast<componentType>(rhs.x);
    y -= static_cast<componentType>(rhs.y);

    return *this;
}

template<typename componentType>
template<typename otherType>
Vector<2, componentType>& Vector<2, componentType>::operator-=(const otherType rhs) const {
    x -= static_cast<componentType>(rhs);
    y -= static_cast<componentType>(rhs);

    return *this;
}

/* -------------------------------------------- */

template<typename componentType>
Vector<2, componentType> Vector<2, componentType>::operator-() {
    return {
            -x,
            -y
    };
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<2, componentType> Vector<2, componentType>::operator*(const Vector<2, otherType>& rhs) const {
    return {
            x * static_cast<componentType>(rhs.x),
            y * static_cast<componentType>(rhs.y)
    };
}

template<typename componentType>
template<typename otherType>
Vector<2, componentType> Vector<2, componentType>::operator*(const otherType rhs) const {
    return {
            x * static_cast<componentType>(rhs),
            y * static_cast<componentType>(rhs)
    };
}

template<typename componentType>
template<typename otherType>
Vector<2, componentType>& Vector<2, componentType>::operator*=(const Vector<2, otherType>& rhs) const {
    x *= static_cast<componentType>(rhs.x);
    y *= static_cast<componentType>(rhs.y);

    return *this;
}

template<typename componentType>
template<typename otherType>
Vector<2, componentType>& Vector<2, componentType>::operator*=(const otherType rhs) const {
    x *= static_cast<componentType>(rhs);
    y *= static_cast<componentType>(rhs);

    return *this;
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
Vector<2, componentType> Vector<2, componentType>::operator/(const Vector<2, otherType>& rhs) const {
    return {
            x / static_cast<componentType>(rhs.x),
            y / static_cast<componentType>(rhs.y)
    };
}

template<typename componentType>
template<typename otherType>
Vector<2, componentType> Vector<2, componentType>::operator/(const otherType rhs) const {
    return {
            x / static_cast<componentType>(rhs),
            y / static_cast<componentType>(rhs)
    };
}

template<typename componentType>
template<typename otherType>
Vector<2, componentType>& Vector<2, componentType>::operator/=(const Vector<2, otherType>& rhs) const {
    x /= static_cast<componentType>(rhs.x);
    y /= static_cast<componentType>(rhs.y);

    return *this;
}

template<typename componentType>
template<typename otherType>
Vector<2, componentType>& Vector<2, componentType>::operator/=(const otherType rhs) const {
    x /= static_cast<componentType>(rhs);
    y /= static_cast<componentType>(rhs);

    return *this;
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
componentType Vector<2, componentType>::dotProduct(Vector<2, otherType> otherVec) const {
    return x * static_cast<componentType>(otherVec.x)
           + y * static_cast<componentType>(otherVec.y);
}

/* -------------------------------------------- */

template<typename componentType>
componentType Vector<2, componentType>::length() const {
    return DatMaths::sqrt(lengthSquared());
}

template<typename componentType>
componentType Vector<2, componentType>::lengthSquared() const {
    return x * x
           + y * y;
}

/* -------------------------------------------- */

template<typename componentType>
void Vector<2, componentType>::normalise() {
    componentType invLength = DatMaths::invSqrt(lengthSquared());
    x *= invLength;
    y *= invLength;
}

template<typename componentType>
Vector<2, componentType> Vector<2, componentType>::normalised() const {
    componentType invLength = DatMaths::invSqrt(lengthSquared());

    return {
            x * invLength,
            y * invLength
    };
}

/* -------------------------------------------- */

template<typename componentType>
Vector<2, componentType> Vector<2, componentType>::perpendicular(bool clockwise) const {
    if (clockwise) {
        return {
                -y,
                x
        };
    } else {
        return {
                y,
                -x
        };
    }
}

/* -------------------------------------------- */
/*  Comparison                                  */
/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
bool Vector<2, componentType>::operator==(const Vector<2, otherType>& rhs) const {
    return x == rhs.x
           && y == rhs.y;
}

template<typename componentType>
template<typename otherType>
bool Vector<2, componentType>::equal(const Vector<2, otherType>& rhs, componentType tolerance) const {
    return std::abs(x - static_cast<componentType>(rhs.x)) < tolerance
           && std::abs(y - static_cast<componentType>(rhs.y)) < tolerance;
}

template<typename componentType>
template<typename otherType>
bool Vector<2, componentType>::operator!=(const Vector<2, otherType>& rhs) const {
    return !operator==(rhs);
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
bool Vector<2, componentType>::operator<(const Vector<2, otherType>& rhs) const {
    return this->lengthSquared() < static_cast<componentType>(rhs.lengthSquared());
}

template<typename componentType>
template<typename otherType>
bool Vector<2, componentType>::operator>(const Vector<2, otherType>& rhs) const {
    return this->lengthSquared() > static_cast<componentType>(rhs.lengthSquared());
}

template<typename componentType>
template<typename otherType>
bool Vector<2, componentType>::operator<=(const Vector<2, otherType>& rhs) const {
    return this->lengthSquared() <= static_cast<componentType>(rhs.lengthSquared());
}

template<typename componentType>
template<typename otherType>
bool Vector<2, componentType>::operator>=(const Vector<2, otherType>& rhs) const {
    return this->lengthSquared() >= static_cast<componentType>(rhs.lengthSquared());
}

/* -------------------------------------------- */

template<typename componentType>
template<typename otherType>
std::strong_ordering Vector<2, componentType>::operator<=>(const Vector<2, otherType>& rhs) const {
    return this->lengthSquared() <=> static_cast<componentType>(rhs.lengthSquared());
}