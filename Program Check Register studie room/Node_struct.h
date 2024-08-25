#ifndef NODESTRUCT_H
#define NODESTRUCT_H

typedef enum {
    KI,
    Tr_Vien_Kh,
    MaLop,
    MaLopKem,
    MaHP,
    Ten_HP_ENG,
    Khoi_luong,
    Buoi_so,
    Thu,
    Thoi_gain,
    Tuan,
    Phong,
    Can_TN,
    SL_Max,
    Loai_lop,
    Dot_mo,
    TeachingType,
    NUM_FIELDS // Number of fields
} ID;

typedef struct {
    char *total_data[NUM_FIELDS];
} NODE_DATA;

typedef struct List_Data {
    NODE_DATA *data;
    struct List_Data *next;
} List_Data;

typedef enum{
    FLAG_SUBJECT = (3 << 2),
    FLAG_TIME = (3 << 3)
}typecompare_flag;

#endif