I edited RayScene and Scene so they take in a copy constructor, and copies the scene data. This is for setting up a RayScene.
MainWindow and Canvas2D then use this to construct a RayScene for rendering.
My ray casting code was consolidated in Ray, which handled all intersection and illumination. I wanted to extend this in the next project to have IlluminationRay and RecursiveRay.
I wanted to keep coordinate systems confined to relevant classes. Film coordinates are only in RayScene, world coordinates in Ray, and object coordinates only in ImplicitShape.
I edited Camera to have a getScaleMatrix, and implemented it in CamtransCamera and OrbitCamera. This was for world<->object matrices.
I decided to write my shapes using a new class, ImplicitShape, because my normal shapes had different functionality than what I needed for Intersect.
I wrote all my single object intersection code in the ImplicitShape classes, with helpers. I also accounted for floating point error in those classes.
I didn't have any extra credit.
