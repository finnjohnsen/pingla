build-cljs:
	rm -Rf data/www/*
	cd cljs; clj -M -m cljs.main --optimizations advanced -c pingla.main; cd .. ;
	mv cljs/out/main.js data/www/
	cp cljs/resources/public/index.html data/www/

clean:
	rm -Rf cljs/out
	rm data/www/*

build:
	pio run -e d1_mini

upload:
	pio run -e d1_mini --target upload

monitor:
	pio device monitor

upload-files:
	pio run --target buildfs --environment d1_mini 
	pio run --target uploadfs --environment d1_mini

bum: build upload monitor
cu: build-cljs upload-files