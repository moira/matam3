CC = gcc
OBJS = mtmFlixTestEx.o mtmflix.o user.o series.o utilities.o mtm_ex3.o
EXEC = prog
DEBUG_FLAG = # now empty, assign -g for debug 
COMP_FLAG = -std=c99 -Wall -Werror -pedantic-errors -DNDEBUG
LIN_FLAG = -L. -lmtm
$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) $(LIN_FLAG)
mtmFlixTestEx.o : mtmFlixTestEx.c mtmflix.h user.h utilities.h series.h user.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
mtmflix.o : mtmflix.c mtmflix.h user.h series.h utilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
user.o : user.c user.h utilities.h mtmflix.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
series.o : series.c series.h utilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
utilities.o : utilities.c utilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
clean:
	rm -f $(OBJS) $(EXEC)