I changed ImplicitShape's findIntersection to return a Intersection struct, which holds the information for the intersection it found.
As well as the t value and the normal, this struct now holds the UV coordinate of the intersection.
I split Ray into RecursiveRay and IlluminationRay, which handle the recursive raytracing and illumination, respectively.
Ray.h now holds the MAX_DEPTH needed for recursive reflections.
RecursiveRay now handles recursive reflections, and adds up all the contributions of illumination, ambient, and reflections.
IlluminationRay now handles all the illumination for a single light: diffuse (with UV mapping) and specular, for both point and directional lights.
It also handles shadows and detection of occluding objects.
I added checks for the raytracing setting (I only used useReflections, useTextures, use*Lights, and useShadows).
I had no extra credit.