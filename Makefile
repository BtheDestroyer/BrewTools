export ROOT :=$(CURDIR)

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
install-windows: windows-install
windows-install:
	@echo "##### Building and installing for Windows™ development #####"
	@$(MAKE) --no-print-directory -fMakefileWin install MAKEFILE="$(ROOT)/MakefileWin"
	@echo "##### Build and install for Windows™ development complete! #####"

install-3ds: 3ds-install
3ds-install:
	@echo "##### Building and installing for Nintendo 3DS™ development #####"
	@$(MAKE) --no-print-directory -fMakefile3DS install MAKEFILE="$(ROOT)/Makefile3DS"
	@echo "##### Build and install for Nintendo 3DS™ development complete! #####"

install-wiiu: wiiu-install
wiiu-install:
	@echo "##### Building and installing for Wii U™ development #####"
	@$(MAKE) --no-print-directory -fMakefileWiiU install MAKEFILE="$(ROOT)/MakefileWiiU"
	@echo "##### Build and install for Wii U™ development complete! #####"

#---------------------------------------------------------------------------------
# Tutorials
#---------------------------------------------------------------------------------
tutorial: windows-tutorial 3ds-tutorial wiiu-tutorial

tutorial-windows: windows-tutorial
windows-tutorial:
	@echo "##### How to use BrewTools in Windows™ development #####"
	@echo "1. Build the library for Windows™ with one of the following commands:"
	@echo "    make windows"
	@echo "    make all"
	@echo "2. Copy the file ./lib/libbrewtoolswin.a into your project's ./libs/ folder."
	@echo "    NOTE: Read the license to ensure you're using it correctly."
	@echo "3. Copy the files ./win-libs/libglad.a and ./win-libs/libglfw3.a into your project's ./libs/ folder."
	@echo "    NOTE: Read the licenses to ensure you're using them correctly."
	@echo "4. Copy the files from ./include into your project's ./include/ folder."
	@echo "5. Copy the files from ./win-libs/include into your project's ./include/ folder."
	@echo "6. Copy the files from ./UserMakefiles into your project's root folder."
	@echo "7. Check out our wiki for a programming tutorial: https://github.com/BtheDestroyer/BrewTools/wiki"

tutorial-3ds: 3ds-tutorial
3ds-tutorial:
	@echo "##### How to use BrewTools in Nintendo 3DS™ development #####"
	@echo "1. Build and install the library for Nintendo 3DS™ with one of the following commands:"
	@echo "    make 3ds-install"
	@echo "    make install-3ds"
	@echo "    make all-install"
	@echo "    make install-all"
	@echo "2. Copy the files from ./UserMakefiles into your project's root folder."
	@echo "3. Check out our wiki for a programming tutorial: https://github.com/BtheDestroyer/BrewTools/wiki"
	

tutorial-wiiu: windows-tutorial
wiiu-tutorial:
	@echo "##### How to use BrewTools in Wii U™ development #####"
	@echo "1. Build and install the library for Wii U™ with one of the following commands:"
	@echo "    make wiiu-install"
	@echo "    make install-wiiu"
	@echo "    make all-install"
	@echo "    make install-all"
	@echo "2. Copy the files from ./UserMakefiles into your project's root folder."
	@echo "3. Check out our wiki for a programming tutorial: https://github.com/BtheDestroyer/BrewTools/wiki"
	
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
	@rm -rf $(BUILD) lib docs/html
	@echo "##### Clean complete! #####"

#---------------------------------------------------------------------------------
