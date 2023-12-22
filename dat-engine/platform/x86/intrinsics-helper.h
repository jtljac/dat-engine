//
// Created by jacob on 03/09/23.
//

#pragma once
#include <emmintrin.h>

namespace DatSSE {
    using VReg4Float = __m128;

    /**
     * Create a VRegister with the values each set to the given value
     * @param value The value to set each part of the VRegister to
     * @return A new Float Vector
     */
    inline VReg4Float vSet(float value) {
        return _mm_set1_ps(value);
    }

    /**
     * Create a VRegister with the values set to the given values
     * @param a The first value of the VRegister
     * @param b The second value of the VRegister
     * @param c The third value of the VRegister
     * @param d The forth value of the VRegister
     * @return A new VRegister
     */
    inline VReg4Float vSet(float a, float b, float c, float d) {
        return _mm_set_ps(d, c, b, a);
    }

    /**
     * Select values from lhs and rhs to load into a new VRegister
     * @ref _mm_shuffle_ps
     * @ref _MM_SHUFFLE
     * @tparam index0 The index of the element in lhs to load into the first slot
     * @tparam index1 The index of the element in lhs to load into the second slot
     * @tparam index2 The index of the element in rhs to load into the third slot
     * @tparam index3 The index of the element in rhs to load into the forth slot
     * @param lhs The VRegister to get the first and second values from
     * @param rhs The VRegister to get the third and forth values from
     * @return A new VRegister
     */
    template<int index0, int index1, int index2, int index3>
    requires(index0 < 4 && index1 < 4 && index2 < 4 && index3 < 4)
    inline VReg4Float vShuffle(const VReg4Float lhs, const VReg4Float rhs) {
        return _mm_shuffle_ps(lhs, rhs, _MM_SHUFFLE(index0, index1, index2, index3));
    }

    /**
     * Create a VRegister with each value set to the value at the given index of the given VRegister
     * @tparam index The index of the value in the given register to use
     * @param otherReg The VRegister to get the value from
     * @return A new VRegister
     */
    template<int index>
    requires(index < 4)
    inline VReg4Float vSet(VReg4Float otherReg) {
        return vShuffle<index, index, index, index>(otherReg, otherReg);
    }

    /**
     * Create a copy of the given VRegister
     * @param otherReg The VRegister to copy
     * @return A new VRegister
     */
    inline VReg4Float vSet(VReg4Float otherReg) {
        return vShuffle<0, 1, 2, 3>(otherReg, otherReg);
    }

    /**
     * Add the two vectors together intrinsically
     * @ref _mm_add_ps
     * @param lhs The left hand Vector
     * @param rhs The right hand Vector
     * @return a new Float Vector
     */
    inline VReg4Float vAdd(const VReg4Float lhs, const VReg4Float rhs) {
        return _mm_add_ps(lhs, rhs);
    }

    /**
     * Multiply the two vectors together intrinsically
     * @ref _mm_mul_ps
     * @param lhs The left hand Vector
     * @param rhs The right hand Vector
     * @return a new Float Vector
     */
    inline VReg4Float vMult(const VReg4Float lhs, const VReg4Float rhs) {
        return _mm_mul_ps(lhs, rhs);
    }
}