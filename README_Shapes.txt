I made a Shape class that handles the drawing and generation of vertices and normals.
The Shape class uses an OpenGLShape to do all the OpenGL call to assign vertex and attribute data.
I extended this class to Cube, Cone, Cylinder, and Sphere to generate these shapes based on tesselation.

I edited OpenGLScene to have a settingsChanged() method, so ShapesScene could update the shape when settings are changed.
ShapesScene holds a vector of Shapes, and draws the repectively selected shape.
When a shape's tesselation is updated, the Shape updates its vertices (if it requires updating).