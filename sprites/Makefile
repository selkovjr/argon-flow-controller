.PHONY: sprites

LAST=255
SPRITES := $(shell seq 0 1 $(LAST))

all: sprites headers dial_face.h

sprites: dial_face.png
	convert "$<" -depth 8 -crop 8x8 +adjoin PNG32:dial_face_%d.sprite.png

.INTERMEDIATE:  $(patsubst %,dial_face_%.sprite.png,$(SPRITES))

dial_face.h: headers
	./collate-sprite-headers > $@
	cp $@ ../flow_controller/

headers: $(patsubst %,dial_face_%.h,$(SPRITES))

dial_face_%.h: dial_face_%.sprite.png
	./png2c/png2c "$<"



dial_face.im: generate-dial-face
	./$< > $@

dial_face.png: dial_face.im
	convert -depth 8 -background black -size 128x128 -strokewidth 1 xc: -font Noto-Sans-ExtraLight -pointsize 12 -set colorspace RGB -draw @"$<" -colorspace sRGB PNG32:$@

dial_face.scaled.png: dial_face.im
	convert -background black -size 128x128 xc: -draw @"$<" -scale 500% $@


clean:
	rm -f dial_face*
