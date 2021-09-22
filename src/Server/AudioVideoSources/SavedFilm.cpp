#include "SavedFilm.h"

SavedFilm::SavedFilm(ProgramConfig driver):AudioVideoSource(driver){
    launch=g_strdup_printf ("( "
      "filesrc location=\"%s\" ! qtdemux name=d "
      "d. ! queue ! rtph264pay pt=96 name=pay0 "
      "d. ! queue ! rtpmp4apay pt=97 name=pay1 " ")", driver.LoadFile.c_str());
}
