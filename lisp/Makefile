default:
	./compile pr03.lisp

install:
	wget http://iweb.dl.sourceforge.net/project/sbcl/sbcl/1.3.2/sbcl-1.3.2-x86-64-linux-binary.tar.bz2;\
	bzip2 -d sbcl-1.3.2-x86-64-linux-binary.tar.bz2;\
	mkdir sbcl;\
	tar xvf sbcl-1.3.2-x86-64-linux-binary.tar -C sbcl --strip-components=1;\
	rm sbcl-1.3.2-x86-64-linux-binary.tar;\
	chmod +x compile run;

clean:
	\rm -f *.fasl

clean-all:
	\rm -rf sbcl/
