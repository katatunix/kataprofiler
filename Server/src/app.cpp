#include "app.h"
#include "glHook.h"
#include "GlHelper.h"
#include "thread/thread.h"
#include "net/Socket.h"
#include "net/Listener.h"
#include "log.h"

#define VERSION "2.3"
const int PORT = 38301;

extern GlPointers glPointers;
GlHelper glHelper(glPointers);
Server server(glHelper);

Listener listener;
Thread serverThread;

void callback(void*)
{
	LOGI("Server thread: begin");

	listener.start(PORT);

	const int REQUEST_CODE_CAPTURE = 0;
	const int REQUEST_CODE_MODIFY_PROGRAM = 1;

	while (listener.isListening())
	{
		LOGI("Waiting for a(nother) client at port %d ...", PORT);
		Socket client = listener.accept();
		LOGI("A client accepted!!!");

		client.setReceiveTimeout(10000);
		Messenger messenger(client);
		
		if (server.isBusy())
		{
			messenger.sendRequestError("Server is busy now, please try again later");
			messenger.close();
			continue;
		}
		
		int requestCode = -1;
		if (!messenger.receiveInt(requestCode))
		{
			messenger.close();
			continue;
		}

		switch (requestCode)
		{
		case REQUEST_CODE_CAPTURE:
		{
			LOGI("Request: CAPTURE");
			CaptureOption co = messenger.receiveCaptureOption();
			server.onRequestCapture(messenger, co);
			server.enterPreCapture();
			break;
		}
		case REQUEST_CODE_MODIFY_PROGRAM:
		{
			LOGI("Request: MODIFY_PROGRAM");
			server.onRequestModifyProgram(messenger);
			server.enterModifyingProgram();
			break;
		}
		}
	}
	LOGI("Server thread: end");
}

void startServerThread()
{
	LOGI("===================================================");
	LOGI("                KataProfiler %s", VERSION);
	LOGI("===================================================");

	initHook(&server);
	serverThread.start(callback, NULL);
}

void stopServerThread()
{
	listener.close();
	serverThread.join();
}
