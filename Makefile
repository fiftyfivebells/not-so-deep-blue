CXX			= g++
RM			= rm -rf
LIB     = -lpthread
WARNING = -Wall -Wextra -Werror=return-type
NAME	  = chess

INCLUDE = -I include/
SRC_DIR = ./src
OBJ_DIR = $(SRC_DIR)/obj

SOURCES = $(wildcard $(SRC_DIR)/*.cc)
SRC_OBJECTS = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SOURCES:.cc=.o))

all: $(NAME)

$(NAME):	$(SRC_OBJECTS) #$(OBJECTS)
	$(CXX) $(WARNING) -o $@ $^ $(LIB)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CXX) -c $(WARNING) -o $@ $^ $(INCLUDE) $(LIB)

clean:
	$(RM) $(SRC_OBJECTS) $(NAME) $(OBJ_DIR) *.tar

run:	$(NAME)
	./$(NAME)

.PHONY: clean run
