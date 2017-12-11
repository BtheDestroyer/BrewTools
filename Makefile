export ROOT :=$(CURDIR)

#---------------------------------------------------------------------------------
# Build all libs
#---------------------------------------------------------------------------------

all:
	@echo "########## Building and installing all versions ##########"
	@echo ""
	@$(MAKE) --no-print-directory windows
	@echo ""
	@$(MAKE) --no-print-directory 3ds
	@echo ""
	@$(MAKE) --no-print-directory wiiu
	@echo ""
	@echo "########## All builds complete! ##########"
	@echo ""

all-install:
	@echo "########## Building and installing all versions ##########"
	@echo ""
	@$(MAKE) --no-print-directory windows-install
	@echo ""
	@$(MAKE) --no-print-directory 3ds-install
	@echo ""
	@$(MAKE) --no-print-directory wiiu-install
	@echo ""
	@echo "########## All builds complete! ##########"
	@echo ""

#---------------------------------------------------------------------------------
# Builds
#---------------------------------------------------------------------------------

windows:
	@echo "##### Building for Windows™ development #####"
	@$(MAKE) --no-print-directory -fMakefileWin MAKEFILE="$(ROOT)/MakefileWin"
	@echo "##### Build for Windows™ development complete! #####"

3ds:
	@echo "##### Building for Nintendo 3DS™ development #####"
	@$(MAKE) --no-print-directory -fMakefile3DS MAKEFILE="$(ROOT)/Makefile3DS"
	@echo "##### Build for Nintendo 3DS™ development complete! #####"

wiiu:
	@echo "##### Building for Wii U™ development #####"
	@$(MAKE) --no-print-directory -fMakefileWiiU MAKEFILE="$(ROOT)/MakefileWiiU"
	@echo "##### Build for Wii U™ development complete! #####"

#---------------------------------------------------------------------------------
# Installs
#---------------------------------------------------------------------------------

windows-install:
	@echo "##### Building and installing for Windows™ development #####"
	@$(MAKE) --no-print-directory -fMakefileWin install MAKEFILE="$(ROOT)/MakefileWin"
	@echo "##### Build and install for Windows™ development complete! #####"

3ds-install:
	@echo "##### Building and installing for Nintendo 3DS™ development #####"
	@$(MAKE) --no-print-directory -fMakefile3DS install MAKEFILE="$(ROOT)/Makefile3DS"
	@echo "##### Build and install for Nintendo 3DS™ development complete! #####"

wiiu-install:
	@echo "##### Building and installing for Wii U™ development #####"
	@$(MAKE) --no-print-directory -fMakefileWiiU install MAKEFILE="$(ROOT)/MakefileWiiU"
	@echo "##### Build and install for Wii U™ development complete! #####"

#---------------------------------------------------------------------------------
# Documentation generation
#---------------------------------------------------------------------------------
docs:
	@doxygen Doxyfile

#---------------------------------------------------------------------------------
# Cleanup
#---------------------------------------------------------------------------------

clean:
	@echo "##### Cleaning all builds! #####"
	@rm -rf build dependencies lib latex html 
	@echo "##### Clean complete! #####"

#---------------------------------------------------------------------------------
