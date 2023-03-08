// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_quad.h
//  header: component to designate the player entity in EnTT
// -----------------------------------------------------------------------------
#ifndef COMPONENT_QUAD_H
#define COMPONENT_QUAD_H

/** 
 * \brief   The QuadComponent struct.
 * \details A struct only made for identifying the quad entity when navigating
 *          the EnTT registry.
 */
struct QuadComponent {
    /**
     * \brief Quad ID, only used for identifying the quad entity.
     */
    int m_id = 0;
};

#endif // COMPONENT_QUAD_H