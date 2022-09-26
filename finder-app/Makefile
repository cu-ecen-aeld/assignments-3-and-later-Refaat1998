CROSS_COMPILE = 
temp = $(CROSS_COMPILE)

all:
ifeq ($(strip $(temp)),)
	echo "CROSS_COMPILE not specified"
	rm -f writer
	gcc -o writer writer.c
else
	echo "CROSS_COMPILE specified"
	rm -f writer
	aarch64-none-linux-gnu-gcc -o writer writer.c
endif

clean:
	rm -f writer
	
