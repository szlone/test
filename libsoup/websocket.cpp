// server with websocket connection sample
#include <string>
#include <thread>
#include <chrono>
#include <iostream>
#include <cassert>
#include <boost/filesystem/string_file.hpp>
#include <libsoup/soup.h>

using std::string, std::cout, std::endl;
using namespace std::chrono_literals;
using boost::filesystem::load_string_file;

constexpr int SERVER_PORT = 40001;

string page_source;

void server_http_handler(SoupServer * server, SoupMessage * message,
	char const * path, GHashTable * query, SoupClientContext * client, gpointer user_data);

void server_websocket_handler(SoupServer * server, SoupWebsocketConnection * connection,
	char const * path, SoupClientContext * client, gpointer user_data);

void websocket_message_handler(SoupWebsocketConnection * connection,
	SoupWebsocketDataType data_type, GBytes * message, gpointer user_data);

int main(int argc, char * argv[])
{
	load_string_file("websocket.html", page_source);

	SoupServer * server = soup_server_new(SOUP_SERVER_SERVER_HEADER, "test soap server", nullptr);
	assert(server);

	soup_server_add_handler(server, "/", server_http_handler, nullptr, nullptr);
	soup_server_add_websocket_handler(server, "/ws", nullptr, nullptr, server_websocket_handler, nullptr, nullptr);
	soup_server_listen_all(server, SERVER_PORT, (SoupServerListenOptions)0, nullptr);

	cout << "page link: http://127.0.0.1:" << SERVER_PORT << "\n";

	GMainLoop * loop = g_main_loop_new(nullptr, FALSE);
	assert(loop);

	g_main_loop_run(loop);

	// clean up
	g_object_unref(G_OBJECT(server));
	g_main_loop_unref(loop);

	cout << "done!\n";

	return 0;
}

void server_http_handler(SoupServer * server, SoupMessage * message,
	char const * path, GHashTable * query, SoupClientContext * client, gpointer user_data)
{
	cout << "http request received" << endl;

	SoupBuffer * page_buf = soup_buffer_new(SOUP_MEMORY_STATIC, page_source.c_str(), size(page_source));
	assert(page_buf);

	soup_message_headers_set_content_type(message->response_headers, "text/html", nullptr);
	soup_message_body_append_buffer(message->response_body, page_buf);

	soup_buffer_free(page_buf);

	soup_message_set_status(message, SOUP_STATUS_OK);
}

void server_websocket_handler(SoupServer * server, SoupWebsocketConnection * connection,
	char const * path, SoupClientContext * client, gpointer user_data)
{
	cout << "websocket connection request received" << endl;

	g_object_ref(G_OBJECT(connection));
	g_signal_connect(G_OBJECT(connection), "message", G_CALLBACK(websocket_message_handler), nullptr);
}

void websocket_message_handler(SoupWebsocketConnection * connection,
	SoupWebsocketDataType data_type, GBytes * message, gpointer user_data)
{
	gchar * msg_str = nullptr;  // received message as string

	switch (data_type)
	{
		case SOUP_WEBSOCKET_DATA_BINARY:
		{
			cout << "websocket: unknown binary message received, ignored" << endl;
			return;
		}

		case SOUP_WEBSOCKET_DATA_TEXT:
		{
			gsize size;
			gchar * data = (gchar *)g_bytes_get_data(message, &size);
			msg_str = g_strndup(data, size);
			break;
		}

		default:
			assert(0);
	}

	cout << "ws >> " << msg_str << endl;

	g_free(msg_str);
}
