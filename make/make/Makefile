

CC = g++
CCFLAGS = -std=c++11 -pthread -g 

RM = rm
RMFLAGS = -fr

MKDIR = mkdir 


DIR_STATIC = static

SRCS = $(wildcard *.cc)
SRCS_B = $(wildcard b/*.cc)


OBJS = $(patsubst %.cc, %.o, $(SRCS))
OBJS_STATIC = $(addprefix $(DIR_STATIC)/, $(OBJS))

OBJS_B = $(patsubst %.cc, %.o, $(SRCS_B))
OBJS_B_STATIC = $(addprefix $(DIR_STATIC)/, $(OBJS_B))


DIRS = $(DIR_STATIC) $(DIR_STATIC)/b

$(DIRS):
	$(MKDIR) $@



all:$(DIRS) $(OBJS_STATIC) $(OBJS_B_STATIC)

$(DIR_STATIC)/%.o : %.cc  
	$(CC) -o $@ -c $^ $(CCFLAGS)


test:
	@echo $(SRCS)
	
	@echo $(OBJS)
	@echo $(OBJS_B)

clean:
	$(RM) $(RMFLAGS) $(DIRS)