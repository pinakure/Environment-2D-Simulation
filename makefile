ifdef NDEBUG
CFLAGS=`allegro-config --cflags` -DLINUX=1 -DFULLSCREEN -DNDEBUG=1 -O3
LDFLAGS=`allegro-config --libs` -O3
else
CFLAGS=`allegro-config --cflags` -DLINUX=1 -D_DEBUG=1 -g
LDFLAGS=`allegro-config --libs` -g
endif

#lista de archivos de entrada llamada 'OBJECT', luego lo tomaremos como referencia
HLINE=---------------------------------------------------
PROGRAM=environment
OBJECT=Common.o \
	Enviroment.o \
	Fire.o \
	Profile.o \
	Rain.o \
	Sky.o \
	Smoke.o \
	Snow.o \
	Thunder.o \
	Video.o \
	Water.o \
	Main.o
#esta es una regla de sufijo, todos los archivos con esta entrada se compilan de esta forma:
# El simbolo $< se reemplaza por el archivo de entrada (ruta/????.c) y $@ por la salida
%.o : %.c
	@echo Compiling $<...
	@gcc $(CFLAGS) -c $< -o $@

%.o : %.asm
	@echo Assembling $<...
	@nasm -felf $< -o $@

all : $(PROGRAM)

$(PROGRAM) : $(OBJECT)
	@echo $(HLINE)
	@echo Linking $(PROGRAM)...
	@gcc -DFULLSCREEN $(CFLAGS) -o $(PROGRAM) $(OBJECT) `allegro-config --libs` -lm
	@echo $(HLINE)

clean :
	@echo Cleaning project...
	@rm -f $(OBJECT) $(PROGRAM)
