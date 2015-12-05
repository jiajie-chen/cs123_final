I decided to make mouseDown create a new Brush everytime it is called.
On mouseDown(), a new Brush is allocated for drawing, and on mouseUp(), it is deallocated.
While it would be better to only update the brush when settings are changed, the lack of event-driven structure made me decide to update the brush everytime the user wants to begin a new stroke instead.
Canvas2d now also holds a Brush object for the mouse functions to use to paint.
I also had SmudgeBrush inherit from QuadraticBrush, and also made pickUpPaint() a public method (so it can be called in Canvas2d).
I didn't implement special brushes or alpha blending fixes.
I had all masks and buffers be allocated upon Brush creation, and deallocated upon Brush destruction. Updating the radius deallocates the old mask and reallocated a newly sized mask.

