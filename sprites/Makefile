.PHONY: sprites

all: face

face: \
	dial_face.png \
	dial_face.scaled.png \
	sprites \
	headers \

dial_face_%.h: dial_face_%.png
	./png2c/png2c "$<"

headers: $(addsuffix .h, $(basename $(wildcard *.sprite.png)))

dial_face.im: generate-dial-face
	./$< > $@

dial_face.png: dial_face.im
	convert -depth 8 -background black -size 128x128 xc: -font Noto-Sans-ExtraLight -pointsize 12 -set colorspace RGB -draw @"$<" -colorspace sRGB PNG32:$@

dial_face.scaled.png: dial_face.im
	convert -background black -size 128x128 xc: -draw @"$<" -scale 500% $@

sprites: dial_face.png
	convert "$<" -depth 8 -crop 8x8 +adjoin PNG32:dial_face_%d.sprite.png

clean:
	rm dial_face*
