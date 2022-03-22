#include "header.h"

/* Working with time*/
void timewait(char* wait,int hours, int minutes, int secundes){
   if(waitinfo.tm_hour < 24){

          waitinfo.tm_hour += hours;
          waitinfo.tm_min  += minutes;
          waitinfo.tm_sec  += secundes;

       if(waitinfo.tm_min > 59){
          waitinfo.tm_hour += waitinfo.tm_min/60;
          waitinfo.tm_min  = waitinfo.tm_min%60;
       }
       if(waitinfo.tm_sec > 59){
          waitinfo.tm_min += waitinfo.tm_sec/60;
          waitinfo.tm_sec  = waitinfo.tm_sec%60;
       }
       strftime(wait, 51, "%H:%M:%S", &waitinfo);
       //printf("%s \n", wait);
       if(waitinfo.tm_sec == 0){
            if(waitinfo.tm_min != 0){
               waitinfo.tm_sec = 60;
               waitinfo.tm_min--;
            }
        }
        if(waitinfo.tm_min == 0){
            if(waitinfo.tm_hour != 0){
               waitinfo.tm_min = 59;
               waitinfo.tm_hour--;
            }
        }
   }
}

void pega_hora(char* data){
      /* pega data atual */
	  time_t currentTime;
	  struct tm timeinfo;
	  currentTime = time(NULL);
      timeinfo = *localtime(&currentTime);

	  /* Cria a string com os codigos de fomatacao no formato:
	    hora:minuto:segundo. */
      //strftime (char*, size_t, const char*, const struct tm*);
	  strftime(data, 51, "%H:%M:%S", &timeinfo);
}

void pega_dataehora(char* data){
	  /* pega data atual */
	  time_t currentTime;
	  struct tm *timeinfo;
	  currentTime = time(NULL);
	  timeinfo = localtime(&currentTime);
      mktime(timeinfo);
	  /* Cria a string com os codigos de fomatacao no formato:
	   dia/mes/ano -- hora:minuto:segundo AM/PM. */
	  strftime(data, 26, "%d/%m/%Y -- %H:%M:%S %p", timeinfo);
}

void pega_data(char* data){
	  /* pega data atual */
	  time_t currentTime;
	  struct tm *timeinfo;
	  currentTime = time(NULL);
	  timeinfo = localtime(&currentTime);

	  /* Cria a string com os codigos de fomatacao no formato:
	   dia/mes/ano. */
	  strftime(data, 51, "%d/%m/%Y", timeinfo);
}

void data_arq(char* data){
	  /* pega data atual */
	  time_t currentTime;
	  struct tm *timeinfo;
	  currentTime = time(NULL);
	  timeinfo = localtime(&currentTime);

	  /* Cria a string com os codigos de fomatacao no formato:
	   dia/mes/ano. */

	  strftime(data, 51, "%d-%m-%Y", timeinfo);
}

void get_mes(char* data){
	  /* pega data atual */
	  time_t currentTime;
	  struct tm *timeinfo;
	  currentTime = time(NULL);
	  timeinfo = localtime(&currentTime);

	  /* Cria a string com os codigos de fomatacao no formato:
	   dia/mes/ano. */

	  strftime(data, 51, "%m-%Y", timeinfo);
}

void get_year(char* data){
	  /* pega data atual */
	  time_t currentTime;
	  struct tm *timeinfo;
	  currentTime = time(NULL);
	  timeinfo = localtime(&currentTime);

	  /* Cria a string com os codigos de fomatacao no formato:
	   dia/mes/ano. */

	  strftime(data, 51, "%Y", timeinfo);
}
