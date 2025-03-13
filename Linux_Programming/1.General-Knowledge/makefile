.PHONY:



CUR_DIR := .
HEADER_DIR := $(CUR_DIR)/Header
SOURCE_DIR := $(CUR_DIR)/Source
OBJS_DIR := $(CUR_DIR)/objs
BIN_DIR := $(CUR_DIR)/bin
LIBS_DIR := $(CUR_DIR)/libs
ADMIN_DIR := $(CUR_DIR)/admin_lib
LIBS_STATIC_DIR := $(LIBS_DIR)/static
LIBS_SHARED_DIR := $(LIBS_DIR)/shared
LIBS_SHARED_NAME_DIR := hello
LIBS_STATIC_NAME_DIR := HELLO
#create the object file shared
create_shared:
	gcc -c -o $(OBJS_DIR)/main.o main.c -I $(HEADER_DIR)
	gcc -c -fPIC -o $(OBJS_DIR)/hello.o $(SOURCE_DIR)/hello.c
	gcc -c -fPIC -o $(OBJS_DIR)/my_sum.o $(SOURCE_DIR)/my_sum.c

#create the object file static
create_static:
	gcc -c -o $(OBJS_DIR)/main.o main.c -I $(HEADER_DIR)
	gcc -c $(SOURCE_DIR)/hello.c -o $(OBJS_DIR)/hello.o
	gcc -c $(SOURCE_DIR)/my_sum.c -o $(OBJS_DIR)/my_sum.o
#create the share lib file 

share_libs: 
	gcc -shared $(OBJS_DIR)/hello.o $(OBJS_DIR)/my_sum.o -o $(LIBS_SHARED_DIR)/lib$(LIBS_SHARED_NAME_DIR).so
link_share_libs:
	gcc  $(OBJS_DIR)/main.o -L$(LIBS_SHARED_DIR) -l$(LIBS_SHARED_NAME_DIR) -o $(BIN_DIR)/output_share
install_share_libs:
	install $(LIBS_SHARED_DIR)/lib$(LIBS_SHARED_NAME_DIR).so $(ADMIN_DIR)

#create the static lib file

static_lib:
	ar rcs $(LIBS_STATIC_DIR)/lib$(LIBS_STATIC_NAME_DIR).a $(OBJS_DIR)/hello.o $(OBJS_DIR)/my_sum.o
link_static_libs:
	gcc $(OBJS_DIR)/main.o -L$(LIBS_STATIC_DIR) -l$(LIBS_STATIC_NAME_DIR) -o $(BIN_DIR)/output_static
install_static_libs:
	install $(LIBS_STATIC_DIR)/lib$(LIBS_STATIC_NAME_DIR).a $(ADMIN_DIR)

# make all shared lib
all_sharelibs: create_shared share_libs link_share_libs 
	@echo "make all target share lib"
#make all static lib
all_staticlibs: create_static static_lib link_static_libs
	@echo "make all target static lib"

# clean
clean_o:
	rm -rf $(OBJS_DIR)/*.o 
clean_share_libs:
	rm -rf $(LIBS_SHARED_DIR)/*.so

clean_static_libs:
	rm -rf $(LIBS_STATIC_DIR)/*.a


clean_share_bin:
	rm -rf $(BIN_DIR)/output_share


clean_static_bin:
	rm -rf $(BIN_DIR)/output_static


clean_share: clean_o clean_share_libs clean_share_bin
	@echo "clean all target"
	
clean_static: clean_o clean_static_libs clean_static_bin
