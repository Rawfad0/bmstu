REPORT_DIR  := report
SLIDES_DIR  := slides
RELEASE_DIR := ./release

REPORT_TEX    := $(REPORT_DIR)/report.tex
REPORT_PARTS  := $(wildcard $(REPORT_DIR)/*.tex)
REPORT_IMGS   := $(wildcard $(REPORT_DIR)/images/*)
REPORT_PDF    := $(REPORT_DIR)/report.pdf
GS_REPORT_PDF := $(RELEASE_DIR)/report.pdf

SLIDES_SRC_PDF := $(firstword $(wildcard $(SLIDES_DIR)/*.pdf))
SLIDES_PPTX = $(firstword $(wildcard $(SLIDES_DIR)/*.pptx))
SLIDES_PPTX_BASE := $(basename $(notdir $(SLIDES_PPTX)))
SLIDES_PPTX_PDF  := $(SLIDES_DIR)/$(SLIDES_PPTX_BASE).pdf

SLIDES_PDF     := $(SLIDES_DIR)/slides.pdf
GS_SLIDES_PDF  := $(RELEASE_DIR)/slides.pdf

LIBREOFFICE := libreoffice

TEMP_EXT := aux log out toc bbl blg bcf run.xml lof lot

.PHONY: clean gs

gs: $(GS_REPORT_PDF)

$(GS_REPORT_PDF): $(REPORT_PDF)
	mkdir -p $(RELEASE_DIR)
	gs -sDEVICE=pdfwrite \
		-dCompatibilityLevel=1.4 \
		-dNOPAUSE \
		-dOptimize=true \
		-dQUIET \
		-dBATCH \
		-dRemoveUnusedFonts=true \
		-dRemoveUnusedImages=true \
		-dOptimizeResources=true \
		-dDetectDuplicateImages \
		-dCompressFonts=true \
		-dEmbedAllFonts=true \
		-dSubsetFonts=true \
		-dPreserveAnnots=true \
		-dPreserveMarkedContent=true \
		-dPreserveOverprintSettings=true \
		-dPreserveHalftoneInfo=true \
		-dPreserveOPIComments=true \
		-dPreserveDeviceN=true \
		-dMaxInlineImageSize=0 \
		-sOutputFile=$@ \
		$<
	rm -f $<

$(REPORT_PDF): $(REPORT_TEX) $(REPORT_PARTS) $(REPORT_IMGS)
	mkdir -p $(RELEASE_DIR)
	cd $(REPORT_DIR) && pdflatex -interaction=nonstopmode report.tex
	cd $(REPORT_DIR) && bibtex report || true
	cd $(REPORT_DIR) && pdflatex -interaction=nonstopmode report.tex
	cd $(REPORT_DIR) && pdflatex -interaction=nonstopmode report.tex
	for ext in $(TEMP_EXT); do \
		find $(REPORT_DIR) -name "*.$$ext" -delete; \
	done

$(GS_SLIDES_PDF): $(SLIDES_PDF)
	gs -sDEVICE=pdfwrite \
		-dCompatibilityLevel=1.4 \
		-dNOPAUSE \
		-dOptimize=true \
		-dQUIET \
		-dBATCH \
		-dRemoveUnusedFonts=true \
		-dRemoveUnusedImages=true \
		-dOptimizeResources=true \
		-dDetectDuplicateImages \
		-dCompressFonts=true \
		-dEmbedAllFonts=true \
		-dSubsetFonts=true \
		-dPreserveAnnots=true \
		-dPreserveMarkedContent=true \
		-dPreserveOverprintSettings=true \
		-dPreserveHalftoneInfo=true \
		-dPreserveOPIComments=true \
		-dPreserveDeviceN=true \
		-dMaxInlineImageSize=0 \
		-sOutputFile=$@ \
		$<
	rm -f $<


$(SLIDES_PDF): $(SLIDES_PPTX)
	mkdir -p $(RELEASE_DIR)
	$(LIBREOFFICE) --headless --convert-to pdf --outdir $(SLIDES_DIR) "$(SLIDES_PPTX)"
	rm -f $(RELEASE_DIR)/*.backup

clean:
	for ext in $(TEMP_EXT); do \
		find $(REPORT_DIR) -name "*.$$ext" -delete; \
	done
	rm -f $(REPORT_DIR)/report.pdf
	rm -f $(RELEASE_DIR)/*