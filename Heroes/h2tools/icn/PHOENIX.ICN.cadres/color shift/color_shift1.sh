convert $1 -alpha on -channel rgba \
	-fill "#FC580Dff" -opaque "#A40000ff" \
	-fill "#A40000ff" -opaque "#C01400ff" \
	-fill "#C01400ff" -opaque "#DC3404ff" \
	-fill "#DC3404ff" -opaque "#FC580Cff" \
	-fill "#FC580Cff" -opaque "#FC580Dff" \
	"frame3.png"
	
for i in {2..0}; do
#color shifting: FC580C, DC3404, C01400, A40000
convert "frame"$(($i + 1))".png" -alpha on -channel rgba \
	-fill "#FC580Dff" -opaque "#A40000ff" \
	-fill "#A40000ff" -opaque "#C01400ff" \
	-fill "#C01400ff" -opaque "#DC3404ff" \
	-fill "#DC3404ff" -opaque "#FC580Cff" \
	-fill "#FC580Cff" -opaque "#FC580Dff" \
	"frame"$i".png"
done