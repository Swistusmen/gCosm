#include "SavedFilm.h"

SavedFilm::SavedFilm(ProgramConfig driver):AudioVideoSource(driver){
      //working for mp4
      sendLaunch="( filesrc location=" + driver.LoadFile+" ! qtdemux name=d d. ! queue ! rtph264pay pt=96 name=pay0 d. ! queue ! rtpmp4apay pt=97 name=pay1 )";
      listenLaunch="rtspsrc location="+driver.Protocol+"://"+driver.IpAddress+ ":"+driver.ListeningPort  +driver.AddressPath +" name=src src. ! decodebin ! x264enc ! queue ! mp4mux name=mux ! filesink location="+driver.SaveFile+ " src. ! decodebin  ! audioconvert ! voaacenc bitrate=128 ! queue ! mux.";
}

