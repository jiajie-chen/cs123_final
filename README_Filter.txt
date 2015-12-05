I made each filter have a function applyFilter() so that it can be applied to aribitrary canvases and width/heights.
That way, the filter objects only have to manage their own implementations of filtering, and the needed variables for that.
I wanted to write a SubImage class that allows iteration/mapping using lambda functions, but I ran out of time.
I wanted to do that so I could abstract out image iteration logic, which was commonly repeated code.
It would also let me extend how travesal and edge cases worked in an OOP fashion.
But I didn't, so lol.

I made Invert and Grayscale go pixel by pixel.
My edge detect filter convolutes through the seperatable Sobel kernel to get the final values.
My blur filter uses a gaussian kernel dependent on radius, which I applied as a separable kernel.
My scale uses bilinear interpolation of the backmapped points, by getting the corners of what each point borders and interpolating.
My special filter is Special 1, which is just a sharpen filter using convolution of a 3x3 sharpen kernel.