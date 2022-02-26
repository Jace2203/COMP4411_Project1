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
| B dissolve | ✔ |
| BW fade in/out input on output canvas | ✔ |
| BW mural (blending) | ✔ |
| BW alpha brush | ✔ |
| BW automatic paint whole image | ✔ |
| BW gradient from user-specified image | ✔ |
| BW edge clipping | ✔ |
| 2B user-specified kernel | ✔ |
| 2B edge detection + user-specified edge clipping | ✔ |
| 2B multiresolution |
| 2B warp brush |
| 2B curved brush following image gradient | ✔ |
| 4B mosaic | ✔ |
| 4B impressionist video with temporal coherency |
| 8B Bayesian matting |

### HOW TO USE:
1. To change brushes or brush attributes, select File > Brushes. On the pop-up window "Brush Dialog", set the desired attributes. Blur, Sharp and Curved brushes are included in "Brush" selections.

2. To apply swap, select Edit > Swap.

3. To apply RGB scale, select File > Color. On the pop-up window "Color Dialog", select the scale by choosing the color directly onthe color board on entering the corresponing color codes.

4. To undo any brush stroke, select Edit > Undo.

5. To apply dissolve, select Edit > Dissolve.

6. To apply fade in/out, select File > Add Faded Background. On the pop-up window "Fade Dialog", select the degree of transparent for the fade-in background.

7. To apply mural, select File > New Mural Image. Choose the images with the same size as the current loaded one to mural.
   
8. To apply alpha brush, select File > Alpha Mapped Brush. On pop-up window "Brush Dialog", select brush type "Alpha Mapped". This brush will not be affected by other attributes.

9.  To apply automatic paint, select File > Brushes. On the pop-up window "Brush Dialog", select the desired point spacing and whether to apply random size. Click "Paint" to automatically paint whole image.

10. To apply gradient from another image, select File > Load Another Image. On the pop-up window "Brush Dialog", click the "Another Gradient" button. If line brush is selected and the stroke type is gradient, the effect will be applied.

11. To apply user specified kernel, select File > Kernel. On the pop-up window "Customize Kernel Dialog", type in the kernel as the following format:
> 1,2,1,
> 2,4,2,
> 1,2,1

- New line is a new row
- Each number is followed by a comma (Not for the last number)
- Normalize the kernel by pressing the button "Normalized"
- Apply the kerenl by pressing the button "Apply Kernel"

12. To do edge clipping, on the pop-up window "Brush Dialog, click the "Edge Clipping" button. If line brush is selected, the effect will be applied.
To apply another edge image, select File > Load Edge Image.

13.   To do mosaic, select Mosaics. On the pop-up window, press "Preprocess" to preprocess images in "images/unprocessed" (feel free to add more images). Then press "Mosaic", the image will be stored in "images/mosaic" named "result.bmp".