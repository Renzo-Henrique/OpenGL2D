all:
	g++ -o trabalhocg main.cpp source/*.cpp  -lGL -lGLU -lglut

run: clean all
	./trabalhocg

clean:
	rm -rf source/*.o
	rm -rf *.o
	rm -rf trabalhocg

valgrind: all
	valgrind -s --error-limit=no ./trabalhocg