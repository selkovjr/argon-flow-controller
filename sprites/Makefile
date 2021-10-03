.PHONY: sprites

LAST=255
SPRITES := $(shell seq 0 1 $(LAST))

all: sprites dial_headers dial_face.h trigger_state.h

sprites: dial_face.png
	convert "$<" -depth 8 -crop 8x8 +adjoin PNG32:dial_face_%d.sprite.png

.INTERMEDIATE:  $(patsubst %,dial_face_%.sprite.png,$(SPRITES))

dial_face.h: dial_headers
	./collate-dial-sprite-headers > $@
	cp $@ ../flow_controller/

dial_headers: $(patsubst %,dial_face_%.h,$(SPRITES))

%.h: %.sprite.png
	./png2c/png2c "$<"



dial_face.im: generate-dial-face
	./$< > $@

dial_face.png: dial_face.im
	convert -depth 8 -background black -size 128x128 -strokewidth 1 xc: -font Noto-Sans-ExtraLight -pointsize 12 -set colorspace RGB -draw @"$<" -colorspace sRGB PNG32:$@

dial_face.scaled.png: dial_face.im
	convert -background black -size 128x128 xc: -draw @"$<" -scale 500% $@




trigger_state.h: \
	trigger_state_t2i.h \
	trigger_state_t2p.h \
	trigger_state_t2r.h \
	trigger_state_t4p1.h \
	trigger_state_t4r1.h \
	trigger_state_t4p2.h \
	trigger_state_t4r2.h \

	./collate-trigger-state-sprite-headers > $@
	cp $@ ../flow_controller/

trigger_state_%.sprite.png: trigger_state_%.im
	convert -depth 8 -background black -size 45x16 -strokewidth 1 xc: -font Noto-Sans-ExtraLight -pointsize 10 -set colorspace RGB -draw @"$<" -colorspace sRGB PNG32:$@

trigger_state_t2i.im: generate-trigger-pictogram
	./$< t2 i > $@

trigger_state_t2p.im: generate-trigger-pictogram
	./$< t2 p > $@

trigger_state_t2r.im: generate-trigger-pictogram
	./$< t2 r > $@

trigger_state_t4p1.im: generate-trigger-pictogram
	./$< t4 p1> $@

trigger_state_t4r1.im: generate-trigger-pictogram
	./$< t4 r1> $@

trigger_state_t4p2.im: generate-trigger-pictogram
	./$< t4 p2> $@

trigger_state_t4r2.im: generate-trigger-pictogram
	./$< t4 r2> $@


clean:
	rm -f dial_face* trigger*
