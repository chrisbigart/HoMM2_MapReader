list=`ls *.bmp`
echo "list=$list"
for file in $list; do
filename=$(basename "$file")
filename="${filename%.*}"
convert $filename.bmp -alpha on -channel rgba \
	-fill "rgba(1.0,1.0,1.0,0)" -opaque "#00ffffff" \
	-fill "rgba(0.5,0.5,0.5,0.4)" -opaque "#ff00ffff" \
	-fill "rgba(0.5,0.5,0.5,0.3)" -opaque "#ff32ffff" \
	-fill "rgba(0.5,0.5,0.5,0.2)" -opaque "#ff64ffff" \
	-fill "rgba(0.5,0.5,0.5,0.1)" -opaque "#ff96ffff" \
	-fill "rgba(1.0,1.0,1.0,0)" -opaque "#ffff00ff" \
	-fill "rgba(0.5,0.5,0.5,0.4)" -opaque "#b400ffff" \
	$filename.png
ImageResizer.exe //load $filename.png //resize auto "XBRz 4x" //save $filename"_4x.png"
done