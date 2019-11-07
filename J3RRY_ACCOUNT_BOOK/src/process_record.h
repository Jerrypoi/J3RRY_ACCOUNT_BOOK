#ifndef PROCESS_RECORD_H
#define PROCESS_RECORD_H
#include "llist.h"
#include "db_connect.h"
#include "stdio.h"
#include "stdlib.h"
#include "model.h"
llist* getTransactionByUserId(const int user_id);


#endif /*PROCESS_RECORD_H*/