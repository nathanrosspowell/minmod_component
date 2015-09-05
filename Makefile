SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.h)  $(wildcard src/*.inl)
CXXFLAGS = -std=c++1y
COMMON_DOC_FLAGS = --report --merge docs --output html $(SOURCES) $(HEADERS)

doc:
	@echo "Generating documentation..."; \
	cldoc generate $(CXXFLAGS) -- $(COMMON_DOC_FLAGS)

static-doc:
	@echo "Generating static documentation..."; \
	cldoc generate $(CXXFLAGS) -- --static $(COMMON_DOC_FLAGS)

serve:
	cldoc serve html
