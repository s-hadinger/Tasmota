#include "be_constobj.h"

static be_define_const_map_slots(be_class_tcpclient_map) {
    { be_const_key(available, 4), be_const_func(wc_tcp_available) },
    { be_const_key(connect, -1), be_const_func(wc_tcp_connect) },
    { be_const_key(_X2Ew, -1), be_const_var(0) },
    { be_const_key(close, 7), be_const_func(wc_tcp_close) },
    { be_const_key(connected, 6), be_const_func(wc_tcp_connected) },
    { be_const_key(flush, -1), be_const_func(wc_tcp_flush) },
    { be_const_key(deinit, -1), be_const_func(wc_tcp_deinit) },
    { be_const_key(init, -1), be_const_func(wc_tcp_init) },
};

static be_define_const_map(
    be_class_tcpclient_map,
    8
);

BE_EXPORT_VARIABLE be_define_const_class(
    be_class_tcpclient,
    1,
    NULL,
    tcpclient
);
