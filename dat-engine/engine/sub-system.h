//
// Created by jacob on 28/07/23.
//

#pragma once

// Predef
class DatEngine;

struct ISubSystem {
    const DatEngine* engine;

    ISubSystem(DatEngine* engine) : engine(engine){}
};