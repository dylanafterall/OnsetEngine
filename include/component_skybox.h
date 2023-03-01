// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_skybox.h
//  header: component to designate the skybox entity in EnTT
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SKYBOX_H
#define COMPONENT_SKYBOX_H

/** 
 * \brief   The SkyboxComponent struct.
 * \details A struct only made for identifying the skybox entity when navigating
 *          the EnTT registry.
 */
struct SkyboxComponent {
    /**
     * \brief Skybox ID, only used for identifying the skybox entity.
     */
    int m_id = 0;
};

#endif // COMPONENT_SKYBOX_H