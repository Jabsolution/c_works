#ifndef MSG_H
#define MSG_H

#define ADR_REQ 0xFE10
#define FSZ_REQ 0xFE20
#define GET_REQ 0xFE30

#define ADR_RPLY 0xFE11
#define FSZ_RPLY 0xFE21
#define GET_RPLY 0xFE31

#define ADR_FAIL 0xFE12
#define FSZ_FAIL 0xFE22
#define GET_FAIL 0xFE32

#define ALL_FAIL 0xFCFE

typedef struct _packet {
    unsigned short m_type;
    unsigned int data_len;
    char *data;
} packet;

#endif
