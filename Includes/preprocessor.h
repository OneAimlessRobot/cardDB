
#define PROGRAMPATHAUX "/home/oar_X_I/cardDB"
#define RESOURCES_PATH PROGRAMPATHAUX "/resources"
#define CARDS_PATH RESOURCES_PATH "/useable.txt"
#define CARDS_DUMP_PATH RESOURCES_PATH "/dump.txt"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>
#include "auxFuncs.h"
#include "hasher.h"
#include "comparator.h"
#include "nodes.h"
#include "doublelistcomp.h"
#include "hashtablecomp.h"
#include "BSTcomp.h"
#include "cmdstruct.h"
#include "hashtablecmd.h"
#include "card.h"
#include "../cmdModules/Includes/maincmds.h"
