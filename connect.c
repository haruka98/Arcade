#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <libpq-fe.h>
#include <windows.h>

#include "header.h"


int connect_to_psql() {
	int cned = 0;
	char conninfo[256];
	PGresult *result = NULL;
	char caddr[] = "192.168.178.52";
	int cport = 5432;
	char cdb[] = "highscore";
	char cname[256] = "root";
	char cpwd[256] = "123456";
	PGconn* connection = NULL;
	sprintf(conninfo, "user=%s password=%s dbname=%s hostaddr=%s port=%d", cname, cpwd, cdb, caddr, cport);
	connection = PQconnectdb(conninfo);

	if (PQstatus(connection) != CONNECTION_OK) {
		PQfinish(connection);
		cned = 0;
	} else {
		cned = 1; 
	}
	if(cned == 1) {
		result = PQexec(connection, "INSERT INTO \"public\".\"highscore\" VALUES ('', '');");
		PQclear(result);
	}
	
	
	PQfinish(connection);
	return 0;
}