cp-library: build main.tex style.sty format.py .clang-format
	pdflatex -shell-escape -output-directory build/ main.tex && cp build/main.pdf cp-library.pdf

build:
	mkdir -p build/

.PHONY: clean
clean:
	trash build
