#include <cstdio>
#include <sqlite3.h>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

const char* db_file_path = "./test.db";

const int DAY_CODE[] = {64, 1, 2, 4, 8, 16, 32};

static int callback(void* arg, int num_col, char** col_val, char **col_name) {
	printf("----------- Print Row ------------\n");
	for (int i=0; i < num_col; i++) {
		printf("%s: %s\n", col_name[i], col_val[i]);
	}
	printf("======== Print Row End =========\n");
	return 0;
}

int main(int argc, char** argv) {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc = sqlite3_open(db_file_path, &db);
	int day_code;
	time_t raw_time;
	tm * time_info;
	time(&raw_time);
	time_info = localtime(&raw_time);
	
	day_code = DAY_CODE[time_info->tm_wday];
	// cout << day_code << endl;
	int current_hour = time_info->tm_hour;
	int current_min = time_info->tm_min;
	
	if (rc) {
		fprintf(stderr, "Cannot open db file :%s\n", db_file_path);
		return 0;
	} else {
		printf("DB file open Success\n");
	}
	
	char *sql = "SELECT `id`, `name`, `hour`, `min`, `day`, `enabled` FROM weekly_alarm;";
	printf("SQL: %s\n", sql)
	rc = sqlite3_exec(db, sql, callback, (void*)0, &zErrMsg);
	
	if (SQLITE_OK != rc) {
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		printf("SELECT Operation Done Successfully\n");
	}
	sqlite3_close(db);
}