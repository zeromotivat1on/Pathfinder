#include "../inc/libmx.h"

char *mx_file_to_str(const char *file) {
	if(!file) return NULL;
	int _file = open(file, O_RDONLY);
	int _file_for_count = open(file, O_RDONLY);
	if(_file < 0){
		close(_file); 
		write(2, "error: file ", mx_strlen("error: file "));
		write(2, file, mx_strlen(file));
		write(2, " does not exist\n", mx_strlen(" does not exist\n"));
		exit(0);
	}
	int filelen = 0;
	char buff;
    while(read(_file_for_count, &buff, 1)) filelen++;
	if(filelen == 0) return NULL;
	char *str = mx_strnew(filelen);
	read(_file, str, filelen);
	close(_file);
	return str;
}
