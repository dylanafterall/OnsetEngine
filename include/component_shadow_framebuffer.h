// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shadow_framebuffer.h
//  header: component to hold shadow framebuffer object ID  
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SHADOW_FRAMEBUFFER_H
#define COMPONENT_SHADOW_FRAMEBUFFER_H

/** 
 * \brief   The ShadowFramebufferComponent struct.
 * \details A struct to hold data pertaining to OpenGL framebuffers for 
 *          rendering shadows via depth maps.
 */
struct ShadowFramebufferComponent {
    /**
     * \brief Unique OpenGL ID for a shadow FBO w/ depth map.
     */
    unsigned int m_shadowFramebuffer;
};

#endif // COMPONENT_SHADOW_FRAMEBUFFER_H