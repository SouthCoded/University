/*
 * Ticker-tape serializer RPC definitions
 */

typedef string msg_t<79>;

struct submit_args {
  msg_t msg;
};
struct submit_result {
  bool ok;
};
struct request_resource_args {
  msg_t message;
  int time;
  int process_id;
  int physical_time;
  int server_id;
};

program TICKER_PROG {
  version TICKER_VERS {
    submit_result TICKER_SUBMIT (submit_args) = 1;
    void TICKER_REQUEST_RESOURCE (request_resource_args) = 2;
  } = 1;
} = 400001;


