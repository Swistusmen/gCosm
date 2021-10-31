#include "HLSServer.h"

HLSServer::HLSServer(ProgramConfig config, DataChunk& dataChunk,std::shared_ptr<PipelineManager> pipManager): StreamingServer(config,dataChunk,pipManager)
{
    std::cout<<"HlS constructor\n";
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
    SetupForListening();
    g_main_loop_run(loop);
}

void HLSServer::SetupForListening(){
    std::string pipelineDescription=pipelineManager->getPipeline();
    std::cout<<pipelineDescription<<std::endl;

    pipeline=gst_parse_launch_full (pipelineDescription.c_str(), NULL, GST_PARSE_FLAG_FATAL_ERRORS, &error);
    if (!pipeline || error) {
        g_printerr ("Unable to build pipeline: %s", error->message ? error->message : "(no debug)");
    }
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}