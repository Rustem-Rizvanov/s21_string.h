#ifndef SRC_HEADERS_S21_SSCANF_H_
#define SRC_HEADERS_S21_SSCANF_H_

struct mods {
  int len;
  int skip;
  int h;
  int l;
  int ll;
};


// typedef struct {
//   int format;
//   long count;
//   int end;
//   int supr;
//   int wid;
//   int len;
//   int err;
//   char buff;
// } ops;

typedef struct Holder {
    int code;
    struct Holder *next;
} Holder;


typedef struct mods mods;

#endif  // SRC_HEADERS_S21_SSCANF_H_