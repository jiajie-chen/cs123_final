I edited the OpenGLScene to make m_uniformLoc protected.
I mainly edited Scene.*, to parse and store the flatten scenegraph, and SceneviewScene.*, which actually draws the scene.

Scene first parses the global and lighting settings. Then it recursively traverses the scenegraph, and flattens it, storing it in m_primitives.
I edited the CS123SceneData to hold a CS123FlattenedNode struct to hold this flattened primitive.
When a primitive is added, I also adjust the material to have no texture and scale the diffuse and abmient by kd and ka.

SceneviewScene draws a scene by iterating through the flattened nodes and drawing each primitive, with material and cumulative transform.
It sets the material, then sets the uniform of "m" to the CTM, and then draws the type of shape.
I use a Proxy format to hold the shapes, so each shape in CS123FlattenedNode is a enum type, and SceneviewScene holds the actual shapes to draw.
SceneviewScene has only a single instance of each shape, for efficiency. The shapes are made with a set tesselation value.