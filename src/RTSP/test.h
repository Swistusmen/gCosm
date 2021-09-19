#include<gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <string>

class TestRunner{
    public:
        TestRunner(std::string filename);
        void run();
    private:
        GMainLoop *loop;
        GstRTSPServer *server;
        GstRTSPMountPoints *mounts;
        GstRTSPMediaFactory *factory;
        gchar *str;
        char* port= (char*)"8554";
    private:

        static void media_configure_cb (GstRTSPMediaFactory * factory, GstRTSPMedia * media);
        static void media_prepared_cb (GstRTSPMedia * media);
};