.PHONY: all clean build rebuild test

# Project configuration
PROJECT_NAME = Design Patterns
BUILD_DIR = build

# Default target
all: build

# Create build directory and generate CMake files
cmake_init:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake ..

# Build the project
build: cmake_init
	@echo "Building $(PROJECT_NAME)..."
	@cd $(BUILD_DIR) && make -j$(shell nproc)
	@echo "Build complete!"

# Clean build directory
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
	@echo "Clean complete!"

# Rebuild the project
rebuild: clean build



# Show help
help:
	@echo "Available targets:"
	@echo "  make          - Build the project"
	@echo "  make clean    - Clean build files"
	@echo "  make rebuild  - Clean and rebuild"
	@echo "  make help     - Show this help message"

