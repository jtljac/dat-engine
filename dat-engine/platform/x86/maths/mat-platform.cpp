//
// Created by jacob on 03/09/23.
//

#include <maths/matrix/mat-platform.h>
#include <maths/matrix/mat4.h>

#include "../intrinsics-helper.h"

namespace DatSSE {
    DatMaths::Matrix<4, 4, float> matrixMultiply(const DatMaths::Matrix<4, 4, float>& lhs, const DatMaths::Matrix<4, 4, float>& rhs) {
        const VReg4Float* lhsV = (const VReg4Float*)&lhs;
        const VReg4Float* rhsV = (const VReg4Float*)&rhs;
        DatMaths::Matrix<4, 4, float> result;
        VReg4Float* resultV = (VReg4Float*)&result;

        /*
         * This one's pretty weird
         * Remember, column major
         *
         * For each column of the new matrix, we grab each value from the same column in the rhs matrix, and multiply it
         * by each column in the lhs matrix.
         *
         * This calculates whole columns in 4 steps
         */

        resultV[0] = vMult(lhsV[0], vSet<0>(rhsV[0]));
        resultV[0] = vAdd(vMult(lhsV[1], vSet<1>(rhsV[0])), resultV[0]);
        resultV[0] = vAdd(vMult(lhsV[2], vSet<2>(rhsV[0])), resultV[0]);
        resultV[0] = vAdd(vMult(lhsV[3], vSet<3>(rhsV[0])), resultV[0]);

        resultV[1] = vMult(lhsV[0], vSet<0>(rhsV[1]));
        resultV[1] = vAdd(vMult(lhsV[1], vSet<1>(rhsV[1])), resultV[1]);
        resultV[1] = vAdd(vMult(lhsV[2], vSet<2>(rhsV[1])), resultV[1]);
        resultV[1] = vAdd(vMult(lhsV[3], vSet<3>(rhsV[1])), resultV[1]);

        resultV[2] = vMult(lhsV[0], vSet<0>(rhsV[2]));
        resultV[2] = vAdd(vMult(lhsV[1], vSet<1>(rhsV[2])), resultV[2]);
        resultV[2] = vAdd(vMult(lhsV[2], vSet<2>(rhsV[2])), resultV[2]);
        resultV[2] = vAdd(vMult(lhsV[3], vSet<3>(rhsV[2])), resultV[2]);

        resultV[3] = vMult(lhsV[0], vSet<0>(rhsV[3]));
        resultV[3] = vAdd(vMult(lhsV[1], vSet<1>(rhsV[3])), resultV[3]);
        resultV[3] = vAdd(vMult(lhsV[2], vSet<2>(rhsV[3])), resultV[3]);
        resultV[3] = vAdd(vMult(lhsV[3], vSet<3>(rhsV[3])), resultV[3]);

        return result;
    }

    void matrixMultiplyInPlace(DatMaths::Matrix<4, 4, float>& lhs, const DatMaths::Matrix<4, 4, float>& rhs) {
        VReg4Float* lhsV = (VReg4Float*)&lhs;
        const VReg4Float* rhsV = (const VReg4Float*)&rhs;

        /*
         * Values are deposited into temporary registers as so lhs isn't disturbed during the multiplication
         */
        VReg4Float r0, r1, r2, r3;

        r0 = vMult(lhsV[0], vSet<0>(rhsV[0]));
        r0 = vAdd(vMult(lhsV[1], vSet<1>(rhsV[0])), r0);
        r0 = vAdd(vMult(lhsV[2], vSet<2>(rhsV[0])), r0);
        r0 = vAdd(vMult(lhsV[3], vSet<3>(rhsV[0])), r0);

        r1 = vMult(lhsV[0], vSet<0>(rhsV[1]));
        r1 = vAdd(vMult(lhsV[1], vSet<1>(rhsV[1])), r1);
        r1 = vAdd(vMult(lhsV[2], vSet<2>(rhsV[1])), r1);
        r1 = vAdd(vMult(lhsV[3], vSet<3>(rhsV[1])), r1);

        r2 = vMult(lhsV[0], vSet<0>(rhsV[2]));
        r2 = vAdd(vMult(lhsV[1], vSet<1>(rhsV[2])), r2);
        r2 = vAdd(vMult(lhsV[2], vSet<2>(rhsV[2])), r2);
        r2 = vAdd(vMult(lhsV[3], vSet<3>(rhsV[2])), r2);

        r3 = vMult(lhsV[0], vSet<0>(rhsV[3]));
        r3 = vAdd(vMult(lhsV[1], vSet<1>(rhsV[3])), r3);
        r3 = vAdd(vMult(lhsV[2], vSet<2>(rhsV[3])), r3);
        r3 = vAdd(vMult(lhsV[3], vSet<3>(rhsV[3])), r3);

        lhsV[0] = r0;
        lhsV[1] = r1;
        lhsV[2] = r2;
        lhsV[3] = r3;
    }
}