// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_color.h
//  header: component to hold color (testing light reflection) data
// -----------------------------------------------------------------------------
#ifndef COMPONENT_COLOR_H
#define COMPONENT_COLOR_H

/** 
 * \brief   The ColorComponent struct.
 * \details A struct to hold data pertaining to a test subject to examine light
 *          reflection in OpenGL rendering.
 */
struct ColorComponent {
    /**
     * \brief Color ID, only used for testing light reflection while rendering.
     */
    int m_id = 0;
};

#endif // COMPONENT_COLOR_H