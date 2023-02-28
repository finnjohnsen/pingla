build-cljs:
	rm -Rf data/www/*
	cd cljs; clj -M -m cljs.main --optimizations advanced -c pingla.main; cd .. ;
	mv cljs/out/main.js data/www/
	cp cljs/resources/public/index.html data/www/

clean:
	rm -Rf cljs/out
	rm data/www/*