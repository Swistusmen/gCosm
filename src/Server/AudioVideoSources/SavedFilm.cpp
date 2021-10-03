#include "SavedFilm.h"

SavedFilm::SavedFilm(ProgramConfig driver):AudioVideoSource(driver){
      sendLaunch="( filesrc location=" + driver.LoadFile+" ! qtdemux name=d d. ! queue ! rtph264pay pt=96 name=pay0 d. ! queue ! rtpmp4apay pt=97 name=pay1 )";
      listenLaunch=" rtspsrc location="+ driver.Protocol+"://"+driver.IpAddress+ ":"+driver.ListeningPort  +driver.AddressPath+ " ! rtph264depay ! h264parse ! mp4mux ! filesink location="+driver.SaveFile;
}
