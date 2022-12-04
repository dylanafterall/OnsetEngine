// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_light.h
//  header: component to hold light (point source) datas
// -----------------------------------------------------------------------------
#ifndef COMPONENT_LIGHT_H
#define COMPONENT_LIGHT_H

/** 
 * \brief   The LightComponent struct.
 * \details A struct to hold data pertaining to a light source (a sphere/point
 *          source).
 */
struct LightComponent {
    /**
     * \brief Light ID, only used for identifying the light entity in registry.
     */
    int m_id = 0;
};

#endif // COMPONENT_LIGHT_H