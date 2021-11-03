#include "HLSServer.h"

HLSServer::HLSServer(ProgramConfig config, DataChunk& dataChunk,std::shared_ptr<PipelineManager> pipManager): StreamingServer(config,dataChunk,pipManager)
{
    gst_init(NULL,NULL);
    loop=g_main_loop_new(NULL,FALSE);
}

HLSServer::~HLSServer(){
    if(pipeline){
        gst_element_set_state(pipeline,GST_STATE_NULL);
        gst_object_unref(pipeline);
    }
    g_main_loop_unref(loop);
}

void HLSServer::run(){
    std::string pipelineDescription=pipelineManager->getPipeline();
    setupPipeline(pipelineDescription);
    g_main_loop_run(loop);
}

void HLSServer::setupPipeline(std::string pipelineDescription){
    std::cout<<pipelineDescription<<std::endl;
    pipeline=gst_parse_launch_full (pipelineDescription.c_str(), NULL, GST_PARSE_FLAG_FATAL_ERRORS, &error);
    if (!pipeline || error) {
        g_printerr ("Unable to build pipeline: %s", error->message ? error->message : "(no debug)");
    }
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    bus=gst_element_get_bus(pipeline);
    gst_bus_add_signal_watch(bus);
    g_signal_connect( G_OBJECT(bus),"message::eos",(GCallback)onEOSCallback,pipeline);
    gst_object_unref(bus);
}

void HLSServer::onEOSCallback(GstBus* bus, GstElement* pipeline){
    gst_element_set_state(pipeline,GST_STATE_NULL);
    gst_object_unref(pipeline);
    g_main_loop_quit(loop);
}