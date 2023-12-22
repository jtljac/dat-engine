//
// Created by jacob on 29/07/23.
//

#pragma once

/**
 * The different groups that an actor can tick with
 */
enum class TickGroup {

    /**
     * The default tick-group, occurs before physics is calculated
     * <br>
     * Actions like movement should be handled here so they can be factored into physics
     * <br>
     * Physics and collision data will be a frame old here
     */
    PRE_PHYSICS,

    /**
     * This tick-group occurs at the same time as physics calculations
     * <br>
     * Actions that do not affect the physics simulation, or does not care about the physics simulation should occur here.
     * For example, UI operations.
     * <br>
     * There is no guarantee or indication of the physics and collision data being of the previous or current frame
     */
    PHYSICS,

    /**
     * This tick-group occurs after the physics simulation has completed
     * <br>
     * Actions that depend on the physics data being up to date should occur here.
     * For example, weapon traces that depend on the weapon's position being up to date.
     * <br>
     * The physics and collision data will be from the current frame
     */
    POST_PHYSICS
};

struct TickingObject {
    bool tickEnabled = true;
    bool tickWhilePaused = false;
    TickGroup tickGroup = TickGroup::PRE_PHYSICS;


    virtual void begin(float deltaTime) = 0;
    virtual void tick(float deltaTime) = 0;
    virtual void end(float deltaTime) = 0;
};