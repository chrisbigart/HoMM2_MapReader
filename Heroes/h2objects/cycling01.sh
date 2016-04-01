
#color shifting: 
	#FC580C			DC3404			C01400			A40000
	#(252, 88, 12, 255)	(220, 52, 4, 255)	(192, 20, 0, 255)	(164, 0, 0, 255)
#additional intermediary colors:
#0	#F4500B		#(252, 88, 12, 255)
	#1	#		#(244, 76, 9, 255)
	#2	#		#(232, 64, 7, 255)
#3	#DC3404		#(220, 52, 4, 255)
	#4	#		#(211, 41, 3, 255)
	#5	#		#(202, 30, 1, 255)	
#6	#C01400		#(192, 20, 0, 255)
	#7	#		#(184, 13, 0, 255)
	#8	#		#(172, 7, 0, 255)
#9	#A40000		#(164, 0, 0, 255)
convert $1 -alpha on -channel rgba \
	-fill "#FC580Dff" -opaque "#A40000ff" \	
	-fill "#A40000ff" -opaque "rgba(172, 7, 0, 255)" \
	-fill "rgba(172, 7, 0, 255)" -opaque "rgba(184, 13, 0, 255)" \
	-fill "rgba(184, 13, 0, 255)" -opaque "#C01400ff" \	
	-fill "#C01400ff" -opaque "rgba(202, 30, 1, 255)" \
	-fill "rgba(202, 30, 1, 255)" -opaque "rgba(211, 41, 3, 255)" \
	-fill "rgba(211, 41, 3, 255)" -opaque "#DC3404ff" \	
	-fill "#DC3404ff" -opaque "rgba(232, 64, 7, 255)" \
	-fill "rgba(232, 64, 7, 255)" -opaque "rgba(244, 76, 9, 255)" \
	-fill "rgba(244, 76, 9, 255)" -opaque "#FC580Cff" \	
	-fill "#FC580Cff" -opaque "#FC580Dff" \
	"frame0.png"
	
for i in {0..8}; do
convert "frame"$i".png" -alpha on -channel rgba \
	-fill "#FC580Dff" -opaque "#A40000ff" \	
	-fill "#A40000ff" -opaque "rgba(172, 7, 0, 255)" \
	-fill "rgba(172, 7, 0, 255)" -opaque "rgba(184, 13, 0, 255)" \
	-fill "rgba(184, 13, 0, 255)" -opaque "#C01400ff" \	
	-fill "#C01400ff" -opaque "rgba(202, 30, 1, 255)" \
	-fill "rgba(202, 30, 1, 255)" -opaque "rgba(211, 41, 3, 255)" \
	-fill "rgba(211, 41, 3, 255)" -opaque "#DC3404ff" \	
	-fill "#DC3404ff" -opaque "rgba(232, 64, 7, 255)" \
	-fill "rgba(232, 64, 7, 255)" -opaque "rgba(244, 76, 9, 255)" \
	-fill "rgba(244, 76, 9, 255)" -opaque "#FC580Cff" \	
	-fill "#FC580Cff" -opaque "#FC580Dff" \
	"frame"$(($i + 1))".png"
done