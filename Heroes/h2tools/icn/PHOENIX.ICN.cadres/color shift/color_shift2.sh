convert $1 -alpha on -channel rgba \
	-fill "#FC580Dff" -opaque "#A40000ff" \
	-fill "#A40000ff" -opaque "rgb(172, 7, 0)" \
	-fill "rgb(172, 7, 0)" -opaque "rgb(184, 13, 0)" \
	-fill "rgb(184, 13, 0)" -opaque "#C01400ff" \
	-fill "#C01400ff" -opaque "rgb(202, 30, 1)" \
	-fill "rgb(202, 30, 1)" -opaque "rgb(211, 41, 3)" \
	-fill "rgb(211, 41, 3)" -opaque "#DC3404ff" \
	-fill "#DC3404ff" -opaque "rgb(232, 64, 7)" \
	-fill "rgb(232, 64, 7)" -opaque "rgb(244, 76, 9)" \
	-fill "rgb(244, 76, 9)" -opaque "#FC580Cff" \
	-fill "#FC580Cff" -opaque "#FC580Dff" \
	"frame12.png"
	
for i in {11..0}; do
#color shifting: 
	#FC580C			DC3404			C01400			A40000
	#(252, 88, 12)	(220, 52, 4)	(192, 20, 0)	(164, 0, 0)
#additional intermediary colors:
#0	#F4500B		#(252, 88, 12)
	#1	#		#(244, 76, 9)
	#2	#		#(232, 64, 7)
#3	#DC3404		#(220, 52, 4)
	#4	#		#(211, 41, 3)
	#5	#		#(202, 30, 1)	
#6	#C01400		#(192, 20, 0)
	#7	#		#(184, 13, 0)
	#8	#		#(172, 7, 0)
#9	#A40000		#(164, 0, 0)


convert "frame"$(($i + 1))".png" -alpha on -channel rgba \
	-fill "#FC580Dff" -opaque "#A40000ff" \
	-fill "#A40000ff" -opaque "rgb(172, 7, 0)" \
	-fill "rgb(172, 7, 0)" -opaque "rgb(184, 13, 0)" \
	-fill "rgb(184, 13, 0)" -opaque "#C01400ff" \
	-fill "#C01400ff" -opaque "rgb(202, 30, 1)" \
	-fill "rgb(202, 30, 1)" -opaque "rgb(211, 41, 3)" \
	-fill "rgb(211, 41, 3)" -opaque "#DC3404ff" \
	-fill "#DC3404ff" -opaque "rgb(232, 64, 7)" \
	-fill "rgb(232, 64, 7)" -opaque "rgb(244, 76, 9)" \
	-fill "rgb(244, 76, 9)" -opaque "#FC580Cff" \
	-fill "#FC580Cff" -opaque "#FC580Dff" \
	"frame"$i".png"
done