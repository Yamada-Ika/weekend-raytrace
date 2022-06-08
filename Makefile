build:
	@c++ -std=c++11 -I . main.cc -o raytrace

run: build
	@./raytrace

write:
	make run > image.ppm

clean:
	@rm -rf *.out *.o
