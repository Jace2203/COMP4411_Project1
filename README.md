# Impressionist

Impressionist is an interactive program that creates pictures that look like impressionistic paintings. It is based on a paper and a program by Paul Haeberli. Here is the web "Paint by Numbers".
To create an impressionistic picture, the user loads an existing image and paints a seqence of "brush strokes" onto a blank pixel canvas. These brush strokes pick up color from the original image, giving the look of a painting.

## TODO:

### Required Tasks:

- [x] Implement 5 different brush types: single line, scattered lines, scattered points, (filled) circles, and scattered (filled) circles. See the sample solution for an example of each brush's appearance. Note that scattered brushes should sample from each location they color individually, not just use a single color for each splotch.
- [x] Add sliders to control various brush attributes. You need to include sliders for the line thickness and brush angle, in addition to the existing brush size slider.
- [x] Add the ability to control the brush direction. The stroke direction should be controlled four different ways: using a slider value, using the right mouse button to drag out a direction line, using the direction of the cursor movement, and using directions that are perpendicular to the gradient of the image. You can use a radio box to allow the user to select which method to use.
- [x] Allow the user to change the opacity (alpha value) of the brush stroke. An alpha value slider should be added to the controls window.

### Extra Tasks:

| Task      | Done |
| -| -- |
| W per new brush |
| W border clipping | ✔ |
| W (red) marker | 	✔ |
| W swap | 	✔ |
| B RGB scale | ✔ |
| B 1 level undo | 	✔ |
| B dissolve |
| BW fade in/out input on output canvas |
| BW mural (blending) | ✔ |
| BW alpha brush | ✔ |
| BW automatic paint whole image |
| BW gradient from user-specified image | ✔ |
| BW edge clipping | ✔ |
| 2B user-specified kernel | ✔ |
| 2B edge detection + user-specified edge clipping | ✔ |
| 2B multiresolution |
| 2B warp brush |
| 2B curved brush following image gradient |
| 4B mosaic |
| 4B impressionist video with temporal coherency |
| 8B Bayesian matting |