convert $1.bmp -alpha on -channel rgba -fill "rgba(1,1,1,0)" -opaque "#00ffffff" -fill "rgba(0,0,0,0.5)" -opaque "#ff00ffff" -fill "rgba(0,0,0,0.4)" -opaque "#ff32ffff" -fill "rgba(0,0,0,0.3)" -opaque "#ff64ffff" -fill "rgba(0,0,0,0.2)" -opaque "#ff96ffff" $1.png
convert $2.bmp -alpha on -channel rgba -fill "rgba(1,1,1,0)" -opaque "#00ffffff" -fill "rgba(0,0,0,0.5)" -opaque "#ff00ffff" -fill "rgba(0,0,0,0.4)" -opaque "#ff32ffff" -fill "rgba(0,0,0,0.3)" -opaque "#ff64ffff" -fill "rgba(0,0,0,0.2)" -opaque "#ff96ffff" $2.png
convert $1.png $2.png +append out.png
ImageResizer.exe //load out.png //resize auto "XBRz 4x" //save out4x.png