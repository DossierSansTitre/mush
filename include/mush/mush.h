#ifndef MUSH_MUSH_H
#define MUSH_MUSH_H

struct mush_ctx_;

typedef struct mush_ctx_ mush_ctx;

/*
 * init.c
 */

mush_ctx*   mush_init();
void        mush_quit(mush_ctx* ctx);

/*
 * dump.c
 */

void        mush_dump(mush_ctx* ctx);

#endif
