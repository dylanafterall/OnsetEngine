// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_material.h
//  header: component to hold material data
// -----------------------------------------------------------------------------
#ifndef COMPONENT_MATERIAL_H
#define COMPONENT_MATERIAL_H

/** 
 * \brief   The MaterialComponent struct.
 * \details A struct to hold data pertaining to mesh surface properties needed 
 *          in OpenGL rendering.
 */
struct MaterialComponent {
    /**
     * \brief Scalar value representing the degree of surface shininess (light 
     *        reflection).
     */
    float m_shininess;
};

#endif // COMPONENT_MATERIAL_H