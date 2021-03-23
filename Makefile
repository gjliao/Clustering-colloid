EXEC = clustering-colloid

all:
	@echo "Checking files..."
	@cd src; make --no-print-directory EXEC=$(EXEC);
	@ln -sf bin/$(EXEC) .

clean:
	@echo "Romoving files..."
	@cd src; make --no-print-directory clean;
	@echo "Removing $(EXEC)..."
	@rm -f bin/$(EXEC)
