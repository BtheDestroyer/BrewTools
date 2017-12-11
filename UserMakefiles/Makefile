export ROOT :=$(CURDIR)

include appinfo

#---------------------------------------------------------------------------------
# Build all libs
#---------------------------------------------------------------------------------

all:
	@echo "########## Building all versions ##########"
	@echo ""
	@$(MAKE) --no-print-directory windows
	@echo ""
	@$(MAKE) --no-print-directory 3ds
	@echo ""
	@$(MAKE) --no-print-directory wiiu
	@echo ""
	@echo "########## All builds complete! ##########"
	@echo ""

#---------------------------------------------------------------------------------
# Builds
#---------------------------------------------------------------------------------

windows:
	@echo "##### Building for Windows™ #####"
	@$(MAKE) --no-print-directory -fMakefileWin MAKEFILE="$(ROOT)/MakefileWin"
	@echo "##### Build for Windows™ complete! #####"

3ds:
	@echo "##### Building for Nintendo 3DS™ #####"
	@$(MAKE) --no-print-directory -fMakefile3DS MAKEFILE="$(ROOT)/Makefile3DS"
	@echo "##### Build for Nintendo 3DS™ complete! #####"

wiiu:
	@echo "##### Building for Wii U™ #####"
	@$(MAKE) --no-print-directory -fMakefileWiiU MAKEFILE="$(ROOT)/MakefileWiiU"
	@echo "##### Build for Wii U™ complete! #####"


#---------------------------------------------------------------------------------
# Testing
#---------------------------------------------------------------------------------

windows-test: 
	@echo "##### Testing Windows™ build #####"
	@$(MAKE) --no-print-directory -fMakefileWin MAKEFILE="$(ROOT)/MakefileWin" test
	@echo "##### Test completed #####"

3ds-test:
	@echo "##### Testing Nintendo 3DS™ build #####"
	@$(MAKE) --no-print-directory -fMakefile3DS MAKEFILE="$(ROOT)/Makefile3DS" test
	@echo "##### Test completed #####"

wiiu-test:
	@echo "##### Testing Wii U™ build #####"
	@$(MAKE) --no-print-directory -fMakefileWiiU MAKEFILE="$(ROOT)/MakefileWiiU" test
	@echo "##### Test completed #####"

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
