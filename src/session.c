#include <stdlib.h>
#include "session.h"

session *session_create(mud_connection *connection, scrollback *output_data, history *hist, input_line *input_data)
{
    if(!connection) return NULL;
    if(!output_data) return NULL;
    if(!hist) return NULL;
    if(!input_data) return NULL;

    session *session = malloc(sizeof(session));
    session->connection = connection;
    session->output_data = output_data;
    session->hist = hist;
    session->input_data = input_data;

    session->last_search_result.line_number = -1;
    session->last_search_result.begin_index = -1;
    session->last_search_result.end_index = -1;

    return session;
}

void session_destroy(session *session)
{
    if(!session) return;

    mud_connection_destroy(session->connection);
    scrollback_destroy(session->output_data);
    history_destroy(session->hist);
    input_line_destroy(session->input_data);
    free(session);
}