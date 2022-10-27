// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_render.cpp
//  implementation of Render System 
// -----------------------------------------------------------------------------

#include "system_render.hpp"

void RenderSystem::update(const float timeStep, entt::registry& registry) {
    // retrieve a view of entities with the BodyPolygonComponent
    auto polygons = registry.view<BodyPolygonComponent>();
    // iterate over each entity in the view
    polygons.each([&](const auto& body) {
        int vertexCount = body.m_polygonShape.m_count;
    	int vertexDataPoints = vertexCount * 8;
    	
        // construct an array of vertex info for OpenGL with:
    	//	3 floats for position x/y/z,
    	//	3 floats for color r/g/b,
    	//	2 floats for texture coords,
        // for each vertex point
    	float vertices[vertexDataPoints];

    	// populate the array
        for (int i = 0; i < vertexCount; i++) {
    		b2Vec2 vertex = body.m_polygonShape.m_vertices[i];
    		float x = vertex.x;
    		float y = vertex.y;
    		vertices[(i * 8)] = x;			// position x coord
    		vertices[(i * 8) + 1] = y;		// position y coord
    		vertices[(i * 8) + 2] = 0.0f;	// position z coord
    		vertices[(i * 8) + 3] = 1.0f;	// color r value	
    		vertices[(i * 8) + 4] = 1.0f;	// color g value
    		vertices[(i * 8) + 5] = 1.0f;	// color b value
    		vertices[(i * 8) + 6] = 1.0f;
    		vertices[(i * 8) + 7] = 1.0f;
    	}      
    });

    // retrieve a view of entities with the BodyCircleComponent
    auto circles = registry.view<BodyCircleComponent>();
    // iterate over each entity in the view
    circles.each([&](const auto& body) {     
    });
}
