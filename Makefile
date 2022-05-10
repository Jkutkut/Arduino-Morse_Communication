# Colors:
NC			=	\033[0m
LRED		=	\033[0;31m
GREEN		=	\033[0;32m
LRED		=	\033[1;31m
LGREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
LBLUE		=	\033[1;34m
TITLE		=	\033[38;5;33m


BIN = ./out
SRC = ./src


all:

re: clean

clean:
	@echo "${RED}Removing Arduino directory${NC} \c"
	@rm -rf $(BIN)
	@echo "${GREEN}[OK]${NC}"