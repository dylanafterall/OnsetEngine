// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_test.h
//  header: component to designate the rendering test entities in EnTT
// -----------------------------------------------------------------------------
#ifndef COMPONENT_TEST_H
#define COMPONENT_TEST_H

/** 
 * \brief   The TestComponent struct.
 * \details A struct only made for identifying the test entity when navigating
 *          the EnTT registry.
 */
struct TestComponent {
    /**
     * \brief Test ID, only used for identifying the test entity.
     *        m_id = 0 for quad that covers the viewport
     *        m_id = 1 for cube model
     *        m_id = 2 for plane model that acts as floor 
     */
    int m_id = 0;

    /**
     * \brief Unique OpenGL ID for a shader program (combination of a vertex and 
     *        fragment shader) for rendering a framebuffer texture to quad.
     */
    unsigned int m_testProgram;
};

#endif // COMPONENT_TEST_H