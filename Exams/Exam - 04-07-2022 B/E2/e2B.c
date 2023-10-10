#include "e2B.h"
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int time_to_int(const char* time){
	char buf[5];
	int res = sprintf(buf, "%c%c%c%c", time[0], time[1], time[3], time[4]);
	return atoi(buf);
}

void getBookingsAfterTime(struct booking ** list, const char * filename, const char * time){
	
	* list = NULL;
	struct booking * last = NULL;
	struct booking * elem;
	
	
	int fd = open(filename, O_RDONLY, S_IRWXU);
	if(fd == -1){
		perror("open");
		exit(EXIT_FAILURE);
	}
	
	int size = lseek(fd, 0, SEEK_END);
	//handle
	lseek(fd, 0, SEEK_SET);

	char* buf = (char*)malloc(size*sizeof(char));
	char* pointer_for_free = buf;
	
	int res_read = read(fd, buf, size);
	//handle
	
	int i = 0;
	while(i < size){
		
		char* _surname = strtok(buf, "_");
		//handle
		char* surname = (char*)calloc(strlen(_surname),sizeof(char));
		strcpy(surname, _surname);
		
		
		char _places[3];
		int res_printf1 = sprintf(_places, "%c%c", buf[30], buf[31]);
		//handle
		int places = atoi(_places);
		
		char _time[6];
		int res_printf2 = sprintf(_time, "%c%c:%c%c", buf[32], buf[33], buf[35], buf[36]);
		//handle
		char* this_time = (char*)calloc(strlen(_time),sizeof(char));
		strcpy(this_time, _time);
		
		if(time_to_int(this_time) >= time_to_int(time)){
			elem = (struct booking *)malloc(sizeof(struct booking));
			elem -> surname = surname;
			elem -> time = this_time;
			elem -> places = places;
			elem -> next = NULL;
				
			if(*list == NULL)
				*list = elem;
			else
				last->next = elem; ///////
			last = elem;
		}
		
		i += 37;
		buf += 37;
	}
	
	free(pointer_for_free);
	close(fd);
	
}

