BUILD_DIR=$(CURDIR)/build

pdf: tex
	cd $(BUILD_DIR) && pdflatex main.tex && cp main.pdf ../cp-library.pdf

tex: main.py temp.tex
	mkdir -p $(BUILD_DIR) && python main.py > $(BUILD_DIR)/main.tex
